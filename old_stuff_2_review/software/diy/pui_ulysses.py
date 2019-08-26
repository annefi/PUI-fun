import sys
sys.path.append('/home/asterix/fischer/ulysses/swics/software/libulpy')
from uswipha import uswipha
import numpy as np
from matplotlib import pylab
from matplotlib.animation import FuncAnimation
from matplotlib import colors


def polarplot(data,prodr,prodphi):
    '''
    mimics dbData's hist2d()-func but in a polar plot.
    Makes sense for prodr=det and prodpi=sec exclusively
    '''
    #rvals = prodr 		#for artificial data
    #phivals = prodphi

    rvals = d.get_data(['epq_mask','ssd_0','det_0'],prodr)
    phivals = d.get_data(['epq_mask','ssd_0','det_0'],prodphi)

    binr = np.linspace(0,3,4)
    binphi = np.linspace(0,8,9)

    Hist, redges, phiedges = np.histogram2d(rvals, phivals, bins = [binr,binphi])

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

    colormap = pylab.cm.get_cmap("jet")
    #ATTENTION angular coordinate goes first!
    Mesh = ax.pcolormesh(phiedges_rad, redges_full, Hist, cmap = colormap)

    colorbar = pylab.colorbar(Mesh, ax=ax)
    return rvals, binr, redges


def histograms(det,sec):
    fig, (ax1,ax2) = pylab.subplots(1,2,figsize=(15,10))
    ax1.hist(det, bins = [0,1,2,3,4])
    ax1.set_xticks(np.arange(0.5,4.5,1))
    ax1.set_xticklabels(np.arange(0,4,1))
    ax1.set_title('det')
    ax2.hist(sec, bins = np.arange(0,8,1))
    ax2.set_title('sec')
    pylab.ticklabel_format(style='sci', axis='y')



def animate_polar(data,prodr,prodphi,prodz):
    '''
    Has been replaced by a class due to reasons
    '''
    rvals = d.get_data(['ssd_0','det_0'],prodr)
    phivals = d.get_data(['ssd_0','det_0'],prodphi)
    zvals = d.get_data(['ssd_0','det_0'],prodz)

    binr = np.linspace(0, 3, 4)
    binphi = np.linspace(0,8,9)
    binz = np.arange(1,257,1)

    Hist, edges = np.histogramdd([rvals,phivals,zvals],bins=[binr,binphi,binz])
    rvals, phivals, zvals = edges

    # for polar presentation
    phiedges_rad = np.linspace(0,2*np.pi,9)
    # for cutting off the egdes
    redges_full = np.array([0,1,2,3.5])

    # setting up the plot
    fig = pylab.figure()
    ax = pylab.subplot(111, projection='polar')
    ax.set_ylim(0, 2.8)
    ax.set_yticks([])
    ax.set_theta_direction(-1)
    ax.set_theta_zero_location('N')
    ax.set_xticks([x+(2*np.pi/16.) for x in np.linspace(0,2*np.pi,8,endpoint=False)])
    ax.set_xticklabels([str(i) for i in np.arange(1,9,1)])

    colormap = pylab.cm.get_cmap("jet")

    #ATTENTION angular coordinate goes first!
    Quadmesh = ax.pcolormesh(phiedges_rad, redges_full, Hist[:,:,0], cmap = colormap)

    Splay = False
    Z_N = -1

    # def keypressfcn(event):
    #     if event.key == "8":
    #         Splay = True
    #     elif event.key == "2":
    #         # stop animation
    #         Splay = False
    #     elif event.key == "4":
    #         Z_N += 1
    #     elif event.key == "6":
    #         Z_N -= 1

    def animate(i):
        # print(i,Splay,Z_N)
        # if Splay:
        #     Z_N += 1
        data = Hist[:,:,i]
        Quadmesh.set_array(data.ravel())

    #C_ID = fig.canvas.mpl_connect('key_press_event', keypressfcn)
    ani = FuncAnimation(fig, animate, interval=100, frames = zvals.shape[0]-1, blit=False)
    pylab.show()
    return ani





