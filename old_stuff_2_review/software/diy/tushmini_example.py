import sys
sys.path.append('/home/asterix/fischer/ulysses/swics/software/libulpy')
from uswipha import uswipha
from pylib import dbData
import numpy as np
from matplotlib import pylab
from matplotlib.animation import FuncAnimation

# Ulysses-Daten:
d = uswipha(year=[1994],tf=[[1,36]])

# artificial data:
# N = 10000
# np.random.seed(10)
# r_art = np.random.randint(low=1,high=3+1,size=N)
# phi_art = np.random.randint(low=0,high=7+1,size=N)

def polarplot(data,prodr,prodphi):
    #rvals = prodr 		#for artificial data
    #phivals = prodphi

    # get_data() is a function of dbData
    rvals = d.get_data(['Master'],prodr)
    phivals = d.get_data(['Master'],prodphi)

    # deciding on your bins
    binr = np.linspace(0,3,4)
    binphi = np.linspace(0,8,9)

    # numpy.histogram returns the actual histogram-values (you can test that out with a small example or look for examples of 2d histogram on google),
    # the bin edges in x-direction and the bin edges in y-direction (in my case polar bins)
    Hist, redges, phiedges = np.histogram2d(rvals, phivals, bins = [binr,binphi])

    # only for polar plot:
    phiedges_rad = np.linspace(0,2*np.pi,9)
    redges_full = np.array([0,1,2,3.5])


    fig = pylab.figure()

    ax = pylab.subplot(111, projection='polar')
    ax.set_ylim(0,2.8)
    ax.set_yticks([])
    ax.set_theta_direction(-1)
    ax.set_theta_zero_location('N')
    ax.set_xticks([x+(2*np.pi/16.) for x in np.linspace(0,2*np.pi,8,endpoint=False)])
    ax.set_xticklabels([str(i) for i in np.arange(1,9,1)])

    # setting which colours should be used
    colormap = pylab.cm.get_cmap("jet")

    # here you do the actual plotting
    #ATTENTION angular coordinate goes first! (only important for polar plot)
    Mesh = ax.pcolormesh(phiedges_rad, redges_full, Hist, cmap = colormap)

    # that's for the colour 'legend'
    colorbar = pylab.colorbar(Mesh, ax=ax)
    return rvals, binr, redges # return not obligatory, only for testing out in ipython

a,b,c = polarplot(d,'det','sec')

pylab.show()