from libacepy.ancil import int2str
from Gnuplot import Gnuplot,Data
from math import sqrt

class swicselemdata:
    def __init__(self,elemname,timeframe,path): 
        self.name=elemname                          #  str -> name of ion  
        self.time=[]                               #  vector [time]
        self.meanch=[]                                #  vector [vel]
        self.flux=[]                               #  vector [flux,cr-error,eff-error]
        self.dens=[]                               #  vector [dens,cr-error,eff-error]
        self.path=path                             #  str -> path of data
        self.timeframe=timeframe                   #  vector -> [[start,stop]]


    def load(self):
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1])+1):
                doystr=int2str(day)
                ergdaypath=self.path+doystr+"/"
                listin=open(ergdaypath+"list.in")
                s=listin.readline()
                for s in listin:
                    k=s.split()
                    time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.))
                    #time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.)+(float(k[0][39:42])+float(k[0][43:45])/24.+float(k[0][46:48])/(24.*60.))+float(k[0][49:51])/(24.*60.*60.))/2.
                    if (time>=tf[0] and time<=tf[1]):
                        elemname=ergdaypath+"elem_"+k[0]
                        self.time.append(time)
                        elemin=open(elemname)
                        s=elemin.readline()
                        k=s.split()
                        while (k[0]!=self.name):
                            s=elemin.readline()
                            k=s.split()
                        self.meanch.append([time,float(k[10])])
                        self.dens.append([time,float(k[4]),float(k[5]),float(k[6])])
                        self.flux.append([time,float(k[1]),float(k[2]),float(k[3])])
                        elemin.close()
        print self.name+" loaded"

