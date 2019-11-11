import sys
sys.path.append('/home/asterix/fischer/PUI/old_stuff/Ulysses/swics/software/libulpy')
sys.path.append('/home/asterix/fischer/PUI')
from DataLoader.uswipha import uswipha
from dist3D_pui_ulysses import Dist3D
from DataLoader.uswiutils import getvelocity
from numpy import *
seterr(divide='ignore', invalid='ignore') # Ignore Ipython error messages
from matplotlib import pylab
from WSlice import WSlice
from WShell import WShell
from WSky import WSky
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)

matplotlib.rcParams.update({'font.size': 12,
                            'xtick.major.size': 13,
                            'xtick.major.width': 2,
                            'xtick.minor.size': 8,
                            'xtick.minor.width': 1,
                            'ytick.major.size': 13,
                            'ytick.major.width': 2,
                            'ytick.minor.size': 8,
                            'ytick.minor.width': 1})

shellstep = 0.1
max_vel = 800

wshellmax = getvelocity(4, 1, 0, frac = 1.) / max_vel
wbins = arange(0.4, (wshellmax - 1) + 0.0001, shellstep)

def load_data(y, start = 1, stop = 166, vel2 = max_vel, r_au = None, ax = None):
    d1 = uswipha(year=y, tf=[[start,stop]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/')
    d1.sync_swoops()
    d1.sync_traj()
    d1.set_mask('Master', 'vsw', 650, vel2, reset=True)
    d1.set_mask('Master', 'rng', 0, 0, reset=True)
    d1.set_mask('Master', 'det', 0, 2, reset=True)  # cut out det = 3 (=rubbish?)
    d1.set_mask('Master', 'ech', 12, 250, reset=True)  # exclude doubles
    d1.set_mask('Master', 'brw', 1, 1, reset=True)
    d1.set_mask('Master', 'epq', 0, 17, reset=True)


    # set masks for excluding ecliptic:
    d1.set_mask('Master', 'lat_hg', -90, -25, reset = True)
    d1.set_mask('Master', 'lat_hg', 25, 90)


    #d1.set_mask('Master','rau', r_au-0.05, r_au+0.05)

    # get a real subset with masks applied:
    print('*** Save Subset ***')
    d1.save_subset('Master', filename='d1.tmp')
    print('*** Load Subset ***')
    d1.load_subset(filename='d1.tmp', force=True)

    D = Dist3D(d1, mass=4, charge=1, sc_vel=True)

    nr = D.d.data['year'].shape
    H0, norm_arr =  D.wspec_1d(ax = ax, name = "%s, %s - %s"%(y, start, stop), mode='ps', wbins = wbins)




    H_cts = H0[:]
    H0[norm_arr == 0] = 0
    norm_arr[norm_arr == 0] = 1
    H = H0 / norm_arr

    # # set up single plot:
    # fig, ax = plt.subplots(figsize=(6,5))
    # fig.suptitle('%s'%y)
    # ax.set_xlim(-0.55,2.1)
    # ax.xaxis.set_minor_locator(MultipleLocator(.5))
    # ax.set_xlabel(r'$\mathrm{w_{sw}}$')
    # ax.set_ylabel('phase space density')
    # ax.plot(wbins[:-1], H, drawstyle ='steps-post', label='PSD', linestyle = '-')
    # ax.plot(wbins[:-1], H_cts, drawstyle='steps-post', label = 'counts', linestyle = ':')
    # ax.plot(wbins[:-1], norm_arr, drawstyle='steps-post', label = 'norm', linestyle = '--')
    # ax.legend()
    #pylab.show()

    return H



years = range(1997, 2005)
H_mat = zeros([wbins.shape[0]-1, len(years)])

def run_through(years = years, H_mat = H_mat):
    for iy, y in enumerate(years):
        try:
            H = load_data(y = y)
            H_mat[:,iy] = H
        except:
            print('no matching data in %s'%y)
            H_mat[:, iy] = zeros(wbins.shape[0]-1) * -1
    return H_mat



yearbins = years + [years[-1]+1]

def plot_h(H_mat, norm = None):
    fig, ax = plt.subplots(figsize=(8, 7))
    if norm == 'sum':
        for i in range(H_mat.shape[1]):
            H_mat[:, i] /= float(sum(H_mat[:, i]))
        ax.pcolormesh(wbins, yearbins, H_mat.T)

    #ax.pcolormesh(wbins, yearbins, H_mat.T)


# try:
#     load_data(r_au = 2.6, ax = ax1)
# except:
#     pass
#
# try:
#     load_data(r_au = 2.0, ax = ax1)
# except:
#     pass
#
# try:
#     load_data(r_au = 1.5, ax = ax1)
# except:
#     pass
#
# # try:
# #     load_data(r_au = 1.0, ax = ax1)
# # except:
# #     pass


pylab.show()