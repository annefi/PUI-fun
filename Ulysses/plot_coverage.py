
import matplotlib
import matplotlib.pyplot as plt
from DataLoader.uswiutils import getvelocity
from custom_colours import lighten_color
import matplotlib.colors as colors
import matplotlib.ticker as ticker
from numpy import *
from pylib import dbData
import sys
from DataLoader.uswipha import uswipha
from mpl_toolkits.axes_grid1 import make_axes_locatable
from matplotlib.patches import Arc

matplotlib.rcParams.update({'font.size': 12,
                            'xtick.major.size': 8,
                            'axes.labelsize': 14,
                            'xtick.major.width': 1.5,
                            'xtick.minor.size': 5,
                            'xtick.minor.width': 1,
                            'ytick.major.size': 8,
                            'ytick.major.width': 1.5,
                            'ytick.minor.size': 5,
                            'ytick.minor.width': 1,
                            'xtick.direction': 'inout',
                            'ytick.direction': 'out',
                            'figure.subplot.left':0.1,
                            'figure.subplot.bottom': 0.1,
                            'figure.subplot.right': 0.93,
                            'figure.subplot.top': 0.94,
                            'figure.figsize': (4.5,4.5)})


# define style of textboxes
props = dict(boxstyle='round', facecolor='#D3D3D3', edgecolor = 'k', alpha=0.8, pad = 0.2)

class PlotCov():
    '''


    '''
    def __init__(self, vsw = 700):
        self.vsw = vsw

        fig, self.ax = plt.subplots()
        self.ax.set_xlim([-1,2.3])
        self.ax.set_ylim([-2.3,2.3])
        self.ax.set_xticks([0,1,2])
        self.ax.set_yticks([-2,-1,0, 1, 2])
        self.ax.annotate(r'$\mathrm{w_{sw,R}}$', xy=(2.2, -0.3), ha='left', va='top', fontsize = 14)

        self.ax.text(1.1, 0, 'vsw = %s km/s' % vsw, bbox=props, transform=self.ax.transAxes, ha='right')

        #self.ax.set_xlabel(r'$\mathrm{w_{sw,R}}$')
        self.ax.set_ylabel(r'$\mathrm{w_{sw,T}}$')




        # spine placement data centered
        self.ax.spines['left'].set_position(('data', -1.0))
        self.ax.spines['bottom'].set_position(('data', 0.0))
        self.ax.spines['right'].set_color('none')
        self.ax.spines['top'].set_color('none')
        self.ax.set_aspect('equal')

    def draw_circ_arc(self, R):
        pac = Arc([-1, 0], 2*R, 2*R, angle= -90, theta1=0, theta2=180, alpha = 0.5)
        self.ax.add_patch(pac)

    def draw_shell(self, R = 1):
        pac = Arc([0, 0], 2 *R, 2*R, angle=0, theta1=0, theta2=360, alpha = 0.3, color = 'blue', lw = 5)
        self.ax.add_patch(pac)

    def get_R(self, step):
        vel = getvelocity(mass = 4, charge = 1,step = step, frac = 1.)
        w_sc = vel/self.vsw
        w_sw = w_sc -1
        return w_sw

    def plot_epq(self):
        for step in range(0,17):
            r = self.get_R(step)
            self.draw_circ_arc(R=r)


    # def fill_cov(self, R = 2):
    #     x = arange(-1.0, 2, 0.01)
    #     y = arange(-2,2-0.01)
    #     pac = Arc([-1, 0], 2*R, 2*R, angle= -90, theta1=0, theta2=180, alpha = 0.5)
    #     a = self.ax.add_patch(pac)
    #     pac2 = Arc([-1, 0], R, R, angle= -90, theta1=0, theta2=180, alpha = 0.5)
    #     b = self.ax.add_patch(pac2)
    #
    #     verts = pac.get_path().vertices
    #     trans = pac.get_patch_transform()
    #     points = trans.transform(verts)
    #
    #     verts2 = pac2.get_path().vertices
    #     trans2 = pac2.get_patch_transform()
    #     points2 = trans2.transform(verts2)
    #
    # def draw_cov(self, R=1):
    #         pac = Arc([-1, 0], 2 * R, 2 * R, angle=-90, theta1=0, theta2=180, alpha=0.1, lw = 100)
    #         self.ax.add_patch(pac)



