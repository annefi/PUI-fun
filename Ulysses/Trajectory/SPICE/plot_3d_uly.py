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
    """ Class for plotting 3D trajectory data
    """

    def __init__(self, epoch = None, ax = None):
        """
        Sets up the 3D Plot

        :param epoch: Sets the epoch for which the equatorial system is drawn (The 1st Point of Aries slowly
        changes its location and so the relative offset between equatorial system and Earth ecliptic system changes,
        too. Note, that it's actually the ecliptic system that changes but that it is chosen to be the fixed system
        aligning with the xyz-axes in the plot)
        """
        print(ax)
        self.epoch = datetime.datetime(2000, 1, 1, 12) if epoch == None else epoch
        if ax == None:
            fig = plt.figure(figsize=(12, 10))
            ax = fig.add_subplot(111, projection='3d')
            fig.canvas.set_window_title('Test')
            ax.set_xlim(-5.1, 1.8)
            ax.set_ylim(-1.5, 1.8)
            ax.set_zlim(-1.8, 1.8)
            ax.set_xlabel("x/AU")
            ax.set_ylabel("y/AU")
            ax.set_zlabel("z/AU")
            ax.scatter(0, 0, 0, 'o', s=50, color="gold")  # Sun
            self.ax = ax
            self.draw_eclip_sys()
            self.draw_equ_sys()
        else:
            self.ax = ax

    def plot_point(self, coords: np.ndarray, cs = None, epoch = None, col = None):
        """ Plots a single point or a series of points into the plot

        :param coords: np.array [r,lat,long] of the (trajectory) point in ° (1D or 2D numpy array)
        :param cs: Specifies reference system in which coords are given [HCI, ECLIPJ2000]. Default is ECLIPJ2000 (Earth
        ecliptic)
        :param epoch: datetime object for specifying the logitudinal offset between ecliptic and solar
        equatorial coordinate systems
        """
        if cs == None:
            cs = ECLIPJ2000
        if epoch == None:
            epoch = self.epoch
        if col == None:
            col = 'red'
        if coords.ndim == 1:
            if cs == HCI:
                xyz = self.transform2eq(coords, cart = False)
            elif cs == ECLIPJ2000:
                xyz = spher2cart(coords)
            else:
                sys.exit('Parameter cs has to be either HCI or ECLIPJ2000')
            self.ax.scatter(*xyz, s = 5., c = col)
        if coords.ndim == 2:
            if cs == HCI:
                xyz = self.transform2eq(coords, cart = False)
            elif cs == ECLIPJ2000:
                xyz = spher2cart(coords)
            self.ax.scatter(*xyz.T, s = 5, c= col)
        return self.ax

    def draw_eclip_sys(self):
        """ Draws the Earth ecliptic system into the plot

        This includes the ecliptic plane (aligning with the x-y plane of the plot), the x-axis pointing towards the
        1st Point of Aries, the y- and z-axis.
        """
        x_ax = self.ax.plot(*np.array([[4., 0., 0], [0, 0, 0]]).T, c="steelblue", linestyle='--', linewidth=1.2,
                            alpha=0.8)
        y_ax = self.ax.plot(*np.array([[0, 1., 0], [0, 0, 0]]).T, c="steelblue", linestyle='--', linewidth=1.2,
                            alpha=0.8)
        z_ax = self.ax.plot(*np.array([[0, 0, 1.], [0, 0, 0]]).T, c="steelblue", linestyle='--', linewidth=1.2)
        #self.draw_fpoa()
        self.draw_ecliptic()

    def draw_equ_sys(self):
        """ Draws the solar equatorial system into to plot

        This includes the Sun equatorial plane, the x-axis (aligning with the line of nodes between the eq. plane and
        the Earth ecliptic plane), the y-axis and the z-axis (labelled as omega and aligning with the Sun's spin axis)
        """
        x_ax_long = self.transform2eq(np.array([4., 0., 0.]))
        self.ax.plot(*np.array([x_ax_long, [0, 0, 0]]).T, c='C1', linestyle='--', linewidth=1.2,
                            alpha=0.8)
        x_ax = self.transform2eq(np.array([1.5, 0., 0.]))
        y_ax = self.transform2eq(np.array([0., 1.5, 0.]))
        z_ax = self.transform2eq(np.array([0., 0., 1.5]))
        x_arr = Arrow3D(x_ax, color="C1", arrowstyle='->')
        y_arr = Arrow3D(y_ax, color="C1", arrowstyle='->')
        z_arr = Arrow3D(z_ax, color="C1", arrowstyle='->')
        self.ax.add_artist(x_arr)
        self.ax.add_artist(y_arr)
        self.ax.add_artist(z_arr)
        self.ax.text(z_ax[0], z_ax[1], z_ax[2], r'$\boldsymbol{\omega}$', color='C1', fontsize='large', \
                     usetex=True)
        self.draw_solar_equator(circ=True, area=False)

    def transform2eq(self, vec: np.ndarray, cart=True, epoch=None):
        """ Active transformation of a vector from the "basic" ecliptic system to the solar equatorial system

        :param vec: 3-dimensional vector in cartesian components (1D or 2D numpy array)
        :param cart: Has to be set to False if vec is given in spherical coordinate system
        :param epoch: datetime object giving the epoch of reference (that determines the offset between the two
        systems' x-axes)
        :return: transformed vector(s) in cartesian coordinates as a numpy array
        :Example:
            array([0.98, 0., 0.17]) -> array([0.26, 0.95, 0.17])
            (which is array([1., 10., 0.]) -> array([1., 9.92, 74.49]) in spherical coordinates)

        """
        if epoch == None:
            epoch = self.epoch
        if cart == True:
            vec = cart2spher(vec)
        if vec.ndim == 1:
            vec_eq = hg_to_hc(vec, ang_ascnode=calc_delta(epoch))  # strange but true: active transformation
        if vec.ndim == 2:
            vec_eq = []
            for v in vec:
                vec_eq.append(hg_to_hc(v, ang_ascnode=calc_delta(epoch)))
        return spher2cart(np.array(vec_eq))

    def draw_fpoa(self):
        """ Draws the axis toward first point of aries

        This axis defines the x-axis of ecliptic coordinate systems and always aligns with the x.axis in this 3D plot.
        In reality it changes with time while the ascending node is relatively stable in space. The time dependent
        offset Delta is realised
        when drawing the equatorial system
        """
        self.fpoa = Arrow3D(np.array([[0, 1.5], [0, 0], [0, 0]]), lw=1, color="C0",
                            arrowstyle="-|>,head_length=0.3,head_width=0.1")
        self.ax.add_artist(self.fpoa)
        self.ax.text(1.5, 0, 0, r'$\textbf{{\LARGE \aries}}$', color='C0', fontsize='large', usetex=True)

    def draw_ecliptic(self, circ=True, area=True):
        """ Draws the Earth ecliptic plane as an elliptical slice into the plot.

        The ecliptic plane aligns with the x-y plane as the ecliptic reference frame is the basic frame for the plot

        :param circ: Draws a line for Earth's position in 2000 if True
        :param area: Fills the area within the line if True
        """
        t1 = datetime.datetime(2000, 1, 1)
        t2 = datetime.datetime(2000, 12, 31)
        DT = 60 * 60 * 24  # 12 hours in seconds
        times = timerange(t1, t2, DT)
        paras_Earth = ['x_earth', 'y_earth', 'z_earth']
        earth_data = {p: [] for p in paras_Earth}
        for t in times:
            [x, y, z] = EARTH.position(time=t, relative_to=SUN, reference_frame=ECLIPJ2000)
            earth_data['x_earth'].append(x / km_per_AU)
            earth_data['y_earth'].append(y / km_per_AU)
            earth_data['z_earth'].append(z / km_per_AU)
        earth_data['x_earth'].append(earth_data['x_earth'][0])
        earth_data['y_earth'].append(earth_data['y_earth'][0])
        earth_data['z_earth'].append(earth_data['z_earth'][0])
        if circ:
            self.ax.plot(earth_data['x_earth'], earth_data['y_earth'], earth_data['z_earth'])
        if area:
            fill_between_3d(self.ax, *[earth_data['x_earth'], earth_data['y_earth'], earth_data['z_earth']],
                            *np.zeros(np.shape([earth_data['x_earth'], earth_data['y_earth'], earth_data['z_earth']])),
                            mode=1, c="C0",
                            alpha=0.05)
        #self.draw_fpoa()

    def draw_solar_equator(self, circ=True, area=True):
        """ Draws the solar equator as a slice into the plot

        The solar equator is tilted by 7.25° against the Earth ecliptic plane

        :param circ: Draws a circle @1AU in the solar equatorial plane if True
        :param area: Fills the area within the circle if True
        """
        x = []
        y = []
        z = []
        for ang in range(0, 360, 1):
            vec_eq = self.transform2eq(np.array([1., 0., ang]), cart=False)
            x.append(vec_eq[0])
            y.append(vec_eq[1])
            z.append(vec_eq[2])
        if circ:
            self.ax.plot(x, y, z, color='C1')
        if area:
            fill_between_3d(self.ax, *[x, y, z], *np.zeros(np.shape([x, y, z])), mode=1, c="C1", alpha=0.05)


class Arrow3D(FancyArrowPatch):
    """ Inherits from matplotlib.patches.FancyArrowPatch
    """
    def __init__(self, xyz, *args, **kwargs):
        """ Draws an 3D arrow in a plot with 3D-projection
        :param xyz: 2D-np.array in format [[x_start,x_end],[y_start,y_end],[z_start,z_end]]
        :param args: See FancyArrowPatch
        :Example:

        arrow = Arrow3D(np.array([[0,1.5],[0,0],[0,0]]), lw = 1,color="k", arrowstyle="-|>,head_length=0.3,
                                                                                        head_width=0.1")
        ax.add_artist(arrow)
        """
        FancyArrowPatch.__init__(self, (0, 0), (0, 0), mutation_scale=20, *args, **kwargs)
        if xyz.ndim == 1:
            self._verts3d = [0, xyz[0]], [0, xyz[1]], [0, xyz[2]]
        if xyz.ndim == 2:
            self._verts3d = xyz[0], xyz[1], xyz[2]

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0], ys[0]), (xs[1], ys[1]))
        FancyArrowPatch.draw(self, renderer)



