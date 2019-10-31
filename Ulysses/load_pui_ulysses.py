import sys
sys.path.append('/home/asterix/fischer/PUI/old_stuff/Ulysses/swics/software/libulpy')
sys.path.append('/home/asterix/fischer/PUI')
from DataLoader.uswipha import uswipha
from dist3D_pui_ulysses import Dist3D
import numpy as np
np.seterr(divide='ignore', invalid='ignore') # Ignore Ipython error messages
from matplotlib import pylab
from WSpec import WSpec
from WShell import WShell
from WSky import WSky

###
# Script for creating an instance d of uswipha and setting masks (s.b.)
###


# # both:
# He1 = True
# He2 = True

# He1+
He1 = True #False #
He2 = False #True #

# # He2+
# He1 = False #
# He2 = True #


# load Ulysses data:
years = [1993]

if He1:
    d1 = uswipha(year=years, tf=[[1,366]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he/')
    d1.sync_swoops()
    d1.sync_traj()
    d1.sync_mag()

    ##d1.set_mask('Master','vsw',600,670,reset = True)
    d1.set_mask('Master','rng',0,0,reset=True)
    d1.set_mask('Master','det',0,2,reset=True) # cut out det = 3 (=rubbish?)
    d1.set_mask('Master','ech',12,250,reset=True) # exclude doubles
    d1.set_mask('Master','brw',1,np.inf,reset=True)


    d1.set_mask('Master','Btheta_deg',-10.,10.,reset=True)
    d1.set_mask('Master','Bphi_deg',95.,105.,reset=True)

    #d1.set_mask('Master','aa_tot', 0, 10)
    #d1.set_mask('Master','aspphi', -30,-19)
    # d1.set_mask('Master','asptheta',5,7)

    # get a real subset with masks applied:
    print('*** Save Subset ***')
    d1.save_subset('Master', filename = 'd1.tmp')
    print('*** Load Subset ***')
    d1.load_subset(filename = 'd1.tmp', force = True)

    D4 = Dist3D(d1, mass = 4, charge = 1, sc_vel = True)


# load Ulysses data:
years = [1993]

if not He1:
    d1 = uswipha(year=years, tf=[[1,366]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he/')
    d1.sync_swoops()
    d1.sync_traj()
    d1.sync_mag()

    ##d1.set_mask('Master','vsw',600,670,reset = True)
    d1.set_mask('Master','rng',0,0,reset=True)
    d1.set_mask('Master','det',0,2,reset=True) # cut out det = 3 (=rubbish?)
    d1.set_mask('Master','ech',12,250,reset=True) # exclude doubles
    d1.set_mask('Master','brw',1,np.inf,reset=True)



    #d1.set_mask('Master','aa_tot', 0, 10)
    #d1.set_mask('Master','aspphi', 0,30)
    # d1.set_mask('Master','asptheta',5,7)

    # get a real subset with masks applied:
    print('*** Save Subset ***')
    d1.save_subset('Master', filename = 'd1.tmp')
    print('*** Load Subset ***')
    d1.load_subset(filename = 'd1.tmp', force = True)

    D6 = Dist3D(d1, mass = 4, charge = 1, sc_vel = True)












###########
### He2
###########

if He2:

    d2 = uswipha(year=years,tf=[[1,200]], path = '/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he2/epq/')
    d2.sync_swoops()
    d2.sync_traj()

    d2.set_mask('Master','rng',0,0,reset=True)
    d2.set_mask('Master','det',0,2,reset=True) # cut out det = 3 (=rubbish?)
    d2.set_mask('Master','ech',12,250,reset=True) # exclude doubles
    d2.set_mask('Master','brw',1,np.inf,reset=True)

    #d2.set_mask('Master','aa_tot', 0 , 10)
    # d2.set_mask('Master','aspphi', 1,5)
    # d2.set_mask('Master','asptheta',5,7)


    # get a real subset with masks applied:
    print('*** Save Subset ***')
    # d1.save_subset('Master', filename = 'd1.tmp')
    d2.save_subset('Master', filename = 'd2.tmp')
    print('*** Load Subset ***')
    # d1.load_subset(filename = 'd1.tmp', force = True)
    d2.load_subset(filename = 'd2.tmp', force = True)

    D2 = Dist3D(d2, mass = 4, charge = 2)
    #D.hist_sec_det()

    # aa_phi = D.d.get_data('Master','aspphi')[0]
    # aa_theta = D.d.get_data('Master', 'asptheta')[0]
    # print('aspphi: ', aa_phi)
    # print('asptheta: ', aa_theta)
    # #ws = WSpec(D, color_norm = 'sg')
    #
    # # from swics_collimator_ulysses import collimator
    # # c = collimator(aspphi = aa_phi, asptheta = aa_theta, offset_sp=185., nrs_para=6, nrs_perp = 3, edges = True,
    # #                nrs_sec = 5)
    # # c.fancy_plot_FoV()
    # #
    # # pylab.show()
