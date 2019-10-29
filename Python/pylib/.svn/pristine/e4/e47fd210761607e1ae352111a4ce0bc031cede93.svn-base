#{{{ Documentation and module imports
"""
Date: 27.04.2015
Author: Christian Drews <drews@physik.uni-kiel.de>,
		Lars Berger <berger@physik.uni-kiel.de>
		Jan Steinhagen <steinhagen@physik.uni-kiel.de>

"""
#}}}


class Mask1D(object):

    """
    Class that is used for custom 1 dimensional masks (e.g. to selcect certain periods by 'clicking')
    """

    def __init__(self, dbData, mask, prodx, prody):
        """
        INPUT ###
        dbData: instance of dbData
        prodx: xval for the 1D mask
        prody: prodys used for the timeseries plot
        """
        self.dbd = dbData
        self.mask = mask
        self.prodx = prodx
        self.prody = prody
        self.pX = self.dbd.data[self.prodx]
        self.m1d = []
        self.state = "NOT APPLIED"
        self.button_state = "SPOINT"
        self.canv = None
        self.pmod = None

    def create_mask1D(self, *args, **kwargs):
        """
        This routine takes the same **kwargs as timeseries from dbData class
        """
        self.pmod = self.dbd.timeseries(
            self.prody, prodx=self.prodx, smask=[self.mask], **kwargs)
        self.pmod.fig.axes[0].set_title(
            "Mask1D of '%s' on mask '%s' (NOT APPLIED)" % (self.prodx, self.mask), backgroundcolor="red")
        self.canv = self.pmod.fig.canvas.mpl_connect(
            'key_press_event', lambda event: self._enter(event))

    def _enter(self, event):
        """
        Method: Event handler / Events are add and remove points to the polygon and apply the mask to the data
        """
        xd, yd = event.xdata, event.ydata
        if event.key == "enter":
            print "Processing Filter %s on mask %s - Please Wait" % (self.prodx, self.mask)
            for xlims in self.m1d:
                self.dbd.set_mask(self.mask, self.prodx, xlims[0], xlims[1])
                print "Processing finished - Filter applied!"
                self.pmod.fig.axes[0].set_title(
                    "Mask1D of '%s' on mask '%s' (Applied)" % (self.prodx, self.mask), backgroundcolor="green")
                self.pmod.fig.canvas.mpl_disconnect(self.canv)
                self.pmod.update()
                self.state = "APPLIED"
        elif event.key == "y" and self.button_state == "SPOINT":
            self.m1d.append([xd])
            self.button_state = "EPOINT"
        elif event.key == "x" and self.button_state == "EPOINT" and xd > self.m1d[-1][0]:
            self.m1d[-1].append(xd)
            self._draw()
            self.button_state = "SPOINT"
        elif event.key == "v":
            if self.m1d:
                self.m1d.pop()
            self._draw()
        elif event.key == "c":
            self.pmod.fig.canvas.mpl_disconnect(self.canv)
            self.pmod.update()
        else:
            pass

    def _clear(self):
        """
        Method: Resets path and updates plot.
        """
        for ax in self.pmod.fig.axes:
            ax.patches = []
            self.pmod.update()

    def _draw(self):
        """
        Method: Updates the plotted polygon
        """
        self._clear()
        for ax in self.pmod.fig.axes:
            for xlims in self.m1d:
                ax.axvspan(xlims[0], xlims[1], facecolor="blue", alpha=0.3)
            self.pmod.update()
