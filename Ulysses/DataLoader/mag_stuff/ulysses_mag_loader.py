""" Read in Ulysses magnetic field data from VHM_FGM (Ulysses Archive)
"""

from pylib3 import dbData
from numpy import array, ndarray, sqrt, column_stack
from Ulysses.Trajectory.ul_coordinates_utils import rtn_to_hg
from Ulysses.DataLoader.ulysses_traj_spice import UlyssesTrajSpice
import matplotlib.pyplot as plt


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
        self.keys = ['year', 'doy', 'hour', 'min', 'sec' ,'Br', 'Bt', 'Bn', 'Babs']
        for key in self.keys:
            self.data[key] = []

        for year in self.year:
            print(year)
            for tf in self.timeframe:
                for doy in range(int(tf[0]),int(tf[1])):
                    try:
                        fname = "%s%.4i/%.3i.dat"%(self.path,year,doy)
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
        offd = offy * 365 + (offy.astype(int) + 2) / 4
        self.add_data("d90", self.data["doy"] + offd)

    def calc_doy_refined(self):
        doy = self.data["doy"] + self.data["hour"] * 1. / 24. + self.data["min"] * (1. / (24. * 60.)) + self.data[
            "sec"] * (1. / (24. * 60. * 60.))
        self.data["doy"] = doy

    def plot_mag(self):
        fig, ax = plt.subplots()
        Br = self.data['Br']
        Bt = self.data['Bt']
        Bn = self.data['Bn']
        B_lat = []
        B_long = []
        for i, b in enumerate(Br):
            B_rtn = np.array([Br[i], Bt[i], Bn[i]])
            B_sph = rtn_to_hg(B_rtn, )
        ax.plot()

    def test_abs_value(self):
        fig, ax = plt.subplots()
        #ax.plot(self.data['doy'],self.data['Babs'], linestyle = 'None', marker = 'o', ms = 1., label = 'Babs')
        #ax.plot(self.data['doy'], sqrt(self.data['Br']**2 + self.data['Bt']**2 + self.data['Bn']**2),
        #        linestyle='None', marker='o', ms=1., label='Babs_calc')
        Babs = self.data['Babs']
        Babs_calc = sqrt(self.data['Br']**2 + self.data['Bt']**2 + self.data['Bn']**2)
        ax.plot(self.data['doy'], Babs - Babs_calc, linestyle = 'None', marker = 'o', ms = 1., label = "Babs - "
                                                                                                       "Babs_calc")
        ax.grid(True)
        ax.set_xlabel('doy in %s'%self.data["year"][0])
        ax.set_ylabel('B_abs in nT')
        ax.legend()
        fig.suptitle('Comparison Absolute Magnitudes')
        fig.savefig('comp_babs.png')
