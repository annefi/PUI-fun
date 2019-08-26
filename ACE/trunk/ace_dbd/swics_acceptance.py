from swics_collimator import collimator
from libacepy.ancil import getvelocity_allsteps
from numpy import *
class v3D(object):
    def __init__(self,m= 4.,q = 1.,vsw=arange(500.,700.,10.),aspphi=arange(-17.,17.01,1.),asptheta=arange(-7.,7.01,1.),epqs=arange(1,59,1)):
        self.m = m
        self.q = q
        self.vsw = vsw
        self.aspphi = aspphi
        self.asptheta = asptheta
        self.epqs=epqs
        self.col = collimator()
        self.v3D = zeros((aspphi.shape[0],asptheta.shape[0],vsw.shape[0],epqs.shape[0],self.col.mv.shape[0],self.col.mv.shape[1],self.col.mv.shape[2]))
        self._calc_v3D()
    def _calc_v3D(self):
        for iv,v in enumerate(self.vsw):
            print iv,v
            for iaspphi,phi in enumerate(self.aspphi):
                for iasptheta,theta in enumerate(self.asptheta):
                    for iepq,epq in enumerate(self.epqs):
                        c = collimator (aspphi=phi,asptheta = theta,vsw=v,vel = getvelocity_allsteps(self.m,self.q,int(epq)))
                        self.v3D[iaspphi,iasptheta,iv,iepq]=c.mv
