from spice_ulysses_new_inheri import *

from mpl_toolkits.mplot3d import Axes3D
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d

import matplotlib
matplotlib.rcParams['lines.linewidth'] = 0.5

import matplotlib.pyplot as plt
plt.rc('text.latex', preamble=r'\usepackage{amsmath} \usepackage{wasysym}')

params = {'text.latex.preamble' : [r'\usepackage{marvosym}}', r'\usepackage{amsmath}']}
plt.rcParams.update(params)



def plot_3d(T: Type[TrajectoryUlysses], ax = None):
    """ blabla
    """
    if ax == None:
        fig = plt.figure(figsize=(10, 10))
        ax = fig.add_subplot(111, projection='3d')
        fig.canvas.set_window_title('Test')
        ax.set_xlim(-2., 2.)
        ax.set_ylim(-2., 2.)
        ax.set_zlim(-2., 2.)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
    ax.scatter(0, 0, 0, 'o', color="gold")  # Sun
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
    return ax

def draw_fpoa(ax):
    """draw the axis toward first point of aries
    
    This axis defines the x-axis of ecliptic coordinate systems and aligns with the x.axis in this 3d plot. Changes 
    with time, thus needs to be given with an epoch [Todo]. Given for J2000 for now...
    
    :param ax: 
    :return: 
    """
    #ax.plot([0,2],[0,0],[0,0], color = 'r')
    a = Arrow3D([0,2],[0,0],[0,0], mutation_scale=20, lw = 1,color="r", arrowstyle="-|>,head_length=0.3,"
                                                                                   "head_width=0.1")
    ax.add_artist(a)
    ax.text(2.1,0,0, r'$\text{a}$', color ='r')

def draw_ecliptic(ax, circ = True, area = True):
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
        ax.plot(x,y,z)
    if area:
        fill_between_3d(ax,*[x,y,z],*np.zeros(np.shape([x,y,z])), mode = 1, c="C0", alpha = 0.05)




class Arrow3D(FancyArrowPatch):
    """ Inherited from matplotlib.patches.FancyArrowPatch
    """
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)