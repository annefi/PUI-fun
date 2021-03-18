
import datetime
from typing import List
import numpy as np



class TrajectUl():
    """

    :param TF: time frame, should be a list of start and end time as
        datetime.datetime objects (one year is assumed if list is empty or contains
        only start time) 
    :param RF: reference frame, can be 'pool', 'helio', 'u_daily' ... 
    :param DT: time increment in seconds; default is 24 hours
    """
    def __init__(self, TF: List[datetime.datetime], RF: str = None, DT: int = None):
        if DT == None:
            DT = 60 * 60 * 24 # 24 h in seconds
        if len(TF) == 2:
            delta_t = (TF[1] - TF[0]).total_seconds()
        elif len(TF) == 0 or len(TF) == 1:
            if len(TF) == 0:
                TF.append(datetime.datetime(1992,1,1))       
            delta_t = (datetime.datetime(TF[0].year+1,TF[0].month,TF[0].day,TF[0].hour)-TF[0]).total_seconds()
        self.times = [TF[0] + datetime.timedelta(seconds = t) for t in range(0,int(delta_t + DT),DT)]
        if RF == None:
            RF = 'pool'
        self.RF = RF
        self.get_data()    

    def get_data(self):
        if self.RF == 'pool':
            self.data = read_pool(self.times)
        if self.RF == 'helio':
            self.data = read_helio_dat()
        if self.RF == 'u_daily':
            self.data = read_ulysses_daily()




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
    HG_lat = np.empty(len(times))
    mask =

    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    fin.close()
    return p_dict


def read_pool_pandas(times):
    pass


def read_helio_dat():
    '''
    Reader for Ulysses trajectory data from helio.dat
    :return: dict with keys "Year", "DOY", "HR", "MN", 'R_AU', 'HG_LAT', 'HC_RA', 'HC_ECL_LAT', 'LONG_WRT_EARTH', "datestring"
    '''
    path_pool = "Ulysses/Trajectory/trajectory_data/helio.dat"
    fin = open(path_pool,'r')
    paras_all = fin.readline().split()
    paras = paras_all[:4] + ['R_AU', "HG_LAT", "HC_RA", "HC_ECL_LAT", "LONG_WRT_EARTH"]
    p_dict = {p:[] for p in paras}
    for headerline in range(5):
        fin.readline()
    for line in fin:
        data_all = line.split()
        data = data_all[:4] + data_all[-5:]
        for i,p in enumerate(p_dict.keys()):
            p_dict[p].append(float(data[i]))
    p_dict["datestring"] = []
    for i,iyear in enumerate(p_dict['Year']):
        # small workaround as there's only DOY data given in helio.dat:
        date = datetime.datetime(int(iyear),1,1) + datetime.timedelta(days = p_dict['DOY'][i] - 1)
        MM = date.month
        DD = date.day
        p_dict['datestring'].append("%i-%i-%i" % (iyear,MM,DD))
    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    fin.close()
    return p_dict

def read_ulysses_daily():
    '''
    Reader for Ulysses trajectory data from ulysses_daily_heliocentric_data_1990-2009.txt
    :return: dict with keys "YYYY", "MM", "DD", "DOY", "R", "lat", "RA", "DEC", "long", "datestring"
    '''
    path_pool = "Ulysses/Trajectory/trajectory_data/ulysses_daily_heliocentric_data_1990-2009.txt"
    fin = open(path_pool,'r')
    for headerline in range(4):
        fin.readline()
    paras_all = fin.readline().split()
    paras = paras_all[:3] + [paras_all[4]] + [paras_all[12]] + paras_all[-4:]
    p_dict = {p:[] for p in paras}
    for headerline in range(2):
        fin.readline()
    for line in fin:
        data_all = line.split()
        data = data_all[:3] + [data_all[4]] + [data_all[12]] + data_all[-4:]
        for i,p in enumerate(p_dict.keys()):
            p_dict[p].append(float(data[i]))
    p_dict["datestring"] = []
    for i,year in enumerate(p_dict['YYYY']):
        p_dict['datestring'].append("%i-%i-%i" % (year,p_dict['MM'][i],p_dict['DD'][i]))
    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    fin.close()
    return p_dict

