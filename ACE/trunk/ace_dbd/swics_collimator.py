from numpy import *
from pylib.etCoord import rotate
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

class collimator(object):
    def __init__(self,dang_para=1.,dang_perp=1.,aspphi=0.,asptheta=0.,vel=600.,vsw=300,calc_full=True):
        """
        Class to calculate the field of view of SWICS (ACE and later on Ulysses)
        dang_para,dang_perp = Step width in degrees to calc entrance slit in parallel and perpendicular direction. Total opening angle parallel is 90 degrees, and 2 degrees perpendicular respectively
        aspphi,ansptheta = Aspect angle in degrees, i.e. orientation of the spacecraft spin axis. NOTE rotation around theta is against usual sense of direction therefore the rotaion has to be by -asptheta!!!!
        Coordinates (GSE):
        X-axis -> Pointing from Spacecraft(Earth) to Sun
        Y-axis -> Against Spacecraft orbit motion in ecliptic (against Earth movement) 
        Z-axis -> Completes the right handed triad (i.e. North)
        """
        self.dang_para = dang_para
        self.dang_perp = dang_perp
        self.aspphi = aspphi
        self.asptheta = asptheta
        self.vel=vel
        self.vsw=vsw
        self.ang_para=arange(0.,-90.001,-self.dang_para)
        self.ang_perp=arange(-2.,2.001,self.dang_perp)
        self.base_points = zeros((3,self.ang_perp.shape[0]))
        self.md1 = self.ang_para>-30.
        self.md2 = (self.ang_para<=-30.)*(self.ang_para>-60.)
        self.md3 = (self.ang_para<=-60.)*(self.ang_para>=-90.)
        self.det1 = zeros((3,self.ang_perp.shape[0]*self.ang_para[self.md1].shape[0]))
        self.det2 = zeros((3,self.ang_perp.shape[0]*self.ang_para[self.md2].shape[0]))
        self.det3 = zeros((3,self.ang_perp.shape[0]*self.ang_para[self.md3].shape[0]))
        self.calc_full = calc_full
        self._calc_points()
        self._rot_aspang()
        self._rot_seczero()
        self._calc_FoV()
        self._calc_vspace()
            
    def _calc_points(self):
        """
        Calculates the unrotatet slit, divided into detectors 1,2,3.
        """
        rax = array([cos(56./180.*pi),sin(56./180.*pi),0])
        if self.calc_full:
            for i,ang in enumerate(self.ang_perp):
                self.base_points[:,i]=array([cos(ang/180.*pi),sin(ang/180.*pi),0])
            for i,ang in enumerate(self.ang_para[self.md1]):
                self.det1[:,i*self.ang_perp.shape[0]:(i+1)*self.ang_perp.shape[0]]=rotate(self.base_points,rax,ang,deg=True).reshape(self.base_points.shape)
            for i,ang in enumerate(self.ang_para[self.md2]):
                self.det2[:,i*self.ang_perp.shape[0]:(i+1)*self.ang_perp.shape[0]]=rotate(self.base_points,rax,ang,deg=True).reshape(self.base_points.shape)
            for i,ang in enumerate(self.ang_para[self.md3]):
                self.det3[:,i*self.ang_perp.shape[0]:(i+1)*self.ang_perp.shape[0]]=rotate(self.base_points,rax,ang,deg=True).reshape(self.base_points.shape)
        else:
            self.base_points=zeros((3,1))
            self.base_points[0]=1.
            self.det1=zeros((3,1))
            self.det2=zeros((3,1))
            self.det3=zeros((3,1))
            self.det1[:,0]=rotate(self.base_points,rax,-15,deg=True)
            self.det2[:,0]=rotate(self.base_points,rax,-45,deg=True)
            self.det3[:,0]=rotate(self.base_points,rax,-75,deg=True)

    def _rot_aspang(self):
        """
        Calculates axes for spacecraft spin axis and rotates the slit to the starting position for sector 0.
        """
        # Axes for aspect phi and theta angle rotations
        self.rphiax = array([0.,0.,1.])
        self.rthetaax = rotate(array([0.,1.,0]),self.rphiax,self.aspphi,deg=True)
        # Spacecraft Z-Axis (Spacecraft rotation axis, direction mostly Sunward)
        self.rax = rotate(array([1.,0.,0.]),self.rphiax,self.aspphi,deg=True)
        self.rax = rotate(self.rax,self.rthetaax,-self.asptheta,deg=True)
        # Swics Z-Axis relative to rotation axis
        self.rzax = rotate(array([0.,0.,1.]),self.rphiax,self.aspphi,deg=True)
        self.rzax = rotate(self.rzax,self.rthetaax,-self.asptheta,deg=True)
        # Rotate detectors in phi direction
        det1_rot = rotate(self.det1,self.rphiax,self.aspphi,deg=True).reshape(self.det1.shape)
        det2_rot = rotate(self.det2,self.rphiax,self.aspphi,deg=True).reshape(self.det2.shape)
        det3_rot = rotate(self.det3,self.rphiax,self.aspphi,deg=True).reshape(self.det3.shape)
        # Rotate detectors in theta direction
        self.det1 = rotate(det1_rot,self.rthetaax,-self.asptheta,deg=True).reshape(self.det1.shape)
        self.det2 = rotate(det2_rot,self.rthetaax,-self.asptheta,deg=True).reshape(self.det2.shape)
        self.det3 = rotate(det3_rot,self.rthetaax,-self.asptheta,deg=True).reshape(self.det3.shape)
    def _rot_seczero(self):
        """
        Rotates slit to 135 degrees against sun pulse trigger,i.e. the starting position for sector 0
        """
        # Sunpulser viewing direction at spin start,i.e. start of sec0 (in plane spanned by spin axis and SC-Sun line, perpendicular to spin axis)
        self.spax = cross(self.rax,cross(array([1.,0.,0.]),self.rax))
        self.spax/=sqrt(sum(self.spax**2))
        # Sunpulser angle relative to Swics Z-Axis 
        self.spang = arccos(dot(self.spax,self.rzax))/pi*180.
        # Rotate slit to Sector 0 starting Position, i.e. rotate by 135-spang
        if self.aspphi<0.:
            self.sec0ang= 90 -self.spang
        else:
            self.sec0ang=(90 +self.spang)
        self.det1 = rotate(self.det1,self.rax,self.sec0ang,deg=True).reshape(self.det1.shape)
        self.det2 = rotate(self.det2,self.rax,self.sec0ang,deg=True).reshape(self.det2.shape)
        self.det3 = rotate(self.det3,self.rax,self.sec0ang,deg=True).reshape(self.det3.shape)

    def plot(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.set_xlim(0.,1)
        ax.set_ylim(0.,1)
        ax.set_zlim(-1.,0)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
        ax.plot(self.det1[0,:],self.det1[1,:],self.det1[2,:],"o",color="k")
        ax.plot(self.det2[0,:],self.det2[1,:],self.det2[2,:],"o",color="b")
        ax.plot(self.det3[0,:],self.det3[1,:],self.det3[2,:],"o",color="r")
        return ax

    def plot_rot(self,ang=0.,ax=None):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(0.,1)
            ax.set_ylim(-1.,1)
            ax.set_zlim(-1.,1)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        det1_rot = rotate(self.det1,self.rax,ang,deg=True).reshape(self.det1.shape)
        det2_rot = rotate(self.det2,self.rax,ang,deg=True).reshape(self.det2.shape)
        det3_rot = rotate(self.det3,self.rax,ang,deg=True).reshape(self.det3.shape)

        ax.plot(det1_rot[0,:],det1_rot[1,:],det1_rot[2,:],"o",color="k")
        ax.plot(det2_rot[0,:],det2_rot[1,:],det2_rot[2,:],"o",color="b")
        ax.plot(det3_rot[0,:],det3_rot[1,:],det3_rot[2,:],"o",color="r")
        return ax

    def _calc_FoV(self):
        if self.calc_full:
            angsteps = range(0,45,3)
            # dimensions of FoV did,sec,(x,y,z)
            self.FoV=zeros((3,8,3,150*len(angsteps)))
            for sec in range(8):
                for ang in angsteps:
                    ind = ang/3
                    self.FoV[0,sec,:,ind*150:(ind+1)*150]=rotate(self.det1,self.rax,sec*45.+ang,deg=True).reshape(self.det1.shape)
                    self.FoV[1,sec,:,ind*150:(ind+1)*150]=rotate(self.det2,self.rax,sec*45.+ang,deg=True).reshape(self.det2.shape)
                    self.FoV[2,sec,:,ind*150:(ind+1)*150]=rotate(self.det3,self.rax,sec*45.+ang,deg=True).reshape(self.det3.shape)[:,0:150]
        else:
            angstep = 22.5
            self.FoV=zeros((3,8,3,1))
            for sec in range(8):
                self.FoV[0,sec,:,0]=rotate(self.det1,self.rax,sec*45.+angstep,deg=True)
                self.FoV[1,sec,:,0]=rotate(self.det2,self.rax,sec*45.+angstep,deg=True)
                self.FoV[2,sec,:,0]=rotate(self.det3,self.rax,sec*45.+angstep,deg=True)

    def _calc_vspace(self):
        """
        convert FoV into v-space (GSE correct for SC eigen-velocity)
        """
        # first invert view direction into v-acceptance
        self.vspace=-self.FoV*self.vel
        self.vspace[:,:,1,:]-=30
        self.vspace[:,:,0,:]=-self.vspace[:,:,0,:]
        self.vspace[:,:,1,:]=-self.vspace[:,:,1,:]
        self.mv = mean(self.vspace,axis=3)
        
    def plot_detsec(self,det,sec,ax=None):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(0.,1)
            ax.set_ylim(-1.,1)
            ax.set_zlim(-1.,1)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        col = zeros(3)
        col[det]=0.1+sec*0.9/7.
        ax.plot(self.FoV[det,sec,0,:],self.FoV[det,sec,1,:],self.FoV[det,sec,2,:],"o",markersize=1.,alpha=0.5,color=col)
        return ax
    def plot_vseg(self,det,sec,ax=None):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(-2*self.vel,2*self.vel)
            ax.set_ylim(-1.*self.vel,1*self.vel)
            ax.set_zlim(-1.*self.vel,1*self.vse)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        col = zeros(3)
        col[det]=0.1+sec*0.9/7.
        ax.plot(self.vspace[det,sec,0,:],self.vspace[det,sec,1,:],self.vspace[det,sec,2,:],"o",markersize=1.,alpha=0.5,color=col)
        return ax
    def _calc_w(self):
        # first assume vsw radial
        vswspace=1.*self.vspace
        vswspace[:,:,0,:]-=self.vsw
        self.wswspace=sqrt(sum(vswspace**2,axis=2))/self.vsw
        self.wscspace=sqrt(sum(self.vspace**2,axis=2))/self.vsw
    def plot_vseg(self,det,sec,ax=None,reduced=False):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(0.,2*self.vel)
            ax.set_ylim(-1.*self.vel,1*self.vel)
            ax.set_zlim(-1.*self.vel,1*self.vse)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        col = zeros(3)
        col[det]=0.1+sec*0.9/7.
        if not reduced:
            ax.plot(self.vspace[det,sec,0,:],self.vspace[det,sec,1,:],self.vspace[det,sec,2,:],"o",markersize=1.,alpha=0.5,color=col)
        else:
            ax.plot(self.vspace[det,sec,0,:],self.vspace[det,sec,1,:],self.vspace[det,sec,2,:],"o",markersize=5.,alpha=1.,color="k")
        return ax
    def plot_FoV(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.set_xlim(0.,2.)
        ax.set_ylim(-1.,1)
        ax.set_zlim(-1.,1)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
        rotax = zeros((3,100))
        xax = zeros((3,100))
        for i in range(100):
            rotax[:,i]=i/100.*self.rax
            xax[:,i]=i/100.*array([1.,0.,0.])
        for sec in range(8):
            for det in range(3):
                self.plot_detsec(det,sec,ax=ax)
        ax.plot(rotax[0,:],rotax[1,:],rotax[2,:],color="k")
        ax.plot(xax[0,:],xax[1,:],xax[2,:],"--",color="k")
        return ax
    def plot_vspace(self,ax = None,reduced=False):
        if ax == None:
            fig = plt.figure(figsize=(9.,9.))
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(-1.*self.vel,2*self.vel)
            ax.set_ylim(-1.5*self.vel,1.5*self.vel)
            ax.set_zlim(-1.5*self.vel,1.5*self.vel)
            ax.set_xlabel("v$_{sc,x}$ [km/s]") 
            ax.set_ylabel("v$_{sc,y}$ [km/s]") 
            ax.set_zlabel("v$_{sc,z}$ [km/s]") 
        rotax = zeros((3,201))
        xax = zeros((3,201))
        for i in range(0,101,1):
            rotax[:,i]=-i/100.*self.rax*self.vel
            xax[:,i]=i/100.*array([self.vel,0.,0.])
        for sec in range(8):
            for det in range(3):
                self.plot_vseg(det,sec,ax=ax,reduced=reduced)
        ax.plot(-rotax[0,:],-rotax[1,:],rotax[2,:],".-",color="k")
        ax.plot(xax[0,:],xax[1,:],xax[2,:],color="k",lw=5)
        ax.view_init(15,190)
        ax.tick_params(pad=20)
        ax.set_xticklabels([-400,"",0,"",400,"",800,"",1200])
        return ax
