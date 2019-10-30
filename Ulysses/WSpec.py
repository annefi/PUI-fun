import sys
import matplotlib.pyplot as plt
from numpy import arange, min, max, amin, amax, unique, around
#import matplotlib.ticker as ticker #for scientific notation at colorbar ticks


class WSpec():
    def __init__(self, D, min_wHe = 1.0, slice = 5, dim = 'x', color_norm = 'sg', mode = 'ps',
                 wbins = arange(-2,2.01, 0.2)):
        self.D = D
        self.slice = slice
        self.dim = dim
        self.color_norm = color_norm
        self.wbins = around(wbins,decimals=1)

        norm_arr, H0 = self.D.calc_w3dspecs(min_whe = min_wHe, wbins = wbins)
        if mode == 'norm':
            self.H = norm_arr
        elif mode == 'counts':
            self.H = H0
        elif mode == 'ps':
            H0[norm_arr == 0] = 0.
            norm_arr[norm_arr == 0] = 1
            self.H = H0 / norm_arr

    def init_plot(self, dim = 'x'):
        def keypress(event):
            if event.key == 'right':
                self.update_plot(dir='+')
            if event.key == 'left':
                self.update_plot(dir='-')
            if event.key == 'up':
                self.rot_plot()
            plt.show()
            print(self.slice)
            print 'click'
        fig, self.ax = plt.subplots(figsize=(10,8))
        fig.canvas.mpl_connect('key_press_event', keypress)
        self.txt_plane = self.ax.text(0.1, 1.05, '%s-plane'%'Y-Z', bbox = {"facecolor":"grey","alpha":0.4,"pad":10},
                                      transform = self.ax.transAxes)
        self.txt_slice = self.ax.text(0.6, 1.05, 'Slice: %s' % '10', bbox = {"facecolor":"grey","alpha":0.4,"pad":10},
                                      transform = self.ax.transAxes)
        self.plot(dim = self.dim, slice = self.slice)
        self.ax.set_xlim(self.ax.get_xlim()[::-1])
        self.cb = plt.colorbar(self.Quadmesh, ax = self.ax)
        self.cb.formatter.set_powerlimits((0, 0)) # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh) # force updating the colorbar

    def plot(self, dim, slice):
        wbins = self.wbins
        colormap = plt.cm.get_cmap("viridis")
        if self.color_norm == 'all':
            vmin = amin(self.H[self.H > 0])
            vmax = amax(self.H)
            if vmax < 1.:
                vmax = 10.
            if dim == 'x':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[slice, :, :].T, cmap=colormap, vmin = vmin,
                                                   vmax = vmax)
                colormap.set_under('white')
                self.txt_plane.set_text('%s-plane'%'Y-Z')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,x} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice+1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,y}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,z}}$')
            elif dim == 'y':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, slice, :].T, cmap=colormap, vmin = vmin,
                                                   vmax = vmax)
                colormap.set_under('white')
                self.txt_plane.set_text('%s-plane' % 'X-Z')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,y} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice+1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,x}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,z}}$')
            elif dim == 'z':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, :, slice], cmap=colormap, vmin = vmin,
                                                   vmax = vmax)
                colormap.set_under('white')
                self.txt_plane.set_text('%s-plane' % 'X-Y')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,z} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice+1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,x}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,y}}$')
            else:
                raise (ValueError("'dim' must be 'x', 'y' or 'z'."))
        if self.color_norm == 'sg':
            vmin = amin(self.H[self.H > 0])
            if dim == 'x':
                vmax = amax(self.H[slice, :, :])
                if vmax < 1.:
                    vmax = 10.
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[slice, :, :].T, cmap=colormap, vmin = vmin,
                                                   vmax=vmax)
                colormap.set_under('white')
                self.txt_plane.set_text('%s-plane' % 'Y-Z')
                self.txt_slice.set_text(r'$w_x = [%2.1f, %2.1f]$' % (wbins[slice], wbins[slice + 1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,y}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,z}}$')
            elif dim == 'y':
                vmax = amax(self.H[:, slice, :])
                if vmax < 1.:
                    vmax = 10.
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, slice, :].T, cmap=colormap, vmin=vmin,
                                                   vmax=vmax)

                colormap.set_under('white')
                self.txt_plane.set_text('%s-plane' % 'X-Z')
                self.txt_slice.set_text(r'$w_y = [%2.1f, %2.1f]$' % (wbins[slice], wbins[slice + 1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,x}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,z}}$')
            elif dim == 'z':
                vmax = amax(self.H[:, :, slice])
                if vmax < 1.:
                    vmax = 10.
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, :, slice], cmap=colormap, vmin=vmin,
                                                   vmax=vmax)
                colormap.set_under('white')
                self.txt_plane.set_text('%s-plane' % 'X-Y')
                self.txt_slice.set_text(r'$w_z = [%2.1f, %2.1f]$' % (wbins[slice], wbins[slice + 1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,x}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,y}}$')
            else:
                raise (ValueError("'dim' must be 'x', 'y' or 'z'."))


    def update_plot(self, dir = '+'):
        if dir == '+':
            if self.wbins[self.slice] == self.wbins[-2]:
                self.txt_slice.set_color('r')
            else:
                self.txt_slice.set_color('k')
                self.slice += 1
        elif dir == '-':
            if self.wbins[self.slice] == self.wbins[0]:
                self.txt_slice.set_color('r')
            else:
                self.txt_slice.set_color('k')
                self.slice -= 1
        else:
            raise(ValueError("'dir' must be '+' or '-'."))

        self.plot(dim = self.dim, slice = self.slice)
        self.cb.formatter.set_powerlimits((0, 0)) # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh) # force updating range of the colorbar


    def rot_plot(self):
        if self.dim == 'x':
            self.dim = 'y'
            self.ax.set_xlim(self.ax.get_xlim()[::-1])
        elif self.dim == 'y':
            self.dim = 'z'
            self.ax.set_xlim(self.ax.get_xlim()[::-1])
        elif self.dim == 'z':
            self.dim = 'x'
        self.plot(dim = self.dim, slice = self.slice)
        self.cb.formatter.set_powerlimits((0, 0)) # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh) # force updating range of the colorbar



