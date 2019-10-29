from pylib import dbData
from numpy import array, ndarray

class mag_loader(dbData):
    def load_data(self, *args, **kwargs):
        if kwargs.has_key("year"):
            if isinstance(kwargs["year"],list):
                self.year=kwargs["year"]
            elif isinstance(kwargs["year"],int) or isinstance(kwargs["year"],float):
                self.year=[kwargs["year"]]
        else:
            self.year=[2007]
        if kwargs.has_key("tf"):
            if isinstance(kwargs["tf"],list) or isinstance(kwargs["tf"],ndarray):
                self.timeframe=kwargs["tf"]
            elif kwargs["tf"]=="all":
                self.timeframe=[[1.,367]]
            else:
                print "periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded"
                self.timeframe=[]
        else:
            print "periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded"
            self.timeframe=[]
        if kwargs.has_key("path"):
            self.path=kwargs["path"]
        else:
            self.path="/data/projects/Ulysses/umag_tp/1sec_data/" # (is only 2 sec data!)

        # initialise keys%ru
        self.keys = ['year', 'doy', 'hour', 'min', 'sec' ,'Br', 'Bt', 'Bn', 'Babs']
        for key in self.keys:
            self.data[key] = []

        for year in self.year:
            print year
            for tf in self.timeframe:
                for doy in range(int(tf[0]),int(tf[1])):
                    try:
                        fname = "%s%.4i/%.3i.dat"%(self.path,year,doy)
                        print fname
                        fin = open(fname,"r")
                        for s in fin:
                            k = s.split()
                            for i,key in enumerate(self.keys):
                                if key!="year":
                                    self.data[key].append(float(k[i]))
                                else:
                                    self.data["year"].append(year)
                    except:
                        print "Problems reading DoY ",doy
        for key in self.data.keys():
            self.data[key]=array(self.data[key])
        self.calc_doy_refined()

    def calc_d90(self):
        offy = self.data["year"] - 1990
        offd = offy * 365 + (offy.astype(int) + 2) / 4
        self.add_data("d90", self.data["doy"] + offd)

    def calc_doy_refined(self):
        doy = self.data["doy"] + self.data["hour"] * 1. / 24. + self.data["min"] * (1. / (24. * 60.)) + self.data[
            "sec"] * (1. / (24. * 60. * 60.))
        self.data["doy"] = doy