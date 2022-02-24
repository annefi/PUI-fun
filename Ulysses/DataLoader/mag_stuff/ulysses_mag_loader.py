""" Read in Ulysses magnetic field data from VHM_FGM (Ulysses Archive)
"""

from pylib3 import dbData
from numpy import array, ndarray, sqrt, column_stack
from Ulysses.Trajectory.ul_coordinates_utils import rtn_to_hg, hg_to_hc
from Ulysses.DataLoader.ulysses_traj_spice import UlyssesTrajSpice
import matplotlib.pyplot as plt
import datetime


class mag_loader(dbData):
    def load_data(self, *args, **kwargs):
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
                self.timeframe=[[1,366]]
            else:
                print("periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), "
                      "no data loaded")
                self.timeframe=[]
        else:
            print("periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded")
            self.timeframe=[]
        if "path" in kwargs:
            self.path=kwargs["path"]
        else:
            self.path="/data/projects/Ulysses/VHM_FGM/1min/"

        # initialise keys
        self.keys = ['year', 'doy', 'hour', 'min', 'sec' ,'Br', 'Bt', 'Bn', 'Babs', 'B_r', 'B_lat', 'B_long']
        for key in self.keys:
            self.data[key] = []

        for year in self.year:
            print(year)
            for tf in self.timeframe:
                for doy in range(int(tf[0]),int(tf[1])):
                    try:
                        fname = "%s%.4i/new/%.3i.dat"%(self.path,year,doy)
                        print(fname)
                        fin = open(fname,"r")
                        for s in fin:
                            k = s.split()
                            for i,key in enumerate(self.keys):
                                if key!="year":
                                    self.data[key].append(float(k[i]))
                                else:
                                    self.data["year"].append(year)
                    except:
                        print("Problems reading DoY ",doy)
        for key in self.data.keys():
            self.data[key]=array(self.data[key])
        #self.calc_doy_refined()

    def calc_d90(self):
        offy = self.data["year"] - 1990
        offd = offy * 365 + (offy.astype(int) + 1) // 4
        self.add_data("d90", self.data["doy"] + offd)

    def calc_doy_refined(self):
        doy = self.data["doy"] + self.data["hour"] * 1. / 24. + self.data["min"] * (1. / (24. * 60.)) + self.data[
            "sec"] * (1. / (24. * 60. * 60.))
        self.data["doy"] = doy

    def calc_datetime(self):
        datetimes = []
        for i in range(len(self.data['year'])):
            datetimes.append(
                datetime.datetime(self.data['year'][i], 1, 1, int(self.data['hour'][i]), int(self.data['min'][i]),
                                  int(self.data['sec'][i])) + datetime.timedelta(days=self.data['doy'][i] - 1))
        self.add_data('datetime', datetimes)

    def plot_mag_hg(self):
        fig, ax = plt.subplots()
        Br = self.data['B_r']
        Bt = self.data['B_lat']
        Bn = self.data['B_long']
        if not 'datetime' in self.data.keys():
            self.calc_datetime()
        ax.plot(self.data['datetime'],self.data['B_r'], linestyle = None, marker = 'o', ms=.1)

    def calc_hc(self):
        B_hc_lat = []
        B_hc_long = []
        for i in range(len(self.data['year'])):
            R, lat, lon = hg_to_hc(array([self.data['B_r'][i], self.data['B_lat'][i], self.data['B_long'][i]]),
                                   ang_ascnode = 75.634) # ang_ascnode not accurate but for 1.1.1991
            B_hc_lat.append(lat)
            B_hc_long.append(lon)
        self.add_data('B_hc_lat', B_hc_lat)
        self.add_data('B_hc_long', B_hc_long)

