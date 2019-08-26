from pylib import dbData
from numpy import loadtxt,arctan2,sqrt,pi

class ace_pha_puis(dbData):
    def load_data(self):
        fin = open("/data/ivar/berger/puis/hepdat_pha.dat","r")
        keys = fin.readline().split()
        dat = loadtxt(fin)
        for i,k in enumerate(keys):
            self.data[k] = dat[:,i]
        # Until fixed in the lower level data By has to be inverted to get to a right handed coordinate system and the angles are calculated accordingly!!!
        self.data["By"]=-self.data["By"]
        self.data["Bphi"]=arctan2(self.data["By"],self.data["Bx"])/pi*180.
        self.data["Btheta"]=arctan2(self.data["Bz"],sqrt(self.data["By"]**2+self.data["Bx"]**2))/pi*180.
        
