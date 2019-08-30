import sys
import matplotlib.pyplot as plt
from numpy import arange, min, max


class WSpec():
    def __init__(self, D, min_wHe = 0.9, slice = 10, dim = 'x'):
        self.D = D
        self.slice = slice
        self.dim = dim
        self.wbins = arange(-2, 2.01, 0.2)

        self.norm_arr, self.H = self.D.calc_w3dspecs(min_whe = min_wHe)
        self.norm_arr[self.norm_arr == 0] = 1

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

        fig, self.ax = plt.subplots()
        fig.canvas.mpl_connect('key_press_event', keypress)
        self.plot(dim = self.dim, slice = self.slice)
        colorbar = plt.colorbar(self.Quadmesh, ax = self.ax)




    def plot(self, dim, slice):
        wbins = self.wbins
        colormap = plt.cm.get_cmap("viridis")
        if dim == 'x':
            self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[slice, :, :], cmap=colormap, vmin = min(self.H[self.H>0]), vmax = max(self.H))
        elif dim == 'y':
            self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, slice, :].T, cmap=colormap, vmin = min(self.H[self.H>0]), vmax = max(self.H))
        elif dim == 'z':
            self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, :, slice], cmap=colormap, vmin = min(self.H[self.H>0]), vmax = max(self.H))
        else:
            raise (ValueError("'dim' must be 'x', 'y' or 'z'."))


    def update_plot(self, dir = '+'):
        if dir == '+':
            self.slice += 1
        elif dir == '-':
            self.slice -= 1
        else:
            raise(ValueError("'dir' must be '+' or '-'."))
        self.plot(dim=self.dim, slice=self.slice)

    def rot_plot(self):
        if self.dim == 'x':
            print('rot')
            self.dim = 'y'
        elif self.dim == 'y':
            self.dim = 'z'
        elif self.dim == 'z':
            self.dim = 'x'
        self.plot(dim=self.dim, slice=self.slice)





