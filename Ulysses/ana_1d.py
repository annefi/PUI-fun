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


def ybins_labels(bins, **kwargs):
    bin_width = (max(bins) - min(bins)) / (len(bins) - 1)
    plt.yticks(arange(min(bins)+bin_width/2., max(bins), bin_width), bins, **kwargs)
    plt.ylim(bins[0], bins[-1])

colormap = plt.cm.get_cmap("jet")


shellstep = 0.1
max_vel = 800

wshellmax = getvelocity(4, 1, 0, frac = 1.) / max_vel
wbins = arange(0.3, (wshellmax - 1) + 0.0001, shellstep)



if True:
    def load_data_year(y, start = 1, stop = 166, vel2 = max_vel, r_au = None, ax = None):
        d1 = uswipha(year=y, tf=[[start,stop]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/')
        d1.sync_swoops()
        d1.sync_traj()
        d1.set_mask('Master', 'vsw', 700, vel2, reset=True)
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

    years = range(1993, 1997)
    H_mat = zeros([wbins.shape[0]-1, len(years)])

    def run_through_year(years = years, H_mat = H_mat):
        for iy, y in enumerate(years):
            try:
                H = load_data_year(y = y)
                H_mat[:,iy] = H
            except:
                print('no matching data in %s'%y)
                H_mat[:, iy] = zeros(wbins.shape[0]-1) * -1
        return H_mat


    yearbins = years + [years[-1]+1]

    def plot_h_year(H_mat, norm = None):
        fig, ax = plt.subplots(figsize=(8, 7))
        if norm == 'sum':
            for i in range(H_mat.shape[1]):
                H_mat[:, i] /= float(sum(H_mat[:, i]))
            ax.pcolormesh(wbins, yearbins, H_mat.T)
            ybins_labels(yearbins)
        #ax.pcolormesh(wbins, yearbins, H_mat.T)

if False:

    def load_data_r(r_au, start=1, stop=366, vel2=max_vel, ax=None):
        d1 = uswipha(year=range(1994,1995), tf=[[start, stop]],
                     path='/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/')
        d1.sync_swoops()
        d1.sync_traj()
        d1.set_mask('Master', 'vsw', 700, vel2, reset=True)
        d1.set_mask('Master', 'rng', 0, 0, reset=True)
        d1.set_mask('Master', 'det', 0, 2, reset=True)  # cut out det = 3 (=rubbish?)
        d1.set_mask('Master', 'ech', 12, 250, reset=True)  # exclude doubles
        d1.set_mask('Master', 'brw', 1, 1, reset=True)
        d1.set_mask('Master', 'epq', 0, 17, reset=True)

        # set masks for excluding ecliptic:
        d1.set_mask('Master', 'lat_hg', -90, -25, reset=True)
        d1.set_mask('Master', 'lat_hg', 25, 90)

        d1.set_mask('Master','rau', r_au-0.2, r_au+0.2)

        # get a real subset with masks applied:
        print('*** Save Subset ***')
        d1.save_subset('Master', filename='d1.tmp')
        print('*** Load Subset ***')
        d1.load_subset(filename='d1.tmp', force=True)

        D = Dist3D(d1, mass=4, charge=1, sc_vel=True)

        nr = D.d.data['year'].shape
        H0, norm_arr = D.wspec_1d(ax=ax, name=r"%s $\pm$ 0.2 AU" % (r_au), mode='ps', wbins = wbins)
        H_cts = H0[:]
        H0[norm_arr == 0] = 0
        norm_arr[norm_arr == 0] = 1
        H = H0 / norm_arr

        # set up single plot:
        fig, ax = plt.subplots(figsize=(6,5))
        fig.suptitle('%s'%r_au)
        ax.set_xlim(-0.55,2.1)
        ax.xaxis.set_minor_locator(MultipleLocator(.5))
        ax.set_xlabel(r'$\mathrm{w_{sw}}$')
        ax.set_ylabel('phase space density')
        ax.plot(wbins[:-1], H, drawstyle ='steps-post', label='PSD', linestyle = '-')
        ax.plot(wbins[:-1], H_cts, drawstyle='steps-post', label = 'counts', linestyle = ':')
        ax.plot(wbins[:-1], norm_arr, drawstyle='steps-post', label = 'norm', linestyle = '--')
        ax.legend()
        pylab.show()

        return H


    r_vals = list(arange(1.5, 3.5, 0.5))
    H_mat = zeros([wbins.shape[0]-1, len(r_vals)])

    def run_through_r(r_au = r_vals):
        for ir, r in  enumerate(r_au):
            try:
                H = load_data_r(r_au = r)
                H_mat[:, ir] = H
            except:
                print('no matching data around %s AU'%r)
                H_mat[:, ir] = zeros(wbins.shape[0]-1) * -1

    r_bins = r_vals + [r_vals[-1] + 0.5]

    def plot_h_r(H_mat, norm = None):
        fig, ax = plt.subplots(figsize=(8, 7))
        if norm == 'sum':
            # every r's spec is normalised to 1
            for i in range(H_mat.shape[1]):
                H_mat[:, i] /= float(sum(H_mat[:, i]))
        if norm == 'rel':
            # every r's spec is divided by the smallest r-spec
            for i in range(H_mat.shape[1]):
                H_mat[:, i] /= H_mat[:,0]
        if norm == 'rel_norm':
            # every r's spec is divided by the smallest r-spec and then normalised to 1
            for i in range(H_mat.shape[1]):
                H_mat[:, i] /= H_mat[:, 0]
                H_mat[:, i] /= float(sum(H_mat[:, i]))
        ybins_labels(r_bins)
        ax.pcolormesh(wbins, r_bins, H_mat.T, cmap=colormap)






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


