from matplotlib import pylab

from DataLoader.uswipha import uswipha # PHA loader
from dist3D_pui_ulysses import Dist3D
from WSlice import WSlice

d = uswipha(year = 1995, tf=[[1, 4]]) # load He+ PHA data
d.sync_swoops() # synchronize SW data
d.sync_traj() # synchronize trajectory data

''' some filtering '''
d.set_mask('Master','rng',0,0,reset=True)
d.set_mask('Master','det',0,2,reset=True) # cut out det = 3 (=rubbish?)
d.set_mask('Master','ech',12,250,reset=True) # exclude doubles
d.set_mask('Master', 'epq', 0, 19, reset=True) 

# get a real subset with masks applied:
print('*** Save Subset ***')
d.save_subset('Master', filename = 'd1.tmp')
print('*** Load Subset ***')
d.load_subset(filename = 'd1.tmp', force = True)

D3 = Dist3D(d, mass = 4, charge = 1, sc_vel = True)

W = WSlice(D3, mode = 'ps') # mode is 'ps' for phase space density, can also be 'counts' or 'norm' (for phase space volume)

# W.init_plot() in ipython opens an interactive figure: click thoruh the slices with arrows left/right and change the cut direction (along R/T/N) with arrows up/down