from Gnuplot import Data

def cutsx(a, b, c):
    """ Returns the intersection parameter t of the ray (0, c)+t*(1,0) (t \in \R) and the straight track between
    a and b in positive direction. If there is no intersection, it returns None. """
    # a+m*(b-a) == (0,c)+t*(1,0)
    # =>
    m=(c-a[1])/(b[1]-a[1])
    if m<0 or m>1:
        return None
    t=a[0]+m*(b[0]-a[0])
    return t

def cutsy(a, b, c):
    """ Returns the intersection parameter t of the ray (c, 0)+t*(0,1) (t \in \R) and the straight track between
    a and b in positive direction. If there is no intersection, it returns None. """
    # a+m*(b-a) == (c,0)+t*(0,1)
    # =>
    m=(c-a[0])/(b[0]-a[0])
    if m<0 or m>1:
        return None
    t=a[1]+m*(b[1]-a[1])
    return t

class PolySelect:
    """ To select polygonal areas on a plot and filter data through the selection. """
    def __init__(self, gp):
        self.gp=gp

    def select(self):
        """ Start interactive polygonal area selection. Please make sure that
        the lines do NOT cross. """
        gp=self.gp

        # fix ranges so that the plot does not move while drawing the polygon
        xr=gp.getXrange()
        yr=gp.getYrange()
        gp.setXrange(xr)
        gp.setYrange(yr)

        poly=[]
        while True:
            p=gp.getxy()
            if gp.eval("MOUSE_KEY")==3:
                break
            poly.append(p)
            if len(poly)>1:
                gp._remove_last_from_queue()
            d=Data(poly)
            d.set_option(with="lines")
            gp.replot(d)
        if len(p):
            gp._remove_last_from_queue()
        gp.replot()
        self.poly=poly
        return poly

    def __contains__(self, point):
        """ Returns if the point 'point' (a 2-tuple) is contained in the last selected polygon. """
        # FIXME: This is O(|poly|) and therefore quite slow!
        poly=self.poly

        n=0 # number of cuts

        # FIXME: *corner*cases still not properly handled!
        for p1,p2 in zip(poly, poly[1:]+poly[:1]):
            c=cutsx(p1, p2, point[1])
            if c!=None and c<point[0]:
                n+=1
        return n%2

    def giveGrid(self, nx=100, ny=100):
        """ Gives a list of points inside the selected polygon and visible in the current GNUplot viewport.
        'nx' and 'ny' specify the number of points in X and Y direction. """
        from numpy import arange
        xr=self.gp.getXrange()
        yr=self.gp.getYrange()

        return [(x,y)
                for x in arange(xr[0], xr[1], (xr[1]-xr[0])/nx)
                for y in arange(yr[0], yr[1], (yr[1]-yr[0])/ny)
                if (x,y) in self]

