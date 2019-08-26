# -*- coding: utf-8 -*-
"""
Created on Mon Jan  8 15:19:55 2018

@author: fischer
"""

2923/1: from uswipha import uswipha
2923/2: uswipha?
2923/3: d = uswipha()
2923/4: d = uswipha(tf="all")
2923/5: d = uswipha(year=[1992,1993],tf=[[1,10]])
2923/6: d.data
2923/7: d.data["doy"].shape
2923/8: d.sync_swoops()
2923/9: d.data
2924/1: from uswo import uswo
2924/2: d = uswo(year=[1992],tf=[[1,10]])
2924/3: d = uswo(year=[1992],tf=[[1,365]])
2925/1: d = uswo(year=[1992],tf=[[1,3]])
2925/2: from uswo import uswo
2925/3: d = uswo(year=[1992],tf=[[1,3]])
2926/1: from uswo import uswo
2926/2: d = uswo(year=[1992],tf=[[1,3]])
2926/3: %debug
2926/4: from uswo import uswo
2926/5: d = uswo(year=[1992],tf=[[1,3]])
2927/1: from uswo import uswo
2927/2: d = uswo(year=[1992],tf=[[1,3]])
2928/1: from uswo import uswo
2928/2: d = uswo(year=[1992],tf=[[1,3]])
2929/1: from uswo import uswo
2929/2: d = uswo(year=[1992],tf=[[1,3]])
2930/1: from uswipha import uswipha
2930/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
2930/3: d.sync_swoops()
2930/4: d.data
2931/1: from uswipha import uswipha
2931/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
2932/1: from uswipha import uswipha
2932/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
2932/3: d = uswipha(year=[1992,1993],tf=[[1,10]],path="/data/etph/Ulysses/swics/pha")
2932/4: d = uswipha(year=[1992,1993],tf=[[1,10]],path="/data/etph/Ulysses/swics/pha/")
2932/5: d.sync_swoops()
2933/1: from uswipha import uswipha
2933/2: d = uswipha(year=[1992,1993],tf=[[1,10]],path="/data/etph/Ulysses/swics/pha/")
2933/3: d.sync_swoops()
2933/4: d.data
2933/5: d.hist2d("tch","ech")
2933/6: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,1024))
2933/7: d.set_mask("rng",0,0)
2933/8: d.set_mask("rng0","rng",0,0)
2933/9: d.add_data("rng0")
2933/10: d.add_mask("rng0")
2933/11: d.set_mask("rng0","rng",0,0)
2933/12: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,1024))
2933/13: d.add_mask("rng1")
2933/14: d.add_mask("rng2")
2933/15: d.set_mask("rng1","rng",1,1)
2933/16: d.set_mask("rng2","rng",2,2)
2933/17: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,1024))
2933/18: pylab.close('all')
2933/19: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
2933/20: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200))
2933/21: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=["Master","rng0","rng1"])
2933/22: pylab.close('all')
2933/23: d.add_mask("rng3")
2933/24: d.set_mask("rng3","rng",3,3)
2933/25: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
2933/26: unique(d.data["rng"]))
2933/27: unique(d.data["rng"])
2933/28: d.remove_mask("rng3")
2933/29: d.hist1d("tch",binx=arange(0,1024),smask=["rng2"])
2933/30: d.hist1d("tch",binx=arange(0,1025),smask=["rng2"])
2933/31: d.hist1d("tch",binx=arange(0,1000),smask=["rng2"])
2933/32: d.hist1d("tch",bin=arange(0,1000),smask=["rng0"])
2933/33: d.hist1d("tch",binx=arange(0,1000),smask=["rng0"])
2933/34: pylab.close('all')
2933/35: d.animate2d("tch","ech",prodz="epq",binx=arange(0,1024),biny=arange(1,200),binz="arange(0,60),smask=["Master","rng0","rng1"])
2933/36: d.animate2d("tch","ech",prodz="epq",binx=arange(0,1024),biny=arange(1,200),binz=arange(0,60),smask=["Master","rng0","rng1"])
2933/37: d.hist2d("tch","epq",binx=arange(200,700),biny=arange(0,60))
2933/38: d.show_mask()
2933/39: d.set_mask("master","vsw",300,400)
2933/40: d.set_mask("master","vsw",300,400)
2933/41: d.set_mask("Master","vsw",300,400)
2933/42: d.show_mask()
2933/43: d.set_mask("Master","vsw",600,700))
2933/44: d.set_mask("Master","vsw",600,700)
2933/45: d.show_mask()
2933/46: d.set_mask("Master","vsw",600,700,reset=True)
2933/47: d.show_mask()
2933/48: d.quicklook()
2933/49: d.hist2d("tch","epq",binx=arange(200,700),biny=arange(0,60))
2933/50: pylab.close('all')
2933/51: d = uswipha(year=[1992,1993],tf=[[1,40]],path="/data/etph/Ulysses/swics/pha/")
2933/52: d.sync_swoops()
2933/53: d.hist2d("tch","epq",binx=arange(200,700),biny=arange(0,60))
2933/54: d.hist2d("tch","epq",binx=arange(200,700),biny=arange(0,60),norm="ymax")
2933/55: d.hist1d("tch",binx=arange(200,700))
2933/56: d.set_mask("Master","epq",32,32)
2933/57: d.hist1d("tch",binx=arange(200,700)