class Animation(uswipha):
    '''
    > Mimics dbData's animate2d()-func but in a polar plot.
    > Makes sense for prodr=det and prodpi=sec exclusively
    > Workflow: set up data w/ load_pui_ulysses, create instance of class, e.g. 'A = Animation(d,'det','sec','doy')
    > Scale determines the way in which pcolormesh scales the color representation.
    '''
    def __init__(self,data,prodr,prodphi,prodz,scale='onestep'):
        self.scale = scale # 'onestep'(default) or 'overall'
        self.prodr = prodr
        self.prodphi = prodphi
        self.prodz = prodz
        self.rvals = data.get_data(['ssd_0', 'det_0','epq_mask'], prodr)
        self.phivals = data.get_data(['ssd_0', 'det_0','epq_mask'], prodphi)
        self.zvals = data.get_data(['ssd_0', 'det_0','epq_mask'], prodz)
    def init_hist(self):
        binr = np.linspace(0, 3, 4)
        binphi = np.linspace(0, 8, 9)
        binz = np.arange(1, max(self.zvals), 1)
        self.Hist, edges = np.histogramdd([self.rvals, self.phivals, self.zvals], bins=[binr, binphi, binz])
        self.binr, self.binphi, self.binz = edges
        print(binz)
    def plot(self):
        # for polar presentation
        phiedges_rad = np.linspace(0, 2 * np.pi, 9)
        # for cutting off the egdes
        redges_full = np.array([0, 1, 2, 3.5])
        # setting up the plot
        self.fig = pylab.figure()
        ax = pylab.subplot(111, projection='polar')
        ax.set_ylim(0, 2.8)
        ax.set_yticks([])
        ax.set_theta_direction(-1)
        ax.set_theta_zero_location('N')
        ax.set_xticks([x + (2 * np.pi / 16.) for x in np.linspace(0, 2 * np.pi, 8, endpoint=False)])
        ax.set_xticklabels([str(i) for i in np.arange(1, 9, 1)])
        ### Bar for z coordinate:
        ax_bar = pylab.axes([0.05, 0.94, 0.9, 0.02])
        self.init_bar(ax_bar,self.prodz)
        ax_bar.set_xlim(min(self.binz), max(self.binz))
        ax_bar.set_ylim(0, 1)
        self.bar_dot = ax_bar.plot([min(self.binz)], [0.5], linestyle="None", marker="o", markersize=6)
        colormap = pylab.cm.get_cmap("jet")
        # ATTENTION angular coordinate goes first!
        # colorbar range relative over all z-steps:
        if self.scale == 'overall':
            self.Quadmesh = ax.pcolormesh(phiedges_rad, redges_full, self.Hist[:, :, 0], cmap=colormap, vmin = np.min(self.Hist[self.Hist>0]), vmax = np.max(self.Hist))
        elif self.scale == 'onestep':
            # colorbar range relative only to current values in one z-step:
            self.Quadmesh = ax.pcolormesh(phiedges_rad, redges_full, self.Hist[:, :, 0], cmap=colormap)
        else:
            print('scale must be either "overall" or "onestep" (default)')
        colorbar = pylab.colorbar(self.Quadmesh, ax=ax)
    def init_bar(self,ax,prodz):
        ax.xaxis.set_ticks_position("top")
        for tick in ax.get_xticklabels():
            tick.set_fontsize(9)
        ax.set_xlabel(str(self.prodz),size=9)
        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_visible(False)
            tick.set_visible(False)
    def keypressfcn(self,event):
        if event.key == "8":
            self.Splay = True
        elif event.key == "2":
            # stop animation
            self.Splay = False
        elif event.key == "4":
            self.Z_N -= 1
        elif event.key == "6":
            self.Z_N += 1
    def animate(self,i):
        if self.Splay:
            self.Z_N += 1
        self.Z_N = self.Z_N % (len(self.binz) - 1) #for when Z_N has reached the end -> starting with 0 again
        self.bar_dot[0].set_data(self.Z_N, [0.5]) #update dot
        data = self.Hist[:, :, self.Z_N]
        print(data)
        if self.scale == "onestep":
            # update range of colourbar
            self.Quadmesh.set_clim(vmin=np.min(data), vmax=np.max(data))
        self.Quadmesh.set_array(data.ravel())   #update histogram
    def animate_polar(self):
        # main function for polar animation
        self.init_hist()
        self.plot()
        self.Splay = True
        self.Z_N = -1
        C_ID = self.fig.canvas.mpl_connect('key_press_event', self.keypressfcn)
        ani = FuncAnimation(self.fig, self.animate, interval=100, frames=self.zvals.shape[0] - 1, blit=False)
        pylab.show()
        # return is required for successful animation
        return ani
    def sync_aa(self):
        path = '/home/asterix/fischer/ulysses/swics/ulysses_daily_heliocentric_data_1990-2009.txt'
        fin = open(path,'r')


