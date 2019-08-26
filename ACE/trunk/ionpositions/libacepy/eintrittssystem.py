from numpy import *
from Gnuplot import Gnuplot,Data

def kartokug(vec):
    return [sqrt(vec[0]**2+vec[1]**2+vec[2]**2),arctan(vec[1]/vec[0]),arctan(vec[2]/sqrt(vec[0]**2+vec[1]**2))]

def kugtokar(vec):
    return [vec[0]*sin(vec[2])*cos(vec[1]),vec[0]*sin(vec[2])*sin(vec[1]),vec[0]*cos(vec[2])]


class eintrittssystem(object):

    def __init__(self,dang=0.5,drot=1.,loaddump=1,dump=1):
        """
        Punktegitter fuer eine Rotation wird berechnet -> wird spaeter als master Gitter mit q/m und Esa-Step skaliert!
        4/dang and 360/drot should be int
        Achtung phi und theta nicht direkt Winkel in Kugelkoordinaten!
        """
        from libacepy.ancil import getvelocity
        
        self.thetamax=58.   # 0 < theta < thetamax in deg
        self.phimax=2.      # -phimax <phi< phimax in deg
        self.v0=getvelocity(1.,1.,0,1.)     # -> proton volocity at step 0 in km/s
        self.phisteps=int(4./dang)
        self.thetasteps=int(58./dang)
        self.geomfac=0.0225*1e-10#/(self.phisteps*self.thetasteps)        # instrumental geometry factor in km^2
        self.dang=4./self.phisteps
        self.rotsteps=int(360./drot)
        self.drot=360./self.rotsteps
        self.loaddump=loaddump
        self.dump=dump
        self.grid=[]
        self.cpicklename="VDgrid_%.2f_%.2f.cpic"%(self.dang,self.drot)
        self.dt=12./float(self.rotsteps)
        self.Vv=self.v0**3*(self.dang*pi/180.)**2*(2.*(sqrt(1.03)-1))
        self.Vo=self.v0*self.dt*self.geomfac
        self.getgrid()
    
    def getgrid(self):
        self.calcgrid()

    def calcgrid(self):
        # Arrays mit den Winkel erstellen!
        phis=linspace(-self.phimax+self.dang/2.,self.phimax-self.dang/2.,self.phisteps)*pi/180.
        thetas=linspace(self.dang/2.,self.thetamax-self.dang/2.,self.thetasteps)*pi/180.
        rotangs=linspace(0.,360.-self.drot,self.rotsteps)*pi/180.
        print rotangs

        # slice0 -> punkte in xy ebene von -phi bis phi
        slice0=zeros([self.phisteps,3])
        slice0[:,0]+=self.v0*cos(phis)
        slice0[:,1]+=self.v0*sin(phis)

        # slit -> slice0 wir um y-Achse gedreht um den Eintrittsspalt zu bauen
        slit=ones([self.phisteps*self.thetasteps,3])
        sldid=ones((self.phisteps*self.thetasteps))
        for i in range(self.thetasteps):
            for j in range(self.phisteps):
                slit[i*self.phisteps+j]=[slice0[j,0]*cos(thetas[i]),slice0[j,1],slice0[j,0]*sin(thetas[i])]
                if thetas[i] <= 20./180 * pi:
                    sldid[i*self.phisteps+j] = 0
                elif thetas[i] <= 40./180 * pi:
                    sldid[i*self.phisteps+j] = 1
                else: 
                    sldid[i*self.phisteps+j] = 2
        # slit wird rotiert und Punktegitter fuer einen Step wird erstellt 
        grid=[]
        did=[]
        sec=[]
        for ang in rotangs:
            for i,val in enumerate(slit):
                grid.append([val[0],val[1]*cos(ang)-val[2]*sin(ang),val[1]*sin(ang)+val[2]*cos(ang)])
                did.append(sldid[i])
                sec.append(int(ang/pi*4.))
        self.grid=array(grid)
        self.did=array(did)
        self.sec=array(sec)
def loadgrid(dang=0.5,drot=1.,loaddump=1,dump=1):
    from os.path import isfile
    from libacepy.eintrittssystem import eintrittssystem
    import cPickle

    cpicklename="VDgrid_%.2f_%.2f.cpic"%(dang,drot)
    
    if isfile(cpicklename) and loaddump:
        inf=open(cpicklename,"r")
        tmp=cPickle.load(inf)
        inf.close()
        print cpicklename+" loaded"
        return tmp
    else:
        entr=eintrittssystem(dang,drot,loaddump,dump)
        if dump:
            dumpgrid(entr)
        return entr

def dumpgrid(eintr):
    """
    cpickles object of type swicsiondata
    """
    from libacepy.eintrittssystem import eintrittssystem
    import cPickle
    out=open(eintr.cpicklename,"w")
    cPickle.dump(eintr,out)
    out.close()
    print "Dumped "+eintr.cpicklename


