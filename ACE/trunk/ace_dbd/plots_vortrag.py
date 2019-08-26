from matplotlib import rcParams
from pylab import *

rcParams["font.size"] = 20
rcParams["lines.linewidth"]=3.
rcParams["figure.figsize"]=(16,12)
rcParams["axes.linewidth"]=3.
rcParams["xtick.minor.width"]=1.5
rcParams["xtick.major.width"]=2.
rcParams["xtick.minor.size"]=4.
rcParams["xtick.major.size"]=5.
rcParams["ytick.minor.width"]=1.5
rcParams["ytick.major.width"]=2.
rcParams["ytick.minor.size"]=4.
rcParams["ytick.major.size"]=5.
rcParams["savefig.directory"]="/home/ivar/berger/projects/eigene_vortraege/seminar04072018/"

fig = figure()
subplots_adjust(hspace=0.)
ax1 = fig.add_subplot(4,1,1)
ax2 = fig.add_subplot(4,1,2)
ax3 = fig.add_subplot(4,1,3)
ax4 = fig.add_subplot(4,1,4)

ax1.set_xticks(arange(0,60.1,5.))
ax2.set_xticks(arange(0,60.1,5.))
ax3.set_xticks(arange(0,60.1,5.))
ax4.set_xticks(arange(0,60.1,5.))

ax1.set_yticks(arange(300.,700.1,100.))
ax2.set_yticks(arange(0.,70.1,10.))
ax3.set_yticks(arange(10.,60.1,10.))
ax4.set_yticks(arange(0.,20.1,5.))

ax1.set_ylabel("v$_{sw}$ [km/s]")
ax2.set_ylabel("d$_{sw}$ [cm$^{-3}$]")
ax3.set_ylabel("v$_{th,sw}$ [km/s]")
ax4.set_ylabel("B [nT]")
ax4.set_xlabel("DoY 2007")
