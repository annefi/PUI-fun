import sys
import matplotlib.pyplot as plt
from numpy import arange, min, max, amin, amax, unique, around
#import matplotlib.ticker as ticker #for scientific notation at colorbar ticks


class WShell():
    def __init__(self, D, min_wHe = 0.01, shell = 5, color_norm = 'sg'):
        self.D = D
        self.shell = shell
        self.color_norm = color_norm

        self.phibins = around(arange(-180, 180, 10),decimals=1)
        self.thetabins = around(arange(-180, 180, 10), decimals=1)
        self.wshellbins = arange(0., 2.01, 0.2)

        norm_arr, H0 = self.D.calc_skymapspec(min_whe = min_wHe)
        norm_arr[norm_arr == 0] = 1
        self.H = H0/norm_arr

    def init_plot(self, dim = 'x'):
        def keypress(event):
            if event.key == 'right':
                self.update_plot(dir='+')
            if event.key == 'left':
                self.update_plot(dir='-')
            plt.show()
            print(self.shell)
            print 'click'
        fig, self.ax = plt.subplots(figsize=(10,8))
        fig.canvas.mpl_connect('key_press_event', keypress)
        self.txt_shell = self.ax.text(0.8, 1.05, 'Shell: %s' % self.shell, bbox = {"facecolor":"grey","alpha":0.4,
                                                                   "pad":10},  transform = self.ax.transAxes)
        self.plot(shell = self.shell)
        self.ax.set_xlim(self.ax.get_xlim()[::-1])
        self.cb = plt.colorbar(self.Quadmesh, ax = self.ax)
        self.cb.formatter.set_powerlimits((0, 0)) # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh) # force updating the colorbar

    def plot(self, shell):
        phibins = self.phibins
        thetabins = self.thetabins
        wshellbins = self.wshellbins
        colormap = plt.cm.get_cmap("viridis")
        if self.color_norm == 'all':
            vmin = amin(self.H[self.H > 0])
            vmax = amax(self.H)
            if vmax < 1.:
                vmax = 10.
            self.Quadmesh = self.ax.pcolormesh(phibins, thetabins, self.H[:, :, shell].T, cmap=colormap, vmin = vmin,
                                               vmax = vmax)
            colormap.set_under('white')
            self.txt_shell.set_text(r'$w = [%2.1f, %2.1f]$' % (wshellbins[shell], wshellbins[shell+1]))

        if self.color_norm == 'sg':
            vmin = amin(self.H[self.H > 0])
            vmax = amax(self.H[:, :, shell])
            if vmax < 1.:
                vmax = 10.
            self.Quadmesh = self.ax.pcolormesh(phibins, thetabins, self.H[:, :, shell].T, cmap=colormap, vmin = vmin,
                                               vmax=vmax)
            colormap.set_under('white')
            self.txt_shell.set_text(r'$w = [%2.1f, %2.1f]$' % (wshellbins[shell], wshellbins[shell+1]))



    def update_plot(self, dir = '+'):
        if dir == '+':
            if self.shell == 10:
                self.txt_shell.set_color('r')
            else:
                self.txt_shell.set_color('k')
                self.shell += 1
        elif dir == '-':
            if self.shell == 0:
                self.txt_shell.set_color('r')
            else:
                self.txt_shell.set_color('k')
                self.shell-= 1
        else:
            raise(ValueError("'dir' must be '+' or '-'."))

        self.plot(shell = self.shell)
        self.cb.formatter.set_powerlimits((0, 0)) # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh) # force updating range of the colorbar


