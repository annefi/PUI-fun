'''
Even newer version of ulysses_traj.py, that replaces it from tbd.
Loads trajectory data via SPICE and adds them as data products to uswipha instance.
Also calculates and adds Aspect Angle data products.
'''

from pylib3 import dbData
from numpy import array,ndarray
import sys

class UlyssesTrajSpice(dbData):
    """ Loader for Ulysses trajectory data

    Inherits from dbData
    Loads trajectory data calculated via SPICE "/data/projects/Ulysses/trajectory/traj_data_ulysses_pool.dat"

    Methods
    -------
    load_data()
    calc_d90()

    """
    def load_data(self,*args,**kwargs):
        if "year" in kwargs:
            if isinstance(kwargs["year"],list):
                self.year=kwargs["year"]
            elif isinstance(kwargs["year"],int) or isinstance(kwargs["year"],float):
                self.year=[kwargs["year"]]
        else:
            self.year=[2007]
        if "tf" in kwargs:
            if isinstance(kwargs["tf"],list) or isinstance(kwargs["tf"],ndarray):
                self.timeframe=kwargs["tf"]
            elif kwargs["tf"]=="all":
                self.timeframe=[[1.,367]]
            else:
                print("periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded")
                self.timeframe=[]
        else:
            print("periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded")
            self.timeframe=[]
        if "path" in kwargs:
            self.path=kwargs["path"]
        else:
            self.path="./Ulysses/Trajectory/trajectory_data/spice_traj.dat"

        if self.year[0] == 1990:
            if float(self.timeframe[0][0]) < 280.0:
                print("No trajectory data available before DOY 280 in 1990. \n ")
                sys.exit()

        try:
            # read in trajectory data keys
            print('read in trajectory data keys...')
            fin = open(self.path,"r")
            s = fin.readline()
            k = s.split() # keys
            self.keys = []
            for key in k:
                self.data[key] = []
                self.keys.append(key)
        except:
            print("Cannot get trajectory data product keys")

        if len(self.data.keys()) > 0:
            datalines = fin.readlines()[2:]
            for year in self.year:
                print(year)
                for tf in self.timeframe:
                    try:
                        for line in datalines:
                            k = line.split()
                            if int(k[0]) == year:
                                if int(k[3]) in range(int(tf[0]),int(tf[1])):
                                    for i,key in enumerate(self.keys):
                                        self.data[key].append(float(k[i]))
                    except:
                        print("Problems reading DoYs")
                if len(self.data["YYYY"]) == 0:
                    sys.exit('No data found for year %s'%year)


    def calc_d90(self):
        offy = self.data["YYYY"] - 1990
        offd = offy*365 + (offy.astype(int)+1)//4
        self.keys.append('d90')
        self.add_data("d90", self.data["doy"] + offd)





