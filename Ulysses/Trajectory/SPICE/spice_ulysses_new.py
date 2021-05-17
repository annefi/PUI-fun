import datetime
from typing import List
import numpy as np
import matplotlib.pyplot as plt
import os, sys
from etspice import *
import spiceypy as spice

# Constants:
km_per_AU = 1.495979e8


#####################
### SPICE kernels ###
#####################

# J2000, ECLIPJ2000 are already loaded

# SPICE built-in frames:
B1950 = ReferenceFrame([kernels.planets], 'B1950')
ECLIPB1950 = ReferenceFrame([kernels.planets], 'ECLIPB1950')

# STEREO Kernel "heliospheric... .tf"
HCI = ReferenceFrame([kernels.heliospheric_frames],'HCI')

# DIY kernels:
my_kernel = kernels.LocalKernel('Ulysses/Trajectory/SPICE/data/test_tf.tf') # load additional rf kernel
my_kernel.load()
HCI_B = ReferenceFrame([my_kernel],'HCI_B1950')
HCI_J = ReferenceFrame([my_kernel],'HCI_J2000') # same as HCI but without freeze_epoch (tiiiiny deviation in rotational matrix)


if os.path.exists("../fusessh/data/projects/spice"):
    os.environ['SPICE_DATA_DIR'] = "../fusessh/data/projects/spice"
elif os.path.exists("/data/projects/spice"):
    os.environ['SPICE_DATA_DIR'] = "/data/projects/spice"
else:
    sys.exit('SPICE_DATA_DIR could not be found.\nProbably working from home and not having SSH-ed to asterix?')


