from numpy import *
from libacepy.eintrittssystem import loadgrid

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


class vdetector(object):

    def __init__(self,func=gauss,para=[600.,0.,0.,20.,40.,40.,1.],ion="He2+",mass=4.,charge=2.,aspphi=0.,asptheta=0.,dang=0.5,drot=1.,rotaspmod=0.,loadeff=1):
        self.ionname=ion
        self.mass=mass
        self.charge=charge
        self.aspphi=aspphi
        self.asptheta=asptheta
        self.rotaspmod=rotaspmod
        epq_arr = array([86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048])
        self.scaleeq=sqrt(epq_arr/epq_arr[0])
        self.scaleion=sqrt(self.charge/self.mass)
        self.eff=loadtxt("/data/etph/ace/efficencies/%s_dcr.eff"%(self.ionname),skiprows=1)
        self.eff=self.eff[:,0]*self.eff[:,1]*self.eff[:,2]+0.15
        if loadeff==0:
            print "Efficiencies are set to 1."#self.eff=self.eff[:,1]
            self.eff[:]=1.
        self.entr=loadgrid(dang,drot)
        self.getaspunitvecs()
        self.rotasp()
        self.entr.grid[:,1]+=30.
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


    def getgridstep(self,step):
        return self.entr.grid*self.scaleeq[step]*self.scaleion

    def getVostep(self,step):
        return self.entr.Vo*self.scaleeq[step]*self.scaleion

    def getVvstep(self,step):
        return self.entr.Vv*(self.scaleeq[step]*self.scaleion)**3

    def getv0step(self,step):
        return self.entr.v0*(self.scaleeq[step]*self.scaleion)

    def calcstep(self,func,para,step):
        return [self.getv0step(step),sum(func(self.getgridstep(step),para))*self.getVvstep(step)*self.getVostep(step)*self.eff[step]]
        
    def calcspec(self,func,para):
        vspec=[]
        for step in range(58):
            vspec.append(self.calcstep(func,para,step))
        self.vspec=array(vspec)
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
        dens=self.vspec[:,1]/12./oduty/geomfac/self.eff[:]/(self.vspec[:,0])/(self.vspec[:,0]*(2.*(sqrt(1.03)-1)))
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
