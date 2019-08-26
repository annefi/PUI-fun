from numpy import *
from libacepy.eintrittssystem import loadgrid
from pylab import *

### Wird so zu sagen als build in function benutzt um vdetector zu initialisieren falls func nicht naeher spezifiziert wird!
def gauss(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3:5] -> sigx,sigy,sigz 
    p[6]   -> total density
    grid   -> input array with points dim(N,3) [x1,y1,z1],[x2,y2,z2]...[xN,yN,zN]
    returns array with function values at grid points
    """
    x=-(grid[:,0]-p[0])**2/(2.*p[3]**2)
    y=-(grid[:,1]-p[1])**2/(2.*p[4]**2)
    z=-(grid[:,2]-p[2])**2/(2.*p[5]**2)
    return p[6]*1e15/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)


def shell(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3]   -> Radius
    p[4,5]   -> width
    p[6]   -> Intensity
    grid   -> input array with points dim(N,3) [x1,y1,z1],[x2,y2,z2]...[xN,yN,zN]
    returns array with function values at grid points
    """
    x=(grid[:,0]-p[0])
    y=(grid[:,1]-p[1])
    z=(grid[:,2]-p[2])
    r = sqrt(x**2+y**2+z**2)
    #vals = zeros(grid.shape[0])
    #vals[(r>(p[3]-p[4]/2.))*(r<(p[3]+p[4]/2.))] = p[5]
    r2 = zeros(r.shape)
    r2[(r - p[3])<0] = -(r[(r - p[3])<0] - p[3])**2/(2.*p[4]**2)
    r2[(r - p[3])>=0] = -(r[(r - p[3])>=0] - p[3])**2/(2.*p[5]**2)
    return p[6]/((2*pi)**0.5*p[4])*exp(r2)

def power_law(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3]   -> kappa
    p[4]   -> Intensity
    grid   -> input array with points dim(N,3) [x1,y1,z1],[x2,y2,z2]...[xN,yN,zN]
    returns array with function values at grid points
    """
    x=(grid[:,0]-p[0])
    y=(grid[:,1]-p[1])
    z=(grid[:,2]-p[2])
    r = sqrt(x**2+y**2+z**2)
    r+=sqrt(p[0]**2+p[1]**2+p[2]**2)
    r/=p[0]**2+p[1]**2+p[2]**2
    #vals = zeros(grid.shape[0])
    #vals[(r>(p[3]-p[4]/2.))*(r<(p[3]+p[4]/2.))] = p[5]
    return p[4]*r**p[3]


def shell_gauss(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3]   -> Radius
    p[4,5]   -> width
    p[6]   -> Intensity
    p[7:]  -> see gauss
    grid   -> input array with points dim(N,3) [x1,y1,z1],[x2,y2,z2]...[xN,yN,zN]
    returns array with function values at grid points
    """
    x=(grid[:,0]-p[0])
    y=(grid[:,1]-p[1])
    z=(grid[:,2]-p[2])
    r = sqrt(x**2+y**2+z**2)
    #vals = zeros(grid.shape[0])
    #vals[(r>(p[3]-p[4]/2.))*(r<(p[3]+p[4]/2.))] = p[5]
    r2 = zeros(r.shape)
    r2[(r - p[3])<0] = -(r[(r - p[3])<0] - p[3])**2/(2.*p[4]**2)
    r2[(r - p[3])>=0] = -(r[(r - p[3])>=0] - p[3])**2/(2.*p[5]**2)

    x=-(grid[:,0]-p[0+7])**2/(2.*p[3+7]**2)
    y=-(grid[:,1]-p[1+7])**2/(2.*p[4+7]**2)
    z=-(grid[:,2]-p[2+7])**2/(2.*p[5+7]**2)
    return p[6+7]/((2*pi)**1.5*p[3+7]*p[4+7]*p[5+7])*exp(x+y+z) + p[6]/((2*pi)**0.5*p[4])*exp(r2)

