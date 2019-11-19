import matplotlib.pyplot as plt
from numpy import *
from numpy import arange, min, max, amin, amax, unique, around
from matplotlib import colors
import matplotlib
from mpl_toolkits.axes_grid1 import make_axes_locatable

from mpl_toolkits.axes_grid1.inset_locator import inset_axes


matplotlib.rcParams.update({'font.size': 12,
                            'axes.labelsize': 14,
                            'xtick.major.size': 8,
                            'xtick.major.width': 1.5,
                            'xtick.minor.size': 5,
                            'xtick.minor.width': 1,
                            'ytick.major.size': 8,
                            'ytick.major.width': 1.5,
                            'ytick.minor.size': 5,
                            'ytick.minor.width': 1,
                            'xtick.direction': 'out',
                            'ytick.direction': 'out',
                            'figure.subplot.left':0.12,
                            'figure.subplot.bottom': 0.1,
                            'figure.subplot.right': 0.84,
                            'figure.subplot.top': 0.88,
                            'figure.figsize': (8,4.5)}) # Achtung anders

# define style of textboxes
props = dict(boxstyle='round', facecolor='#D3D3D3', edgecolor = 'k', alpha=0.8, pad = 0.8)


class WSky():
    '''
    Class for plotting clickable skymap of dist3D instance.
    Mode can be "ps", "norm" or "counts"

    Example of use:

    ***
    wsky = WSky(D, mode = 'norm') (for plotting the norm matrice)
    wsky.init_plot()
    ***

    '''
    def __init__(self, D, color_norm='sg', mode='ps', phirange = [-pi, pi + 0.001],
                 thetarange = [-pi / 2., pi / 2. + 0.001], angstep = 10 * pi / 180., shellstep = 0.1):
        # shift wshellmax to SW frame:
        self.wshellbins = arange(shellstep, (D.wshellmax -1) + 0.0001, shellstep)
        self.D = D
        self.shell = len(self.wshellbins) / 2
        self.color_norm = color_norm
        self.mode = mode
        self.angstep = angstep

        norm_arr, H0 = self.D.calc_skymapspec(phirange = phirange, thetarange = thetarange, angstep = angstep,
                                              shellstep = shellstep)

        self.n = norm_arr

        if mode == 'norm':
            self.unit = 'PSV / ?TODO'
            norm_arr[norm_arr == 0] = -5.
            self.H = norm_arr
        elif mode == 'counts':
            self.unit = 'Counts'
            H0[norm_arr == 0] = -5
            self.H = H0
        elif mode == 'ps':
            self.unit = r'Phase Space Density / $s^3 \, km^{-6}$'
            H0[norm_arr == 0] = -5
            norm_arr[norm_arr == 0] = 1
            self.H = H0 / norm_arr

        # cut out extra high values (at the edges: only few counts) that destroy the colormap:
        for shell in range(len(self.wshellbins)-1):
            for i in range(4):
                    print(self.H[:, :, shell].max())
                    self.H[:, :, shell][self.H[:, :, shell] > (mean(self.H[:, :, shell]) + 3 * std(self.H[:, :,
                                                                                                   shell]))] = 0
                    print(self.H[:, :, shell].max())
                    print(shell)


    def init_plot(self):
        def keypress(event):
            if event.key == 'right':
                self.update_plot(dir='+')
            if event.key == 'left':
                self.update_plot(dir='-')
            plt.show()
            print(self.shell)
            print 'click'

        fig = plt.figure('%s' % self.mode)
        self.ax = plt.subplot(111, projection="mollweide")

        #self.plot_belt()
        fig.canvas.mpl_connect('key_press_event', keypress)
        self.ax.set_xlabel(r'$\varphi \, / \, \degree$')
        self.ax.set_ylabel(r'$\vartheta \, / \, \degree$')
        #self.ax.tick_params(axis='x', colors = 'w')
        #self.ax.tick_params(axis='x', zorder=10)
        self.ax.grid()
        #self.txt_shell = self.ax.text(0.05, 1.05, 'Shell: %s' % self.shell, bbox={"facecolor": "grey", "alpha": 0.4,
                                                       #"pad": 10},transform=self.ax.transAxes)
        self.txt_w = self.ax.text(0.5, 1.15, r'$\mathrm{w_{sw} = [%2.1f, %2.1f]}$' % (self.wshellbins[self.shell],
                   self.wshellbins[self.shell + 1]), bbox=props, transform=self.ax.transAxes, ha = 'center',
                                  va = 'bottom')
        self.plot(shell=self.shell)

        axins = inset_axes(self.ax,
                           width="4%",  # width = 5% of parent_bbox width
                           height="99%",  # height : 50%
                           loc='center left',
                           bbox_to_anchor=(1.05, -.0, 1, 1),
                           bbox_transform=self.ax.transAxes,
                           borderpad=0,
                           )


        self.cb = plt.colorbar(self.Quadmesh, cax = axins)
        self.cb.set_label("%s" % (self.unit), labelpad=10)
        self.cb.formatter.set_powerlimits((0, 0))  # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh)  # force updating the colorbar


    def plot_belt(self):
        phival = arange(-pi -1,pi +1)
        thetaval = zeros(shape(phival))
        thetaval[thetaval == 0] = 7.5/180.*pi
        self.ax.plot(phival, thetaval, lw = 10, alpha = 0.2, color = 'w', zorder = 1)

    def plot(self, shell):
        # bins that are shown in the plot. Have to have the dimension of the histogram.
        phibins = arange(-pi, pi + 0.001, self.angstep)
        thetabins = arange(-pi/2., pi/2. + 0.0001, self.angstep)
        colormap = plt.cm.get_cmap("viridis")
        if self.color_norm == 'all':
            vmin = 0
            vmax = amax(self.H)
            self.Quadmesh = self.ax.pcolormesh(phibins, thetabins, self.H[:, :, shell].T, cmap=colormap, vmin=vmin,
                                               vmax=vmax)
            colormap.set_under(color='#D3D3D3')
            #self.txt_shell.set_text('Shell: %s' % self.shell)
            self.txt_w.set_text(r'$w = [%2.1f, %2.1f]$' % (self.wshellbins[self.shell], self.wshellbins[
                self.shell + 1]))

        if self.color_norm == 'sg':
            # set limits for colormap:
            vmin = 0
            vmax = amax(self.H[:, :, shell])
            if vmax <= 0:
                vmax = 0.0001
            self.Quadmesh = self.ax.pcolormesh(phibins, thetabins, self.H[:, :, shell].T, cmap=colormap, vmin = vmin, vmax=vmax)
            colormap.set_under(color='#D3D3D3')
            #self.txt_shell.set_text('Shell: %s' % self.shell)
            self.txt_w.set_text(r'$w = [%2.1f, %2.1f]$' % (self.wshellbins[self.shell], self.wshellbins[
                self.shell + 1]))
            self.ax.grid()

    def update_plot(self, dir='+'):
        if dir == '+':
            if self.wshellbins[self.shell] == self.wshellbins[-2]:
                self.txt_w.set_color('r')
            else:
                self.txt_w.set_color('k')
                self.shell += 1
        elif dir == '-':
            if self.wshellbins[self.shell] == self.wshellbins[0]:
                self.txt_w.set_color('r')
            else:
                self.txt_w.set_color('k')
                self.shell -= 1
        else:
            raise (ValueError("'dir' must be '+' or '-'."))

        self.plot(shell=self.shell)
        self.cb.formatter.set_powerlimits((0, 0))  # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh)  # force updating range of the colorbar


