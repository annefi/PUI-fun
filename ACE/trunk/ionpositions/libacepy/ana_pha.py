from numpy import *
from response import response
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from ace_pha import ace_pha
import time

class ana_pha(object):
    def __init__(self,d):
        """
        In the present form the ana_pha class takes a dbData instance that has a (unique,i.e. not doy for several year but rather days since) time , energy per charge step , energy, time-of-flight, and total,and sector base rate respectively. The instrumental responses are defined in response.py (at the current state 2D-Gaussian with the parameters defined in ion_para (Old parameters from the PHD-thesises of Koeten,Berger))
        """
        self.d = d
        self.doy = d.data["doy"]
        self.EpQ = d.data["epq"]
        self.E = d.data["esd"]
        self.T = d.data["tof"]
        self.Secw = d.data["swt"]

        # Responses and Probabilities (P_ion(E,T)) are calculated
        R = response()
        self.R,self.ions = R.calc_response(self.EpQ,self.T,self.E)
        self.Nion = self.R.shape[0]
        self.P = self.R/sum(self.R,axis=0)
        self.P[isnan(self.P)]=0.
        self.P[isinf(self.P)]=0.
        # Only use PHA words that are in the range of at leat one ion that is analysed (i.e. there are many PHA words even real signals that are not covered by the instrumental model function, and thus can not be analysed properly -> thus we can skip them in the beginning to minimise the computing time)
        self.mask=sum(self.P,axis=0)>.99
        self.remove_data(self.mask)

        self.DOYS = arange(1.,11.1,1.)
        self.indT = searchsorted(self.DOYS,self.doy)-1
        #self.DOYS,self.indT = unique(self.doy,return_inverse=True)
        self.EPQS,self.indEpQ = unique(self.EpQ,return_inverse=True)

        self.nfspec = zeros((self.Nion,self.DOYS.shape[0],self.EPQS.shape[0]))
        self.ctsspec = zeros((self.Nion,self.DOYS.shape[0],self.EPQS.shape[0]))
        self.octsspec = zeros((self.Nion,self.DOYS.shape[0],self.EPQS.shape[0]))
        self.res = zeros((self.Nion,self.DOYS.shape[0],self.EPQS.shape[0]))
        self.DOYS=append(self.DOYS,self.DOYS[-1]+1)
        self.EPQS=append(self.EPQS,self.EPQS[-1]+1)

    def remove_data(self,mask):
        # call to remove PHA words defined by mask from further analysis. NOTE! the mask defines which PHA are NOT removed!
        self.doy = self.doy[mask]
        self.EpQ = self.EpQ[mask]
        self.E = self.E[mask]
        self.T = self.T[mask]
        self.Secw = self.Secw[mask]
        self.R=self.R[:,mask]
        self.P=self.P[:,mask]
        
    def get_cts(self):
        # how many ions contribute to each DOY,EPQ combination
        self.nioncontr = zeros((self.Nion,self.DOYS.shape[0]-1,self.EPQS.shape[0]-1))
        for ion in range(self.Nion):
            self.nioncontr[ion],x,y = histogram2d(self.doy,self.EpQ,bins=(self.DOYS,self.EPQS),weights=self.P[ion])
        self.ncontr=sum(self.nioncontr.astype(bool),axis=0)
        # number of PHAs for each DOY,EPQ combination
        self.ncts,x,y = histogram2d(self.doy,self.EpQ,bins=(self.DOYS,self.EPQS))
        # assign each PHA the number of counts and ions that contribute to its DoY,EpQ combination. This can be used to iterate only iterate where nrcts>=nrions.
        self.nrcts = self.ncts[self.indT,self.indEpQ]
        self.nrcontr = self.ncontr[self.indT,self.indEpQ]
        self.frp = self.nrcts-self.nrcontr
        self.nofitmask = self.frp<0
        for i in range(self.Nion):
            self.nfspec[i],x,y = histogram2d(self.doy[self.nofitmask],self.EpQ[self.nofitmask],bins=(self.DOYS,self.EPQS),weights=self.Secw[self.nofitmask]*self.P[i][self.nofitmask])
        self.res+=self.nfspec
        self.remove_data(~self.nofitmask)
        self.indT=self.indT[~self.nofitmask]
        self.indEpQ=self.indEpQ[~self.nofitmask]

        for i in range(self.Nion):
            self.octsspec[i],x,y = histogram2d(self.doy,self.EpQ,bins=(self.DOYS,self.EPQS),weights=self.Secw*self.P[i])
        j = -1
        run = True
        while run:
            j+=1
            W = self.octsspec[:,self.indT,self.indEpQ]*self.R/sum(self.octsspec[:,self.indT,self.indEpQ]*self.R,axis=0)
            W[isnan(W)]=0.
            W[isinf(W)]=0.
            for i in range(self.Nion):
                self.ctsspec[i],x,y = histogram2d(self.doy,self.EpQ,bins=(self.DOYS,self.EPQS),weights=self.Secw*W[i])
            dspec = abs(self.ctsspec-self.octsspec)
            print "step, mean, max , sum, NrPHA"
            print j,mean(dspec.flatten()),max(dspec.flatten()),sum(dspec),self.doy.shape[0]
            m = amax(dspec,axis=0)[self.indT,self.indEpQ]<0.1
            m2 = (amax(dspec,axis=0)<0.1)*(sum(self.ctsspec,axis=0)>0.)
            self.res[:,m2]=self.ctsspec[:,m2]
            self.remove_data(~m)
            self.indT=self.indT[~m]
            self.indEpQ=self.indEpQ[~m]
            self.octsspec[:,~m2]=self.ctsspec[:,~m2]
            self.octsspec[:,m2]=0.
            if sum(~m)==0:
                run = False
                
    def plot_ion(self,ion,color="k"):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        for j in range(self.ctsspec.shape[1]):
            ax.plot(j*ones(58),arange(1,59),a.ctsspec[ion][j],color=color)


def plot_ion(dat,color="k",ax = None):
    if ax==None:
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
    for j in range(dat.shape[0]):
        ax.plot(j*ones(58),arange(1,59),dat[j],color=color)
    return ax

t1 = time.time()
d = ace_pha(years=["2007"],tf=[[1,10]],rng=(0,1),mqrange=(0.,100.))
t2 = time.time()
a = ana_pha(d)
t3 = time.time()
a.get_cts()
t4 = time.time()
print "load",t2-t1
print "initialise",t3-t2
print "iterate",t4-t3
print "total",t4-t1
