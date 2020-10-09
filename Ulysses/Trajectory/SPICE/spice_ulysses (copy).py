from etspice import SUN, ULYSSES
from etspice import ReferenceFrame, utils
from etspice import kernels
import datetime
import os
import numpy as np
import matplotlib.pyplot as plt
from sys import exit
from Ulysses.Trajectory.ul_calc_traj import hc_to_hg

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
HCI_B = ReferenceFrame([my_kernel],'HCI_B1950')
HCI_J = ReferenceFrame([my_kernel],'HCI_J2000')

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
        # small workaround as there's only DOY data given in helio.dat:
        date = datetime.datetime(int(iyear),1,1) + datetime.timedelta(days = p_dict['DOY'][i] - 1)
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

def plot_ts(tf, RF, rou = False, diff = False, ax = None):
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
    if len(tf) == 2:
        first_day = datetime.datetime(tf[0].year,tf[0].month,tf[0].day)
        last_day = datetime.datetime(tf[1].year, tf[1].month, tf[1].day)
        delta = last_day - first_day
    if len(tf) == 1:
        first_day = datetime.datetime(tf[0].year,tf[0].month,tf[0].day) - datetime.timedelta(days = 1)
        last_day = datetime.datetime(tf[0].year, tf[0].month, tf[0].day) - datetime.timedelta(days = 1)
        delta = last_day - first_day
    times = [first_day + datetime.timedelta(days = x) for x in range(delta.days + 1)]

    # set up the plot
    if ax == None:
        fig, ax = plt.subplots()
    #test_data = np.random.random(len(times))
    # real data:
    plot_dict = {p:[] for p in ['y_dim', 'label', 'data', 'RF']}
    for frame in RF:
        if frame[0] == "SP":
            # calculate with SPICE
            data_SP = []
            if frame[2] == "LAT":
                for t in times:
                    if rou == True:
                        data_SP.append(round(locateUlysses(t,frame[1])[1],2))
                    else:
                        data_SP.append(locateUlysses(t, frame[1])[1])
            elif frame[2] == "LONG":
                for t in times:
                    if rou == True:
                        data_SP.append(round(locateUlysses(t,frame[1])[2],2))
                    else:
                        data_SP.append(locateUlysses(t, frame[1])[2])
            else:
                print("Third argument has not been recognised. Choose one of \"LAT\", \"LONG\".")
            plot_dict["y_dim"].append(frame[2])
            plot_dict["label"].append("SPICE %s" % frame[1].name)
            plot_dict['data'].append(data_SP)
            plot_dict['RF'].append(frame[0])
            #ax.plot(times, data_SP, linestyle="None", marker="v", ms="5", label = "SPICE %s" %frame[2])

        elif frame[0] == "UD":
            # data from "ulysses_daily_heliocentric_data_1990-2009.txt"
            data_UD = []
            ud_dict = read_ulysses_daily()
            if frame[1] == "lat":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year,t.month,t.day)
                    data_UD.append(ud_dict['lat'][ud_dict['datestring'] == t_ds][0])
                plot_dict["y_dim"].append('LAT')
            elif frame[1] == "RA":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year,t.month,t.day)
                    data_UD.append(ud_dict['RA'][ud_dict['datestring'] == t_ds][0])
                plot_dict["y_dim"].append('LONG')
            elif frame[1] == "DEC":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year,t.month,t.day)
                    data_UD.append(ud_dict['DEC'][ud_dict['datestring'] == t_ds][0])
            else:
                print("Second argument has not been recognised. Choose one of \"lat\", \"RA\", \"DEC\".")

            plot_dict["label"].append("ulysses_daily %s" % frame[1])
            plot_dict['data'].append(data_UD)
            plot_dict['RF'].append(frame[0])
        
        elif frame[0] == "HE":
            # data from "helio.txt"
            data_HE = []
            he_dict = read_helio_dat()
            if frame[1] == "HG_LAT":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    data_HE.append(he_dict['HG_LAT'][he_dict['datestring'] == t_ds][0])
                plot_dict["y_dim"].append('LAT')
            elif frame[1] == "HC_RA":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    data_HE.append(he_dict['HC_RA'][he_dict['datestring'] == t_ds][0] - 180.)
                plot_dict["y_dim"].append('LONG')
            elif frame[1] == "HC_ECL_LAT":
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    data_HE.append(he_dict['HC_ECL_LAT'][he_dict['datestring'] == t_ds][0])
            plot_dict["label"].append("helio.dat %s" % frame[1])
            plot_dict['data'].append(data_HE)
            plot_dict['RF'].append(frame[0])

        elif frame[0] == "CALC":
            data_CALC = []
            he_dict = read_helio_dat()
            ud_dict = read_ulysses_daily()
            if frame[1] == 'HG_LAT':
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    hc_R = ud_dict['R'][ud_dict['datestring'] == t_ds][0]
                    hc_long = ud_dict['RA'][ud_dict['datestring'] == t_ds][0]
                    hc_lat = ud_dict['DEC'][ud_dict['datestring'] == t_ds][0]
                    hg_vec = hc_to_hg([hc_R,hc_long,hc_lat])
                    data_CALC.append(hg_vec[2])
                plot_dict["y_dim"].append('LAT')
            if frame[1] == 'HG_LONG':
                for t in times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    hc_R = ud_dict['R'][ud_dict['datestring'] == t_ds][0]
                    hc_long = ud_dict['RA'][ud_dict['datestring'] == t_ds][0]
                    hc_lat = ud_dict['DEC'][ud_dict['datestring'] == t_ds][0]
                    hg_vec = hc_to_hg([hc_R,hc_long,hc_lat])
                    data_CALC.append(hg_vec[1])
                plot_dict["y_dim"].append('LONG')
            plot_dict["label"].append("calc. %s" % frame[1])
            plot_dict['data'].append(data_CALC)
            plot_dict['RF'].append(frame[0])


        elif frame[0] == "PO":
            pass
        else:
            print("First assignment has not been recognised. Choose one of \"SP\", \"UD\", \"HE\", \"PO\".")
    #return plot_dict
    # y axis depends on lat/long
    if all(y_dim == "LAT" for y_dim in plot_dict['y_dim']):
        ax.set_ylabel("Lat. in degree")
        ax.set_ylim(-90, 90)
    elif all(y_dim == "LONG" for y_dim in plot_dict['y_dim']):
        ax.set_ylabel("Long. in degree")
        ax.set_ylim(-180, 360)
    else:
        print('y dimensions do not match')
        exit()
    if diff == False:
        for i, data in enumerate(plot_dict['data']):
            if plot_dict['RF'][i] == 'SP':
                ax.plot(times, data, linestyle='None', label=plot_dict['label'][i], marker='v', ms = "5", alpha = 0.3)
            elif plot_dict['RF'][i] == 'UD':
                ax.plot(times, data, linestyle = 'None', label = plot_dict['label'][i], marker = 'o', ms = "4", alpha = 0.3)
            elif plot_dict['RF'][i] == 'HE':
                ax.plot(times, data, linestyle = 'None', label = plot_dict['label'][i], marker = 's', ms = "4", alpha = 0.3)
            elif plot_dict['RF'][i] == 'CALC':
                ax.plot(times, data, linestyle='None', label=plot_dict['label'][i], marker='s', ms="4", alpha=0.3)
    else:
        ymin = 0.00001
        ymax = 0.001
        for i, data in enumerate(plot_dict['data']):
            print('i:', i)
            diff_data = np.array(data) - np.array(plot_dict['data'][i+1])
            ax.plot(times, diff_data, linestyle='None', label = "%s - %s" %(plot_dict['label'][i], plot_dict[
                'label'][i+1]), marker='v',
            ms="5", alpha=0.3)
            ymin = min(list(diff_data) + [ymin])
            ymax = max(list(diff_data) + [ymax])
            if i == len(plot_dict['data'])-2:
                break
        ax.set_ylim(ymin*3.,ymax*3.)




    #fig.autofmt_xdate()
    ax.legend()
    ax.grid()
    plt.show()
    return ax, times, plot_dict['data']
