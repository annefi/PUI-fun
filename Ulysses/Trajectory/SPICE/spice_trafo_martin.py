import datetime
from typing import List, Type
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


def locateUlysses(date, RF):
    '''
    Return Ulysses' position acc. to SPICE data

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
    Return a body's position acc. to SPICE data

    :param body: body object, e.g. EARTH
    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: spherical coordinates [heliocentric range in AU, latitude, longitude] with latitude in [-90 deg, 90 deg], longitude in [-180 deg, 180 deg]
    '''
    xyz = body.position(time = date, relative_to = SUN, reference_frame = RF)
    r, theta, phi = utils.cart2spherical(xyz, degrees = True)
    return(np.array([r/km_per_AU,theta,phi]))

def timerange(start_t: datetime,end_t: datetime,dt: int):
    """ Create a datetime.datetime range

    :param start_t: datetime.datetime of first time step
    :param end_t: datetime.datetime of last time step
    :param dt: time increment in seconds
    :return: numpy.array of datetime.datetimes from start_t to end_t with increment dt
    """
    delta_t = (end_t - start_t).total_seconds()  # auxiliary time delta
    times = [start_t + datetime.timedelta(seconds=t) for t in range(0, int(delta_t + dt), dt)]
    return times


class TrajectoryUlysses():
    """
    :param TF: time frame, should be a list of start and end time as
        datetime.datetime objects (one year is assumed if list is empty or contains
        only start time)
    :param RF: 2-element-list: [source, reference frame]. E.g. ['pool','EQ']
        If source == 'pool': possible reference frames: 'EQ' (equatorial BC1950, HG), 'EC' (ecliptic BC1950, HC)
        If source == 'SPICE': possible reference frames: (...)
    :param DT: time increment in seconds; default is 24 hours
    """
    def __init__(self, TF: List[datetime.datetime], RF: str = None, DT: int = None):
        if DT == None:
            DT = 60 * 60 * 24 # 24 h in seconds
        if len(TF) == 1:
            TF.append(datetime.datetime(TF[0].year+1,TF[0].month,TF[0].day,TF[0].hour))
        elif len(TF) == 0:
            TF = [datetime.datetime(1992,1,1), datetime.datetime(1993,1,1)]
            print("time frame set automatically to %s - %s" %(TF[0],TF[1]))
        self.times = timerange(TF[0],TF[1],DT)
        self.t_southpass = [datetime.datetime(1994, 9, 13), datetime.datetime(2000, 11, 27),
                            datetime.datetime(2007, 2, 7)]
        self.t_northpass = [datetime.datetime(1995, 7, 31), datetime.datetime(2001, 10, 13),
                            datetime.datetime(2008, 1, 14)]
        if RF == None:
            RF = 'EQ'
        self.RF = RF
        self.get_data()
        self.get_aa_data()

    def get_data(self):
        paras = ['r', 'lat', 'long']
        self.data = {p:[] for p in paras}
        print('getdata')

    def get_aa_data(self):
        paras_asp = ['asp_lat', 'asp_long', 'asp_tot']
        self.data.update({p:[] for p in paras_asp})
        print('get asp ang data')

    def sync_times(self, alien_times, data):
        """ Synchronise the data set times with self.times

        No nearest neighbour sampling etc., just checking for coincidence.
        NaNs for gaps if alien_times has a lower resolution than self.times
        """
        data_sync = np.empty(len(self.times))
        data_sync[:] = np.nan
        mask_t = np.isin(self.times, alien_times)
        mask_at = np.isin(alien_times,self.times)
        data_sync[mask_t] = data[mask_at]
        return data_sync