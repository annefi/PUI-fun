'''
Older version that is replaced by ulysses_traj.py (@03.04.2019)
Here the two separate trajectory lists 'helio.dat' and "ulysses_daily_heliocentric_data_1990-2009.txt" are used and
no differentiated aspect angles are calculated (can't be used with Dist3D.py).
@author Anne
'''

from pylib import dbData
from numpy import array,ndarray

class ulysses_traj(dbData):
    def load_data(self,*args,**kwargs):
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
            self.path="/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt"

        try:
            # read in trajectory data keys
            print('read in trajectory data keys...')
            fin = open(self.path,"r")
            for line in range(4):
                # skip headlines
                fin.readline()
            s = fin.readline()
            k = s.split() # keys
            self.keys=[]
            for key in k:
                key = key.split()
                self.data[key[0]]=[]
                self.keys.append(key[0])
        except:
            print "Cannot get trajectory data product keys"

        if len(self.data.keys()) > 0:
            datalines = fin.readlines()[2:]
            for year in self.year:
                print(year)
                for tf in self.timeframe:
                    try:
                        for line in datalines:
                            k = line.split()
                            if int(k[0]) == year:
                                if int(k[4]) in range(int(tf[0]),int(tf[1])):
                                    print(int(k[4]))
                                    for i,key in enumerate(self.keys):
                                        self.data[key].append(float(k[i]))
                    except:
                        print "Problems reading DoYs "

            for key in self.data.keys():
                self.data[key]=array(self.data[key])
            print('...almost done')

        try:
            # read in trajectory data keys from helio.dat
            print('read in trajectory data key ra_heliographic from helio.dat')
            fin = open('/data/etph/Ulysses/trajectory/helio.dat', "r")
            self.data['ra_hg'] = []
            self.keys.append('ra_hg')
        except:
            print "Cannot get trajectory data product key from helio.dat"

        if self.year[0] == 1990:
            if float(self.timeframe[0][0]) < 308.0:
                print("No RA heliographic data available before DOY 308 in 1990. \n ")
                self.keys.remove('ra_hg')
        else:
            try:
                datalines = fin.readlines()[6:]
                for year in self.year:
                    print(year)
                    for tf in self.timeframe:
                        try:
                            for line in datalines:
                                k = line.split()
                                if int(k[0]) == year:
                                    if int(k[1]) in range(int(tf[0]), int(tf[1])):
                                        print(int(k[1]))
                                        self.data['ra_hg'].append(float(k[10]))
                        except:
                            print "Problems reading DoYs in helio.dat"
                self.data['ra_hg'] = array(self.data['ra_hg'])
                print('...almost done')
            except:
                print('hm. Something went wrong. Go and investigate.')

            #self.calc_doy() # not necessary. Given in data.

    def calc_d90(self):
        offy = self.data["YYYY"] - 1990
        offd = offy*365 + (offy.astype(int)+2)/4
        self.add_data("d90", self.data["DOY"] + offd)