#{{{ Documentation and module imports
"""
Date: 27.04.2015
Authors: Christian Drews <drews@physik.uni-kiel.de>,
		 Lars Berger <berger@physik.uni-kiel.de>
		 Jan Steinhagen <steinhagen@physik.uni-kiel.de>

"""
import numpy as np
import matplotlib as mpl
#}}}


class Mask2D(object):

    """
    Class that is used for 2 dimensional masks
    """

    def __init__(self, dbData, mask, prodx, prody):
        """
        INPUT ###
        dbData: instance of dbData
        prodx: xval for the 2D mask
        prody: yval for the 2D mask
        """
        self.dbd = dbData
        self.mask = mask
        self.prodx = prodx
        self.prody = prody
        self.m2d = []
        self.state = "NOT APPLIED"
        self.canv = None
        self.pmod = None

    def _draw(self):
        """
        Method: Updates the plotted polygon
        """
        for patch in self.pmod.fig.gca().patches:
            patch.remove()
        self.pmod.fig.gca().add_patch(
            mpl.patches.Polygon(self.m2d, facecolor="red", alpha=0.5, fill=True))
        self.pmod.update()

    def _enter(self, event):
        """
        Method: Event handler / Events are add and remove points to the polygon and apply the mask to the data
        """
        xd, yd = event.xdata, event.ydata
        if event.key == "enter":
            print "Processing Filter %s/%s on mask %s - Please Wait" % (self.prodx, self.prody, self.mask)
            self.dbd.set_mask(self.mask, self.prodx, self.prody, self.m2d,
                              op=mask2d_op, set_custom_prod="MASK2D %s/%s" % (self.prodx, self.prody))
            print "Processing finished - Filter applied!"
            self.pmod.fig.gca().set_title("Mask2D of '%s'/'%s' on mask '%s' (Applied)" %
                                          (self.prodx, self.prody, self.mask), backgroundcolor="green")
            self.pmod.fig.canvas.mpl_disconnect(self.canv)
            self.pmod.update()
            self.state = "APPLIED"
        elif event.key == "a":
            self.m2d.append((xd, yd))
            self._draw()
        elif event.key == "r":
            if self.m2d:
                self.m2d.pop()
                if self.m2d:
                    self._draw()
        elif event.key == "c":
            self.pmod.fig.canvas.mpl_disconnect(self.canv)
            self.pmod.update()
        else:
            pass

    def create_mask2D(self, *args, **kwargs):
        """
        This routine takes the same **kwargs as hist2d from dbData class
        """
        if kwargs.has_key("cb"):
            kwargs.pop("cb")
        self.pmod = self.dbd.hist2d(
            self.prodx, self.prody, smask=[self.mask], **kwargs)
        self.pmod.fig.gca().set_title("Mask2D of '%s'/'%s' on mask '%s' (NOT APPLIED)" %
                                      (self.prodx, self.prody, self.mask), backgroundcolor="red")
        self.canv = self.pmod.fig.canvas.mpl_connect(
            'key_press_event', lambda event: self._enter(event))


def mask2d_op(datadict, key_1, key_2, m2d, *args, **kwargs):
    """
    This operator returns a 2D mask on data according to the points contained in m2d
    """
    pX = datadict[key_1]
    pY = datadict[key_2]
    try:
        return mpl.nxutils.points_inside_poly(np.array((pX, pY)).T, m2d)
    except:
        path = mpl.path.Path(np.array(m2d))
        return path.contains_points(np.array([pX, pY]).T)
