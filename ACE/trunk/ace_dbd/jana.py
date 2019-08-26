import pylab as pyl
from ace_data import ace_data
from matplotlib import rcParams
import numpy as np

ion = ["He2+","O6+","Fe8+","Fe9+","Fe10+"]
rc = rcParams
rc["figure.subplot.hspace"] = 0.
rc["xtick.direction"] = "in"
rc["ytick.direction"] = "in"
rc["xtick.top"] = True
rc["ytick.right"] = True
rc["xtick.major.width"] = 2.
rc["ytick.major.width"] = 2.
rc["axes.linewidth"] = 2.
rc["legend.frameon"] = False
class plot_jana(object):
    def __init__(self,year,tf,ion=ion):
        self.d = ace_data(year=year,tf=tf,ion=ion)
        self.tf = tf
        self.ion = ion
        self.year = year

    def plot(self):
        fig = pyl.figure()
        ax1 = fig.add_subplot(3,1,1)
        ax2 = fig.add_subplot(3,1,2)
        ax3 = fig.add_subplot(3,1,3)


        uT,ind = np.unique(self.d.data["time"],return_index = True)
        ax1.plot(uT,self.d.data["velHe2+"][ind],label=r"He$^{2+}$")
        ax1.plot(uT,self.d.data["velO6+"][ind],label=r"O$^{6+}$")
        #m=self.d.data["ctsFe9+"][ind]>3.
        #ax1.plot(uT[m],self.d.data["velFe9+"][ind][m],label=r"v$_{Fe^{9+}}$")
        #m=self.d.data["ctsFe10+"][ind]>3.
        ax1.plot(uT,self.d.data["velFe10+"][ind],label=r"Fe$^{10+}$")
        ax1.plot(uT,self.d.data["vsw"][ind],label="H$^{1+}$",color="k")
        ax1.set_ylabel(r"v$_{ion}$ [km/s]")
        ax1.legend(ncol = 4)

        ax2.plot(uT,self.d.data["dvHe2+"][ind],label=r"He$^{2+}$")
        ax2.plot(uT,self.d.data["dvO6+"][ind],label=r"O$^{6+}$")
        #m=self.d.data["ctsFe9+"][ind]>3.
        #ax1.plot(uT[m],self.d.data["velFe9+"][ind][m],label=r"v$_{Fe^{9+}}$")
        #m=self.d.data["ctsFe10+"][ind]>3.
        ax2.plot(uT,self.d.data["dvFe10+"][ind],label=r"Fe$^{10+}$")
        ax2.set_ylabel(r"$\Delta$v$_{ion-proton}$ [km/s]")
        ax2.set_ylim(-50,50)
        ax2.plot([uT[0],uT[-1]],[0,0],color="k")
        ax2.legend(ncol = 3)

        ax3.plot(uT,self.d.data["alpha"][ind])
        ax3.plot([uT[0],uT[-1]],[90,90],color="k")
        ax3.set_ylim(0,180)
        ax3.set_ylabel(r"$\alpha$ [$\circ$]")
        ax3.set_xlabel("DoY %i"%(self.d.data["year"][0]))

        pyl.savefig("%i-%i_%i.pdf"%(self.tf[0][0],self.tf[0][1]+1,self.year[0]))
