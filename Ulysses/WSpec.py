import sys
import matplotlib.pyplot as plt
from numpy import arange, min, max, unique


class WSpec():
    def __init__(self, D, min_wHe = 0.01, slice = 10, dim = 'x', color_norm = 'sg'):
        self.D = D
        self.slice = slice
        self.dim = dim
        self.color_norm = color_norm

        self.wbins = arange(-2, 2.01, 0.2)
        norm_arr, H0 = self.D.calc_w3dspecs(min_whe = min_wHe)
        norm_arr[norm_arr == 0] = 1
        self.H = H0/norm_arr

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
        self.txt_slice = self.ax.text(0.8, 1.05, 'Slice: %s' % '10', bbox = {"facecolor":"grey","alpha":0.4,"pad":10},
                                      transform = self.ax.transAxes)
        self.plot(dim = self.dim, slice = self.slice)
        self.ax.set_xlim(self.ax.get_xlim()[::-1])
        self.cb = plt.colorbar(self.Quadmesh, ax = self.ax)



    def plot(self, dim, slice):
        #min(self.H[self.H > 0])
        wbins = self.wbins
        colormap = plt.cm.get_cmap("viridis")
        if self.color_norm == 'all':
            if dim == 'x':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[slice, :, :].T, cmap=colormap, vmin = 0,
                                                   vmax = max(self.H))
                self.txt_plane.set_text('%s-plane'%'Y-Z')
                self.txt_slice.set_text('Slice: %s' % str(slice))
            elif dim == 'y':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, slice, :].T, cmap=colormap, vmin = 0,
                                                   vmax = max(self.H))
                self.txt_plane.set_text('%s-plane' % 'X-Z')
                self.txt_slice.set_text('Slice: %s' % str(slice))
            elif dim == 'z':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, :, slice], cmap=colormap, vmin = 0,
                                                   vmax = max(
                    self.H))
                self.txt_plane.set_text('%s-plane' % 'X-Y')
                self.txt_slice.set_text('Slice: %s' % str(slice))
            else:
                raise (ValueError("'dim' must be 'x', 'y' or 'z'."))
        if self.color_norm == 'sg':
            if dim == 'x':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[slice, :, :].T, cmap=colormap, vmin = 50,
                                                   vmax=max(self.H[slice, :, :]))
                self.txt_plane.set_text('%s-plane' % 'Y-Z')
                self.txt_slice.set_text('Slice: %s' % str(slice))
            elif dim == 'y':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, slice, :].T, cmap=colormap, vmin=50,
                                                   vmax=max(self.H[:, slice, :]))
                self.txt_plane.set_text('%s-plane' % 'X-Z')
                self.txt_slice.set_text('Slice: %s' % str(slice))
            elif dim == 'z':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, :, slice], cmap=colormap, vmin=50,
                                                   vmax=max(
                                                       self.H[:, slice, :]))
                self.txt_plane.set_text('%s-plane' % 'X-Y')
                self.txt_slice.set_text('Slice: %s' % str(slice))
            else:
                raise (ValueError("'dim' must be 'x', 'y' or 'z'."))



    def update_plot(self, dir = '+'):
        if dir == '+':
            if self.slice == 19:
                self.txt_slice.set_color('r')
            else:
                self.txt_slice.set_color('k')
                self.slice += 1
        elif dir == '-':
            if self.slice == 0:
                self.txt_slice.set_color('r')
            else:
                self.txt_slice.set_color('k')
                self.slice -= 1
        else:
            raise(ValueError("'dir' must be '+' or '-'."))
        self.plot(dim = self.dim, slice = self.slice)
        self.cb.update_bruteforce(self.Quadmesh)


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
        self.cb.update_bruteforce(self.Quadmesh) # for updating the range of the colorbar





