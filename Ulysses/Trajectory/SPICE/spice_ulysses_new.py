
import datetime
from typing import List
import numpy as np
from sys import exit
from etspice import SUN, ULYSSES, EARTH

# Constants:
km_per_AU = 1.495979e8



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
        if len(TF) == 2:
            delta_t = (TF[1] - TF[0]).total_seconds()
        elif len(TF) == 0 or len(TF) == 1:
            if len(TF) == 0:
                TF.append(datetime.datetime(1992,1,1))       
            delta_t = (datetime.datetime(TF[0].year+1,TF[0].month,TF[0].day,TF[0].hour)-TF[0]).total_seconds()
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
        paras = ['R', 'long', 'lat']
        self.data = {p:[] for p in paras}
        if self.RF[0] == 'pool':
            # pool data is a file merged from the two Ulysses archive files 'helio.dat' and
            # 'ulysses_daily_heliocentric_data_1990-2009.txt' (which on their own don't contain both HG and HC
            # coordinate systems independently)
            pool_data = read_pool(self.times)
            if self.RF[1] == 'EQ':
                # Equatorial System is mostly called HG (heliographic) within the archive files
                self.data['R'] = self.sync_times(pool_data['datetimes'],pool_data['R'])
                self.data['long'] = self.sync_times(pool_data['datetimes'],pool_data['HG_Long'])
                self.data['lat'] = self.sync_times(pool_data['datetimes'],pool_data['HG_Lat'])
            if self.RF[1] == 'EC':
                # Ecliptic System is mostly called HC (heliocentric) within the archive files
                self.data['R'] = self.sync_times(pool_data['datetimes'],pool_data['R'])
                self.data['long'] = self.sync_times(pool_data['datetimes'],pool_data['HC_Long'])
                self.data['lat'] = self.sync_times(pool_data['datetimes'],pool_data['HC_Lat'])
        elif self.RF[0] == 'SPICE':

        else:
            exit("\nFirst argument of RF has to be either \'pool\' or \'SPICE\'\n")


    def sync_times(self, alien_times, data):
        data_sync = np.empty(len(self.times))
        data_sync[:] = np.nan
        mask_t = np.isin(self.times, alien_times)
        mask_at = np.isin(alien_times,self.times)
        data_sync[mask_t] = data[mask_at]
        return data_sync


###############################################################################################
################################### DATA LOADERS ##############################################
###############################################################################################

def read_pool(times):
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
    Returns Ulysses' position after SPICE data

    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: [heliocentric range in AU, latitude, longitude]
    '''
    xyz = ULYSSES.position(time = date, relative_to = SUN, reference_frame = RF) # in km
    if len(xyz) == 3:
        r, theta, phi = utils.cart2spherical(xyz, degrees = True)
        #print(RF.name , np.array([r/1.496e8,theta,phi]))
        return np.array([r/km_per_AU,theta,phi])
    elif len(xyz) > 3:
        positions = []
        for t in xyz:
            r, theta, phi = utils.cart2spherical(t, degrees=True)
            positions.append(np.array([r/km_per_AU,theta,phi]))
        return positions


def locateBody(body, date, RF):
    '''
    Returns a body's position after SPICE data

    :param body: body object, e.g. EARTH
    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: Prints position vector as [R/AU, LAT/deg, LONG/deg]
    '''
    xyz = body.position(time = date, relative_to = SUN, reference_frame = RF)
    r, theta, phi = utils.cart2spherical(xyz, degrees = True)
    return(np.array([r/km_per_AU,theta,phi]))


