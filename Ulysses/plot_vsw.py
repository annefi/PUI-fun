import sys
import matplotlib.ticker as ticker
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


def load_year(y):
    d1 = uswipha(year=y, tf=[[1,366]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/')
    d1.sync_swoops()
    #d1.sync_traj()
    d1.set_mask('Master', 'rng', 0, 0, reset=True)
    d1.set_mask('Master', 'det', 0, 2, reset=True)  # cut out det = 3 (=rubbish?)
    d1.set_mask('Master', 'ech', 12, 250, reset=True)  # exclude doubles
    #d1.set_mask('Master', 'brw', 1, 1, reset=True)
    d1.set_mask('Master', 'epq', 0, 17, reset=True)

    # get a real subset with masks applied:
    print('*** Save Subset ***')
    d1.save_subset('Master', filename='d1.tmp')
    print('*** Load Subset ***')
    d1.load_subset(filename='d1.tmp', force=True)

    vsw = d1.data['vsw']
    return vsw

vswbins = arange(200,1001,10)


years = range(1993,2010)

H_col = zeros([vswbins.shape[0]-1, len(years)])
sum_col = []


def loop():
    for iy, year in enumerate(years):
        try:
            vsw = load_year(y = year)
            sum = vsw.shape
            sum_col.append(sum)
            H, b = histogram(vsw, vswbins)
            H_col[:,iy] = H
        except:
            print('no matching data in %s' % year)

yearbins = years + [years[-1]+1]
halfs = arange(yearbins[0] + 0.5, yearbins[-1], 1)


def plot_v(norm = 'max'):
    fig, ax = plt.subplots(figsize=(8, 7))
    colormap = plt.cm.get_cmap("viridis")
    colormap.set_under('white')
    if norm == 'max':
        for i in range(H_col.shape[1]):
            if amax(H_col[:, i]) > 0:
                H_col[:, i] /= float(max(H_col[:, i]))
    ax.text(vswbins[-1]+5, yearbins[-1]+0.2, r'$\sum$ PHA')
    ax.set_xlabel(r'$vsw \, / \, km/s$')
    ax.set_xlabel(r'vsw / $km/s$')

    ax.yaxis.set_major_formatter(ticker.NullFormatter())
    ax.set_yticks(halfs, minor=True)
    ax.set_yticklabels(years, minor=True)
    for tick in ax.yaxis.get_minor_ticks():
        tick.set_pad(14.)
        tick.tick1line.set_markersize(0)
        tick.tick2line.set_markersize(0)
        tick.label1.set_horizontalalignment('center')

    ax.set_yticks(yearbins)
    for i, s in enumerate(sum_col):
        ax.text(vswbins[-1] +10, yearbins[i] + 0.5, '%i'%s, fontsize = 10)

    ax.pcolormesh(vswbins, yearbins, H_col.T, cmap = colormap, vmin = 0.0000001, vmax = H_col.max())



















