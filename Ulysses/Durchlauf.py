import sys
sys.path.append('/home/asterix/fischer/PUI/old_stuff/Ulysses/swics/software/libulpy')
sys.path.append('/home/asterix/fischer/PUI')
from DataLoader.uswipha import uswipha
from dist3D_pui_ulysses import Dist3D
from numpy import *
seterr(divide='ignore', invalid='ignore') # Ignore Ipython error messages


def run(year):
    d1 = uswipha(year=year, tf='all', path='/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he/')
    d1.sync_swoops()
    d1.sync_traj()

    ##d1.set_mask('Master','vsw',600,670,reset = True)
    d1.set_mask('Master','rng',0,0,reset=True)
    d1.set_mask('Master','det',0,2,reset=True) # cut out det = 3 (=rubbish?)
    d1.set_mask('Master','ech',12,250,reset=True) # exclude doubles
    d1.set_mask('Master','brw',1,inf,reset=True)

    # get a real subset with masks applied:
    print('*** Save Subset ***')
    d1.save_subset('Master', filename = 'd1.tmp')
    print('*** Load Subset ***')
    d1.load_subset(filename = 'd1.tmp', force = True)

    D = Dist3D(d1, mass = 4, charge = 1, sc_vel = True)
    return D

m = 'counts'


D = run(year = 1993)
pm = D.d.hist1d('wsw2',binx = arange(0,4,0.1))
D = run(year=1994)
D.d.hist1d('wsw2',binx = arange(0,4,0.1), pm = pm)





#
# D = run(year = 1993)
# ax = D.wspec_1d(mode=m, year = 1993)
#
# for y in [1994,1995,1996, 1997, 1998, 1999]:
#     D = run(year=y)
#     D.wspec_1d(mode=m, ax = ax, year = y)