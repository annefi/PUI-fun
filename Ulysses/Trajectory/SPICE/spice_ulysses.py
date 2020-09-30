from etspice import SUN, ULYSSES
from etspice import ReferenceFrame, utils
from etspice import kernels
import datetime
import os
import numpy as np
import matplotlib.pyplot as plt
from typing import List

#os.environ['SPICE_DATA_DIR'] = "../fusessh/data/projects/spice"
os.environ['SPICE_DATA_DIR'] = "/data/projects/spice"

#my_kernel = kernels.LocalKernel('Ulysses/Trajectory/SPICE/metakernel.tm') # load additional kernels via meta kernel
#my_kernel.load()

my_kernel = kernels.LocalKernel('Ulysses/Trajectory/SPICE/data/test_tf.tf') # load additional rf kernel
my_kernel.load()

# SPICE built-in frames:
from etspice import J2000, ECLIPJ2000
B1950 = ReferenceFrame([kernels.planets], 'B1950')
ECLIPB1950 = ReferenceFrame([kernels.planets], 'ECLIPB1950')

# STEREO Kernel "heliospheric... .tf"
HCI = ReferenceFrame([kernels.heliospheric_frames],'HCI')

# DIY kernel
HCI_T2 = ReferenceFrame([my_kernel],'HCI_T2')
HCI_N = ReferenceFrame([my_kernel],'HCI_NEW')


def cart2sph(t, deg=False):
    """
    cart2sph(t,deg)

    Transforms a cartesian t to spherical coordinates.

    The input vector has to be in cartesian coordinates. The angles angles of the output vector phi and theta (r_vec[
    1],r_vec[2]) will be returned in radians. If deg == True the angles of the output vector phi and theta (r_vec[1],
    r_vec[2]) will be returned in degrees.

    Parameters
    ----------
    t : numpy.array with shape (3,)
            First argument.
    deg :   bool
            Third argument.

    Returns
    -------
    output : numpy.array with shape (3,)
        Returns the vector t in spherical coordinates.

    Examples
    --------
    >>> eg.cart2sph(numpy.array([1,1,1]),True)
    [  1.73205081  45.          54.73561032]
    """
    from numpy import sqrt, arctan2, arccos, pi, array

    x = t[0]
    y = t[1]
    z = t[2]

    r = sqrt(x ** 2. + y ** 2. + z ** 2.)
    phi = arctan2(y, x)
    theta = arccos(z / r)

    if deg:
        out = array([r, phi / pi * 180., theta / pi * 180.])
    else:
        out = array([r, phi, theta])

    return out

def locateUlysses(date, RF, spher = True):
    '''
    Returns Ulysses' position after SPICE data

    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: [heliocentric range in AU, latitude, longitude]
    '''
    xyz = ULYSSES.position(time = date, relative_to = SUN, reference_frame = RF)
    if spher == True:
        r, theta, phi = utils.cart2spherical(xyz, degrees = True)
    #print(RF.name , np.array([r/1.496e8,theta,phi]))
    return np.array([r/1.496e8,theta,phi])

def locateBody(body, date, RF, spher = True):
    '''
    Returns a body's position after SPICE data

    :param body: body object, e.g. EARTH
    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return:
    '''
    xyz = body.position(time = date, relative_to = SUN, reference_frame = RF)
    if spher == True:
        r, theta, phi = utils.cart2spherical(xyz, degrees = True)
    print(RF.name , np.array([r/1.496e8,theta,phi]))


def read_pool():
    path_pool = "Ulysses/Trajectory/trajectory_data/traj_data_ulysses_pool.dat"
    fin = open(path_pool,'r')
    paras = fin.readline().split()
    for headerline in range(3):
        fin.readline()
    p_dict = {p:[] for p in paras}
    for line in fin:
        data = line.split()
        for i,p in enumerate(p_dict.keys()):
            p_dict[p].append(float(data[i]))
    p_dict["datestring"] = []
    for i,year in enumerate(p_dict['Year']):
        p_dict['datestring'].append("%i-%i-%i" % (year,p_dict['MM'][i],p_dict['DD'][i]))
    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    fin.close()
    return p_dict

def read_ulysses_daily():
    path_pool = "Ulysses/Trajectory/trajectory_data/ulysses_daily_heliocentric_data_1990-2009.txt"
    fin = open(path_pool,'r')
    for headerline in range(4):
        fin.readline()
    paras = fin.readline().split()
    p_dict = {p:[] for p in paras}
    for headerline in range(2):
        fin.readline()
    for line in fin:
        data = line.split()
        for i,p in enumerate(p_dict.keys()):
            p_dict[p].append(float(data[i]))
    p_dict["datestring"] = []
    for i,year in enumerate(p_dict['YYYY']):
        p_dict['datestring'].append("%i-%i-%i" % (year,p_dict['MM'][i],p_dict['DD'][i]))
    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    fin.close()
    return p_dict