def shell_gauss_torus(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3]   -> Radius
    p[4,5]   -> width
    p[6]   -> Intensity
    p[7:]  -> see gauss
    grid   -> input array with points dim(N,3) [x1,y1,z1],[x2,y2,z2]...[xN,yN,zN]
    grid[14:] -> Torus
    returns array with function values at grid points
    """
    x=(grid[:,0]-p[0])
    y=(grid[:,1]-p[1])
    z=(grid[:,2]-p[2])
    r = sqrt(x**2+y**2+z**2)
    #vals = zeros(grid.shape[0])
    #vals[(r>(p[3]-p[4]/2.))*(r<(p[3]+p[4]/2.))] = p[5]
    r2 = zeros(r.shape)
    r2[(r - p[3])<0] = -(r[(r - p[3])<0] - p[3])**2/(2.*p[4]**2)
    r2[(r - p[3])>=0] = -(r[(r - p[3])>=0] - p[3])**2/(2.*p[5]**2)
    
    x=-(grid[:,0]-p[0+7])**2/(2.*p[3+7]**2)
    y=-(grid[:,1]-p[1+7])**2/(2.*p[4+7]**2)
    z=-(grid[:,2]-p[2+7])**2/(2.*p[5+7]**2)
    shell = p[6]/((2*pi)**0.5*p[4])*exp(r2)
    gauss = p[6+7]/((2*pi)**1.5*p[3+7]*p[4+7]*p[5+7])*exp(x+y+z)

    x=(grid[:,0]-p[0])
    y=(grid[:,1]-p[1])
    z=(grid[:,2]-p[2])

    da = -y**2/(2.*p[15]**2)
    torus = shell * p[14]*exp(da)
    return shell + gauss + torus


#return p[6]/((2*pi)**0.5*p[4])*exp(r2)

def plot_func(func,para,xbins,ybins):
    R = para[0]
    yoff = para[1]
    grid = []
    for x in range(0,1501,2):
        for y in range(-1000,1001,2):
            grid.append([float(x),float(y),0.])
    grid = array(grid)
    vals = func(grid,para)
    Hw,x,y = histogram2d(grid[:,0],grid[:,1],(xbins,ybins))
    H,x,y = histogram2d(grid[:,0],grid[:,1],(xbins,ybins),weights=vals)
    H = H/(1.*Hw)
    fig = figure()
    ax = fig.gca()
    ax.set_aspect("equal")
    ax.pcolormesh(x[:-1],y[:-1],H.T)
    ax.plot([0.,1500.],[0.,1500.*tan(58./180.*pi)],color="k")
    ax.plot([0.,1500.],[0.,-1500.*tan(58./180.*pi)],color="k")
    ax.plot([0.,1500.],[0.,1500.*tan(40./180.*pi)],color="k")
    ax.plot([0.,1500.],[0.,-1500.*tan(40./180.*pi)],color="k")
    ax.plot([0.,1500.],[0.,1500.*tan(20./180.*pi)],color="k")
    ax.plot([0.,1500.],[0.,-1500.*tan(20./180.*pi)],color="k")
    ax.plot([0.,1500.],[0.,1500.*tan(79.25/180.*pi)],color="k")
    ax.plot([0.,1500.],[0.,1500.*tan(58.75/180.*pi)],color="k")
    ax.plot([0.,1500.],[0.,0.],color="k")
    # WSC = 1 Kreis
    x = arange(0.,R+0.1,1.)
    y = sqrt(R**2-x**2.)
    ax.plot(x,y,color="k")
    ax.plot(x,-y,color="k")
    # WSC = 1.6 Kreis
    x = arange(0.,1.6*R+0.1,1.)
    y = sqrt((1.6*R)**2-x**2.)
    ax.plot(x,y,color="k")
    ax.plot(x,-y,color="k")
    # WSC = 0.5 Kreis
    x = arange(0.,R/2.+.1,1.)
    y = sqrt((R/2.)**2-x**2.)
    ax.plot(x,y,color="k")
    ax.plot(x,-y,color="k")
    # WSC = 2 Kreis
    x = arange(0.,2*R+0.1,1.)
    y = sqrt((2.*R)**2-x**2.)
    ax.plot(x,y,color="k")
    ax.plot(x,-y,color="k")
    # WSW = 1 Kreis
    x = arange(-R,R+.1,1.)
    y = sqrt(R**2-x**2.)
    ax.plot(x+R,y+yoff,color="k")
    ax.plot(x+R,-y+yoff,color="k")
    # WSW = 0.8 Kreis
    x = arange(-0.8*R,0.8*R+.1,1.)
    y = sqrt((0.8*R)**2-x**2.)
    ax.plot(x+R,y+yoff,color="k")
    ax.plot(x+R,-y+yoff,color="k")
    # WSW = = 0.5 Kreis
    x = arange(-R/2.,R/2.+.1,1.)
    y = sqrt((R/2.)**2-x**2.)
    ax.plot(x+R,y+yoff,color="k")
    ax.plot(x+R,-y+yoff,color="k")
    # SW-Bulk
    ax.plot([R],[yoff],"x",color = "k")
    ax.set_xlim(0.,4.*R)
    ax.set_ylim(-2.*R,2.*R)
    ax.set_xlabel("v$_x$")
    ax.set_ylabel("v$_y$")

    #ylim(-1000.,1000.)
class vdetector(object):
    """
    func -> eine Funktion die als Eingabe ein Gitter von Punkten (grid) und einen Satz von Parametern (para) benoetig.
    ion -> wir dzum laden der Effizienzen benoetigt.
    mass,charge -> wird zur Berechnung der Geschwindigkeiten in Abhaengigkeit von E/e benoetigt.
    aspphi,asptheta -> Aspect Angle in und aus der Ekliptik.
    dang -> Winkelschrittweite mit der das Eintrittssystem dargestellt wird
    drot -> Winkelschrittweite mit der das Eintrittssystem rotiert wird.
    rotaspmod -> Aspectangle-Transformation durch Drehung (1) oder durch Projection mit Einheitsvektoren (0)
    loadeff -> True Effizienzen werden geladen, False Eff=100%
    Winkelangaben sind alle in Grad (0:360)
    """
    def __init__(self,func=gauss,para=[600.,0.,0.,20.,40.,40.,1.],ion="He2+",mass=4.,charge=2.,aspphi=0.,asptheta=0.,dang=0.5,drot=1.,rotaspmod=0.,loadeff=True,effpath="/data/etph/ace/efficencies/"):
        self.ionname=ion
        self.mass=mass
        self.charge=charge
        self.aspphi=aspphi
        self.asptheta=asptheta
        self.rotaspmod=rotaspmod
        self.effpath=effpath
        epq_arr = array([86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048])
        self.scaleeq=sqrt(epq_arr/epq_arr[0])
        self.scaleion=sqrt(self.charge/self.mass)
        if loadeff:
            self.eff=loadtxt("%s%s.eff"%(self.effpath,self.ionname))
        else:
            self.eff=ones([58,3])
        self.entr=loadgrid(dang,drot)
        self.entr.grid[:,1]+=30. # Eigengeschwindikeit von ACE (in der Ekliptik)
        self.getaspunitvecs()
        self.rotasp()
        self.calcspec(func,para)
        
    def rotaspphi(self):
        """
        rotiert entr.grid um x-Achse (self.aspphi)
        """
        x=self.entr.grid[:,0]*cos(self.aspphi)-self.entr.grid[:,1]*sin(self.aspphi)
        y=self.entr.grid[:,1]*cos(self.aspphi)+self.entr.grid[:,0]*sin(self.aspphi)
        self.entr.grid[:,0]=x
        self.entr.grid[:,1]=y

    def rotasptheta(self):
        """
        rotiert entr.grid um y-Achse (self.asptheta)
        """
        x=self.entr.grid[:,0]*cos(self.asptheta)-self.entr.grid[:,2]*sin(self.asptheta)
        z=self.entr.grid[:,2]*cos(self.asptheta)+self.entr.grid[:,0]*sin(self.asptheta)
        self.entr.grid[:,0]=x
        self.entr.grid[:,2]=z

    def rotasp(self):
        """
        Transformiert das Eintrittssystem ueber den aspect-angle in Sun-Earth Koordinaten
        """
        if self.rotaspmod==1.:
            x=sum(self.entr.grid[:]*self.aspex,axis=1)
            y=sum(self.entr.grid[:]*self.aspey,axis=1)
            z=sum(self.entr.grid[:]*self.aspez,axis=1)
            self.entr.grid[:,0]=x
            self.entr.grid[:,1]=y
            self.entr.grid[:,2]=z
        else:
            self.rotaspphi()
            self.rotasptheta()

    def getaspunitvecs(self):
        """
        Berechnet die Einheitsvektoren des gedrehten Koordinatensystems.
        Dies Kann alternativ verwendet werden um das Eintrittssystem um den aspect-angle zu drehen -> rotaspmod=1.
        """
        def getnewex(phi,theta):
            x=sqrt(1./(1+tan(phi)**2+tan(theta)**2+tan(phi)**2*tan(theta)**2))
            y=tan(phi)*x
            z=tan(theta)*sqrt(x**2*(1+tan(phi)**2))
            if phi==pi/2.:
                x,y,z=0.,1.,0.
            if phi==-pi/2.:
                x,y,z=0.,-1.,0.
            return array([x,y,z])
        def getnewey(phi):
            y=1./sqrt(1+tan(phi)**2)
            x=-tan(phi)*y
            return array([x,y,0.])

        def getnewez(x,y):
            z1=x[1]*y[2]-x[2]*y[1]
            z2=x[2]*y[0]-x[0]*y[2]
            z3=x[0]*y[1]-x[1]*y[0]
            return array([z1,z2,z3])
        self.aspex=getnewex(self.aspphi,self.asptheta)
        self.aspey=getnewey(self.aspphi)
        self.aspez=getnewez(self.aspex,self.aspey)


    def getgridstep(self,step,mask):
        return self.entr.grid[mask]*self.scaleeq[step]*self.scaleion

    def getVostep(self,step):
        return self.entr.Vo*self.scaleeq[step]*self.scaleion

    def getVvstep(self,step):
        return self.entr.Vv*(self.scaleeq[step]*self.scaleion)**3

    def getv0step(self,step):
        return self.entr.v0*(self.scaleeq[step]*self.scaleion)

    def calcstep(self,func,para,step,mask):
        return [self.getv0step(step),sum(func(self.getgridstep(step,mask),para))*self.getVvstep(step)*self.getVostep(step)*self.eff[step][1]]
        
    def calcspec(self,func,para):
        vspec=[]
        vspecdid0=[]
        vspecdid1=[]
        vspecdid2=[]
        for step in range(58):
            vspec.append(self.calcstep(func,para,step,mask=ones(self.entr.grid.shape[0],dtype=bool)))
            vspecdid0.append(self.calcstep(func,para,step,mask=self.entr.did == 0))
            vspecdid1.append(self.calcstep(func,para,step,mask=self.entr.did == 1))
            vspecdid2.append(self.calcstep(func,para,step,mask=self.entr.did == 2))
        self.vspec=array(vspec)
        self.vspecdid0=array(vspecdid0)
        self.vspecdid1=array(vspecdid1)
        self.vspecdid2=array(vspecdid2)
        self.H = zeros((self.vspec[:,0].shape[0],3))
        self.H[:,0] = self.vspecdid0[:,1]
        self.H[:,1] = self.vspecdid1[:,1]
        self.H[:,2] = self.vspecdid2[:,1]
        mvals = amax(self.H,axis=1)
        self.H2 = 1.*self.H
        self.H2[:,0] /= mvals
        self.H2[:,1] /= mvals
        self.H2[:,2] /= mvals
        self.H2[isnan(self.H2)]=0.
        self.calcvspecmoments()
        return array(vspec)

    def calcvspecmoments(self):
        from libacepy.fluxes import dutycycle as olddutycycle
        geomfac=0.0225*1e-10
        tmpmoments=getmoments(self.vspec[:,0],self.vspec[:,1])
        self.vcrmoments=tmpmoments
        machang=(180./pi)*arctan(tmpmoments[2]/tmpmoments[1])
        oduty=olddutycycle(arccos(cos(self.aspphi)*cos(self.asptheta))/pi*180.,machang)
        print "oduty = ",oduty
        dens=self.vspec[:,1]/12./oduty/geomfac/self.eff[:,1]/(self.vspec[:,0])/(self.vspec[:,0]*(2.*(sqrt(1.03)-1)))
        self.dens=dens
        self.vmoments=getmoments(self.vspec[:,0],self.dens)

def getmoments(vel,data):
    A=0.     #-->  integral
    v0=0.    #-->  central of mass
    sigsq=0. #-->  sigma^2
    dvel=zeros([len(vel)])
    dvel[1:-1]=(vel[:-2]-vel[2:])*0.5
    dvel[0]=(vel[0]-vel[1])
    dvel[-1]=(vel[-2]-vel[-1])
    #print vel
    #print dvel
    A=sum(dvel*data)
    v0=sum(vel*data*dvel)/A
    sigsq=sqrt(sum(data*dvel*(vel-v0)**2)/A)
    return array([A,v0,sigsq])
