# -*- coding: utf-8 -*-
"""
Created on Mon Jul 23 17:16:24 2018

@author: fischer
"""

12/1: from uswipha import uswipha
12/4: from numpy import arange
12/5: d = uswipha(year=[1992,1995],tf=[[1,150]]) #nur zwei Jahre!
12/6: d.sync_swoops()
12/7: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
12/8: d.show_mask()
12/9: pylab.close('all')
12/10: d.data
12/11: d.hist2d('tch','epq',binx=arange(0,1024),biny = arange(0,64))
12/12: pylab.close('all')
12/13: d.hist2d('tch','epq',binx=arange(0,1024),biny = arange(0,64),norm="ymax")
12/14: d.hist2d('tch','epq',binx=arange(200,1024),biny = arange(0,64),norm="ymax")
12/19: d.set_mask("Master","wHe+",1.1,10,reset=True)
12/20: d.hist2d('tch','epq',binx=arange(200,1024),biny = arange(0,64),norm="ymax")
12/21: ls
12/22: d.data
12/23: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/24: d.set_mask("Master","year",1993,1995)
12/25: d.set_mask("Master","year",1993,1995,reset=True)
12/26: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")


12/32: d.set_mask2D('Master','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/33: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/34: d.hist1d('wHe+',binx=arange(1.,5.,.1))
12/35: pylab.close('all')
12/36: d.data
12/37: d.hist1d('wHe+',binx=arange(1.,5.,.1))
12/40: d.set_mask("Master","ech",1,200,reset=True) % Doubles rausnehmen
12/43: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4))
12/44: pylab.close('all')
12/45: d.show_mask()
12/47: d.remove_submask('Master',"MASK2D tch/epq")
12/48: d.show_mask()
12/49: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/50: d.add_mask("He+")
12/51: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/52: d.show_mask()
12/53: d.remove_submask('Master',"ech")
12/54: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/55: d.set_mask("Master","ech",1,200,reset=True)
12/56: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4))
12/57: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax")
12/58: d.set_mask("Master","wHe+",1.2,10,reset=True)
12/59: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax")
12/60: pylab.close('all')
12/61: d.data
12/62: d.animate2d('wHe+','det',prodz="rau",binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax",binz=arange(1.3,5.,.1))
12/63: pylab.close('all')
12/64: d.animate2d('wHe+','det',prodz="rau",binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax",binz=arange(1.3,5.,.1))
12/65: d.show_mask()
12/66: d.animate2d('wHe+','det',prodz="rau",binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax",binz=arange(1.3,5.,.3))
12/67: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax")
12/68: d.hist2d('sec','det',binx=arange(0.,10,,1.),biny = arange(0,4),norm="ymax")
12/69: d.hist2d('sec','det',binx=arange(0.,10,1.),biny = arange(0,4),norm="ymax")
12/70: d.hist2d('rau','det',binx=arange(1.3,5,.1),biny = arange(0,4),norm="ymax")
12/71: d.data
12/72: pylab.close('all')
12/73: d.hist2d('rau','det',binx=arange(1.3,6,.1),biny = arange(0,4),norm="ymax")
   1: from uswipha import uswipha
   2: from numpy import arange
   3: d = uswipha(year=[1992,1995],tf=[[1,150]])
   4: d = uswipha(year=[1990,1991,1992,1993,1994,1995],tf=[[1,150]])
   5: d.hist1d('wHe+',binx=arange(1.,5.,.1))
   6: d.sync_swoops()
   7: d.sync_swoops?
   8: d.sync_swoops()
   9: d.sync_swoops()
  10: d.hist2d('rau','det',binx=arange(1.3,5,.1),biny = arange(0,4),norm="ymax")
  11: d.data
  12: %history -g
