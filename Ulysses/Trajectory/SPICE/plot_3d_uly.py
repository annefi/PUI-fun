from spice_ulysses_new_inheri import *

from mpl_toolkits.mplot3d import Axes3D
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d

import matplotlib
matplotlib.rcParams['lines.linewidth'] = 0.5

#import matplotlib.pyplot as plt
#plt.rcParams['text.latex.preamble'] = r"\usepackage{wasysym} \usepackage{amsmath}"


# import matplotlib.pyplot as plt
# plt.rcParams.update({
#     "text.usetex": True,
#     "font.family": "sans-serif",
#     "font.sans-serif": ["Helvetica"]})

import matplotlib.pyplot as plt

#plt.rc('text', usetex=True)
plt.rc('text.latex', preamble=r'\usepackage{amsmath} \usepackage{wasysym}')



class Plot_3d():
    """ blabla
    """
    def __init__(self):
        fig = plt.figure(figsize=(10, 10))
        ax = fig.add_subplot(111, projection='3d')
        fig.canvas.set_window_title('Test')
        ax.set_xlim(-2., 2.)
        ax.set_ylim(-2., 2.)
        ax.set_zlim(-2., 2.)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
        ax.scatter(0, 0, 0, 'o', s = 50, color="gold")  # Sun
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

    def draw_eclip_sys(self):

        y_ax = Arrow3D(np.array([0,2,0]), color="goldenrod", arrowstyle = '->')
        z_ax = Arrow3D(np.array([0,0,2]), color="goldenrod", arrowstyle = '->')
        self.ax.add_artist(y_ax)
        self.ax.add_artist(z_ax)
        self.draw_fpoa()
        self.draw_ecliptic()

    def draw_equ_sys(self, epoch):
        x_ax = spher2cart(np.array([2.,0, calc_delta(epoch)]))
        print(x_ax[2])
        y_ax = spher2cart(np.array([2.,7.25,90.+calc_delta(epoch)]))
        print(y_ax)
        x_arr = Arrow3D(x_ax,color="green", arrowstyle = '->')
        y_arr = Arrow3D(y_ax, color="green", arrowstyle='->')
        self.ax.add_artist(x_arr)
        self.ax.add_artist(y_arr)

    def draw_fpoa(self):
        """draw the axis toward first point of aries

        This axis defines the x-axis of ecliptic coordinate systems and always aligns with the x.axis in this 3d plot.
        In reality it changes with time while the ascending node is relatively stable in space. The time dependent offset Delta is realised
        when drawing the equatorial system

        :param ax:
        :return:
        """
        self.fpoa = Arrow3D(np.array([[0,2],[0,0],[0,0]]), lw = 1,color="goldenrod",
                            arrowstyle="-|>,head_length=0.3,head_width=0.1")
        self.ax.add_artist(self.fpoa)
        self.ax.text(2.,0,0, r'$\textbf{{\LARGE \aries}}$', color ='goldenrod',fontsize = 'large', usetex = True)

    def draw_ecliptic(self, circ = True, area = True):
        t1 = datetime.datetime(2000,1,1)
        t2 = datetime.datetime(2000,12,31)
        DT = 60 * 60 * 24# 12 hours in seconds
        times = timerange(t1,t2,DT)
        paras_Earth = ['r_earth', 'lat_earth', 'long_earth']
        earth_data = {p: [] for p in paras_Earth}
        for t in times:
            [R, lat, long] = locateBody(EARTH, t, ECLIPJ2000)
            earth_data['r_earth'].append(R)
            earth_data['lat_earth'].append(lat)
            earth_data['long_earth'].append(long)
        earth_data['r_earth'].append(earth_data['r_earth'][0])
        earth_data['lat_earth'].append(earth_data['lat_earth'][0])
        earth_data['long_earth'].append(earth_data['long_earth'][0])
        x, y, z = spher2cart(np.array([earth_data['r_earth'], earth_data['lat_earth'], earth_data['long_earth']]).T).T
        if circ:
            self.ax.plot(x,y,z)
        if area:
            fill_between_3d(self.ax,*[x,y,z],*np.zeros(np.shape([x,y,z])), mode = 1, c="C0", alpha = 0.05)

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
    print(T0)
    ang_ascnode = 75.76 + 1.397 * T0
    return ang_ascnode