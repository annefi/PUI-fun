import matplotlib.pyplot as plt
from numpy import *
from numpy import arange, min, max, amin, amax, unique, around
from matplotlib import colors


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
            norm_arr[norm_arr == 0] = -5.
            self.H = norm_arr
        elif mode == 'counts':
            H0[norm_arr == 0] = -5
            self.H = H0
        elif mode == 'ps':
            H0[norm_arr == 0] = -5
            norm_arr[norm_arr == 0] = 1
            self.H = H0 / norm_arr
        #
        # # cut out extra high values (at the edges: only few counts) that destroy the colormap:
        # for shell in range(len(self.wshellbins)-1):
        #     for i in range(4):
        #             print(self.H[:, :, shell].max())
        #             self.H[:, :, shell][self.H[:, :, shell] > (mean(self.H[:, :, shell]) + 3 * std(self.H[:, :,
        #                                                                                            shell]))] = 0
        #             print(self.H[:, :, shell].max())
        #             print(shell)


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
        thetabins = arange(-pi/2., pi/2. + 0.0001, self.angstep)

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
            #vmin = amin(self.H[self.H > 0])
            vmax = amax(self.H[:, :, shell])
            # if vmax < 1:
            #     vmax = 10.

            self.Quadmesh = self.ax.pcolormesh(phibins, thetabins, self.H[:, :, shell].T, cmap=colormap, vmin = vmin, vmax=vmax)
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


