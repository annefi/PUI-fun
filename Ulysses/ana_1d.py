import sys
sys.path.append('/home/asterix/fischer/PUI/old_stuff/Ulysses/swics/software/libulpy')
sys.path.append('/home/asterix/fischer/PUI')
from DataLoader.uswipha import uswipha
from dist3D_pui_ulysses import Dist3D
import numpy as np
np.seterr(divide='ignore', invalid='ignore') # Ignore Ipython error messages
from matplotlib import pylab
from WSlice import WSlice
from WShell import WShell
from WSky import WSky
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)

matplotlib.rcParams.update({'font.size': 14,
                            'xtick.major.size': 13,
                            'xtick.major.width': 2,
                            'xtick.minor.size': 8,
                            'xtick.minor.width': 1,
                            'ytick.major.size': 13,
                            'ytick.major.width': 2,
                            'ytick.minor.size': 8,
                            'ytick.minor.width': 1})

#year = [1994,1995]
shellstep = 0.1

fig, ax = plt.subplots(figsize=(8, 7))
ax.set_xlim(-1.05, 4)
ax.xaxis.set_minor_locator(MultipleLocator(.5))
ax.set_xlabel(r'$\mathrm{w_{sw}}$')
ax.set_ylabel('phase space density')

def load_data(y, start, stop, r_au = None, ax = None):
    d1 = uswipha(year=y, tf=[[start,stop]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/')
    d1.sync_swoops()
    d1.sync_traj()
    d1.set_mask('Master', 'vsw', 700, 800, reset=True)
    d1.set_mask('Master', 'rng', 0, 0, reset=True)
    d1.set_mask('Master', 'det', 0, 2, reset=True)  # cut out det = 3 (=rubbish?)
    d1.set_mask('Master', 'ech', 12, 250, reset=True)  # exclude doubles
    d1.set_mask('Master', 'brw', 1, 1, reset=True)
    d1.set_mask('Master', 'epq', 0, 17, reset=True)

    #d1.set_mask('Master','rau', r_au-0.05, r_au+0.05)

    # get a real subset with masks applied:
    print('*** Save Subset ***')
    d1.save_subset('Master', filename='d1.tmp')
    print('*** Load Subset ***')
    d1.load_subset(filename='d1.tmp', force=True)

    D = Dist3D(d1, mass=4, charge=1, sc_vel=True)
    nr = D.d.data['year'].shape
    ax1 = D.wspec_1d(ax = ax, name = "%s, %s - %s"%(y, start, stop), mode='ps')
    # #D.wspec_1d(ax = ax1, mode = 'ps')
    # D.wspec_1d(ax=ax1, mode='norm')
    return ax1, nr


nr_a = []
ax1, nr = load_data(y = 1993, start = 240, stop = 366, ax = ax)
nr_a.append(nr)


for y in [1994]:
    for t in [0,1,2]:
        a, nr = load_data(y = y, start = (t*120)+1, stop = (t+1)*120 , ax=ax1)
        nr_a.append(nr)





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