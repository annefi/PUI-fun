import sys
sys.path.append('/home/asterix/fischer/ulysses/swics/software/libulpy')
from uswipha import uswipha
from pylib import dbData
import numpy as np
import pylab,matplotlib

#colormap = pylab.cm.get_cmap("spectral")
#colormap.set_under("white")

# create artificial data
r_mu , r_sigma = 0.5,0.02
phi_mu, phi_sigma = np.pi/2., .1 #in degree

r_data = np.random.normal(r_mu, r_sigma, 10000)
phi_data = np.random.normal(phi_mu, phi_sigma, 10000)
phi_data_cont = np.random.random(size=10000) *2.*np.pi

binr = np.arange(0,1,.01)
binphi = np.arange(0,2*np.pi,1/200.)

H, redges, phiedges = np.histogram2d(r_data, phi_data, bins = [binr,binphi])

fig = pylab.figure()
ax = fig.gca()
ax = pylab.subplot(111, polar=True)

#ATTENTION angular coordinate goes first!
Mesh = ax.pcolormesh(phiedges,redges, H)
pylab.show()