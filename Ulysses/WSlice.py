import sys
import matplotlib.pyplot as plt
from numpy import arange, min, max, amin, amax, unique, around
from numpy import *
import matplotlib

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
                            'figure.subplot.left':0.0,
                            'figure.subplot.bottom': 0.1,
                            'figure.subplot.right': 0.97,
                            'figure.subplot.top': 0.88,
                            'figure.figsize': (7,5.5)}) # Achtung anders

# define style of textboxes
props = dict(boxstyle='round', facecolor='#D3D3D3', edgecolor = 'k', alpha=0.8, pad = 0.8)


class WSlice():
    def __init__(self, D, min_wHe = 0.0, slice = 0, dim = 'R', color_norm = 'sg', mode = 'ps', wbins = arange(-2.1,
                                                                                                              2.11,
                                                                                                              0.2) ):
        self.D = D
        self.slice = slice
        self.dim = dim
        self.color_norm = color_norm

        self.wbins = around(wbins,decimals=1)

        norm_arr, H0 = self.D.calc_w3dspecs(wbins = wbins)
        if mode == 'norm':
            self.unit = 'PSV / $km^{6} \, s^{-3}$'
            norm_arr[norm_arr == 0] = -5.
            self.H = norm_arr
        elif mode == 'counts':
            self.unit = 'Counts'
            H0[norm_arr == 0] = -5.
            self.H = H0
        elif mode == 'ps':
            self.unit = r'Phase Space Density / $s^3 \, km^{-6}$'
            H0[norm_arr == 0] = -5.
            norm_arr[norm_arr == 0] = 1
            self.H = H0 / norm_arr

    def init_plot(self):
        def keypress(event):
            if event.key == 'right':
                self.update_plot(dir='+')
            if event.key == 'left':
                self.update_plot(dir='-')
            if event.key == 'up':
                self.rot_plot()
            plt.show()
            print(self.slice)
            print('click')
        fig, self.ax = plt.subplots()
        fig.canvas.mpl_connect('key_press_event', keypress)
        self.txt_plane = self.ax.text(0.05, 1.05, '%s-plane'%r'$\rm{w_T-w_N}$', bbox = props, transform =
        self.ax.transAxes, ha = 'left', va = 'bottom')
        self.ax.set_aspect('equal')
        self.ax.set_xticks(arange(-2,2.01,1))
        self.ax.set_yticks(arange(-2, 2.01, 1))

        #self.txt_slice = self.ax.text(0.61, 1.05, 'Slice: %s' % '10', bbox = props, transform = self.ax.transAxes)
        self.txt_slice = self.ax.text(0.95,1.05, 'Slice: %s' % '10', bbox=props, transform=self.ax.transAxes,
                                      ha = 'right', va = 'bottom')
        self.plot(dim = self.dim, slice = self.slice)
        self.cb = plt.colorbar(self.Quadmesh, ax = self.ax)
        self.cb.set_label("%s"%(self.unit), labelpad = 10)
        self.cb.formatter.set_powerlimits((0, 0)) # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh) # force updating the colorbar

    def plot(self, dim, slice):
        wbins = self.wbins
        colormap = plt.cm.get_cmap("jet")
        if self.color_norm == 'all':
            #vmin = amin(self.H[self.H > 0])
            vmin = 0.
            vmax = amax(self.H)
            if dim == 'R':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[slice, :, :].T, cmap=colormap, vmin = vmin,
                                                   vmax = vmax, rasterized=True)

                colormap.set_under(color='#D3D3D3')
                self.txt_plane.set_text('%s plane' % r'$\rm{w_T-w_N}$')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,R} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice+1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,T}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,N}}$')
            elif dim == 'T':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, slice, :].T, cmap=colormap, vmin = vmin,
                                                   vmax = vmax, rasterized=True)
                colormap.set_under(color='#D3D3D3')
                self.txt_plane.set_text('%s plane' % r'$\rm{w_R-w_N}$')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,T} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice+1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,R}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,N}}$')
            elif dim == 'N':
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, :, slice].T, cmap=colormap, vmin = vmin,
                                                   vmax = vmax, rasterized=True)
                colormap.set_under(color='#D3D3D3')
                self.txt_plane.set_text('%s plane' % r'$\rm{w_R-w_T}$')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,N} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice+1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,R}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,T}}$')
            else:
                raise (ValueError("'dim' must be 'R', 'T' or 'N'."))
        if self.color_norm == 'sg':
            if dim == 'R':
                #vmax = 10000.
                vmax = amax(self.H[slice, :, :])
                vmax = mean(self.H[slice, :, :]) + 3.5*std(self.H[slice, :, :])
                if vmax <= 0:
                    vmax = 0.0001

                try:
                    vmin = min(self.H[slice,:,:][self.H[slice,:,:] > 0.])
                except:
                    vmin = 0.00001
                print(vmin)
                # if vmin == 0.:
                #     vmin = 10
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[slice, :, :].T, cmap=colormap, vmin = vmin,
                                                   vmax = vmax, rasterized=True)
                colormap.set_under(color = '#D3D3D3')
                self.txt_plane.set_text('%s plane'%r'$\rm{w_T-w_N}$')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,R} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice+1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,T}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,N}}$')
            elif dim == 'T':
                vmax = amax(self.H[:, slice, :])
                #vmax = mean(self.H[slice, :, :]) + 1 * std(self.H[slice, :, :])
                if vmax <= 0:
                    vmax = 0.0001
                try:
                    vmin = min(self.H[:,slice,:][self.H[:,slice,:] > 0.])
                except:
                    vmin = 0.00001
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, slice, :].T, cmap=colormap, vmin = vmin,
                                                   vmax = vmax, rasterized=True)
                colormap.set_under(color = '#D3D3D3')
                self.txt_plane.set_text('%s plane' % r'$\rm{w_R-w_N}$')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,T} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice+1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,R}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,N}}$')
            elif dim == 'N':
                vmax = amax(self.H[:, :, slice])
                #vmax = mean(self.H[slice, :, :]) + 1.5 * std(self.H[slice, :, :])
                if vmax <= 0:
                    vmax = 0.0001
                try:
                    vmin = min(self.H[:,:,slice][self.H[:,:,slice] > 0.])
                except:
                    vmin = 0.00001
                self.Quadmesh = self.ax.pcolormesh(wbins, wbins, self.H[:, :, slice].T, cmap=colormap, vmin=vmin,
                                                   vmax=vmax, rasterized=True)
                colormap.set_under(color = '#D3D3D3')
                self.txt_plane.set_text('%s plane' % r'$\rm{w_R-w_T}$')
                self.txt_slice.set_text(r'$\mathrm{w_{sw,N} = [%2.1f, %2.1f]}$' % (wbins[slice], wbins[slice + 1]))
                self.ax.set_xlabel(r'$\mathrm{w_{sw,R}}$')
                self.ax.set_ylabel(r'$\mathrm{w_{sw,T}}$')
            else:
                raise (ValueError("'dim' must be 'R', 'T' or 'N'."))

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
        if self.dim == 'R':
            self.dim = 'T'
        elif self.dim == 'T':
            self.dim = 'N'
        elif self.dim == 'N':
            self.dim = 'R'
        self.plot(dim = self.dim, slice = self.slice)
        self.cb.formatter.set_powerlimits((0, 0)) # limits for changing to scientific number notation -> (0,0): always
        self.cb.update_bruteforce(self.Quadmesh) # force updating range of the colorbar



