from etspice import SUN, ULYSSES, EARTH
from etspice import ReferenceFrame, utils
from etspice import kernels
import datetime
import os, sys
import numpy as np
import matplotlib.pyplot as plt
from sys import exit
from Ulysses.Trajectory.ul_calc_traj import hc_to_hg, calc_asp_angles

if os.path.exists("../fusessh/data/projects/spice"):
    os.environ['SPICE_DATA_DIR'] = "../fusessh/data/projects/spice"
elif os.path.exists("/data/projects/spice"):
    os.environ['SPICE_DATA_DIR'] = "/data/projects/spice"
else:
    sys.exit('SPICE_DATA_DIR could not be found.\nProbably working from home and not having SSH-ed to asterix?')

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

def locateUlysses(date, RF):
    '''
    Returns Ulysses' position after SPICE data

    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: [heliocentric range in AU, latitude, longitude]
    '''
    xyz = ULYSSES.position(time = date, relative_to = SUN, reference_frame = RF)
    if len(xyz) == 3:
        r, theta, phi = utils.cart2spherical(xyz, degrees = True)
        #print(RF.name , np.array([r/1.496e8,theta,phi]))
        return np.array([r/1.496e8,theta,phi])
    elif len(xyz) > 3:
        positions = []
        for t in xyz:
            r, theta, phi = utils.cart2spherical(t, degrees=True)
            positions.append(np.array([r/1.496e8,theta,phi]))
        return positions


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
    return(np.array([r/1.496e8,theta,phi]))


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

def read_aa_data():
    path_aa = "Ulysses/Trajectory/trajectory_data/aa_data.dat"
    fin = open(path_aa, 'r')
    paras = fin.readline().split()
    p_dict = {p:[] for p in paras}
    for line in fin:
        data = line.split()
        for i,p in enumerate(p_dict.keys()):
            p_dict[p].append(float(data[i]))
    p_dict['datestring'] = []
    for i, iyear in enumerate(p_dict['YEAR']):
        date = datetime.datetime(int(iyear), 1, 1) + datetime.timedelta(days=p_dict['DOY'][i] - 1)
        MM = date.month
        DD = date.day
        p_dict['datestring'].append("%i-%i-%i" % (iyear, MM, DD))
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

def get_aa(t,RF, vec_hc = "None", vecE_hg = "None"):
    '''
    :param t:
    :param RF:
    :param vec_hc: [R,lat,long]
    :param vecE_hc: [R,lat,long]
    :return: asp_angs = (aspphi,asptheta)
    '''
    if vec_hc == "None":
        vec_hc = locateUlysses(t, RF)
    if vecE_hg == "None":
        vecE = locateBody(EARTH, t, HCI_J)
        vecE_hg = [vecE[0], vecE[2], vecE[1]]
    vec_hg = hc_to_hg([vec_hc[0], vec_hc[2], vec_hc[1]], long_shift = 0.)
    # print("vec_hg new: ", vec_hg)
    # print("vec_hg Earth new: ", vecE_hg)
    asp_angs = calc_asp_angles(vec_hg, vecE_hg, l_s_sc=0.)
    return asp_angs

