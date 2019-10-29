#{{{ Documentation and module imports
"""
Date: 28.01.2015
Author: Christian Drews <drews@physik.uni-kiel.de>, Lars Berger <berger@physik.uni-kiel.de>
"""

import datetime
import numpy as np
import matplotlib as mpl
import pylab
# from numpy import *
import scipy
#}}}


class PlotMod(object):

    def __init__(self, pylabfig, style="STD"):
        """
        Init the plot modifier. This class is used to give the user a
        backend to modifiy plot created with dbData
        """
        self.fig = pylabfig
        self.style = style
        self.oldobj = self._process_fig()
        self.data = None
        self.CMouse = False

    def connect_mouse(self):
        """
        This routine connects Mouse clicks to the current active Canvas and prints them on Screen.
        If Mouse is already connected, connection is terminated
        """
        def _enter(event):
            try:
                MSG = datetime.datetime.now().strftime(
                    '%Y-%m-%d %H:%M:%S') + ": B:%d, (X, Y): (%f, %f)" % (event.button, event.xdata, event.ydata)
                print MSG
            except:
                pass
        if not self.CMouse:
            self.CMouse = True
            self.C = self.fig.canvas.mpl_connect(
                'button_press_event', lambda event: _enter(event))
        else:
            self.fig.canvas.mpl_disconnect(self.C)

    def _process_fig(self):
        """
        Internal routine for handling figure axis objects
        """
        self.axes = {}
        self.texts = {}
        self.lines = {}
        self.linelabels = {}
        self.objects = {}
        for a, axes in enumerate(self.fig.axes):
            self.axes["A%i" % a] = axes
            self.objects["A%i" % a] = {}
            self.texts["A%i" % a] = {}
            self.lines["A%i" % a] = {}
        for a, axes in enumerate(self.axes):
            for t, text in enumerate(self.axes[axes].texts):
                self.objects[axes]["T%i" % t] = text
                self.texts[axes]["T%i" % t] = text
        for a, axes in enumerate(self.axes):
            lines = self.axes[axes].lines
            for l, line in enumerate(lines):
                self.objects[axes]["L%i" % l] = line
                self.lines[axes]["L%i" % l] = line
        return self.objects

    def get_axis(self, keya):
        """
        Return the chosen axis.
        INPUT: keyword of the axis (Can be looked up with self.show_axes)
        """
        if keya in self.axes:
            return self.axes[keya]
        else:
            print "Can't find axis '%s'" % (keya)

    def get_object(self, keya, keyo):
        """
        Return the choses object.
        INPUT: keya: keyword of the axis (Can be looked up with self.show_axes)
        keyt: keyword of the object (Can be looked up with self.show_axes)
        """
        if keya in self.objects:
            if keyo in self.objects[keya]:
                return self.objects[keya][keyo]
            else:
                print "Can't find object %s in axis '%s'" % (keya, keyo)
        else:
            print "Can't find axis '%s'" % (keya)

    def del_object(self, keya, keyo):
        """
        Return the choses object.
        INPUT: keya: keyword of the axis (Can be looked up with self.show_axes)
        keyt: keyword of the object (Can be looked up with self.show_axes)
        """
        self.get_object(keya, keyo).remove()
        self._process_fig()

    def set_fontsize(self, size):
        """
        Set all labels to the given fontsize
        """
        mpl.rcParams.update({'font.size': size})

    def show_axes(self):
        """
        This routine shows all available axes with all printed labels in it.
        """
        self._process_fig()
        print "Available Axes to modify on plot %s:" % (self.style)
        print "|"
        for keya in sorted(self.axes.keys()):
            print "Axis %s:" % (keya)
            print "---------"
            print "   | Labels"
            for keyt in sorted(self.texts[keya].keys()):
                text = self.objects[keya][keyt].get_text()
                print "   ----> %s: '%s'" % (keyt, text)
            print "   | Lines"
            for keyl in sorted(self.lines[keya].keys()):
                linec = self.objects[keya][keyl].get_color()
                lineds = self.objects[keya][keyl].get_drawstyle()
                linels = self.objects[keya][keyl].get_linestyle()
                print "   ----> %s: ls='%s', ds='%s', c='%s'" % (keyl, linels, lineds, linec)

    def set_line(self, *arg, **kwarg):
        """
        This routine plots lines onto the given axes. It is used just like the normal
        matplotlib plot command.
        INPUT: arg and kwarg can be the same arguments you would give to pylab.plot
        kwarg may contain one additional keyword 'axes',
        which may be a list axes keys or an axis key string. If this keyword is not given,
        lineplot is performed on all axis
        """
        if "axes" in kwarg:
            if isinstance(kwarg["axes"], str):
                Axes = [kwarg["axes"]]
            else:
                Axes = kwarg["axes"]
            kwarg.pop("axes")
        else:
            Axes = self.axes.keys()
        for A in Axes:
            xl = self.axes[A].get_xlim()
            yl = self.axes[A].get_ylim()
            self.axes[A].plot(*arg, **kwarg)
            self.axes[A].set_xlim(xl)
            self.axes[A].set_ylim(yl)
        self.update()

    def set_text(self, *arg, **kwarg):
        """
        This routine plots text onto the given axes. It is used just like the normal
        matplotlib text command.
        INPUT: arg and kwarg can be the same arguments you would give to pylab.plot
        kwarg may contain one additional keyword 'axes',
        which may be a list axes keys or an axis key string. If this keyword is not given,
        lineplot is performed on all axis
        """
        if "axes" in kwarg:
            if isinstance(kwarg["axes"], str):
                Axes = [kwarg["axes"]]
            else:
                Axes = kwarg["axes"]
            kwarg.pop("axes")
        else:
            Axes = self.axes.keys()
        for A in Axes:
            self.axes[A].text(*arg, **kwarg)
        self.update()

    def reset(self):
        """
        This method resets the whole figure to its original state
        """
        for ax in self.axes:
            for o in self.objects[ax]:
                if not self.objects[ax][o] in self.oldobj[ax].values():
                    self.del_object(ax, o)
        self._process_fig()
        self.update()

    def update(self):
        """
        Updates the plot
        """
        self.fig.show()

    def set_data(self, data):
        """
        Sets the corresponding plot_data object
        """
        self.data = data

    def get_data(self):
        """
        Returns the corresponding plot_data object, if it was added, else None
        """
        return self.data

    def fit_peak1d(self, mask, lim1, lim2, fun, starts, sigma=None, plotit=True, showres=True, setmax=True, resname=False):  # Umschreiben fuer f(p,x)
        """
        This routine fits a function to the data displayed in a two-dimensional plot (y=f(x)).
        INPUT: The mask(string) for which the data shall be fitted. lim1 and lim2(float) represent the lower and upper limit of the x area to fit.
        fun is the model function. It must have the form f(parameters,x), where parameters is a list. starts is a list with a guess of the function parameters.
        plotit=True/False states if the fitted function shall be displayed in the current plot. showres=True/False states if the residual shall be plotted.
        If setmax=True the starting value of the first parameter is set to the maximum value of the fit area. sigma is the standard deviation of the data.
        resname is the key, with that the data can be adressed in the plot_mod object.
        RETURNS the optimal set of parameters and the covariance matrix.
        """
        plotdata = self.get_data()
        ydat, xdat = plotdata.get_data()[mask]
        if len(xdat) != len(ydat):
            xdat = xdat[0:-1]
        x = xdat[(xdat > lim1) * (xdat < lim2)]
        y = ydat[(xdat > lim1) * (xdat < lim2)]
        args = (x, y)
        if sigma == None:
            lsqr = lambda paras, xdata, ydata: ydata - fun(paras, xdata)
        else:
            sigma = sigma[(xdat > lim1) * (xdat < lim2)]
            sigma[sigma <= 0] = 1
            lsqr = lambda paras, xdata, ydata, weights: weights * \
                (ydata - fun(paras, xdata))
            args += (1.0 / np.asarray(sigma), )
        if setmax == True:
            starts[0] = np.amax(ydat)
        args = scipy.optimize.leastsq(
            lsqr, starts, args=args, maxfev=100000, full_output=1)
        res = args[0]
        pcov = args[1]
        yfit = fun(res, x)   # get predicted observations/calc errors
        SSE = np.sum((y - yfit)**2)
        sig2 = SSE / (len(y) - len(res))
        try:
            ecov = sig2 * pcov
        except TypeError:
            ecov = None
        if plotit == True:
            self.set_line(xdat, fun(res, xdat), label="Fit")
            if showres == True:
                self.set_line(
                    xdat, ydat - fun(res, xdat), ls="steps-post", label="Residual")
                if resname:
                    self.data.add_data(resname, (ydat - fun(res, xdat), xdat))
            self.update()
        return res, ecov

    def fit_peak1d_spares(self, mask, lims, fun, starts, sigma=None, plotit=True, showres=True, setmax=True, resname=False, addargs=False):
        """
        This routine fits a function to the data displayed in a two-dimensional plot (y=f(x)).
        INPUT: The mask(string) for which the data shall be fitted. lims is list of lists, where the fit area can be specified.
        fun is the model function. It must have the form f(parameters,x), where parameters is a list. starts is a list with a guess of the function parameters.
        plotit=True/False states if the fitted function shall be displayed in the current plot. showres=True/False states if the residual shall be plotted.
        If setmax=True the starting value of the first parameter is set to the maximum value of the fit area. sigma is the standard deviation of the data. resname is the key,
        with that the data can be adressed in the plot_mod object. Addargs is a tuple of additional arguments for the function.
        RETURNS the optimal set of parameters and the covariance matrix.
        """
        plotdata = self.get_data()
        ydat, xdat = plotdata.get_data()[mask]
        if len(xdat) != len(ydat):
            xdat = xdat[0:-1]
        mask2 = False
        for l in lims:
            mask2 += (xdat > l[0]) * (xdat < l[1])

        x = xdat[mask2]
        y = ydat[mask2]
        args = (x, y)
        if sigma == None:
            lsqr = lambda paras, xdata, ydata: ydata - fun(paras, xdata)
        else:
            sigma = sigma[mask2]
            sigma[sigma <= 0] = 1
            lsqr = lambda paras, xdata, ydata, weights: weights * \
                (ydata - fun(paras, xdata))
            args += (1.0 / np.asarray(sigma), )
        if addargs and sigma == None:
            lsqr = lambda paras, xdata, ydata, adds: ydata - \
                fun(paras, xdata, adds)
            args += addargs
        elif addargs:
            lsqr = lambda paras, xdata, ydata, weights, adds: weights * \
                (ydata - fun(paras, xdata, adds))
            args += addargs
        if setmax == True:
            starts[0] = np.amax(ydat)
        args = scipy.optimize.leastsq(
            lsqr, starts, args=args, maxfev=100000, full_output=1)
        res = args[0]
        pcov = args[1]
        if addargs:
            yfit = fun(res, x, addargs[0])
                       # get predicted observations/calc errors
        else:
            yfit = fun(res, x)
        SSE = np.sum((y - yfit)**2)
        sig2 = SSE / (len(y) - len(res))
        try:
            ecov = sig2 * pcov
        except TypeError:
            ecov = None
        if plotit == True:
            if addargs:
                self.set_line(xdat, fun(res, xdat, addargs[0]), label="Fit")
            else:
                self.set_line(xdat, fun(res, xdat), label="Fit")
            if showres == True:
                if addargs:
                    self.set_line(
                        xdat, ydat - fun(res, xdat, addargs[0]), ls="steps-post", label="Residual")
                else:
                    self.set_line(
                        xdat, ydat - fun(res, xdat), ls="steps-post", label="Residual")
                if resname:
                    if addargs:
                        self.data.add_data(
                            resname, (ydat - fun(res, xdat, addargs[0]), xdat))
                    else:
                        self.data.add_data(
                            resname, (ydat - fun(res, xdat), xdat))
            self.update()
        return res, ecov

    def fit_peak2d(self, mask, key1r, key2r, fun, starts, sigma=None, plotit=True, setmax=True, cb=False):  # ----> fun(parameter,x,y)
        """This routine can fit a distribution function to the data displayed in a three-dimensional plot (z=f(x,y)).
        INPUT: The mask(string) for which the data shall be fitted. key1r and key2r are lists containing the two limits of the xdata and ydata, respectively [lowerlimit,upperlimit].
        fun is a function of the form f(parameters,x,y), where parameters is a list. starts(list) is a guess for the parameters. If setmax=True the starting value of the first parameter is set
        to the maximum value of the fit area. sigma (len(sigma)=len(data in plot)) is the standard deviation of the data. cb states if a colorbar for the contour shall be plotted. It's not that beautiful...
        RETURNS the optimal set of parameters and the covariance matrix."""
        plotdata = self.get_data()
        hdat, xdat, ydat = plotdata.get_data()[mask]
        x = xdat[0:-1]
        y = ydat[0:-1]
        tempmaskx = (x > key1r[0]) * (x < key1r[1])
        tempmasky = (y > key2r[0]) * (y < key2r[1])
        x = x[tempmaskx]
        y = y[tempmasky]
        hdat = hdat[tempmaskx]
        hist = hdat[::, tempmasky]
        l = len(x)
        ygrid, xgrid = np.meshgrid(y, x)
        xg, yg = np.ravel(xgrid), np.ravel(ygrid)
        h = np.ravel(hist)
        args = (xg, yg, h)
        if sigma is None:
            lsqr = lambda paras, xdata, ydata, hdata: hdata - \
                fun(paras, xdata, ydata)
        else:
            sigma = sigma[tempmaskx]
            sigma = sigma[::, tempmasky]
            sigma = np.ravel(sigma)
            sigma[sigma == 0] = 1
            lsqr = lambda paras, xdata, ydata, hdata, weights: weights * \
                (hdata - fun(paras, xdata, ydata))
            args += (1.0 / np.asarray(sigma), )
        if setmax == True:
            starts[0] = np.amax(h)
        args = scipy.optimize.leastsq(
            lsqr, starts, args=args, maxfev=100000, ftol=1.e-6, full_output=1)
        res = args[0]
        pcov = args[1]
        hfit = fun(res, xg, yg)   # get predicted observations/calc errors
        SSE = np.sum((h - hfit)**2)
        sig2 = SSE / (len(h) - len(res))
        try:
            ecov = sig2 * pcov
        except TypeError:
            ecov = None
        if plotit == True:
            hfit = reshape(hfit, (l, -1))
            hfit = swapaxes(hfit, 0, 1)
            for i in self.axes:
                if "TO" in self.objects[i]:
                    lab = self.get_object(i, "T0")
                    if lab.get_text() == mask:
                        ax = self.get_axis(i)
                        ax.contour(x, y, hfit, 4, cmap=pylab.cm.RdYlBu)
            if cb == True:
                axcb = pylab.axes([0.127, 0.1, 0.02, 0.8])
                cb2 = mpl.colorbar.ColorbarBase(
                    axcb, cmap=pylab.cm.RdYlBu, orientation="vertical",)
            self.update()
        return res, ecov

    def smooth(self, mask, wl, bins):
        """
        Routine that smoothes the data in the plot. This means that for every bin the mean of the the neighboring bins is calculated.
        mask is the key of the data to be smoothed.
        wl stand for the windowlength. For example if the windowlength is 3, the mean of the bin and its direct lower and upper neighboring bins is calculated
        as the value of the bin.
        bins is the bin width of the original histogram to be smoothed.
        No return value, but the data is stored in the plot_data object with the key "smooth".
        """
        counts, data = self.get_data().get_data()[mask]
        data = data[0:-1]
        newcounts = []
        if wl % 2 == 0:
            for i in np.arange(wl / 2 - 1, len(counts) - wl / 2 - 1):
                newcounts.append(
                    np.sum(counts[(i - wl / 2 + 1):i + wl / 2 + 1]))
                newcounts.append(np.sum(counts[len(counts) - wl / 2 - 1::]))
                newdata = data[(wl / 2 - 1):(-wl / 2)] + bins / 2.
        else:
            for i in np.arange(wl / 2, len(counts) - wl / 2 - 1):
                newcounts.append(np.sum(counts[(i - wl / 2):i + wl / 2 + 1]))
                newcounts.append(float(np.sum(counts[-wl::])))
                newdata = data[(wl / 2):(-wl / 2 + 1)]
        res = (np.array(newcounts) / float(wl), newdata)
        self.get_data().add_data("smooth", res)
        self.set_line(res[1], res[0], ls="steps-post", label="Smoothed data")
        return
