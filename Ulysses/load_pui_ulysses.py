import sys
sys.path.append('/home/asterix/fischer/PUI/old_stuff/Ulysses/swics/software/libulpy')
sys.path.append('/home/asterix/fischer/PUI')
from DataLoader.uswipha import uswipha
from dist3D_pui_ulysses import Dist3D
import numpy as np
np.seterr(divide='ignore', invalid='ignore') # Ignore Ipython error messages
from matplotlib import pylab

###
# Script for creating an instance d of uswipha and setting masks (s.b.)
###

# load Ulysses data:
years = [1994]
d = uswipha(year=years,tf='all', path = '/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he/epq/')
#d = uswipha(year=years,tf=[[1,20]], path = '/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he2/epq/')
d.sync_swoops()
d.sync_traj()

# d.set_mask('Master','rng',0,0,reset=True)
# d.set_mask('Master','det',0,2,reset=True) # cut out det = 3 (=rubbish?)
# d.set_mask('Master','ech',12,250,reset=True) # exclude doubles
# d.set_mask('Master','brw',1,np.inf,reset=True)
# d.set_mask('Master','epq',1,58,reset=True) # transitional mask to match with the ACE velocity steps
#
# # get a real subset with masks applied:
# print('*** Save Subset ***')
# d.save_subset('Master')
# print('*** Load Subset ***')
# d.load_subset(force=True)
#
# D = Dist3D(d)
# from WSpec import WSpec
# ws = WSpec(D,color_norm = 'sg')