def read_helio_dat():
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
        # small workaround as there's only DOY datagiven in helio.dat:
        date = datetime.datetime(int(iyear),1,1) + datetime.timedelta(p_dict['DOY'][i])
        MM = date.month
        DD = date.day
        p_dict['datestring'].append("%i-%i-%i" % (iyear,MM,DD))
    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    fin.close()
    return p_dict

def get_pool_data(date):
    '''

    :param date: datetime.datetime object
    :return:
    '''
    data = read_pool()
    datestring = "%i-%i-%i" % (date.year, date.month, date.day)
    index = np.where(data['datestring'] == datestring)[0][0]
    print("HC       R_AU: %s Lat: %s, Long: %s \nHG     R_AU: %s  Lat: %s,  Long: %s \n \n" %(data['R'][index],
                                                                                         data['HC_Lat'][index],
                                                                    data['HC_Long'][index],data['R'][index],
                                                                    data['HG_Lat'][index],data['HG_Long'][index]))

def comp_rf(date, RF = HCI):
    #get_pool_data(date)
    locateUlysses(date, ECLIPJ2000)
    locateUlysses(date, ECLIPB1950)
    locateUlysses(date, HCI)
    locateUlysses(date, HCI_T2)
    locateUlysses(date, HCI_N)

def plot_ts(tf, RF):
    '''
    :param tf: list of start and end date for time series
    :param RF: list of Reference Frames that will be plotted
                    > Possible first arguments:
                        "SP" --- calculated by SPICE
                        "UD" --- data from "ulysses_daily... .txt"
                        "HE" --- data from "helio.dat"
                        "PO" --- data from the pooled file. Should be
                                matching with data files for the most parts.
                    > Check resp. read-in-function (e.g. read_pool()) 
                        for possible suffixes
    Example: plot_ts([d1,d2], [["SP",ECLIPJ200,"LAT"]])
                with d1, d2 being datetime.datetime objects
    '''
    # create timeseries:
    first_day = datetime.datetime(tf[0].year,tf[0].month,tf[0].day)
    last_day = datetime.datetime(tf[1].year, tf[1].month, tf[1].day)
    delta = last_day - first_day
    times = [first_day + datetime.timedelta(days = x) for x in range(delta.days + 1)]

    # set up the plot
    fig, ax = plt.subplots()
    test_data = np.random.random(len(times))
    # real data:
    plot_dict = {p:[] for p in ['y_dim', 'label', 'data', 'RF']}
    for frame in RF:
        if frame[0] == "SP":
            data_SP = []
            if frame[2] == "LAT":
                for t in times:
                    data_SP.append(locateUlysses(t,frame[1])[1])
            elif frame[2] == "LONG":
                for t in times:
                    data_SP.append(locateUlysses(t,frame[1])[2])
            else:
                print("Third argument has not been recognised. Choose one of \"LAT\", \"LONG\".")
            plot_dict["y_dim"].append(frame[2])
            plot_dict["label"].append("SPICE %s" % frame[1])
            plot_dict['data'].append([data_SP])
            plot_dict['RF'].append(frame[0])
            #ax.plot(times, data_SP, linestyle="None", marker="v", ms="5", label = "SPICE %s" %frame[2])
        elif frame[0] == "UD":
            pass
            data_UD = []
            ud_dict = read_ulysses_daily()
            if frame[1] == "lat":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year,t.month,t.day)
                    data_UD.append(ud_dict['lat'][ud_dict['datestring'] == t_ds])
                plot_dict["y_dim"].append('LAT')
            if frame[1] == "RA":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year,t.month,t.day)
                    data_UD.append(ud_dict['lat'][ud_dict['datestring'] == t_ds])
                plot_dict["y_dim"].append('LONG')
            if frame[1] == "DEC":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year,t.month,t.day)
                    data_UD.append(ud_dict['lat'][ud_dict['datestring'] == t_ds])
            plot_dict["label"].append("ulysses_daily %s" % frame[1])
            plot_dict['data'].append([data_UD])
            plot_dict['RF'].append(frame[0])
        
        elif frame[0] == "HE":
            pass
        elif frame[0] == "PO":
            pass
        else:
            print("First assignment has not been recognised. Choose one of \"SP\", \"UD\", \"HE\", \"PO\".")

    ax.set_ylabel("Degrees")
    fig.autofmt_xdate()
    ax.legend()
    plt.show()
    


# def create_file(RF):
#     first_day = datetime.datetime(1990,)
#     last_day = datetime.datetime()
#     file_path = "Ulysses/Trajectory/SPICE/%s" %RF
#     fout = open(file_path, 'w')