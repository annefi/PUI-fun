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


def load_year(y):
    d1 = uswipha(year=y, tf='all', path='/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/')
    d1.sync_swoops()
    d1.sync_traj()
    d1.set_mask('Master', 'rng', 0, 0, reset=True)
    d1.set_mask('Master', 'det', 0, 2, reset=True)  # cut out det = 3 (=rubbish?)
    d1.set_mask('Master', 'ech', 12, 250, reset=True)  # exclude doubles
    d1.set_mask('Master', 'brw', 1, 1, reset=True)
    d1.set_mask('Master', 'epq', 0, 17, reset=True)

    # get a real subset with masks applied:
    print('*** Save Subset ***')
    d1.save_subset('Master', filename='d1.tmp')
    print('*** Load Subset ***')
    d1.load_subset(filename='d1.tmp', force=True)

    vsw = d1.data['vsw']
    return vsw

vswbins = arange(0,1000,10)
years = range(1993,2007)
H_col = zeros([vswbins.shape[0]-1, len(years)])
sum_col = []


def loop():
    for iy, year in enumerate(years):
        vsw = load_year(y = year)
        sum = vsw.sum()
        sum_col.append(sum)
        H, b = histogram(vsw, vswbins)
        H_col[:,iy] = H

yearbins = years + [years[-1]+1]

def plot_v():
    fig, ax = plt.subplots(figsize=(8, 7))
    ax.text(1.5,1994,'test')
    ax.pcolormesh(vswbins, yearbins, H_col.T)




















