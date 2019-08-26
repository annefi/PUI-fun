from math import atan,sqrt
from numpy import *

class attdata:
    def __init__(self,year,path):
        self.time=[]                               #  vector [time]
        self.x=[]                                  #  vector [x component of direction vector]
        self.y=[]                                  #  vector [y component of direction vector]
        self.z=[]                                  #  vector [z component of direction vector]
        self.phi=[]                                #  vector [phi]
        self.theta=[]                              #  vector [theta]
        self.path=path                             #  str -> path of data (ancillary.dat)
        self.year=year                             #  int -> year of attdata

    def load(self):
        ancilin=open(self.path+"ancillary.dat")
        # skip header
        ancilin.readline()
        ancilin.readline()
        ancilin.readline()
        ancilin.readline()
        # header ends
        for s in ancilin:
            k=s.split()
            tmpalpha=0.
            tmpbeta=0.
            tmptime=0.
            if (int(k[0][0:4])==self.year):
                tmptime+=float(k[0][4:7])
                tmptime+=float(k[1])/1.e8
                tmpx=float(k[2])
                tmpy=float(k[3])
                tmpz=float(k[4])
                tmpalpha=atan(-tmpy/tmpx)
                tmpbeta=atan(tmpz/(sqrt(tmpx**2+tmpy**2)))
                self.time.append(tmptime)
                self.x.append(tmpx)
                self.y.append(tmpy)
                self.z.append(tmpz)
                self.phi.append(tmpalpha)
                self.theta.append(tmpbeta)
        self.time=array(self.time)
        self.x=array(self.x)
        self.y=array(self.y)
        self.z=array(self.z)
        self.phi=array(self.phi)
        self.theta=array(self.theta)
        ancilin.close()
        print "ATTITUDE-data loaded"

    def calc_angles(self):
        self.phi=arctan(-self.y/self.x)
        self.theta=arctan(self.z/(sqrt(self.x**2+self.y**2)))

def sync_attitude(att,iondata):
    "Syncronizes ATTITUDE to SWICS data! \n att -> class attitude \n iondata -> class swicsiondata \n output -> returns syncronized object of class att_data"
    syncatt=attdata(att.year,att.path)
    print "synchronizing ATTITUDE to SWICS data"
    j=0
    for i in range(len(iondata.time)):
        while (att.time[j+1]<iondata.time[i] and j<len(att.time)-2):
            j+=1
        dT=att.time[j+1]-att.time[j]
        dx=att.x[j+1]-att.x[j]
        dy=att.y[j+1]-att.y[j]
        dz=att.z[j+1]-att.z[j]
        T=iondata.time[i]-att.time[j]
        syncatt.time.append(iondata.time[i])
        syncatt.x.append(T*dx/dT+att.x[j])
        syncatt.y.append(T*dy/dT+att.y[j])
        syncatt.z.append(T*dz/dT+att.z[j])
    syncatt.time=array(syncatt.time)
    syncatt.x=array(syncatt.x)
    syncatt.y=array(syncatt.y)
    syncatt.z=array(syncatt.z)
    syncatt.calc_angles()
    print "done"
    return syncatt
