"""
Date: 23.01.2015
Authors: Christian Drews <drews@physik.uni-kiel.de>,
Lars Berger <berger@physik.uni-kiel.de>
"""

import numpy as np
from numpy import *
from scipy import ndimage
import matplotlib
from matplotlib import animation
import pylab
from _plotmod import PlotMod
from _datacontainer import DataContainer
from pylib.etMisc import loading_bar

class PlotdbData(object):
    def __init__(self, db):
        """
        Class that provides the plotting routines for dbData
        INPUT:
            db : dbData instance
        """
        self.db = db
    def __configure_axes(self, kindex, ax, validmasks, Nx, xlabel, ylabel, rot_xticks, prodx, prody):
        """
        Internal routine to configure axes of hist2d and animate2d plot
        """
        if kindex >= len(validmasks)-Nx:
            if not xlabel:
                ax.set_xlabel(self.db.dp[prodx].get("name"))
            else:
                ax.set_xlabel(xlabel)
            ax.xaxis.set_major_locator(matplotlib.ticker.MaxNLocator(prune='both'))
            if rot_xticks:
                for tick in ax.xaxis.get_major_ticks():
                    tick.label.set_rotation('vertical')
        else:
            for tick in ax.xaxis.get_major_ticks():
                tick.label.set_visible(False)
            ax.xaxis.set_major_locator(matplotlib.ticker.MaxNLocator(prune='both'))
        if (kindex)%Nx == 0:
            if not ylabel:
                ax.set_ylabel(self.db.dp[prody].get("name"))
            else:
                ax.set_ylabel(ylabel)
            ax.yaxis.set_major_locator(matplotlib.ticker.MaxNLocator(prune='both'))
        else:
            ax.yaxis.set_major_locator(matplotlib.ticker.MaxNLocator(prune='both'))
            for tick in ax.yaxis.get_major_ticks():
                tick.label.set_visible(False)
    def __create_bins(self, binx, prodx, valx):
        """
        Internal routine to create bin arrays used for hist2d, hist1d, and animate2d
        """
        if not isinstance(binx, ndarray):
            P = self.db.data[prodx][self.db.DM()]
            P = P[(P > -1e99)*(P < 1e99)]
            if alltrue(valx%1 == 0):
                Nbins = np.amax(P)-np.amin(P)+2
                if Nbins > binx:
                    Nbins = binx
                binx = linspace(np.amin(P), np.amax(P)+1, Nbins)
            else:
                Nbins = binx
                binx = linspace(np.amin(P), np.amax(P), Nbins+1)
        return binx
    def __process_norm(self, C, norm):
        """
        Internal routine to processes normalization for hist2d and animate2d
        """
        def func(C, norm):
            if norm == "ysum":
                for i in range(C.shape[1]):
                    if sum(C[:, i]) > 0:
                        C[:, i] /= float(sum(C[:, i]))
            elif norm == "ymax":
                for i in range(C.shape[1]):
                    if np.amax(C[:, i]) > 0:
                        C[:, i] /= float(np.amax(C[:, i]))
            elif norm == "xsum":
                for i in range(C.shape[0]):
                    if sum(C[i,:]) > 0:
                        C[i,:] /= float(sum(C[i,:]))
            elif norm == "xmax":
                for i in range(C.shape[0]):
                    if np.amax(C[i,:]) > 0:
                        C[i,:] /= float(np.amax(C[i,:]))
            elif norm == "sqrt":
                for i in range(C.shape[0]):
                    C[i,:] = sqrt((C[i,:]))
            elif norm == "max":
                C = C/float(np.amax(C))
            elif norm == "sum":
                C = C/float(sum(C))
            elif norm == "log":
                C = log10(C)
            return C
        if len(C.shape) == 3:
            for i in range(0, C.shape[2]):
                C[:,:, i] = func(C[:,:, i], norm)
        else:
            C = func(C, norm)
        return C
    def __calculate_panels(self, ncols, validmasks):
        """
        Internal routine to calculate the panel number and format of hist2d and animate2d
        """
        NPlots = len(validmasks)
        if ncols:
            Nx = ncols
            if len(validmasks)%int(ncols) == 0:
                Ny = int(len(validmasks)/ncols)
            else:
                Ny = int(len(validmasks)/ncols)+1
        else:
            if NPlots == 1:
                Nx, Ny = 1, 1
            elif 2 >= NPlots > 0:
                Nx, Ny = 2, 1
            elif 4 >= NPlots > 2:
                Nx, Ny = 2, 2
            elif 6 >= NPlots > 4:
                Nx, Ny = 3, 2
            elif 10 > NPlots > 6:
                Nx, Ny = 3, 3
            elif 12 >= NPlots >= 10:
                Nx, Ny = 4, 3
            elif 16 >= NPlots > 12:
                Nx, Ny = 4, 4
            else:
                print "Too Many Mask or no Mask - Use less than 10 or at least 1 Mask(s) for histogram2d"
                return
        return Nx, Ny
    def __init_anim_axes(self, ax_anim, zlabel, prodz):
        """
        Internal routine to create animation control axes
        """
        ax_anim.xaxis.set_ticks_position("top")
        for tick in ax_anim.get_xticklabels():
            tick.set_fontsize(9)
        if not zlabel:
            ax_anim.set_xlabel(self.db.dp[prodz].get("name"), size=9)
        else:
            ax_anim.set_xlabel(zlabel, size=9)
        for tick in ax_anim.yaxis.get_major_ticks():
            tick.label.set_visible(False)
            tick.set_visible(False)
    def __prepare_timeseries(self, P, smask, Master):
        """
        Internal Routine to prepare the timeseries plot. Calculated number panels, processes
        product and mask list to proper format
        """
        if smask:
            validmasks = smask
            NPlots = len(validmasks)
            if isinstance(P, list):
                Counter = len(P)
                for product in P:
                    if product[0] == '*':
                        Counter -= 1
                NPlots *= Counter
                NPlots += len(P)-Counter
            else:
                P = [P]
        else:
            validmasks = self.db.mask.keys()
            validmasks.remove("Master")
            if Master != False:
                validmasks.append("Master")
            NPlots = len(validmasks)
            if isinstance(P, list):
                Counter = len(P)
                for product in P:
                    if product[0] == '*':
                        Counter -= 1
                NPlots *= Counter
                NPlots += len(P)-Counter
            else:
                P = [P]
        return NPlots, P, validmasks
    def __init_anim_control(self):
        def _enter(event):
            if event.key == "8":
                self.Splay = True
            elif event.key == "2":
                self.Splay = False
            elif event.key == "4":
                self.ANIMATION_C -= 1
            elif event.key == "6":
                self.ANIMATION_C += 1
        def _enterB(event, Z):
            try:
                if event.inaxes.get_position().x0 < 0.05001:
                    X = event.xdata
                    self.ANIMATION_C = searchsorted(Z, X)
            except:
                pass
        return _enter, _enterB
    def hist1d(self, prod,binx=50,norm=False,smask=False,weights=False,Master=True,xlabel=False,ylabel=False,
               legend=True,legendbox=True, avg=False, pm = False):
        """This routine makes a 1d histogram of the current data
        input: prod: key of self.data to be histogrammed
        binx: bins for the histogram (number or ndarray)
        norm: 'ymax' (normalized to max of hist) or 'ysum' (normalized to sum of hist)
        avg: if a float is supplied a 1D gaussian filter (sigma=avg * bins width) is applied to the data
        smask: list of masks that should be plotted
        weights: weights for the histogram (e.g. 'counts')
        Master: If True, the Master mask is plotted
        """

        pdata = DataContainer("hist1D", self.db)
        if pm:
            ax = pm.get_axis('A0')
            pylabh = pm.fig
        else:
            pylabh = pylab.figure()
            ax = pylab.gca()
        if not xlabel:
            ax.set_xlabel(self.db.dp[prod].get("name"))
        else:
            ax.set_xlabel(xlabel)
        if not ylabel:
            ax.set_ylabel('N')
        else:
            ax.set_ylabel(ylabel)
        if smask:
            validmasks = smask
        else:
            validmasks = self.db.mask.keys()
            validmasks.remove("Master")
            if Master != False:
                validmasks.append("Master")
        valy = self.db.data[prod][self.db.DM()]

        binx = self.__create_bins(binx, prod, valy)
        pylab.xlim(binx[0], binx[-1])
        for mask in validmasks:
            valy = self.db.data[prod][self.db.get_mask(mask)]
            if weights:
                hist, xvals = histogram(valy, bins=binx, weights=self.db.data[weights][self.db.get_mask(mask)])
            else:
                hist, xvals = histogram(valy, bins=binx)
            if avg:
                h = ndimage.gaussian_filter(h, sigma=avg)
            pdata.add_data(mask, (hist, xvals), prodx=prod, norm=norm)
            hist = 1.*hist
            if norm == 'ymax':
                hist /= float(np.amax(hist))
            elif norm == "ysum":
                hist /= float(sum(hist))
            elif norm:
                print "Unrecognized norm mode!"
            hist = append(hist, 0.)
            ax.plot(xvals[:], hist, label=self.db.mp[mask].get("name"), color=self.db.mp[mask].get("color"), lw = self.db.mp[mask].get("linewidth"), ls = "steps-post"+self.db.mp[mask].get("linestyle"), marker=self.db.mp[mask].get("marker"))

        if legend and legendbox:
            pylab.legend()
        elif legend:
            pylab.legend().get_frame().set_visible(False)
        pmod = PlotMod(pylabh, style="hist1D")
        pmod.set_data(pdata)
        return pmod
    def hist2d(self, prodx, prody, prodz=False, binx=50, biny=50, norm=False, cb=False, weights=False, smask=False, ncols=False, Master=True, xlabel=False, ylabel=False, rot_xticks=True, style = "both", shade=False, clines=10, avg=False):
        """
        This routine creates 2D Histograms of two different data products
        TODO: Use proper automatic bins
        INPUT:
        prodx: key of self.data to be histogrammed onto x-axis
        prody: key of self.data to be histogrammed onto y-axis
        prodz: if a prod is given, the averaged product prodz over prodx
               and prody will be plotted
        binx: xbins for the histogram (number or ndarray)
        biny: ybins for the histogram (number or ndarray)
        norm: can be either 'xmax','xsum','ymax', 'ysum', 'max', 'sum', or 'log'
        smask: list of masks that should be plotted
        avg: if a float is supplied a 2D gaussian filter (sigma=avg * bins width) is applied to the data
        rot_xticks: If True xticks are rotated for plot
        weights: weights for the histogram
        cb: a string for the colorbar - The colrbar is only plotted if a non empty string is passed
        ncols: number of columns for the 2d histogram
        style: can be 'contour', 'contourline', or 'both'
        shade: True or False, Turns on/off the shading plot option, which illuminates the contour.
               Parameters 'shadeazimuth' and 'shadepolar' in mask properties determine the
               direction from which the contour is illuminated
        Master: If True, the Master mask is plotted
        clines: number of contourlines for the contour plot

        """
        pylab2dh = pylab.figure()
        pdata = DataContainer("hist2D", self.db)
        pylab.subplots_adjust(hspace=0, wspace=0)
        if smask:
            validmasks = smask
        else:
            validmasks = self.db.mask.keys()
            validmasks.remove("Master")
            if Master != False:
                validmasks.append("Master")
        Nx, Ny = self.__calculate_panels(ncols, validmasks)
        MINX, MAXX = False, False
        MINY, MAXY = False, False
        axtmp = False
        for kindex, key in enumerate(validmasks):
            if axtmp:
                ax = pylab2dh.add_subplot(Ny, Nx, kindex+1, sharex=axtmp, sharey=axtmp)
            else:
                ax = pylab2dh.add_subplot(Ny, Nx, kindex+1)
            axtmp = ax
            self.__configure_axes(kindex, ax, validmasks, Nx, xlabel, ylabel, rot_xticks, prodx, prody)

            valx = self.db.data[prodx][self.db.get_mask(key)]
            valy = self.db.data[prody][self.db.get_mask(key)]

            binx = self.__create_bins(binx, prodx, valx)
            biny = self.__create_bins(biny, prody, valy)

            if weights:
                C, X, Y = histogram2d(valx, valy, bins=[binx, biny], weights=self.db.data[weights][self.db.get_mask(key)])
            elif prodz:
                C, X, Y = histogram2d(valx, valy, bins=[binx, biny], weights=self.db.data[prodz][self.db.get_mask(key)])
                CFREQ, X, Y = histogram2d(valx, valy, bins=[binx, biny])
                C = C/CFREQ
            elif prodz and weights:
                C, X, Y = histogram2d(valx, valy, bins=[binx, biny], weights=self.db.data[prodz][self.db.get_mask(key)]*self.db.data[prodz][self.db.get_mask(key)])
                CFREQ, X, Y = histogram2d(valx, valy, bins=[binx, biny])
                C = C/CFREQ
            else:
                C, X, Y = histogram2d(valx, valy, bins=[binx, biny])
            if avg:
                C = ndimage.gaussian_filter(C, sigma=avg)

            pdata.add_data(key, (C, X, Y), prodx, prody, prodz, norm)
            if MINX == False or MINX > np.amin(X):
                MINX = np.amin(X)
            if MAXX == False or MAXX < np.amax(X):
                MAXX = np.amax(X)
            if MINY == False or MINY > np.amin(Y):
                MINY = np.amin(Y)
            if MAXY == False or MAXY < np.amax(Y):
                MAXY = np.amax(Y)
            C[isnan(C)] = -1
            C = 1.*C
            if norm == "log":
                C = self.__process_norm(C, norm)
                C[isinf(C)] = -999
                vmin = np.amin(C[C > -999])
                vmax = np.amax(C)
            elif norm != False:
                C = self.__process_norm(C, norm)
                vmin = np.amin(C[C > 0])
                vmax = np.amax(C)
            else:
                vmin = np.amin(C[C > 0])
                vmax = np.amax(C)
            #print(self.db.mp[key].get("contourcolor"))
            colormap = pylab.cm.get_cmap(self.db.mp[key].get("contourcolor"), 1024*16)

            if style == "contour" or style == "both":
                if shade:
                    ls = matplotlib.colors.LightSource(azdeg=self.db.mp[key].get("shadeazimuth"), altdeg=self.db.mp[key].get("shadepolar"))
                    rgb = ls.shade(C.T, colormap)
                    ax.imshow(rgb, extent=(X[0], X[-1], Y[-1], Y[0]), aspect="auto", alpha=0.7)
                    Mesh = ax.pcolormesh(X, Y, C.T, cmap=colormap, vmin=vmin, vmax=vmax, zorder=0)
                else:
                    Mesh = ax.pcolormesh(X, Y, C.T, cmap=colormap, vmin=vmin, vmax=vmax)
            if style == "both" or style == "contourline":
                C[C < 0] = 0
                G = ndimage.gaussian_filter(C, 2)
            if style == "both":
                MeshL = ax.contour(X[:-1], Y[:-1], G.T, clines, colors="white", alpha=0.5, vmin=vmin, vmax=vmax)
                pylab.clabel(MeshL, fontsize=9, inline=True, alpha=1.0, fmt="%4.1f")
            if style == "contourline":
                MeshL = ax.contour(X[:-1], Y[:-1], G.T, clines, cmap=colormap, alpha=1.0, vmin=vmin, vmax=vmax)
                pylab.clabel(MeshL, fontsize=9, inline=True, alpha=1.0, fmt="%4.1f")
            colormap.set_under('white')
            ax.text(self.db.mp[key].get("label_loc")[0], self.db.mp[key].get("label_loc")[1], self.db.mp[key].get("name"), horizontalalignment='left', verticalalignment="bottom", transform=ax.transAxes, backgroundcolor=self.db.mp[key].get("color"), color="white")
            ax.xaxis.grid(True)
            ax.yaxis.grid(True)
        for ax in pylab2dh.axes:
            ax.set_xlim(np.amin(X), np.amax(X))
            ax.set_ylim(np.amin(Y), np.amax(Y))
        if cb:
            axcb = pylab.axes([0.9, 0.1, 0.02, 0.8])
            MINZ, MAXZ = vmin, vmax
            if prodz:
                cb1 = matplotlib.colorbar.ColorbarBase(axcb, cmap=colormap, orientation="vertical", norm=matplotlib.colors.Normalize(vmin=MINZ, vmax=MAXZ))
            else:
                cb1 = matplotlib.colorbar.ColorbarBase(axcb, cmap=colormap, orientation="vertical", norm=matplotlib.colors.Normalize(vmin=MINZ, vmax=MAXZ))
            cb1.set_label("%s"%(cb))
        pmod = PlotMod(pylab2dh, style="hist2D")
        pmod.set_data(pdata)
        return pmod
    def timeseries(self, prody,prodx="time",time=None,smask=False,avg=False,weights=False,mode="mean",Master=True):
        """
        This routine creates timeseries of various data products
        INPUT:

        prodx: key of self.data over which the series is plotted (prob. 'time')
        prody: key of self.data that is plotted over time, can also be a list of products.
               If prody starts with '*' this dataproduct is ONLY plotted for the first entry
               in smask. E.g prody="vsw" means vsw is plotted for all masks, while for prody='*vsw'
               vsw is only plotted for the first mask in smask
        time: time bins used for time series - must a ndarray
        smask: list of masks that should be plotted
        weights: weights for the timeseries
        mode: Either a string or a list of strings -->
            'mean': mean of prody inside time bin is plotted over time
            'sum' : sum of prody inside time bin is plotted over time
            'freq' : number of occurences of prody inside time bin is plotted over time
        avg: number of bins (to the left AND right) used for a slindig average
        sliding average is only plotted if avg is passed

        """


        pylabts = pylab.figure()
        pylab.subplots_adjust(hspace=0, wspace=0)
        pdata = DataContainer("timeseries", dbData=self.db)
        P = prody
        if time == None:
            untimes = unique(self.db.data[prodx])
            time = append(untimes, untimes[-1]+(untimes[-1]-untimes[-2]))
        NPlots, P, validmasks = self.__prepare_timeseries(P, smask, Master)
        if isinstance(mode, list):
            if len(mode) != len(P):
                print "Not enough Modes (N=%s) supplied for timeseries of Prods (N=%s)"%(len(mode), len(P))
                return
        else:
            mode = len(P)*[mode]
        PCounter = 0
        axtmp = False
        for kindex, key in enumerate(validmasks):
            for pindex, prody in enumerate(P):
                if prody[0] == "*":
                    plotmask_label = False
                    prody = prody[1:]
                    if kindex != 0:
                        continue
                else:
                    plotmask_label = True
                mL = matplotlib.ticker.AutoMinorLocator()
                PCounter += 1
                if axtmp:
                    ax = pylabts.add_subplot(NPlots, 1, PCounter, sharex=axtmp)
                else:
                    ax = pylabts.add_subplot(NPlots, 1, PCounter)
                axtmp = ax
                if PCounter == NPlots:
                    ax.set_xlabel(self.db.dp[prodx].get("name"))
                else:
                    for tick in ax.xaxis.get_major_ticks():
                        tick.label.set_visible(False)
                ax.set_ylabel(self.db.dp[prody].get("name"), color="white", backgroundcolor=self.db.dp[prody].get("color"))
                valx = self.db.data[prodx][self.db.get_mask(key)]
                valy = self.db.data[prody][self.db.get_mask(key)]
                if weights:
                    valw = self.db.data[weights][self.db.get_mask(key)]
                    Counts, binedges = histogram(valx, bins=time, weights=valw)
                else:
                    Counts, binedges = histogram(valx, bins=time)
                ProdY, binedges = histogram(valx, bins=time, weights=valy)
                if mode[pindex] == "mean":
                    plotres = ProdY/(Counts*1.)
                elif mode[pindex] == "sum":
                    plotres = ProdY
                elif mode[pindex] == "freq":
                    plotres = Counts
                else:
                    print "Please enter valid mode!"
                    return
                pdata.add_data(key+":"+self.db.dp[prody].get("name"), (plotres, time[:-1]), prodx=prodx, prody=P, prodz=validmasks, norm=(mode, avg))
                ticks = ax.yaxis.get_major_ticks()
                ticks[0].label.set_visible(False)
                if avg:
                    avg_arr = zeros(len(plotres))
                    for tindex in range(avg, len(time)-avg):
                        dat = plotres[tindex-avg:tindex+avg]
                        avg_arr[tindex] = average(dat[isnan(dat) == False])
                    ax.plot(time[:-1], plotres, color=self.db.dp[prody].get("color"), marker="o", markersize=self.db.dp[prody].get("markersize"), linestyle="")
                    ax.plot(time[:-1], avg_arr, c=self.db.dp[prody].get("color"), lw = self.db.dp[prody].get("linewidth"), ls = self.db.dp[prody].get("linestyle"))
                else:
                    ax.plot(time[:-1], plotres, c=self.db.dp[prody].get("color"), lw = self.db.dp[prody].get("linewidth"), ls = self.db.dp[prody].get("linestyle"), marker=self.db.dp[prody].get("marker"), markersize=self.db.dp[prody].get("markersize"))
                if plotmask_label:
                    ax.text(1.02, 0.5, self.db.mp[key].get("name"), horizontalalignment='center', verticalalignment="center", transform=ax.transAxes, backgroundcolor=self.db.mp[key].get("color"), color="white", rotation="vertical")
                ax.set_xlim(time[0], time[-1])
                ax.xaxis.set_minor_locator(mL)
                ax.xaxis.grid(True, which="both")
                ax.yaxis.grid(True)
        pmod = PlotMod(pylabts, style="timeseries")
        pmod.set_data(pdata)
        return pmod
    def animate1d(self, prod,prodz,binx=50,binz=50,speed=100,norm=False,smask=False,weights=False,Master=True,xlabel=False,ylabel=False, zlabel=False, legend=True,legendbox=True,save='',fps=5):
        """This routine makes an animation of 1d histograms of the current data
        input: prod: key of self.data to be histogrammed
        binx: bins for the histogram (number or ndarray)
        binz: zbins for the aimation
        prodz: key of self.data to be histogrammed used for the animation frames
        speed: Animation speed (small = Fast)
        norm: 'ymax' (normalized to max of hist) or 'ysum' (normalized to sum of hist)
        smask: list of masks that should be plotted
        weights: weights for the histogram (e.g. 'counts')
        Master: If True, the Master mask is plotted
        """
        pylaba = pylab.figure()
        ax = pylab.gca()
        ax_anim = pylab.axes([0.05, 0.94, 0.9, 0.02])
        self.__init_anim_axes(ax_anim, zlabel, prodz)
        if not xlabel:
            ax.set_xlabel(self.db.dp[prod].get("name"))
        else:
            ax.set_xlabel(xlabel)
        if not ylabel:
            ax.set_ylabel('N')
        else:
            ax.set_ylabel(ylabel)
        if smask:
            validmasks = smask
        else:
            validmasks = self.db.mask.keys()
            validmasks.remove("Master")
            if Master != False:
                validmasks.append("Master")
        valx = self.db.data[prod][self.db.DM()]
        valz = self.db.data[prodz][self.db.DM()]
        binx = self.__create_bins(binx, prod, valx)
        binz = self.__create_bins(binz, prodz, valz)
        pylab.xlim(binx[0], binx[-1])
        DATACONT = {}
        DATA = {}
        for mask in validmasks:
            valx = self.db.data[prod][self.db.get_mask(mask)]
            valz = self.db.data[prodz][self.db.get_mask(mask)]
            if weights:
                C, X, Z = histogram2d(valx, valz, bins=[binx, binz], weights=self.db.data[weights][self.db.get_mask(mask)])
            else:
                C, X, Z = histogram2d(valx, valz, bins=[binx, binz])
            C = 1.*C
            if norm:
                C = self.__process_norm(C, norm)
            DATA[mask] = C
            DATACONT[mask] = ax.plot(binx, append(C[:, 0], 0), label=self.db.mp[mask].get("name"), color=self.db.mp[mask].get("color"), lw = self.db.mp[mask].get("linewidth"), ls = "steps-post"+self.db.mp[mask].get("linestyle"), marker=self.db.mp[mask].get("marker"))[0]
        ax_anim.set_xlim(np.amin(Z), np.amax(Z))
        ax_anim.set_ylim(0, 1)
        if legend and legendbox:
            ax.legend()
        elif legend:
            ax.legend().get_frame().set_visible(False)
        ANIMCONT = ax_anim.plot([np.amin(Z)], [0.5], linestyle="None", marker="o", markersize=6)

        # Here the Animation logic starts
        self.ANIMATION_C = -1
        ZW = (Z[1]-Z[0])/2.
        self.Splay = True
        _enter, _enterB = self.__init_anim_control()
        def animate(i):
            if self.Splay:
                self.ANIMATION_C += 1
            self.ANIMATION_C = self.ANIMATION_C%(len(Z)-1)
            ANIMCONT[0].set_data([Z[self.ANIMATION_C]], [0.5])
            for key in validmasks:
                z = append(DATA[key][:, self.ANIMATION_C], 0)
                DATACONT[key].set_data(binx, z)
            return 0,
        self.C2 = pylaba.canvas.mpl_connect('key_press_event', lambda event: _enter(event))
        self.C2 = pylaba.canvas.mpl_connect('motion_notify_event', lambda event: _enterB(event, Z))
        print "SMALL HOWTO: ANIMATED1D"
        print "------------------------"
        print "Use NUMPAD arrowkeys to control animation."
        print "Hover Mouse over animation bar, to jump to that location!"
        self.anim = matplotlib.animation.FuncAnimation(pylaba, animate, frames=Z.shape[0]-1, interval=speed, blit=False)
        if save:
            self.anim.save(save, fps=fps, codec="mpeg4")
    def animate2d(self, prodx,prody,prodz,binx=50,biny=50,binz=50,speed=100,norm=False,cb=False,weights=False,smask=False,ncols=False,Master=True,xlabel=False,ylabel=False, zlabel=False,shade=False,rot_xticks=True,save='',fps=5, avg = False):
        """
        This routine creates animated 2D Histograms of two different data products over a third
        Data Product
        TODO: Use proper automatic bins
        INPUT:
        prodx: key of self.data to be histogrammed onto x-axis
        prody: key of self.data to be histogrammed onto y-axis
        prodz: key of self.data to be histogrammed used for the animation frames
        binx: xbins for the histogram (number or ndarray)
        biny: ybins for the histogram (number or ndarray)
        binz: zbins for the aimation
        speed: Animation speed (small = Fast)
        norm: can be either 'xmax','xsum','ymax', 'ysum', 'max', 'sum', or 'log'
        smask: list of masks that should be plotted
        avg: if a float is supplied a 2D gaussian filter (sigma=avg * bins width) is applied to the data
        rot_xticks: If True xticks are rotated for plot
        shade: True or False, Turns on/off the shading plot option, which illuminates the contour.
               Parameters 'shadeazimuth' and 'shadepolar' in mask properties determine the
               direction from which the contour is illuminated
        weights: weights for the histogram
        cb: a string for the colorbar - The colrbar is only plotted if a non empty string is passed
        ncols: number of columns for the 2d histogram
        Master: If True, the Master mask is plotted

        """
        pylab2da = pylab.figure()
        ax_anim = pylab.axes([0.05, 0.94, 0.9, 0.02])
        self.__init_anim_axes(ax_anim, zlabel, prodz)
        pylab.subplots_adjust(hspace=0, wspace=0)
        if smask:
            validmasks = smask
        else:
            validmasks = self.db.mask.keys()
            validmasks.remove("Master")
            if Master != False:
                validmasks.append("Master")
        Nx, Ny = self.__calculate_panels(ncols, validmasks)
        MINX, MAXX = False, False
        MINY, MAXY = False, False
        axtmp = False
        DATACONT = {}
        DATACONTS = {}
        DATA = {}
        for kindex, key in enumerate(validmasks):
            if axtmp:
                ax = pylab2da.add_subplot(Ny, Nx, kindex+1, sharex=axtmp, sharey=axtmp)
            else:
                ax = pylab2da.add_subplot(Ny, Nx, kindex+1)
            axtmp = ax
            self.__configure_axes(kindex, ax, validmasks, Nx, xlabel, ylabel, rot_xticks, prodx, prody)

            valx = self.db.data[prodx][self.db.get_mask(key)]
            valy = self.db.data[prody][self.db.get_mask(key)]
            valz = self.db.data[prodz][self.db.get_mask(key)]
            if weights:
                valw = self.db.data[weights][self.db.get_mask(key)]
            binx = self.__create_bins(binx, prodx, valx)
            biny = self.__create_bins(biny, prody, valy)

            C, edges = histogramdd([valx, valy, valz], bins=[binx, biny, binz])

            if weights:
                C, edges = histogramdd([valx, valy, valz], bins=[binx, biny, binz], weights=valw)
            else:
                C, edges = histogramdd([valx, valy, valz], bins=[binx, biny, binz])

            if avg:
                for i in range(0, C.shape[2]):
                    C[:,:, i] = ndimage.gaussian_filter(C[:,:,i], sigma=avg)

            X, Y, Z = edges
            C[isnan(C)] = -1
            C = 1.*C
            if MINX == False or MINX > np.amin(X):
                MINX = np.amin(X)
            if MAXX == False or MAXX < np.amax(X):
                MAXX = np.amax(X)
            if MINY == False or MINY > np.amin(Y):
                MINY = np.amin(Y)
            if MAXY == False or MAXY < np.amax(Y):
                MAXY = np.amax(Y)
            C[isnan(C)] = -1
            C = 1.*C
            if norm:
                C = self.__process_norm(C, norm)
            DATA[key] = C
            colormap = pylab.cm.get_cmap(self.db.mp[key].get("contourcolor"), 1024*16)


            if shade:
                ls = matplotlib.colors.LightSource(azdeg=self.db.mp[key].get("shadeazimuth"), altdeg=self.db.mp[key].get("shadepolar"))
                rgb = ls.shade(C[:,:, 0].T, colormap)
                DATACONTS[key] = ax.imshow(rgb, extent=(X[0], X[-1], Y[-1], Y[0]), aspect="auto", alpha=0.7, zorder=1)

            print(C)

            DATACONT[key] = ax.pcolormesh(X, Y, C[:,:, 0].T, cmap=colormap, vmin=np.amin(C[C > 0]), vmax=np.amax(C))
            colormap.set_under('white')
            ax.text(self.db.mp[key].get("label_loc")[0], self.db.mp[key].get("label_loc")[1], self.db.mp[key].get("name"), horizontalalignment='left', verticalalignment="bottom", transform=ax.transAxes, backgroundcolor=self.db.mp[key].get("color"), color="white")
            ax.xaxis.grid(True)
            ax.yaxis.grid(True)
        for ax in pylab2da.axes:
            ax.set_xlim(np.amin(X), np.amax(X))
            ax.set_ylim(np.amin(Y), np.amax(Y))
        ax_anim.set_xlim(np.amin(Z), np.amax(Z))
        ax_anim.set_ylim(0, 1)
        ANIMCONT = ax_anim.plot([np.amin(Z)], [0.5], linestyle="None", marker="o", markersize=6)
        if cb:
            axcb = pylab.axes([0.9, 0.1, 0.02, 0.8])
            if prodz:
                MINZ, MAXZ = np.amin(C), np.amax(C)
                cb1 = matplotlib.colorbar.ColorbarBase(axcb, cmap=colormap, orientation="vertical", norm=matplotlib.colors.Normalize(vmin=MINZ, vmax=MAXZ))
            else:
                cb1 = matplotlib.colorbar.ColorbarBase(axcb, cmap=colormap, orientation="vertical",)
            cb1.set_label("%s"%(cb))

        # Here the Animation logic starts
        self.ANIMATION_C = -1
        ZW = (Z[1]-Z[0])/2.
        self.Splay = True
        self.SHADEAZ = 0
        _enter, _enterB = self.__init_anim_control()
        def animate(i):
            if self.Splay:
                self.ANIMATION_C += 1
            self.ANIMATION_C = self.ANIMATION_C%(len(Z)-1)
            ANIMCONT[0].set_data([Z[self.ANIMATION_C]], [0.5])
            for key in validmasks:
                z = DATA[key][:,:, self.ANIMATION_C].T
                DATACONT[key].set_array(z.ravel())
                if shade:
                    rgb = ls.shade(DATA[key][:,:, self.ANIMATION_C].T, colormap)
                    DATACONTS[key].set_array(rgb)
            return 0,
        self.C2 = pylab2da.canvas.mpl_connect('key_press_event', lambda event: _enter(event))
        self.C2 = pylab2da.canvas.mpl_connect('motion_notify_event', lambda event: _enterB(event, Z))
        print "SMALL HOWTO: ANIMATED2D"
        print "------------------------"
        print "Use NUMPAD arrowkeys to control animation."
        print "Hover Mouse over animation bar, to jump to that location!"
        print speed
        self.anim = matplotlib.animation.FuncAnimation(pylab2da, animate, frames=Z.shape[0]-1, interval=speed, blit=False)
        if save:
            self.anim.save(save, fps=fps, codec="mpeg4")
        return pylab2da
    def quicklook(self,prods=False,cb=False,mask=False,bins=50):
        """
        This routine creates a quicklook of all available data products
        INPUT:
        prods: List of Products to be plotted
        cb: a string for the colorbar - The colrbar is only plotted if a non empty string is passed
        mask: a string of the mask used for quicklook - if False the Master mask is used
        bins: maximum number of bins for histogram plotting

        """
        if prods:
            pass
        else:
            prods = self.db.data.keys()
        N = len(prods)
        pylabql = pylab.figure(figsize=(N, N+1))
        pylab.subplots_adjust(hspace=0, wspace=0)
        pC = 0
        print "Processing Data"
        for yN, ykey in enumerate(prods):
            for xN, xkey in enumerate(prods):
                pC += 1
                loading_bar(N*N, pC, ">")
                ax = pylabql.add_subplot(N+1, N, pC)
                if pC <= N:
                    ax.xaxis.set_major_locator(matplotlib.ticker.MaxNLocator(nbins=10, prune='both'))
                    ax.xaxis.set_ticks_position('top')
                    ax.xaxis.set_label_position('top')
                    for tick in ax.xaxis.get_ticklabels():
                        tick.set_rotation('vertical')
                        tick.set_size(6)

                else:
                    ax.xaxis.set_ticklabels([])
                    ax.xaxis.set_major_locator(matplotlib.ticker.MaxNLocator(nbins=10, prune='both'))
                if N-xN == N:
                    ax.yaxis.set_major_locator(matplotlib.ticker.MaxNLocator(nbins=10, prune='both'))
                    for tick in ax.yaxis.get_ticklabels():
                        tick.set_size(6)
                elif xN+1 == N and not cb:
                    ax.yaxis.set_major_locator(matplotlib.ticker.MaxNLocator(nbins=10, prune='both'))
                    ax.yaxis.set_ticks_position('right')
                    ax.yaxis.set_label_position('right')
                    for tick in ax.yaxis.get_ticklabels():
                        tick.set_size(6)
                else:
                    ax.yaxis.set_ticklabels([])
                    ax.yaxis.set_major_locator(matplotlib.ticker.MaxNLocator(nbins=10, prune='both'))
                if mask:
                    valx = self.db.data[xkey][self.db.get_mask(mask)]
                    valy = self.db.data[ykey][self.db.get_mask(mask)]
                else:
                    valx = self.db.data[xkey][self.db.DM()]
                    valy = self.db.data[ykey][self.db.DM()]
                try:
                    binx, biny = bins, bins
                    if alltrue(valx%1 == 0):
                        Nbins = np.amax(valx)-np.amin(valx)+2
                        if Nbins > bins:
                            Nbins = bins
                        binx = linspace(np.amin(valx), np.amax(valx)+1, Nbins)
                    if alltrue(valy%1 == 0):
                        Nbins = np.amax(valy)-np.amin(valy)+2
                        if Nbins > bins:
                            Nbins = bins
                        biny = linspace(np.amin(valy), np.amax(valy)+1, Nbins)
                    C, X, Y = histogram2d(valx, valy, bins=(binx, biny))
                    C = 1.*C
                    C = C/sum(C)
                    colormap = pylab.cm.get_cmap(self.db.dp[ykey].get("contourcolor"), 1024)
                    if yN < xN:
                        ax.pcolormesh(X, Y, C.T, cmap=colormap, vmin=np.amin(C[C > 0]), vmax=np.amax(C))
                        ax.xaxis.grid(True, ls="solid")
                        ax.yaxis.grid(True, ls="solid")
                    elif yN == xN:
                        ax.text(0.5, 0.5, self.db.dp[xkey].get("name"), horizontalalignment='center', verticalalignment="center", transform=ax.transAxes, backgroundcolor=self.db.dp[xkey].get("color"), color="white")
                    else:
                        pass
                except:
                    pass
                colormap.set_under('white', 0)
                ax.set_xlim(np.amin(X), np.amax(X))
                ax.set_ylim(np.amin(Y), np.amax(Y))
                if pC >= N**2-N:
                    ax = pylabql.add_subplot(N+1, N, pC+N)
                    ax.xaxis.set_major_locator(matplotlib.ticker.MaxNLocator(nbins=10, prune='both'))
                    for tick in ax.xaxis.get_ticklabels():
                        tick.set_rotation('vertical')
                        tick.set_size(6)
                    ax.yaxis.set_ticklabels([])
                    ax.plot(X[:-1], sum(C, axis=1), color=self.db.dp[xkey].get("color"), lw = self.db.dp[xkey].get("linewidth"), ls = "steps"+self.db.dp[xkey].get("linestyle"), marker=self.db.dp[xkey].get("marker"), markersize=self.db.dp[xkey].get("markersize"))
        if cb:
            axcb = pylab.axes([0.9, 0.1, 0.02, 0.8])
            cb1 = matplotlib.colorbar.ColorbarBase(axcb, cmap=colormap, orientation="vertical")
            cb1.set_label("%s"%(cb))
