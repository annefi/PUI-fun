from pylib import dbData
from numpy import *

class ace_ancil(dbData):
    def load_data(self,*args,**kwargs):
        fin=open("/data/ivar/ace/ancillary.dat","r")
        for i in range(4):
            fin.readline()
        year=[]
        doy=[]
        x=[]
        y=[]
        z=[]
        for l in fin:
            s=l.split()
            year.append(float(s[0][:4]))
            doy.append(float(s[0][4:])+(float(s[1])/1000.)/(24.*60.*60.))
            x.append(float(s[2]))
            y.append(float(s[3]))
            z.append(float(s[4]))
        self.data["year"]=array(year)
        self.data["doy"]=array(doy)
        self.data["x"]=array(x)
        self.data["y"]=array(y)
        self.data["z"]=array(z)
        self.data["aphi"]=arctan2(self.data["y"],self.data["x"])
        self.data["atheta"]=arctan2(self.data["z"],sqrt(self.data["x"]**2+self.data["y"]**2))
        self.data["aspang"]=arccos(cos(self.data["aphi"])*cos(self.data["atheta"]))
        self.data["aphi"]*=180./pi
        self.data["atheta"]*=180./pi
        self.data["aspang"]*=180./pi
