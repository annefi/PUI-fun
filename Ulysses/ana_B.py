import sys
sys.path.append('/home/asterix/fischer/PUI/old_stuff/Ulysses/swics/software/libulpy')
sys.path.append('/home/asterix/fischer/PUI')
from DataLoader.uswipha import uswipha
from dist3D_pui_ulysses import Dist3D
from numpy import *
import numpy as np
seterr(divide='ignore', invalid='ignore') # Ignore Ipython error messages
from matplotlib import pylab

from WSky import WSky
from Wsky_rel import Wsky_rel
import matplotlib

matplotlib.rcParams.update({'font.size': 14,
                            'xtick.major.size': 13,
                            'xtick.major.width': 2,
                            'xtick.minor.size': 8,
                            'xtick.minor.width': 1,
                            'ytick.major.size': 13,
                            'ytick.major.width': 2,
                            'ytick.minor.size': 8,
                            'ytick.minor.width': 1})



year = [1994]
shellstep = 0.1
phirange = [-pi, pi + 0.001]
thetarange = [-pi / 2., pi / 2. + 0.001]
angstep = 10 * pi / 180.


def load_B(B = 90):
    d1 = uswipha(year=year, tf=[[1,300]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/')
    d1.sync_swoops()
    d1.sync_traj()

    d1.set_mask('Master','vsw',750,780,reset = True)
    d1.set_mask('Master','rng',0,0,reset=True)
    d1.set_mask('Master','det',0,2,reset=True) # cut out det = 3 (=rubbish?)
    d1.set_mask('Master','ech',12,250,reset=True) # exclude doubles
    d1.set_mask('Master','brw',1,1,reset=True)

    d1.set_mask('Master','Btheta',-20./180.*np.pi,20./180.*np.pi,reset=True)

    if B == 90:
        d1.set_mask('Master','Bphi',-95./180.*np.pi,-85./180.*np.pi,reset=True)
        d1.set_mask('Master', 'Bphi', 85. / 180. * np.pi, 95. / 180. * np.pi)
    if B == 0:
        d1.set_mask('Master','Bphi',-15/180.*np.pi,15./180.*np.pi,reset=True)
    if B == 45:
        d1.set_mask('Master','Bphi',-140./180.*np.pi,-130./180.*np.pi,reset=True)
        d1.set_mask('Master', 'Bphi', 40. / 180. * np.pi, 50. / 180. * np.pi)


    # get a real subset with masks applied:
    print('*** Save Subset ***')
    d1.save_subset('Master', filename = 'd1.tmp')
    print('*** Load Subset ***')
    d1.load_subset(filename = 'd1.tmp', force = True)

    D = Dist3D(d1, mass = 4, charge = 1, sc_vel = True)


    norm_arr, H0 = D.calc_skymapspec(phirange = phirange, thetarange = thetarange, angstep = angstep, shellstep =
    shellstep)

    H0[norm_arr == 0] = -5
    norm_arr[norm_arr == 0] = 1
    H = H0 / norm_arr

    return H, D.wshellmax


H0, wshellmax0 = load_B(B=0)
H45, wshellmax45 = load_B(B=45)
H90, wshellmax90 = load_B(B=90)

wsmax= min([wshellmax0, wshellmax45, wshellmax90])


for H in [H0,H45,H90]:
    # cut out extra high values (at the edges: only few counts) that destroy the colormap:
    wshellbins = arange(shellstep, (wsmax - 1) + 0.0001, shellstep)
    for shell in range(len(wshellbins) - 1):
        for i in range(1):
            H[:, :, shell][H[:, :, shell] > (mean(H[:, :, shell]) + 3 * std(H[:, :,shell]))] = 0


wsky0 = Wsky_rel(H = H0, wshellmax = wsmax, name = '0')
wsky45 = Wsky_rel(H = H45, wshellmax = wsmax, name = '45')
wsky90 = Wsky_rel(H = H90, wshellmax = wsmax, name = '90')

H_0 = H0 + H45 + H90
H_0[(H0==-5) | (H45 == -5) | (H90 == -5)] = NaN

H00 = H0/H_0
H045 = H45/H_0
H090 = H90/H_0

H00[isnan(H00)] = -5
H045[isnan(H045)] = -5
H090[isnan(H090)] = -5



wskyrel0 = Wsky_rel(H = H00, wshellmax = wsmax, name = '0 rel')
wskyrel45 = Wsky_rel(H = H045, wshellmax = wsmax, name = '45 rel')
wskyrel90 = Wsky_rel(H = H090, wshellmax = wsmax, name = '90 rel')


