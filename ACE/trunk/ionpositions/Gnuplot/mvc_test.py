from Gnuplot.mvc import *
pl=Plot()
l=[1,2,3,4,5,6,7,8]
lv=listView(l)
l2=[(1.0, 1.0, 2.0),
    (2.0, 2.0, 2.0),
    (3.0, 2.0, 1.0),
    (4.0, 2.0, 0.5)]
lv2=listView(l2, "xyey")

class DrawLine(listView):
    def __init__(self):
        listView.__init__(self, [], "xy")
    def mouseclick(self, x, y, btn):
        self.l+=[(x, y)]
        self.changed()
        
dl=DrawLine()
#pl.update()
pl.add(lv)
pl.add(lv2)
pl.add(dl)
#pl.update()
pu=PlotUpdater(pl)
pu.start()
