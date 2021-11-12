#{{{ Documentation and module imports
"""
Date: 23.01.2015
Author: Christian Drews <drews@physik.uni-kiel.de>, Lars Berger <berger@physik.uni-kiel.de>

"""
from numpy import greater_equal, greater, less_equal, less, not_equal, ndarray
from _mask import mask2D
#}}}
class mask2D(object):
    def __init__(self,dbData,mask,prodx,prody):
        """
        INPUT ###
        dbData: instance of dbData
        prodx: xval for the 2D mask
        prody: yval for the 2D mask
        """
        self.db = dbData
        self.mask = mask
        self.prodx = prodx
        self.prody = prody
        self.M2D = []
        self.state = "NOT APPLIED"
    def _draw(self):
        for patch in self.P.fig.gca().patches: patch.remove()
        self.P.fig.gca().add_patch(matplotlib.patches.Polygon(self.M2D,facecolor="red",alpha=0.5,fill=True))
        self.P.update()
    def _enter(self,event):
        xd,yd = event.xdata,event.ydata
        if event.key=="enter":
            print "Processing Filter %s/%s on mask %s - Please Wait"%(self.prodx,self.prody,self.mask)
            self.db.set_mask(self.mask,"MASK2D %s/%s"%(self.prodx,self.prody),self.M2D,op="m2d")
            print "Processing finished - Filter applied!"
            self.P.fig.gca().set_title("Mask2D of '%s'/'%s' on mask '%s' (Applied)"%(self.prodx,self.prody,self.mask),backgroundcolor="green")
            self.P.fig.canvas.mpl_disconnect(self.C2)
            self.P.update()
            self.state="APPLIED"
        elif event.key=="a":
            self.M2D.append((xd,yd))
            self._draw()
        elif event.key=="r":
            self.M2D.pop()
            self._draw()
        elif event.key=="c":
            self.P.fig.canvas.mpl_disconnect(self.C2)
            self.P.update()
        else:
            pass
    def create_mask2D(self,**kwargs):
        """
        Thos routine takes the same **kwargs as hist2d from dbData class
        """
        self.P = self.db.hist2d(self.prodx,self.prody,smask=[self.mask],**kwargs)
        self.P.fig.gca().set_title("Mask2D of '%s'/'%s' on mask '%s' (NOT APPLIED)"%(self.prodx,self.prody,self.mask),backgroundcolor="red")
        self.C2=self.P.fig.canvas.mpl_connect('key_press_event',lambda event: self._enter(event))
    @staticmethod
    def op(data, M2D):
        """
        This operator returns a 2D mask on data according to the points contained in M2D
        """
        pX = data[0]
        pY = data[1]
        try:
            return matplotlib.nxutils.points_inside_poly(array((pX,pY)).T,M2D)
        except:
            P = matplotlib.path.Path(array(M2D))
            return P.contains_points(array([pX,pY]).T)
    
