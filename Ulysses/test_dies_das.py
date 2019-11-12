import matplotlib.pyplot as plt
from matplotlib import pylab
from numpy import arange, array
from Trajectory.ulysses_traj import ulysses_traj
from DataLoader.ulysses_mag_loader import mag_loader
from DataLoader.uswipha import uswipha
from Trajectory.ul_calc_traj import hg_to_hc, hc_to_hg, calc_v

fig, ax = plt.subplots(figsize=(6, 5))

def test_diff_sec(D):
    # function to check the difference of w-value between first and last (9th) detector point in one det-sec-combi
    # for different sectors over epq
    for sec in range(8):
        arr = []
        for epq in range(60):
            p1 = D.wspace[10,0,0,epq,0,sec,0,0]
            p2 = D.wspace[10,0,0,epq,0,sec,0,8]
            arr.append(p2-p1)
        ax.plot(arange(0,len(arr)), arr, label="%s"%sec)
        ax.legend()
    plt.show()


def test_diff_vsw(D):
    # function to check the difference of w-value between first and last (9th) detector point in one det-sec-combi
    # for different vsw over epq
    for v in range(0,52,10):
        arr = []
        for epq in range(60):
            p1 = D.wspace[v,0,0,epq,2,7,0,0]
            p2 = D.wspace[v,0,0,epq,2,7,0,8]
            arr.append(p2-p1)
        ax.plot(arange(0,len(arr)), arr, label="%s"%D.vswbins[v])
        ax.legend()
    plt.show()


def test_event_handle():
    from matplotlib.pyplot import figure, show
    import numpy as npy
    from numpy.random import rand

    # picking on a scatter plot (matplotlib.collections.RegularPolyCollection)

    x, y, c, s = rand(4, 100)

    def onpick3(event):
        ind = event.ind
        print 'onpick3 scatter:', ind, npy.take(x, ind), npy.take(y, ind)

    fig = figure()
    ax1 = fig.add_subplot(111)
    col = ax1.scatter(x, y, 100*s, c, picker=True)
    fig.canvas.mpl_connect('pick_event', onpick3)

    show()

def checken_ob_r():
    '''
    ... einen Unterschied macht, wenn ich in km statt AU nehme...
    :return:
    '''
    traj = ulysses_traj(year = [1993], tf = [[1,10]], path = 'Trajectory/trajectory_data/traj_data_ulysses_pool.dat')
    for i in range(3):
        HC_Lat = traj.data['HC_Lat'][i]
        HC_Long = traj.data['HC_Long'][i]
        HG_Lat = traj.data['HG_Lat'][i]
        HG_Long = traj.data['HG_Long'][i]
        R_AU = traj.data['R'][i]
        R_km = traj.data['R_km'][i]

        vec_HC_km = array([R_km, HC_Long, HC_Lat])
        vec_HC_AU = array([R_AU, HC_Long, HC_Lat])

        vec_HG_km = array([R_km, HG_Long, HG_Lat])
        vec_HG_AU = array([R_AU, HG_Long, HG_Lat])

        HG_AU = hc_to_hg(vec_HC_AU, long_shift= 180.)
        HG_km = hc_to_hg(vec_HC_km, long_shift= 180.)
        HG_km[0] /= 149597870.7

        print(vec_HG_AU)
        print(HG_AU)
        print(HG_km)
        print('\n')

        HC_AU = hg_to_hc(vec_HG_AU, long_shift = 180.)
        HC_km = hg_to_hc(vec_HG_km, long_shift=180.)
        HC_km[0] /= 149597870.7

        # print(vec_HC_AU)
        # print(HC_AU)
        # print(HC_km)
        # print('\n')


def analyse_why_eigen_v_wackelt(R = 'km'):
    traj = ulysses_traj(year = [1994], tf = [[1,10]])
    for i in range(1,5):
        if R == 'km':
            vec1 = array([traj.data['R_km'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
            vec2 = array([traj.data['R_km'][i+1], traj.data['HG_Long'][i+1], traj.data['HG_Lat'][i+1]])
            calc_v(vec1,vec2,24*60*60, R = 'km')
        if R == 'AU':
            vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
            vec2 = array([traj.data['R'][i+1], traj.data['HG_Long'][i+1], traj.data['HG_Lat'][i+1]])
            calc_v(vec1,vec2,24*60*60, R = 'AU')


def evolution_RTN():
    traj = ulysses_traj(year = [1995], tf = [[1,10]])
    for i in range(1,5):
            vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
            vec2 = array([traj.data['R'][i+1], traj.data['HG_Long'][i+1], traj.data['HG_Lat'][i+1]])
            calc_v(vec1,vec2,24*60*60, R = 'AU')




def evolution_B_data():
    '''
    plot B data from original data file
    '''
    fig, ax = plt.subplots(figsize=(8, 7))
    ax.set_xlim(1994,1999)
    ax.set_ylim(-4, 4)

    fig2, ax2 = plt.subplots(figsize=(8, 7))


    d = uswipha(year = range(1997, 1999), tf = [[1, 366]], path =
    '/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he/')
    d.sync_mag()


    mag_data = d.data['Br']
    doy =d.data['doy']
    year = d.data['year']
    time = year + doy/365.

    ax.plot(time, d.data['Br'], marker = 'o', label = 'BR', ms = .1)
    ax.plot(time, d.data['Bt'], marker='o', label='BT', ms = 1)
    ax.plot(time, d.data['Bn'], marker='o', label='BN', ms = 1)

    ax2.plot(time, d.data['Bphi'], marker = 'o', label = 'Bphi', ms = 1)
    ax2.plot(time, d.data['Btheta'], marker='o', label='Btheta', ms=1)

    ax.legend()
    ax2.legend()
    #pylab.show()



def evolution_B_PHA():
    '''
    plot B data from reduced PHA file
    '''
    fig1, ax1 = plt.subplots(figsize=(8, 7))
    fig2, ax2 = plt.subplots(figsize=(8, 7))
    fig3, ax3 = plt.subplots(figsize=(8, 7))
    d = uswipha(year = range(1993,2001), tf = [[1,366]], path ='/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/')
    doy = d.data['doy'][::10]
    year = d.data['year'][::10]
    time = year + doy / 365.
    ax1.plot(time, d.data['Bphi'][::10], marker='o', label='Bphi', ms=1)
    ax2.plot(time, d.data['Btheta'][::10], marker='o', label='Btheta', ms=1)
    # ax1.plot(time, d.data['BR'][::100], marker='o', label='BR', ms=1)
    # ax2.plot(time, d.data['BT'][::100], marker='o', label='BT', ms=1)
    # ax3.plot(time, d.data['BN'][::100], marker='o', label='BN', ms=1)
    ax1.legend()
    ax2.legend()
    ax3.legend()
    plt.show()

