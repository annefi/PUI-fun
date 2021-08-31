import numpy as np
import datetime
from Ulysses.Trajectory.ul_coordinates_utils import *
from Ulysses.Trajectory.spice_loader import *

from mpl_toolkits.mplot3d import Axes3D
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d

import matplotlib
matplotlib.rcParams['lines.linewidth'] = 0.5

import matplotlib.pyplot as plt

plt.rc('text.latex', preamble=r'\usepackage{amsmath} \usepackage{wasysym}')

# Constants:
km_per_AU = 1.495979e8


class Plot_3d():
    """ blabla
    """
    def __init__(self, epoch = None):
        """
        Sets up the 3D Plot

        :param epoch: Sets the epoch for which the equatorial system is drawn (as the First Point of Aries slowly
        changes its location the relative offset between equatorial system and Earth ecliptic system changes,
        too. Note, that it's actually the ecliptic system that changes but that is is chosen to be the fixed system
        aligning with the xyz-axes in the plot)
        """
        self.epoch = datetime.datetime(2000,1,1,12) if epoch == None else epoch
        fig = plt.figure(figsize=(12, 10))
        ax = fig.add_subplot(111, projection='3d')
        fig.canvas.set_window_title('Test')
        ax.set_xlim(-1.8, 1.8)
        ax.set_ylim(-1.8, 1.8)
        ax.set_zlim(-1.8, 1.8)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
        ax.scatter(0, 0, 0, 'o', s = 50, color="gold")  # Sun

        # WOFÜR das Folgende? Hab ich das schon ersetzt?
        # delta_t = (TF[1] - TF[0]).total_seconds()  # auxiliary time delta for setting up self.times
        # self.times = [TF[0] + datetime.timedelta(seconds=t) for t in range(0, int(delta_t + DT), DT)]
        # paras_Earth = ['r_earth', 'lat_earth', 'long_earth']
        # self.data = {p:[] for p in paras_Earth}
        # for t in self.times:
        #     [R, lat, long] = locateBody(EARTH, t, self.RF)
        #     self.data['r_earth'].append(R)
        #     self.data['lat_earth'].append(lat)
        #     self.data['long_earth'].append(long)
        # x,y,z = spher2cart(np.array([self.data['r_earth'],self.data['lat_earth'],self.data['long_earth']]).T).T
        # ax.plot(x,y,z, linewidth = 1)
        # fill_between_3d(ax,[self.data['r_earth'],self.data['lat_earth'],self.data['long_earth']],[0,0,0],
        # mode = 1, c="C0")
        # ax.plot([x,x],[y,y],[z,z], 'o', color = 'r')
        self.ax = ax
        self.draw_ecliptic()
        self.draw_solar_equator()

    def plot_point(self, coords: np.ndarray, cs, epoch):
        """

        :param coords: [r,lat,long] of the (trajectory) point in °
        :param cs: specifies reference system in which coords are given [HCI, ECLIPJ2000]
        :param epoch:
        :return:
        """
        epoch = datetime.datetime(2000, 1, 1, 12)
        if coords.ndim == 1:
            if cs == HCI:
                xyz = self.transform2eq(coords, epoch, cart = False)
            elif cs == ECLIPJ2000:
                xyz = spher2cart(coords)
            self.ax.scatter(*xyz, c = 'red')
        if coords.ndim == 2:
            if cs == HCI:
                xyz = self.transform2eq(coords, epoch, cart = False)
            elif cs == ECLIPJ2000:
                xyz = spher2cart(coords)
            self.ax.scatter(*xyz.T, c='red')


    def draw_eclip_sys(self):
        y_ax = self.ax.plot(*np.array([[0,1.,0],[0,0,0]]).T, c="steelblue", linestyle = '--', linewidth = 1.2,
                            alpha = 0.8)
        z_ax = self.ax.plot(*np.array([[0, 0, 1.], [0, 0, 0]]).T,c="steelblue", linestyle = '--', linewidth = 1.2)
        #y_ax = Arrow3D(np.array([0,1.,0]), color="C0", arrowstyle = '->', linestyle = '--')
        #z_ax = Arrow3D(np.array([0,0,1.]), color="C0", arrowstyle = '->', linestyle = ':')
        #self.ax.add_artist(y_ax)
        #self.ax.add_artist(z_ax)
        self.draw_fpoa()
        self.draw_ecliptic()

    def draw_equ_sys(self, epoch):
        x_ax = self.transform2eq(np.array([1.5, 0., 0.]), epoch)
        y_ax = self.transform2eq(np.array([0., 1.5, 0.]), epoch)
        z_ax = self.transform2eq(np.array([0., 0., 1.5]), epoch)
        x_arr = Arrow3D(x_ax,color="C1", arrowstyle = '->')
        y_arr = Arrow3D(y_ax, color="C1", arrowstyle='->')
        z_arr = Arrow3D(z_ax, color="C1", arrowstyle='->')
        self.ax.add_artist(x_arr)
        self.ax.add_artist(y_arr)
        self.ax.add_artist(z_arr)
        self.ax.text(z_ax[0],z_ax[1],z_ax[2], r'$\boldsymbol{\omega}$', color='C1', fontsize='large', \
                                                                                                    usetex=True)
        self.draw_solar_equator(epoch, circ = True, area = False)

    def transform2eq(self, vec: np.ndarray, epoch, cart = True):
        """ Active transformation of a vector from the "basic" ecliptic system to the solar equatorial system

        :param vec:
        :param epoch:
        :param cart: vec should be given in cartesian coordinates if True
        :return:
        """
        if cart:
            vec = cart2spher(vec)
        if vec.ndim == 1:
            vec_eq = hg_to_hc(vec, ang_ascnode = calc_delta(epoch)) # strange but true: active transformation
        if vec.ndim == 2:
            vec_eq = []
            for v in vec:
                vec_eq.append(hg_to_hc(v, ang_ascnode = calc_delta(epoch)))
        return spher2cart(np.array(vec_eq))

    def draw_fpoa(self):
        """ Draw the axis toward first point of aries

        This axis defines the x-axis of ecliptic coordinate systems and always aligns with the x.axis in this 3d plot.
        In reality it changes with time while the ascending node is relatively stable in space. The time dependent offset Delta is realised
        when drawing the equatorial system

        :param ax:
        :return:
        """
        self.fpoa = Arrow3D(np.array([[0,1.5],[0,0],[0,0]]), lw = 1,color="C0",
                            arrowstyle="-|>,head_length=0.3,head_width=0.1")
        self.ax.add_artist(self.fpoa)
        self.ax.text(1.5,0,0, r'$\textbf{{\LARGE \aries}}$', color ='C0',fontsize = 'large', usetex = True)


    def draw_ecliptic(self, circ = True, area = True):
        """ Draws the Earth ecliptic plane as an elliptical slice into the plot.

        The ecliptic plane aligns with the x-y plane as the ecliptic reference frame is the basic frame for the plot

        :param circ: Draws a line for Earth's position in 2000 if True
        :param area: Fills the area within the line if True
        """
        t1 = datetime.datetime(2000,1,1)
        t2 = datetime.datetime(2000,12,31)
        DT = 60 * 60 * 24# 12 hours in seconds
        times = timerange(t1,t2,DT)
        paras_Earth = ['x_earth', 'y_earth', 'z_earth']
        earth_data = {p: [] for p in paras_Earth}
        for t in times:
            [x,y,z] = EARTH.position(time = t, relative_to = SUN, reference_frame = ECLIPJ2000)
            earth_data['x_earth'].append(x/km_per_AU)
            earth_data['y_earth'].append(y/km_per_AU)
            earth_data['z_earth'].append(z/km_per_AU)
        earth_data['x_earth'].append(earth_data['x_earth'][0])
        earth_data['y_earth'].append(earth_data['y_earth'][0])
        earth_data['z_earth'].append(earth_data['z_earth'][0])
        if circ:
            self.ax.plot(earth_data['x_earth'], earth_data['y_earth'], earth_data['z_earth'])
        if area:
            fill_between_3d(self.ax,*[earth_data['x_earth'],earth_data['y_earth'],earth_data['z_earth']],
                            *np.zeros(np.shape([earth_data['x_earth'],earth_data['y_earth'],earth_data['z_earth']])),
                            mode = 1, c="C0",
                            alpha = 0.05)
        self.draw_fpoa()


    def draw_solar_equator(self, circ = True, area = True):
        """ Draws the solar equator as a slice into the plot

        The solar equator is tilted by 7.25° against the Earth ecliptic plane

        :param circ: Draws a circle @1AU in the solar equatorial plane if True
        :param area: Fills the area within the circle if True
        """
        x = []
        y = []
        z = []
        for ang in range(0,360,1):
            vec_eq = self.transform2eq(np.array([1.,0.,ang]), self.epoch, cart = False)
            x.append(vec_eq[0])
            y.append(vec_eq[1])
            z.append(vec_eq[2])
        if circ:
            self.ax.plot(x,y,z, color='C1')
        if area:
            fill_between_3d(self.ax,*[x,y,z],*np.zeros(np.shape([x,y,z])), mode = 1, c="C1", alpha = 0.05)

    def draw_axis(self, end: np.ndarray, main: bool = False):
        if main:
            pass
        else:
            self.ax.plot()


class Arrow3D(FancyArrowPatch):
    """ Inherited from matplotlib.patches.FancyArrowPatch
    """

    def __init__(self, xyz, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), mutation_scale = 20, *args, **kwargs)
        if xyz.ndim == 1:
            self._verts3d = [0,xyz[0]], [0,xyz[1]], [0,xyz[2]]
        if xyz.ndim == 2:
            self._verts3d = xyz[0], xyz[1], xyz[2]

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)


def calc_delta(epoch):
    # longitude of the ascending node of the solar equator on the ecliptic: Delta = 75°.76+1°.397T0 with T0 Julian
    # centuries from J2000
    jc_per_days = 36525.
    dt = epoch - datetime.datetime(2000,1,1,12)
    T0 = dt.total_seconds()/ (24. * 60. * 60.) / jc_per_days
    ang_ascnode = 75.76 + 1.397 * T0
    return ang_ascnode