class CompTimeseries:
    """
    Todo
    """
    def __init__(self, frames, para, tf = None):
        # create timeseries:
        if tf == None:
            # default time frame:
            first_day = datetime.datetime(1990,11,6)
            last_day = datetime.datetime(1990,12,1)
            delta = last_day - first_day
        elif len(tf) == 2:
            first_day = datetime.datetime(tf[0].year, tf[0].month, tf[0].day)
            last_day = datetime.datetime(tf[1].year, tf[1].month, tf[1].day)
            delta = last_day - first_day
        elif len(tf) == 1:
            first_day = datetime.datetime(tf[0].year, tf[0].month, tf[0].day) - datetime.timedelta(days=1)
            last_day = datetime.datetime(tf[0].year, tf[0].month, tf[0].day) + datetime.timedelta(days=1)
            delta = last_day - first_day
        self.times = [first_day + datetime.timedelta(days=x) for x in range(delta.days + 1)]
        self.t_southpass = datetime.datetime(1994,9,13)
        self.t_northpass = datetime.datetime(1995,7,31)
        self.frames = frames
        self.para = para
        self.get_data()

    def get_data(self):
        self.data_dict = {p: [] for p in ['frame', 'data', 'data2', 'label']}
        for frame in self.frames:
            if len(frame) == 2:
                if frame[0] == 'SP':
                    self.get_spice_data(frame[1])
                if frame[0] == 'UD':
                    self.get_ud_data(frame[1])
                if frame[0] == 'HE':
                    self.get_he_data(frame[1])
                if frame[0] == 'CALC':
                    self.get_calc_data()
                if frame[0] == 'CALC_SP':
                    self.get_calc_data_SP()
            else:
                print('Every frame needs to have two elements, e.g. [\'SP\',ECLIPB1950] or [\'UD\',\'ECL\']. Please '
                      'try again.')
                exit()

    def get_spice_data(self, RF):
        # calculate with SPICE
        data_SP = []
        data_SP2 = []
        if self.para == 'LAT':
            #data_SP2.append(locateUlysses(self.times,RF)[1])
            for t in self.times:
                data_SP.append(locateUlysses(t, RF)[1])
        elif self.para == 'LONG':
            for t in self.times:
                data_SP.append(locateUlysses(t, RF)[2])
        else:
            print("Second argument has not been recognised. Choose one of \"LAT\", \"LONG\".")
        self.data_dict['frame'].append('SP')
        self.data_dict['data'].append(data_SP)
        self.data_dict['data2'].append(data_SP2)
        self.data_dict['label'].append("SPICE %s" % (RF.name))

    def get_ud_data(self, RF):
        # data from "ulysses_daily_heliocentric_data_1990-2009.txt"
        data_UD = []
        ud_dict = read_ulysses_daily()
        if self.para == 'LAT':
            if RF == 'ECL':
                for t in self.times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    data_UD.append(ud_dict['DEC'][ud_dict['datestring'] == t_ds][0])
            elif RF == 'EQ':
                for t in self.times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    data_UD.append(ud_dict['lat'][ud_dict['datestring'] == t_ds][0])
            else:
                print("Second argument has not been recognised. Choose one of \'ECL\' and \'EQ\'.")
                exit()
        if self.para == 'LONG':
            if RF == 'ECL':
                for t in self.times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    if ud_dict['RA'][ud_dict['datestring'] == t_ds][0] <= 180.:
                        data_UD.append(ud_dict['RA'][ud_dict['datestring'] == t_ds][0])
                    else:
                        data_UD.append(ud_dict['RA'][ud_dict['datestring'] == t_ds][0]-360.)
            else:
                exit("Second frame argument has not been recognised. LONG not available in equatorial (HG) system for "
                      "ulysses_daily.")
        self.data_dict['frame'].append('UD')
        self.data_dict['data'].append(data_UD)
        self.data_dict['label'].append("ulysses_daily %s" % (RF))

    def get_he_data(self, RF):
        # data from "helio.txt"
        data_HE = []
        he_dict = read_helio_dat()
        if self.para == 'LAT':
            if RF == 'ECL':
                for t in self.times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    data_HE.append(he_dict['HC_ECL_LAT'][he_dict['datestring'] == t_ds][0])
            elif RF == 'EQ':
                for t in self.times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    data_HE.append(he_dict['HG_LAT'][he_dict['datestring'] == t_ds][0])
            else:
                exit("Second argument has not been recognised. Choose one of \'ECL\' and \'EQ\'.")
        if self.para == 'LONG':
            if RF == 'EQ':
                for t in self.times:
                    t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                    data_HE.append(he_dict['HC_RA'][he_dict['datestring'] == t_ds][0] - 180.)
            else:
                exit("Second argument has not been recognised. LONG not available in ecliptic system for "
                      "helio.txt")
        self.data_dict['frame'].append('HE')
        self.data_dict['data'].append(data_HE)
        self.data_dict['label'].append("helio.txt %s" % (RF))

    def get_calc_data(self):
        # calculate HG (EQ) data by rotating HC (ECLIP) data from ulysses daily
        data_CALC = []
        ud_dict = read_ulysses_daily()
        if self.para == 'LAT':
            for t in self.times:
                t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                hc_R = ud_dict['R'][ud_dict['datestring'] == t_ds][0]
                hc_long = ud_dict['RA'][ud_dict['datestring'] == t_ds][0]
                hc_lat = ud_dict['DEC'][ud_dict['datestring'] == t_ds][0]
                #print('\n\nUD:\n',hc_R,hc_lat,hc_long)
                hg_vec = hc_to_hg([hc_R,hc_long,hc_lat], long_shift = 0.)
                data_CALC.append(hg_vec[2])
        if self.para == 'LONG':
            for t in self.times:
                t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
                hc_R = ud_dict['R'][ud_dict['datestring'] == t_ds][0]
                hc_long = ud_dict['RA'][ud_dict['datestring'] == t_ds][0]
                hc_lat = ud_dict['DEC'][ud_dict['datestring'] == t_ds][0]
                hg_vec = hc_to_hg([hc_R,hc_long,hc_lat], long_shift = 0.)
                data_CALC.append(hg_vec[1])
        self.data_dict['frame'].append('CALC')
        self.data_dict['data'].append(data_CALC)
        self.data_dict['label'].append("EQ calculated")

    def get_calc_data_SP(self):
        # calculate HG (EQ) data by rotation ECLIPB1950 data by SPICE
        data_CALC_SP = []
        if self.para == 'LAT':
            for t in self.times:
                hc_vec = (locateUlysses(t, ECLIPB1950))
                hg_vec = hc_to_hg([hc_vec[0],hc_vec[2],hc_vec[1]], long_shift = 0.)
                #print("\n\n SP:\n",hc_vec)
                data_CALC_SP.append(hg_vec[2])
        if self.para == 'LONG':
            for t in self.times:
                hc_vec = (locateUlysses(t, ECLIPB1950))
                hg_vec = hc_to_hg([hc_vec[0], hc_vec[2], hc_vec[1]], long_shift=0.)
                data_CALC_SP.append(hg_vec[1])
        self.data_dict['frame'].append('CALC')
        self.data_dict['data'].append(data_CALC_SP)
        self.data_dict['label'].append("EQ calculated SP")

    def get_old_aa_data(self):
        data_old_aa_lat = []
        data_old_aa_long = []
        aa_dict = read_aa_data()
        for t in self.times:
            t_ds = "%i-%i-%i" % (t.year, t.month, t.day)
            data_old_aa_lat.append(aa_dict['ASP_THETA'][aa_dict['datestring'] == t_ds][0])
            data_old_aa_long.append(aa_dict['ASP_PHI'][aa_dict['datestring'] == t_ds][0])
        self.data_old_aa_lat = np.array(data_old_aa_lat)
        self.data_old_aa_long = np.array(data_old_aa_long)

    def get_aa(self):
        # calculate aspect angles based on different coordinate systems
        data_aspJ = []
        data_aspB = []
        for t in self.times:
            data_aspJ.append(get_aa(t, RF = ECLIPJ2000))
            data_aspB.append(get_aa(t, RF = ECLIPB1950))
        self.data_aspB = np.array(data_aspB)
        self.data_aspJ = np.array(data_aspJ)

    def plot_ts(self, rou = False, ax = None):
        # set up the plot

        if ax == None:
            fig = plt.figure()
            ax = fig.subplots()

        if self.para == 'LAT':
            ax.set_ylabel("Lat. in degree")
            ax.set_ylim(-90, 90)
            #ax.set_ylim(-79.15, -79.)
        elif self.para == 'LONG':
            ax.set_ylabel("Long. in degree")
            ax.set_ylim(-190, 250)
        for i, dataset in enumerate(self.data_dict['data']):
            if self.data_dict['frame'][i] == 'SP':
                if rou:
                    ax.plot(self.times, np.around(np.array(dataset),2), linestyle='None', label = self.data_dict[
                        'label'][i], marker='v', ms="5", alpha=0.3)
                else:
                    ax.plot(self.times, dataset, linestyle='None', label = self.data_dict['label'][i], marker='v', ms="7", alpha=0.3)
            elif self.data_dict['frame'][i] == 'UD':
                ax.plot(self.times, dataset, linestyle='None', label=self.data_dict['label'][i], marker='o', ms="7",
                        alpha=0.3)
            elif self.data_dict['frame'][i] == 'HE':
                ax.plot(self.times, dataset, linestyle='None', label=self.data_dict['label'][i], marker='s', ms="7",
                        alpha=0.3)
            elif self.data_dict['frame'][i] == 'CALC':
                ax.plot(self.times, dataset, linestyle='None', label=self.data_dict['label'][i], marker='P', ms="7",
                        alpha=0.3)
        # plot vertical lines at polar passes
        plt.vlines(self.t_southpass, ymin = -180, ymax = 360, color = 'firebrick', alpha = 0.5, linestyle = 'dashed')
        plt.vlines(self.t_northpass, ymin = -180, ymax = 360, color = 'navy', alpha = 0.5, linestyle = 'dashed')
        plt.gcf().autofmt_xdate()
        ax.legend()
        ax.grid(True)
        return ax

    def plot_diff(self, rou = False, ax = None):
        '''
        plots the difference between first frame and the other frames resp.
        :return:
        '''
        if len(self.frames) == 1:
            exit('Cannot subtract frames: Only one frame loaded.')
        if ax == None:
            fig = plt.figure()
            diff_ax = fig.subplots()
            if self.para == 'LAT':
                diff_ax.set_ylabel("Diff. of Lat. in degree")
            elif self.para == 'LONG':
                diff_ax.set_ylabel("Diff. of Long. in degree")
        else:
            diff_ax = ax
        ymin = -0.001
        ymax = 0.001
        for i, dataset in enumerate(self.data_dict['data'][1:]):
            #print('i: ', i)
            #print("%s - %s" % (self.data_dict['label'][0],self.data_dict['label'][i]))
            if rou:
                diff_data = np.around(np.array(self.data_dict['data'][0]),2) - np.around(np.array(dataset),2)
            else:
                diff_data = np.array(self.data_dict['data'][0]) - np.array(dataset)
            diff_ax.plot(self.times, diff_data, linestyle='None', label="%s - %s" % (self.data_dict['label'][
                                                0], self.data_dict['label'][i+1]),marker='v',ms="5",alpha=0.3)
            if ax == None:
                ymin = min(list(diff_data) + [ymin])
                ymax = max(list(diff_data) + [ymax])
            if i == len(self.data_dict['data']) - 2:
                break
        diff_ax.set_ylim(ymin * 4., ymax * 4.)
        # plot vertical lines at polar passes
        plt.vlines(self.t_southpass, ymin = ymin * 4., ymax = ymax * 4., color = 'firebrick', alpha = 0.5, linestyle = 'dashed')
        plt.vlines(self.t_northpass, ymin = ymin * 4., ymax = ymax * 4., color = 'navy', alpha = 0.5, linestyle = 'dashed')
        plt.gcf().autofmt_xdate()
        diff_ax.legend()
        diff_ax.grid(True)
        return diff_ax

    def plot_aa(self, ax = None, para = 'both'):
        self.get_old_aa_data()
        self.get_aa()
        if ax == None:
            fig = plt.figure()
            ax = fig.subplots()
        if para == 'LAT' or para == 'both':
            ax.plot(self.times, self.data_old_aa_lat, linestyle = 'None', marker = 'o', label = 'old asptheta', ms = 1.)
            ax.plot(self.times, self.data_aspB[:,1], linestyle = 'None', marker = 'o', label = 'asptheta B', ms = 1.)
            ax.plot(self.times, self.data_aspJ[:, 1], linestyle = 'None', marker = 'o', label = 'asptheta J', ms = 1.)
        if para == 'LONG' or para == 'both':
            ax.plot(self.times, self.data_old_aa_long, linestyle='None', marker='o', label='old aspphi', ms = 1.)
            ax.plot(self.times, self.data_aspB[:, 0], linestyle = 'None', marker = 'o', label = 'aspphi B', ms = 1.)
            ax.plot(self.times, self.data_aspJ[:, 0], linestyle = 'None', marker = 'o', label = 'aspphi J', ms = 1.)
        # plot vertical lines at polar passes
        plt.vlines(self.t_southpass, ymin=-18, ymax=18, color='firebrick', alpha=0.5, linestyle='dashed')
        plt.vlines(self.t_northpass, ymin=-18, ymax=18, color='navy', alpha=0.5, linestyle='dashed')
        plt.gcf().autofmt_xdate()
        ax.legend()
        ax.grid(True)
        return ax


    def plot_dev_aa(self, ax = None, para = 'both'):
        self.get_old_aa_data()
        self.get_aa()
        if ax == None:
            fig = plt.figure()
            ax = fig.subplots()
        if para == 'LAT' or para == 'both':

            ax.plot(self.times, self.data_aspB[:,1] - self.data_old_aa_lat, linestyle = 'None', marker = 'o', label = 'aspdataB - old asptheta', ms = 1.)
            ax.plot(self.times, self.data_aspB[:,1] - self.data_aspJ[:, 1], linestyle = 'None', marker = 'o', label = 'aspdataB - aspdataJ', ms = 1.)
        if para == 'LONG' or para == 'both':
            ax.plot(self.times, self.data_aspB[:,0] - self.data_old_aa_long, linestyle = 'None', marker = 'o', label = 'aspdataB - old aspphi', ms = 1.)
            ax.plot(self.times, self.data_aspB[:,0] - self.data_aspJ[:, 0], linestyle = 'None', marker = 'o', label = 'aspdataB - aspdataJ', ms = 1.)
        # plot vertical lines at polar passes
        plt.vlines(self.t_southpass, ymin=-1.8, ymax=1.8, color='firebrick', alpha=0.5, linestyle='dashed')
        plt.vlines(self.t_northpass, ymin=-1.8, ymax=1.8, color='navy', alpha=0.5, linestyle='dashed')
        plt.gcf().autofmt_xdate()
        ax.legend()
        ax.grid(True)
        return ax