def trajectory(data):
    '''
    Tries to plot aspect angle versus D90 and the trajectory in a fancy way at the same time
    '''
    try:
        aa = data.get_data([],'aa')
        d90 = data.get_data([], 'd90')
        fig = pylab.figure()
        ax = pylab.subplot(111)
        ax.set_position([0.05, 0.80, 0.9, 0.15])
        ax.set_xlim(0,20*365)
        ax.set_xticks(np.arange(365,19*365+1,365))
        ax.set_xticklabels(np.arange(1991,2010,1))
        ax.set_ylim(0,90)
        ax.set_ylabel('Aspect Angle / deg')
        ax.plot(d90,aa,marker='o',markersize='1',linestyle='none')
    except:
        print('That did not work: You need to synchronise trajectory data first!')


def summary_traj(data):
    '''
    Plots all trajectory data products versus D90
    '''
    if True: #try:
        aa = data.get_data([], 'aa')[::200]
        d90 = data.get_data([], 'd90')[::200]
        r = data.get_data([], 'r')[::200]
        lat = data.get_data([], 'lat')[::200]
        RA = data.get_data([], 'ra')[::200]
        Dec = data.get_data([], 'dec')[::200]
        long = data.get_data([], 'long')[::200]
        fig = pylab.figure()
        ax = pylab.subplot(111)
        ax.set_position([0.05, 0.05, 0.9, 0.9])
        ax.set_xlim(0, 6 * 365)
        ax.set_xticks(np.arange(365, 8 * 365 + 1, 365))
        ax.set_xticklabels(np.arange(1991, 1999, 1))
        ax.set_ylim(-100,500)
        ax.set_ylabel('deg')
        ax2 = ax.twinx()
        ax2.set_ylim(-5,10)
        ax2.plot(d90, r, marker='o', markersize='1', linestyle='none', label='R', c='crimson')
        ax2.set_ylabel('R / AU')
        ax2.tick_params('y', colors='crimson')
        # ax.plot(d90, aa, marker='o', markersize='1', linestyle='none', label='aa')
        ax.plot(d90, lat, marker='o', markersize='1', linestyle='none', label='Lat', c='olive')
        ax.plot(d90, long, marker='o', markersize='1', linestyle='none', label='Long', c='cadetblue')
        ax.plot(d90, Dec, marker='o', markersize='1', linestyle='none', label='DEC', c='y')
        ax.plot(d90, RA, marker='o', markersize='1', linestyle='none', label='RA', c='powderblue')
        fig.tight_layout()
        lines, labels = ax.get_legend_handles_labels()
        lines2, labels2 = ax2.get_legend_handles_labels()
        ax2.legend(lines + lines2, labels + labels2, loc=0)
    # except:
    #     print('Some kind of error!')

