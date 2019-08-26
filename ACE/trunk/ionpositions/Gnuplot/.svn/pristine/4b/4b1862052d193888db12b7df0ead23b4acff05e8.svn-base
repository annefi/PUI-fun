# cares about minor items like arrows and rectangles (and whatever) on a GNUPlot


class GPItemsManager:
    def __init__(self, gp):
        self.gp=gp
        self.l=[]
        self.clear()

    def clear(self):
        """ Clears all items on the plot. """
        from copy import copy
        for i in copy(self.l):
            self.remove(i)

    def update(self): # update for dynamic items
        for i in self.l:
            i.update()

    def add(self, a):
        self.gp.sync() # to be sure that all variables are set etc.
        a.setManager(self, len(self.l)+1)
        self.l.append(a)

    def remove(self, a):
        if a.m!=self:
            raise Exception, "Wrong object, not managed by this."
        a.setManager(None, 0)
        self.l.remove(a)

class GPMinorItem:
    def __init__(self):
        # manager
        self.m=None
        # index of corresponding object in GNUplot
        self.index=None
        self.updaters=[]

    def setManager(self, newm, newindex):
        if self.m and newm:
            raise Exception, "Item is already connected to a GPItemsManager."
        if (not self.m) and (not newm):
            return # this is already done!
        if newm:
            self.index=newindex

        if self.m:
            if self.index!=None:
                self.removeFromPlot(self.m.gp)
            self.m=None
        else:
            self.m=newm
            if self.index!=None:
                self.addToPlot(self.m.gp)

    def update(self):
        for u in self.updaters:
            u(self)
        if self.index!=None:
            self.addToPlot(self.m.gp)

    def __del__(self):
        if self.m:
            self.m.remove(self)

def filterAuto(*a):
    r=[]
    for i in a:
        if i=="auto":
            r.append(0.0)
        else:
            r.append(i)
    return r


class Arrow(GPMinorItem):
    def __init__(self, x1, y1, x2, y2, opts=""):
       self.x1, self.y1, self.x2, self.y2=filterAuto(x1,y1,x2,y2)
       
       self.autoranges={"x1" : x1=="auto",
                        "y1" : y1=="auto",
                        "x2" : x2=="auto",
                        "y2" : y2=="auto"}
       self.opts=opts
       GPMinorItem.__init__(self)
       if sum(self.autoranges.values()):
           self.updaters.append(auto_range)
           

    def addToPlot(self, gp):
        gp("set arrow %d from %f, %f to %f, %f %s" % (self.index, self.x1, self.y1, self.x2, self.y2, self.opts))

    def removeFromPlot(self, gp):
        gp("unset arrow %d" % self.index)

def auto_range(item):
    xra=item.m.gp.getXrange()
    yra=item.m.gp.getYrange()
    for k, v in item.autoranges.iteritems():
        if v:
            if k=="x1":
                item.x1=xra[0]
            elif k=="y1":
                item.y1=yra[0]
            elif k=="x2":
                item.x2=xra[1]
            elif k=="y2":
                item.y2=yra[1]

def VBar(x, opts="nohead"):
    return Arrow(x, "auto", x, "auto", opts)

def HBar(x, opts="nohead"):
    return Arrow("auto", y, "auto", y, opts)

class Rectangle(GPMinorItem):
   def __init__(self, x1, y1, x2, y2, opts=""):
       # FIXME: copy/paste
       self.x1, self.y1, self.x2, self.y2=filterAuto(x1,y1,x2,y2)
       
       self.autoranges={"x1" : x1=="auto",
                        "y1" : y1=="auto",
                        "x2" : x2=="auto",
                        "y2" : y2=="auto"}
       self.opts=opts
       GPMinorItem.__init__(self)
       if sum(self.autoranges.values()):
           self.updaters.append(auto_range)

   def addToPlot(self, gp):
       gp("set object %d rect from %f, %f to %f, %f %s" % (self.index, self.x1, self.y1, self.x2, self.y2, self.opts))

   def removeFromPlot(self, gp):
       gp("unset object %d" % self.index)


def ShadedArea(x1, y1, x2, y2,
               r, g, b, a=1.0):
    col="#%02x%02x%02x" % (int(r*255.0), int(g*255.0), int(b*255.0))

    return Rectangle(x1,y1,x2,y2,
                     'fc rgb "%s" fillstyle solid %f noborder' % (col, a))

def ShadedAreaS(x1, y1, x2, y2,
               col, a=1.0):
    return Rectangle(x1,y1,x2,y2,
                     'fc rgb "%s" fillstyle solid %f noborder' % (col, a))
