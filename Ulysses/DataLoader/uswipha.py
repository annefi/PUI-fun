"""
PHA loader for Ulysses SWICS data

Based on dbData
"""

import sys
import os

if os.path.isdir("/home/af/fusessh/data/projects/Ulysses/") == True:
    ### from Laptop: ###
    datapath = "/home/af/fusessh/data/projects/Ulysses/"
elif os.path.isdir("/data/projects/Ulysses/") == True:
    ### from Uni/skeletor: ###
    datapath = "/data/projects/Ulysses/"
else:
    print("Problem finding data path on asterix (needed for SWOOPS data). \nAre you connected to asterix via fusessh?\n")
    sys.exit()
####################

magpath = "/Ulysses/data_misc/PHA_mag/"

from pylib3 import *
from numpy import *
from Ulysses.DataLoader.uswo import uswo
from Ulysses.DataLoader.ulysses_traj_spice import UlyssesTrajSpice
#from Ulysses.DataLoader.ulysses_mag_loader import mag_loader
from Ulysses.DataLoader.uswiutils import getvelocity


class uswipha(dbData):
    """ PHA loader for Ulysses SWICS data
    
    Inherits loader from dbData

    Methods
    -------
    load_data()
        Data loader based on timeframe and masks
    calc_d90()
        Calculates days since 1990
    sync_swoops()
        Synchronises solar wind speed, density etc. (data from SWOOPS)
    sync_traj()
    sync_mag()
        To be reviewed
    calc_d90_epq()

    Examples
    --------
    d = uswipha(year = 1991, tf = [[1,10])

    Data Products
    -------------
    doy - day of year
    epq - energy per charge (ESA step)
    tch - time of flight channel
    ech - energy channel (SSD)
    sec - sector [0,7]
    det - detector [0,2]
    rng - priority range [0,2]
    brw - base rate weight
    vHe+ - He+ velocity based on epq
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
                print("periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), "
                      "no data loaded")
                self.timeframe=[]
        else:
            print("periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded")
            self.timeframe=[]
        if "path" in kwargs:
            self.path=kwargs["path"]
        else:
            self.path = datapath + "swics/pha/"
            #self.path = "Ulysses/data_misc/pha_he/"

        self.data["year"]=[]
        self.data["doy"]=[]
        self.data["epq"]=[]
        self.data["tch"]=[]
        self.data["ech"]=[]
        self.data["sec"]=[]
        self.data["det"]=[]
        self.data["rng"]=[]
        self.data["brw"]=[]
        # if self.path == magpath:
        #     self.data["Bphi"] = []
        #     self.data["Btheta"] = []
        #     self.data["BR"] = []
        #     self.data["BT"] = []
        #     self.data["BN"] = []

        for year in self.year:
            for tf in self.timeframe:
                for doy in range(int(tf[0]),int(tf[1])):
                    try:
                        fname = "%s%.4i/%.3i.pha"%(self.path,year,doy)
                        print(fname)
                        fin = open(fname,"r")
                        s = fin.readline()
                        for s in fin:
                            k = s.split()
                            self.data["year"].append(int(year))
                            self.data["doy"].append(float(k[0]))
                            self.data["epq"].append(int(k[1]))
                            self.data["tch"].append(int(k[2]))
                            self.data["ech"].append(int(k[3]))
                            self.data["sec"].append(int(k[4]))
                            self.data["det"].append(int(k[5]))
                            self.data["rng"].append(int(k[6]))
                            self.data["brw"].append(float(k[7]))
                            # if self.path == magpath:
                            #     self.data["Bphi"].append(float(k[8]))
                            #     self.data["Btheta"].append(float(k[9]))

                            #     self.data["BR"].append(float(k[10]))
                            #     self.data["BT"].append(float(k[11]))
                            #     self.data["BN"].append(float(k[12]))
                    except:
                        print("Problems reading DoY ",doy)
        self.data["year"]=array(self.data["year"])
        self.data["doy"]=array(self.data["doy"])
        self.data["epq"]=array(self.data["epq"])
        self.data["tch"]=array(self.data["tch"])
        self.data["ech"]=array(self.data["ech"])
        self.data["sec"]=array(self.data["sec"])
        self.data["det"]=array(self.data["det"])
        self.data["rng"]=array(self.data["rng"])
        self.data["brw"]=array(self.data["brw"])
        self.data["vHe+"] = getvelocity(4.,1.,self.data["epq"])

        # if self.path == magpath:
        #     self.data["Bphi"] = array(self.data["Bphi"])
        #     self.data["Btheta"] = array(self.data["Btheta"])
        #
        #     self.data["BR"] = array(self.data["BR"])
        #     self.data["BT"] = array(self.data["BT"])
        #     self.data["BN"] = array(self.data["BN"])

    def calc_d90(self):
        """ Calculates days since 01.01.1990 -> attribute self.d90

        """
        offy = self.data["year"] - 1990
        offd = offy*365 + (offy.astype(int)+2)/4
        self.add_data("d90",self.data["doy"] + offd)

    def sync_swoops(self):
        ''' Synchronisation with SWOOPS data

        Adds data products from SWOOPS
    
        Data products
        -------------        
        vsw : solar wind velocity
        dsw : solar wind density 
        hlat : latitude Ulysses in TODO
        hlong :  longitude Ulysses in TODO
        rau : solar radius Ulysses in AU
        wHe+ : vHe+ / vsw

        '''
        seterr(divide='ignore', invalid='ignore')
        swo = uswo(year = self.year,tf = self.timeframe, path = datapath + "swoops/4min_data/")
        if not 'd90' in self.data.keys():
            self.calc_d90()
        swo.calc_d90()
        uTi,index=unique(self.data["d90"],return_inverse=True)
        uTi=append(uTi,uTi[-1]+1./24./5.) # 12 minutes
        uTi=uTi+1./24./30. # 2 minutes shift
        # **
        mask = swo.data["vges"]>0
        nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
        vsw,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["vges"])
        vsw = vsw/nrT # mean
        vsw[isnan(vsw)]=0.
        self.add_data("vsw",vsw[index]) #number of vsw-steps are filled into self.datas shape here
        # **
        mask = swo.data["denp"]>0
        nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
        dsw,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["denp"])
        dsw = dsw/nrT # mean
        dsw[isnan(dsw)]=0.
        self.add_data("dsw",dsw[index])
        # **
        mask = (swo.data["hlat"]>=-90.)*(swo.data["hlat"]<=90.)
        nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
        hlat,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["hlat"])
        hlat = hlat/nrT
        hlat[isnan(hlat)]=0.
        self.add_data("hlat",hlat[index])
        # **
        mask = (swo.data["hlong"]>=0.)*(swo.data["hlong"]<=360.)
        nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
        hlong,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["hlong"])
        hlong = hlong/nrT
        hlong[isnan(hlong)]=0.
        self.add_data("hlong",hlong[index])
        # **
        mask = (swo.data["rau"]>=0.)*(swo.data["rau"]<=6.)
        nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
        rau,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["rau"])
        rau = 1.*rau/nrT
        rau[isnan(rau)]=0.
        self.add_data("rau",rau[index])
        # **
        self.add_data("wHe+",self.data["vHe+"]/self.data["vsw"])


    def sync_traj_spice(self):
        ''' Synchronisation with Ulysses trajectory data

        Adds data products from ulysses_traj_spice, i.e. trajectory data from SPICE

        '''
        traj = UlyssesTrajSpice(year = self.year,tf = self.timeframe)
        # __hier weiter__
        if not 'd90' in self.data.keys():
            self.calc_d90()
        traj.calc_d90()
        uTi_int, index_int = unique(self.data['doy'].astype(int),return_inverse=True)
        uTi_int = append(uTi_int,uTi_int[-1]+1) # insert right border for histogram bins
        # Radius (/AE):
        mask = traj.data['R'] > 0.
        r, x = histogram(traj.data["doy"], bins=uTi_int, weights=traj.data["R"])
        self.add_data("r", r[index_int])
        #latitude in HG:
        mask = traj.data['HG_Lat'] != 0.
        lat, x = histogram(traj.data["doy"], bins=uTi_int, weights=traj.data["HG_Lat"])
        self.add_data("lat_hg", lat[index_int])
        # longitude in HG:
        mask = traj.data['HG_Long'] != 0.
        long, x = histogram(traj.data["doy"], bins=uTi_int, weights=traj.data["HG_Long"])
        self.add_data("long_hg", long[index_int])
        # asp_phi
        mask = traj.data['AA_phi'] != 0.
        aa_phi, x = histogram(traj.data["doy"], bins=uTi_int, weights=traj.data["AA_phi"])
        self.add_data("aspphi", aa_phi[index_int])
        # asp_theta
        mask = traj.data['AA_theta'] != 0.
        aa_theta, x = histogram(traj.data["doy"], bins=uTi_int, weights=traj.data["AA_theta"])
        self.add_data("asptheta", aa_theta[index_int])
        # # v_r_eigen
        # mask = traj.data['v_R'] != 0.
        # v_R, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_R"])
        # self.add_data("vr_sc", v_R[index_int])
        # # v_t_eigen
        # mask = traj.data['v_T'] != 0.
        # v_T, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_T"])
        # self.add_data("vt_sc", v_T[index_int])
        # # v_n_eigen
        # mask = traj.data['v_N'] != 0.
        # v_N, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_N"])
        # self.add_data("vn_sc", v_N[index_int])
        # # v_abs
        # mask = traj.data['v'] != 0.
        # v_abs, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v"])
        # self.add_data("v_abs_sc", v_abs[index_int])


    def sync_traj(self):
        ''' Synchronisation with Ulysses trajectory data

        Adds data products from ulysses_traj, i.e. trajectory data from the Ulysses archive files

        '''
        traj = ulysses_traj(year = self.year,tf = self.timeframe, path = datapath + "trajectory/traj_data_ulysses_pool.dat")
        if not 'd90' in self.data.keys():
            self.calc_d90()
        traj.calc_d90()
        uTi_int, index_int = unique(self.data['d90'].astype(int),return_inverse=True)
        uTi_int = append(uTi_int,uTi_int[-1]+1) # insert right border for histogram bins
        # Aspect Angle Total (flat):
        mask = traj.data['SPE'] != 0.
        aa, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["SPE"])
        self.add_data("aa_tot", aa[index_int])
        # Radius (/AE):
        mask = traj.data['R'] > 0.
        r, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["R"])
        self.add_data("r", r[index_int])
        #latitude in HG:
        mask = traj.data['HG_Lat'] != 0.
        lat, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["HG_Lat"])
        self.add_data("lat_hg", lat[index_int])
        # longitude in HG:
        mask = traj.data['HG_Long'] != 0.
        long, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["HG_Long"])
        self.add_data("long_hg", long[index_int])
        # asp_phi
        mask = traj.data['asp_phi'] != 0.
        aa_phi, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["asp_phi"])
        self.add_data("aspphi", aa_phi[index_int])
        # asp_theta
        mask = traj.data['asp_theta'] != 0.
        aa_theta, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["asp_theta"])
        self.add_data("asptheta", aa_theta[index_int])
        # v_r_eigen
        mask = traj.data['v_R'] != 0.
        v_R, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_R"])
        self.add_data("vr_sc", v_R[index_int])
        # v_t_eigen
        mask = traj.data['v_T'] != 0.
        v_T, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_T"])
        self.add_data("vt_sc", v_T[index_int])
        # v_n_eigen
        mask = traj.data['v_N'] != 0.
        v_N, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_N"])
        self.add_data("vn_sc", v_N[index_int])
        # v_abs
        mask = traj.data['v'] != 0.
        v_abs, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v"])
        self.add_data("v_abs_sc", v_abs[index_int])

    # def sync_traj_SPICE(self):
    #      ''' Synchronisation with Ulysses trajectory data

    #     Adds data products from ulysses_traj_spice, i.e. trajectory data calculated with SPICE
    #     '''
    #     pass

    def calc_d90_epq(self):
        '''
        calculates refined time since 1990 with epq fraction (= 12 sec)
        :return:
        '''
        offy = self.data["year"] - 1990
        offd = offy*365 + (offy.astype(int)+2)//4
        off_epq = self.data['epq'] * 1./24./60./60. *12.
        self.add_data("d90_epq",self.data["doy"] + offd + off_epq)



    def sync_mag(self):
        '''
        todo
        '''
        mag = mag_loader(year = self.year, tf = self.timeframe)
        mag.calc_d90()
        self.mag = mag

        if not 'd90_epq' in self.data.keys():
            self.calc_d90_epq()

        #bins1min = arange(around(min(mag.data['d90'])), around(max(mag.data['d90'])), 1.)

        bins1min = arange(around(min(mag.data['d90'])), around(max(mag.data['d90'])), 1./24./60.)
        N, bins = histogram(mag.data['d90'], bins = bins1min)
        N[N==0] = 1.

        Babs, bins = histogram(mag.data['d90'], bins = bins1min, weights = mag.data['Babs'])
        Babs = Babs / N
        index_Babs = searchsorted(bins1min[1:-1], self.data['d90_epq'])
        self.add_data('Babs', Babs[index_Babs])
        Br, bins = histogram(mag.data['d90'], bins = bins1min, weights = mag.data['Br'])
        Br = Br / N
        index_Br = searchsorted(bins1min[1:-1], self.data['d90_epq'])
        self.add_data('Br', Br[index_Br])
        Bt, bins = histogram(mag.data['d90'], bins = bins1min, weights = mag.data['Bt'])
        Bt = Bt / N
        index_Bt = searchsorted(bins1min[1:-1], self.data['d90_epq'])
        self.add_data('Bt', Bt[index_Bt])
        Bn, bins = histogram(mag.data['d90'], bins = bins1min, weights = mag.data['Bn'])
        Bn = Bn / N
        index_Bn = searchsorted(bins1min[1:-1], self.data['d90_epq'])
        self.add_data('Bn', Bn[index_Bn])
        # add magnetic field angles in radian:
        self.Br = Br
        # Todo: Achtung: NaNs drin
        Br = self.data['Br']
        Bt = self.data['Bt']
        Bn = self.data['Bn']
        self.add_data('Bphi', (arctan2(Bt , Br)))
        self.add_data('Btheta',  (arcsin(Bn / sqrt(Br**2 + Bt**2 + Bn**2))))

        # add magnetic field angles in degree:
        self.add_data('Bphi_deg', (self.data['Bphi'] * 180. / pi))
        self.add_data('Btheta_deg', (self.data['Btheta'] * 180. / pi))