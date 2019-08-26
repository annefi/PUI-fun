import sys
sys.path.append('/home/asterix/fischer/PUI/Ulysses/swics/software/libulpy')
from uswipha import uswipha
from pylib import dbData
import numpy as np
from matplotlib import pylab
from matplotlib.animation import FuncAnimation

###
# Script for creating an instance d of uswipha and setting masks (s.b.)
###

# Ulysses-Daten:
d = uswipha(year=[1994],tf=[[1,20]])

##TODO: PUIs ausschneiden
##TODO: Masken in Fkt. setzen?

d.add_mask('det_0')
#d.set_mask('det_0','det',0,2)

d.add_mask('ssd_0')
d.set_mask('ssd_0','ech',0,0)
d.add_mask('epq_mask')
d.set_mask('epq_mask','epq',0,70)

# artificial data:
# N = 10000
# np.random.seed(10)
# r_art = np.random.randint(low=1,high=3+1,size=N)
# phi_art = np.random.randint(low=0,high=7+1,size=N)