from scipy import constants
from pylab import *
from numpy import *
kbm=constants.k/constants.atomic_mass

class maxbol(object):
    def __init__(self,Tpa,Tpe,N=1.e7):
        self.Tpe=Tpe
        self.Tpa=Tpa
        self.N=N
        self.sigpe=sqrt((constants.constants.k*self.Tpe)/constants.atomic_mass)
        self.sigpa=sqrt((constants.constants.k*self.Tpa)/constants.atomic_mass)
        self.vx=random.normal(0.,self.sigpa,N)
        self.vy=random.normal(0.,self.sigpe,N)
        self.vz=random.normal(0.,self.sigpe,N)
        self.v=sqrt(self.vx**2+self.vy**2+self.vz**2)
        self.vlpe=sqrt(2.*constants.k*self.Tpe/constants.atomic_mass)
        self.vlpa=sqrt(2.*constants.k*self.Tpa/constants.atomic_mass)

    def calc_Tl(self,newfig=False):
        y,x=histogram(self.v,bins=arange(0.,1000.01e3,1e3))
        if newfig:
            figure()
        plot(x[:-1],y,drawstyle="steps-post",marker="o")
        self.vmax=x[:-1][y==amax(y)][0]
        self.Tv=self.vmax**2*constants.atomic_mass/2./constants.k
        