class TrajectUl():
    """

    :param TF: time frame, should be a list of start and end time as
        datetime.datetime objects (one year is assumed if list is empty or contains
        only start time) 
    :param RF: 2-element-list: [source, reference frame]. E.g. ['pool','EQ']
        If source == 'pool': possible reference frames: 'EQ' (equatorial BC1950, HG), 'EC' (ecliptic BC1950, HC)
        If source == 'SPICE': possible reference frames: (...)
    :param DT: time increment in seconds; default is 24 hours
    """
    def __init__(self, TF: List[datetime.datetime], RF: List[str] = None, DT: int = None):
        if DT == None:
            DT = 60 * 60 * 24 # 24 h in seconds
        if len(TF) == 1:
            TF.append(datetime.datetime(TF[0].year+1,TF[0].month,TF[0].day,TF[0].hour))
        elif len(TF) == 0:
            TF = [datetime.datetime(1992,1,1), datetime.datetime(1993,1,1)]
        delta_t = (TF[1] - TF[0]).total_seconds() # auxiliary time delta for setting up self.times
        self.times = [TF[0] + datetime.timedelta(seconds = t) for t in range(0,int(delta_t + DT),DT)]
        self.t_southpass = [datetime.datetime(1994, 9, 13), datetime.datetime(2000, 11, 27),
                            datetime.datetime(2007, 2, 7)]
        self.t_northpass = [datetime.datetime(1995, 7, 31), datetime.datetime(2001, 10, 13),
                            datetime.datetime(2008, 1, 14)]
        if RF == None:
            RF = ['pool', 'EQ']
        self.RF = RF
        self.get_data()    

    def get_data(self):
        paras = ['R', 'lat', 'long']
        self.data = {p:[] for p in paras}
        if self.RF[0] == 'pool':
            # pool data is a file merged from the two Ulysses archive files 'helio.dat' and
            # 'ulysses_daily_heliocentric_data_1990-2009.txt' (which on their own don't contain both HG and HC
            # coordinate systems independently)
            pool_data = read_pool()
            if self.RF[1] == 'EQ':
                # Equatorial System is mostly called HG (heliographic) within the archive files
                self.data['R'] = self.sync_times(pool_data['datetimes'],pool_data['R'])
                self.data['lat'] = self.sync_times(pool_data['datetimes'],pool_data['HG_Lat'])
                self.data['long'] = self.sync_times(pool_data['datetimes'],pool_data['HG_Long'])
                self.lbl = 'Ul. Archive Solar Eq.'
                self.clr = "darkmagenta"
            elif self.RF[1] == 'EC':
                # Ecliptic System is mostly called HC (heliocentric) within the archive files
                self.data['R'] = self.sync_times(pool_data['datetimes'],pool_data['R'])
                self.data['lat'] = self.sync_times(pool_data['datetimes'],pool_data['HC_Lat'])
                self.data['long'] = self.sync_times(pool_data['datetimes'],pool_data['HC_Long'])
                self.lbl = 'Ul. Archive Ecliptic'
                self.clr = "orchid"
            else:
                sys.exit("\nSecond argument of RF not recognised. Has to be \'EQ\' or \'EC\' for pool data.\n")
        elif self.RF[0] == 'SPICE':
            try:
                for t in self.times:
                    [R,lat,long] = locateUlysses(t, self.RF[1])
                    self.data['R'].append(R)
                    self.data['lat'].append(lat)
                    self.data['long'].append(long) 
                self.lbl = 'SPICE %s' %self.RF[1].name
                self.clr = "fuchsia"
            except:
                sys.exit('Second RF argument not recognised for SPICE')
        else:
            sys.exit("\nFirst argument of RF has to be either \'pool\' or \'SPICE\'\n")


    def sync_times(self, alien_times, data):
        ''' Synchronise the data set times with self.times
        '''
        data_sync = np.empty(len(self.times))
        data_sync[:] = np.nan
        mask_t = np.isin(self.times, alien_times)
        mask_at = np.isin(alien_times,self.times)
        data_sync[mask_t] = data[mask_at]
        return data_sync

    def plot_timeseries(self, axes = None):
        ''' Plot R, lat, long over time
        '''
        # set up the plot:
        if axes is None:
            fig, axes = plt.subplots(nrows = 3, sharex = True)
        ### R ###
        axes[0].plot(self.times, self.data['R'], linestyle = 'None', marker = 'o', ms = 2., label = self.lbl, c = self.clr, alpha= 0.5)
        axes[0].set_xlim(self.times[0],self.times[-1                                                                     ])
        axes[0].set_ylabel('R in AU')
        lg = axes[0].legend(loc='upper center', ncol=3, fontsize='small', bbox_to_anchor=(0.5, 1.3), fancybox=
                True, framealpha=1., facecolor='#fff5f8', shadow=True)
        for legend_handle in lg.legendHandles:
                legend_handle._legmarker.set_markersize(6)
        ### LAT ###
        axes[1].plot(self.times, self.data['lat'], linestyle = 'None', marker = 'o', ms = 2., c = self.clr, alpha= 0.5)
        axes[1].set_ylabel('Lat. in deg.')
        axes[1].set_yticks([-90,-45,0,45,90])
        axes[1].set_ylim(-95,95)
        ### LONG ###
        axes[2].plot(self.times, self.data['long'], linestyle = 'None', marker = 'o', ms = 2., c = self.clr, alpha= 0.5)
        axes[2].set_ylabel('Long. in deg.')
        axes[2].set_yticks([-180,-90,0,90,180])
        axes[2].set_ylim(-185,185)
        # plot vertical lines at polar passes:
        plt.vlines(self.t_southpass, ymin = -180, ymax = 360, color = 'firebrick', alpha = 0.5, linestyle = 'dashed')
        plt.vlines(self.t_northpass, ymin = -180, ymax = 360, color = 'navy', alpha = 0.5, linestyle = 'dashed')
        plt.gcf().autofmt_xdate()
        plt.gcf().tight_layout()
        plt.gcf().align_ylabels()
        for ax in axes:
            ax.grid(True)
        #plt.subplots_adjust(hspace=None)
        return axes

    def comp_timeseries(self, T, axes = None):
        ''' Plot difference between two sets of trajectory data for R, lat, long
        '''
        if axes is None:
            fig, axes = plt.subplots(nrows = 3, sharex = True, sharey = True)
        ymin = -0.001
        ymax = 0.001
        ### R ###
        axes[0].plot(self.times, self.data['R']- T.data['R'], linestyle = 'None', marker = 'o', ms = 1., label = "%s - %s" %(self.lbl, T.lbl))
        axes[0].set_xlim(self.times[0],self.times[-1])
        axes[0].set_ylabel(r'$\Delta$R in AU')
        lg = axes[0].legend(loc='upper center', ncol=1, fontsize='small', bbox_to_anchor=(0.5, 1.3), fancybox=
                True, framealpha=1., facecolor='#dfe9f5', shadow=True)
        for legend_handle in lg.legendHandles:
                legend_handle._legmarker.set_markersize(6)
        ### LAT ###
        axes[1].plot(self.times, self.data['lat'] - T.data['lat'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[1].set_ylabel(r'$\Delta$Lat. in deg.')
        #axes[1].set_ylim(-90,90)
        ### LONG ###
        axes[2].plot(self.times, self.data['long'] - T.data['long'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[2].set_ylabel(r'$\Delta$Long. in deg.')
        #axes[2].set_ylim(-180,180)

        ymin = min(-0.001,min(self.data['R']- T.data['R']),min(self.data['lat'] - T.data['lat']),min(self.data['long'] - T.data['long'])) 
        ymax = max(0.001,max(self.data['R']- T.data['R']),max(self.data['lat'] - T.data['lat']),max(self.data['long'] - T.data['long']))
        axes[0].set_ylim(-max(abs(ymin),abs(ymax))*2,max(abs(ymin),abs(ymax))*2) 
        print(ymin, ymax)
        plt.gcf().autofmt_xdate()
        plt.gcf().tight_layout()
        plt.gcf().align_ylabels()
        for ax in axes:
            ax.grid(True)
            ax.hlines(y=0.0, xmin = self.times[0], xmax = self.times[-1], color = 'dimgray')
        return axes

###############################################################################################
################################### DATA LOADERS ##############################################
###############################################################################################

def read_pool():
    '''
    Reader for Ulysses trajectory data from condensed file traj_data_ulysses_pool.dat
    :return: dict with keys 'Year', 'DOY', 'MM', 'DD', 'ESP', 'SPE', 'SEP', 'R', 'R_km', 'HC_Lat', 'HC_Long', 'HG_Lat',
                'HG_Long', 'HG_Long_wrtE', 'v', 'v_R', 'v_T', 'v_N', 'datestring'
    '''
    path_pool = "Ulysses/Trajectory/trajectory_data/traj_data_ulysses_pool.dat"
    fin = open(path_pool,'r')
    keys = fin.readline().split()
    for headerline in range(3):
        fin.readline()
    p_dict = {k:[] for k in keys}
    for line in fin:
        data = line.split()
        for i,k in enumerate(p_dict.keys()):
            if k == 'HG_Long':
                p_dict[k].append(float(data[i])-180.)
            else:
                p_dict[k].append(float(data[i]))
    p_dict["datetimes"] = []
    for i,year in enumerate(p_dict['Year']):
        p_dict['datetimes'].append(datetime.datetime(int(year),int(p_dict['MM'][i]),int(p_dict['DD'][i])))
    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    fin.close()
    return p_dict


def locateUlysses(date, RF):
    '''
    Return Ulysses' position after SPICE data

    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: spherical coordinates [heliocentric range in AU, latitude, longitude] with latitude in [-90 deg, 90 deg], longitude in [-180 deg, 180 deg]
    '''
    xyz = ULYSSES.position(time = date, relative_to = SUN, reference_frame = RF) # in km
    if len(xyz) == 3:
        r, theta, phi = utils.cart2spherical(xyz, degrees = True)
        #print(RF.name , np.array([r/1.496e8,theta,phi]))
        return np.array([r/km_per_AU,theta,phi])
    elif len(xyz) > 3:
        positions = []
        for t in xyz:
            r, theta, phi = utils.cart2spherical(t, degrees = True)
            positions.append(np.array([r/km_per_AU,theta,phi]))
        return positions

def locateBody(body, date, RF):
    '''
    Return a body's position after SPICE data

    :param body: body object, e.g. EARTH
    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: spherical coordinates [heliocentric range in AU, latitude, longitude] with latitude in [-90 deg, 90 deg], longitude in [-180 deg, 180 deg]
    '''
    xyz = body.position(time = date, relative_to = SUN, reference_frame = RF)
    r, theta, phi = utils.cart2spherical(xyz, degrees = True)
    return(np.array([r/km_per_AU,theta,phi]))