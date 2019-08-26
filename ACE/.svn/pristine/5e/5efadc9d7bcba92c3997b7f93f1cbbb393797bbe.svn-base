from pylib import dbData
from numpy import *

class ace_swics_hk(dbData):
    def load_data(self,*args,**kwargs):
        if kwargs.has_key("year"):
            if isinstance(kwargs["year"],list):
                self.year=kwargs["year"]
            elif isinstance(kwargs["year"],int) or isinstance(kwargs["year"],float):
                self.year=[kwargs["year"]]
        else:
            self.year=[2007]
        if kwargs.has_key("tf"):
            self.tf = kwargs["tf"]
        if kwargs.has_key("path"):
            self.path = kwargs["path"]
        else:
            self.path = "/data/etph/ace/swics/lv0/"
        self.keys = ["year","time","doy","eoq","GV28","GV20","GV10","GV5P","GV5M","SPR1","GTE1","GTE2","GPI1","GPI2","GI5P","GI20","GPAV","SPR2","GEPQ","SPR3","PAC7","PTE1","PTE2","PV5P","PI5P","PV5M","PI5M","PMCP","PGAI"]
        for k in self.keys:
            self.data[k] = array([])

        self.load()

    def load(self):
        print "Loading HK for years ",self.year
        for year in self.year:
            for doy in range(self.tf[0][0],self.tf[-1][1]+1):
                try:
                    dat = loadtxt(self.path+"%.4i/hk/%.3i.hk"%(int(year),doy),skiprows=2)
                    for i,k in enumerate(self.keys):
                        self.data[k] = append(self.data[k],dat[:,i])
                except:
                    print "No hk data for doy ",doy,year
        


