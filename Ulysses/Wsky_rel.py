import matplotlib.pyplot as plt
from numpy import *
from numpy import arange, min, max, amin, amax, unique, around
from matplotlib import colors


class Wsky_rel():
    '''
    class for plotting the skymap specs but takes external histogram (= no calculation, only plotting)
    '''
    def __init__(self, H, wshellmax, name = 'no name'):
        self.wshellbins = arange(0.3, (wshellmax - 1) + 0.0001, 0.1)
        self.H = H
        self.color_norm = 'sg'
        self.mode = 'ps'
        self.shell = len(self.wshellbins) / 2
        self.phirange = [-pi, pi + 0.001]
        self.thetarange = [-pi / 2., pi / 2. + 0.001]
        self.angstep = 10 * pi / 180.
        self.name = name

    def init_plot(self, ax = None):
        def keypress(event):
            if event.key == 'right':
                self.update_plot(dir='+')
            if event.key == 'left':
                self.update_plot(dir='-')
            plt.show()
            print(self.shell)
            print 'click'

        fig = plt.figure(self.name)
        #fig = plt.figure('%s' % self.mode)
        self.ax = plt.subplot(111, projection="mollweide")
        fig.canvas.mpl_connect('key_press_event', keypress)
        self.ax.set_xlabel(r'$\varphi \, / \, \degree$')
        self.ax.set_ylabel(r'$\vartheta \, / \, \degree$')
        self.ax.grid()
        self.txt_shell = self.ax.text(0.05, 1.05, 'Shell: %s' % self.shell, bbox={"facecolor": "grey", "alpha": 0.4,
                                                                                  "pad": 10},
                                      transform=self.ax.transAxes)
        self.txt_w = self.ax.text(0.6, 1.05, r'$\mathrm{w_{sw} = [%2.1f, %2.1f]}$' % (self.wshellbins[self.shell],
                                                                                      self.wshellbins[self.shell + 1]),
                                  bbox={"facecolor": "grey", "alpha": 0.4, "pad": 10}, transform=self.ax.transAxes)
        self.plot(shell=self.shell)
        self.cb = plt.colorbar(self.Quadmesh, ax=self.ax)
        self.cb.formatter.set_powerlimits((0, 0))  # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh)  # force updating the colorbar


    def plot(self, shell):
        # bins that are shown in the plot. Have to have the dimension of the histogram.
        phibins = arange(-pi, pi + 0.001, self.angstep)
        thetabins = arange(-pi / 2., pi / 2. + 0.0001, self.angstep)

        colormap = plt.cm.get_cmap("viridis")
        if self.color_norm == 'all':
            vmin = amin(self.H[self.H > 0])
            vmax = amax(self.H)
            if vmax < 1.:
                vmax = 10.
            self.Quadmesh = self.ax.pcolormesh(phibins, thetabins, self.H[:, :, shell].T, cmap=colormap, vmin=vmin,
                                               vmax=vmax)
            colormap.set_under('gray')
            self.txt_shell.set_text('Shell: %s' % self.shell)
            self.txt_w.set_text(r'$w = [%2.1f, %2.1f]$' % (self.wshellbins[self.shell], self.wshellbins[
                self.shell + 1]))

        if self.color_norm == 'sg':
            # set limits for colormap:
            vmin = 0
            # vmin = amin(self.H[self.H > 0])
            vmax = amax(self.H[:, :, shell])
            # if vmax < 1:
            #     vmax = 10.

            self.Quadmesh = self.ax.pcolormesh(phibins, thetabins, self.H[:, :, shell].T, cmap=colormap, vmin=vmin,
                                               vmax=vmax)
            colormap.set_under('gray')
            self.txt_shell.set_text('Shell: %s' % self.shell)
            self.txt_w.set_text(r'$w = [%2.1f, %2.1f]$' % (self.wshellbins[self.shell], self.wshellbins[
                self.shell + 1]))


    def update_plot(self, dir='+'):
        if dir == '+':
            if self.wshellbins[self.shell] == self.wshellbins[-2]:
                self.txt_shell.set_color('r')
            else:
                self.txt_shell.set_color('k')
                self.shell += 1
        elif dir == '-':
            if self.wshellbins[self.shell] == self.wshellbins[0]:
                self.txt_shell.set_color('r')
            else:
                self.txt_shell.set_color('k')
                self.shell -= 1
        else:
            raise (ValueError("'dir' must be '+' or '-'."))

        self.plot(shell=self.shell)
        self.cb.formatter.set_powerlimits((0, 0))  # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh)  # force updating range of the colorbar

