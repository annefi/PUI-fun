 2/1: from uswipha import uswipha
 3/1: from uswipha import uswipha
 3/2: d = uswipha(year=[1992,1993],tf=[[1,10]],path="/data/etph/Ulysses/swics/pha/")
 3/3: d = uswipha(year=[1992,1993],tf=[[1,10]])
 4/1: d
 3/4: d = uswipha(year=[1992,1993],tf=[[1,10]])
 3/5: d.data
 3/6: d.data['doy']
 3/7: d = uswipha(year=[1992],tf=[[1,10]])
 3/8: d.data
 3/9: len(d.data)
3/10: d.data['tf']
3/11: d = uswipha(year=[1992])
3/12: d = uswipha(year=[1992,1992],tf=[[1,10]])
3/13: len(d)
3/14: len(d.data)
3/15: len(d.data['ech'])
3/16: d = uswipha(year=[1992],tf=[[1,10]])
3/17: len(d.data['ech'])
3/18: len(d.data)
3/19: d = uswipha(year=[1992],tf=[[1,20]])
3/20: len(d.data)
3/21: len(d.data['ech'])
3/22: d = uswipha(year=[1992],tf=[[1,2]])
3/23: d = uswipha(year=[1992],tf=[[1,1]])
3/24: d = uswipha(year=[1992],tf=[[1,2]])
3/25: len(d.data['doy'])
3/26: len(d.data['epq'])
3/27: d.data['doy']
3/28: d = uswipha(year=[1992],tf=[[1,20]])
3/29: d.sync_swoops()
 5/1: d = uswipha(year=[1992],tf=[[1,50]])
 5/2: from uswipha import uswipha
 5/3: d = uswipha(year=[1992],tf=[[1,50]])
 5/4: d.sync_swoops()
 5/5: d.animated2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,,1),biny=arange(1,200,1),prodz=arange(60))
 5/6: d.animated2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,1),biny=arange(1,200,1),prodz=arange(60))
 5/7: d.animated2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,1),biny=arange(1,200,1),binz=arange(60))
 5/8: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,1),biny=arange(1,200,1),binz=arange(60))
 5/9: from numpy import arange
5/10: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,1),biny=arange(1,200,1),binz=arange(60))
5/11: show()
5/12: %pylab
5/13: ion()
5/14: show()
5/15: pylab.close("all")
5/16: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,1),biny=arange(1,200,1),binz=arange(60))
5/17: pylab.close("all")
5/18: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(60))
5/19: unique(d.data["epq"])
5/20: d.set_mask("Master","ech",0,0)
5/21: d.animate1d(prodx="tch",prodz="epq",binx=arange(100,500,2),binz=arange(60))
5/22: d.animate1d("tch",prodz="epq",binx=arange(100,500,2),binz=arange(60))
5/23: d.animate1d("tch",prodz="epq",binx=arange(100,500,2),binz=arange(10,60))
5/24: d.reset_mask("Master")
5/25: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
 6/1: from uswipha import uswipha
 6/2: d = uswipha(year=[1992],tf=[[1,50]])
 6/3: %history
 6/4: %history -g
 6/5: %history -o -f -g
 6/6: %history -o -g
 6/7: %history -o -g -f
 6/8: d = uswipha(year=[1992],tf=[[1,50]])
 6/9: d.sync_swoops()
6/10: a = arange(5)
6/11: from numpy import arange
6/12: a = arange(5)
6/13: a
6/14: a = arange(1,5)
6/15: a
6/16: a = arange(1,5,0.1)
6/17: a
6/18: d.animate2d(prodx="tch",prody="ech",prodz="epq")
6/19: %pylab
6/20: show()
6/21: d.animate2d(prodx="tch",prody="ech",prodz="epq")
6/22: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
6/23: animate2d ?
6/24: ion()
6/25: show()
6/26: pylab.close('all)
6/27: pylab.close('all')
6/28: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
6/29: pylab.close('all')
6/30: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
 8/1: from uswipha import uswipha
 8/2: from numpy import arange
 8/3: d = uswipha(year=[1992],tf=[[1,50]])
 8/4: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
 8/5: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
 8/6: d = uswipha(year=[1992,1995],tf=[[1,150]])
 8/7: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
 8/8: pylab.close('all')
 8/9: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
8/10: pylab.close('all')
8/11: d.animate1d("tch",prodz="epq",binx=arange(100,500,2),binz=arange(10,60))
8/12: pylab.close('all')
8/13: d.animate1d("tch",prodz="epq",binx=arange(100,500,2),binz=arange(10))
8/14: pylab.close('all')
8/15: d.animate1d("tch",prodz="epq",binx=arange(100,500,2),binz=arange(60))
8/16: pylab.close('all')
8/17: d.set_mask("Master","ech",0,0)
8/18: d.animate1d("tch",prodz="epq",binx=arange(100,500,2),binz=arange(60))
8/19: pylab.close('all')
8/20: d.hist2d('tch','ech',binx=arange(0,1024),biny=arange(0,1024))
8/21: d.remove_mask('all)
8/22: d.remove_mask('all')
8/23: d.show_mask()
8/24: d.remove_mask('ech')
8/25: d.hist2d('tch','ech',binx=arange(0,1024),biny=arange(0,1024))
8/26: pylab.close('all')
8/27: d.data
8/28: d.mask
8/29: d.mask()
 9/1: from uswipha import uswipha
 9/2: from numpy import arange
 9/3: d = uswipha(year=[1992,1995],tf=[[1,150]])
 9/4: d.sync_swoops()
 9/5: d.hist2d('tch','ech',binx=arange(0,1024),biny=arange(0,1024))
 9/6: d.hist2d('tch','ech',binx=arange(0,1024),biny=arange(0,300))
10/1: from uswipha import uswipha
10/2: from numpy import arange
10/3: d = uswipha(year=[1992,1995],tf=[[1,150]])
10/4: d.sync_swoop()
10/5: d.sync_swoops()
10/6: d.data
10/7: d.hist2d('tch','ech',binx=arange(0,1024),biny = arange(0,1024))
10/8: d.hist2d('tch','ech',binx=arange(0,1024),biny = arange(0,300))
11/1: runfile('/home/asterix/keilbach/Abstimmung/abstimmung_prompt.py', wdir='/home/asterix/keilbach/Abstimmung')
11/2: os
12/1: from uswipha import uswipha
12/2: from numpy import numoy
12/3: from numpy import numpy
12/4: from numpy import arange
12/5: d = uswipha(year=[1992,1995],tf=[[1,150]])
12/6: d.sync_swoops()
12/7: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
12/8: d.show_mask()
12/9: pylab.close('all')
12/10: d.data
12/11: d.hist2d('tch','epq',binx=arange(0,1024),biny = arange(0,64))
12/12: pylab.close('all')
12/13: d.hist2d('tch','epq',binx=arange(0,1024),biny = arange(0,64),norm="ymax")
12/14: d.hist2d('tch','epq',binx=arange(200,1024),biny = arange(0,64),norm="ymax")
12/15: d.set_mask("Master","year",1991,1995)
12/16: d.hist2d('tch','epq',binx=arange(200,1024),biny = arange(0,64),norm="ymax")
12/17: d.da
12/18: d.data
12/19: d.set_mask("Master","wHe+",1.1,10,reset=True)
12/20: d.hist2d('tch','epq',binx=arange(200,1024),biny = arange(0,64),norm="ymax")
12/21: ls
12/22: d.data
12/23: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/24: d.set_mask("Master","year",1993,1995)
12/25: d.set_mask("Master","year",1993,1995,reset=True)
12/26: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/27: d.set_mask("Master","year",1990,1993,reset=True)
12/28: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/29: d.set_mask("Master","year",1990,1995,reset=True)
12/30: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/31: d.set_mask2D2d('Master','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/32: d.set_mask2D('Master','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/33: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
12/34: d.hist1d('wHe+',binx=arange(1.,5.,.1))
12/35: pylab.close('all')
12/36: d.data
12/37: d.hist1d('wHe+',binx=arange(1.,5.,.1))
12/38: d.set_mask("Master","esd",1,200,reset=True)
12/39: d.data
12/40: d.set_mask("Master","ech",1,200,reset=True)
12/41: d.hist2d('wHe+','did',binx=arange(1.,2.5,0.1),biny = arange(0,4))
12/42: d.data
12/43: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4))
12/44: pylab.close('all')
12/45: d.show_mask()
12/46: d.remove_submask('master',"MASK2D tch/epq")
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
14/1: from uswipha import uswipha
14/2: from numpy import arange
14/3: d = uswipha(year=[1992,1995],tf=[[1,150]])
14/4: d = uswipha(year=[1990,1991,1992,1993,1994,1995],tf=[[1,150]])
14/5: d.hist1d('wHe+',binx=arange(1.,5.,.1))
14/6: d.sync_swoops()
14/7: d.sync_swoops?
14/8: d.sync_swoops()
14/9: d.sync_swoops()
14/10: d.hist2d('rau','det',binx=arange(1.3,5,.1),biny = arange(0,4),norm="ymax")
14/11: d.data
14/12: %history -g
15/1: d = uswipha(year=[1992,1995],tf=[[1,150]])
15/2: from uswipha import uswipha
15/3: from numpy import arange
15/4: d = uswipha(year=[1992,1995],tf=[[1,150]])
15/5: d.sync_swoops()
15/6: d.show_mask()
15/7: d.hist2d("tch","epq",binx=arange(0.1024),biny=arange(0.64),norm=ymax)
15/8: d.hist2d("tch","epq",binx=arange(0.1024),biny=arange(0.64),norm="ymax")
15/9: pylab.close('all')
15/10: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64),norm="ymax")
15/11: d.data
15/12: d.set_mask("vsw","vsw",300,400)
15/13: d.set_mask("vsw","vsw",300,400,reset="True")
15/14: d.data
15/15: d.vsw?
15/16: d.vsw ?
15/17: d.vsw
15/18: d.vsw()
15/19: d.hist1d("vsw",binx=arange(0,1000,1))
15/20: d.hist1d("vsw",binx=arange(0,1000,1))
15/21: d.set_mask("v","vsw",300,400)
15/22: d.add_mask("vsw")
15/23: d.set_mask("vsw","vsw",300,400,reset="True")
15/24: d.show_mask
15/25: d.show_mask()
15/26: d.hist1d("vsw",binx=arange(0,1000,1))
15/27: d.set_mask("vsw","vsw",300,500,reset="True")
15/28: d.show_mask()
15/29: d.show_mask()
15/30: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64),norm="ymax")
15/31: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
15/32: d.set_mask("vsw","vsw",300,400,reset="True")
15/33: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
15/34: d.set_mask("vsw","vsw",300,310,reset="True")
15/35: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
15/36: d.show_mask()
15/37: d.mask
15/38: d.smask
15/39: d.smask()
15/40: d.reset_mask("Master")
15/41: d.reset_mask("all")
15/42: d.show_mask()
15/43: d.set_mask("vsw","vsw",300,310,reset="True")
15/44: d.show_mask()
15/45: d.set_mask("vsw","vsw",300,350,reset="True")
15/46: d.show_mask()
15/47: d.reset_mask("vsw")
15/48: d.set_mask("vsw","vsw",300,350,reset="True")
15/49: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
15/50: unique(d.data["epq"])
15/51: d.add_mask("vsw_2")
15/52: d.hist1d("vsw",binx=arange(0,1000,1))
15/53: d.add_mask("vsw_2")
15/54: d.set_mask("vsw_2","vsw",750,760,reset="True")
15/55: d.reset_mask("vsw")
15/56: d.set_mask("vsw","vsw",450,460,reset="True")
15/57: d.show_mask()
15/58: d.hist1d("vsw",binx=arange(0,1000,1))
15/59: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
15/60: unique(d.data["epq"])
17/1: from uswipha import uswipha
17/2: from numpy import arange
17/3: d = uswipha(year=[1992,1995],tf=[[1,150]])
17/4: d.sync_swoops()
17/5: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
17/6: d.add_mask("vsw1")
17/7: d.set_mask("vsw1","vsw",450,460,reset="True")
17/8: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
17/9: d.reset_mask("vsw1")
17/10: d.set_mask("vsw","vsw",459,460,reset="True")
17/11: d.set_mask("vsw1","vsw",459,460,reset="True")
17/12: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
17/13: d.add_mask("vsw2")
17/14: d.set_mask("vsw2","vsw",750,760,reset="True")
17/15: d.hist2d("tch","epq",binx=arange(0,1024),biny=arange(0,64))
17/16: d.reset_mask('all')
17/17: d.animate2d('tch','epq',prodz="vsw",binx=arange(0,1024),biny = arange(0,64),norm="ymax",binz=arange(100,1000,2))
17/18: d.remove_mask('all')
17/19: d.remove_submask('all')
17/20: d.remove_submask('Master','all')
17/21: d.show_mask()
17/22: pylab.close('all')
17/23: d.show_mask()
17/24: d.animate2d('tch','epq',prodz="vsw",binx=arange(0,1024),biny = arange(0,64),norm="ymax",binz=arange(100,1000,2))
17/25: d.animate2d('tch','epq',prodz="vsw",binx=arange(0,750),biny = arange(0,64),norm="ymax",binz=arange(100,1000,10))
17/26: pylab.close('all')
17/27: d.hist2d('tch','epq',binx=arange(200,1024),biny = arange(0,64),norm="ymax")
17/28: unique(d.data['wHe+'])
17/29: for i in unique(d.data['wHe+'])
17/30:
for i in unique(d.data['wHe+']):
    print i
17/31: u = unique(d.data['wHe+'])
17/32: x = numpy.arange(len(u))
17/33: print(x)
17/34: plt?
17/35: import matplotlib.pyplot as plt
17/36: plt.plot(x,u,'x')
17/37: plt.show()
17/38: pylab.close('all')
17/39: plt.show()
17/40: pylab.close('all')
17/41: plt.plot(x,u,'x')
17/42: max(u)
17/43: numpy.max(u)
17/44: u[u!=inf]=0
17/45: plt.plot(x,u,'x')
17/46: u = unique(d.data['wHe+'])
17/47: u[u==inf]=0
17/48: pylab.close('all')
17/49: max(u)
17/50: plt.plot(x,u,'x')
17/51: pylab.close('all')
17/52: plt.plot(x,u,'x')
19/1: %history -g
20/1: from uswipha import uswipha
20/2: from numpy import arange
20/3: d = uswipha(year=[1992,1995],tf=[[1,150]])
20/4: d.sync_swoops()
20/5: d.hist2d('tch','epq',binx=arange(200,1024),biny = arange(0,64),norm="ymax")
20/6: d.add_mask('w')
20/7: d.set_mask('w','wHe+',1.1,10)
20/8: d.hist2d('tch','epq',binx=arange(200,1024),biny = arange(0,64),norm="ymax")
20/9: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/10: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64))
20/11: d.set_mask2D('w','tch','epq',binx=arange(200,500),biny=arange(0.64),norm="ymax")
20/12: d.set_mask2D('w','tch','epq',binx=arange(200,500),biny=arange(0,64),norm="ymax")
20/13: d.show_mask()
20/14: d.set_mask2D('w','tch','epq',binx=arange(200,500),biny=arange(0,64),norm="ymax",smask=['w'])
20/15: d.set_mask2D('w','tch','epq',binx=arange(200,500),biny=arange(0,64),norm="ymax"),smask=['w']
20/16: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax",smask=["w"])
20/17: pylab.close('all')
20/18: d.hist1d('wHe+')
20/19: d.hist1d('wHe+',smask=['w'])
20/20: d.hist1d('det')
20/21: d.hist1d('ech')
20/22: d.remove_submask('Master','all')
20/23: d.show_mask()
20/24: d.remove_mask('all')
20/25: d.remove_submask('all')
20/26: d.reset_mask('all')
20/27: d.show_mask()
20/28: d.add_mask('test')
20/29: d.set_mask('test','tch',0,400)
20/30: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/31: d.set_mask('test','tch',0,400,reset="True")
20/32: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/33: d.show_mask()
20/34: d.set_mask('test','epq',0,40,reset="True")
20/35: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/36: d.show_mask()
20/37: d.set_mask('test','tch',0,800,reset="True")
20/38: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/39: d.show_mask()
20/40: d.reset_mask('all')
20/41: d.add_mask('test')
20/42: d.show_mask()
20/43: d.delete_mask('all')
20/44: d.remove_submask('all')
20/45: d.remove_submask('Master','test')
20/46: d.show_mask()
20/47: d.show_mask()
20/48: d.remove_mask('test')
20/49: d.show_mask()
20/50: d.add_mask('test')
20/51: d.set_mask('test','tch',0,500,reset="True")
20/52: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/53: d.set_mask('test','tch',0,560,reset="True")
20/54: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/55: d.show_mask()
20/56: pylab.close('all')
20/57: d.remove_mask('test')
20/58: d.show_mask()
20/59: d.set_mask("Master","wHe+",1.1,10,reset=True)
20/60: d.show_mask()
20/61: d.set_mask2D('Master','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
20/62: d.show_mask()
20/63: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/64: d.set_mask("Master","ech",1,200,reset=True)
20/65: d.show_mask()
20/66: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/67: d.hist2d('wHe+','det',binx=arange(1,2.5,0.1),biny=arange(0,5))
20/68: d.hist1d('det')
20/69: unique(d.data['det'])
20/70: d.hist1d('det')
20/71: d.hist2d('wHe+','det',binx=arange(1,2.5,0.1),biny=arange(0,4))
20/72: d.hist2d('wHe+','det',binx=arange(1,2.5,0.1),biny=arange(0,4,1))
20/73: pylab.close('all')
20/74: d.hist2d('wHe+','det',binx=arange(1,2.5,0.1),biny=arange(0,4,1))
20/75: pylab.close('all')
20/76: d.show_mask()
20/77: d.remove_submask('Master','all')
20/78: d.show_mask()
20/79: d.add_mask('He+')
20/80: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
20/81: d.set_mask("Master","ech",1,200,reset=True)
20/82: d.set_mask("Master","ech",1,200,reset=True)
20/83: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax")
20/84: d.show_mask()
20/85: d.remove_submask('Master','all')
20/86: d.show_mask()
20/87: d.set_mask("Master","ech",1,200,reset=True)
20/88: d.show_mask()
20/89: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/90: d.set_mask("Master","wHe+",1.2,10,reset=True)
20/91: d.show_mask()
20/92: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
20/93: d.data['epq']
20/94: unique(d.data['epq'])
20/95: pylab.close('all')
20/96: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax")
21/1: os
21/2: os.chdir("/home/asterix/keilbach/PLASTIC_pha_scripts/")
21/3: chdir("/home/asterix/keilbach/PLASTIC_pha_scripts/")
21/4: os?
21/5: os help
21/6: help os
21/7: os ?
23/1: from uswipha import uswipha
23/2: ls
23/3: cd libulpy
23/4: from uswipha import uswipha
23/5: from numpy import arange
23/6: d = uswipha(year=[1992,1995],tf=[[1,150]])
23/7: d.sync_swoops()
23/8: d.animate2d('tch','epq',prodz="vsw",binx=arange(0,750),biny = arange(0,64),norm="ymax",binz=arange(100,1000,10))
23/9: d.animate2d('tch','ech',prodz="epq",binx=arange(0,750),biny = arange(0,64),norm="ymax",binz=arange(0,64,1))
23/10: d.animate2d('tch','ech',prodz="epq",binx=arange(0,750),biny = arange(0,100),norm="ymax",binz=arange(0,64,1))
23/11: pylab.close('all')
23/12: d.animate2d('tch','ech',prodz="epq",binx=arange(0,750),biny = arange(0,140),norm="ymax",binz=arange(0,64,1))
23/13: pylab.close('all')
23/14: d = uswipha(year=[arange(1992,1996)],tf=[[1,366]])
23/15: d = uswipha(year=[1992,1993,1994,1995,1996],tf=[[1,366]])
23/16: d.sync_swoops()
23/17: d.animate2d('tch','ech',prodz="epq",binx=arange(0,750),biny = arange(0,140),norm="ymax",binz=arange(0,64,1))
23/18: d.animate2d('tch','ech',prodz="epq",binx=arange(0,750),biny = arange(0,140),norm="ymax",binz=arange(0,64,1),norm="ymax")
23/19: d.animate2d('tch','ech',prodz="epq",binx=arange(0,750),biny = arange(0,140),norm="ymax",binz=arange(0,64,1))
23/20: pylab.close('all')
23/21: d.animate2d('tch','ech',prodz="epq",binx=arange(0,750),biny = arange(0,140),norm="ymax",binz=arange(0,64,1))
24/1: cd /home/asterix/keilbach/PLASTIC_pha_scripts/
24/2: %run EQ_positions_CTOF.py
24/3: %run EQ_positions_gui(self,hide=False)
24/4: ls
24/5: %run EQ_positions_gui
24/6: %run EQ_positions_gui_OOP.py
24/7: EQ_positions_gui?
24/8: EQ_positions_gui
24/9: EQ_positions_gui(t)
24/10: EQ_positions_gui(self,hide=False)
24/11: false
24/12: False
24/13: EQ_positions_gui(hide=False)
24/14: EQ_positions_gui(DPATH=False,hide=False)
27/1: cd /home/asterix/keilbach/PLASTIC_pha_scripts/
27/2: %run EQ_positions_CTOF.py
27/3: %run EQ_positions_CTOF.py
27/4: %run EQ_positions_CTOF.py
28/1: %run EQ_positions_CTOF.py
28/2: cd /home/asterix/keilbach/PLASTIC_pha_scripts/
28/3: %run EQ_positions_CTOF.py
28/4: %run EQ_positions_CTOF.py
28/5: %run EQ_positions_CTOF.py
28/6: %run EQ_positions_CTOF.py
28/7: %run EQ_positions_CTOF.py
30/1: d = uswipha(year=[1993,1994,1995],tf=[[1,366]])
30/2: from numpy import arange
30/3: from uswipha import uswipha
30/4: d = uswipha(year=[1993,1994,1995],tf=[[1,366]])
30/5: d.sync_swoops()
30/6: d.set_mask("Master","wHe+",1.1,10,reset=True)
30/7: d.set_mask("Master","ech",1,200,reset=True)
30/8: d.show_mask()
30/9: d.remove_submask('Master',"ech")
30/10: d.add_mask('He+')
30/11: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
30/12: d.show_mask()
30/13: d.show_mask()
30/14: d.remove_submask('Master',"ech")
30/15: d.show_mask()
30/16: d.remove_submask('Master',"wHe+")
30/17: d.show_mask()
30/18: d.remove_mask("all")
30/19: d.remove_mask('He+')
30/20: d.show_mask()
30/21: d.add_mask("test")
30/22: d.show_mask()
30/23: d.remove_mask('all')
30/24: d.show_mask()
30/25: d.add_mask("test")
30/26: d.show_mask()
30/27: d.set_mask("Master","ech",1,100,reset=True)
30/28: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
30/29: d.show_mask()
30/30: d.remove_submask('Master',"all")
30/31: d.show_mask()
30/32: d.set_mask('test','tch',0,400,reset="True")
30/33: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
30/34: d.show_mask()
30/35: d.set_mask('test','tch',0,500,reset="True")
30/36: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
30/37: d.show_mask
30/38: d.show_mask()
30/39: d.remove_mask('all')
30/40: d.show_mask()
30/41: d.set_mask('Master','wHe+',1.1,10,reset=True)
30/42: d.show_mask()
30/43: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
30/44: d.add_mask('He+')
30/45: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
30/46: d.set_mask('Master','ech',1,200,reset=True)
30/47: d.hist2d('tch','epq',binx=arange(200,600),biny = arange(0,64),norm="ymax")
30/48: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax")
30/49: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax",cb='yes')
30/50: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax",cb=True)
30/51: d.hist2d('wHe+','det',binx=arange(1.,2.5,0.1),biny = arange(0,4),norm="ymax")
32/1: from numpy import arange
32/2: from uswipha import uswipha
32/3: d = uswipha(year=[1993,1994,1995],tf=[[1,366]])
32/4: d.sync_swoops()
32/5: d.data
32/6: d.dp
32/7: d.dp["brw"]
32/8: pp= d.dp["brw"]
32/9: pp.props
32/10: pp.set["contourcolor"]="jet"
32/11: pp
32/12: pp.props
32/13: pp.set_name?
32/14: pp.set("contourcolor","jet")
32/15: pp.props
32/16: d.hist1d("brw")
32/17: d.hist2d("brw","brw")
32/18: pylab.close('all')
32/19: d.mp
32/20: d.mp["Master"].set("contourcolor","jet")
32/21: d.hist2d("brw","brw")
32/22: d.hist2d("tch","ech")
32/23: d.hist2d("tch","ech",norm="ymax")
32/24: pylab.close('all')
32/25: pp)
32/26: pp
32/27: pp.props
32/28: d.set_mask('Master','ech',1,200,reset=True)
32/29: d.show_mask()
32/30: d.set_mask('Master','ech',30,100,reset=True)
32/31: d.show_mask()
32/32: d.add_mask("test")
32/33: d.set_mask('test','ech',45,55,reset=True)
32/34: d.show_mask()
32/35: d.set_mask('test','ech',10,300,reset=True)
32/36: d.show_mask()
32/37: d.set_mask('test','ech',10,300,reset=True)
32/38: d.set_mask('test','ech',10,200,reset=True)
32/39: d.show_mask()
32/40: d.remove_submask('test')
32/41: d.remove_mask('test')
32/42: d.show_mask()
32/43: d.add_mask("test")
32/44: d.set_mask('test','tch',0,500,reset="True")
32/45: d.show_mask()
32/46: d.set_mask('test','tch',0,400,reset="True")
32/47: d.show_mask()
32/48: d.set_mask('test','tch',0,400,reset=True)
32/49: d.show_mask()
37/1: %run fitting
37/2: ls
37/3: cd
37/4: ls
37/5: cd Documents/
37/6: ls
37/7: %run fitting.py
37/8: close all
38/1: %run fitting.py
40/1:
AString = """Das Anführungszeichen \" kann nur mit Hilfe des Escape Zeichens \\ verwendet werden.
\nZusätzlich können wir auch Tabs \t und das drücken von Backspace emulieren. 12345 \b\b 6789"""

print(AString)
40/2:
from numpy import pi
A = 5
R = 0.2
L =12452627

S = """Das Auto hat {2} Reifen mit einem Durchmesser von jeweils 2*{0:.2f}*{1} Meter und {3:,} Km Laufleistung.\n
{3:,} Km ist im Binärformat ausgedrückt  {3:#b}""".format(pi, R, A, L)

print(S)
40/3:
from numpy import pi
A = 5
R = 0.2
L =12452627

S = """Das Auto hat {2} Reifen mit einem Durchmesser von jeweils 2*{0:.2f}*{1} Meter und {3:,1f} Km Laufleistung.\n
{3:,} Km ist im Binärformat ausgedrückt  {3:#b}""".format(pi, R, A, L)

print(S)
40/4:
from numpy import pi
A = 5
R = 0.2
L =12452627

S = """Das Auto hat {2} Reifen mit einem Durchmesser von jeweils 2*{0:.2f}*{1} Meter und {3:,1} Km Laufleistung.\n
{3:,} Km ist im Binärformat ausgedrückt  {3:#b}""".format(pi, R, A, L)

print(S)
40/5:
from numpy import pi
A = 5
R = 0.2
L =12452627

S = """Das Auto hat {2} Reifen mit einem Durchmesser von jeweils 2*{0:.2f}*{1} Meter und {3:,1} Km Laufleistung.\n
{3:,} Km ist im Binärformat ausgedrückt  {3:#b}""".format(pi, R, A, L)

print(S)
40/6:
from numpy import pi
A = 5
R = 0.2
L =12452627

S = """Das Auto hat {2} Reifen mit einem Durchmesser von jeweils 2*{0:.2f}*{1} Meter und {3:,} Km Laufleistung.\n
{3:,} Km ist im Binärformat ausgedrückt  {3:#b}""".format(pi, R, A, L)

print(S)
40/7:
AString = """Das Anführungszeichen \" kann nur mit Hilfe des Escape Zeichens \\ verwendet werden.
\nZusätzlich können wir auch Tabs \t und \b das Drücken von Backspace emulieren. 12345 \b\b 6789"""

print(AString)
40/8:
AString = """Das Anführungszeichen \" kann nur mit Hilfe des Escape Zeichens \\ verwendet werden.
\nZusätzlich können wir auch Tabs \t und das Drücken von Backspace emulieren. 12345 \b\b 6789"""

print(AString)
40/9:
print(1  == True)
print(2  == True)
print(0  == False)
print([] == False)
40/10: print (r"Die Ausdrücke \" und \t sind Escape Zeichen")
40/11:
print(1  == True)
print(2  == True)
print(0  == False)
print([] == False)
40/12:
print(1  == True)
print(2  == True)
print([] == False)
print(0  == False)
40/13:
print(1  == True)
print(2  == True)
print([] == False)
print(0  == False)
42/1: print(1 ==True)
42/2: print(1 ==False)
42/3: print(10 ==True)
42/4: print([0] ==True)
42/5: print([0] ==False)
42/6: print([] ==False)
42/7: print([] ==True)
44/1:
l = []
print(l)
44/2:
l = [1, 2, 3]
print(l)
44/3:
l = [1, 2, 3]
print(len(l))
44/4:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/5:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/6:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/7: t[0] = 5
44/8:
l = []
print(l)
44/9:
l = [1, 2, 3]
print(l)
44/10:
l = [1, 2, 3]
print(len(l))
44/11:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/12:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/13:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/14: t[0] = 5
44/15:
l = []
print(l)
44/16:
l = [1, 2, 3]
print(l)
44/17:
l = [1, 2, 3]
print(len(l))
44/18:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/19:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/20:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/21: t[0] = 5
44/22:
l = []
print(l)
44/23:
l = [1, 2, 3]
print(l)
44/24:
l = [1, 2, 3]
print(len(l))
44/25:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/26:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/27:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/28: t[0] = 5
44/29:
l = []
print(l)
44/30:
l = [1, 2, 3]
print(l)
44/31:
l = [1, 2, 3]
print(len(l))
44/32:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/33:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/34:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/35: t[0] = 5
44/36:
l = []
print(l)
44/37:
l = [1, 2, 3]
print(l)
44/38:
l = [1, 2, 3]
print(len(l))
44/39:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/40:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/41:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/42: t[0] = 5
44/43:
l = []
print(l)
44/44:
l = [1, 2, 3]
print(l)
44/45:
l = [1, 2, 3]
print(len(l))
44/46:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/47:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/48:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/49: t[0] = 5
44/50:
l = []
print(l)
44/51:
l = [1, 2, 3]
print(l)
44/52:
l = [1, 2, 3]
print(len(l))
44/53:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/54:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/55:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/56: t[0] = 5
44/57:
l = []
print(l)
44/58:
l = [1, 2, 3]
print(l)
44/59:
l = [1, 2, 3]
print(len(l))
44/60:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/61:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/62:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/63: t[0] = 5
44/64:
l = []
print(l)
44/65:
l = [1, 2, 3]
print(l)
44/66:
l = [1, 2, 3]
print(len(l))
44/67:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/68:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/69:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/70: t[0] = 5
44/71:
l = []
print(l)
44/72:
l = [1, 2, 3]
print(l)
44/73:
l = [1, 2, 3]
print(len(l))
44/74:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/75:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/76:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/77: t[0] = 5
44/78:
l = []
print(l)
44/79:
l = [1, 2, 3]
print(l)
44/80:
l = [1, 2, 3]
print(len(l))
44/81:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/82:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/83:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/84: t[0] = 5
44/85:
l = []
print(l)
44/86:
l = [1, 2, 3]
print(l)
44/87:
l = [1, 2, 3]
print(len(l))
44/88:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/89:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/90:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/91: t[0] = 5
44/92:
l = []
print(l)
44/93:
l = [1, 2, 3]
print(l)
44/94:
l = [1, 2, 3]
print(len(l))
44/95:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/96:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/97:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/98: t[0] = 5
44/99:
l = []
print(l)
44/100:
l = [1, 2, 3]
print(l)
44/101:
l = [1, 2, 3]
print(len(l))
44/102:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/103:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/104:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/105: t[0] = 5
44/106:
l = []
print(l)
44/107:
l = [1, 2, 3]
print(l)
44/108:
l = [1, 2, 3]
print(len(l))
44/109:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/110:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/111:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/112: t[0] = 5
44/113:
l = []
print(l)
44/114:
l = [1, 2, 3]
print(l)
44/115:
l = [1, 2, 3]
print(len(l))
44/116:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/117:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/118:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/119: t[0] = 5
44/120:
l = []
print(l)
44/121:
l = [1, 2, 3]
print(l)
44/122:
l = [1, 2, 3]
print(len(l))
44/123:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/124:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/125:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/126: t[0] = 5
44/127:
l = []
print(l)
44/128:
l = [1, 2, 3]
print(l)
44/129:
l = [1, 2, 3]
print(len(l))
44/130:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/131:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/132:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/133: t[0] = 5
44/134:
l = []
print(l)
44/135:
l = [1, 2, 3]
print(l)
44/136:
l = [1, 2, 3]
print(len(l))
44/137:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/138:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/139:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/140: t[0] = 5
44/141:
l = []
print(l)
44/142:
l = [1, 2, 3]
print(l)
44/143:
l = [1, 2, 3]
print(len(l))
44/144:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/145:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/146:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/147: t[0] = 5
44/148:
l = []
print(l)
44/149:
l = []
print(l)
44/150:
l = [1, 2, 3]
print(l)
44/151:
l = [1, 2, 3]
print(len(l))
44/152:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/153:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/154:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/155: t[0] = 5
44/156: t.append(6)
44/157:
l = []
print(l)
44/158:
l = [1, 2, 3]
print(l)
44/159:
l = [1, 2, 3]
print(len(l))
44/160:
l = [1, 2]
l.append(3)
print(l)
l.append("Hallo Welt!")
print(l)
print(len(l))
44/161:
l = [1, 2, 3, 4]
l.pop()
print(l)
l.pop(1)
print(l)
44/162:
t = 5, 6
print(type(t))
t = (5, 6)
print(type(t))
44/163: t[0] = 5
44/164: t.append(6)
44/165:
print(d['a'])
print(d[(1,2)])
44/166:
d = { 'a': 'Hallo Welt!', 'b': 5, (1,2): [3,4,5] }
print(type(d))
44/167:
print(d['a'])
print(d[(1,2)])
44/168:
d[7] = 7
print(d[7])
d['a'] = "Tschüss Welt!"
print(d['a'])
44/169: print(d['d'])
44/170:
print(d['d'])
print(d)
44/171: print(d['d'])
44/172:
print(d.keys())
print(d.values())
print(d.items())
print()
for k,v in d.items():
    print(k, v)
44/173:
print(d.keys())
print(d.values())
print(d.items())
print()
for k,v in d.items():
    print(k, v)
print()
44/174:
print(d.keys())
print(d.values())
print(d.items())
print()
for a,b in d.items():
    print(a, b)
print()
43/1:
a = [1, 2.0, "Hallo"]
np.array(a)
43/2:
import numpy as np

MyList  = [1,2,3,4]
MyArray = np.array(MyList)

print(type(MyList), type(MyArray))
43/3:
MyArr = np.arange(0,5,1)
MyArr2 = np.linspace(0,4,5)

print(MyArr)
print(MyArr2)
43/4:
a = [1, 2.0, "Hallo"]
np.array(a)
43/5:
a = [1, 2, (3, 4)]
np.array(a)
43/6:
# Element-wise multiplication of a ndarray and integer
print(MyArr * 2)

# Element-wise Multipliciation of two ndarray
print(MyArr * MyArr)
43/7: np.array(["Spam","Eggs"]) * 2
43/8: np.arange(5) * np.arange(6)
43/9:
# Boolean Operations with ndarrays
print(myArr > 2)
print((myArr < 4) * (myArr > 2))
43/10:
# Boolean Operations with ndarrays
print(myArr > 2)
print((myArr < 4) * (myArr > 2))
43/11:
# Boolean Operations with ndarrays
print(MyArr > 2)
print((MyArr < 4) * (MyArr > 2))
47/1:
myArr  = np.zeros((2,3))
myArr2 = np.ones((3,4))
myList = [[1,2,3], [3,4,5], [6,7,8]]
myArr3 = np.array(myList)

print(myArr3)
47/2:
import numpy as np

MyList  = [1,2,3,4]
MyArray = np.array(MyList)

print(type(MyList), type(MyArray))
47/3:
MyArr = np.arange(0,5,1)
MyArr2 = np.linspace(0,4,5)

print(MyArr)
print(MyArr2)
47/4:
a = [1, 2.0, "Hallo"]
np.array(a)
47/5:
a = [1, 2, (3, 4)]
np.array(a)
47/6:
# Element-wise multiplication of a ndarray and integer
print(MyArr * 2)

# Element-wise Multipliciation of two ndarray
print(MyArr * MyArr)
47/7: np.array(["Spam","Eggs"]) * 2
47/8: np.arange(5) * np.arange(6)
47/9:
# Boolean Operations with ndarrays
print(MyArr > 2)
print((MyArr < 4) * (MyArr > 2))
47/10:
myArr  = np.zeros((2,3))
myArr2 = np.ones((3,4))
myList = [[1,2,3], [3,4,5], [6,7,8]]
myArr3 = np.array(myList)

print(myArr3)
47/11:
print("Shape: ",myArr3.shape)
print("Length: ",myArr3.size)
print("Number of Dimensions: ",myArr3.ndim)
47/12:
print("Slice operation with lists: ",myList[2][:])
print("Slice operation with ndarrays: ",myArr3[2,:])
47/13: print(myArr3[[(0,1),(0,2)]])
47/14:

print(myArr3)
print(myArr3[[(0,1),(0,2)]])
47/15:

print(myArr3)
print()
print(myArr3[[(0,1),(0,2)]])
47/16:

print(myArr3)
print(myArr3(0,0))
print(myArr3[[(0,1),(0,2)]])
47/17:

print(myArr3)
print(myArr3[0,0])
print(myArr3[[(0,1),(0,2)]])
48/1: import numpy as np
48/2: x = np.array([[1,2],[3,4],[5,6]])
48/3: x
48/4: print(x[[0,1,2],[0,1,0]])
48/5: x = np.array([[ 0,  1,  2],[ 3,  4,  5],[ 6,  7,  8],[ 9, 10, 11]])
48/6: x
48/7: rows = np.array([[0,0],[3,3]])
48/8: rows
48/9: [rows,cols]
48/10: cols= np.array([[0,0],[3,3]])
48/11: [rows,cols]
48/12: cols= np.array([[0,2],[0.2]])
48/13: [rows,cols]
48/14: rows
48/15: cols
48/16: cols= np.array([[0,2],[0,2]])
48/17: [rows,cols]
48/18: cols= np.array([[0,2],[0,2]])
48/19: rows
48/20: rows = np.array([[0,0],[3,3]])
48/21: rows
48/22: cols
47/18:
myArr4 = np.arange(100)**2
print(myArr4[[2,2,2,15,15,17,32]])
47/19:
myArr5 = np.arange(10)
mask = np.array(([True, True, True] + [False, False, False] + [True, True, True, True]))
maskedArray = myArr5[mask]
print(maskedArray)
48/23: mA4 = np.arange(10)
48/24: mA4
48/25: mA4 = np.arange(10)**2
48/26: mA4
48/27: myArr6 = np.arange(100)
48/28: myArr6
48/29: mask = (myArr6 > 30) * (myArr6<50) * (myArr6>25)
48/30: mask
48/31: m1 = (myArr > 30)
48/32: m1 = (myArr6 > 30)
48/33: m2 = (myArr6 < 50)
48/34: m1
48/35: m2
48/36: m1*m2
49/1:
from hanoi import Hanoi

# Create an instance of the Hanoi class
myHanoi = Hanoi(n=3)

# Create an instance of a list
aList = [1,2,3]
49/2:
class MyClass:
    pass

A = MyClass()
B = MyClass()

print(type(A), type(B))
49/3:
class Auto:
    def honk(self):
        print("Tut Tut")
    def drive(self, Zeit):
        print("Brumm Brumm for %i minutes"%(Zeit))
49/4:
A = Auto()
A.honk()
A.drive(10)
49/5: aList.append([1,2,3])
48/37:
class Auto:
    def __init__(self, Name):
        print("I am a %s"%(Name))
48/38: A = Auto()
48/39: A = Auto('VW')
49/6:
A.topspeed = 120
print("Topspeed of A: ", A.topspeed)
print("Topspeed of B", B.topspeed)
49/7:
class Auto:
    def __init__(self, name = "Volvo", N = 4):
        self.name = name
        self.N = N
    def drive(self):
        print("The car %s is driving on %i wheels"%(self.name, self.N))

A = Auto()
B = Auto("Volkswagen", N = 6)

# Accessing Instance variables from within the instance
A.drive()
B.drive()

#Accessing Instance variables from outside the instance
A.N = 16
A.drive()
B.drive()
49/8:
A.topspeed = 120
print("Topspeed of A: ", A.topspeed)
print("Topspeed of B", B.topspeed)
54/1: import pyplot as plt
54/2: from matplotlib import pylab as plt
54/3: cd
54/4: cd /home/skeletor/fischer
54/5: ls
54/6: cd
54/7: ls
54/8: cd Documents/MA/
54/9: ls
54/10: %run pui_ulysses.py
54/11: %run pui_ulysses.py
54/12: %run pui_ulysses.py
54/13: %run pui_ulysses.py
54/14: %run pui_ulysses.py
54/15: a = pui_ana
54/16: a = pui_ana()
54/17: np.arange(1,2,3)
54/18: np.arange(1,20)
54/19: np.arange(1,20,3)
54/20: a.data
54/21: a.data()
54/22: %run pui_ulysses.py
54/23: %run pui_ulysses.py
54/24: d = pui_ana()
56/1: cd ../..
56/2: cd BA/Fischer/PLASTIC/
56/3: %run hepui_ana.py
57/1: ls
60/1: sudo pip2.7 install --upgrade html5lib
60/2: sudo pip install --upgrade html5lib
67/1: sudo pip install --upgrade html5lib
69/1: cd
69/2: ls
69/3: cd Documents/MA/
69/4: ls
69/5: % run pui_ulysses.py
69/6: a = pui_ana()
70/1: d = he_interactive()
71/1: d = he_interactive()
72/1: a = pui_ana()
75/1: import sys
75/2: print(sys.path)
80/1: import sys
80/2: print(sys.path)
80/3: sys.path.append("/home/asterix/fischer/ulysses/")
81/1: print(sys.path)
82/1: print(sys.path)
84/1: from uswipha impoert uswipha
84/2: from uswipha import uswipha
84/3: from uswipha import uswipha
84/4: ls
84/5: cd
84/6: cd ulysses/swics/software/
84/7: cd diy/
84/8: from uswipha import uswipha
84/9: import sys
84/10: sys.path.insert(0, "/home/asterix/fischer/ulysses/")
84/11: from uswipha import uswipha
84/12: sys.path.insert(0, "/home/asterix/fischer/ulysses/swics/software")
84/13: from uswipha import uswipha
84/14: sys.path.insert(0, "/home/asterix/fischer/ulysses/swics/software/libulpy")
84/15: from uswipha import uswipha
84/16: sys.path.remove(0, "/home/asterix/fischer/ulysses/swics/software")
84/17: sys.path.remove("/home/asterix/fischer/ulysses/swics/software")
84/18: sys.path.remove("/home/asterix/fischer/ulysses/swics/software/libulpy")
84/19: sys.path.remove("/home/asterix/fischer/ulysses")
84/20: ls
84/21: from ../libulpy/uswipha import uswipha
84/22: from ./libulpy/uswipha import uswipha
84/23: from /libulpy/uswipha import uswipha
84/24: from /libulpy import uswipha
84/25: from .. /libulpy import uswipha
84/26: sys.path.insert(0, "/home/asterix/fischer/ulysses/swics/software/libulpy")
84/27: from uswipha import uswipha
86/1: import sys
86/2: print(sys.path)
91/1: print(sys.path)
93/1: import sys
93/2: print(sys.path)
93/3: sys.path.insert(0,'/home/asterix/fischer/ulysses/swics/software/libulpy')
93/4: from uswipha import uswipha
94/1: print(sys.path)
73/1: python -c 'import sys; print(sys.prefix)'
96/1: print(sys.path)
97/1: print(sys.path)
98/1: %run pui_ulysses.py
98/2: %run pui_ulysses.py
98/3: %run pui_ulysses.py
99/1: d = pui_ana()
100/1: d = pui_ana()
101/1: for uswipha import uswipha
101/2: from uswipha import uswipha
101/3: d = uswipha()
102/1:
class Auto:
    def __init__(self):
        self.topspeed = 180
    def honk(self):
        print("Tut Tut")
    def drive(self, time):
        print("Car is driving for %i minutes"%time)
        
class FlyingCar(Auto):
    def fly(self, time):
        print("Car is flying for %i minutes"%time)
    def drive(self):
        print("This car cannot drive, it's a flying car!")
        
A = FlyingCar()
A.honk()
A.fly(5)
A.drive(10)
print("The topspeed is: ", A.topspeed)
102/2:
class Auto:
    def __init__(self):
        self.topspeed = 180
    def honk(self):
        print("Tut Tut")
    def drive(self, time):
        print("Car is driving for %i minutes"%time)
        
class FlyingCar(Auto):
    def fly(self, time):
        print("Car is flying for %i minutes"%time)
    def drive(self,time=10):
        print("This car cannot drive, it's a flying car!")
        
A = FlyingCar()
A.honk()
A.fly(5)
A.drive(10)
print("The topspeed is: ", A.topspeed)
101/4: range(10)
108/1:
class Auto:
    def __init__(self):
        self.topspeed = 180
    def honk(self):
        print("Tut Tut")
    def drive(self, time):
        print("Car is driving for %i minutes"%time)
        
class FlyingCar(Auto):
    def fly(self, time):
        print("Car is flying for %i minutes"%time)
    def drive(self,time=10):
        print("This car cannot drive, it's a flying car!")
        
A = FlyingCar()
A.honk()
A.fly(5)
A.drive(10)
print("The topspeed is: ", A.topspeed)
109/1: d.data
110/1: polar_plot()
111/1: polar_plot()
112/1: polar_plot()
113/1: polar_plot()
114/1: add()
115/1: add()
115/2: polar_plot()
116/1: polar_plot()
116/2: year
117/1: polar_plot()
118/1: polar_plot()
119/1: polar_plot()
119/2: d.data()
121/1: polar_plot()
121/2: d.data()
121/3: d
122/1: d = load()
122/2: d.data()
122/3: d.data
123/1: d = test()
102/3:
class Auto:
    wheels = 4
    def __init__(self, name):
        self.name = name
        print("The car has currently %i wheels."%(Auto.wheels))

A = Auto("Volvo")
B = Auto("Volkswagen")

Auto.wheels = 12

print("Number of wheels on A and B: ",A.wheels, B.wheels)
A.wheels = 16
print("Number of wheels on A and B: ",A.wheels, B.wheels)
Auto.wheels = 5
print("Number of wheels on A and B: ",A.wheels, B.wheels)
102/4:
class Auto:
    wheels = 4
    def __init__(self, name='VW'):
        self.name = name
        print("The car has currently %i wheels."%(Auto.wheels))

        
A = Auto("Volvo")
B = Auto("Volkswagen")
C = Auto()

Auto.wheels = 12

print("Number of wheels on A and B: ",A.wheels, B.wheels)
A.wheels = 16
print("Number of wheels on A and B: ",A.wheels, B.wheels)
Auto.wheels = 5
print("Number of wheels on A and B: ",A.wheels, B.wheels)
102/5:
class Auto:
    wheels = 4
    def __init__(self, name='VW'):
        self.name = name
        print("The car %s has currently %i wheels."%(Auto.name,Auto.wheels))

        
A = Auto("Volvo")
B = Auto("Volkswagen")
C = Auto()

Auto.wheels = 12

print("Number of wheels on A and B: ",A.wheels, B.wheels)
A.wheels = 16
print("Number of wheels on A and B: ",A.wheels, B.wheels)
Auto.wheels = 5
print("Number of wheels on A and B: ",A.wheels, B.wheels)
102/6:
class Auto:
    wheels = 4
    def __init__(self, name='VW'):
        self.name = name
        print("The car %s has currently %i wheels."%(name,Auto.wheels))

        
A = Auto("Volvo")
B = Auto("Volkswagen")
C = Auto()

Auto.wheels = 12

print("Number of wheels on A and B: ",A.wheels, B.wheels)
A.wheels = 16
print("Number of wheels on A and B: ",A.wheels, B.wheels)
Auto.wheels = 5
print("Number of wheels on A and B: ",A.wheels, B.wheels)
123/2: d = test()
124/1: d = test()
125/1: d = test()
126/1: d = test()
127/1: d = test()
129/1: d = test()
130/1: d.data
130/2: d.sync_swoops()
133/1: 2 * np.pi * r
133/2: r = np.arange(0, 2, 0.01)
133/3: 2 * np.pi * r
133/4: %run pui_ulysses.py
134/1: %run pui_ulysses.py
134/2: pylab.close('all')
134/3: %run pui_ulysses.py
135/1: r
135/2: theta
138/1: pylab.show()
139/1: d = uswipha(year=[1992],tf=[[1,50]])
139/2: d.data
139/3: d.data('doy')
139/4: d.data['dox']
139/5: d.data['doy']
139/6: d.add_mask('epq')
139/7: d.set_mask('epq','epq',55,55)
139/8: d.data['epq']
139/9: d.remove_mask('all')
139/10: d.show_mask()
139/11: d.data['epq']
139/12: d.set_mask('epq','epq',55,56)
139/13: d.add_mask('epq')
139/14: d.set_mask('epq','epq',55,56)
139/15: d.data['epq']
139/16: d.get_data('epq,'epq')
139/17: d.get_data('epq',epq)
139/18: d.get_data('epq','epq')
139/19: d.set_mask('epq','epq',55,55)
139/20: d.get_data('epq','epq')
139/21: d.data
140/1: polarplot(d,'det','sec',3,8)
140/2: np.arange(0,10,2)
141/1: polarplot(d,'det','sec',3,8)
142/1: polarplot(d,'det','sec',3,8)
142/2: Hist
142/3: Hist, r_edges,phi_edges =polarplot(d,'det','sec',3,8)
142/4: polarplot(d,'det','sec',3,8)
142/5: a= polar_plot()
142/6: polarplot(d,'det','sec',3,8)
142/7: a= polarplot(d,'det','sec',3,8)
142/8: a
142/9: a
142/10: whso a
142/11: whos a
142/12: size(a)
142/13: type(a)
142/14: a,b,c= polarplot(d,'det','sec',3,8)
144/1: polarplot(d,'det','sec',3,8)
144/2: a,b,c=polarplot(d,'det','sec',3,8)
144/3: a
148/1: polarplot(d,'det','sec',3,8)
149/1: polarplot(d,'det','sec',3,8)
150/1: polarplot(d,'det','sec',3,8)
151/1: polarplot(d,'det','sec',3,8)
152/1: polarplot(d,'det','sec',3,8)
153/1: polarplot(d,'det','sec',3,8)
154/1: polarplot(d,'det','sec',3,8)
155/1: polarplot(d,'det','sec',3,8)
156/1: polarplot(d,'det','sec',3,8)
157/1: polarplot(d,'det','sec',3,8)
158/1: polarplot(d,'det','sec',3,8)
158/2: Hist
158/3: H,r,p = polarplot(d,'det','sec',3,8)
158/4: H
158/5: min(H)
158/6: H.min()
158/7: H.max()
159/1: H,r,p = polarplot(d,'det','sec',3,8)
159/2: H
161/1: np.pi
161/2: np.arange(1,50,1)
161/3: np.arange(1,np.pi,1)
161/4: np.arange(1,np.pi,1)
166/1: phi_data_rad
166/2: phi_data
166/3: phi_data /360
166/4: phi_data /360*2*np.pi
168/1: phi_data
168/2: phi_data_rad
169/1: r = .5 + np.random.normal(size=N, scale=.1)
169/2: r = .5 + np.random.normal(size=5, scale=.1)
169/3: r
170/1: r = .5 + np.random.normal(size=5, scale=.1)
170/2: r
171/1: r_data
171/2: size(r_data)
171/3: size(binr)
171/4: type(r_data)
171/5: dim(r_data)
171/6: binr
171/7: r_data
173/1: redges
173/2: phiedges
186/1: binphi
196/1:
N = 10000
r = .5 + np.random.normal(size=N, scale=.1)
theta = np.pi / 2 + np.random.normal(size=N, scale=.1)
196/2: pylab.plot(np.arange(1,len(r),1),r)
196/3: np.arange(1,len(r),1)
196/4: r
196/5: len(r)
196/6: b = np.arange(1,len(r),1)
196/7: len(b)
196/8: b = np.arange(1,len(r)+1,1)
196/9: pylab.plot(b,r)
196/10: r_mu , r_sigma = 0.5,0.2
196/11: r_data = np.random.normal(r_mu, r_sigma, 10000)
196/12: pylab.plot(b,r_data)
196/13: fig = pylab.figure()
196/14: ax = pylab.subplot(121)
196/15: pylab.plot(b,r_data)
196/16: ax2 = pylab.subplot(221)
196/17: pylab.close('all')
196/18: ax = pylab.subplot(211)
196/19: pylab.plot(b,r_data)
196/20: ax2 = pylab.subplot(212)
196/21: pylab.plot(b,r)
198/1: np.random.randon(10)
198/2: np.random.random(10)
198/3: np.random.random(10)*10
198/4: np.random.random(10)*np.pi*2
203/1: phi
203/2: r
203/3: redges
209/1: polarplot(d,'det','sec',3,8)
210/1: polarplot(d,'det','sec',3,8)
210/2: polarplot(d,'det','sec')
210/3: rvals
211/1: a= polarplot(d,'det','sec')
211/2: a
211/3: a[1]
211/4: for i in a[1]
211/5:
for i in a[1]:
    print i
211/6:
for i in a[0]:
    print i
211/7: np.hist1d(a[0])
211/8: np.histd(a[0])
211/9: np.histogram(a[0])
211/10: b = np.histogram(a[0])
211/11: pylab.plot(b[0],b[1])
211/12: b
211/13: pylab.hist(a[0])
211/14: pylab.show()
211/15: hist,edges = np.histogram(a[0])
211/16: hist
211/17: size(hist)
211/18: size(edges)
211/19: pylab.plot(edges[:-1],hist)
211/20: pylab.show()
211/21: pylab.close('all')
211/22: pylab.plot(edges[:-1],hist)
211/23: pylab.close('all')
211/24: pylab.hist(a[0],bins=[0,1,2,3,4,5])
212/1: rvals, bb = polarplot(d,'det','sec')
212/2: rvals
212/3: pylab.close('all')
212/4: np.histogram(rvals)
212/5: pylab.hist(rvals)
212/6: rvals.unique()
212/7: np.unique(rvals)
212/8: pylab.hist(rvals,bins=[0,1,2,3])
212/9: pylab.cl
212/10: pylab.close('all')
212/11: pylab.hist(rvals,bins=[0,1,2,3])
213/1: rvals, bb = polarplot(d,'det','sec')
213/2: np.unique(rvals)
213/3: pylab.hist(rvals,bins=[0,1,2,3])
213/4: pylab.clos
213/5: pylab.close('all')
213/6: pylab.hist(rvals,bins=[0,1,2,3])
214/1: rvals, bb = polarplot(d,'det','sec')
214/2: pylab.close('all')
214/3: pylab.hist(rvals,bins=[0,1,2,3])
215/1: rvals, bb = polarplot(d,'det','sec')
215/2: pylab.close('all')
215/3: rvals, bb = polarplot(d,'det','sec')
215/4: pylab.close('all')
215/5: pylab.hist(rvals,bins=[0,1,2,3])
216/1: rvals, bb = polarplot(d,'det','sec')
216/2: d.data
216/3: np.arange(0,4,1)
216/4: pylab.hist(rvals,bins=[0,1,2,3])
216/5: pylab.close('all')
216/6: pylab.hist(rvals,bins=[0,1,2,3])
217/1: rvals, bb = polarplot(d,'det','sec')
217/2: rvals
217/3: bb
218/1: Hist, rbins, phibins = polarplot(d,'det','sec')
219/1: Hist, rbins, phibins = polarplot(d,'det','sec')
219/2: Hist
219/3:
for i in Hist:
    print(i)
219/4: Hist[0]
219/5: Hist[0,1]
219/6: Hist[0,0]
219/7: Hist[:,0]
220/1: Hist, rbins, phibins, rvals, phivals = polarplot(d,'det','sec')
220/2: rvals
220/3: np.uniwue(rvals)
220/4: np.unique(rvals)
221/1: d.show_mask()
221/2: d.data
222/1: np.unique(d.data['ech'])
223/1: np.unique(d.data['ech'])
224/1: np.unique(d.data['ech'])
224/2: np.unique(d.get_data(['epq_mask','ssd_mask'],'ech'))
224/3: np.unique(rvals)
224/4: polarplot(d,'det','sec')
224/5: np.unique(rvals)
224/6: pylab.close('all')
224/7: Hist, rbins, phibins, rvals, phivals = polarplot(d,'det','sec')
224/8: rvals
224/9: np.unique(rvals)
224/10: pylab.hist(rvals,bins=[0,1,2,3])
224/11: pylab.close('all')
224/12: pylab.hist(rvals,bins=[0,1,2,3])
224/13: pylab.hist(rvals,bins=[0,1,2,3,4])
224/14: d.show_mask()
225/1: d.show_mask()
225/2: Hist, rbins, phibins, rvals, phivals = polarplot(d,'det','sec')
225/3: pylab.close('all')
225/4: pylab.hist(rvals,bins=[0,1,2,3,4])
225/5: d
225/6: d.remove_mask('all')
225/7: d.show_mask()
225/8: d.add_mask('sectest')
225/9: d.set_mask('sectest',0,0)
225/10: d.set_mask('sectest','sec',0,0)
225/11: d.show_mask()
225/12: s = d.get_data(['sectest'],'ech')
225/13: pylab.hist(s)
225/14: pylab.hist(s,bins=[0,1,2,3,4])
225/15: s
225/16: np.unique(s)
225/17: s
225/18: len(s)
225/19: pylab.hist(s,bins=np.arange(0,255))
225/20: pylab.show()
225/21: pylab.close('all')
225/22: pylab.hist(s,bins=np.arange(0,255))
225/23: d.remove_mask('all')
225/24: d.add_mask('ech')
225/25: d.set_mask('ech','ech',0,0)
225/26: s = d.get_data(['ech'],'det')
225/27: np.unique(s)
225/28: pylab.close('all')
225/29: pylab.hist(s,bins=np.arange(0,5))
225/30: np.unique(d.get_data(['ech'],'ech'))
225/31: d.remove_mask('all')
225/32: d.add_mask('det')
225/33: d.set_mask('det','det',0,0)
225/34: s = d.get_data(['det'],'ech')
225/35: np.unique(s)
225/36: pylab.close('all')
225/37: pylab.hist(s,bins=np.arange(0,255))
225/38: d.show_mask()
225/39: np.unique(d.get_data(['det'],'det'))
225/40: d.add_mask('ech')
225/41: d.set_mask('ech','ech',0,0)
225/42: s = d.get_data(['ech'],'det')
225/43: np.unique(s)
225/44: pylab.close('all')
225/45: pylab.hist(s,bins=np.arange(0,5))
227/1: Hist, rbins, phibins, rvals, phivals = polarplot(d,'det','sec')
227/2: rvals
227/3: np.unique(rvals)
227/4: pylab.hist(rvals,bins=np.arange(0,5))
227/5: pylab.close('all')
227/6: pylab.hist(rvals,bins=np.arange(0,5))
228/1: Hist, rbins, phibins, rvals, phivals = polarplot(d,'det','sec')
228/2: pylab.close('all')
228/3: pylab.hist(rvals,bins=np.arange(0,5))
228/4: phivals
228/5: np.unique(phivals)
228/6: phiedges
228/7: phibins
230/1: Hist, rbins, phibins, rvals, phivals = polarplot(d,'det','sec')
230/2: Hist
230/3: np.random.random(10)
231/1: r_art
231/2: phi_art
232/1: phi_art
232/2: r_art
232/3: Hist, rbins, phibins, rvals, phivals = polarplot(d,r_art,phi_art)
232/4: Hist, rbins, phibins, rvals, phivals = polarplot(1,r_art,phi_art)
232/5: rbins
232/6: phibins
233/1: Hist, rbins, phibins, rvals, phivals = polarplot(1,r_art,phi_art)
233/2: phiedges
233/3: a = np.arange(0,4,1)
233/4: a
234/1: Hist, rbins, phibins, rvals, phivals = polarplot(1,r_art,phi_art)
234/2: rvals
234/3: redges
234/4: rbins
234/5: phibins
235/1: binphi
235/2: Hist, redges, phiedges, rvals, phivals = polarplot(1, prodr, prodphi)
235/3: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
236/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
236/2: Hist
237/1: Hist
237/2: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
237/3: Hist
237/4: size(Hist)
237/5: redges
237/6: phiedges
237/7: dim(Hist)
237/8: len(Hist)
237/9: shape(Hist)
238/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
238/2: rvals
238/3: redges
238/4: phiedges
238/5: np.arange(0,np.pi,np.pi/8.)
239/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
239/2: np.arange(0,np.pi,np.pi/8.)
239/3: np.pi
239/4: np.arange(1,10,1)
239/5: np.arange(1,10,0.5)
239/6: sec_rad = np.pi/7.
239/7: np.arange(0,sec_rad*(8./7.),sec_rad)
239/8: np.linspace(0,np.pi,7)
239/9: np.linspace(0,np.pi,8)
240/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
240/2: Hist
241/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
241/2: Hist
242/1: r_art
242/2: np.random.randint(low=1,high=3+1,size=N)
242/3: np.random.randint(low=1,high=3+1,size=N)
242/4: np.random.randint(low=1,high=3+1,size=N)
242/5: np.random.randint(low=1,high=3+1,size=N)
242/6: np.random.randint(low=1,high=3+1,size=N)
242/7: np.random.randint(low=1,high=3+1,size=N)
242/8: np.random.randint(low=1,high=3+1,size=N)
242/9: np.random.randint(low=1,high=3+1,size=N)
242/10: np.random.randint(low=1,high=3+1,size=N)
242/11: np.random.randint(low=1,high=3+1,size=N)
242/12: np.random.randint(low=1,high=3+1,size=N)
242/13: np.random.randint(low=1,high=3+1,size=N)
242/14: np.random.randint(low=1,high=3+1,size=N)
242/15: np.random.randint(low=1,high=3+1,size=N)
242/16: np.random.randint(low=1,high=3+1,size=N)
242/17: phi_art
242/18: np.arange(0,8,1)
242/19: np.linspace(0,8,8)
242/20: np.linspace(0,8,8)
242/21: np.linspace(0,8,8)
242/22: np.linspace(0,8,9)
242/23: np.linspace(0,np.pi,8)
242/24: np.arange(1,5,1)
243/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
243/2: Hist
244/1: Hist
244/2: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
244/3: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
244/4: Hist
244/5: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
245/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
246/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
247/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
248/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
249/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
250/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
250/2: np.arange(0,4,1)
251/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
252/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
253/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
254/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
255/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
256/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
257/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
258/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
259/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
260/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
261/1:
import numpy as np
import matplotlib.pyplot as plt

plt.pcolormesh(np.arange(12).reshape(4, 3), edgecolor='#888888', facecolor='none')
plt.show()
262/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
263/1: N = 20
263/2: theta = np.linspace(0.0, 2 * np.pi, N, endpoint=False)
263/3: theta
263/4: np.linspace(0.0,2*np.pi,N)
264/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
265/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
266/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
266/2: Hist
266/3: Hist/1000.
266/4: Hist/10
266/5: Hist/100.
266/6: Hist
266/7: np.arange(1,5,1)
266/8: np.linspace(1,4,4)
267/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
268/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
269/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
269/2: Hist
270/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
271/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
272/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
273/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
274/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
275/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
276/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
277/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
278/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
279/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
280/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
281/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
282/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
283/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
284/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
285/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
286/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
286/2: np.random.seed()
286/3: np.random.seed(seed=1.))
286/4: np.random.seed(seed=1.)
286/5: np.random.seed(seed=1)
286/6: print(np.random.seed(seed=1))
286/7: np.random.seed(1)
286/8: np.random
286/9: np.random(1)
286/10: np.random.random(1)
286/11: np.random.seed(1)
286/12: np.random.random(1)
286/13: np.random.seed(1)
286/14: np.random.random(1)
286/15: np.random.seed(1)
286/16: np.random.random(1)
286/17: np.random.random(1)
287/1: np.random.random(1)
288/1: np.random.random(1)
288/2: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
290/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
291/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
292/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
293/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
294/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
295/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
296/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
297/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
297/2: str(i) for i in np.arange(1,9,1))
297/3: (str(i) for i in np.arange(1,9,1))
297/4: a = (str(i) for i in np.arange(1,9,1))
297/5: a
297/6: a = [str(i) for i in np.arange(1,9,1)]
297/7: a
298/1: a
298/2: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
298/3: np.arange(1,np.pi,8)
298/4: np.linspace(1,np.pi,8,endpoint=False)
299/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
299/2: [x+(2*np.pi/16.) for x in np.linspace(1,2*np.pi,8,endpoint=False)]
299/3: [x+(2*np.pi/16.) for x in np.linspace(0,2*np.pi,8,endpoint=False)]
300/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
301/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
302/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
303/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
305/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
306/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
307/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
308/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
308/2: Hist
309/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
310/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
311/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
312/1: Hist, redges, phiedges, rvals, phivals = polarplot(1,r_art,phi_art)
313/1: d.data()
313/2: d.data
313/3: d.data['det']
313/4: size(d.data['det'])
313/5: rvals = d.get_data(['epq_mask','ssd_0','det_0'],'det')
313/6: rvals
313/7: size(rvals)
314/1: rvals = d.get_data(['epq_mask','ssd_0','det_0'],'det')
314/2: size(rvals)
316/1: rvals = d.get_data(['epq_mask','ssd_0','det_0'],'det')
316/2: size(rvals)
316/3: Hist, redges, phiedges, rvals, phivals = polarplot(d,r_art,phi_art)
317/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,r_art,phi_art)
318/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,r_art,phi_art)
319/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,r_art,phi_art)
319/2: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
320/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
320/2: pylab.hist(rvals,bins=np.arange(0,5))
320/3: rvals
320/4: pylab.close('all')
320/5: pylab.hist(rvals,bins=np.arange(0,5))
320/6: pylab.close('all')
320/7: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
320/8: fig2=pylab.figure()
320/9: ax2 = fig2.gca()
320/10: pylab.hist(rvals,bins=np.arange(0,5))
320/11: pylab.hist(phivals,bins=np.arange(0,5))
320/12: pylab.close('all')
320/13: fig, ax = plt.subplots(1, 1)
320/14: fig, (ax1, ax2) = plt.subplots(2, 1)
321/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
321/2: histograms(rvals,phivals)
322/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
322/2: histograms(rvals,phivals)
323/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
323/2: histograms(rvals,phivals)
324/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
324/2: histograms(rvals,phivals)
325/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
325/2: histograms(rvals,phivals)
326/1: histograms(rvals,phivals)
326/2: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
326/3: histograms(rvals,phivals)
327/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
327/2: histograms(rvals,phivals)
328/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
328/2: histograms(rvals,phivals)
329/1: histograms(rvals,phivals)
329/2: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
329/3: histograms(rvals,phivals)
330/1: histograms(rvals,phivals)
330/2: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
330/3: histograms(rvals,phivals)
331/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
331/2: histograms(rvals,phivals)
332/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
332/2: histograms(rvals,phivals)
333/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
333/2: histograms(rvals,phivals)
334/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
334/2: histograms(rvals,phivals)
335/1: animate_polar(d,'det','sec','ech')
335/2: C, edges = animate_polar(d,'det','sec','ech')
335/3: D
335/4: C
335/5: np.linspace(1,257,1)
335/6: np.array(1,257,1)
335/7: np.arange(1,257,1)
336/1: C, edges = animate_polar(d,'det','sec','ech')
336/2: C
336/3: shape(C)
336/4: C[isnan(C)]=-1
336/5: C
336/6: a_c = -1
336/7: a_c +=1
336/8: a_c
336/9: len(Z)
336/10: Z
336/11: X,Y,Z = edges
336/12: Z
336/13: len(Z)
336/14: a_c = a_c %256
336/15: a_c
336/16: fig = figure()
336/17: ax = fig.gca()
336/18: ANIMCONT=ax.plot([min(Z)],[0.5],linestyle="None",marker="o",markersize=6)
336/19: pylab.close('all')
336/20:
pylab2da = pylab.figure()
        ax_anim = pylab.axes([0.05,0.94,0.9,0.02])
336/21: pylab2da = pylab.figure()
336/22: ax_anim = pylab.axes([0.05,0.94,0.9,0.02])
336/23: ax_anim.set_xlim(min(Z),max(Z))
336/24: ax_anim.set_ylim(0,1)
336/25: Z
336/26: ax_anim.set_xlim(min(Z),max(Z))
336/27: pylab.show()
336/28: ax_anim.set_ylim(0,1)
336/29: pylab.show()
336/30: ANIMCONT=ax_anim.plot([min(Z)],[0.5],linestyle="None",marker="o",markersize=6)
336/31: pylab.show()
336/32: pylab.close('all')
336/33: pylab2da = pylab.figure()
336/34: ax_anim = pylab.axes([0.05,0.94,0.9,0.02])
336/35: ax_anim.set_xlim(min(Z),max(Z))
336/36: pylab.show()
336/37: ax_anim.set_ylim(0,1)
336/38: pylab.show()
336/39: ANIMCONT=ax_anim.plot([min(Z)],[0.5],linestyle="None",marker="o",markersize=6)
336/40: pylab.show()
336/41: ANIMCONT
336/42: shape(ANIMCONT)
336/43: ANIMCONT[0]
336/44: Z.shape()
336/45: Z.shape[0]
336/46: shape(Z)
337/1:
from matplotlib import pyplot as plt

fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)

data = ax.plot(x, sine(x,0))
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(-2,2)

from matplotlib import animation
import matplotlib

def animate(i):
    phase = i * 0.01 * 2 * np.pi
    yvals = np.cos(x)+sine(x, phase)
    data[0].set_data(x, yvals)
    
matplotlib.animation.FuncAnimation(fig, animate, interval=100, blit=False)
337/2:
%matplotlib auto

import numpy as np

def sine(x,phase):
    return np.sin(x+phase)
337/3:
from matplotlib import pyplot as plt

fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)

data = ax.plot(x, sine(x,0))
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(-2,2)

from matplotlib import animation
import matplotlib

def animate(i):
    phase = i * 0.01 * 2 * np.pi
    yvals = np.cos(x)+sine(x, phase)
    data[0].set_data(x, yvals)
    
matplotlib.animation.FuncAnimation(fig, animate, interval=100, blit=False)
343/1: pylab.show()
350/1: ani
350/2: pylab.show()
358/1: Hist, redges, phiedges, rvals, phivals = polarplot(d,'det','sec')
358/2: histograms(rvals,phivals)
358/3: d.show_mask()
358/4: d.hist1d("det",arange(0.,4.1,1.))
358/5: d.set_mask('ech','ech',0,0,reset=True)
358/6: d.set_mask('ech','ssd_0',0,0,reset=True)
358/7: d.set_mask('ssd_0','ech',0,0,reset=True)
358/8: d.hist1d("det",arange(0.,4.1,1.))
358/9: d.set_mask('ssd_0','ech',1,1000,reset=True)
358/10: d.hist1d("det",arange(0.,4.1,1.))
358/11: d.set_mask('ssd_0','ech',5,1000,reset=True)
358/12: d.hist1d("det",arange(0.,4.1,1.))
358/13: d.set_mask('ssd_0','ech',5,1000,reset=True)
358/14: d.hist2d("tof","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1))
358/15: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1))
358/16: d.show_mask()
358/17: d.set_mask('det_0','ech',5,1000,reset=True)
358/18: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1))
358/19: d.show_mask()
358/20: d.set_mask('det_0','det',0,0,reset=True)
358/21: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1))
358/22: d.set_mask('det__0','det',0,0,reset=True)
358/23: d.add_mask('d0')
358/24: d.add_mask('d1')
358/25: d.add_mask('d2')
358/26: d.set_mask('d00','det',0,0,reset=True)
358/27: d.set_mask('d0','det',0,0,reset=True)
358/28: d.set_mask('d1','det',1,1,reset=True)
358/29: d.set_mask('d2','det',2,2,reset=True)
358/30: d.set_mask('Master','ech',5,1000,reset=True)
358/31: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1),smask=["d0","d1","d2"])
360/1:
%matplotlib auto

import numpy as np

def sine(x,phase):
    return np.sin(x+phase)
360/2:
from matplotlib import pyplot as plt

fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)

data = ax.plot(x, sine(x,0))
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(-2,2)

from matplotlib import animation
import matplotlib

def animate(i):
    phase = i * 0.01 * 2 * np.pi
    yvals = np.cos(x)+sine(x, phase)
    data[0].set_data(x, yvals)
    
matplotlib.animation.FuncAnimation(fig, animate, interval=100, blit=False)
360/3:
fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)
XX, YY = meshgrid(x,x)

Z = sine(XX,0)+np.cos(YY)
#Z = Z.T

data = ax.pcolormesh(x,x, Z)
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(0,2*np.pi)

from matplotlib import animation
import matplotlib

def animate2(i):
    phase = i * 0.01 * 2 * np.pi
    B = sine(XX, phase)+np.cos(XX*YY)
    B = B[:-1, :-1]
    data.set_array(B.ravel())
    
matplotlib.animation.FuncAnimation(fig, animate2, interval=100, blit=False)
360/4:
fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)
XX, YY = plt.meshgrid(x,x)

Z = sine(XX,0)+np.cos(YY)
#Z = Z.T

data = ax.pcolormesh(x,x, Z)
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(0,2*np.pi)

from matplotlib import animation
import matplotlib

def animate2(i):
    phase = i * 0.01 * 2 * np.pi
    B = sine(XX, phase)+np.cos(XX*YY)
    B = B[:-1, :-1]
    data.set_array(B.ravel())
    
matplotlib.animation.FuncAnimation(fig, animate2, interval=100, blit=False)
360/5:
fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)
XX, YY = plt.meshgrid(x,x)

Z = sine(XX,0)+np.cos(YY)
#Z = Z.T

data = ax.pcolormesh(x,x, Z)
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(0,2*np.pi)

from matplotlib import animation
import matplotlib

def animate2(i):
    phase = i * 0.01 * 2 * np.pi
    B = sine(XX, phase)+np.cos(XX*YY)
    B = B[:-1, :-1]
    data.set_array(B.ravel())
    
matplotlib.animation.FuncAnimation(fig, animate2, interval=100, blit=False)
360/6:
%matplotlib auto

import numpy as np

def sine(x,phase):
    return np.sin(x+phase)
360/7:
from matplotlib import pyplot as plt

fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)

data = ax.plot(x, sine(x,0))
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(-2,2)

from matplotlib import animation
import matplotlib

def animate(i):
    phase = i * 0.01 * 2 * np.pi
    yvals = np.cos(x)+sine(x, phase)
    data[0].set_data(x, yvals)
    
matplotlib.animation.FuncAnimation(fig, animate, interval=100, blit=False)
360/8:
fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)
XX, YY = meshgrid(x,x)

Z = sine(XX,0)+np.cos(YY)
#Z = Z.T

data = ax.pcolormesh(x,x, Z)
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(0,2*np.pi)

from matplotlib import animation
import matplotlib

def animate2(i):
    phase = i * 0.01 * 2 * np.pi
    B = sine(XX, phase)+np.cos(XX*YY)
    B = B[:-1, :-1]
    data.set_array(B.ravel())
    
matplotlib.animation.FuncAnimation(fig, animate2, interval=100, blit=False)
360/9:
from mpl_toolkits.mplot3d import Axes3D

# For a 3D plot you need to set the axis projection to 3D
ax = pylab.figure(figsize=(5,5)).gca(projection="3d")

# plot_surface needs grid data, i.e. x and y also need to be supplied as grid.
XX, YY = meshgrid(xedges[:-1], yedges[:-1])

ax.plot_surface(XX,YY,Hist,cmap="hot")
360/10:
from matplotlib import pyplot as plt

#Only needed if you want an in-line plot in jupyter notebook
%matplotlib inline 


Fig = plt.figure(figsize(5,3)) #Create a figure with a figure size given by figsize
Ax  = Fig.gca()    #Create and return an axis

import numpy as np
x = np.arange(10)
y = x**2

Ax.plot(x,y)
360/11:
from matplotlib import pyplot as plt

#Only needed if you want an in-line plot in jupyter notebook
%matplotlib inline 


Fig = plt.figure(figsize(5,3)) #Create a figure with a figure size given by figsize
Ax  = Fig.gca()    #Create and return an axis

import numpy as np
x = np.arange(10)
y = x**2

Ax.plot(x,y)
360/12:
x = np.linspace(0,2*np.pi,20)
y = np.sin(x)
y2 = np.cos(x)

fig = plt.figure(figsize=(5,3))
ax = fig.gca()

ax.plot(x,y,color="blue",label="Sin(x)",marker="o")
ax.plot(x,y2,color="red",label="Cos(x)",marker="*")

ax.set_xlim(0,2*np.pi) # Set the x-limit of the axis

ax.set_xlabel("x")     # Set the x-label
ax.set_ylabel("f(x)")  # Set the y-label

ax.legend(loc="best")  # Set the legend
360/13:
fig = plt.figure()
ax  = fig.gca()

# Creates 100 random numbers between 0 and 10
x = np.random.random_sample(200)*10            
y = np.random.random_sample(200)*100
# Create a scatter plot
ax.scatter(x,y, color = "black", label="Scatter")  

 # Creates 100 normal distributed random numbers around 3 with a std of 1
x = np.random.normal(loc=3, size=200)
# Create a histogram with 10 bins
ax.hist(x, bins=10, alpha = 0.5, color="blue", label="Hist")                   

x = np.arange(10)
y = x ** 2
# Fill the area between y and y+10
ax.fill_between(x, y, y+10, alpha=0.5, color="red", label="Fill")

ax.legend()
360/14:
fig = plt.figure()

#Create two axes
ax1 = fig.add_axes([0.1, 0.1, 0.8, 0.8])
ax2 = fig.add_axes([0.2 , 0.2 , 0.3 , 0.3])

# Plot the data 
ax1.plot(np.sin(np.linspace(0 ,2* np.pi ,36)))
ax2.plot(np.cos(np.linspace(0 ,2* np.pi ,36)))
360/15:
fig = plt.figure()
for i in range(4):
    ax = fig.add_subplot(2,2,i+1) #Create an axis at position i on a 2x3 grid
    ax.plot(np.arange(10)+i)
    ax.text(0.1,0.8,"Axis #%i"%(i+1), transform=ax.transAxes) # Create text
360/16:
# Create 2 * 1e6 normal distributed x- and y-values consisting of two distinct normal distributions
xvals = np.append(np.random.normal(15, 2, size=1000000), np.random.normal(20, 5, size=1000000))
yvals = np.append(np.random.normal(10, 3, size=1000000), np.random.normal(15, 2, size=1000000))

# Histogram the data
Hist, xedges, yedges = np.histogram2d(xvals, yvals, bins = (np.arange(10 ,30 ,0.2), np.arange(0 ,20 ,0.2)))
360/17:
# Create two Axes
fig = pylab.figure(figsize(9,3))
ax1 = fig.add_subplot(1,3,1)
ax2 = fig.add_subplot(1,3,2)
ax3 = fig.add_subplot(1,3,3)

# Create iso contour areas
Mesh = ax1.contourf(xedges[:-1], yedges[:-1], Hist, levels = np.arange(0,1000,100), cmap = "hot")

#Create iso contour lines
Mesh = ax2.contour(xedges[:-1], yedges[:-1], Hist, levels=[100,500,1000], colors = ["red","blue","green"])
ax2.clabel(Mesh, fontsize=6, fmt="%i")

# Define a colormap and set the color for values smaller than the defined z limits to white
colormap = plt.cm.get_cmap("spectral")
colormap.set_under("white")

# Create a mesh contour plot (vmin defines the z-limit)
Mesh = ax3.pcolormesh(xedges[:-1], yedges[:-1], Hist, cmap = colormap, vmin = 0.1)

# Create a Colorbar for ax3
colorbar = plt.colorbar(Mesh, ax=ax3)
colorbar.set_label("Intensity")
360/18: Hist = Hist.T
360/19:
# Create two Axes
fig = pylab.figure(figsize(9,3))
ax1 = fig.add_subplot(1,3,1)
ax2 = fig.add_subplot(1,3,2)
ax3 = fig.add_subplot(1,3,3)

# Create iso contour areas
Mesh = ax1.contourf(xedges[:-1], yedges[:-1], Hist, levels = np.arange(0,1000,100), cmap = "hot")

#Create iso contour lines
Mesh = ax2.contour(xedges[:-1], yedges[:-1], Hist, levels=[100,500,1000], colors = ["red","blue","green"])
ax2.clabel(Mesh, fontsize=6, fmt="%i")

# Define a colormap and set the color for values smaller than the defined z limits to white
colormap = plt.cm.get_cmap("spectral")
colormap.set_under("white")

# Create a mesh contour plot (vmin defines the z-limit)
Mesh = ax3.pcolormesh(xedges[:-1], yedges[:-1], Hist, cmap = colormap, vmin = 0.1)

# Create a Colorbar for ax3
colorbar = plt.colorbar(Mesh, ax=ax3)
colorbar.set_label("Intensity")
360/20:
from mpl_toolkits.mplot3d import Axes3D

# For a 3D plot you need to set the axis projection to 3D
ax = pylab.figure(figsize=(5,5)).gca(projection="3d")

# plot_surface needs grid data, i.e. x and y also need to be supplied as grid.
XX, YY = meshgrid(xedges[:-1], yedges[:-1])

ax.plot_surface(XX,YY,Hist,cmap="hot")
360/21:
import pylab
from mpl_toolkits.mplot3d import Axes3D

# For a 3D plot you need to set the axis projection to 3D
ax = pylab.figure(figsize=(5,5)).gca(projection="3d")

# plot_surface needs grid data, i.e. x and y also need to be supplied as grid.
XX, YY = meshgrid(xedges[:-1], yedges[:-1])

ax.plot_surface(XX,YY,Hist,cmap="hot")
360/22:
import pylab
from mpl_toolkits.mplot3d import Axes3D

# For a 3D plot you need to set the axis projection to 3D
ax = pylab.figure(figsize=(5,5)).gca(projection="3d")

# plot_surface needs grid data, i.e. x and y also need to be supplied as grid.
XX, YY = np.meshgrid(xedges[:-1], yedges[:-1])

ax.plot_surface(XX,YY,Hist,cmap="hot")
360/23:
fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)
XX, YY = np.meshgrid(x,x)

Z = sine(XX,0)+np.cos(YY)
#Z = Z.T

data = ax.pcolormesh(x,x, Z)
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(0,2*np.pi)

from matplotlib import animation
import matplotlib

def animate2(i):
    phase = i * 0.01 * 2 * np.pi
    B = sine(XX, phase)+np.cos(XX*YY)
    B = B[:-1, :-1]
    data.set_array(B.ravel())
    
matplotlib.animation.FuncAnimation(fig, animate2, interval=100, blit=False)
360/24:
from matplotlib import pyplot as plt

fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)

data = ax.plot(x, sine(x,0))
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(-2,2)

from matplotlib import animation
import matplotlib

def animate(i):
    phase = i * 0.01 * 2 * np.pi
    yvals = np.cos(x)+sine(x, phase)
    data[0].set_data(x, yvals)
    
matplotlib.animation.FuncAnimation(fig, animate, interval=100, blit=False)
371/1:
%matplotlib auto

import numpy as np

def sine(x,phase):
    return np.sin(x+phase)
371/2:
from matplotlib import pyplot as plt

fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)

data = ax.plot(x, sine(x,0))
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(-2,2)

from matplotlib import animation
import matplotlib

def animate(i):
    phase = i * 0.01 * 2 * np.pi
    yvals = np.cos(x)+sine(x, phase)
    data[0].set_data(x, yvals)
    
matplotlib.animation.FuncAnimation(fig, animate, interval=100, blit=False)
371/3:
fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)
XX, YY = np.meshgrid(x,x)

Z = sine(XX,0)+np.cos(YY)
#Z = Z.T

data = ax.pcolormesh(x,x, Z)
ax.set_xlabel("x")
ax.set_xlabel("y")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(0,2*np.pi)

from matplotlib import animation
import matplotlib

def animate2(i):
    phase = i * 0.01 * 2 * np.pi
    B = sine(XX, phase)+np.cos(XX*YY)
    B = B[:-1, :-1]
    data.set_array(B.ravel())
    
matplotlib.animation.FuncAnimation(fig, animate2, interval=100, blit=False)
379/1: i
385/1: %run EQ_positions_gui_OOP.py
385/2: %run EQ_positions_gui2.py
385/3: cd EQ_positions_gui/
385/4: %run EQ_positions_gui_OOP.py
388/1: animate_polar(d,'det','sec','epq')
389/1: animate_polar(d,'det','sec','epq')
390/1: animate_polar(d,'det','sec','epq')
390/2: H = animate_polar(d,'det','sec','epq')
390/3: shape(H)
391/1: H = animate_polar(d,'det','sec','epq')
392/1: H = animate_polar(d,'det','sec','epq')
392/2: z = H[:,:,0]
392/3: z
392/4: z.ravel()
393/1: M = animate_polar(d,'det','sec','epq')
393/2: M
393/3: shape(M)
394/1: M = animate_polar(d,'det','sec','epq')
394/2: M = animate_polar(d,'det','sec','epq')
395/1: M = animate_polar(d,'det','sec','epq')
396/1: M = animate_polar(d,'det','sec','epq')
396/2: M
396/3: M.ravel()
398/1: animate_polar(d,'det','sec','epq')
399/1: animate_polar(d,'det','sec','epq')
403/1: animate_polar(d,'det','sec','epq')
404/1: animate_polar(d,'det','sec','epq')
409/1: animate_polar(d,'det','sec','epq')
409/2: d
410/1: animate_polar(d,'det','sec','epq')
413/1: test()
414/1: animate_polar(d,'det','sec','epq')
415/1: animate_polar(d,'det','sec','epq')
416/1: animate_polar(d,'det','sec','epq')
428/1: a,z = animate_polar(d,'det','sec','epq')
428/2: z
428/3: z.shape[0]
432/1: %run uswipha.py
432/2: %run uswipha.py
433/1: %run uswipha.py
433/2: d = uswipha(year=[1992],tf=[[1,50]])
433/3: d.sync_swoops()
433/4:
d.animate2d(prodx='tch',prody="ech",prodz="epq"




)
435/1: %run uswipha.py
436/1: aaaad
437/1: a
437/2: a = animate_polar(d,'det','sec','epq')
438/1: Z = animate_polar(d,'det','sec','epq')
438/2: Z
438/3: C = 0
438/4: C = C/(len(Z)-1)
438/5: C
438/6:
def func(x):
    x = x%(len(Z)-1)
438/7:
def func(x):
    x = x%(len(Z)-1)
    return x
438/8: func(1)
438/9: func(0)
438/10: func(100)
438/11: func(10)
443/1: a = Animation(d,"sec","det","ech")
443/2: a = Animation(d,"sec","det","ech")
444/1: a = Animation(d,"sec","det","ech")
445/1: a = Animation(d,"sec","det","ech")
446/1: a = Animation(d,"sec","det","ech")
447/1: a = Animation(d,"sec","det","ech")
447/2: a.d
447/3: a.data
448/1: a = Animation(d,"sec","det","ech")
448/2: a.rvals
451/1: T = Test()
451/2: T = Test
451/3: T
451/4: T
451/5: T = Test
451/6: T = Test()
451/7: T = Test()
452/1: T = Test()
453/1: T = Test()
454/1: A = Animation()
454/2: A = Animation(d,'sec','det','epq')
454/3: A.zvals
455/1: A = Animation(d,'sec','det','epq')
456/1: A = Animation(d,'sec','det','epq')
457/1: A = Animation(d,'sec','det','epq')
458/1: A = Animation(d,'sec','det','epq')
459/1: A = Animation(d,'sec','det','epq')
459/2: A.
459/3: A.animate_polar()
459/4: animate_polar(A)
460/1: A.animate_polar()
460/2: A = Animation(d,'sec','det','epq')
460/3: A.animate_polar()
461/1: A = Animation(d,'sec','det','epq')
461/2: A.animate_polar()
462/1: A = Animation(d,'sec','det','epq')
462/2: A.animate_polar()
463/1: T = Test()
464/1: T = Test()
465/1: T = Test()
466/1: test = Animation()
466/2: test = Animation(d,"det","sec","epq")
466/3: t.animate2d()
466/4: test.animate2d()
467/1: test = Animation(d,"det","sec","epq")
467/2: test.aanimate2d()
468/1: test = Animation(d,"det","sec","epq")
468/2: test.animate_polar()
469/1: T = Test()
469/2: T.say_hello()
470/1: T = Test()
470/2: test = Animation(d,"det","sec","epq")
470/3: test.animate_polar()
471/1: test = Animation(d,"det","sec","epq")
471/2: test.animate_polar()
472/1: test = Animation(d,"det","sec","epq")
472/2: test.animate_polar()
473/1: test = Animation(d,"det","sec","epq")
473/2: test.animate_polar()
474/1: t = Test()
475/1: test = Animation(d,"det","sec","epq")
475/2: test.animate_polar()
476/1: test = Animation(d,"det","sec","epq")
476/2: test.animate_polar()
477/1: test = Animation(d,"det","sec","epq")
477/2: test.animate_polar()
478/1: test = Animation(d,"det","sec","epq")
478/2: a = test.animate_polar()
478/3:
# Create two Axes
fig = pylab.figure(figsize(9,3))
ax1 = fig.add_subplot(1,3,1)
ax2 = fig.add_subplot(1,3,2)
ax3 = fig.add_subplot(1,3,3)

# Create iso contour areas
Mesh = ax1.contourf(xedges[:-1], yedges[:-1], Hist, levels = np.arange(0,1000,100), cmap = "hot")

#Create iso contour lines
Mesh = ax2.contour(xedges[:- yedges[:-1], Hist, levels=[100,500,1000], colors = ["red","blue","green"])
ax2.clabel(Mesh, fontsize=6, fmt="%i")

# Define a colormap and set the color for values smaller than the defined z limits to white
colormap = plt.cm.get_cmap("spectral")
colormap.set_under("white")

# Create a mesh contour plot (vmin defines the z-limit)
Mesh = ax3.pcolormesh(xedges[:-1], yedges[:-1], Hist, cmap = colormap, vmin = 0.1)

# Create a Colorbar for ax3
colorbar = plt.colorbar(Mesh, ax=ax3)
colorbar.set_label("Intensity")
478/4: d.animate_polar('det','sec','epq')
478/5: d.polarplot('det','sec')
479/1: d.polarplot('det','sec')
482/1: d.test()
483/1: d.test()
483/2: d
483/3: type(d)
483/4: test(d)
487/1: a = Animation()
487/2: test = Animation(d,"det","sec","epq")
487/3: test.animate_polar()
488/1: a = Animation(d,"sec","det","ech")
488/2: a.animate_polar()
489/1: test = Animation(d,"det","sec","epq")
489/2: test.animate_polar()
489/3: test = Animation(d,"det","sec","epq")
489/4: test.animate_polar()
489/5: a = Animation(d,"sec","det","ech")
489/6: a = Animation(d,"sec","det","epq")
489/7: a.animate_polar()
490/1: a = Animation(d,"sec","det","epq")
490/2: test = Animation(d,"det","sec","epq")
490/3: test.animate_polar()
491/1: test = Animation(d,"det","sec","epq")
491/2: test.animate_polar()
492/1: test = Animation(d,"det","sec","epq")
492/2: test.animate_polar()
493/1: test = Animation(d,"det","sec","epq")
493/2: test.animate_polar()
494/1: test = Animation(d,"det","sec","epq")
494/2: test.animate_polar()
495/1: test = Animation(d,"det","sec","epq")
495/2: test.animate_polar()
496/1: test = Animation(d,"det","sec","epq")
496/2: test.animate_polar()
497/1: test = Animation(d,"det","sec","epq")
497/2: test.animate_polar()
497/3: fig = pylab.figure()
497/4: ax_anim = pylab.axes([0.05,0.94,0.9,0.02])
497/5: ax_bar
497/6: ax_anim.xaxis.set_ticks_position("top")
497/7: pylab.show()
498/1: t = Test()
498/2: t = Test('g')
498/3: t.func()
499/1: t = Test('g')
499/2: t.func()
500/1: test = Animation(d,"det","sec","epq")
500/2: test.animate_polar()
501/1: test = Animation(d,"det","sec","epq")
501/2: test.animate_polar()
502/1: test = Animation(d,"det","sec","epq")
502/2: test.animate_polar()
503/1: test = Animation(d,"det","sec","epq")
503/2: test.animate_polar()
504/1: test = Animation(d,"det","sec","epq")
504/2: test.animate_polar()
505/1: test = Animation(d,"det","sec","epq")
505/2: test.animate_polar()
506/1: test = Animation(d,"det","sec","epq")
506/2: test.animate_polar()
507/1: test = Animation(d,"det","sec","epq")
507/2: test.animate_polar()
508/1: test = Animation(d,"det","sec","epq")
508/2: test.animate_polar()
509/1: d
509/2: d.add__mask('doubles','ech',0,0)
509/3: d.add_mask('doubles','ech',0,0)
509/4: d.add_mask('doubles','ech')
509/5: d.add_mask('doubles')
509/6: d.set_mask('doubles','ech',0,0)
509/7: d.set_mask('trebles','ech',0,0)
509/8: d.add_mask('trebles')
509/9: d.set_mask('trebles','ech',5,500)
509/10: d.hist1d('det',smask=["doubles","trebles"])
510/1: d.add_mask('doubles')
510/2: d.add_mask('trebles')
510/3: d.set_mask('trebles','ech',5,500)
510/4: d.set_mask('doubles','ech',0,0)
510/5: d.hist1d('det',smask=["doubles","trebles"])
510/6: np.linspace(1,4,4)
510/7: binr,rvals,redges = polarplot(d,'det','sec')
510/8: binr
511/1: redges = polarplot(d,'det','sec')
511/2: redges
512/1: rvals,binr,redges = polarplot(d,'det','sec')
512/2: rvals
512/3: unique(rvals)
512/4: binr
512/5: np.linspace(0,3,4)
513/1: rvals,binr,redges = polarplot(d,'det','sec')
513/2: rvals
513/3: binr
513/4: redges
513/5: polarplot(d,'det','sec')
514/1: a = Animation(d,"sec","det","epq")
514/2: a.animate_polar()
515/1: a = Animation(d,"det","sec","epq")
516/1: a = Animation(d,"det","sec","epq")
516/2: a.animate_polar()
516/3: d.hist2d('tch','epq')
517/1: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1))
518/1: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1))
519/1: a = Animation(d,"det","sec","epq")
519/2: a.animate_polar()
520/1: a = Animation(d,"det","sec","epq")
520/2: a.animate_polar()
521/1: a = Animation(d,"det","sec","epq")
521/2: a.animate_polar()
522/1: a = Animation(d,"det","sec","epq")
522/2: a.animate_polar()
522/3: 68%(68)
522/4: 69%(68)
523/1: a = Animation(d,"det","sec","epq")
523/2: a.animate_polar()
524/1: a = Animation(d,"det","sec","epq")
524/2: a.animate_polar()
525/1: a = Animation(d,"det","sec","epq")
525/2: a.animate_polar()
526/1: a = Animation(d,"det","sec","epq")
526/2: a.animate_polar()
526/3: d.show_mask()
527/1: a = Animation(d,"det","sec","epq")
527/2: a.animate_polar()
527/3: d.hist2d
527/4: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1))
527/5: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1),smask=["ssd_0"])
527/6: d.hist2d("tch","epq",binx=arange(10.,1024.1,1.),biny=arange(0.,65.,1),smask=["Master"])
527/7: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
527/8: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60),smask=('Master'))
527/9: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60),smask='Master')
527/10: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60),smask=['Master'])
527/11: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(250,500,2),biny=arange(1,200,2),binz=arange(10,60),smask=['Master'])
527/12: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(250,500,2),biny=arange(1,200,2),binz=arange(10,60),smask=['Master','ssd_0'])
527/13: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(0,200,2),binz=arange(10,60),smask=['Master','ssd_0'])
527/14: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(0,200,2),binz=arange(10,60),smask=['Master','ssd_0'])
527/15: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(250,500,2),biny=arange(1,200,2),binz=arange(10,60),smask=['Master','ssd_0'])
530/1: a = Test()
530/2: a
530/3: a.test()
530/4: test(a)
530/5: a
530/6: a.test()
531/1: a = Test()
531/2: a.test()
531/3: a.test()
532/1: t = Test()+
532/2: t = Test()
532/3: t.d
532/4: t.test()
532/5: t.test()
532/6: t = Test()
532/7: t.test()
532/8: t = Test()
532/9: t.test()
533/1: t = Test()
533/2: t.test()
533/3: t = Test()
533/4: t.test()
535/1: t = Test()
535/2: t.test()
535/3: t = Test()
535/4: t.test()
535/5: t.test()
535/6: t.test()
535/7: t.test_2()
535/8: t = Test()
535/9: t.test_2()
535/10: t = Test()
536/1: d.polarplot('det','sec')
536/2: d.polarplot('det','sec')
536/3: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(250,500,2),biny=arange(1,200,2),binz=arange(10,60),smask=['Master','ssd_0'])
536/4: d
536/5: polarplot(d,'det','sec')
536/6: a = np.array([1,2,3,4,5])
536/7: b = np.array([1,1,5,5,5])
536/8: H,e,r = nphist2d(a,b)
536/9: H,e,r = np.hist2d(a,b)
536/10: H,e,r = np.histogram2d(a,b)
536/11: H
541/1: a = Test()
541/2: a.d
541/3: a.d.get_data('sec')
541/4: a.d
541/5: a.d.get_data('Master','sec')
541/6: a.test()
541/7: a.test()
541/8: a = Test()
541/9: a.test()
542/1: t = Test()
542/2: t.test()
542/3: t = Test()
542/4: t.test()
545/1: d
545/2: test(d)
545/3: test(d)
546/1: %run test.py
546/2: d
546/3: %run test2.py
546/4: d
546/5: mult(d)
547/1: %run load_pui_ulysses.py
547/2: %run pui_ulysses.py
548/1: %run load_pui_ulysses.py
548/2: %run pui_ulysses.py
548/3: A = Animation(d,'sec','det','epq')
548/4: A.animate_polar()
548/5: A = Animation(d,'det','sec','epq')
548/6: A.animate_polar()
549/1: %run load_pui_ulysses.py
549/2: d
549/3: d.get_data('Master','epq')
549/4: e = d.get_data('Master','epq')
549/5: unique(e)
549/6: %run pui_ulysses.py
549/7: d.get_data
549/8: d.data
549/9: A = Animation(d,'det','sec','ech')
549/10: A.animate_polar()
549/11: A.animate_polar()
549/12: %run pui_ulysses.py
549/13: A = Animation(d,'det','sec','ech')
549/14: A.animate_polar()
550/1: %run load_pui_ulysses.py
550/2: %run pui_ulysses.py
550/3: A = Animation(d,'det','sec','ech')
550/4: A.animate_polar()
550/5: pylab.close('all')
550/6: %run pui_ulysses.py
550/7: A = Animation(d,'det','sec','ech')
550/8: A.animate_polar()
550/9: %run pui_ulysses.py
550/10: %run pui_ulysses.py
550/11: pylab.close('all')
550/12: A = Animation(d,'det','sec','ech')
550/13: A.animate_polar()
550/14: %run pui_ulysses.py
550/15: A = Animation(d,'det','sec','ech')
550/16: A = Animation(d,'det','sec','epq')
550/17: A.animate_polar()
550/18: A.animate_polar()
550/19: pylab.close('all')
550/20: A = Animation(d,'det','sec','ech')
550/21: A.animate_polar()
550/22: pylab.close('all')
550/23: A = Animation(d,'det','sec','tch')
550/24: A.animate_polar()
550/25: %run pui_ulysses.py
550/26: A = Animation(d,'det','sec','tch')
550/27: A.animate_polar()
550/28: np.arange(1,70,1)
550/29: A.zvals
550/30: unique(A.zvals)
550/31: max(A.zvals)
550/32: %run pui_ulysses.py
550/33: %run pui_ulysses.py
550/34: pylab.close('all')
550/35: A = Animation(d,'det','sec','tch')
550/36: A.animate_polar()
550/37: pylab.close('all')
550/38: A = Animation(d,'det','sec','epq')
550/39: A.animate_polar()
550/40: pylab.close('all')
550/41: A = Animation(d,'det','sec','ech')
550/42: A.animate_polar()
550/43: A.animate_polar()
550/44: pylab.close('all')
550/45: %run pui_ulysses.py
550/46: pylab.close('all')
550/47: A = Animation(d,'det','sec','ech')
550/48: A = Animation(d,'det','sec','epq')
550/49: A.animate_polar()
550/50: A.Hist
550/51: max(A.Hist)
550/52: np.argmax(A.Hist)
550/53: np.argmin(A.Hist)
550/54: unique(A.Hist)
550/55: A.Hist
550/56: shape(A.Hist)
550/57: A.Hist(:,:,1)
550/58: A.Hist(1)
550/59: A.Hist[1]
550/60: A.Hist[:,:,1]
550/61: e = A.Hist[:,:,1]
550/62:
for i in e:
    print i
550/63: np.argmax(e)
550/64: np.max(e)
550/65: np.min(e)
550/66: np.min(A.Hist)
550/67: np.max(A.Hist)
550/68: e[e>0]
550/69: e
550/70: e[1,1] = 0.
550/71: e
550/72: e[e>0]
550/73: %run pui_ulysses.py
550/74: A = Animation(d,'det','sec','epq')
550/75: A.animate_polar()
550/76: A.Quadmesh.vmin
550/77: A.Quadmesh
550/78: %run pui_ulysses.py
550/79: A = Animation(d,'det','sec','epq')
550/80: A.animate_polar()
550/81: A.Quadmesh.vmin
550/82: A.Quadmesh.get_edgecolors
550/83: A.Quadmesh.colorbar
550/84: A.Quadmesh
550/85: A.Quadmesh.get_array()
550/86: np.max(A.Hist)
550/87: np.min(A.Hist)
551/1: %run load_pui_ulysses.py
551/2: %run pui_ulysses.py
551/3: %run pui_ulysses.py
551/4: A = Animation(d,'det','sec','epq')
551/5: A.animate_polar()
551/6: %run pui_ulysses.py
551/7: %run pui_ulysses.py
551/8: A = Animation(d,'det','sec','epq')
551/9: A = Animation(d,'det','sec','epq')
551/10: A.animate_polar()
551/11: %run pui_ulysses.py
551/12: A = Animation(d,'det','sec','epq')
551/13: A.animate_polar()
551/14: %run pui_ulysses.py
551/15: A = Animation(d,'det','sec','epq')
551/16: A.animate_polar()
551/17: %run pui_ulysses.py
551/18: A = Animation(d,'det','sec','epq')
551/19: A.animate_polar()
551/20: %run pui_ulysses.py
551/21: pylab.close('all')
551/22: %run pui_ulysses.py
551/23: A = Animation(d,'det','sec','epq')
551/24: A.animate_polar()
551/25: %run pui_ulysses.py
551/26: A = Animation(d,'det','sec','epq')
551/27: A.animate_polar()
551/28: %run pui_ulysses.py
551/29: %run pui_ulysses.py
551/30: %run pui_ulysses.py
551/31: %run pui_ulysses.py
551/32: %run pui_ulysses.py
551/33: A = Animation(d,'det','sec','epq')
551/34: %run pui_ulysses.py
551/35: A = Animation(d,'det','sec','epq')
551/36: A.animate_polar()
551/37: %run pui_ulysses.py
551/38: A = Animation(d,'det','sec','epq')
551/39: A.animate_polar()
551/40: %run pui_ulysses.py
551/41: pylab.close('all')
551/42: %run pui_ulysses.py
551/43: A = Animation(d,'det','sec','epq')
551/44: A.animate_polar()
551/45: %run pui_ulysses.py
551/46: A = Animation(d,'det','sec','epq')
551/47: A.animate_polar()
551/48: pylab.close('all')
551/49: %run pui_ulysses.py
551/50: A = Animation(d,'det','sec','epq')
551/51: A.animate_polar()
551/52: pylab.close('all')
551/53: %run pui_ulysses.py
551/54: A = Animation(d,'det','sec','epq')
551/55: A.animate_polar()
551/56: A = Animation(d,'det','sec','epq')
551/57: A.animate_polar()
551/58: pylab.close('all')
551/59: %run pui_ulysses.py
551/60: A = Animation(d,'det','sec','epq')
551/61: A.animate_polar()
551/62: %run pui_ulysses.py
551/63: A = Animation(d,'det','sec','epq')
551/64: A.animate_polar()
551/65: %run pui_ulysses.py
551/66: A = Animation(d,'det','sec','epq')
551/67: A.animate_polar()
551/68: %run pui_ulysses.py
551/69: A = Animation(d,'det','sec','epq')
551/70: A.animate_polar()
551/71: A.animate_polar()
551/72: A.animate_polar()
551/73: %run pui_ulysses.py
551/74: A = Animation(d,'det','sec','epq')
551/75: A.animate_polar()
551/76: %run pui_ulysses.py
551/77: %run pui_ulysses.py
551/78: A = Animation(d,'det','sec','epq')
551/79: A.animate_polar()
551/80: A = Animation(d,'det','sec','epq',scale="overall")
551/81: A.animate_polar()
551/82: %run pui_ulysses.py
551/83: A = Animation(d,'det','sec','epq',scale="overall")
551/84: A.animate_polar()
551/85: A = Animation(d,'det','sec','epq',scale="onestep")
551/86: A.animate_polar()
551/87: A = Animation(d,'det','sec','epq')
551/88: A.animate_polar()
551/89: pylab.close('all')
551/90: ls
551/91: cd ..
551/92: ls
551/93: cd ..
551/94: ls
551/95: f = open('ulysses_daily_heliocentric_data_1990-2009.txt','r')
551/96: f.readline()
551/97: f.readline(5)
551/98: f = open('ulysses_daily_heliocentric_data_1990-2009.txt','r')
551/99:
for i in range(0,5):
    f.readline()
551/100: f.readline()
551/101: range(0,5)
551/102: range(4)
551/103: f = open('ulysses_daily_heliocentric_data_1990-2009.txt','r')
551/104:
for i in range(4):
    f.readline()
551/105: h = f.readline()
551/106: a = h.split()
551/107: a
551/108: ls
551/109: cd software/libulpy/
551/110: ös
551/111: ls
551/112: %run uswo
551/113: %run uswo
551/114: swo = uswo()
551/115: swo = uswo(year =2000,tf='all')
551/116: swo = uswo()
551/117: %run uswo
551/118: swo = uswo(year =2000,tf=[0,10])
551/119: swo = uswo(year =2000,tf='all')
551/120: a = 'hi'
551/121: a.split()
552/1: t = open('ulysses_daily_heliocentric_data_1990-2009.txt','r')
552/2:
for i in range(4):
    t.readline()
552/3: h = t.readline()
552/4: k = h.split()
552/5:
for key in k:
    key = key.split()
    print(key[0])
552/6: data[key[0]]=[]
555/1: %run uswo.py
555/2: swo = uswo(year =[2000],tf=[[1,16]])
555/3: swo.data.keys
555/4: swo.data.keys()
555/5: swo.data
555/6: swo.data.keys()
555/7: swo.keys
555/8: %run uswo_backup.py
555/9: swo = uswo(year =[2000],tf=[[1,16]])
555/10: swo.keys
555/11: %run uswo.py
555/12: swo = uswo(year =[2000],tf=[[1,16]])
555/13: %run uswo.py
555/14: swo = uswo(year =[2000],tf=[[1,16]])
555/15: %run uswo.py
555/16: swo = uswo(year =[2000],tf=[[1,16]])
555/17: %run uswo.py
555/18: swo = uswo(year =[2000],tf=[[1,16]])
556/1: %run uswo.py
556/2: swo = uswo(year =[2000],tf=[[1,16]])
556/3: %run uswo.py
556/4: swo = uswo(year =[2000],tf=[[1,16]])
556/5: abc = ['a','b','c']
556/6:
for i in enumerate(abc):
    +
556/7:
for i,j in enumerate(abc):
    print(i,j)
556/8: fname
556/9: fname = "%s%.4i/%.3i.dat"%(self.path,year,doy)
556/10: fname = "%s%.4i/%.3i.dat"%(swo.path,2000,001)
556/11: fname
556/12: fin = open(fname,'r')
556/13: s = fin.readline()
556/14:
for s in fin:
    k = s.split()
    print(k)
556/15:
for s in fin:
    k = s.split()
    for i,key in enumerate(swo.keys):
        print(i,key)
556/16: fin = open(fname,'r')
556/17: s = fin.readline()
556/18:
for s in fin:
    k = s.split()
    for i,key in enumerate(swo.keys):
        print(i,key)
556/19: fin = open(fname,'r')
556/20: s = fin.readline()
556/21: s = fin.readline()
556/22: s
556/23: k = s.split()
556/24:
for i,key in enumerate(swo.keys):
    print(k[i])
556/25: swo.keys
556/26: swo.data
557/1: %run uswo.py
557/2: %run uswo.py
557/3: swo = uswo(year =[2000],tf=[[1,16]])
557/4: %run uswo.py
557/5: swo = uswo(year =[2000],tf=[[1,16]])
557/6: swo.data
557/7: %run uswipha.py
557/8: %run uswipha.py
557/9: u = uswipha(year=[2000],tf=[[1,16]])
557/10: u.data
557/11: u.data.values()
557/12: u.data.keys()
557/13: u.data('year')
557/14: u.data['year']
557/15: y = u.data['year']
557/16: e = u.data['ech']
557/17: len(y)
557/18: len(e)
557/19: e = u.data['doy']
557/20: e
557/21: len(e)
557/22: ee = unique(e)
557/23: ee
557/24: len(ee)
557/25: yy = unique(y)
557/26: yy
557/27: u = uswipha(year=[2000,2001,2002,2003],tf=[[1,16]])
557/28: d = u.data['doy']
557/29: y = u.data['year']
557/30: yy = unique(y)
557/31: yy
557/32: dd = unique(d)
557/33: dd
557/34: len(dd)
557/35: len(yy)
557/36: 6708/365.
557/37: dd
557/38:
for i in dd:
    print(i)
557/39: 6708/15.
557/40: 6708/16.
557/41: u.data['tof']
557/42: u.data['tch']
557/43: u.sync_swoops()
557/44: u.data()
557/45: u.data
557/46: %run uswo.py
557/47: swo = uswo(year =[2000],tf=[[1,16]])
557/48: swo.data
557/49: len(swo.data['year'])
557/50: swo = uswo(year =[2000],tf=[[1,2]])
557/51: len(swo.data['year'])
557/52: len(swo.data['doy'])
557/53: swo.data['doy']
557/54: %run uswipha.py
557/55: u = uswipha(year=[2000],tf=[[1,16]])
557/56: u.data['year']
557/57: len(u.data['year'])
557/58: u.sync_swoops()
557/59: len(u.data['vsw'])
557/60: u.data
557/61: %run uswo.py
557/62: swo = uswo(year =[2000],tf=[[1,2]])
557/63: swo.data
557/64: offy = swo.data['year'] -1990
557/65: offy
557/66: offd = offy*365 + (offy.astype(int)+2)/4
557/67: offd
557/68: offy.astype(int)
557/69: offy.astype(int)+2
557/70: (offy.astype(int)+2)/4
557/71: offy
559/1: %run uswipha.py
559/2: u = uswipha(year=[2000,2001],tf=[[1,16]])
559/3: u.data['d90']
559/4: u.data
559/5: d.sync_swoops()
559/6: u.sync_swoops()
559/7: u.data
559/8: u.data['d90']
560/1: %run uswo.py
560/2: swo = uswo(year =[2000],tf=[[1,11]])
560/3: uswo_d = uswo.calc_d90()
560/4: uswo_d = calc_d90(uswo)
560/5: calc_d90
560/6: calc_d90
560/7: %run uswo.py
560/8: swo = uswo(year =[2000],tf=[[1,11]])
560/9: calc_d90
560/10: uswo.calc_d90()
560/11: calc_90(uswo)
560/12: calc_d90(uswo)
560/13: %run uswo.py
560/14: swo = uswo(year =[2000],tf=[[1,11]])
560/15: calc_d90(uswo)
560/16: uswo.calc_d90
560/17: uswo.calc_d90()
560/18: swo.calc_d90()
560/19: %run uswo.py
560/20: swo = uswo(year =[2000],tf=[[1,11]])
560/21: swo_d = swo.calc_d90()
560/22: swo_d.data
560/23: swo_d.data()
560/24: swo.data
560/25: swo.calc_d90()
560/26: swo.data['d90']
560/27: len(swo.data['d90'])
560/28: len(swo.data['year'])
560/29: swo.data['doy']
560/30: %run uswo.py
560/31: swo = uswo(year =[2000],tf=[[1,11]])
560/32: d = swo.data['doy']
560/33: d
560/34: swo.calc_doy()
560/35: swo.calc_d90()
560/36: swo.data['doy']
560/37: swo.data['d90']
560/38: 2000-1990
560/39: 10*365
560/40: 10+2
560/41: 12/4
560/42:
for i in enumerate(swo.data['d90']):
    print(swo.data['d90'][i])
560/43: swo.data['d90'](0)
560/44: swo.data['d90'][0]
560/45:
for i,j in enumerate(swo.data['d90']):
    print(swo.data['doy'][i],j)
560/46: swo.data['year']
560/47: a,b =unique(swo.data['year'])
560/48: a,b =np.unique(swo.data['year'])
560/49: import numpy as np
560/50: a,b =np.unique(swo.data['year'])
560/51: np.unique(swo.data['year'])
560/52: np.unique(swo.data['year'])
560/53: unique
560/54: np.unique
560/55: a,b =np.unique(swo.data['year'],return_inverse=True)
560/56: a
560/57: b
560/58: np.unique(b)
560/59: c = np.array[1,2,3,4,1,2,1,2,1,1,1]
560/60: c = np.array([1,2,3,4,1,2,1,2,1,1,1])
560/61: a,b =np.unique(c,return_inverse=True)
560/62: a
560/63: c
560/64: b
560/65: c = np.array([1,2,3,4,1,2,1,2,1,1,100])
560/66: a,b =np.unique(c,return_inverse=True)
560/67: b
560/68: uTi,index = unique(swo.data['d90'],return_inverse = True)
560/69: uTi,index = np.unique(swo.data['d90'],return_inverse = True)
560/70: uTi
561/1: %run uswo.py
561/2: swo = uswo(year =[2000],tf=[[1,3]])
561/3: swo.data()
561/4: swo.data
561/5: swo.data['year']
561/6: len(swo.data['year'])
561/7: swo = uswo(year =[2000],tf=[[1,1]])
561/8: len(swo.data['year'])
561/9: swo = uswo(year =[2000],tf=[[1,2]])
561/10: len(swo.data['year'])
561/11: swo = uswo(year =[2000],tf=[[1,3]])
561/12: len(swo.data['year'])
561/13: uTi,index = np.unique(swo.data['d90'],return_inverse = True)
561/14: from numpy import unique
561/15: uTi,index = unique(swo.data['d90'],return_inverse = True)
561/16: swo.calc_dd90()
561/17: swo.calc_d90()
561/18: uTi,index = unique(swo.data['d90'],return_inverse = True)
561/19: uTi
561/20: len(uTi)
561/21: len(swo.data['year'])
561/22: index
561/23: uTi=append(uTi,uTi[-1]+1./24./5.)
561/24: from numpy import np
561/25: from numpy import append
561/26: uTi=append(uTi,uTi[-1]+1./24./5.)
561/27: uTi
561/28: len(uTi)
561/29: a = 0
561/30: (a.astype(int)+2)/4
561/31: import numpy as np
561/32: year = np.array([1990,1990,1990])
561/33: day = np.array([1.,2.,3.])
561/34: (year.astype(int)+2)/4
561/35: year = year-1990
561/36: (year.astype(int)+2)/4
561/37: (year.astype(int)+2)
561/38: 2/4
561/39: 1./24./5.
561/40: 1./24./30.
561/41: swo
561/42: swo()
561/43: swo.data
561/44: swo.data['doy']
561/45: %run uswipha.py
561/46: u = uswipha(year=[2000],tf=[[1,3]])
561/47: u.data['doy']
561/48: swo.data['d90']
561/49: u.calc_d90()
561/50: uTi,index=unique(u.data["d90"],return_inverse=True)
561/51: uTi
561/52: u.data['doy']
561/53: 10*365+(10+2)/4
561/54: uTi=append(uTi,uTi[-1]+1./24./5.)
561/55: uTi
561/56: uTi=uTi+1./24./30.
561/57: uTi
561/58: n,x = histogram([1.,2.,3.,4.],bins=[0.,2.,5.])
561/59: n
561/60: x
561/61: n,x = histogram([1.,2.,3.,4.],bins=np.arange(0,5,0.5))
561/62: n
561/63: x
561/64: v,x = histogram([1.,2.,3.,4.],bins=np.arange(0,5,0.5),weights=[1.,2.,3.,4.])
561/65: v
561/66: x
561/67: v = v/n
561/68: v
561/69: v[isnan(v)]=0.
561/70: v
561/71: mask = swo.data["vges"]>0
561/72:
nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
        vsw,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["vges"])
561/73: nrT
561/74: nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
561/75: vsw,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["vges"])
561/76: nrT
561/77: vsw
561/78: swo.data['d90']
561/79: uTi
561/80: swo.data['d90'][0:10]
561/81: uTi[0:10]
561/82: x[0:10]
561/83: vsw,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["vges"])
561/84: vsw
561/85: a = [1,,2,3,4,5,6,7,8,9,1,1,1,1,2,2,3,1,1]
561/86: a = [1,2,3,4,5,6,7,8,9,1,1,1,1,2,2,3,1,1]
561/87: b = np.arange(0,10,2)
561/88: n = histogram(a,bins=b)
561/89: n
561/90: n,x = histogram(a,bins=b)
561/91: n
561/92: x
561/93: len(a)
561/94: v,x = histogram(a,bins=b,weights=a)
561/95: v
561/96: x
561/97: a
561/98: n
561/99: v
561/100: vv=v/n
561/101: vv
561/102: uTi
561/103: nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
561/104: vsw,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["vges"])
561/105: nrT
561/106: vsw
561/107: vsw/nrT
561/108: b =[0,1,2,3]
561/109: a=[0.5,0.5,1.5,2.5]
561/110: v=[420,400,480,400]
561/111: n = histogram(a,bins=b)
561/112: n
561/113: v,x = histogram(a,bins=b,weights=v)
561/114: v
561/115: v/n
561/116: n,x = histogram(a,bins=b)
561/117: v/n
561/118: %run uswo.py
561/119: swo = uswo(year =[2000],tf=[[1,2]])
561/120: %run uswipha.py
561/121: u = uswipha(year=[2000],tf=[[1,2]])
561/122: d.data['year']
561/123: len(u.data['year'])
561/124: len(swo.data['year'])
561/125: len(swo.data['vsw'])
561/126: len(swo.data['vges'])
561/127: u.sync_swoops()
561/128: len(swo.data['vges'])
561/129: len(u.data['year'])
561/130: len(u.data['vsw'])
561/131: clc
562/1: %run uswo.py
562/2: swo = uswo(year =[2000],tf=[[1,2]])
562/3: %run uswipha.py
562/4: u = uswipha(year=[2000],tf=[[1,2]])
562/5: swo.calc_d90()
562/6: u.calc_d90()
562/7: uTi,index = unique(swo.data['d90'],return_inverse = True)
562/8: uTi,index = unique(u.data['d90'],return_inverse = True)
562/9: uTi=append(uTi,uTi[-1]+1./24./5.)
562/10: uTi=uTi+1./24./30.
562/11: uTi
562/12: swo.data['d90']
562/13: mask = swo.data["vges"]>0
562/14: mask
562/15: nrT,x = histogram(swo.data["d90"][mask],bins=uTi)
562/16: nrT
562/17: vsw,x = histogram(swo.data["d90"][mask],bins=uTi,weights=swo.data["vges"])
562/18: vsw
562/19: vsw = nsw/nrT
562/20: vsw = vsw/nrT
562/21: vsw[isnan(vsw)]=0.
562/22: vsw
562/23: index
562/24: u.data['vsw']
562/25: u.data['doy']
562/26: len(u.data['doy'])
562/27: len(swo.data['doy'])
562/28: v[index]
562/29: vsw
562/30: vsw[index]
562/31: len(vsw[index])
562/32: vsw
562/33: index
562/34: len(index)
562/35: d = [0,0,0,1,1,1,1,2,3]
562/36: a = [1,2,3,4]
562/37: a[d]
562/38: vsw
562/39: index
562/40: a = np.array(a)
562/41: import numpy as np
562/42: a = np.array(a)
562/43: d = np.array(d)
562/44: [a]
562/45: a
562/46: a[d]
562/47: d
562/48: u,index = unique(d,return_inverse=True)
562/49: u
562/50: u
562/51: d
562/52: i
562/53: index
562/54: i = np.array([0,1,0,1,0,1])
562/55: u
562/56: u[i]
562/57: a[i]
562/58: a
562/59: a
562/60: a[0,0,0]
562/61: b = np.array([0,0,0])
562/62: a[b]
562/63: a
562/64: b = np.array([0,0,0,5])
562/65: a[b]
562/66: a
562/67: a = np.array([10,20,30])
562/68: b = np.array([2,2,2,2,3])
562/69: a[b]
562/70: b = np.array([2,2,2,2,1])
562/71: a[b]
562/72: a = np.array([True,True,False])
562/73: b= np.array([1,2,3])
562/74: b[a]
562/75: b[(1,2)]
562/76: b[[1,2]]
562/77: a
562/78: a = np.array([1,2,3,1,2,3,44,55,1,1,3])
562/79: u,i = np.unique(a)
562/80: u,i = np.unique(a,return_inverse = True)
562/81: u
562/82: i
562/83: a
562/84: path="/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt"
562/85: fin = open(path,'r')
562/86:
for i in range(0,4):
    fin.readline()
562/87: a = fin.readline()
562/88: a
562/89: b = fin.readline()
562/90: b
562/91: path="/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt"
562/92: fin = open(path,'r')
562/93:
for i in range(4):
    fin.readline()
562/94: s = fin.readline()
562/95: k = s.split()
562/96: k
562/97: len(k)
562/98: keys = []
562/99:
for key in k:
    key = key.split()
    print(key[0])
562/100: %run uswo_traj.py
562/101: t = uswo_traj(year=[2000],tf=[[1,2]])
562/102: t
562/103: t.data
562/104: t.keys
563/1: %run uswo_traj.py
563/2: swo = uswo_traj(year=[2000],tf=[1,4])
563/3: swo.data
563/4: swo.year
563/5: swo.tf
563/6: swo.timeframe
563/7:
for tf in self.timeframe:
    print tf
563/8:
for tf in swo.timeframe:
    print tf
563/9: swo = uswo_traj(year=[2000],tf=[[1,4]])
563/10: swo.timeframe
563/11:
for tf in swo.timeframe:
    print tf
563/12:
for tf in swo.timeframe:
    
    
    
    f
563/13: path="/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt"
563/14: d = open(path,'r')
563/15:
for i in range(4):
    d.readline()
563/16: len(d)
563/17: d
563/18:
for line in d:
    l = line.split()
    print(l[0])
563/19:
for line in d:
    print line
563/20:
for line in d:
    l = line.split()
    print(l)
563/21: path="/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt"
563/22: d = open(path,'r')
563/23: d.readline(4)
563/24:
for i in range(4):
    d.readline()
563/25:
for i in range(3):
    d.readline
563/26: print(d.readline())
563/27: d.readline
563/28: d.readline()
563/29:
for i in range(3):
    d.readline()
563/30: print(d.readline())
563/31:
for line in d:
    l = line.split()
    print(l)
563/32:
for line in d:
    l = line.split()
    print(l[0])
563/33: d = open(path,'r')
563/34:
for i in range(6):
    d.readline()
563/35:
for line in d:
    l = line.split()
    print(l[0])
563/36: print(d.readline())
563/37: d.readline()
563/38: d =
563/39: d = open(path,'r')
563/40:
for i in range(6):
    d.readline()
563/41: print(d.readline())
563/42: print(d.readline())
563/43:
for line in d:
    l = line.split()
    print(l[0])
563/44: d = open(path,'r')
563/45:
for i in range(6):
    d.readline()
564/1: %run uswo_traj.py
564/2: %run uswo_traj.py
564/3: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/4: %run uswo_traj.py
564/5: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/6: %run uswo_traj.py
564/7: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/8: %run uswo_traj.py
564/9: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/10: %run uswo_traj.py
564/11: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/12: print(d.readline())
564/13: print(fin.readline())
564/14: %run uswo_traj.py
564/15: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/16: %run uswo_traj.py
564/17: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/18: %run uswo_traj.py
564/19: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/20: a = [1,2,3]
564/21: len(a)
564/22: %run uswo_traj.py
564/23: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/24: %run uswo_traj.py
564/25: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/26: swo.data
564/27: len(swo.data)
564/28: %run uswo_traj.py
564/29: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/30: %run uswo_traj.py
564/31: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/32: %run uswo_traj.py
564/33: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/34: swo.data
564/35:
for d in swo.data:
    print(swo.data['d'])
564/36:
for d in swo.data:
    print d
564/37:
for d in swo.data:
    print(swo.data['%s'd])
564/38:
for d in swo.data:
    print(swo.data['%s',d])
564/39: %run uswo_traj.py
564/40: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/41:
for d in swo.data:
    print(swo.data['%s',d])
564/42:
for d in swo.data:
    print(swo.data['%s' % (d)])
564/43:
for d in swo.data:
    print(len(swo.data['%s' % (d)]))
564/44:
for d in swo.data:
        print(swo.data['%s' %(d)])
        print(len(swo.data['%s' % (d)]))
564/45:
for d in swo.data:
        print(d)
        print(len(swo.data['%s' % (d)]))
564/46: %run uswo_traj.py
564/47: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/48:
for d in swo.data:
      print(len(swo.data['%s' % (d)]))
564/49: swo.data
564/50:
for key in swo.data.keys():
    swo.data[key] = array(self.data[key])
564/51:
for key in swo.data.keys():
    swo.data[key] = array(swo.data[key])
564/52: swo.data
564/53: %run uswo_traj.py
564/54: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/55: %run uswo_traj.py
564/56: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/57: %run uswo_traj.py
564/58: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/59: swo.data['DOY']
564/60: swo.data['DOY2']
564/61: %run uswo_traj.py
564/62: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/63: swo.data['d90']
564/64: y = 2000-1990
564/65: d = y*365 + (y.astype(int)+2)/4
564/66: d = y*365 + (y+2)/4
564/67: d
564/68: %run uswo_traj.py
564/69: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/70: %run uswo_traj.py
564/71: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/72: swo.data['YYYY']
564/73: %run uswo_traj.py
564/74: %run uswo_traj.py
564/75: swo = uswo_traj(year=[2000],tf=[[1,4]])
564/76:
for key in swo.data.keys():
    swo.data[key] = array(swo.data[key])
564/77:
for d in swo.data:
        print(d)
        print(len(swo.data['%s' % (d)]))
564/78:
for d in swo.data:
        print(len(swo.data['%s' % (d)]))
564/79: %run uswipha.py
564/80: u = uswipha(year=[2000],tf=[[1,2]])
564/81: u.data['d90']
564/82:
if not u.data['d90']:
    print('n')
564/83:
if not 'd90' in u.data.keys():
    print('n')
566/1: t = uswo_traj(year=[2000],tf=[[1,50]])
566/2: %run uswo_traj
566/3: ls
567/1: %run uswo_traj.py
567/2: t = uswo_traj(year=[2000],tf=[[1,50]])
567/3: t.data
567/4: %run uswipha.py
567/5: u = uswipha(year=[2000],tf=[[1,2]])
567/6: t = uswo_traj(year=[2000],tf=[[1,2]])
567/7: u.data
567/8: u.calc_d90()
567/9: t.data
567/10: t.calc_d90()
567/11: t.data
567/12: %run uswipha.py
567/13: %run uswo.py
567/14: a = uswo(year=[2000],tf=[[1,2]])
567/15: a.calc_d90()
567/16: a_90 = a.get_data['d90']
567/17: a.data['d90']
567/18: a_90 = a.data['d90']
567/19: u_90 = u.data['d90']
567/20: t_90 = t.data['d90']
567/21: u_90
567/22: len(u_90)
567/23: len(a_90)
567/24: u_90
567/25: uTi, index = unique(u_90,return_inverse=True)
567/26: uTi
567/27: index
567/28: len(index)
567/29: test = np.array([1,2,3,1,2,3,1,2,3,1,2,3])
567/30: ta,tb=unique(test,return_inverse = True)
567/31: ta
567/32: tb
567/33: uTi, index = unique(u_90,return_inverse=True)
567/34: append(1,2)
567/35: uTi[-1]+1./24./5.
567/36: a_90
567/37: mask = a.data['vges']>0
567/38: mask
567/39: len(mask)
567/40: len(a_90)
567/41: uTi
567/42: len(uTi)
567/43: nrT,x = histogram(a_90,bins=uTi)
567/44: nrT
567/45: x
567/46: nrT
567/47: vsw,x = histogram(a_90,bins=uTi, weights=a.data['vges'])
567/48: vsw
567/49: x
567/50: a_90
567/51: u_90
567/52: unique(a_90)
567/53: unique(u_90)
567/54: vsw,x = histogram(a_90,bins=uTi, weights=a.data['vges'])
567/55: a.data['vges']
567/56: len(a.data['vges'])
567/57: vsw
567/58: u_90[:3]
567/59: a_90[:5]
567/60: uTi
567/61: index
567/62: nrT
567/63: a_v = a.data['vges'][0:5]
567/64: a_v
567/65: index
567/66: vsw
567/67: vsw=vsw/nrT
567/68: vsw[isnan(vsw)]=0.
567/69: vsw
567/70: vsw[index]
567/71: uTi,index = unique(u.data['d90'],return_inverse = True)
567/72: uTi = append(uTi,uTi[-1]+1./24./5.)
567/73: uTi = uTi +1./24./30.
567/74: uTi
567/75: nrT,x = histogram(a_90,bins=uTi)
567/76: vsw,x = histogram(a_90,bins=uTi, weights=a.data['vges'])
567/77: vsw = vsw/nrT
567/78: vsw[isnan(vsw)]=0.
567/79: vsw[index]
567/80: vsw
567/81: index
567/82: len(index)
567/83: index[:20]
567/84: vsw[index][:20]
567/85: index[:40]
567/86: index[:50]
567/87: index[:500]
567/88: unique(index)
567/89: len(unique(index))
567/90: len(vsw)
567/91: aa=np.array([1,2,3,4,5])
567/92: bb = np.array([0,0,0,1,1,1,1,2,2,2,2,2,2,3])
567/93: aa[bb]
567/94: bb = np.array([0,0,1,1,2,2,3,3,4,4])
567/95: aa[bb]
567/96: bb = np.array([0,0,1,1,2,2,3,3,4,4,5])
567/97: aa[bb]
569/1: %run uswo_traj.py
569/2: t = uswo_traj(year=[2000],tf=[[1,2]])
569/3: t.data
569/4: %run uswipha.py
569/5: %run uswipha.py
569/6: u = uswipha(year=[2000],tf=[[1,16]])
569/7: u.sync_swics()
569/8: u.sync_swoops()
569/9: u.sync_traj()
569/10: u.sync_traj()
569/11: u = uswipha(year=[2000],tf=[[1,16]])
569/12: u.sync_swoops()
569/13: u.sync_traj()
569/14: u.data
569/15: %run uswo_traj.py
569/16: u = uswipha(year=[2000],tf=[[1,16]])
569/17: u.sync_swoops()
569/18: u.sync_traj()
569/19: u.data
570/1: %run uswipha.py
570/2: %run uswo_traj.py
570/3: u = uswipha(year=[2000],tf=[[1,16]])
570/4: u.sync_traj()
570/5: u.data
570/6: u.quicklook
570/7: u.quicklook()
570/8: pylab.plot(u.data['d90'],u.data['aa'])
570/9: unique(u.data['aa'])
570/10: pylab.plot(u.data['d90'],u.data['aa'],marker="o")
570/11: unique(u.data['d90'])
570/12: pylab.close('all')
571/1: %run uswo_traj.py
571/2: %run uswo.py
571/3: u = uswipha(year=[2000],tf=[[1,16]])
571/4: %run uswipha.py
572/1: %run uswipha.py
572/2: u = uswipha(year=[2000],tf=[[1,16]])
572/3: u.sync_swoops()
572/4: u.sync_traj()
572/5: pylab.plot(u.data['d90'],u.data['aa'],marker="o")
572/6: pylab.close('all')
572/7: plot(u.data['d90'],u.data['aa'],marker="o")
572/8: pylab.close('all')
572/9: unique(u.data['d90'])
572/10: a = unique(u.data['d90'])
572/11: a
572/12: for i in a=
572/13:
for i in a:
    print i
572/14: print(min(a))
572/15: print(max(a))
572/16: print(numpy.min(a))
572/17: plot(u.data['d90'],u.data['aa'],marker="o")
572/18: plot(u.data['d90'],u.data['aa'],marker="o",linestyle='none')
572/19: pylab.close('all')
572/20: unique(u.data['aa'])
574/1: t = uswo_traj(year=[2000],tf=[[1,2]])
574/2: %run uswo_traj.py
574/3: t = uswo_traj(year=[2000],tf=[[1,2]])
574/4: t.data
574/5: unique(t.data['SPE'])
575/1: %run uswipha.py
575/2: u = uswipha(year=[2000],tf=[[1,2]])
575/3: u.sync_traj()
575/4: unique(u.data['aa'])
576/1: %run uswipha.py
576/2: u = uswipha(year=[1990],tf=[[280,281]])
576/3: u = uswipha(year=[1991],tf=[[1,2]])
576/4: u.data
576/5: u.sync_traj()
576/6: u.data
576/7: t = uswo_traj(year=[1991],tf=[[1,2]])
576/8: t.data
576/9: unique(t.data['SPE'])
576/10: t = uswo_traj(year=[1991],tf=[[1,2]])
576/11: t.tf
576/12: t.timeframe
576/13:
for tf in t.timeframe:
    print(tf)
576/14: tf = self.timeframe[0]
576/15: tf = t.timeframe[0]
576/16: tf
576/17: range(int(tf[0]),int(tf[1]))
576/18: t = uswo_traj(year=[1991],tf=[[1,20]])
576/19: tf = t.timeframe[0]
576/20: range(int(tf[0]),int(tf[1]))
577/1: %run uswo_traj.py
577/2: %run uswo_traj.py
577/3: t = uswo_traj(year=[1991],tf=[[1,20]])
578/1: %run uswo_traj.py
578/2: t = uswo_traj(year=[1991],tf=[[1,20]])
578/3: %run uswo_traj.py
578/4: t = uswo_traj(year=[1991],tf=[[1,20]])
578/5: %run uswo_traj.py
578/6: t = uswo_traj(year=[1991],tf=[[1,20]])
578/7: %run uswo_traj.py
578/8: t = uswo_traj(year=[1991],tf=[[1,20]])
578/9: %run uswo_traj.py
578/10: t = uswo_traj(year=[1991],tf=[[1,20]])
578/11: %run uswo_traj.py
578/12: t = uswo_traj(year=[1991],tf=[[1,20]])
578/13: %run uswo_traj.py
578/14: t = uswo_traj(year=[1991],tf=[[1,20]])
578/15: %run uswo_traj.py
578/16: t = uswo_traj(year=[1991],tf=[[1,20]])
578/17: %run uswo_traj.py
578/18: t = uswo_traj(year=[1991],tf=[[1,20]])
578/19: %run uswo_traj.py
578/20: t = uswo_traj(year=[1991],tf=[[1,20]])
578/21: %run uswo_traj.py
578/22: t = uswo_traj(year=[1991],tf=[[1,20],[200,220]])
578/23: t = uswo_traj(year=[1991,1992],tf=[[1,2]])
578/24: t.data['SPE']
579/1: %run uswipha.py
579/2: u = uswipha(year=[1991],tf=[[1,2]])
579/3: u.sync_tr
579/4: u.sync_traj()
579/5: u.data['aa']
579/6: unique(u.data['aa'])
579/7: %run uswipha.py
579/8: u = uswipha(year=[1991],tf=[[1,2]])
579/9: u.sync_traj()
579/10: %run uswipha.py
579/11: u = uswipha(year=[1991],tf=[[1,2]])
579/12: u.sync_traj()
580/1: %run uswipha.py
580/2: u = uswipha(year=[1991],tf=[[1,2]])
580/3: %run uswipha.py
580/4: u = uswipha(year=[1991],tf=[[1,2]])
580/5: u.sync_traj()
581/1: %run uswipha.py
581/2: u = uswipha(year=[1991],tf=[[1,2]])
581/3: u.sync_traj()
581/4: unique
581/5: unique(u.data['aa'])
582/1: %run uswipha.py
582/2: u = uswipha(year=[1991],tf=[[1,2]])
582/3: u.sync_traj()
583/1: %run uswipha.py
583/2: u = uswipha(year=[1991],tf=[[1,2]])
583/3: u.sync_traj()
583/4: %run uswipha.py
583/5: u = uswipha(year=[1991],tf=[[1,2]])
583/6: u.sync_traj()
583/7: %run uswipha.py
583/8: u = uswipha(year=[1991],tf=[[1,2]])
583/9: u.sync_traj()
583/10: %run uswipha.py
583/11: u = uswipha(year=[1991],tf=[[1,2]])
583/12: u.sync_traj()
584/1: %run uswo_traj.py
584/2: t = uswo_traj(year=[1991,1992],tf=[[1,2]])
584/3: %run uswo.py
584/4: swo = uswo(year=[1991,1992],tf=[[1,2]])
584/5: %run uswipha.py
584/6: u = uswipha(year=[1991,1992],tf=[[1,2]])
584/7: swo.calc_doy()
584/8: swo.calc_d90()
584/9: u.calc_d90()
584/10: t.calc_d90()
584/11: u.data['d90']
584/12: swo.data['d90']
584/13: t.data['d90']
584/14: len(swo.data['d90'])
584/15: len(u.data['d90'])
584/16: uTi,index=unique(u.data["d90"],return_inverse=True)
584/17: u1 = uTi
584/18: u2=append(uTi,uTi[-1]+1./24./5.)
584/19: u3=u2+1./24./30.
584/20: u1
584/21: len(u1)
584/22: len(u2)
584/23: len(u3)
584/24: u1[-5:]
584/25: u2[-5:]
584/26: u3[-5:]
584/27: u1[-3:]
584/28: u2[-4:]
584/29: u3[-5:]
584/30: u3[0]
584/31: u2[0]
584/32: 1./24./5.
584/33: t
584/34: t.data['d90']
584/35: u
584/36: u1
584/37: u1[0]
584/38: u2[0]
584/39: u3[0]
584/40: swo.data['d90']
584/41: diff(swo.data['d90'])
584/42: swo.data['d90']
584/43: diff(swo.data['d90'])
584/44: diff(swo.data['d90'])*24.*60.
584/45: 1./24./60.
584/46: diff(swo.data['d90'])*24.*60.
584/47: diff(swo.data['d90'])
584/48: 1./24./60.
584/49: diff(swo.data['d90'])*24.*60.
584/50: unique(diff(swo.data['d90'])*24.*60.)
584/51: u.data['d90']
584/52: diff(u.data['d90'])
584/53: diff(unique(u.data['d90']))
584/54: diff(unique(u.data['d90']))*24*60
584/55: diff(unique(swo.data['d90']))*24*60
584/56: unique(u.data['d90'])
584/57: diff(unique(u.data['d90']))
584/58: diff(unique(u.data['d90']))*24*60
584/59: diff(unique(u.data['d90']))
584/60: unique(u.data['d90'])
584/61: unique(u.data['d90'])[-4:]
584/62: unique(swo.data['d90'])[-4:]
584/63: diff(732.9928889,733.99319444)
584/64: diff([732.9928889,733.99319444])
584/65: swo.data['d90']
584/66: t.data['d90']
584/67: unique(u.data['d90'])
585/1: %run uswipha.py
585/2: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/3: u.sync_traj()
585/4: %run uswipha.py
585/5: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/6: u.sync_traj()
585/7: %run uswipha.py
585/8: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/9: u.sync_traj()
585/10: u.data['aa']
585/11: unique(u.data['aa'])
585/12: %run uswipha.py
585/13: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/14: u.sync_traj()
585/15: %run uswipha.py
585/16: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/17: u.sync_traj()
585/18: aa[index]
585/19: %run uswipha.py
585/20: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/21: u.sync_traj()
585/22: %run uswipha.py
585/23: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/24: i = u.sync_traj()
585/25: i
585/26:
for ii in i:
    print(ii)
585/27: i.reshape(25,4).tolist()
585/28: 39200/20
585/29: u = uswipha(year=[1991],tf=[[1,2]])
585/30: u.sync_traj()
585/31: %run uswipha.py
585/32: u = uswipha(year=[1991],tf=[[1,2]])
585/33: u.sync_traj()
585/34: %run uswipha.py
585/35: u = uswipha(year=[1991],tf=[[1,2]])
585/36: u.sync_traj()
585/37: %run uswipha.py
585/38: u = uswipha(year=[1991],tf=[[1,2]])
585/39: u.sync_traj()
585/40: %run uswipha.py
585/41: u = uswipha(year=[1991],tf=[[1,2]])
585/42: u.sync_traj()
585/43: %run uswipha.py
585/44: u = uswipha(year=[1991],tf=[[1,2]])
585/45: u.sync_traj()
585/46: %run uswipha.py
585/47: u = uswipha(year=[1991],tf=[[1,2]])
585/48: index = u.sync_traj()
585/49: idex
585/50: index
585/51: len(index)
585/52: %run uswipha.py
585/53: u = uswipha(year=[1991],tf=[[1,2]])
585/54: traj = uswo_traj(year=u.year,tf=u.timeframe)
585/55: u.calc_d90()
585/56: traj.calc_d90()
585/57: uTi, index = unique(u.data["d90"], return_inverse=True)
585/58: aa, x = histogram(traj.data["d90"][mask], bins=uTi, weights=traj.data["SPE"])
585/59:
unique(int(u.data['d90'])

)+
585/60:
unique(int(u.data['d90'])

)
585/61: unique(int(u.data['d90']))
585/62: u.data['d90']
585/63: u.data['d90'].astype(int)
585/64: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/65: u.calc_d90()
585/66: traj = uswo_traj(year=u.year,tf=u.timeframe)
585/67: traj.calc_d90()
585/68: traj.data['d90']
585/69: u.data['d90']
585/70: unique(u.data['d90'])
585/71: u = unique(u.data['d90'])[:75]
585/72: u
585/73: i = u.astype(int)
585/74: i
585/75: uTi,index = unique(i,return_inverse=True)
585/76: index
585/77: uTi
585/78: traj.data['d90']
585/79: nrt,x = histogram(traj.data['d90'],bins=uTi)
585/80: nrt
585/81: uTi=uTi+733
585/82: uTi
585/83: uTi,index = unique(i,return_inverse=True)
585/84: uTi = append(uTi,733)
585/85: uTi
585/86: nrt,x = histogram(traj.data['d90'],bins=uTi)
585/87: nrt
585/88: x
585/89: nrt,x = histogram(traj.data['d90'],bins=uTi,weights=traj.data['SPE'])
585/90: nrt
585/91: nrt[index]
585/92: index
585/93: len(index)
585/94: len(uTi)
585/95: %run uswipha.py
585/96: u = uswipha(year=[1991,1992],tf=[[1,2]])
585/97: aa = u.sync_traj()
585/98: aa
585/99: aa[index]
586/1: %run uswipha.py
586/2: u = uswipha(year=[1991,1992],tf=[[1,2]])
586/3: aa = u.sync_traj()
586/4: u.data['d90']
586/5: len(u.data['d90'])
586/6: len(unique(u.data['d90']))
586/7: uTi_int, index_int = unique(u.data['d90'].astype(int),return_inverse=True)
586/8: uTi_int
586/9: index_int
586/10: len(index_int)
586/11: uTi_int = append(uTi_int,uTi_int[-1]+1)
586/12: uTi_int
586/13: aa, x = histogram(traj.data["d90"][mask], bins=uTi_int, weights=traj.data["SPE"])
587/1: %run uswipha.py
587/2: traj = uswo_traj(year=u.year,tf=u.timeframe)
587/3: u = uswipha(year=[1991,1992],tf=[[1,2]])
587/4: u.sync_traj()
587/5: aa = u.sync_traj()
588/1: %run uswipha.py
588/2: u =
588/3: u = uswipha(year=[1991,1992],tf=[[1,2]])
588/4: u.calc_d90()
588/5: traj = uswo_traj(year=u.year,tf=u.timeframe)
588/6: traj.calc_d90()
588/7: uTi_int, index_int = unique(u.data['d90'].astype(int),return_inverse=True)
588/8: uTi_int = append(uTi_int,uTi_int[-1]+1)
588/9: uTi_int
588/10: mask = traj.data['SPE']>0.
588/11: aa, x = histogram(traj.data["d90"][mask], bins=uTi_int, weights=traj.data["SPE"])
588/12: aa
588/13: index_int
588/14: aa[index_int]
588/15: len(aa[index_int])
588/16: len(u.data['d90'])
588/17:
for i in len(aa[index_int]):
    print(aa[index_int][i],u.data['d90'][i])
588/18: aa[index_int][0]
588/19: aa[index_int]
588/20:
for i in range(len(aa[index_int])):
    print(aa[index_int][i],u.data['d90'][i])
588/21:
for i,n in enumerate( range(0,len(aa[index_int]),3)):
    print(aa[index_int][i],u.data['d90'][i],n)
588/22:
for i in range(1,len(aa[index_int]),3):
    print(aa[index_int][i],u.data['d90'][i])
588/23:
for i in range(200,len(aa[index_int])-200,3):
    print(aa[index_int][i],u.data['d90'][i])
588/24:
for i in range(2000,len(aa[index_int])-2000,3):
    print(aa[index_int][i],u.data['d90'][i])
588/25:
for i in range(len(aa[index_int])-2):
    if i.data['d90'] != u.data['d90'][i+1]:
        for ii in range(i-2,i+3,1):
            print(aa[index_int][ii],u.data['d90'][ii])
588/26:
for i in range(len(aa[index_int])-2):
    if u.data['d90'] != u.data['d90'][i+1]:
        for ii in range(i-2,i+3,1):
            print(aa[index_int][ii],u.data['d90'][ii])
588/27:
for i in range(len(aa[index_int])-2):
    if u.data['d90'][i] != u.data['d90'][i+1]:
        for ii in range(i-2,i+3,1):
            print(aa[index_int][ii],u.data['d90'][ii])
588/28: %run uswipha.py
588/29: u = uswipha(year=[1991,1992],tf=[[1,2]])
588/30: u.sync_traj()
588/31: u.data['d90']
588/32: u.data['aa']
588/33: len(u.data['aa'])
588/34: len(u.data['d90'])
588/35: %run uswipha.py
588/36: u = uswipha(year=[1991,1992],tf=[[1,200]])
588/37: u.sync_traj()
588/38:
for i in range(len(u.data['d90'])-1):
    if u.data['d90'][i] != u.data['d90'][i+1]:
        for ii in range(i-1,i+2):
            print(u.data['d90'][ii],u.data['aa'][ii])
588/39:
for i in range(len(u.data['d90'])-1):
    if u.data['aa'][i] != u.data['aa'][i+1]:
        for ii in range(i-1,i+2):
            print(u.data['d90'][ii],u.data['aa'][ii])
588/40:
for i in range(len(u.data['d90'])-1000):
    if u.data['aa'][i] != u.data['aa'][i+1]:
        for ii in range(i-1,i+2):
            print(u.data['d90'][ii],u.data['aa'][ii])
        print('\n')
588/41: plot(u.data['d90'],u.data['aa'])
588/42: plot(u.data['aa'])
588/43: pylab.close('all')
588/44: plot(u.data['aa'])
589/1: %run pui_ulysses.py
589/2: %run pui_ulysses.py
589/3: u = uswipha(year=[2000,2001],tf=['all'])
589/4: u = uswipha(year=[2000,2001],tf='all']
589/5: u = uswipha(year=[2000,2001],tf='all')
589/6: trajectory(u)
589/7: u.calc_d90
589/8: u.calc_d90()
589/9: u.sync_traj()
589/10: trajectory(u)
589/11: u.get_data('aa')
589/12: u.get_data([],'aa')
590/1: %run pui_ulysses.py
590/2: %run pui_ulysses.py
590/3: u = uswipha(year=[2000,2001],tf=[[1,10]])
590/4: u.sync_traj()
590/5: trajectory(u)
590/6: u = uswipha(year=[2000],tf=[[1,100]])
590/7: trajectory(u)
590/8: u.sync_traj()
590/9: %run pui_ulysses.py
591/1: %run pui_ulysses.py
591/2: u = uswipha(year=[2000],tf=[[1,100]])
591/3: trajectory(u)
591/4: u.sync_traj()
591/5: trajectory(u)
591/6: 10*365
591/7: %run pui_ulysses.py
591/8: u.sync_traj()
591/9: trajectory(u)
591/10: u.get_data([],'d90')
591/11: 2009-1990
591/12: 19*365
591/13: %run pui_ulysses.py
591/14: trajectory(u)
591/15: %run pui_ulysses.py
591/16: trajectory(u)
591/17: pylab.close('all')
591/18: %run pui_ulysses.py
591/19: trajectory(u)
591/20: %run pui_ulysses.py
591/21: trajectory(u)
591/22: %run pui_ulysses.py
591/23: trajectory(u)
591/24: %run pui_ulysses.py
591/25: trajectory(u)
591/26: np.arange(0,6935,365)
591/27: np.arange(0,6936,365)
591/28: %run pui_ulysses.py
591/29: trajectory(u)
591/30: %run pui_ulysses.py
591/31: u = uswipha(year=[2000],tf=[[1,300]])
591/32: u.sync_traj()
591/33: trajectory(u)
591/34: %run pui_ulysses.py
591/35: trajectory(u)
591/36: pylab.close('all')
591/37: 20*365
591/38: %run pui_ulysses.py
591/39: trajectory(u)
591/40: %run pui_ulysses.py
591/41: trajectory(u)
592/1: %run pui_ulysses.py
592/2: u = uswipha(year=range(1992,2005),tf=[[1,300]])
593/1: u = uswipha(year=range(1992,1995),tf='all')
593/2: %run pui_ulysses.py
593/3: u = uswipha(year=range(1992,1995),tf='all')
593/4: trajectory(u)
593/5: u.sync_traj()
593/6: trajectory(u)
593/7: %run pui_ulysses.py
593/8: u.sync_traj()
593/9: %run pui_ulysses.py
593/10: u = uswipha(year=range(1990,1995),tf='all')
593/11: u.sync_traj()
593/12: d90=u.data['d90']
593/13: plot(d90,r)
593/14: plot(d90,u.data['r'])
593/15: u.data['r']
593/16: u.data
594/1: u = uswipha(year=range(1991,1994),tf='all')
594/2: %run pui_ulysses.py
594/3: u = uswipha(year=range(1991,1994),tf='all')
594/4: u.sync_traj()
596/1: %run uswipha.py
596/2: u = uswipha(year=range(1993),tf=[[1,20]])
596/3: u.sync_traj()
596/4: %run uswipha.py
596/5: u = uswipha(year=range(1993),tf=[[1,20]])
596/6: u = uswipha(year=[1993],tf=[[1,20]])
596/7: u.sync_traj()
596/8: u.data
596/9: %run uswipha.py
596/10: u = uswipha(year=[1993],tf=[[1,20]])
596/11: u.sync_traj()
596/12: %run uswipha.py
596/13: u = uswipha(year=[1993],tf=[[1,20]])
596/14: u.sync_traj()
596/15: u.data
596/16: traj.data
596/17: traj = uswo_traj(year=u.year,tf=u.timeframe)
596/18: traj.data
596/19: traj.data['lat']
596/20: %run uswipha.py
596/21: %run uswipha.py
596/22: u = uswipha(year=[1993],tf=[[1,20]])
596/23: u.sync_traj()
596/24: u.data
596/25: %run uswipha.py
596/26: u.sync_traj()
597/1: %run uswipha.py
597/2: u.sync_traj()
597/3: u = uswipha(year=[1993],tf=[[1,20]])
597/4: u.sync_traj()
598/1: u = uswipha(year=[1993],tf=[[1,20]])
598/2: u = uswipha(year=[1993],tf=[[1,20]])
598/3: %run uswipha.py
598/4: u = uswipha(year=[1993],tf=[[1,20]])
598/5: u.sync_traj()
598/6: u.data
599/1: %run pui_ulysses.py
599/2: u = uswipha(year=[1993],tf=[[1,20]])
599/3: u.sync_traj()
599/4: test(u)
600/1: %run pui_ulysses.py
600/2: u = uswipha(year=[1993],tf=[[1,20]])
600/3: u.sync_traj()
600/4: test(u)
600/5: %run pui_ulysses.py
600/6: u.sync_traj()
600/7: n
600/8: %run pui_ulysses.py
601/1: %run pui_ulysses.py
601/2: u = uswipha(year=[1993],tf=[[1,20]])
601/3: u.sync_traj()
601/4: test(u)
601/5: %run pui_ulysses.py
601/6: u = uswipha(year=[1993],tf=[[1,20]])
601/7: u.sync_traj()
601/8: test(u)
602/1: %run pui_ulysses.py
602/2: u = uswipha(year=range(1991,1997),tf='all')
602/3: u.sync_traj()
602/4: test(u)
602/5: u = uswipha(year=range(1991,1993),tf='all')
602/6: u.sync_traj()
602/7: test(u)
602/8: %run pui_ulysses.py
603/1: %run pui_ulysses.py
603/2: u = uswipha(year=range(1991,1993),tf='all')
603/3: u.sync_traj()
603/4: test(u)
603/5: pylab.close('all')
603/6: %run pui_ulysses.py
604/1: %run pui_ulysses.py
604/2: u = uswipha(year=range(1991,1994),tf='all')
604/3: u.sync_traj()
604/4: test(u)
604/5: %run pui_ulysses.py
604/6: pylab.close('all')
604/7: %run pui_ulysses.py
604/8: test(u)
604/9: %run pui_ulysses.py
604/10: %run pui_ulysses.py
605/1: %run pui_ulysses.py
605/2: range(1,4)
605/3: u = uswipha(year=range(1991,1993),tf='all')
605/4: u.sync_traj()
605/5: test(u)
605/6: %run pui_ulysses.py
605/7: test(u)
606/1: %run pui_ulysses.py
606/2: u = uswipha(year=range(1990,1996),tf='all')
606/3: u.sync_traj()
606/4: %run pui_ulysses.py
606/5: test(u)
606/6: pylab.close('all')
606/7: %run pui_ulysses.py
606/8: test(u)
606/9: np.min(u.data['lat'])
606/10: np.max(u.data['lat'])
606/11: ulong = np.sort(u.data['lat'])
606/12: ulong
606/13: ulong[0:20]
606/14: ulong[0:50]
606/15: ulong[0:100]
606/16: ulong[0:500]
606/17: len(ulong)
606/18: unique(ulong)
606/19: u.data['lat']
606/20: u.data['long']
606/21: unique(u.data['long'])
606/22: np.min(u.data['long'])
606/23: np.max(u.data['long'])
606/24: %run pui_ulysses.py
606/25: %run pui_ulysses.py
606/26: test(u)
606/27: #
607/1: a=[1,2,3,4,5,6]
607/2: import numpy as np
607/3: a=np.array(a)
607/4: a
607/5: a[1,2,3]
607/6: a[1:-1]
607/7: a[::2]
607/8: a[::3]
607/9: %run pui_ulysses.py
607/10: u = uswipha(year=range(1990,1992),tf='all')
607/11: test(u)
607/12: u.sync_traj()
607/13: test(u)
607/14: u = uswipha(year=range(1990,1996),tf='all')
608/1: u = uswipha(year=range(1990,1996),tf='all')
608/2: %run pui_ulysses.py
608/3: u = uswipha(year=range(1990,1996),tf='all')
608/4: u.sync_traj()
608/5: test(u)
608/6: %run pui_ulysses.py
608/7: pylab.close('all')
608/8: test(u)
608/9: pylab.close('all')
608/10: %run pui_ulysses.py
608/11: test(u)
608/12: pylab.close('all')
608/13: u = uswipha(year=range(1990,1998),tf='all')
608/14: u
608/15: u.data
608/16: u = uswipha(year=range(1995,1998),tf='all')
610/1: u = uswipha(year=range(1995,1998),tf='all')
610/2: %run pui_ulysses.py
610/3: u = uswipha(year=range(1995,1998),tf='all')
611/1: u = uswipha(year=range(1990,1998),tf='all')
611/2: %run pui_ulysses.py
611/3: u = uswipha(year=range(1990,1998),tf='all')
611/4: %run pui_ulysses.py
611/5: u.sync_traj()
611/6: %run pui_ulysses.py
611/7: test(u)
611/8: u.data['r']
611/9: np.max(u.data['r'])
611/10: unique(u.data['r'])
611/11: a = uswipha(year=range(1990,1992),tf='all')
611/12: a.sync_traj()
611/13: pylab.close('all')
611/14: test(a)
611/15: pylab.close('all')
611/16: %run pui_ulysses.py
611/17: test(a)
611/18: %run pui_ulysses.py
611/19: test(a)
611/20: %run pui_ulysses.py
611/21: test(a)
611/22: %run pui_ulysses.py
611/23: test(a)
611/24: pylab.close('all')
611/25: %run pui_ulysses.py
611/26: test(a)
611/27: pylab.close('all')
611/28: %run pui_ulysses.py
611/29: test(a)
611/30: pylab.close('all')
611/31: %run pui_ulysses.py
611/32: test(a)
611/33: pylab.close('all')
611/34: %run pui_ulysses.py
611/35: test(a)
611/36: pylab.close('all')
611/37: %run pui_ulysses.py
611/38: test(a)
611/39: pylab.close('all')
611/40: %run pui_ulysses.py
611/41: test(a)
611/42: %run pui_ulysses.py
611/43: pylab.close('all')
611/44: test(a)
611/45: %run pui_ulysses.py
611/46: pylab.close('all')
611/47: test(a)
611/48: pylab.close('all')
611/49: pylab.close('all')
611/50: %run pui_ulysses.py
611/51: test(a)
611/52: %run pui_ulysses.py
611/53: pylab.close('all')
611/54: test(a)
611/55: %run pui_ulysses.py
611/56: pylab.close('all')
611/57: test(a)
611/58: %run pui_ulysses.py
611/59: pylab.close('all')
611/60: test(a)
611/61: %run pui_ulysses.py
611/62: pylab.close('all')
611/63: test(a)
611/64: %run pui_ulysses.py
611/65: pylab.close('all')
611/66: test(u)
611/67: %run pui_ulysses.py
611/68: pylab.close('all')
611/69: test(u)
611/70: pylab.close('all')
611/71: %run pui_ulysses.py
611/72: test(u)
612/1: u = uswipha(year=range(1990,1998),tf='all')
612/2: %run pui_ulysses.py
612/3: u = uswipha(year=range(1990,1998),tf='all')
612/4: %run pui_ulysses.py
612/5: test(u)
612/6: u.sync_traj()
612/7: test(u)
612/8: %run pui_ulysses.py
612/9: pylab.close('all')
612/10: test(u)
612/11: pylab.close('all')
612/12: %run pui_ulysses.py
612/13: test(u)
612/14: %run pui_ulysses.py
612/15: pylab.close('all')
612/16: test(u)
613/1: %run pui_ulysses.py
613/2: u = uswipha(year=range(1990,1998),tf='all')
613/3: u.sync_traj()
613/4: test(u)
614/1: ls
614/2: %run uswipha
614/3: from uswipha import uswipha
614/4: d = uswipha(year=1993,tf='all')
614/5: d
614/6: d.norm
614/7: d.data
614/8: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
614/9: unique(d.data['epq'])
614/10: unique(d.data['ech'])
614/11: unique(d.data['rng'])
614/12: cd ../diy/
614/13: %run pui_ulysses.py
615/1: from uswipha import uswipha
615/2: d = uswipha(year=1993,tf='all')
615/3: d.data
615/4: len(d.data['brw'])
615/5: l = len(d.data['brw'])
615/6: l/365.
615/7: l/365./24./60.
615/8: 19.5*13
615/9: unique(d.data['brw'])
615/10: unique(d.data['rng'])
615/11: d.add_mask('Master','rng',0,0)
615/12: d.set_mask('Master','rng',0,0)
615/13: d.hist1d('ech')
615/14: d.reset_mask()
615/15: d.reset_mask('Master')
615/16: d.show_mask()
615/17: d.add_mask('0')
615/18: d.add_mask('1')
615/19: d.add_mask('2')
615/20: d.set_mask('0','rng',0,0)
615/21: d.set_mask('1','rng',1,1)
615/22: d.set_mask('2','rng',2,2)
615/23: d.hist1d('ech')
615/24: d.hist1d('ech',smask='0','1')
615/25: d.hist1d('ech',smask=['0','1'])
615/26: d.hist1d('ech',smask=['0','2'])
615/27: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=["Master","0","1"])
615/28: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=["Master","0","1",'2'])
615/29: pylab.close('all')
615/30: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=["Master","0","1",'2'])
615/31: pylab.close('all')
615/32: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=["Master","0","1","2"])
615/33: d.show_mask()
615/34: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=["Master","0","2"])
615/35: pylab.close('all')
615/36: d.add_mask('w')
615/37: d.sync_swoops()
615/38: d.set_mask('w','wHe+',1.1,10)
615/39: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
615/40: d.add_mask('He+')
615/41: pylab.close('all')
615/42: d.set_mask2D('He+','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
615/43: d.set_mask('He2+','wHe+',1.1,10)
615/44: d.show_mask()
615/45: d.set_mask('He+','wHe+',1.1,10)
615/46: d.remove_mask('1','2','0')
615/47: d.remove_mask('1')
615/48: d.remove_mask('2')
615/49: d.remove_mask('0')
615/50: d.show_mask()
615/51: d.remove_mask('w')
615/52: pylab.close('all')
615/53: d.hist1d('rng',smask=['He+'])
615/54: d.data['weights']
616/1: from uswipha import uswipha
616/2: d = uswipha(year=1993,tf='all')
616/3: d.data
616/4: a = d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200))
616/5: a
616/6: len(a)
616/7: a.get_data()
616/8: b = a.get_data()
616/9: b[0]
616/10: b.get_data()
616/11: Hist, x, y = b.get_data()
616/12: size(b.get_data())
616/13: type(b.get_data())
616/14: p = d.hist2d('tch','ech',binx=arange(200,1024),biny = arange(0,1024))
616/15: p.get_data().get_data()
617/1: d = uswipha(year=1993,tf='all')
617/2: from uswipha import uswipha
617/3: d = uswipha(year=1993,tf='all')
617/4: p = d.hist2d('tch','ech',binx=arange(200,1024),biny = arange(0,1024))
617/5: a = p.get_data().get_data()
617/6: a
617/7: a['Master']
617/8: a['Master'][0]
617/9: H,xbins,ybins = [a['Master'][n] for n in [0,1,2]]
617/10: H
617/11: ls
617/12: cd ..
617/13: ls
617/14: cd diy
617/15: ls
618/1: ls
618/2: cd EQ_positions_gui/
618/3: ls
618/4: %run ulysses_clicking.py
619/1: %run ulysses_clicking.py
619/2: cd
619/3: cd ulysses/swics/software/EQ_positions_gui/
619/4: %run ulysses_clicking.py
619/5: %run ulysses_clicking.py
619/6: %run ulysses_clicking.py
619/7: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
619/8: unique(d.data['tch'])
619/9: unique(d.data['ech'])
619/10: %run ulysses_clicking.py
619/11: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(100,500,2),biny=arange(1,200,2),binz=arange(10,60))
619/12: pylab.close('all')
619/13: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
619/14: H_params
619/15: H_params.save_ascii()
619/16: p.get_data()
619/17: p.get_data().save_ascii()
619/18: %run ulysses_clicking.py
619/19: %run ulysses_clicking.py
619/20: %run ulysses_clicking.py
619/21: %run ulysses_clicking.py
620/1: %run ulysses_clicking.py
620/2: %run ulysses_clicking.py
620/3: %run ulysses_clicking.py
620/4: %run ulysses_clicking.py
620/5: %run ulysses_clicking.py
620/6: %run ulysses_clicking.py
620/7: %run ulysses_clicking.py
620/8: %run ulysses_clicking.py
620/9: %run ulysses_clicking.py
620/10: %run ulysses_clicking.py
620/11: type(Hist)
620/12:
for line in Hist:
    print(line[0])
620/13: %run ulysses_clicking.py
620/14: %run ulysses_clicking.py
620/15: %run ulysses_clicking.py
620/16: pcolormesh(Hist)
620/17: pylab.show()
620/18: pcolormesh(Hist)
620/19: pcolormesh(xbins,ybins,Hist)
620/20: %run ulysses_clicking.py
620/21: pcolormesh(xbins,ybins,Hist)
620/22: pcolormesh(xbins[:-1],ybins[:-1],Hist)
620/23: help(pcolormesh)
620/24: %run ulysses_clicking.py
620/25: %run ulysses_clicking.py
620/26: pcolormesh(xbins,ybins,Hist)
620/27: h = Hist.T()
620/28: Hist
620/29: Hist.t()
620/30: Hist.T
620/31: h = Hist.t
620/32: h = Hist.T
620/33: pcolormesh(xbins,ybins,h)
620/34: a = pcolormesh(xbins,ybins,h)
620/35: pylab.show()
620/36: a = pcolormesh(xbins,ybins,h)
621/1: from uswipha import uswipha
621/2: %run ulysses_clicking.py
621/3: %run ulysses_clicking.py
623/1: %run read_in_clicking_test.py
623/2: %run ulysses_clicking.py
623/3: %run read_in_clicking_test.py
623/4: %run read_in_clicking_test.py
623/5: %run read_in_clicking_test.py
623/6: ls
623/7: cd ..
623/8: cd ..
623/9: %run read_in_clicking_test.py
623/10: cd ..
623/11: %run read_in_clicking_test.py
623/12: path
623/13: a = loadtxt(path)
623/14: a = loadtxt(path)[:]
623/15: %run ulysses_clicking.py
623/16: %run ulysses_clicking.py
623/17: Hist
623/18: Hist[:-1]
623/19: size(Hist)
623/20: shape(Hist)
623/21: %run ulysses_clicking.py
623/22: Hist[0:100]
624/1: %run ulysses_clicking.py
624/2: %run ulysses_clicking.py
624/3: %run ulysses_clicking.py
624/4: Hist
624/5: shape(Hist)
624/6: %run ulysses_clicking.py
624/7: shape(Hist)
624/8: shape(Hist2)
625/1: %run ulysses_clicking.py
625/2: %run ulysses_clicking.py
625/3: %run ulysses_clicking.py
626/1: %run ulysses_clicking.py
626/2: %run ulysses_clicking.py
627/1: %run ulysses_clicking.py
627/2: loadtxt(fid)
627/3: ls
627/4: path = 'histograms/%i/all_sec/counts%i_all_step%i.dat'%(y,y,epq)
627/5: path
627/6: loadtxt(path)
627/7: a = loadtxt(path)
627/8: shape(a)
628/1: %run ulysses_clicking.py
628/2: a = loadtxt(path)
628/3: path = 'histograms/%i/all_sec/counts%i_all_step%i.dat'%(y,y,epq)
628/4: a = loadtxt(path)
628/5: shape(a)
628/6: %run ulysses_clicking.py
628/7: %run read_in_clicking_test.py
628/8: epq
628/9: fid
628/10: shape(fid)
628/11: loadtxt(path)
628/12: shape(loadtxt(path))
628/13: arange(0,1024)
628/14: shape(arange(0,1024))
628/15: %run read_in_clicking_test.py
628/16: %run read_in_clicking_test.py
628/17: %run read_in_clicking_test.py
628/18: Hist
628/19: %run read_in_clicking_test.py
629/1: %run read_in_clicking_test.py
629/2: pylab.show()
630/1: %run read_in_clicking_test.py
630/2: pylab.show()
630/3: max(Hist)
630/4: numpy.max(Hist)
630/5: Mesh = ax.pcolormesh(binx,biny,Hist.T,cmap=colormap,vmin=min(C[C>0]),vmax=max(C),zorder=0)
630/6: Mesh = ax.pcolormesh(binx,biny,Hist.T,cmap=colormap,vmin=min(Hist[Hist>0]),vmax=max(Hist),zorder=0)
630/7: Mesh = ax.pcolormesh(binx,biny,Hist.T,cmap=colormap,vmin=numpy.min(Hist[Hist>0]),vmax=numpy.max(Hist),zorder=0)
630/8: pylab.show()
631/1: %run ulysses_clicking.py
631/2: %run ulysses_clicking.py
631/3: %run ulysses_clicking.py
631/4: %run read_in_clicking_test.py
631/5: %run read_in_clicking_test.py
631/6: %run ulysses_clicking.py
631/7: %run read_in_clicking_test.py
631/8: %run read_in_clicking_test.py
631/9: pylab.show()
631/10: pylab.close('all')
631/11: %run read_in_clicking_test.py
632/1: %run read_in_clicking_test.py
633/1: %run read_in_clicking_test.py
633/2: %run ulysses_clicking.py
633/3: %run read_in_clicking_test.py
634/1: %run read_in_clicking_test.py
635/1: %run read_in_clicking_test.py
635/2: %run read_in_clicking_test.py
635/3: %run read_in_clicking_test.py
635/4: %run read_in_clicking_test.py
635/5: pylab.close('all')
635/6: %run read_in_clicking_test.py
635/7: pylab.close('all')
635/8: %run read_in_clicking_test.py
635/9: pylab.close('all')
635/10: %run read_in_clicking_test.py
635/11: %run read_in_clicking_test.py
635/12: pylab.close('all')
635/13: pylab.close('all')
635/14: %run read_in_clicking_test.py
635/15: max(Hist)
635/16: numpy.max(Hist)
635/17: numpy.sort(Hist)[:-10]
635/18: %run read_in_clicking_test.py
635/19: numpy.hist1d(Hist)
635/20: numpy.histogram1d(Hist)
635/21: numpy.histogram(Hist)
635/22: plot(numpy.histogram(Hist))
635/23: plot(numpy.histogram(Hist))
635/24: H = numpy.histogram(Hist)
635/25: shape(H)
635/26: H
635/27: plot(H[0],H[1])
635/28: H[0]
635/29: H[1]
635/30: histogram(Hist)
635/31: hist1d(Hist)
636/1: %run ulysses_clicking.py
636/2: xbins
636/3: ybins
636/4: Hist
636/5: unqiue(Hist)
636/6: unique(Hist)
636/7: numpy.histogram(Hist)
636/8: a,bins = numpy.histogram(Hist)
636/9: pylab.hist(a,bins)
636/10: pylab.show()
636/11: pylab.close('all')
636/12: pylab.hist(a,bins)
636/13: pylab.close('all')
636/14: pylab.hist(a,bins)
636/15: a
636/16: bins
636/17: pylab.hist(a,bins[1:])
636/18: pylab.show()
636/19: pylab.close('all')
636/20: pylab.hist(a,bins[1:])
636/21: a
636/22: aa = a[1:]
636/23: aa
637/1: %run ulysses_clicking.py
637/2: %run ulysses_clicking.py
637/3: %run read_in_clicking_test.py
637/4: Hist
637/5: unique(Hist)
637/6: Histt = Hist[Hist>0]
637/7: Histt
637/8: unique(Histt)
637/9: pylab.hist(Histt,biny)
637/10: pylab.close('all')
637/11: pylab.hist(Histt,biny)
637/12: pylab.hist(Histt,bins='auto')
637/13: Histt
637/14: max(Histt)
637/15: pylab.hist(Histt,bins=numpy.arange(0,max(Histt),100))
637/16: pylab.close('all')
637/17: %run read_in_clicking_test.py
637/18: %run read_in_clicking_test.py
637/19: %run ulysses_clicking.py
637/20: %run read_in_clicking_test.py
637/21: pylab.close('all')
637/22: %run read_in_clicking_test.py
637/23: pylab.close('all')
637/24: %run read_in_clicking_test.py
637/25: Hist
637/26: Hist[Hist>0.]
637/27: %run read_in_clicking_test.py
637/28: %run read_in_clicking_test.py
637/29: %run read_in_clicking_test.py
637/30: %run read_in_clicking_test.py+
637/31: %run read_in_clicking_test.py+
637/32: %run read_in_clicking_test.py
637/33: Hist
637/34: Hist[Hist>0.]
637/35: Mesh = ax.pcolormesh(binx, biny, Hist.T, cmap = colormap)
637/36: size(binx)
637/37: size(biny)
637/38: size(Hist)
637/39: %run read_in_clicking_test.py
637/40: %run read_in_clicking_test.py
637/41: pylab.close('all')
637/42: Hist
637/43: shape(Hist)
637/44: shape(Hist[Hist>0.])
637/45: numpy.min(Hist[Hist>0.])
637/46: pylab.close('all')
637/47: %run read_in_clicking_test.py
637/48: pylab.close('all')
637/49: %run read_in_clicking_test.py
637/50: pylab.close('all')
637/51: %run read_in_clicking_test.py
637/52: pylab.close('all')
637/53: %run ulysses_clicking.py
637/54: %run read_in_clicking_test.py
637/55: pylab.close('all')
637/56: %run read_in_clicking_test.py
637/57: pylab.close('all')
637/58: %run read_in_clicking_test.py
639/1: pylab.close('all')
639/2: %run read_in_clicking_test.py
639/3: pylab.close('all')
639/4: %run ulysses_clicking.py
639/5: pylab.close('all')
639/6: %run ulysses_clicking.py
639/7: %run ulysses_clicking.py
639/8: %run ulysses_clicking.py
639/9: %run ulysses_clicking.py
639/10: d
639/11: d
639/12: %run ulysses_clicking.py
639/13: %run ulysses_clicking.py
640/1: %run ulysses_clicking.py
640/2: %run ulysses_clicking.py
640/3: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200))
640/4: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),weights='brw')
641/1: %run ulysses_clicking.py
642/1: %run ulysses_clicking.py
642/2: H_params = p.get_data().get_data()
642/3: H_params
643/1: %run ulysses_clicking.py
644/1: %run ulysses_clicking.py
644/2: %run read_in_clicking_test.py
644/3: Hist
644/4: H_params
644/5: H_params['Master'][0]
644/6: Hist
644/7: shape(H_params['Master'][0])
644/8: shape(Hist)
644/9: pylab.close('all')
644/10: %run read_in_clicking_test.py
644/11: pylab.close('all')
644/12: %run read_in_clicking_test.py
644/13: d.hist2d('tch','ech',binx=arange(400,450),biny = arange(50,100))
644/14: d.hist2d('tch','ech',binx=arange(400,450),biny = arange(50,100))
644/15: %run read_in_clicking_test.py
644/16: %run read_in_clicking_test.py
644/17: %run read_in_clicking_test.py
644/18: pylab.close('all')
644/19: %run read_in_clicking_test.py
644/20: d.hist2d('tch','ech',binx=arange(400,450),biny = arange(50,100))
645/1: %run read_in_clicking_test.py
645/2: %run ulysses_clicking.py
645/3: p.data['ech']
645/4: d.data['ech']
645/5: unique(d.data['ech'])
645/6: numpy.arange(1,256)
646/1: %run ulysses_clicking.py
647/1: %run ulysses_clicking.py
647/2: %run ulysses_clicking.py
647/3: savetxt('histograms/tofbins_ch.dat',arange(0,1024))
647/4: savetxt('histograms/tofbins_ch.dat',arange(0,1024),fmt='%.0f')
647/5: unique(d.data['tch'])
648/1: %run ulysses_clicking.py
648/2: unique(d.data['epq'])
649/1: ls
649/2: %run EQ_positions_ULYSSES_SWICS.py
650/1: %run EQ_positions_ULYSSES_SWICS.py
650/2: %run EQ_positions_ULYSSES_SWICS.py
650/3: d
650/4: d = uswipha(year=y,tf=[[1,10]])
650/5:
import sys, os
import datetime
sys.path.append('/home/asterix/fischer/ulysses/swics/software/libulpy')
from pylib import dbData
from numpy import array,ndarray,unique,histogram,append,isnan,savetxt,loadtxt,shape
from numpy import arange
from uswipha import uswipha
from matplotlib import pylab
650/6: d = uswipha(year=y,tf=[[1,10]])
650/7: d = uswipha(year=1994,tf=[[1,10]])
650/8: d.data['epq']
650/9: unique(d.data['epq'])
650/10: arange(63)
650/11: d.add_mask('epq')
650/12: d.set_mask('epq','epq',50,50)
650/13: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200))
650/14: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
650/15: d = uswipha(year=1994,tf=[[1,100]])
650/16: d.remove_mask('epq')
650/17: d.show_mask()
650/18: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
650/19: d.add_mask('epq')
650/20: d.set_mask('epq','epq',25,25)
650/21: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200))
650/22: d.add_mask('epq_m')
650/23: d.set_mask('epq_m','epq',25,25)
650/24: d.set_mask('epq_m','epq',25,25)
651/1: %run ulysses_clicking.py
652/1: %run ulysses_clicking.py
652/2: %run EQ_positions_ULYSSES_SWICS.py
653/1: %run EQ_positions_ULYSSES_SWICS.py
653/2:
shape(zeros((1023, 255, 63))

)
653/3: %run EQ_positions_ULYSSES_SWICS.py
653/4: %run EQ_positions_ULYSSES_SWICS.py
653/5: %run EQ_positions_ULYSSES_SWICS.py
654/1: %run EQ_positions_ULYSSES_SWICS.py
654/2: %run EQ_positions_ULYSSES_SWICS.py
654/3: data
654/4: DPATH
654/5: i = 0
654/6: a = loadtxt(DPATH + "counts_DOY150-220_step%i.dat"%(i))
654/7: %run EQ_positions_ULYSSES_SWICS.py
654/8: zeros(2,5,7)
654/9: numpy.zeros(1,3,5)
654/10: numpy.zeros
654/11: numpy.zeros ?
654/12: numpy.zeros help
654/13: numpy.zeros(5)
654/14: numpy.zeros((1,3,5))
654/15: numpy.zeros((2,3,5))
654/16: loadtxt(DPATH + "1993/all_sec/counts%i_%s_step%i.dat" % (year,sec,i))
654/17: a = loadtxt(DPATH + "1993/all_sec/counts%i_%s_step%i.dat" % (year,sec,i))
654/18: a
654/19: shape(a)
654/20: shape(a)
654/21: data
654/22: data[3]
654/23: data[3][:,:,0]
654/24: z = numpy.zeros((1,2,3))
654/25: type(z)
654/26: z
654/27: z = numpy.zeros((10,2,3))
654/28: type(z)
654/29: z
654/30: z(0)
654/31: z[0]
654/32: type(z[0])
654/33: type(z)
654/34:
for i in range(10):
    z[3][:,:,i] = 3
654/35: z = numpy.zeros((10,2,3))
654/36:
for i in range(3):
    z[3][:,:,i] = 3
654/37:
for i in range(2):
    z[3][:,:,i] = 3
654/38: range(2)
654/39: z[3]
654/40:
for i in range(2):
    z[:,:,i] = 3
654/41: z
654/42:
for i in range(1):
    z[:,:,i] = 3
654/43: z
654/44:
for i in range(1):
    z[:,:,i] = 7
654/45: z
654/46: data[3][:, :, i] = loadtxt(DPATH + "1993/all_sec/counts%i_%s_step%i.dat" % (year,sec,i))
654/47: i
654/48: i = 1
654/49: data[3][:, :, i] = loadtxt(DPATH + "1993/all_sec/counts%i_%s_step%i.dat" % (year,sec,i))
655/1: %run EQ_positions_ULYSSES_SWICS.py
655/2: i = 63
655/3: a = loadtxt(DPATH + "1993/all_sec/counts%i_%s_step%i.dat" % (year,sec,i))
655/4: a
655/5: shape(a)
655/6: shape(data[3][:,:62])
655/7: shape(data[3][:,:63])
655/8: shape(data[3][:,:64])
655/9: shape(data[3][:,:163])
655/10: shape(data[3][:,:,163])
655/11: shape(data[3][:,:,63])
655/12: shape(data[3][:,:,62])
655/13: shape(a)
655/14: %run EQ_positions_ULYSSES_SWICS.py
655/15: %run EQ_positions_ULYSSES_SWICS.py
656/1: %run EQ_positions_ULYSSES_SWICS.py
656/2: %run EQ_positions_ULYSSES_SWICS.py
657/1: %run ulysses_clicking.py
657/2: %run ulysses_clicking.py
657/3: %run ulysses_clicking.py
657/4: Hist
657/5: %run ulysses_clicking.py
657/6: %run ulysses_clicking.py
657/7: H_params
657/8: H_params[0]
657/9: H_params
657/10: %run ulysses_clicking.py
657/11: %run ulysses_clicking.py
657/12: %run EQ_positions_ULYSSES_SWICS.py
657/13: pylab.close('all')
657/14: %run EQ_positions_ULYSSES_SWICS.py
657/15: %run ulysses_clicking.py
657/16: %run EQ_positions_ULYSSES_SWICS.py
657/17: pylab.close('all')
657/18: %run EQ_positions_ULYSSES_SWICS.py
658/1: %run EQ_positions_ULYSSES_SWICS.py
658/2: cd ..
658/3: ls
658/4: cd libulpy/
658/5: ls
658/6: from uswipha import uswipha
658/7: from uswipha import uswipha
658/8: d = uswipha(year=[1994,1996],tf=['all'])
658/9: d = uswipha(year=[1994,1996],tf='all')
658/10: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
658/11: pylab.close('all')
658/12: cd ../EQ_positions_gui/
658/13: %run EQ_positions_ULYSSES_SWICS.py
659/1: from uswipha import uswipha
659/2: d = uswipha(year=[1993],tf='all')
659/3: d.add_mask('epq')
659/4: d.set_mask('epq_m','epq',25,25)
659/5: d.set_mask('epq','epq',25,25)
659/6: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=['epq_m'])
659/7: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=['epq_'])
659/8: pylab.close('all')
659/9: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=['epq'])
659/10: pylab.close('all')
659/11: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200),smask=['epq'])
659/12: pylab.show()
659/13: pylab.close('all')
659/14: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
659/15: d.hist2d('tch','ech',binx=arange(400,450),biny = arange(50,100))
659/16: d.hist2d(prodx="tch",prody="ech",binx=arange(0,1024,2),biny=arange(1,256,2))
660/1: pylab.close('all')
660/2: d = uswipha(year=[1993],tf='all')
660/3: from uswipha import uswipha
660/4: d = uswipha(year=[1993],tf='all')
660/5: d.hist2d(prodx="tch",prody="ech",binx=arange(0,1024,2),biny=arange(1,256,2))
660/6: arange(0,1024,2)
660/7: d.hist2d(prodx="tch",prody="ech")
660/8: pylab.close('all')
660/9: d.hist1d('tch')
660/10: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
660/11: from numpy import arange
660/12: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
660/13: p = d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
660/14: p.get_data()
660/15: p.get_data().get_data()
660/16: p = d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
660/17: p = d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
661/1: d = uswipha(year=[1998],tf='all')
661/2: from uswipha import uswipha
661/3: d = uswipha(year=[1998],tf='all')
661/4: from uswipha import uswipha
661/5: p = d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
661/6: d.hist2d
661/7: %run pui_ulysses.py
661/8: ls
661/9: cd ../diy/
661/10: %run pui_ulysses.py
661/11: p = d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
661/12: %run pui_ulysses.py
661/13: p = d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
662/1: from uswipha import uswipha
662/2: ls
662/3: cd ../libulpy/
662/4: ls
662/5: from uwipha import uswipha
662/6: from uswipha import uswipha
662/7: d = uswipha(year=[1998],tf='all')
662/8: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
662/9: cd
662/10: cd Python/pylib/
662/11: %run dbData/
662/12: %run dbData
662/13: %run dbData.py
662/14: ls
662/15: cd dbData/
662/16: %run dbData.py
662/17: ls
662/18: %run _dbData.py
662/19: ls
662/20: cd
662/21: cd ulysses/swics/software/libulpy/
662/22: %run uswipha.py
662/23: d
662/24: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
662/25: d.get_data('ech')
662/26: d.data
662/27: d
662/28: d = uswipha(year=[1998],tf='all')
662/29: d.data
662/30: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
662/31: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
662/32: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200))
662/33: %run uswipha.py
662/34: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
662/35: %run uswipha.py
662/36: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
663/1: %run uswipha.py
664/1: %run uswipha.py
664/2: d = uswipha(year=[1998],tf=[[1,30]])
664/3: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
664/4: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(1,200))
664/5: d.hist2d("tch","ech")
664/6: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1))
664/7: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1))
664/8: %run uswipha.py
664/9: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1))
665/1: %run uswipha.py
665/2: d = uswipha(year=[1998],tf=[[1,3]])
665/3: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1))
666/1: %run uswipha.py
666/2: d = uswipha(year=[1998],tf=[[1,3]])
666/3: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1))
668/1: cd libulpy
668/2: %run uswipha.py
668/3: d = uswipha(year=[1998],tf=[[1,3]])
668/4: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1))
668/5: d.set_mask('epq_m','epq',25,25)
668/6: d = uswipha(year=[1997],tf='all')
668/7: d.set_mask('epq_m','epq',25,25)
668/8: d.remove_mask('epq')
668/9: d.remove_mask('epq_m')
668/10: d.set_mask('epq_m','epq',25,25)
668/11: d.set_mask('ech_m','epq',25,25)
668/12: d.set_mask('ech_m','ech',3,25)
668/13: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1),smask=['ech_m','epq_m'])
668/14: d.show_mask()
668/15: d.set_mask('ech_m','ech',3,200)
668/16: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1),smask=['ech_m','epq_m'])
668/17: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
668/18: d.set_mask('ech_m','epq',45,45)
668/19: d.set_mask('epq_m','epq',45,45)
668/20: pylab.close('all')
668/21: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1),smask=['ech_m','epq_m'])
668/22: d.show_mask()
668/23: d.set_mask('epq_m','epq',45,45,reset=True)
668/24: d.set_mask('ech_m','epq',45,45,reset=True)
668/25: d.set_mask('ech_m','ech',3,25,reset=True)
668/26: d.show_mask()
668/27: pylab.close('all')
668/28: d.show_mask()
668/29: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1),smask=['ech_m','epq_m'])
668/30: d.set_mask('ech_m','ech',3,250,reset=True)
668/31: pylab.close('all')
668/32: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(1,200,1),smask=['ech_m','epq_m'])
668/33: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(0,200,1),smask=['ech_m','epq_m'])
668/34: unique(d.get_data['ech'])
668/35: d.get_data['ech']
668/36: d.data['ech']
668/37: unqieu(d.data['ech'])
668/38: unique(d.data['ech'])
668/39: d.hist1d('ech')
668/40: d.hist1d('ech',Master=False)
668/41: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60),Master=False,weights='bwr')
668/42: d.data
668/43: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60),Master=False,weights='brw')
668/44: pylab.close('all')
668/45: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(0,200,1),smask=['ech_m','epq_m'],weights='brw')
668/46: d.hist2d("tch","ech",binx=arange(0,1024,1),biny=arange(0,200,1),smask=['ech_m','epq_m'])
668/47: d.remove_mask('all')
668/48: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60),Master=False,weights='brw')
668/49: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60),weights='brw')
668/50: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
668/51: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
668/52: pylab.close('all')
668/53: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
668/54: d = uswipha(year=[1997,1999,2004],tf='all')
668/55: d.animate2d(prodx="tch",prody="ech",prodz="epq",binx=arange(0,1024,2),biny=arange(1,256,2),binz=arange(10,60))
668/56: arange(1990,2019)
668/57: arange(1990,2010)
669/1: ls
669/2: cd EQ_positions_gui/
669/3: %run ulysses_clicking.py
670/1: %run ulysses_clicking.py
671/1: %run ulysses_clicking.py
672/1: %run ulysses_clicking.py
673/1: %run ulysses_clicking.py
673/2: %run ulysses_clicking.py
673/3: %run ulysses_clicking.py
673/4: d
674/1: %run ulysses_clicking.py
674/2: %run ulysses_clicking.py
674/3: %run ulysses_clicking.py
674/4: %run ulysses_clicking.py
674/5: pwd
674/6: y
674/7: os.mkdir('histograms/1994)
674/8: os.mkdir('histograms/1994')
674/9: pwd
674/10: pwd
674/11: os.mkdir('histograms/1994/all_det/trebles')
674/12: ls
675/1: %run ulysses_clicking.py
675/2: %run ulysses_clicking.py
675/3: y = 1003
675/4: y = 1993
675/5: os.mkdir('histograms/%i'%(y))
675/6: os.mkdirs('histograms/%i/all_det/trebles/brw'%(y))
675/7: os.makedirs('histograms/%i/all_det/trebles/brw'%(y))
675/8: %run ulysses_clicking.py
675/9: %run ulysses_clicking.py
675/10: %run ulysses_clicking.py
675/11: %run ulysses_clicking.py
675/12: %run ulysses_clicking.py
675/13: %run ulysses_clicking.py
675/14: %run ulysses_clicking.py
675/15: %run ulysses_clicking.py
675/16: %run ulysses_clicking.py
676/1: %run ulysses_clicking.py
676/2: %run ulysses_clicking.py
677/1: %run ulysses_clicking.py
677/2: %run ulysses_clicking.py
678/1: %run ulysses_clicking.py
679/1: %run ulysses_clicking.py
680/1: %run EQ_positions_ULYSSES_SWICS.py
680/2: len(arange(150,650))
680/3: len(arange(5,140))
681/1: %run EQ_positions_ULYSSES_SWICS.py
681/2: %run EQ_positions_ULYSSES_SWICS.py
681/3: %run EQ_positions_ULYSSES_SWICS.py
682/1: %run ulysses_clicking.py
683/1: %run EQ_positions_ULYSSES_SWICS.py
684/1: %run EQ_positions_ULYSSES_SWICS.py
684/2: %run EQ_positions_ULYSSES_SWICS.py
684/3: %run EQ_positions_CTOF.py
684/4: %run EQ_positions_ULYSSES_SWICS.py
684/5: %run uswipha.py
684/6: cd ..
684/7: ls
684/8: ls diy
684/9: from uswipha import uswipha
684/10: cd ..
684/11: ls
684/12: from uswipha import uswipha
684/13: ls
685/1: %run EQ_positions_ULYSSES_SWICS.py
685/2: %run EQ_positions_ACE_SWICS.py
686/1: %run EQ_positions_ACE_SWICS.py
686/2: cd ..
686/3: cd diy/
686/4: from uswipha import uswipha
686/5: cd ../
686/6: ls
686/7: cd ..
686/8: cd software/
686/9: from uswipha import uswipha
686/10: ls
686/11: cd libulpy/
686/12: from uswipha import uswipha
686/13: d = uswipha(year=[1997,1999,2004],tf='all')
686/14: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,200,1))
686/15: pylab.close('all')
686/16: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2))
686/17: d.sync_swoops()
686/18: d.add_mask('v','vsw',400,420)
686/19: d.set_mask('v','vsw',400,420)
686/20: pylab.close('all')
686/21: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2))
686/22: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax'))
686/23: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
686/24: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2))
687/1: ls
687/2: %run ulysses_clicking.py
688/1: %run ulysses_clicking.py
688/2: %run ulysses_clicking.py
689/1: %run ulysses_clicking_adding.py
689/2: %run ulysses_clicking_adding.py
689/3: %run ulysses_clicking_adding.py
689/4: %run ulysses_clicking_adding.py
689/5: pwd
689/6: %run ulysses_clicking_adding.py
689/7: %run ulysses_clicking_adding.py
690/1: fid = open('histograms/%i/rngALL/detALL/ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (1993,1993,1993, 1), 'r')
690/2: cd histograms/1993/rngALL/detALL
690/3: ls
690/4: fid = open('histograms/%i/rngALL/detALL/ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (1993,1993,1993, 1), 'r')
690/5: fid.close()
691/1: %run ulysses_clicking_adding.py
691/2: cd histograms/1994/rngALL/detALL/
691/3: pwd
692/1: %run ulysses_clicking_adding.py
692/2: cd histograms/1993/rngALL/detALL/
692/3: ls
692/4: ls
692/5: pwd
692/6: cd ../../..
692/7: ls
692/8: cd 1993/rngALL/detALL/
692/9: ls
692/10: fid = open('ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (1993,1993,1993, 1), 'r')
692/11: fid = open('ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (1993,1993, 1), 'r')
693/1: pwd
693/2: %run ulysses_clicking_adding.py
693/3: %run ulysses_clicking_adding.py
694/1: fid = open('/histograms/%i/rngALL/detALL/ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (y, y, y, epq), 'r')
694/2: y = 1993
694/3: epq = 1
694/4: fid = open('/histograms/%i/rngALL/detALL/ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (y, y, y, epq), 'r')
694/5: cd histograms/1993/rngALL/detALL
694/6: fid = open('ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (y, y, epq), 'r')
694/7: fid
695/1: %run ulysses_clicking_adding.py
695/2: pwd
695/3: fid = open('/histograms/%i/rngALL/detALL/ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (y, y, y, epq), 'r')
696/1: %run ulysses_clicking_adding.py
696/2: fid
696/3: l = fid.readline()
696/4: l
696/5: a = fid.loadtxt()
696/6: import numpy as np
696/7: a = fid.np.loadtxt()
696/8: a = np.loadtext(fid)
696/9: a = np.loadtxt(fid)
696/10: a
696/11: dims(a)
696/12: shape(a)
696/13: y = 1994
696/14: fid = open('/histograms/%i/rngALL/detALL/ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (y, y, y, epq), 'r')
696/15: fid = open('histograms/%i/rngALL/detALL/ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (y, y, y, epq), 'r')
696/16: pwd
697/1: %run ulysses_clicking.py
698/1: %run ulysses_clicking.py
699/1: %run ulysses_clicking.py
700/1: %run EQ_positions_ACE_SWICS.py
699/2: n
700/2: %run EQ_positions_CTOF.py
701/1: %run ulysses_clicking_adding.py
701/2: fid
701/3: yy = 1994
701/4: y = 1994
701/5: fid2 = open('histograms/%i/rngALL/detALL/ULYSSES_SWICS_%i_%i_rngALL_detALL_step%i.dat' % (y, y, y, epq), 'r')
701/6: l = loadtxt(fid)
701/7: l1 = loadtxt(fid2)
701/8: l
701/9: ll = l + l1
701/10: shape(ll)
701/11: shape(l)
701/12: a = np.zeros(549,134)
701/13: s = (549,134)
701/14: np.zeros(s)
702/1: %run ulysses_clicking_adding.py
702/2: %run ulysses_clicking_adding.py
703/1: %run ulysses_clicking_adding.py
704/1: %run ulysses_clicking_adding.py
704/2: ls
704/3: %run ulysses_clicking_adding.py
704/4: ls
704/5: cd ..
704/6: ls
704/7: cd diy
704/8: ls
704/9: cd ..
704/10: from uswipha import uswipha
704/11: d = uswipha(year=[1997],tf='all')
704/12: d.add_mask('rng_m')
704/13: d.set_mask('rng_m','rng',0,0)
704/14: d.show_mask()
704/15: d.set_mask('rng_m','rng',1,1,reset=True)
704/16: d.show_mask()
704/17: d.set_mask('rng_m','rng',2,2,reset=True)
704/18: d.show_mask()
704/19: arange(3)
704/20: epq = 5
704/21: d.set_mask('epq_m','epq',epq,epq,reset=True)
704/22: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
704/23: H_params = p.get_data().get_data()
704/24: H_params
704/25: r = 1
704/26: d.set_mask('rng_m','rng',r,r,reset=True)
704/27: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m','rng_m'])
704/28: d.reset_mask('all')
704/29: .set_mask('epq_m','epq',epq,epq,reset=True)
704/30: d.set_mask('epq_m','epq',epq,epq,reset=True)
704/31: d.set_mask('epq_m','rng',r,r,reset=True)
704/32: d.show_mask()
704/33: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
705/1: %run ulysses_clicking.py
706/1: %run ulysses_clicking.py
707/1: %run ulysses_clicking.py
708/1: import numpy as np
708/2: a = np.array([320,362,352,333,305,317,325,405,348,312])
708/3: t = a
708/4: t
708/5: v = 10000./t
708/6: v
708/7: np.mean(v)
708/8: np.std(v)
709/1: %run ulysses_clicking.py
709/2: %run ulysses_clicking.py
709/3: %history -g
710/1: %run ulysses_clicking.py
711/1: %run ulysses_clicking.py
711/2: d
711/3: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/4: p
711/5: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/6: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/7: cc
711/8: C
711/9: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/10: P
711/11: p
711/12: p
711/13: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/14: pylab.close('all')
711/15: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/16: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/17: from pylib import dbData
711/18: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/19: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/20: from pylib import dbData
711/21: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/22: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/23: from pylib import dbData
711/24: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/25: pylab.close('all')
711/26: pylab.close('all')
711/27: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/28: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
711/29: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
712/1: d = uswipha(year=[1992],tf='all')
712/2: from uswipha import uswipha
713/1: from uswipha import uswipha
713/2: d = uswipha(year=[1994],tf='all')
713/3: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
713/4: r = 3
713/5: d.set_mask('epq_m','rng',r,r,reset=True)
713/6: epq = 50
713/7: d.set_mask('epq_m','epq',epq,epq,reset=True)
713/8: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
714/1: r = 3
714/2: epq = 50
714/3: d.set_mask('epq_m','epq',epq,epq,reset=True)
714/4: d = uswipha(year=[1994],tf='all')
714/5: from uswipha import uswipha
714/6: d = uswipha(year=[1994],tf='all')
714/7: d.set_mask('epq_m','epq',epq,epq,reset=True)
714/8: d.set_mask('epq_m','rng',r,r,reset=True)
714/9: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
714/10: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
714/11: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
714/12: from pylib import dbData
714/13: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
715/1: d = uswipha(year=[1994],tf='all')
715/2: from uswipha import uswipha
715/3: d = uswipha(year=[1994],tf='all')
715/4: d = uswipha(year=[1994],tf='all')
715/5: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
715/6: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
715/7: reload(dbData)
715/8: from pylib import dbData
715/9: reload(dbData)
715/10: dbData
715/11: dbData.type()
715/12: type(dbData)
715/13: pylib.dbData
715/14: reload(pylib.dbData)
715/15: reload(_dbData)
715/16: from pylib import dbData
715/17: reload(_dbData)
715/18: reload(dbData)
715/19: import(dbData)
715/20: import dbData
715/21: pylib
715/22: from pylib import dbData
715/23: import(pylib.dbData)
715/24: from pylib import dbData
715/25: import(_dbData)
715/26: reload(_dbData)
715/27: reload(dbData)
715/28: reload(pylib.dbData)
715/29: import pylib
715/30: reload(pylib.dbData)
716/1: d = uswipha(year=[1994],tf=[[1,10]])
716/2: from uswipha import uswipha
716/3: d = uswipha(year=[1994],tf=[[1,10]])
716/4: r = 3
716/5: epq = 50
716/6: d.set_mask('epq_m','rng',r,r,reset=True)
716/7: d.set_mask('ech_m','epq',45,45,reset=True)
716/8: d.set_mask('epq_m','epq',epq,epq,reset=True)
716/9: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
717/1: ls
717/2: cd ..
717/3: cd EQ_positions_gui/
717/4: %run tetsbla.py
717/5: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
718/1: %run tetsbla.py
719/1: %run tetsbla.py
719/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
720/1: %run tetsbla.py
720/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
720/3: p
720/4: unique(p)
720/5: np.amax(p)
720/6: np.amin(p)
720/7: np.amin(C[C>0])
720/8: np.amin(p[p>0])
720/9: np.amin(p)
721/1: %run tetsbla.py
721/2: %run tetsbla.py
721/3: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
722/1: %run tetsbla.py
722/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
723/1: %run tetsbla.py
723/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
724/1: %run tetsbla.py
724/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
724/3: p
724/4: H_params = p.get_data().get_data()
724/5: H_params
724/6: H_params['epq_m']
724/7: H_params['epq_m'][0]
724/8: unique(H_params['epq_m'][0])
725/1: %run tetsbla.py
725/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
725/3: p.get_data().get_data()
725/4: H_params = p.get_data().get_data()
725/5: H_params['epq_m']
725/6: epq_m
726/1: %run tetsbla.py
726/2: epq_m
726/3: d.show_mask()
726/4: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
726/5: p
726/6: H_params = p.get_data().get_data()
726/7: H_params
727/1: %run tetsbla.py
727/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
728/1: %run tetsbla.py
728/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
729/1: %run tetsbla.py
729/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
729/3: H_params = p.get_data().get_data()
729/4: p
729/5: unique(p)
730/1: %run tetsbla.py
730/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
730/3: p
730/4: H_params = p.get_data().get_data()
730/5: H_params['epq_m'][0]
730/6: uniqe(p)
730/7: unique(p)
730/8: unique(H_params['epq_m'][0])
730/9: arange(3)
730/10:
for epq in arange(6):
    d.set_mask(
    'epq_m','epq',epq,epq,reset=True)
730/11:
for epq in arange(6):
    d.set_mask('epq_m','epq',epq,epq,reset=True)
    p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
730/12:
for epq in arange(6):
    d.set_mask('epq_m','epq',epq,epq,reset=True)
    p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
    H_params = p.get_data().get_data()
    Hist, xbins, ybins = [H_params['epq_m'][n] for n in [0,1,2]]
730/13: pylab.close('all')
730/14:
for epq in arange(6):
    d.set_mask('epq_m','epq',epq,epq,reset=True)
    p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
    H_params = p.get_data().get_data()
    Hist, xbins, ybins = [H_params['epq_m'][n] for n in [0,1,2]]
    print(epq)
730/15: pylab.close('all')
730/16: d.set_mask('epq_m','epq',2,2,reset=True)
730/17: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
730/18: p
730/19: p.get_data().get_data()
730/20: d.set_mask('epq_m','epq',1,1,reset=True)
730/21: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
730/22: p.get_data().get_data()
731/1: %run tetsbla.py
731/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
731/3: p
731/4: unique(p)
732/1: %run tetsbla.py
732/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
732/3: unique(p)
733/1: %run tetsbla.py
733/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
733/3: p
733/4: unique(p)
734/1: %run tetsbla.py
734/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
734/3: p
735/1: %run tetsbla.py
735/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
735/3: p
735/4: shape(p)
735/5: p.get_data().get_data()
735/6: type(p)
736/1: %run tetsbla.py
736/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
736/3: p.get_data().get_data()
736/4: H_params['epq_m'][0]
736/5: H_params = p.get_data().get_data()
736/6: H_params['epq_m'][0]
736/7: shape(H_params['epq_m'])
736/8: shape(H_params['epq_m'][0])
736/9: shape(H_params['epq_m'][0])
736/10: type(H_params['epq_m'][0])
736/11: H_params['epq_m'][1]
736/12: arange(100,650)
736/13: H_params['epq_m'][2]
736/14: arange(5,140)
738/1: %run ulysses_clicking.py
739/1: %run ulysses_clicking.py
740/1: %run ulysses_clicking.py
741/1: %run ulysses_clicking.py
741/2: zeros(1,20)
741/3: zeros((1,20))
741/4: zeros((549,134))
742/1: %run ulysses_clicking.py
743/1: %run ulysses_clicking.py
744/1: %run ulysses_clicking.py
745/1: %run ulysses_clicking.py
746/1: %run EQ_positions_ULYSSES_SWICS.py
746/2: %run EQ_positions_ULYSSES_SWICS.py
748/1: %run tetsbla.py
748/2: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
749/1: %run tetsbla.py
749/2: d.hist2d("tch","epq",binx=arange(0,1024,1),biny=arange(0,65,2),norm='ymax')
749/3: d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
749/4: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
749/5: p
749/6: unique(p)
749/7: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),smask=['epq_m'])
749/8: p
749/9: unique(p)
750/1: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),smask=['epq_m'])
750/2: %run tetsbla.py
750/3: %run tetsbla.py
750/4: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),smask=['epq_m'])
750/5: d.show_mask()
751/1: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),smask=['epq_m'])
751/2: %run tetsbla.py
751/3: %run tetsbla.py
751/4: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),smask=['epq_m'])
751/5: d.show_mask()
751/6: p
751/7: unique(p)
751/8: d.set_mask('epq_m','rng',1,2,reset=True)
751/9: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),smask=['epq_m'])
751/10: d.show_mask()
751/11: pylab.close('all')
751/12: d.show_mask()
751/13: d.data['rng']
751/14: unique(d.data['rng'])
751/15: d.hist1d('rng')
751/16: pylab.close('all')
751/17: d.set_mask('epq_m','rng',2,2,reset=True)
751/18: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),smask=['epq_m'])
751/19: d.hist1d('rng')
752/1: %run tetsbla.py
752/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),smask=['epq_m'])
752/3: d.get_data['ech']
752/4: d.get_data()
752/5: d.get_data(['epq_m'],'rng')
752/6: unique(d.get_data(['epq_m'],'rng'))
752/7: unique(d.get_data(['epq_m'],'tch'))
752/8: unique(d.get_data(['epq_m'],'epq'))
752/9: unique(d.get_data(['epq_m'],'ech'))
752/10: d.set_mask('epq_m','rng',0,0,reset=True)
752/11: unique(d.get_data(['epq_m'],'ech'))
753/1: %run EQ_positions_ULYSSES_SWICS.py
754/1: %run EQ_positions_ULYSSES_SWICS.py
754/2: zeros((549,134))
754/3: zeros((549,134)) * 6
754/4: a = zeros((549,134))
754/5: a*6
754/6: type(a)
754/7: a.multiply(6)
754/8: numpy.multiply(a,6)
754/9: 6*a
754/10: np.full((10,20),6)
754/11: a
754/12: a.fill(6)
754/13: a
755/1: numpy.arange(2,3)
756/1: %run ulysses_clicking.py
757/1: %run ulysses_clicking.py
757/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
758/1: %run ulysses_clicking.py
759/1: %run ulysses_clicking.py
759/2: shape(Hist)
759/3: Hist
760/1: %run ulysses_clicking.py
760/2: %run ulysses_clicking.py
761/1: %run ulysses_clicking.py
761/2: %run ulysses_clicking.py
762/1: %run ulysses_clicking.py
763/1: %run ulysses_clicking.py
763/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
763/3: unique(d.get_data(['epq_m'],'ech'))
763/4: unique(d.get_data(['epq_m'],'rng'))
763/5: unique(d.get_data([],'rng'))
763/6: unique(d.get_data([],'epq'))
763/7: d.show_mask()
764/1: d.show_mask()
764/2: p = d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
764/3: %run ulysses_clicking.py
765/1: %run ulysses_clicking.py
765/2: d.show_mask()
765/3: d.set_mask('epq_m','epq',0,50,reset=True)
765/4: d.show_mask()
765/5: pylab.close('all')
765/6: d.show_mask()
765/7: unique(d.get_data([],'epq'))
765/8: unique(d.get_data(['epq_m'],'epq'))
765/9: d.hist1d('epq')
765/10: d.set_mask('epq_m','epq',0,0,reset=True)
765/11: d.show_mask()
765/12: pylab.close('all')
765/13: d.show_mask()
765/14: d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
766/1: %run ulysses_clicking.py
767/1: %run ulysses_clicking.py
768/1: %run ulysses_clicking.py
768/2: %run ulysses_clicking.py
768/3: d.hist2d('tch','ech',binx=arange(100,650),biny = arange(5,140),weights='brw',smask=['epq_m'])
769/1: d = uswipha(year=[1994],tf=[[1,10]])
769/2: from uswipha import uswipha
770/1: %run ulysses_clicking.py
770/2: p
770/3: H_params = p.get_data().get_data()
770/4: Hist, xbins, ybins = [H_params['epq_m'][n] for n in [0,1,2]]
770/5: Hisz
770/6: Hist
770/7: unique(Hist)
770/8: shape(Hist)
770/9: a = zeros((10,10))
770/10: a
770/11: a[1,1] = 5
770/12: a
770/13: a[1,1] = 0
770/14: b = arange(11)
770/15: b
770/16: a[1,:]=b
770/17: b = arange(10)
770/18: a[1,:]=b
770/19: a
771/1: %run ulysses_clicking.py
771/2: p
771/3: p.get_data().get_data()
771/4: shape(p.get_data().get_data())
771/5: shape(p.get_data().get_data()['peq_m'])
771/6: shape(p.get_data().get_data()['epq_m'])
771/7: H_params = p.get_data().get_data()
771/8: H_params['epq_m'][1]
771/9: H_params['epq_m'][0]
771/10: sahpe(H_params['epq_m'][0])
771/11: shape(H_params['epq_m'][0])
772/1: %run ulysses_clicking.py
773/1: %run ulysses_clicking.py
773/2: Hist
774/1: %run ulysses_clicking.py
775/1: %run ulysses_clicking.py
775/2: Hist
775/3: shape(Hist)
775/4: H_params['epq_m'][0]
775/5: p
775/6: d.hist1d('tch', binx=arange(100, 650), smask=['epq_m'])
775/7: p.get_data().get_data()
775/8: H_params = p.get_data().get_data()
775/9: H_params['epq_m'][0]
775/10: Hist = zeros((134,549))
775/11: Hist
775/12: Hist[0,:] = H_params['epq_m'][0]
775/13: shape(Hist)
775/14: Hist = Hist.T
775/15: shape(Hist)
775/16: unique(Hist)
776/1: %run ulysses_clicking.py
776/2: d
776/3: d.data['det']
776/4: unique(d.data['det'])
777/1: %run ulysses_clicking.py
778/1: %run ulysses_clicking.py
779/1: %run ulysses_clicking.py
779/2: cd ..
780/1: %run pui_ulysses.py
780/2: d = uswipha(year=[1994],tf=[[1,100]])
780/3: d.get_data([],'aa')
780/4: d.sync_traj()
780/5: d.get_data([],'aa')
780/6: d.get_data([],'aa')[::200]
780/7: shape(d.get_data([],'aa'))
780/8: shape(d.get_data([],'aa')[::200])
780/9: d.get_data([],'aa')[0:0:0]
780/10: 200*13717
780/11: d.summary_traj()
780/12: %run pui_ulysses.py
780/13: summary_traj(d)
780/14: d = uswipha(year=[1994,1995],tf='all')
780/15: d.sync_traj()
780/16: summary_traj(d)
780/17: d.get_data([],'aa')
780/18: d.get_data([],'d_90')
780/19: d.get_data([],'d90')
780/20: 6*365
780/21: data.get_data([], 'd90')[::200]
780/22: d.get_data([], 'd90')[::200]
780/23: len(d.get_data([], 'd90')[::200])
780/24: pylab.close('all')
780/25: summary_traj(d)
780/26: pylab.close('all')
780/27: %run pui_ulysses.py
780/28: summary_traj(d)
780/29: pylab.close('all')
780/30: %run pui_ulysses.py
780/31: summary_traj(d)
780/32: pylab.close('all')
780/33: %run pui_ulysses.py
780/34: pylab.close('all')
780/35: summary_traj(d)
780/36: %run pui_ulysses.py
780/37: summary_traj(d)
780/38: %run pui_ulysses.py
780/39: pylab.close('all')
780/40: summary_traj(d)
780/41: pylab.close('all')
780/42: pylab.close('all')
780/43: %run pui_ulysses.py
780/44: summary_traj(d)
780/45: %run pui_ulysses.py
780/46: pylab.close('all')
780/47: summary_traj(d)
780/48: np.arange(365, 1 * 365 + 1, 365)
780/49: np.arange(365, 2 * 365 + 1, 365)
780/50: d90
780/51: d.get_data([], 'd90')[::200]
780/52: summary_traj(d)
780/53: %run pui_ulysses.py
780/54: pylab.close('all')
780/55: summary_traj(d)
780/56: 6*365
780/57: 4*365
780/58: %run pui_ulysses.py
780/59: pylab.close('all')
780/60: summary_traj(d)
780/61: %run pui_ulysses.py
780/62: pylab.close('all')
780/63: summary_traj(d)
780/64: pylab.close('all')
780/65: %run pui_ulysses.py
781/1: %run pui_ulysses.py
781/2: %run pui_ulysses.py
781/3: %run pui_ulysses.py
781/4: %run pui_ulysses.py
781/5: %run pui_ulysses.py
781/6: %run pui_ulysses.py
781/7: %run pui_ulysses.py
781/8: %run pui_ulysses.py
781/9: summary_traj(d)
781/10: d = uswipha(year=[1994,1995],tf='all')
781/11: summary_traj(d)
781/12: d.sync_traj()
781/13: summary_traj(d)
781/14: %run pui_ulysses.py
781/15: %run pui_ulysses.py
781/16: summary_traj(d)
781/17: d.get_data([], 'r')
781/18: min(d.get_data([], 'r'))
781/19: %run pui_ulysses.py
781/20: pylab.close('all')
781/21: summary_traj(d)
781/22: trajectory(d)
781/23: animate_polar(d)
781/24: a = Animation()
781/25: d.animate_polar()
781/26: d = Animation(year=[1994,1995],tf='all')
781/27: a = Animation(d,'det','sec','vsw')
781/28: pylab.close('all')
782/1: %run load_pui_ulysses.py
782/2: %run pui_ulysses.py
782/3: a = Animation(d,'det','sec','doy')
782/4: a.animate_polar()
782/5: pylab
783/1: from uswipha import uswipha
783/2: d = Animation(year=[1994,1995],tf='all')
783/3: d = uswipha(year=np.arange(1990,2010),tf='all')
783/4: d = uswipha(year=[1994,1995],tf='all')
783/5: d = uswipha(year=range(1990,2010),tf='all')
784/1: %run uswipha.py
784/2: d = uswipha(year=range(1990,2010),tf='all')
785/1: %run uswipha.py
785/2: d = uswipha(year=range(1990,2002),tf='all')
785/3: d
785/4: d
786/1: d = uswipha(year=range(1990,1996),tf='all')
786/2: %run uswipha.py
786/3: d = uswipha(year=range(1990,1999),tf='all')
787/1: %run ace_colimator.py
787/2: %run swics_collimator.py
788/1: %run swics_collimator.py
788/2: c = collimator()
788/3: c = collimator
788/4: c
788/5: c.plot()
788/6: c.plot()
788/7: plot(c)
788/8: c.plot_rot()
788/9: plot_rot(c)
788/10: c.plot_rot()
788/11: c = collimator()
789/1: %run swics_collimator.py
789/2: c = collimator()
789/3: c
789/4: c.plot()
789/5: ang_para=arange(0.,-90.001,1.)
789/6: ang_para
789/7: ang_perp=arange(-2.,2.001,1.)
789/8: ang_perp
789/9: base_points = zeros((3,ang_perp.shape[0]))
789/10: base_points
790/1: ang_perp=arange(-2.,2.001,1.)
790/2: ang_para=arange(0.,-90.001,-1.)
790/3: md1 = ang_para>30.
790/4: md1
791/1: %run swics_collimator.py
791/2: c = collimator
791/3: c = collimator()
791/4: c.det1
791/5: c.md1
791/6: c.ang_perp
791/7: c.ang_para
791/8: c.ang_para[c.md1]
791/9: c.det1
791/10: c.ang_perp
791/11: a = zeros((10,10))
791/12: a
791/13: a[:,2] = 5.
791/14: a
793/1: %run swics_collimator.py
793/2: c = collimator()
793/3: base_points = zeros((3,self.ang_perp.shape[0]))
793/4: base_points = zeros((3,c.ang_perp.shape[0]))
793/5: base_points
793/6:
            for i,ang in enumerate(c.ang_perp):
    print(i,ang)
793/7:
            for i,ang in enumerate(c.ang_perp):
    base_points[:,i] = array([cos(ang/180.*pi),sin(ang/180.*pi),0])
793/8: base_points
793/9:
for i,ang in enumerate(c.ang_para[c.md1]):
    print(i,ang)
794/1: %run swics_collimator.py
794/2: c = collimator()
794/3: .det1 = zeros((3,c.ang_perp.shape[0]*c.ang_para[c.md1].shape[0]))
794/4: det1 = zeros((3,c.ang_perp.shape[0]*c.ang_para[c.md1].shape[0]))
794/5: det1
794/6: shape(det1)
794/7: c.ang_para
794/8: shape(c.ang_para)
794/9: c.ang_para[c.md1]
794/10: shape(c.ang_para[c.md1])
794/11:
for i,ang in enumerate(c.ang_para[c.md1]):
    print(i,ang)
794/12: c.ang_perp
794/13: shape(c.ang_perp)
794/14:
for i,ang in enumerate(c.ang_para[c.md1]):
    print(i*c.ang_perp.shape[0])
    print((i+1)*c.ang_perp.shape[0],'\n')
795/1: %run swics_collimator.py
795/2: i = 1
795/3: det1 = zeros((3,c.ang_perp.shape[0]*c.ang_para[c.md1].shape[0]))
795/4: c = collimator()
795/5: det1 = zeros((3,c.ang_perp.shape[0]*c.ang_para[c.md1].shape[0]))
795/6: i = 1
795/7: det1[:,i*c.ang_perp.shape[0]:(i+1)*c.ang_perp.shape[0]]
795/8: det1[:,i*c.ang_perp.shape[0]:(i+1)*c.ang_perp.shape[0]] = 55.
795/9: det1
795/10: c.base_points
795/11: array([cos(56./180.*pi),sin(56./180.*pi),0])
795/12: c.base_points
795/13: shape(c.base_points)
795/14: rax = array([cos(56./180.*pi),sin(56./180.*pi),0])
795/15: ang = 0.
795/16: rotate(c.base_points,rax,ang,deg=True)
795/17: ang = 1.
795/18: rotate(c.base_points,rax,ang,deg=True)
795/19: rotate(c.base_points,rax,ang,deg=True).reshape(c.base_points.shape)
795/20: c.base_points
795/21: 2./360*2*pi
795/22: rphiax = array([0.,0.,1.])
795/23: rotate(array([0.0,0.,1.]),rphiax,30,deg=True)
795/24: rax = array([1.,0.,0.])
795/25: cross(rax,cross(array([1.,0.,0.]),rax))
795/26: rax = array([0.9,0.1,0.])
795/27: cross(rax,cross(array([1.,0.,0.]),rax))
795/28: rax = array([0.5,0.5,0.5])
795/29: cross(rax,cross(array([1.,0.,0.]),rax))
795/30: dot([1,2,3],[6,8,10])
795/31: dot([1,2,3],[2,3,4])
795/32: c.spang
795/33: c.spax
796/1: %run swics_collimator.py
796/2: c.spax
796/3: c = collimator()
796/4: c.spax
796/5: c.det1
796/6: c.det1_rot
796/7: %run swics_collimator.py
796/8: c = collimator()
796/9: d.det1
796/10: c.det1
796/11: %run swics_collimator.py
796/12: c =
796/13: c = collimator()
796/14: c.det1
797/1: %run swics_collimator.py
797/2: c = collimator()
798/1: %run swics_collimator.py
798/2: c = collimator()
798/3: c.FoV
798/4: c.FoV.shape(0)
798/5: c.FoV.shape
798/6: 90/3.
798/7: 22.5*3
799/1: %run swics_collimator.py
799/2: c = collimator()
799/3: c.FoV
799/4: c.FoV[0]
799/5: c.FoV[0,1,:,0]
799/6:
for sec in range(8):
    print(sec*45.+22.5)
799/7: 360-337.5
799/8: 360/8.
799/9: FoV=zeros((3,8,3,1))
799/10: shape(FoV)
799/11: FoV
799/12: c.FoV[0,0,:,:10]
799/13: c.plot()
800/1: %run swics_collimator.py
800/2: c = collimator()
800/3: c.plot()
800/4: c._calc_points()
800/5: pylab.close('all')
800/6: c.plot()
801/1: %run swics_collimator.py
801/2: %run swics_collimator.py
801/3: c = collimator()
801/4: c.plot()
802/1: %run swics_collimator.py
802/2: c = collimator()
802/3: c.det1
802/4: c.det1.shape
802/5: c._calc_points()
802/6: c.det1
804/1: %run swics_collimator.pyw
804/2: %run swics_collimator.py
804/3: c = collimator()
804/4: c.plot()
804/5: c = collimator()
804/6: c.plot
804/7: c.plot()
804/8: a = c.plot()
805/1: %run swics_collimator.py
805/2: c = collimator()
805/3: c.plot()
805/4: c.plot()
805/5: %run swics_collimator.py
805/6: c = collimator()
805/7: c.plot()
805/8: c.det1[0,:]
805/9: %run swics_collimator.py
805/10: %run swics_collimator.py
805/11: c = collimator()
805/12: c.plot()
805/13: %run swics_collimator.py
805/14: c = collimator()
805/15: c.plot()
805/16: %run swics_collimator.py
805/17: c = collimator()
805/18: c.plot()
805/19: %run swics_collimator.py
805/20: c = collimator()
805/21: c.plot()
805/22: array(0:5)
805/23: array(0,5)
805/24: array[0:5]
805/25: array[0,5]
805/26: arange(0,5)
805/27: arange(0:5)
805/28: %run swics_collimator.py
805/29: %run swics_collimator.py
805/30: c = collimator()
805/31: c.plot()
805/32: pylab.close('all')
805/33: %run swics_collimator.py
805/34: c = collimator()
805/35: c.plot()
805/36: pylab.close('all')
805/37: %run swics_collimator.py
805/38: c = collimator()
805/39: c.plot()
805/40: arange(0,cos(56./180.*pi))
805/41: arange(1,10,5)
805/42: arange(0,2,cos(56./180.*pi))
805/43: arange(0,1.,cos(56./180.*pi))
806/1: %run swics_collimator.py
806/2: c = collimator()
806/3: c.plot()
806/4: arange(0,1,cos(56./180.*pi))
807/1: %run swics_collimator.py
807/2: c = collimator()
807/3: c.plot()
807/4: %run swics_collimator.py
807/5: pylab.close('all')
807/6: c = collimator()
807/7: c.plot()
808/1: %run swics_collimator.py
808/2: c = collimator()
808/3: c._calc_points()
808/4: c.det1
808/5: c.base_points()
808/6: c.base_points
808/7: c.base_points[:,1]
808/8: %run swics_collimator.py
808/9: pylab.close('all')
808/10: c = collimator()
808/11: c.
808/12: c._calc_points()
808/13: c.plot()
808/14: %run swics_collimator.py
808/15: pylab.close('all')
808/16: c._calc_points()
808/17: c.plot()
808/18: c.det1
808/19: c._calc_points()
808/20: c.det1
808/21: %run swics_collimator.py
808/22: pylab.close('all')
808/23: c._calc_points()
808/24: c.det1
809/1: %run swics_collimator.py
809/2: c = collimator()
809/3: c._calc_points()
809/4: c.plot()
810/1: %run swics_collimator.py
810/2: c = collimator()
810/3: c.plot()
810/4: c._rot_aspang()
810/5: c.plot()
811/1: %run swics_collimator.py
811/2: c = collimator()
811/3: c.plot()
811/4: c = collimator(aspphi=10.)
811/5: c.plot()
811/6: pylab.close('all')
811/7: %run swics_collimator.py
811/8: c = collimator(aspphi=10.)
811/9: cc = collimator()
811/10: c.plot()
811/11: cc.plot()
811/12: cc.plot()
811/13: c.plot()
811/14: c = collimator(aspphi=80.)
811/15: cc.plot()
811/16: c.plot()
812/1: %run swics_collimator.py
812/2: c = collimator(aspphi=80.)
812/3: c = collimator()
812/4: c.plot()
812/5: c.rax
812/6: cross(self.rax,cross(array([1.,0.,0.]),self.rax))
812/7: cross(c.rax,cross(array([1.,0.,0.]),c.rax))
812/8: arccos(dot(c.spax,c.rzax))/pi*180.
812/9: %run swics_collimator.py
812/10: c = collimator()
812/11: c.rzax
812/12: arccos(dot(c.spax,c.rzax))/pi*180.
812/13: %run swics_collimator.py
812/14: c = collimator(aspphi=10.)
812/15: c.plot()
812/16: %run swics_collimator.py
812/17: c = collimator(aspphi=10.)
812/18: c.plot()
812/19: %run swics_collimator.py
812/20: c = collimator(aspphi=10.)
812/21: c = collimator(aspphi=0.001)
812/22: c.plot()
812/23: c.spang
812/24: c = collimator(aspphi=10)
812/25: c.spang
812/26: c = collimator(aspphi=10.,asptheta=10.)
812/27: c.spang
812/28: c = collimator(aspphi=109.,asptheta=10.)
812/29: c.spang
812/30: c = collimator(0.1)
812/31: c.spang
812/32: c = collimator(aspphi=.01,asptheta=.01)
812/33: c.spang
812/34: c = collimator()
812/35: c.spang
812/36: c = collimator(aspphi=.00001,asptheta=.00001)
812/37: c.spang
812/38: pylab.close('all')
813/1: %run swics_collimator.py
813/2: c = collimator(aspphi=.00001,asptheta=.00001)
813/3: c.spang
813/4: %run swics_collimator.py
813/5: c = collimator(aspphi=.00001,asptheta=.00001)
813/6: c.plot()
813/7: cross(array[1.,0.,0.],c.rax)
813/8: cross(array([1.,0.,0.]),c.rax)
813/9: c.rax
813/10: c = collimator(aspphi=.00000001,asptheta=.000000001)
813/11: c.spang
813/12: cross(array([1.,0.,0.]),c.rax)
813/13: c.rax
813/14: c.spax
813/15: c.plot()
813/16: c = collimator(aspphi=1,asptheta=.000000001)
813/17: c.plot()
813/18: c.spang
813/19: c.plot()
813/20: c.spang
813/21: c
813/22: c.aspphi
813/23: c.asptheta
813/24: c = collimator(aspphi=.01,asptheta=.01)
813/25: c.spang
813/26: c = collimator(aspphi=20.,asptheta=.01)
813/27: c.spang
813/28: c = collimator(aspphi=20.,asptheta=1)
813/29: c.spang
813/30: c = collimator(aspphi=20.,asptheta=20.)
813/31: c.spang
814/1: %run swics_collimator.py
814/2: c = collimator(aspphi=0.1.,asptheta=0.1)
814/3: c = collimator(aspphi=0.1,asptheta=0.1)
814/4: c.plot()
815/1: %run swics_collimator.py
815/2: c = collimator(aspphi=0.1,asptheta=0.1)
815/3: c.plot()
815/4: c.spang
816/1: %run swics_collimator.py
816/2: c = collimator(aspphi=0.1,asptheta=0.1)
816/3: c = collimator(aspphi=0.01,asptheta=0.01)
816/4: c.spang
816/5: c.plot()
816/6: %run swics_collimator.py
816/7: c = collimator(aspphi=0.01,asptheta=0.01)
816/8: c.spang
816/9: c.plot()
816/10: %run swics_collimator.py
816/11: c = collimator(aspphi=0.01,asptheta=0.01)
816/12: c.span
816/13: c.spang
816/14: c.plot()
816/15: c.sec0ang
816/16: pylab.close('all')
816/17: %run swics_collimator.py
816/18: c = collimator(aspphi=0.01,asptheta=0.01)
816/19: c.spang
816/20: c.sec0ang
816/21: 660 - c.sec0ang
816/22: 360 - c.sec0ang
816/23: c.plot
816/24: c.plot()
816/25: c = collimator(aspphi=0.00000001,asptheta=0.000000001)
816/26: c.spang
816/27: c.plot()
816/28: %run swics_collimator.py
816/29: pylab.close('all')
816/30: c = collimator(aspphi=0.00000001,asptheta=0.000000001)
816/31: c.plot()
816/32: %run swics_collimator.py
816/33: pylab.close('all')
816/34: c = collimator(aspphi=0.00000001,asptheta=0.000000001)
816/35: c.plot()
816/36: c.sec0ang
816/37: c.spax2
816/38: %run swics_collimator.py
816/39: c = collimator(aspphi=0.00000001,asptheta=0.000000001)
816/40: pylab.close('all')
816/41: c.plot()
816/42: %run swics_collimator.py
816/43: pylab.close('all')
816/44: c = collimator(aspphi=0.00000001,asptheta=0.000000001)
816/45: c.plot()
816/46: %run swics_collimator.py
816/47: pylab.close('all')
816/48: c = collimator(aspphi=0.00000001,asptheta=0.000000001)
816/49: c.plot()
816/50: c.sec0ang
816/51: c = collimator(aspphi=0.00000001,asptheta=20.)
816/52: c.plot()
816/53: c = collimator(aspphi=1.,asptheta=20.)
816/54: c.spang
816/55: c.sec0ang
816/56: c.plot()
819/1: %run swics_collimator.py
819/2: c = collimator(aspphi=0.00001,asptheta=0.00001)
819/3: c.plot()
819/4: %run swics_collimator.py
819/5: c = collimator(aspphi=0.00001,asptheta=0.00001)
819/6: c.plot()
819/7: c.plot()
819/8: c = collimator(aspphi=2.00001,asptheta=0.00001)
819/9: c = collimator(aspphi=2.00001,asptheta=2.00001)
819/10: c = collimator(aspphi=20.00001,asptheta=2.00001)
819/11: pylab.close('all')
819/12: %run swics_collimator.py
819/13: c = collimator(aspphi=2.00001,asptheta=2.00001)
819/14: c.plot()
819/15: c = collimator(aspphi=10.,asptheta=10.0)
819/16: c.plot()
819/17: c = collimator(aspphi=10.,asptheta=40.0)
819/18: c.plot()
819/19: pylab.close('all')
819/20: %run swics_collimator.py
819/21: c = collimator(aspphi=10.,asptheta=40.0)
819/22: c = collimator(aspphi=0.0001,asptheta=0.00001)
819/23: c.plot_rot()
819/24: 22.5*3
819/25: 22.5*2
819/26: zeros((3,8,4))
819/27: %run swics_collimator.py
819/28: pylab.close('all')
819/29: c = collimator(aspphi=0.0001,asptheta=0.00001)
819/30: c.plot_detsec()
819/31: c.plot()
819/32: c.plot_detsec(det=0.,sec=0.)
819/33: c.plot_detsec(det=0,sec=0)
819/34: c.plot_detsec(det=[0,1,2],sec=0)
819/35: c.plot_detsec(det=[1],sec=0)
819/36: c.plot_detsec(det=1,sec=0)
819/37: c.FoV
819/38: max(c.FoV)
819/39: numpy.max(c.FoV)
819/40: numpy.min(c.FoV)
819/41: c.vspace
819/42: shape(c.vspace)
819/43: c = collimator(aspphi=0.0001,asptheta=0.00001,calc_full=False)
819/44: c.plot()
819/45: c.plot_detsec(det=1,sec=0)
819/46: c.FoV
819/47: shape(c.FoV)
819/48: c.vspace
819/49: c.vspace[0,0,:,:]
819/50: c.FoV[0,0,:,:]
819/51: c.FoV[0,0,:,:]-c.FoV[0,0,:,:]*c.vel
819/52: c.plot_detsec(det=0,sec=0)
819/53: FoV = c.FoV[0,0,:,:]
819/54: np.linalg.norm(FoV)
819/55: np.linalg.norm(c.FoV[0,0,:,:]-c.FoV[0,0,:,:]*c.vel)
819/56: FoV2 = -c.FoV[0,0,:,:]*c.vel
819/57: vsp = -c.FoV[0,0,:,:]*c.vel
819/58: vsp
819/59: -c.FoV[2,0,:,:]*c.vel
819/60: np.linalg.norm(vsp)
819/61: np.linalg.norm(c.vspace[0,0,:,:])
819/62: FoV
819/63: vsp
819/64: c.vspace[0,0,:,:]
819/65: x = -52
819/66: x-=30
819/67: x
819/68: c.mv
819/69: shape(c.mv)
819/70: a = c.plot_detsec(0,0)
819/71: c.plot_detsec(1,0)
819/72: a.c.plot_detsec(1,0)
819/73: c.plot_detsec(1,0,ax=a)
819/74: pylab.close('all')
819/75: a = c.plot_detsec(0,0)
819/76: c.plot_detsec(1,0,ax=a)
819/77: c.plot_detsec(2,0,ax=a)
819/78: %run swics_collimator.py
819/79: pylab.close('all')
819/80: c = collimator(aspphi=0.0001,asptheta=0.00001)
819/81: a = c.plot_detsec(0,0)
819/82: c.FoV[0,0,0,:]
819/83: c.plot_detsec(1,0,ax=a)
819/84: c.plot_detsec(2,0,ax=a)
819/85: c.plot_detsec(0,1,ax=a)
819/86: c.plot_detsec(0,2,ax=a)
819/87: c.plot_detsec(0,3,ax=a)
819/88: c.plot_detsec(0,4,ax=a)
819/89: c.plot_detsec(0,5,ax=a)
819/90: b = c.plot_vsed(0,0)
819/91: b = c.plot_vseg(0,0)
819/92: c.vspace
819/93: shape(c.vspace)
819/94: c = collimator(aspphi=0.0001,asptheta=0.00001,calc_full=False)
819/95: shape(c.vspace)
819/96: c.vspace[0,0,:,:]
819/97: c.wswspace
819/98: c._calc_w()
819/99: c.wswspace
819/100: c.vsw
819/101: c.FoV
819/102: c.FoV[0,0,;,;]
819/103: c.FoV[0,0,:,:]
819/104: c.FoV[2,0,:,:]
819/105: -c.FoV{0,0,:,:]*c.vel
819/106: -c.FoV[0,0,:,:]*c.vel
819/107: -c.FoV[2,0,:,:]*c.vel
819/108: pylab.close('all')
819/109: c.plot_FoV()
819/110: c.plot_vspace()
819/111: c = collimator(aspphi=0.0001,asptheta=0.00001,calc_full=True)
819/112: c.plot_vspace()
820/1: %run swics_collimator.py
820/2: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/3: c.spax
820/4: c = collimator(aspphi=0.000,asptheta=0.0000,calc_full=False)
820/5: c.spax
820/6: c = collimator(aspphi=1.000,asptheta=0.0000,calc_full=False)
820/7: c.spax
820/8: c.rax
820/9: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/10: c.rax
820/11: c = collimator(aspphi=4.0001,asptheta=0.0000,calc_full=False)
820/12: c.rax
820/13: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/14: c.rzax
820/15: c.rax
820/16: c.spax
820/17: c.spang
820/18: c = collimator(aspphi=2.0001,asptheta=0.0000,calc_full=False)
820/19: c.spang
820/20: c = collimator(aspphi=20.0001,asptheta=0.0000,calc_full=False)
820/21: c.spang
820/22: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/23: c.sec0ang
820/24: %run swics_collimator.py
820/25: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/26: c.det1
820/27: c.det1:old
820/28: c.det1_old
820/29: c.plot()
820/30: %run swics_collimator.py
820/31: pylab.close('all')
820/32: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/33: c.plot()
820/34: c.det1_old
820/35: %run swics_collimator.py
820/36: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/37: c.plot()
820/38: %run swics_collimator.py
820/39: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/40: c.plot()
820/41: %run swics_collimator.py
820/42: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
820/43: c.plot()
820/44: c.sec0ang
820/45: c.plot_rot()
821/1: %run swics_collimator.py
821/2: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
821/3: c.FoV
821/4: %run swics_collimator.py
821/5: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
821/6: c.plot()
821/7: sec = 0
821/8: c.FoV[0,sec,0,0]
821/9: c.det3[0,;]
821/10: c.det3[0,:]
821/11: %run swics_collimator.py
821/12: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
821/13: c.plot()
821/14: array([self.FoV[0,sec,0,0]]),array([self.FoV[0,sec,1,0]]),array([self.FoV[0,sec,2,0]])
821/15: pylab.close('all')
821/16: array([c.FoV[0,0,0,0]])
821/17: array([c.FoV[0,0,1,0]])
821/18: array([c.FoV[0,0,2,0]])
821/19: %run swics_collimator.py
821/20: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
821/21: c.plot()
822/1: %run swics_collimator.py
822/2: %run swics_collimator.py
822/3: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
822/4: c.det1
822/5: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
822/6: c.and:para
822/7: c.ang_para
822/8: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
822/9: c.spang
822/10: %run swics_collimator.py
822/11: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
822/12: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
822/13: c.spang
822/14: c = collimator(aspphi=0.0001,asptheta=1.0000,calc_full=True)
822/15: c.spang
822/16: c = collimator(aspphi=0.0001,asptheta=1.0000,calc_full=True)
822/17: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
822/18: c.sec0ang
822/19: c = collimator(aspphi=0.50001,asptheta=0.0000,calc_full=True)
822/20: c.spang
822/21: c.sec0ang
822/22: %run swics_collimator.py
822/23: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
822/24: c.plot()
822/25: %run swics_collimator.py
822/26: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
822/27: c.plot()
822/28: %run swics_collimator.py
822/29: pylab.close('all')
822/30: c.plot()
822/31: %run swics_collimator.py
822/32: pylab.close('all')
822/33: c.plot()
822/34: %run swics_collimator.py
822/35: pylab.close('all')
822/36: c.plot()
823/1: %run swics_collimator.py
823/2: c.plot()
823/3: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
823/4: c.plot()
823/5: %run swics_collimator.py
823/6: c.plot()
824/1: %run swics_collimator.py
824/2: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
824/3: c.plot()
825/1: %run swics_collimator.py
825/2: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
825/3: c.plot()
826/1: %run swics_collimator.py
826/2: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
826/3: c.plot()
827/1: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
827/2: %run swics_collimator.py
827/3: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
827/4: c.plot()
828/1: %run swics_collimator.py
828/2: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
828/3: c.plot()
828/4: %run swics_collimator.py
828/5: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=True)
828/6: c.plot()
829/1: c = collimator(aspphi=10.0,asptheta=0.0000,calc_full=True)
829/2: %run swics_collimator.py
829/3: c = collimator(aspphi=10.0,asptheta=0.0000,calc_full=True)
829/4: c.plot()
829/5: c = collimator(aspphi=10.0,asptheta=20.0000,calc_full=True)
829/6: c.plot()
829/7: %run swics_collimator.py
829/8: pylab.close('all')
829/9: c = collimator(aspphi=10.0,asptheta=0.0000,calc_full=True)
829/10: c.plot()
829/11: c.aspphi
829/12: c.sec0ang
829/13: c = collimator(aspphi=0.0,asptheta=10.0000,calc_full=True)
829/14: c.plot()
829/15: c.sec0ang
829/16: c.spang
829/17: pylab.close('all')
829/18: range(0,45,3)
829/19: c.plot()
829/20: c.det1
829/21: len(c.det1)
829/22: shape(c.det1)
829/23: c.ang_perp
829/24: c.ang_para
829/25: len(c.ang_perp) * len(c.ang_para)
829/26: 455*3
829/27: 455/3
830/1: %run swics_collimator.py
830/2: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
830/3: c.FoV
830/4: zeros(2,3,4)
830/5: zeros((2,3,4))
830/6: zeros((2,3,4,5))
830/7: shape(c.FoV)
830/8: 2250/150.
830/9: c.det1
830/10: shape(c.det1)
831/1: range(0,45,3)
831/2: %run swics_collimator.py
831/3: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
831/4: c.FoV
831/5: shape(c.FoV)
831/6: shape(c.det1)
831/7: 90*5/3.
831/8: c.plot()
831/9: c.FoV(0,0,:,0)
831/10: c.FoV[0,0,:,0]
831/11: %run swics_collimator.py
831/12: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
831/13: c.FoV[0,0,:,0]
831/14: c.vspace[0,0,:,0]
831/15: %run swics_collimator.py
831/16: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
831/17: c.plot()
831/18: pylab.close('all')
831/19: %run swics_collimator.py
831/20: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
831/21: c.plot()
831/22: shape(c.det1)
831/23: %run swics_collimator.py
831/24: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
831/25: c.plot()
831/26: c.det1[0,:]
831/27: %run swics_collimator.py
831/28: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
831/29: c.plot()
831/30: %run swics_collimator.py
831/31: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
831/32: pylab.close('all')
831/33: c.plot()
831/34: c.vspace[0,0,0,0]
831/35: c.vspace[0,0,1,0]
831/36: c.vspace[0,0,2,0]
831/37: c.vspace[0,0,:,0]
831/38: c.vspace[1,0,:,0]
831/39: c.vspace[2,0,:,0]
831/40: %run swics_collimator.py
831/41: pylab.close('all')
831/42: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
831/43: c.plot()
831/44: c.FoV[0,0,:,0]
831/45: c.vspace[0,0,:,0]
831/46: c.FoV[0,0,1,0]
831/47: c.FoV[0,0,1,0] - c.FoV[0,0,0,0]
831/48: c.vspace[0,0,1,0] - c.vspace[0,0,0,0]
831/49: c.FoV[0,0,1,0] - c.FoV[0,0,0,0]
831/50: c.plot_detsec
831/51: c.plot_detsec()
831/52: c.plot_detsec(0,0)
831/53: c.plot_detsec(1,0)
831/54: c.plot_detsec(2,0)
831/55: c.plot_FoV()
833/1: %run swics_collimator.py
833/2: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
833/3: c.plot_detsec(2,0)
833/4: c.plot_detsec(:,0)
833/5: c.plot_detsec([0,1,2],0)
833/6: c.plot_detsec(0,0)
833/7: axx = c.plot(detsec(0,0))
833/8: axx = c.plot_detsec(0,0))
833/9: axx = c.plot_detsec(0,0)
833/10: axx = c.plot_detsec(0,0,ax=axx)
833/11: axx = c.plot_detsec(1,0,ax=axx)
833/12: axx = c.plot_detsec(2,0,ax=axx)
833/13: shape(c.FoV[0,0,:,:])
833/14: 2250/5
833/15: 2250/5.
833/16: /30
833/17: 450./30.
833/18: a = [1,2,3,4]
833/19: b = zeros(4,4,4)
833/20: b = zeros((4,4,4))
833/21: b
833/22:
for i in range(4):
    for j in range(4):
        b[i,:,j] = a*i*j
833/23: a*3*4
833/24: a
833/25: a *3
833/26: type(a)
833/27: a = array(a)
833/28: a
833/29: a*4
833/30:
for i in range(4):
    for j in range(4):
        b[i,:,j] = a*i*j
833/31: b
833/32:
for i in range(1,5):
    for j in range(1,5):
        b[i,:,j] = a*i*j
833/33: range(1,5)
833/34:
for i in range(4):
    for j in range(4):
        b[i,:,j] = a*(i+1)*(j+1)
833/35: b
833/36: sum(a,axis=0)
833/37: sum(a,axis=1)
833/38: sum(b,axis=0)
833/39: b
833/40: sum(b,axis=1)
833/41: c = zeros(3,3)
833/42: c = zeros((2,2))
833/43: c
833/44: c = zeros((3,3))
833/45: c
833/46: c[0,0] = 0.1
833/47: c[0,2] = 0.5
833/48: c[2,2] = 1
833/49: c[1,2] = 5
833/50: c[1,1] = 10
833/51: c
833/52: c[1,0] = 50
833/53: c[2,0] = 20
833/54: c[0,1] = 2
833/55: c
833/56: c[2,1] = 100
833/57: c
833/58: sum(c,axis=0.)
833/59: sum(c,axis=0)
833/60: c
833/61: sum(c,axis=1)
833/62: c = zeros((2,2,2))
833/63: c[0,0,0] = 0.1
833/64: c[1,0,0] = 10
833/65: c[1,1,0] = 50
833/66: c[0,1,0] = 2
833/67: c[0,1,1] = 20
833/68: c[1,1,1] = 0.2
833/69: c
833/70: c[0,1,1] = 100
833/71: c[0,1,0] = 200
833/72: c
833/73: c[0,1,0]
833/74: c[0,1,0] = 0.02
833/75: c
833/76: c[0,1,1] = 0.01
833/77: c
833/78: c[0,1,1] = 2.5
833/79: c[0,1,0] = 25.5
833/80: c
833/81: c[0,0,1] = 5
833/82: c[1,0,1] = 1
833/83: c
833/84: sum(c,axis=1)
833/85: sum(c,axis=0)
833/86: c.append([[2.2,3.3],[22,33]])
833/87: c[2,:,:]=array([2.2,3.3],[22,33])
833/88: c[2,:,:]=array([[2.2,3.3],[22,33]])
833/89: d = zeros(3,2,2)
833/90: d = zeros((3,2,2))
833/91: d
833/92: d[0:1,:,:] = c
833/93: d[0:2,:,:] = c
833/94: d
833/95: d[2,0,0] = 3.3
833/96: d[2,1,0] = 33
833/97: d[2,1,1] = 44
833/98: d[2,0,1] = 4.4
833/99: d
833/100: sum(c,axis=0.)
833/101: sum(c,axis=0)
833/102: c
833/103: d
833/104: sum(d,axis=0)
833/105: sum(d,axis=1)
833/106: sum(d,axis=2)
833/107: c.plot_vspace()
833/108: c = zeros((2,2,2))
834/1: %run swics_collimator.py
834/2: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
834/3: c.plot_vspace()
834/4: c.plot_FoV()
834/5: %run swics_collimator.py
834/6: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
834/7: c.plot_FoV()
834/8: %run swics_collimator.py
834/9: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
834/10: c.plot_FoV()
835/1: %run swics_collimator.py
835/2: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
835/3: c.plot()
837/1: %run swics_collimator.py
837/2: %run swics_collimator.py
837/3: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
837/4: c.plot()
839/1: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
839/2: %run swics_collimator.py
839/3: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
839/4: c.plot_vspace()
839/5: %run swics_collimator.py
839/6: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
839/7: c.plot_vspace()
839/8: %run swics_collimator.py
839/9: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
839/10: c.plot_vspace()
839/11: %run swics_collimator.py
839/12: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
839/13: c.plot_vspace()
839/14: axx = c.plot_vspace()
839/15: c2 = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True,vel=500.)
839/16: c2.plot_vspace(ax=axx)
839/17: c3 = collimator(aspphi=0.0,asptheta=5.00001,calc_full=True,vel=500.)
839/18: c3.plot_vspace(ax=axx)
840/1: %run swics_collimator.py
840/2: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
840/3: c.plot()
840/4: %run swics_collimator.py
840/5: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
840/6: c.plot()
840/7: %run swics_collimator.py
840/8: c = collimator(aspphi=0.0,asptheta=0.00001,calc_full=True)
840/9: c.plot()
840/10: c = collimator(aspphi=1.0,asptheta=0.0000,calc_full=True)
840/11: c.plot()
840/12: c = collimator(aspphi=5.0,asptheta=0.0000,calc_full=True)
840/13: c.plot()
840/14: c = collimator(aspphi=-5.0,asptheta=0.0000,calc_full=True)
840/15: c.plot()
840/16: c.spang
840/17: c = collimator(aspphi=5.0,asptheta=0.0000,calc_full=True)
840/18: c.spang
840/19: c.plot()
840/20: cm = collimator(aspphi=-5.0,asptheta=0.0000,calc_full=True)
840/21: c.plot()
840/22: pylab.close('all')
840/23: cm.plot()
840/24: cm.spang
840/25: cm.aspphi
840/26: c
840/27: c.vspace
840/28: shape(c.vspace)
840/29: c.vspace[0,0,:,0]
840/30: c.FoV[0,0,:,0]
840/31: F = zeros((3,2))
840/32: F
840/33: Ff = zeros((3,2,1))
840/34: Ff
840/35: Ff[0,;0] = array([2,0])
840/36: Ff[0,:,0] = array([2,0])
840/37: Ff[1,:,0] = array([1,1])
840/38: Ff[2,:,0] = array([1,-1])
840/39: Ff
840/40: Fv = -Ff * 6
840/41: Fv
840/42: c
840/43: c.plot_vspace()
840/44: c = collimator(aspphi=5.0,asptheta=0.0000,calc_full=False)
840/45: c.plot_vspace()
840/46: c.vspace
840/47: shape(c.vsapce)
840/48: shape(c.vspace)
840/49: mean(c.vspace[0,0,:,0])
840/50: mean(c.vspace[1,0,:,0])
840/51: mean(c.vspace[2,0,:,0])
841/1: %run dist3D.py
842/1: %run dist3d
842/2: %run dist3D.py
842/3: cd
843/1: %run dist3D.py
844/1: $run dist3D.py
844/2: %run dist3D.py
845/1: %run dist3D.py
846/1: from swics_collimator import collimator
846/2: sys.path
846/3: sys.path.insert(0, '/home/asterix/fischer/ulysses')
846/4: sys.path
846/5: from libacepy.ancil import getvelocity_allsteps
846/6: sys.path.insert(0, '/home/asterix/fischer/ulysses/')
846/7: sys.path
846/8: from libacepy.ancil import getvelocity_allsteps
846/9: sys.path.insert(0, '/home/asterix/fischer/ulysses/swics/swics_allg/trunk/')
846/10: from libacepy.ancil import getvelocity_allsteps
846/11: sys.path.insert(0, '/home/asterix/fischer/ulysses/swics/swics_allg/trunk/ionpositions/libacepy/')
846/12: from libacepy.ancil import getvelocity_allsteps
847/1: from libacepy.ancil import getvelocity_allsteps
847/2: import sys
847/3: from libacepy.ancil import getvelocity_allsteps
847/4: sys.path
848/1: sys.path
848/2: sys.path.insert(0, '/home/asterix/fischer/ulysses/swics/swics_allg/trunk/ionpositions/libacepy/')
848/3: sys.path
848/4: from libacepy.ancil import getvelocity_allsteps
848/5: sys.path.append('/home/asterix/fischer/ulysses/swics/swics_allg/trunk/ionpositions/libacepy/')
848/6: sys.path
848/7: from libacepy.ancil import getvelocity_allsteps
849/1: sys.path
850/1: from libacepy.ancil import getvelocity_allsteps
851/1: from libacepy.ancil import getvelocity_allsteps
852/1: sys.path.append('/home/asterix/fischer/ulysses/swics/swics_allg/trunk/ionpositions/')
852/2: from libacepy.ancil import getvelocity_allsteps
853/1: from libacepy.ancil import getvelocity_allsteps
854/1: sys.path
854/2: from libacepy.ancil import getvelocity_allsteps
855/1: from libacepy.ancil import getvelocity_allsteps
855/2: sys.path
855/3: sys.path.append('/home/asterix/fischer/ulysses/swics/swics_allg/trunk/ionpositions/')
855/4: from libacepy.ancil import getvelocity_allsteps
856/1: sys.path.append('/home/asterix/fischer/ulysses/swics/swics_allg/trunk/')
856/2: from libacepy.ancil import getvelocity_allsteps
856/3: from swics_collimator import collimator
857/1: from swics_collimator import collimator
858/1: from swics_collimator import collimator
859/1: %run dist3D.py
860/1: from libacepy.ancil import getvelocity_allsteps
860/2: %run dist3D.py
861/1: sys.path.append('../ionpositions')
861/2: from libacepy.ancil import getvelocity_allsteps
861/3: from libacepy.ace_utils import *
862/1: %run dist3D.py
863/1: from swics_collimator import collimator
864/1: from swics_collimator import collimator
865/1: from swics_collimator import collimator
865/2: env
865/3: . ~/.bashrc
865/4: source ~/.bashrc
865/5: exec bash
866/1: from swics_collimator import collimator
867/1: %run dist3D.py
868/1: from swics import test
869/1: from swics import test
869/2: test()
869/3: test
869/4: test.test
869/5: test.test)(
869/6: test.test()
869/7: from swics import test.test
869/8: from swics.test import test
869/9: test()
870/1: import test
870/2: test()
871/1: import test
871/2: test()
871/3: test.test()
871/4: test
873/1: from test1.test2 import test
873/2: test()
874/1: from test1.test2 import test
875/1: import test
875/2: test()
875/3: test.
875/4: test
875/5: import test1 import test
875/6: import test2 import test
875/7: from test2 import test
875/8: from test1 import test
875/9: test()
876/1: import libacepy
876/2: from swics import libacepy
876/3: libacepy.ancil
877/1: from libacepy.ancil import *
878/1: %run dist3D.py
879/1: from libacepy.ancil import *
880/1: from libacepy.ancil import *
881/1: %run dist3D.py
882/1: %run dist3D.py
883/1: from libulpy import uswipha
884/1: from libulpy import uswipha
884/2: d = uswipha(year=[1992,1995],tf=[[1,150]])
884/3: %run uswipha
884/4: %run uswipha.py
885/1: %run uswipha.py
885/2: d = uswipha(year=[1992,1995],tf=[[1,150]])
885/3: cd ../..
885/4: cd ..
885/5: cd ..
885/6: import dist3D
885/7: cd swics/trunk/ace_dbd/
885/8: %run dist3D.py
885/9: d3 = dist3D(d)
885/10: d3 = Dist3D(d)
885/11: d.sync_swoops()
886/1: pwd
886/2: d = uswipha(year=[1992,1993],tf=[[1,150]])
886/3: import uswipa
886/4: import uswipha
886/5: import uswipha
886/6: d = uswipha(year=[1992,1993],tf=[[1,150]])
886/7: from uswipha import uswipha
886/8: d = uswipha(year=[1992,1993],tf=[[1,150]])
886/9: d.sync_swoops()
886/10: d.sync_traj()
886/11: cd ..
886/12: cd ..
886/13: cd ..
886/14: ös
886/15: ls
886/16: cd ..
886/17: cd swics/trunk/ace_dbd/
886/18: ls
886/19: %run dist3D.py
886/20: d3 = Dist3D(d)
886/21: d.data
887/1: %run swics_collimator.py
887/2: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
887/3: c.plot()
887/4: %run swics_collimator.py
887/5: c.plot()
887/6: %run swics_collimator.py
887/7: %run swics_collimator.py
887/8: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
887/9: c.plot()
887/10: %run swics_collimator.py
887/11: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
887/12: c.plot()
887/13: %run swics_collimator.py
887/14: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
887/15: c.plot()
887/16: %run swics_collimator.py
887/17: c.plot()
888/1: %run swics_collimator.py
888/2: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/3: c.plot()
888/4: %run swics_collimator.py
888/5: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/6: c.plot()
888/7: %run swics_collimator.py
888/8: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/9: c.plot()
888/10: pylab.close('all')
888/11: %run swics_collimator.py
888/12: pylab.close('all')
888/13: c.plot()
888/14: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/15: c.plot()
888/16: c.plot()
888/17: pylab.close('all')
888/18: %run swics_collimator.py
888/19: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/20: c.plot()
888/21: %run swics_collimator.py
888/22: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/23: c.plot()
888/24: %run swics_collimator.py
888/25: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/26: c.plot()
888/27: %run swics_collimator.py
888/28: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/29: c.plot()
888/30: %run swics_collimator.py
888/31: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/32: c.plot()
888/33: %run swics_collimator.py
888/34: pylab.close('all')
888/35: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/36: c.plot()
888/37: %run swics_collimator.py
888/38: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/39: c.plot()
888/40: %run swics_collimator.py
888/41: pylab.close('all')
888/42: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/43: c.plot()
888/44: %run swics_collimator.py
888/45: c = collimator(aspphi=0.0001,asptheta=0.0000,calc_full=False)
888/46: c.plot()
888/47: c = collimator(aspphi=2.0001,asptheta=0.0000,calc_full=False)
888/48: c.plot()
888/49: c = collimator(aspphi=6.0001,asptheta=0.0000,calc_full=False)
888/50: c.plot()
888/51: c = collimator(aspphi=6.0001,asptheta=12.0000,calc_full=False)
888/52: c.plot()
888/53: c = collimator(aspphi=6.0001,asptheta=-12.0000,calc_full=False)
888/54: pylab.close('all')
888/55: c.plot()
888/56: %run swics_collimator.py
888/57: c = collimator(aspphi=6.0001,asptheta=-12.0000,calc_full=False)
888/58: c.plot()
888/59: %run swics_collimator.py
888/60: c = collimator(aspphi=6.0001,asptheta=-12.0000,calc_full=False)
888/61: c.plot()
888/62: c = collimator(aspphi=6.0001,asptheta=-22.0000,calc_full=False)
888/63: c.plot()
888/64: c = collimator(aspphi=16.0001,asptheta=-22.0000,calc_full=False)
888/65: c.plot()
888/66: pylab.close('all')
888/67: c.plot()
889/1: %run swics_collimator.py
889/2: c = collimator(aspphi=16.0001,asptheta=-22.0000,calc_full=False)
889/3: c.plot()
890/1: fu = open('ulysses_daily_heliocentric_data_1990-2009.txt','r')
890/2: fu.readline()
890/3: fu.readline()
890/4: fu.readline()
890/5: fu.readline()
890/6: fu.readline()
890/7: fu.readline()
890/8: fh = open("helio.dat","r")
890/9: rh.readline()
890/10: fh.readline()
890/11: fh.readline()
890/12: fh.readline()
890/13: fh.readline()
890/14: fh.readline()
890/15: fh.readline()
890/16: fh.readline()
890/17: len(fh)
890/18: type(fh)
890/19: size(fh)
890/20: import numpy as np
890/21: RA_h = np.array[[]]
890/22: RA_h = np.array([])
890/23: RA_u = np.array([])
890/24:
for line in fh:
    l = fh.readline.split[' ']
    RA_h.append(l[10])
890/25:
for line in fh:
    l = fh.readline().split[' ']
    RA_h.append(l[10])
890/26:
for line in fh:
    l = line.split[' ']
    RA_h.append(l[10])
890/27:
for line in fh:
    l = line.split[' ']
    print(l)
890/28:
for line in fh:
    l = line.split()
    print(l)
890/29: fh.readline()
890/30: fh = open("helio.dat","r")
890/31: fh.readline()
890/32: fh.readline()
890/33: fh.readline()
890/34: fh.readline()
890/35: fh.readline()
890/36: fh.readline()
890/37: fh.readline()
890/38: fu.readline()
890/39: fu.readline()
890/40: fu.readline(10)
890/41: fu.readline()
890/42: fu.readline()
890/43: fu.readline()
890/44: fu.readline()
890/45: fu.readline()
890/46: fu.readline()
890/47: fu.readline()
890/48: fu.readline()
890/49: fu.readline()
890/50: fu.readline()
890/51: fu.readline()
890/52: fu.readline()
890/53: fu.readline()
890/54: fu.readline()
890/55: fu.readline()
890/56: fu.readline()
890/57: fh.readline()
890/58: fu.readline()
890/59: dir
890/60:
for line in fh:
    l = line.split()
    RA_h.append(l[10])
890/61: RA_h = []
890/62: RA_u = []
890/63:
for line in fh:
    l = line.split()
    RA_h.append(l[10])
890/64: RA_h
890/65:
for line in fu:
    l = line.split()
    RA_u.append(l[17])
890/66: RA_u[0]
890/67: RA_h[0]
890/68: RA_h[20]
890/69: RA_h[20]
890/70: RA_u[20]
890/71: RA_u[15]
890/72: RA_h[15]
890/73: RA_h=RA_h[1:]
890/74: RA_h[15]
890/75: RA_u=RA_u[2:]
890/76: RA_u[15]
890/77: RA_u[20]
890/78: RA_h[20]
890/79: len(RA_h)_
890/80: len(RA_h)
890/81: len(RA_u)
890/82:
for i in range(50):
    print('%i - %i = %i'%(RA_h[i],RA_u[i],RA_h[i]-RA_u[i]))
890/83: type(RA_h[0])
890/84:
for i in RA_h:
    i = int(i)
890/85:
for i in RA_h:
    i = float(i)
890/86:
for i in RA_u:
    i = float(i)
890/87: Rh = np.array(RA_h)
890/88: Ru = np.array(RA_u)
890/89:
for i in range(100):
    print('%f - %f = %f'%(Rh[i],Ru[i],Rh[i]-Ru[i]))
890/90: Ru[0]
890/91:
for i in Ru:
    i = float(i)
890/92: Ru[0]
890/93:
for i in range(len(Ru)):
    Ru[i]=float(RU[i])
890/94:
for i in range(len(Ru)):
    Ru[i]=float(Ru[i])
890/95: Ru[0]
890/96: type(Ru[0])
890/97: Ru_new = []
890/98:
for i in range(len(RA_u)):
    Ru_new[i]=float(RA_u[i])
890/99:
for i in range(len(RA_u)):
    Ru_new[i].append(float(RA_u[i]))
890/100:
for i in range(len(RA_u)-1):
    Ru_new[i].append(float(RA_u[i]))
890/101: Ru_new = []
890/102:
for i in range(len(RA_u)):
    Ru_new.append(float(RA_u[i]))
890/103: Ru_new
890/104: Rh_new = []
890/105:
for i in range(len(RA_h)):
    Rh_new.append(float(RA_h[i]))
890/106: Rh = np.array(Rh_new)
890/107: Ru = np.array(Ru_new)
890/108: Rh
890/109:
for i in range(100):
    print('%f - %f = %f'%(Rh[i],Ru[i],Rh[i]-Ru[i]))
890/110:
for i in range(1000):
    print('%f - %f = %f'%(Rh[i],Ru[i],Rh[i]-Ru[i]))
890/111:
for i in range(4000):
    print('%f - %f = %f'%(Rh[i],Ru[i],Rh[i]-Ru[i]))
891/1: %run ulysses_traj.py
891/2: t = ulysses_traj(path='/home/skeletor/fischer/helio.dat')
891/3: t = ulysses_traj(path='/home/skeletor/fischer/helio.dat',tf='all')
891/4: t
891/5: size(t)
891/6: t.key
891/7: t.keys
891/8: %run ulysses_traj.py
891/9: t = ulysses_traj(path='/home/skeletor/fischer/helio.dat',tf='all')
891/10: t.keys
891/11: t[-999.]
891/12: t['-999.']
891/13: t
891/14: type(t)
891/15: t.data
891/16: t.data['-999.']
891/17: t.data('-999.')
891/18: t.get_data['95.11']
891/19: t.get_data('95.11')
891/20: t.data()
891/21: t.data
891/22: t = ulysses_traj(path='/home/skeletor/fischer/helio.dat',tf='all')
891/23: t.path
891/24: fin = open(t.path,'r')
891/25: fin.readline(6)
891/26: fin.readline()
891/27: fin.readline()
891/28: fin.readline()
891/29: fin.readline()
891/30: fin.readline()
891/31: fin.readline()
891/32: fin.readline()
891/33: fin.readline()
891/34:
for line in fin:
    l=line.split()
    print(l[12])
891/35:
for line in fin:
    l=line.split()
    print(l[11])
891/36: fin = open(t.path,'r')
891/37: fin.readline()
891/38: fin.readline()
891/39: fin.readline()
891/40: fin.readline()
891/41: fin.readline()
891/42: fin.readline()
891/43: fin.readline()
891/44: fin.readline()
891/45:
for line in fin:
    l=line.split()
    print('%s-%s=%s'%(l[9],l[11],l[9]-l[11]))
891/46:
for line in fin:
    l=line.split()
    print('%s-%s=%f'%(l[9],l[11],float(l[9])-float(l[11])))
891/47: fin = open(t.path,'r')
891/48: fin.readline()
891/49: fin.readline()
891/50: fin.readline()
891/51: fin.readline()
891/52: fin.readline()
891/53: fin.readline()
891/54: fin.readline()
891/55: a = []
891/56:
for line in fin:
    l=line.split()
    print('%s-%s=%f'%(l[9],l[11],float(l[9])-float(l[11])))
    a.append(float(l[9]-float(l[11])))
891/57:
for line in fin:
    l=line.split()
    print('%s-%s=%f'%(l[9],l[11],float(l[9])-float(l[11])))
    a.append(float(l[9])-float(l[11]))
891/58: a
891/59: aa = numpy.array(a)
891/60: aa.mean()
891/61: fin = open(t.path,'r')
891/62: fin.readline()
891/63: fin.readline()
891/64: fin.readline()
891/65: fin.readline()
891/66: fin.readline()
891/67: fin.readline()
891/68: fin.readline()
891/69: fin.readline()
891/70: fin.readline()
891/71:
for line in fin:
    l=line.split()
    print('%s-%s=%f'%(l[9],l[11],float(l[9])-float(l[11])))
    a.append(float(l[9])-float(l[11]))
892/1: %run ulysses_traj.py
892/2: t = ulysses_traj(tf='all')
892/3: t = ulysses_traj(tf='all')
893/1: %run ulysses_traj.py
893/2: t = ulysses_traj(tf='all')
893/3: t = ulysses_traj(path='/home/skeletor/fischer/helio.dat',tf='all')
893/4: t = ulysses_traj(path='/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt',tf='all')
893/5: d = uswipha(year=[1992,1993],tf=[[1,150]])
893/6: from uswipha import uswipha
893/7: d = uswipha(year=[1992,1993],tf=[[1,150]])
893/8: t = ulysses_traj(path='/home/skeletor/fischer/helio.dat',tf='all')
893/9: t = ulysses_traj(tf='all')
893/10: t = ulysses_traj(d)
893/11: d
893/12: d.sync_traj()
893/13: d.sync_swoops
893/14: d.sync_swoops()
893/15: %run ulysses_traj.py
893/16: from pylib import dbdata
893/17: from pylib import dbData
893/18: d.add_mask('Master')
893/19: d.sync_traj()
894/1: d = uswipha(year=[1992,1993],tf=[[1,15]])
894/2: from uswipha import uswipha
894/3: d = uswipha(year=[1992,1993],tf=[[1,15]])
894/4: d.sync_swoops()
894/5: d.sync_traj()
895/1: from uswipha import uswipha
895/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
895/3: d.sync_traj()
896/1: from uswipha import uswipha
896/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
896/3: d.sync_traj()
897/1: from uswipha import uswipha
898/1: from uswipha import uswipha
898/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
898/3: d.sync_traj()
899/1: from uswipha import uswipha
899/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
899/3: d.sync_swoops()
899/4: d.sync_traj()
899/5: d.sync_traj()
900/1: from uswipha import uswipha
901/1: from uswipha import uswipha
902/1: from uswipha import uswipha
902/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
902/3: d.sync_traj()
902/4: from uswipha import uswipha
902/5: d.sync_traj()
903/1: from uswipha import uswipha
903/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
903/3: d.sync_traj()
904/1: d = uswipha(year=[1992,1993],tf=[[1,15]])
904/2: from uswipha import uswipha
904/3: d = uswipha(year=[1992,1993],tf=[[1,15]])
904/4: d.sync_traj()
904/5: from uswipha import uswipha
904/6: d.sync_traj()
904/7: from uswipha import uswipha
904/8: d.sync_traj()
904/9: from uswipha import uswipha
904/10: d.sync_traj()
904/11: d.data
904/12: d.keys
904/13: d.keys()
904/14: d.data
904/15: from uswipha import uswipha
904/16: d.sync_traj()
904/17: d.data
904/18: from uswipha import uswipha
904/19: d.sync_traj()
904/20: d.sync_traj(tf='all')
904/21: clear
904/22: d.sync_traj()
904/23: d.sync_traj(tf='all')
904/24: from uswipha import uswipha
904/25: d.sync_traj()
904/26: d.sync_swoops()
904/27: from uswipha import uswipha
904/28: d.sync_swoops()
905/1: from uswipha import uswipha
905/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
905/3: d.sync_swoops()
905/4: d = uswipha(year=[1992,1993],tf=[[1,15]])
905/5: from uswipha import uswipha
905/6: d.sync_swoops()
905/7: d.sync_swoops()
905/8: from uswipha import uswipha
905/9: d.sync_swoops()
906/1: from uswipha import uswipha
906/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
906/3: d.sync_swoops()
906/4: d.sync_traj()
906/5: d.sync_swoops()
906/6: d = uswipha(year=[1992,1993],tf=[[1,15]])
906/7: d.sync_swoops()
906/8: from uswipha import uswipha
906/9: d = uswipha(year=[1992,1993],tf=[[1,15]])
906/10: d.sync_swoops()
906/11: d.sync_traj()
906/12: from uswipha import uswipha
906/13: d.sync_traj()
906/14: d = uswipha(year=[1992,1993],tf=[[1,15]])
906/15: d.sync_traj()
906/16: from uswipha import uswipha
906/17: d = uswipha(year=[1992,1993],tf=[[1,15]])
906/18: d.sync_traj()
906/19: d.sync_swoops()
906/20: from uswipha import uswipha
906/21: d.sync_traj()
907/1: from uswipha import uswipha
907/2: d.sync_swoops()
907/3: d = uswipha(year=[1992,1993],tf=[[1,15]])
907/4: d.sync_swoops()
908/1: from uswipha import uswipha
908/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
908/3: d.sync_swoops()
908/4: from uswipha import uswipha
908/5: d.sync_swoops()
908/6: from uswipha import uswipha
908/7: d.sync_swoops()
909/1: from uswipha import uswipha
909/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
909/3: d.sync_swoops()
910/1: d = uswipha(year=[1992,1993],tf=[[1,15]])
910/2: from uswipha import uswipha
910/3: d = uswipha(year=[1992,1993],tf=[[1,15]])
910/4: d.sync_swoops()
910/5: from uswipha import uswipha
910/6: d = uswipha(year=[1992,1993],tf=[[1,15]])
910/7: d.sync_swoops()
911/1: from uswipha import uswipha
911/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
911/3: d.sync_swoops()
912/1: from uswipha import uswipha
912/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
912/3: d.sync_swoops()
912/4: from pylib import dbData
912/5: d.sync_swoops()
912/6: from uswipha import uswipha
912/7: d.sync_swoops()
912/8: from uswipha import uswipha
912/9: d.sync_swoops()
913/1: from uswipha import uswipha
913/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
913/3: d.sync_swoops()
913/4: d.sync_traj()
913/5: sync_swoops(d)
913/6: d.sync_traj()
913/7: d.sync_swoops()
914/1: from uswipha import uswipha
914/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
914/3: d = uswipha(year=[1992,1993],tf=[[1,15]])
914/4: from uswipha import uswipha
914/5: d = uswipha(year=[1992,1993],tf=[[1,15]])
915/1: from uswipha import uswipha
915/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
915/3: d = uswipha(year=[1992,1993],tf=[[1,15]])
915/4: d.sync_swoops()
916/1: d.sync_swoops()
916/2: from uswipha import uswipha
916/3: d = uswipha(year=[1992,1993],tf=[[1,15]])
916/4: d.sync_swoops()
917/1: from uswipha import uswipha
917/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
917/3: d.sync_swoops()
917/4: d.sync_swoops()
917/5: d = uswipha(year=[1992,1993],tf=[[1,15]])
917/6: from uswipha import uswipha
917/7: d = uswipha(year=[1992,1993],tf=[[1,15]])
917/8: d.sync_swoops()
917/9: d.sync_traj()
917/10: from uswipha import uswipha
917/11: d.sync_traj()
917/12: d = uswipha(year=[1992,1993],tf=[[1,15]])
917/13: d.sync_traj()
917/14: d.sync_swoops()
917/15: d.sync_traj()
918/1: from uswipha import uswipha
918/2: d = uswipha(year=[1992,1993],tf=[[1,15]])
918/3: d.sync_traj()
918/4: d.sync_swoops()
918/5: d.sync_traj()
918/6: d = uswipha(year=[1992,1993],tf=[[1,15]])
918/7: from uswipha import uswipha
918/8: d = uswipha(year=[1992,1993],tf=[[1,15]])
918/9: d.sync_traj()
918/10: d.sync_swoops()
918/11: from uswipha import uswipha
918/12: d = uswipha(year=[1992,1993],tf=[[1,10]])
918/13: d.sync_swoops()
918/14: d.sync_traj()
918/15: from uswipha import uswipha
918/16: d = uswipha(year=[1992,1993],tf=[[1,10]])
918/17: d.sync_swoops()
918/18: d.data
919/1: from uswipha import uswipha
919/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
919/3: d.sync_swoops()
919/4: d.data
919/5: d.sync_swoops()
919/6: d.data
919/7: dd = uswipha(year=[1992,1993],tf=[[1,10]])
919/8: dd.data
919/9: from uswipha import uswipha
919/10: d = uswipha(year=[1992,1993],tf=[[1,10]])
919/11: d.sync_swoops()
920/1: from uswipha import uswipha
920/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
920/3: d.sync_swoops()
920/4: d.data
920/5: d = uswipha(year=[1992,1993],tf=[[1,10]])
920/6: d.sync_swoops()
920/7: d.data
921/1: from uswipha import uswipha
921/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
921/3: d.sync_swoops()
921/4: d.data
922/1: from uswipha import uswipha
922/2: d.sync_swoops()
922/3: d = uswipha(year=[1992,1993],tf=[[1,10]])
922/4: d.sync_swoops()
922/5: d.sync_traj()
922/6: d.sync_swoops()
923/1: from uswipha import uswipha
923/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
923/3: d.sync_traj()
924/1: from uswipha import uswipha
924/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
924/3: d.sync_traj()
924/4: d.sync_swoops()
924/5: d.sync_traj()
925/1: from uswipha import uswipha
925/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
925/3: d.sync_swoops()
926/1: from uswipha import uswipha
926/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
926/3: d.sync_swoops()
927/1: from uswipha import uswipha
927/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
927/3: d.sync_swoops()
927/4: d.sync_traj()
928/1: d.sync_traj()
928/2: from uswipha import uswipha
928/3: d = uswipha(year=[1992,1993],tf=[[1,10]])
928/4: d.sync_traj()
928/5: from ulysses_traj import ulysses_traj
928/6: d.sync_traj()
928/7: d = uswipha(year=[1992,1993],tf=[[1,10]])
928/8: d.sync_traj()
929/1: from uswipha import uswipha
929/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
929/3: d.sync_traj()
930/1: from uswipha import uswipha
930/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
930/3: d.sync_traj()
931/1: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
931/2: fid.readline()
931/3: print(fid.readline())
931/4: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
931/5:
for line in range(6):
    fid.readline()
931/6: s = fid.readline()
931/7: print(s)
931/8: k = s.split()
931/9: k
931/10: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
931/11: fid.readline()
931/12: fid.readline()
931/13: fid.readline()
931/14: fid.readline()
931/15: fid.readline()
931/16: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
931/17:
for line in range(5):
    fid.readline()
931/18: s = fid.readline()
931/19: k = s.split()
931/20: k
931/21: d
932/1: d = uswipha(year=[1992,1993],tf=[[1,10]])
932/2: from uswipha import uswipha
932/3: d = uswipha(year=[1992,1993],tf=[[1,10]])
932/4: d.sync_traj()
933/1: from uswipha import uswipha
934/1: from uswipha import uswipha
934/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
934/3: d.sync_swoops()
934/4: d.sync_traj()
935/1: from uswipha import uswipha
935/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
935/3: d.sync_traj()
936/1: from uswipha import uswipha
936/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
936/3: d.sync_traj()
936/4: d.data
936/5: traj.data
936/6: traj
936/7: t = ulysses_traj()
936/8: t = d.ulysses_traj()
936/9: from ulysses_traj import ulysses_traj
936/10: t = ulysses_traj()
936/11: t
936/12: t.data
937/1: from uswipha import uswipha
937/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
937/3: d.sync_traj()
937/4: d.ata
937/5: d.data
937/6: d.sync_swoops()
937/7: d.data
937/8: fid
937/9: fid = open('/home/skeletor/fischer/helio.dat','r')
937/10: fid.readline()
937/11: fid.readline()
937/12: fid.readline()
937/13: fid.readline()
937/14: fid.readline()
937/15: fid.readline()
937/16: fid.readline()
937/17: len(dif)
937/18: len(fid)
937/19: h = []
937/20:
for line in fid:
    h.append(line.split()[10])
937/21: h
937/22: h[0]
937/23: d.data
937/24: d = uswipha(year=[1992,1993],tf='all')
937/25: d.data['ra']
937/26: d.data
937/27: d.sync_traj()
937/28: d.data['ra']
937/29: d.data['doy']
937/30: h
937/31: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
937/32: fid.readline()
937/33: fid.readline()
937/34: fid.readline()
937/35: fid.readline()
937/36: fid.readline()
937/37: fid.readline()
937/38: fid.readline()
937/39: fid.readline()
937/40: u = []
937/41:
for line in fid:
    u.append(line.split()[18])
937/42: u
937/43: u[0]
937/44: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
937/45: fid.readline()
937/46: fid.readline()
937/47: fid.readline()
937/48: fid.readline()
937/49: fid.readline()
937/50: fid.readline()
937/51: fid.readline()
937/52: fid.readline()
937/53:
for line in fid:
    u.append(line.split()[17])
937/54: u
937/55: u[0]
937/56: u = []
937/57: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
937/58: fid.readline()
937/59: fid.readline()
937/60: fid.readline()
937/61: fid.readline()
937/62: fid.readline()
937/63: fid.readline()
937/64: fid.readline()
937/65: fid.readline()
937/66:
for line in fid:
    u.append(line.split()[17])
937/67: u[0]
937/68: h[0]
937/69: h=h[10:]
937/70: h[0]
937/71: h=h[10:]
937/72: h[0]
937/73: u = u[20:]
937/74: u[0]
937/75: u = u[16:]
937/76: u[0]
937/77: h[0]
937/78:
for i in range(10):
    print('%f'%(float(u[i])-float(h[i])))
937/79:
for i in range(100):
    print('%f'%(float(u[i])-float(h[i])))
937/80:
for i in range(1000):
    print('%f'%(float(u[i])-float(h[i])))
937/81:
for i in range(100):
    print('%f'%(float(u[i])-float(h[i])))
937/82: max(len(h),len(u))
937/83: min(len(h),len(u))
937/84: h = h[:6200]
937/85: u= u[:6200]
937/86: len(u)
937/87: len(h)
937/88: diff_long = []
937/89:
for i in range(len(u)):
    diff_long.append(float(u[i]-float(h[i])))
937/90:
for i in range(len(u)):
    diff_long.append(float(u[i])-float(h[i]))
937/91: diff_long
937/92: fid
937/93: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
937/94: u_dec = []
937/95: u_lat = []
937/96: fid.readline()
937/97: fid.readline()
937/98: fid.readline()
937/99: fid.readline()
937/100: fid.readline()
937/101: fid.readline()
937/102: fid.readline()
937/103: fid.readline()
937/104:
for line in fid:
    a = line.split()
    u_dec.append(a[17])
    u_lat.append(a[15])
937/105: u_dec[0]
937/106: u_dec = []
937/107: u_lat = []
937/108:
for line in fid:
    a = line.split()
    u_dec.append(a[17])
    u_lat.append(a[15])
937/109: u_lat[0]
937/110: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
937/111: u_dec = []
937/112: u_lat = []
937/113:
for line in fid:
    a = line.split()
    u_dec.append(a[17])
    u_lat.append(a[15])
937/114: fid.readline()
937/115: fid.readline()
937/116: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
937/117: fid.readline()
937/118: fid.readline()
937/119: fid.readline()
937/120: fid.readline()
937/121: fid.readline()
937/122: fid.readline()
937/123: fid.readline()
937/124: fid.readline()
937/125: u_lat = []
937/126: u_dec = []
937/127:
for line in fid:
    a = line.split()
    u_dec.append(a[17])
    u_lat.append(a[15])
937/128: u_dec[0]
937/129: fid = open('/data/etph/Ulysses/trajectory/ulysses_daily_heliocentric_data_1990-2009.txt','r')
937/130: fid.readline()
937/131: fid.readline()
937/132: fid.readline()
937/133: fid.readline()
937/134: fid.readline()
937/135: fid.readline()
937/136: fid.readline()
937/137: fid.readline()
937/138: u_dec = []
937/139: u_lat = []
937/140:
for line in fid:
    a = line.split()
    u_dec.append(a[18])
    u_lat.append(a[16])
937/141: u_dec[0]
937/142: u_lat[0]
937/143: diff_lat = []
937/144: min(len(u_dec),len(u_lat))
937/145:
for i in range(6800):
    diff_lat.append(float(u_dec[i])-float(u_lat[i]))
937/146: diff_lat
937/147: diff_long
937/148: ax = pylab.subplot(111)
937/149: ax.plot(len(diff_lat),diff_lat)
937/150: size(diff_lat)
937/151: ax.plot(range(len(diff_lat)),diff_lat)
938/1: ls
939/1: %run pui_ulysses.py
939/2: from uswipha import uswipha
940/1: from uswipha import uswipha
940/2: import sys
940/3: sys
940/4: sys.list
940/5: sys.path
941/1: %run pui_ulysses.py
941/2: %run pui_ulysses.py
941/3: d = uswipha(year=[1992,1993],tf=[[1,10]])
941/4: d.sync_traj()
941/5: %run pui_ulysses.py
941/6: d = uswipha(year=[1992,1993],tf=[[1,10]])
941/7: d.sync_traj()
942/1: d = uswipha(year=[1992,1993],tf=[[1,10]])
942/2: %run pui_ulysses.py
942/3: d = uswipha(year=[1992,1993],tf=[[1,10]])
942/4: d.sync_traj()
943/1: %run pui_ulysses.py
944/1: %run pui_ulysses.py
945/1: %run pui_ulysses.py
945/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
945/3: d.sync_traj()
945/4: d.data
945/5: d.data.keys
945/6: d.data.keys()
946/1: %run pui_ulysses.py
946/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
946/3: d.data
946/4: d.sync_traj()
947/1: %run pui_ulysses.py
947/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
947/3: d.sync_traj()
947/4: d.data
947/5: d = uswipha(year=[1992,1993],tf=[[1,10]])
947/6: d.get_data([],'d90')
947/7: d.sync_traj()
947/8: d.get_data([],'d90')
947/9: dd = d.get_data([],'d90')
947/10: size(d)
947/11: size(dd)
947/12: len(dd)
947/13: dd[::200]
947/14: len(dd[::200])
948/1: %run pui_ulysses.py
948/2: d = uswipha(year=[1992,1993],tf=[[1,10]])
948/3: d.plot_deviation_coord()
948/4: plot_deviation_coord(d)
948/5: d.sync_traj()
948/6: plot_deviation_coord(d)
948/7: d = uswipha(year=[1992,1993],tf='all')
948/8: plot_deviation_coord(d)
948/9: d.sync_traj()
948/10: plot_deviation_coord(d)
949/1: from uswipha import uswipha
949/2: d = uswipha(year=[1992,2000],tf='all')
949/3: d.sync_traj()
949/4: d.data
949/5: %run pui_ulysses.py
949/6: %run pui_ulysses.py
949/7: plot_deviation_coord(d)
949/8: len(d)
949/9: %run pui_ulysses.py
949/10: plot_deviation_coord(d)
949/11: d.get_data([],'d90')
949/12: len(d.get_data([],'d90'))
949/13: len(d.get_data([],'d90')/200.)
949/14: len(d.get_data([],'d90'))/200.
949/15: %run pui_ulysses.py
949/16: plot_deviation_coord(d)
949/17: d.get_data([],'d90')
949/18: %run pui_ulysses.py
949/19: plot_deviation_coord(d)
949/20: %run pui_ulysses.py
949/21: plot_deviation_coord(d)
949/22: plot_deviation_coord(d)
949/23: %run pui_ulysses.py
949/24: plot_deviation_coord(d)
949/25: %run pui_ulysses.py
949/26: plot_deviation_coord(d)
949/27: %run pui_ulysses.py
949/28: plot_deviation_coord(d)
949/29: %run pui_ulysses.py
949/30: plot_deviation_coord(d)
949/31: %run pui_ulysses.py
949/32: plot_deviation_coord(d)
949/33: pylab.close('all')
949/34: plot_deviation_coord(d)
949/35: plot_deviation_coord(d)
949/36: pylab.close('all')
949/37: plot_deviation_coord(d)
949/38: pylab.close('all')
949/39: pylab.close('all')
949/40: %run pui_ulysses.py
949/41: plot_deviation_coord(d)
949/42: pylab.close('all')
949/43: %run pui_ulysses.py
949/44: plot_deviation_coord(d)
949/45: %run pui_ulysses.py
949/46: plot_deviation_coord(d)
949/47: %run pui_ulysses.py
949/48: pylab.close('all')
949/49: plot_deviation_coord(d)
949/50: %run pui_ulysses.py
949/51: plot_deviation_coord(d)
949/52: %run pui_ulysses.py
949/53: pylab.close('all')
949/54: plot_deviation_coord(d)
949/55: %run pui_ulysses.py
949/56: plot_deviation_coord(d)
949/57: %run pui_ulysses.py
949/58: plot_deviation_coord(d)
949/59: %run pui_ulysses.py
949/60: pylab.close('all')
949/61: plot_deviation_coord(d)
949/62: pylab.close('all')
949/63: %run pui_ulysses.py
949/64: plot_deviation_coord(d)
949/65: %run pui_ulysses.py
949/66: plot_deviation_coord(d)
949/67: %run pui_ulysses.py
949/68: pylab.close('all')
949/69: plot_deviation_coord(d)
950/1: d = uswipha(year=range(1990,2004),tf='all')
950/2: from uswipha import uswipha
950/3: d = uswipha(year=range(1990,2004),tf='all')
951/1: from uswipha import uswipha
951/2: d = uswipha(year=range(1991,2000),tf='all')
952/1: from uswipha import uswipha
952/2: d = uswipha(year=range(1991,1998),tf='all')
952/3: %run pui_ulysses.py
952/4: plot_deviation_coord(d)
952/5: d.sync_traj()
952/6: plot_deviation_coord(d)
952/7: d = uswipha(year=range(1990,1999),tf='all')
953/1: from uswipha import uswipha
953/2: d = uswipha(year=range(1990,1998),tf='all')
953/3: %run pui_ulysses.py
953/4: d.sync_traj()
953/5: %run pui_ulysses.py
953/6: d.sync_traj()
953/7: d = uswipha(year=range(1990,1997),tf='all')
954/1: from uswipha import uswipha
954/2: d = uswipha(year=range(1990,1997),tf=range(0,365,10))
954/3: d = uswipha(year=range(1990,1997),tf=[range(0,365,10)])
955/1: range(0,100,5)
955/2: range(0,365,10)
954/4: d = uswipha(year=range(1990,1997),tf=[[1,10],[100,110],[200,210],[300,310]])
954/5: d.sync_traj()
954/6: %run pui_ulysses.py
954/7: plot_deviation_coord(d)
954/8: d.sync_traj()
954/9: plot_deviation_coord(d)
954/10: from uswipha import uswipha
954/11: d.sync_traj()
954/12: d = uswipha(year=range(1990,1997),tf=[[1,10],[100,110],[200,210],[300,310]])
954/13: %run pui_ulysses.py
954/14: d.sync_traj()
954/15: plot_deviation_coord(d)
956/1: from uswipha import uswipha
956/2: d = uswipha(year=range(1990,1997),tf=[[1,10],[100,110],[200,210],[300,310]])
956/3: %run pui_ulysses.py
956/4: d.sync_traj()
956/5: plot_deviation_coord(d)
956/6: %run pui_ulysses.py
956/7: plot_deviation_coord(d)
956/8: %run pui_ulysses.py
956/9: plot_deviation_coord(d)
957/1: range(0,365,10)
957/2: from uswipha import uswipha
957/3: d = uswipha(year=range(1990,1997),tf=[[0,10],[50,60],[100,110],[150,160],[200,210],[250,260],[300,310]])
957/4: %run pui_ulysses.py
957/5: d.sync_traj()
957/6: plot_deviation_coord(d)
958/1: from uswipha import uswipha
958/2: d = uswipha(year=1990,tf='all')
958/3: d = uswipha(year=[1992],tf='all')
958/4: d = uswipha(year=[1990],tf='all')
958/5: d = uswipha(year=[1990],tf='all')
959/1: from pylib.etCoord import *
959/2: cart_to_sph(5,5,0,deg=True)
959/3: carth_to_sph(5,5,0,deg=True)
959/4: carth_to_sphere(5,5,0,deg=True)
959/5: cart2sph(5,5,0,deg=True)
959/6: cart2sph((5,5,0),deg=True)
959/7: carth_to_sph(5,5,0,deg=True)
959/8: cart_to_sph(5,5,0,deg=True)
959/9: rotate((5,5,0),'z',-90,degree=True)
959/10: rotate((5,5,0),'z',-90,deg=True)
959/11: v = [-4.126,1.318,-1.891]
959/12: rotate(v,'z',105.,deg=True)
959/13: rotate(v,'x',-7.25,deg=True)
959/14: vv = rotate(v,'x',-7.25,deg=True)
959/15: cart_to_sph(vv,deg=True)
959/16: cart_to_sph(vv[0],vv[1],vv[2],deg=True)
959/17: vv = rotate(v,'z',105.,deg=True)
959/18: vvv = rotate(vv,'x',-7.25,deg=True)
959/19: cart_to_sph(vvv[0],vvv[1],vvv[2],deg=True)
959/20: vv
959/21: vvv = rotate(vv,'x',7.25,deg=True)
959/22: cart_to_sph(vvv[0],vvv[1],vvv[2],deg=True)
959/23: cos(90)
959/24: cos(2*pi/360*90)
959/25: 2*pi/360*90
959/26: pi/2
959/27: a = [cos(2*pi/360*75),sin(2*pi/360*75),0]
959/28: rotate(v,a,-7.25,deg=True)
959/29: rotate(v,axis=a,-7.25,deg=True)
959/30: a = np.array(a)
959/31: rotate(v,axis=a,-7.25,deg=True)
959/32: rotate(v,a,-7.25,deg=True)
959/33: vv = rotate(v,a,-7.25,deg=True)
959/34: cart_to_sph(vv[0],vv[1],vv[2],deg=True)
959/35: 120.8-90
959/36: vvv = rotate(vv,'z',105.,deg=True)
959/37: vvv
959/38: uu = rotate(v,'z',105.,deg=True)
959/39: uuu = rotate(zz,a,-7.25,deg=True)
959/40: uuu = rotate(uu,a,-7.25,deg=True)
959/41: uuu
959/42: v
959/43: vv = rotate(v,x,45,deg=True)
959/44: vv = rotate(v,'x',45,deg=True)
959/45: vvv = rotate(v,'z',45,deg=True)
959/46: uu = rotate(v,'z',45,deg=True)
959/47: uuu = rotate(v,'x',45,deg=True)
959/48: vvv
959/49: uuu
959/50: a
959/51: v
959/52: vv = rotate(v,a,7.5,deg=True)
959/53: vvv = rotate(vv,'z',75,deg=True)
959/54: uu = rotate(v,'z',75,deg=True)
959/55: uuu = rotate(uu,'x',7.5,deg=True)
959/56: vvv
959/57: uuu
959/58: vv = rotate(v,a,7.5,deg=True)
959/59: vvv = rotate(vv,'z',10,deg=True)
959/60: uu = rotate(v,'z',10,deg=True)
959/61: uuu = rotate(uu,'x',7.5,deg=True)
959/62: vvv
959/63: uuu
961/1: from pylib.etCoord import *
961/2: u = [-4.126,1.318,-1.891]
961/3: uu = rotate(u,'z',-105.036,deg=True)
961/4: uu
961/5: rotate(uu,'x',-7.25,deg=True)
961/6: uu = rotate(u,'z',105.036,deg=True)
961/7: uu
961/8: rotate(uu,'x',7.25,deg=True)
961/9: cart_to_sph(-4.126,1.318,-1.891)
961/10: cart_to_sph(-4.126,1.318,-1.891,deg=True)
961/11: carth_to_sphere(-4.126,1.318,-1.891,deg=True)
961/12: carth_to_sphere(-4.126,1.318,-1.891)
961/13: sph_to_cart(2.772,1.75,90-130.96,deg=True)
961/14: sph_to_cart(2.772,-4.12,90-235.88,deg=True)
961/15: u = sph_to_cart(2.772,1.75,90-130.96,deg=True)
961/16: uu = rotate(u,'z',105.036,deg=True)
961/17: uuu = rotate(uu,'x',7.5,deg=True)
961/18: uuu
961/19: sph_to_cart(uuu,deg=True)
961/20: sph_to_cart(uuu[0],uuu[1],uuu[2],deg=True)
961/21: carth_to_sphere(uuu[0],uuu[1],uuu[2],deg=True)
961/22: carth_to_sphere(uuu[0],uuu[1],uuu[2])
961/23: cart_to_sphere(uuu[0],uuu[1],uuu[2],deg=True)
961/24: cart_to_sph(uuu[0],uuu[1],uuu[2],deg=True)
961/25: clear
961/26: hc_c = [2722,1.75,130.96]
961/27: hc_s = [2722,1.75,130.96]
961/28: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2])
961/29: hc_c
961/30: hc_s
961/31: hc_s = [2.722,1.75,130.96]
961/32: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2])
961/33: hc_c
961/34: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
961/35: hc_c
961/36: uu = rotate(hc_c,'z',105.036,deg=True)
961/37: uuu=rotate(uu,'x',7.25,deg=True)
961/38: uuu
961/39: cart_to_sph(uuu[0],uuu[1],uuu[2],deg=True)
961/40: hc_c
961/41: hc_s
961/42: hc_s = [2.722,1.75,90-130.96]
961/43: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
961/44: uu = rotate(hc_c,'z',105.036,deg=True)
961/45: uuu = rotate(uu,'x',7.5,deg=True)
961/46: uuu
961/47: sph_to_cart(uuu[0],uuu[1],uuu[2],deg=True)
961/48: cart_to_sph(uuu[0],uuu[1],uuu[2],deg=True)
961/49: hc_s = [4.726,162.3,90+23.59,deg=True]
961/50: hc_s = [4.726,162.3,90.+23.59]
961/51: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
961/52: hc_c
961/53: hc_c = sph_to_cart(hc_s[0],hc_s[2],hc_s[1],deg=True)
961/54: hc_c
961/55: hc_s = [2.722,90-1.75,130.96]
961/56: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
961/57: uu = rotate(hc_c,'z',105.036,deg=True)
961/58: uuu = rotate(uu,'x',7.5,deg=True)
961/59: uuu
961/60: cart_to_sph(uuu[0],uuu[1],uuu[2],deg=True)
961/61: hc_s = [4.726,90+23.59,162.3]
961/62: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
961/63: hc_c
961/64: uu = rotate(hc_c,'z',105.036,deg=True)
961/65: uuu = rotate(uu,'x',7.5,deg=True)
961/66: uuu
961/67: cart_to_sph(uuu[0],uuu[1],uuu[2],deg=True)
961/68: sph_to_cart(4.726,90+30.8,267.0,deg=True)
961/69: cart_to_sph(-0.212,-4.054,-2.419,deg=True)
961/70: hc_c
961/71: cart_to_sph(hc_c[0],hc_c[1],hc_c[2],deg=True)
961/72: cart_to_sph(-0.2125,-4.054,-2.42,deg=True)
961/73: sph_to_cart(4.726,90+23.59,162.3,deg=True)
961/74: sph_to_cart(4.726,90+30.8,267.0,deg=True)
961/75: cart_to_sph(-0.2125,-4.054,-2.42,deg=True)
961/76: cart_to_sph(-4.126,1.318,-1.891,deg=True)
961/77: carth_to_sphere(-4.126,1.318,-1.891)
961/78: old_c = np.array([-4.126,1.318,-1.891])
961/79: cart2sph(old_c,deg=True)
961/80: new_c = np.array([-0.2125,-4.054,-2.42])
961/81: cart2sph(new_c,deg=True)
961/82: 360-267
961/83: 167+90+90-75
961/84: 360-167+180+180
961/85: 360-167+75
961/86: cart2sph(new_c,deg=True)
961/87: new_c = np.array([-0.2125,4.054,-2.42])
961/88: cart2sph(new_c,deg=True)
962/1: from pylib.etCoord import *
962/2: c_old = [-4.126,1.318,-1.891]
962/3: c_new = [-0.2125,-4.054,-2.42]
962/4: cart_to_sph(c_old[0],c_old[1],c_old[2],deg=True))
962/5: cart_to_sph(c_old[0],c_old[1],c_old[2],deg=True)
962/6: cart_to_sph(c_new[0],c_new[1],c_new[2],deg=True))
962/7: cart_to_sph(c_new[0],c_new[1],c_new[2],deg=True)
962/8: s = [2.722,1.75,130.96,deg=True)]
962/9: s = [2.722,1.75,130.96,deg=True)
962/10: s = [2.722,1.75,130.96]
962/11: sph_to_cart(s[0],s[1],s[2],deg=True)
962/12: sph_to_cart(s[0],90.-s[1],s[2],deg=True)
962/13: c_hc = sph_to_cart(s[0],90.-s[1],s[2],deg=True)
962/14: c_hg = rotate(c_hc,'z',105.036,deg=True)
962/15: c_hg
962/16: cart_to_sph(c_hg[0],c_hg[1],c_hg[2],deg=True)
962/17: rotate(c_hg,'x',7.25,deg=True)
962/18: hg_c = rotate(c_hg,'x',7.25,deg=True)
962/19: cart_to_sph(hg_c[0],hg_c[1],hg_c[2],deg=True)
962/20: 124.09303+235.88
962/21: sqrt(1.5215**2+2.24794**2+0.202178**2)
962/22: uuu = sph_to_cart(2.722,94.12,235.88)
962/23: uuu
962/24: sqrt(uuu[0]**2+uuu[1]**2+uuu[2]**2)
962/25: clear
962/26: hg_s = [2.7223,94.12,235.88]
962/27: hg_c = sph_to_cart(gh_s[0],hg_s[1],hg_s[2],deg=True)
962/28: hg_c = sph_to_cart(hg_s[0],hg_s[1],hg_s[2],deg=True)
962/29: hg_c
962/30: cart_to_sph(hg_s[0],hg_s[1],hg_s[2],deg=True)
962/31: cart_to_sph(hg_c[0],hg_c[1],hg_c[2],deg=True)
962/32: rotate(hg_c,'z',-105.036,deg=True)
962/33: z = rotate(hg_c,'z',-105.036,deg=True)
962/34: hg_t = rotate(z,'x',-7.25,deg=True)
962/35: hg_t
962/36: clear
962/37: s = [4.726,90+23.69,162.3]
962/38: c = sph_to_cart(s[0],s[1],s[2],deg=True)
962/39: c
962/40: rotat(c,'z',105.036,deg=True)
962/41: rotate(c,'z',105.036,deg=True)
962/42: rotate(c,'z',-105.036,deg=True)
962/43: u = rotate(c,'z',-105.036,deg=True)
962/44: rotate(u,'x',-7.25,deg=True)
962/45: uu = rotate(u,'x',-7.25,deg=True)
962/46: s
962/47: u
962/48: c
962/49: u = rotate(c,'z',-105.036,deg=True)
962/50: uu = rotate(u,'x',-7.25,deg=True)
962/51: uu
962/52: u = rotate(c,'z',105.036,deg=True)
962/53: uu = rotate(u,'x',7.25,deg=True)
962/54: uu
962/55: u
962/56: hc = [2.7223,90-1.75,130.96]
962/57: hc_c = sph_to_cart(hc[0],hc[1],hc[2],deg=True)
962/58: hc_c
962/59: rotate(hc_c,'z',105.036,deg=True)
962/60: u = rotate(hc_c,'z',105.036,deg=True)
962/61: uu = rotate(u,'x',7.25,deg=True)
962/62: uu
962/63: sph_to_cart(uu[0],uu[1],uu[2],deg=True)
962/64: cart_to_sph(uu[0],uu[1],uu[2],deg=True)
962/65: 124.093+235.88
962/66: hc_s = [3.565,90-48.62,144.89]
962/67: sph_to_cart(hc_s[0],hc[1],hc_s[2],deg=True)
962/68: hc_c = sph_to_cart(hc_s[0],hc[1],hc_s[2],deg=True)
962/69: u = rotate(hc_c,'z',105.036,deg=True)
962/70: u
962/71: uu = rotate(u,'x',7.25,deg=True)
962/72: uu
962/73: cart_to_sph(uu[0],uu[1],uu[2],deg=True)
962/74: hc_c
962/75: 90-48.62
962/76: sqrt(hc_c[0]**2+hc_c[1]**2+hc_c[2]**2)
962/77: sin(0)
962/78: sin(360)
962/79: sin(360*2*pi/360.)
962/80: hc_s
962/81: hc_s = [3.565,90-48.62,144.89]
962/82: cart_to_sph(hc_s[0],hc_s[1],hc_s[2],deg=True)
962/83: sph_to_cart(hc_s[0],hc[1],hc_s[2],deg=True)
962/84: sph2cart
962/85: sph2cart(hc_s,deg=True)
962/86: hc_s
962/87: sph2cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
962/88: sph2cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
962/89: sph_to_cart(hc_s[0],hc[1],hc_s[2],deg=True)
962/90: sph_to_cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
962/91: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
962/92: u = rotate(hc_c,'z',105.036,deg=True)
962/93: uu = rotate(u,'x',7.25,deg=True)
962/94: uu
962/95: cart_to_sph(uu[0],uu[1],uu[2],deg=True)
962/96: 90-48.241909
962/97: cart_to_sph(uu[0],uu[1],uu[2],deg=True)[2]
962/98: cart_to_sph(uu[0],uu[1],uu[2],deg=True)[2] - 252.3
963/1: from uswipha import uswipha
963/2: d = uswipha(year=[1993],tf='all')
963/3: d.sync_traj()
963/4: d.data
963/5: d.ra
963/6: d.get_data['ra']
963/7: d.get_data('ra')
963/8: d.get_data([],'d90')
963/9: from uswipha import uswipha
963/10: d = uswipha(year=[1993],tf=[[1.10]])
963/11: d = uswipha(year=[1993],tf=[[1,10]])
963/12: d.sync_traj()
963/13: d.data
964/1: from uswipha import uswipha
964/2: d = uswipha(year=[1993],tf=[[1,10]])
964/3: d.data
964/4: d.sync_traj()
964/5: d.data
965/1: from uswipha import uswipha
965/2: d = uswipha(year=[1993],tf=[[1,10]])
965/3: d.sync_traj()
965/4: d.data
965/5: d.get_data([],'lat_hc')
965/6: d.get_data([],'lat_hc') - d.get_data([],'lat_hg')
965/7: d = uswipha(year=[1993,1995,1998],tf=[[1,10]])
965/8: d.sync_traj()
965/9: d.get_data([],'lat_hc') - d.get_data([],'lat_hg')
965/10: dif = d.get_data([],'lat_hc') - d.get_data([],'lat_hg')
965/11: plot(len(dif),dif)
965/12: dif
965/13: shape(dif)
965/14: len(dif)
965/15: plot(len(dif),dif[0])
965/16: d.get_data([],'d90')
965/17: plot(len(dif),dif)[0]
965/18: plot(len(dif),dif[0])
965/19: mean(dif[0])
965/20: plot(range(len(dif)),dif[0])
965/21: plot(range(len(dif))-1,dif[0])
965/22: range(len(dif))
965/23: len(dif)
965/24: len(range(len(dif)))
965/25: plot(range(len(dif)),dif[0])
965/26: len(dif[0])
965/27: dif[0]
965/28: dif
965/29: plot(range(len(dif)),dif)
966/1: d = uswipha(year=[1993,1994,1995,1996,1997,1998],tf=[[1,10]])
966/2: from uswipha import uswipha
966/3: d = uswipha(year=[1993,1994,1995,1996,1997,1998],tf=[[1,10]])
966/4: d.sync_traj()
966/5: plot(range(len(dif)),dif)
966/6: dif = d.get_data([],'lat_hc') - d.get_data([],'lat_hg')
966/7: plot(range(len(dif)),dif)
966/8: %run pui_ulysses.py
966/9: summary_traj(d)
966/10: %run pui_ulysses.py
966/11: summary_traj(d)
966/12: d = uswipha(year=[1993,1994,1995],tf='all')
966/13: d.sync_traj()
966/14: summary_traj(d)
967/1: %run pui_ulysses.py
967/2: range(1,30,3)
967/3: time = range(1,365,4)
967/4: d = uswipha(year=range(1990,1998),tf=[[time]])
968/1: d = uswipha(year=range(1990,1998),tf='all')
968/2: %run pui_ulysses.py
968/3: d = uswipha(year=range(1990,1997),tf='all')
968/4: d.sync_traj()
968/5: d.data
968/6: d.summary()
968/7: d.summary_traj()
968/8: summary_traj(d)
969/1: %run pui_ulysses.py
969/2: d = uswipha(year=range(1990,1997),tf='all')
969/3: d.sync_traj()
970/1: %run pui_ulysses.py
970/2: d = uswipha(year=range(1990,1993),tf='all')
970/3: d.sync_traj()
971/1: %run pui_ulysses.py
971/2: d = uswipha(year=range(1990,1992),tf='all')
971/3: d.sync_traj()
971/4: from uswipha import uswipha
971/5: d.sync_traj()
971/6: d = uswipha(year=range(1990,1992),tf=[[1,100]])
971/7: d.sync_traj()
972/1: %run pui_ulysses.py
972/2: d = uswipha(year=range(1990,1992),tf=[[1,100]])
972/3: d.sync_traj()
972/4: d = uswipha(year=range(1990,1992),tf='all')
972/5: d.sync_traj()
972/6: traj
972/7: t = ulysses_traj(d)
972/8: from ulysses_traj import ulysses_traj
972/9: t = ulysses_traj(d)
972/10: t
972/11: t.data
972/12: t.get_data('RA')
972/13: t.get_data([],'RA')
973/1: from ulysses_traj import ulysses_traj
973/2: t = ulysses_traj(year=range(1990,1992),tf='all')
973/3: t
973/4: t.data
973/5: t.data.keys
973/6: t.data.keys()
973/7: t.get_data([],'DEC')
973/8: t('DEC')
973/9: t['DEC']
973/10: t.get_data['DEC']
973/11: t.get_data('DEC')
973/12: t.get_data('all','DEC')
973/13: len(t.get_data('all','DEC'))
973/14: len(t.get_data('all','ra_heliographic'))
973/15: t.keys()
973/16: t.keys
974/1: from ulysses_traj import ulysses_traj
974/2: t = ulysses_traj(year=range(1990,1992),tf='all')
975/1: t = ulysses_traj(year=range(1990,1992),tf='all')
975/2: from ulysses_traj import ulysses_traj
975/3: t = ulysses_traj(year=range(1990,1992),tf='all')
975/4: t.timeframe
975/5:
for tf in t.tiemframe:
    print(tf)
975/6:
for tf in t.timeframe:
    print(tf)
976/1: from ulysses_traj import ulysses_traj
976/2: t = ulysses_traj(year=range(1990,1992),tf='all')
976/3: t.data['ra_hg']
976/4: (t.data['ra_hg'])
976/5: len(t.data['ra_hg'])
976/6: len(t.data['DEC'])
976/7: len(t.data['RA'])
977/1: from ulysses_traj import ulysses_traj
977/2: t = ulysses_traj(year=range(1991,1993),tf='all')
977/3: len(t.data['RA'])
977/4: len(t.data['DEC'])
977/5: len(t.data['ra_hg'])
978/1: from ulysses_traj import ulysses_traj
978/2: t = ulysses_traj(year=range(1991,1993),tf='all')
978/3: t.timeframe
978/4: t.timeframe[0]
978/5: t = ulysses_traj(year=range(1991,1993),tf=[[1,10]])
978/6: t.timeframe[0]
978/7: t.timeframe[0][0]
978/8: type(t.timeframe[0][0])
978/9: t.keys
978/10: type(t.keys)
978/11: type(t)
978/12: t.keys.remove('ra_hg')
978/13: t.keys
979/1: from ulysses_traj import ulysses_traj
979/2: t = ulysses_traj(year=range(1991,1993),tf=[[1,10]])
979/3: t = ulysses_traj(year=range(1990,1993),tf=[[1,10]])
979/4: t = ulysses_traj(year=range(1990,1993),tf=[[1,10]])
980/1: from ulysses_traj import ulysses_traj
980/2: t = ulysses_traj(year=range(1990,1993),tf=[[1,10]])
980/3: t.year
981/1: t = ulysses_traj(year=range(1990,1993),tf=[[1,10]])
981/2: from ulysses_traj import ulysses_traj
981/3: t = ulysses_traj(year=range(1990,1993),tf=[[1,10]])
982/1: from ulysses_traj import ulysses_traj
982/2: t = ulysses_traj(year=range(1990,1993),tf=[[1,10]])
983/1: from ulysses_traj import ulysses_traj
983/2: t = ulysses_traj(year=range(1990,1993),tf=[[1,10]])
984/1: from ulysses_traj import ulysses_traj
984/2: t = ulysses_traj(year=range(1990,1993),tf=[[1,10]])
985/1: t = ulysses_traj(year=range(1991,1993),tf=[[1,10]])
985/2: from ulysses_traj import ulysses_traj
985/3: t = ulysses_traj(year=range(1991,1993),tf=[[1,10]])
986/1: from ulysses_traj import ulysses_traj
986/2: t = ulysses_traj(year=range(1991,1993),tf=[[1,10]])
987/1: from uswipha import uswipha
987/2: d = uswipha(year=range(1990,1992),tf='all')
987/3: d.sync_traj()
987/4: d = uswipha(year=range(1991,1992),tf='all')
987/5: d.sync_traj()
987/6: summary_traj(d)
987/7: from ulysses_traj import ulysses_traj
987/8: summary_traj(d)
987/9: %run pui_ulysses.py
987/10: summary_traj(d)
988/1: d = uswipha(year=range(1991,1999),tf='all')
988/2: from uswipha import uswipha
988/3: d = uswipha(year=range(1991,1999),tf='all')
989/1: from uswipha import uswipha
989/2: d = uswipha(year=range(1991,1992),tf='all')
989/3: %run pui_ulysses.py
989/4: d.sync_traj()
989/5: summary_traj(d)
990/1: d = uswipha(year=range(1991,1992),tf='all')
990/2: from uswipha import uswipha
990/3: d = uswipha(year=range(1991,1992),tf='all')
990/4: %run pui_ulysses.py
990/5: summary_traj(d)
991/1: %run pui_ulysses.py
991/2: d = uswipha(year=range(1991,1992),tf='all')
991/3: summary_traj(d)
991/4: d.sync_traj()
991/5: summary_traj(d)
992/1: %run pui_ulysses.py
992/2: d = uswipha(year=range(1991,1992),tf='all')
992/3: d.sync_traj()
992/4: summary_traj(d)
993/1: %run pui_ulysses.py
993/2: d = uswipha(year=range(1991,1999),tf='all')
994/1: %run pui_ulysses.py
994/2: d = uswipha(year=range(1991,1998),tf='all')
994/3: d.sync_traj()
994/4: summary_traj(d)
995/1: from pylib.etCoord import *
995/2: hc_s = [2.7223,1.75,130.96]
995/3: hc_c = sph_to_cart(hc_s[0],hc_s[1],hc_s[2],deg=True)
995/4: hc_c
995/5: test = [10,10,90]
995/6: test_c = sph_to_cart(test[0],test[1],tets[2],deg=True)
995/7: test_c = sph_to_cart(test[0],test[1],test[2],deg=True)
995/8: test_c
995/9: test_c = sph_to_cart(test[0],90-10,test[2],deg=True)
995/10: test_c
995/11: test_s = [10,90-40,90]
995/12: test_c = sph_to_cart(test[0],test[1],test[2],deg=True)
995/13: test_c
995/14: test_c = sph_to_cart(test_s[0],test_s[1],test_s[2],deg=True)
995/15: test_c
995/16: u = rotate(test_c,'x',40,deg=True)
995/17: u
995/18: test_c
995/19: u = rotate(test_c,'x',-50,deg=True)
995/20: u
995/21: test_c
995/22: cart_to_sph(test_c[0],test_c[1],test_c[2],deg=True)
995/23: u = rotate(test_c,'x',-40,deg=True)
995/24: u
995/25: uu = rotate(u,'z',90,deg=True)
995/26: uu = rotate(u,'z',-90,deg=True)
995/27: uu
995/28: p_c = [-5,5,4.5]
995/29: u = rotate(p_c,'x',-40,deg=True)
995/30: uu = rotate(u,'z',-90,deg=True)
995/31: uu
995/32: u = rotate(p_c,'z',-90,deg=True)
995/33: uu = rotate(u,'x',-40,deg=True)
995/34: uu
996/1: from pylib.etCoord import *
996/2: rotate([1,2,3],'x',10,deg=True)
996/3: a,b,c = rotate([1,2,3],'x',10,deg=True)
996/4: a
996/5: c
997/1: %run ul_calc_traj.py
997/2: sc = [10,90,50]
997/3: r,t,n = hg_to_rtn(sc,sc)
997/4: %run ul_calc_traj.py
997/5: sc = [10,90,50]
997/6: r,t,n = hg_to_rtn(sc,sc)
997/7: %run ul_calc_traj.py
997/8: sc = [10,90,50]
997/9: r,t,n = hg_to_rtn(sc,sc)
997/10: r
997/11: t
997/12: n
997/13: %run ul_calc_traj.py
997/14: r,t,n = hg_to_rtn(sc,sc)
997/15: sph2cart(r_vec,deg=True)
997/16: sph2cart(sc,deg=True)
997/17: sc_c = sph2cart(sc,deg=True)
997/18: sc_c
997/19: %run ul_calc_traj.py
997/20: r,t,n = hg_to_rtn(sc,sc)
997/21: %run ul_calc_traj.py
997/22: r,t,n = hg_to_rtn(sc,sc)
997/23: sc
997/24: sc_c
997/25: u = rotate(sc,'x',-40,deg=True)
997/26: u
997/27: u = rotate(sc_c,'x',-40,deg=True)
997/28: u
997/29: uu = rotate(u,'z',90,deg=True)
997/30: uu
997/31: uu = rotate(u,'z',-90,deg=True)
997/32: uu
997/33: %run ul_calc_traj.py
997/34: sc
997/35: hg_to_rtn(sc,sc)
997/36: sc =
997/37: sc = [10,90,40]
997/38: hg_to_rtn(sc,sc)
997/39: %run ul_calc_traj.py
997/40: hg_to_rtn(sc,sc)
998/1: %run ul_calc_traj.py
998/2: hg_to_rtn(sc,sc)
998/3: sc = [10,90,40]
998/4: hg_to_rtn(sc,sc)
998/5: sc_vec[2]
998/6: sc_vec(2)
998/7: sc[2]
998/8: sc = [10,90,40]
998/9: sc[2]
998/10: hg_to_rtn(sc,sc)
999/1: %run ul_calc_traj.py
999/2: sc = [10,90,40]
999/3: hg_to_rtn(sc,sc)
1000/1: %run ul_calc_traj.py
1000/2: %run ul_calc_traj.py
1000/3: sc = [10,90,40]
1000/4: hg_to_rtn(sc,sc)
1001/1: hg_to_rtn(sc,sc)
1001/2: %run ul_calc_traj.py
1001/3: sc = [10,90,40]
1001/4: hg_to_rtn(sc,sc)
1002/1: %run ul_calc_traj.py
1002/2: sc = [10,90,40]
1002/3: hg_to_rtn(sc,sc)
1003/1: %run ul_calc_traj.py
1003/2: sc = [10,90,40]
1003/3: hg_to_rtn(sc,sc)
1003/4: array(1,2,3)
1003/5: array
1003/6: array 1 2 3
1003/7: array( 1 2 3)
1003/8: numpy.array(1,2,3)
1003/9: numpy.array([1,2,3])
1004/1: %run ul_calc_traj.py
1005/1: %run ul_calc_traj.py
1005/2: sc = [10,90,40]
1005/3: hg_to_rtn(sc,sc)
1005/4: %run ul_calc_traj.py
1005/5: hg_to_rtn(sc,sc)
1005/6: sc
1005/7: %run ul_calc_traj.py
1005/8: hg_to_rtn(sc,sc)
1005/9: sc = [10,270,40]
1005/10: hg_to_rtn(sc,sc)
1006/1: %run ul_calc_traj.py
1006/2: sc = [10,270,40]
1006/3: %run ul_calc_traj.py
1006/4: sc = [10,270,40]
1006/5: hg_to_rtn(sc,sc)
1006/6: sc
1007/1: %run ul_calc_traj.py
1007/2: sc = [10,270,40]
1007/3: hg_to_rtn(sc,sc)
1008/1: c = [1,2,3]
1008/2: test(a)
1008/3: test(c)
1008/4: c[0]
1009/1: c = [1,2,3]
1009/2: test(c)
1010/1: c = [1,2,3]
1010/2: t_func(c)
1010/3: %run ul_calc_traj.py
1010/4: t_func(c)
1010/5: a
1010/6: c
1011/1: %run ul_calc_traj.py
1011/2: sc
1011/3: sc = [10,270,40]
1011/4: hg_to_rtn(sc,sc)
1012/1: %run ul_calc_traj.py
1012/2: sc = [10,270,40]
1012/3: hg_to_rtn(sc,sc)
1012/4: e_sph = [1,326,0]
1012/5: e_sph = array([1,326,0])
1012/6: e_cart = sph2cart(e_sph)
1012/7: e_cart
1012/8: 360-326
1012/9: e_sph = array([1,-34.,0])
1012/10: e_cart = sph2cart(e_sph)
1012/11: e_cart
1013/1: from pylib.etCoord import *
1013/2: e_sph = array([1,-34.,0])
1013/3: e_cart = sph2cart(e_sph)
1013/4: e_cart
1013/5: e_cart = sph2cart(e_sph,deg=True)
1013/6: e_cart
1013/7: e_sph = array([10.,-34.,0])
1013/8: e_cart = sph2cart(e_sph,deg=True)
1013/9: e_cart
1013/10: sph2cart([5,90,45])
1013/11: sph2cart([5,90,0])
1013/12: e_sph = array([10.,-34.,90.])
1013/13: e_cart = sph2cart(e_sph,deg=True)
1013/14: e_cart
1013/15: e_new = rotate(e_cart,'x',-7.25,deg=True)
1013/16: e_new
1013/17: cart2sph(e_new,deg=True)
1013/18: e_new2 = rotate(e_cart,'x',-72.25,deg=True)
1013/19: cart2sph(e_new2,deg=True)
1015/1: from pylib.etCoord import *
1015/2: hg_sp = array([1,0,325.8])
1015/3: sph2cart(hg_sp)
1015/4: hg_sp = array([1,325.8,0])
1015/5: sph2cart(hg_sp)
1015/6: sph2cart(hg_sp,deg=True)
1015/7: sph_to_cart(hg_sp[0],hg_sp[2],hg_sp[1],deg=True)
1015/8: hg_sp = [1.,325.8,0.]
1015/9: sph_to_cart(hg_sp[0],hg_sp[2],hg_sp[1],deg=True)
1015/10: hg_sp = [1.,25.8,0.]
1015/11: sph_to_cart(hg_sp[0],hg_sp[2],hg_sp[1],deg=True)
1015/12: hg_sp = [1.,25.8,10.]
1015/13: sph_to_cart(hg_sp[0],hg_sp[2],hg_sp[1],deg=True)
1015/14: hg_sp = [1.,360.-325.88,10.]
1015/15: hg_sp
1015/16: sph_to_cart(hg_sp[0],hg_sp[2],hg_sp[1],deg=True)
1015/17: sph2cart(hg_sp,deg=True)
1015/18: hg_sp = [1.,360.-325.88,0.]
1015/19: hg_cart = sph2cart(hg_sp,deg=True)
1015/20: hg_cart
1015/21: hg_sp
1015/22: hg_sp = [1.,-360.+325.88,0.]
1015/23: hg_sp
1015/24: hg_cart = sph2cart(hg_sp,deg=True)
1015/25: hg_cart
1015/26: hg_sp = array([1.,-360.+325.88,0.])
1015/27: hg_cart = sph2cart(hg_sp,deg=True)
1015/28: hg_cart
1015/29: sph_to_cart(hg_sp[0],hg_sp[2],hg_sp[1],deg=True)
1015/30: hg_sp = array([1.,-360.+325.88,0.000001])
1015/31: sph_to_cart(hg_sp[0],hg_sp[2],hg_sp[1],deg=True)
1015/32: hg_sp = array([1.,-360.+325.88,90.])
1015/33: sph_to_cart(hg_sp[0],hg_sp[2],hg_sp[1],deg=True)
1015/34: 360-325.88
1015/35: ans + 180
1015/36: 34.12+180.
1015/37: 34.12-180.
1015/38: 325.88-180
1015/39: 325.88-90
1015/40: rot_sp = array([1,235.88,90])
1015/41: sph2cart(rot_sp,deg=True)
1015/42: rot_sp = array([10,235.88,90])
1015/43: sph2cart(rot_sp,deg=True)
1015/44: hg_cart = sph2cart(hg_sp,deg=True)
1015/45: hg_cart
1015/46: n_cart = sph2cart(0.,0.,90.,deg=True)
1015/47: n_cart = sph2cart([0.,0.,90.],deg=True)
1015/48: n_cart
1015/49: n_cart = sph2cart([1.,0.,90.],deg=True)
1015/50: n_cart
1015/51: hg_cart - n_cart
1015/52: diff = hg_cart - n_cart
1015/53: sqrt(diff[0]^2+diff[1]^2)
1015/54: diff
1015/55: diff[0]
1015/56: diff[0]^2
1015/57: diff[0]**2
1015/58: sqrt(diff[0]**2+diff[1]**2)
1015/59: 360-325.88
1015/60: 34.12 * 1.
1015/61: 34.12*pi/180
1015/62: tan(1)
1015/63: tan(7.25*180/pi)
1015/64: tan(7.25/180*pi)
1015/65: tan(7.25/180*pi) * 0.58674597
1015/66: hg_cart
1015/67: hg_cart - array([1.,0.,0.])
1015/68: diff = hg_cart - array([1.,0.,0.])
1015/69: A = sqrt(diif[0]**2+diff[1]**2)
1015/70: A = sqrt(diff[0]**2+diff[1]**2)
1015/71: A
1015/72: 155.19+180
1015/73: 335.19-9.24
1015/74: hg_sph2 = array([1.0593,325.95,90.])
1015/75: hg2_c = sph2cart(hg_sph2,deg=True)
1015/76: hg2_c - array([1.0593,0.,0.])
1015/77: diff = hg2_c - array([1.0593,0.,0.])
1015/78: A = sqrt(diff[0]**2+diff[1]**2)
1015/79: A
1015/80: diff
1015/81: 75+180+41
1015/82: 360-75
1015/83: +41
1015/84: 285+41
1015/85: hg_sph2 = array([0.992,325.95,90.])
1015/86: hg_c2 = sph2cart(hg_sph2,deg=True)
1015/87: diff = hg2_c - array([0.992,0.,0.])
1015/88: A = sqrt(diff[0]**2+diff[1]**2)
1015/89: A
1015/90: arctan(1.)
1016/1: %run ul_calc_traj.py
1016/2: %run ul_calc_traj.py
1016/3: sc_sph = array([2,270,30])
1016/4: sc_sph
1016/5: sph2cart(sc_sph,deg=True)
1016/6: sc_sph = array([2,270,3])
1016/7: sph2cart(sc_sph,deg=True)
1016/8: sc_sph = array([2,270,30])
1016/9: hg_to_rtn(sc_sph,sc_sph)
1016/10: e_sph = array([1.,180.,0])
1016/11: hg_to_rtn(e_sph,sc_sph)
1016/12: e_rtn = hg_to_rtn(e_sph,sc_sph)
1016/13: sc_rtn = hg_to_rtn(sc_rtn,sc_rtn)
1016/14: sc_rtn = hg_to_rtn(sc_sph,sc_sph)
1016/15: calc_asp_angles(sc_rtn,e_rtn)
1017/1: %run ul_calc_traj.py
1017/2: sc_sph = array([2,270,30])
1017/3: e_sph = array([1.,180.,0])
1017/4: calc_asp_angles(sc_rtn,e_rtn)
1017/5: calc_asp_angles(sc_sph,earth_sph)
1017/6: calc_asp_angles(sc_sph,e_sph)
1017/7: e_sph
1018/1: sc_sph = array([2,90,30])
1018/2: e_sph = array([1.,0.,0])
1018/3: calc_asp_angles(sc_sph,e_sph)
1018/4: calc_asp_angles(sc_sph,e_sph)
1019/1: %run ul_calc_traj.py
1019/2: sc_sph = array([2,90,30])
1019/3: e_sph = array([1.,0.,0])
1019/4: calc_asp_angles(sc_sph,e_sph,cs='hg')
1020/1: %run ul_calc_traj.py
1020/2: sc_sph = array([2,90,30])
1020/3: e_sph = array([1.,0.,0])
1020/4: calc_asp_angles(sc_sph,e_sph,cs='hg')
1020/5: hg_to_rtn(e_sph,sc_sph,long_shift=0.)
1021/1: %run ul_calc_traj.py
1021/2: e_sph = array([1.,0.,0])
1021/3: sc_sph = array([2,90,30])
1021/4: %run ul_calc_traj.py
1021/5: hg_to_rtn(e_sph,sc_sph,long_shift=0.)
1021/6: calc_asp_angles(sc_sph,e_sph,cs='hg')
1022/1: %run ul_calc_traj.py
1022/2: sc = [2,90.,30.]
1022/3: e = [1,0,0,]
1022/4: hg_to_rtn(e,sc,long_shift=0.)
1022/5: calc_asp_angles(sc,e,cs='hg')
1022/6: sc
1022/7: e
1022/8: %run ul_calc_traj.py
1022/9: calc_asp_angles(sc,e,cs='hg')
1022/10: %run ul_calc_traj.py
1022/11: calc_asp_angles(sc,e,cs='hg')
1022/12: e
1022/13: sc
1022/14: hg_to_rtn(sc,sc,long_shift=0.)
1022/15: %run ul_calc_traj.py
1022/16: hg_to_rtn(sc,sc,long_shift=0.)
1022/17: sc = [2,90.,10.]
1022/18: hg_to_rtn(sc,sc,long_shift=0.)
1022/19: sc = [2,90.,30.]
1022/20: hg_to_rtn(sc,sc,long_shift=0.)
1022/21: %run ul_calc_traj.py
1022/22: hg_to_rtn(sc,sc,long_shift=0.)
1022/23: sc[1]
1023/1: %run ul_calc_traj.py
1023/2: sc = [2,90.,30.]
1023/3: hg_to_rtn(sc,sc,long_shift=0.)
1023/4: e = [1,0,0,]
1023/5: calc_asp_angles(sc,e,cs='hg')
1023/6: %run ul_calc_traj.py
1023/7: calc_asp_angles(sc,e,cs='hg')
1023/8: e = [1,0,10]
1023/9: calc_asp_angles(sc,e,cs='hg')
1023/10: sc = [2,90.,0.]
1023/11: calc_asp_angles(sc,e,cs='hg')
1024/1: %run ul_calc_traj.py
1024/2: e = [1,0,10]
1024/3: sc = [2,90.,0.]
1024/4: calc_asp_angles(sc,e,cs='hg')
1025/1: %run ul_calc_traj.py
1025/2: sc = [2,90.,0.]
1025/3: e = [1,0,10]
1025/4: calc_asp_angles(sc,e,cs='hg')
1025/5: sc = [2,90.,0.]
1026/1: %run ul_calc_traj.py
1026/2: sc = [2,90.,0.]
1026/3: e = [1,0,10]
1026/4: calc_asp_angles(sc,e,cs='hg')
1027/1: %run ul_calc_traj.py
1027/2: e = [1,0,10]
1027/3: sc = [2,90.,0.]
1027/4: calc_asp_angles(sc,e,cs='hg')
1027/5: %run ul_calc_traj.py
1027/6: calc_asp_angles(sc,e,cs='hg')
1027/7: 153.78+180
1027/8: -153.78+180
1027/9: %run ul_calc_traj.py
1027/10: calc_asp_angles(sc,e,cs='hg')
1027/11: sc = [2,90.,10.]
1027/12: calc_asp_angles(sc,e,cs='hg')
1027/13: sc = [2,90.,20.]
1027/14: calc_asp_angles(sc,e,cs='hg')
1027/15: sc = [2,90.,330.]
1027/16: sc = [2,90.,30.]
1027/17: calc_asp_angles(sc,e,cs='hg')
1028/1: %run ul_calc_traj.py
1028/2: ls
1028/3: pwd
1028/4: cd
1028/5: cd pui/ulysses/swics/
1028/6: ls
1028/7: cd software/libulpy/
1028/8: %run ul_calc_traj.py
1029/1: %run ul_calc_traj.py
1029/2: sc = [2,90.,30.]
1029/3: e = [1,0,10]
1029/4: calc_asp_angles(sc,e,cs='hg')
1029/5: 360-270
1029/6: 180-40
1029/7: -90
1029/8: 140-90
1029/9: 90-86.002
1029/10: sc
1029/11: e = [1,0,0]
1029/12: calc_asp_angles(sc,e,cs='hg')
1029/13: sc
1029/14: hg_to_rtn(sc,sc,long_shift=0.)
1029/15: e
1029/16: hg_to_rtn(e,sc,long_shift=0.)
1030/1: %run ul_calc_traj.py
1030/2: sc = [2,90.,30.]
1030/3: e = [1,0,0]
1030/4: hg_to_rtn(e,sc,long_shift=0.)
1031/1: %run ul_calc_traj.py
1031/2: e = [1,0,0]
1031/3: sc = [2,90.,30.]
1031/4: hg_to_rtn(e,sc,long_shift=0.)
1031/5: e = [1,0,10.]
1031/6: hg_to_rtn(e,sc,long_shift=0.)
1031/7: sc = [2,180.,30.]
1031/8: e = [1,0,10.]
1031/9: hg_to_rtn(e,sc,long_shift=0.)
1031/10: %run ul_calc_traj.py
1031/11: e = [1,0,10.]
1031/12: sc = [2,45.,10.]
1031/13: hg_to_rtn(e,sc,long_shift=0.)
1031/14: sc = [2,0.,10.]
1031/15: hg_to_rtn(e,sc,long_shift=0.)
1031/16: sc = [2,90.,10.]
1031/17: hg_to_rtn(e,sc,long_shift=0.)
1031/18: e
1031/19: sc
1031/20: calc_asp_angles(sc,e,cs='hg')
1032/1: e = [1,0,10.]
1032/2: sc = [2,90.,10.]
1032/3: calc_asp_angles(sc,e,cs='hg')
1032/4: %run ul_calc_traj.py
1032/5: calc_asp_angles(sc,e,cs='hg')
1032/6: e
1032/7: sc
1032/8: hg_to_rtn(e,sc,long_shift=0.)
1032/9: %run ul_calc_traj.py
1032/10: hg_to_rtn(e,sc,long_shift=0.)
1032/11: e = [1,0,0]
1032/12: hg_to_rtn(e,sc,long_shift=0.)
1032/13: e = [1,0,10.]
1032/14: hg_to_rtn(e,sc,long_shift=0.)
1032/15: e = [1,0,40.]
1032/16: hg_to_rtn(e,sc,long_shift=0.)
1032/17: e = [1,0,10.]
1032/18: hg_to_rtn(e,sc,long_shift=0.)
1032/19: %run ul_calc_traj.py
1032/20: hg_to_rtn(e,sc,long_shift=0.)
1032/21: calc_asp_angles(sc,e,cs='hg')
1032/22: e
1032/23: sc
1032/24: e = [1,0,20]
1032/25: calc_asp_angles(sc,e,cs='hg')
1032/26: e = [1,0,0]
1032/27: sc = [2,90.,10.]
1032/28: calc_asp_angles(sc,e,cs='hg')
1032/29: 360-153.4
1032/30: e = [1,0,5]
1032/31: calc_asp_angles(sc,e,cs='hg')
1032/32: e = [1,0,5]
1032/33: sc = [2,270.,10.]
1032/34: calc_asp_angles(sc,e,cs='hg')
1032/35: sc = [2,30.,10.]
1032/36: calc_asp_angles(sc,e,cs='hg')
1032/37: e
1032/38: e = [1,0,0]
1032/39: calc_asp_angles(sc,e,cs='hg')
1032/40: sc = [2,0.,10.]
1032/41: calc_asp_angles(sc,e,cs='hg')
1032/42: e
1032/43: sc
1032/44: sc = [2,10.,10.]
1032/45: calc_asp_angles(sc,e,cs='hg')
1032/46: %run ul_calc_traj.py
1032/47: calc_asp_angles(sc,e,cs='hg')
1032/48: sc = [2,-10.,10.]
1032/49: calc_asp_angles(sc,e,cs='hg')
1032/50: sc = [2,80,10.]
1032/51: calc_asp_angles(sc,e,cs='hg')
1033/1: sqrt(1)
1033/2: cos(180*2*pi/360)
1033/3:
cos(180*pi/180
)
1033/4: arccos(3)
1033/5: cos**(-1)
1033/6: cos**(-1)(3)
1033/7: arccos(1)
1034/1: %run ul_calc_traj.py
1034/2: %run ul_calc_traj.py
1034/3: %run ul_calc_traj.py
1034/4: calc_SPE(28.3,0.83)
1034/5: arccos(1)
1034/6: numpy.arccos
1034/7: numpy.arccos(1)
1035/1: calc_SPE(28.3,0.83)
1035/2: %run ul_calc_traj.py
1035/3: %run ul_calc_traj.py
1035/4: calc_SPE(28.3,0.83)
1035/5: %run ul_calc_traj.py
1035/6: calc_SPE(28.3,0.83)
1035/7: %run ul_calc_traj.py
1035/8: calc_SPE(28.3,0.83)
1035/9: numpy.pi
1035/10: calc_SPE(28.3,0.83)
1035/11: %run ul_calc_traj.py
1035/12: calc_SPE(28.3,0.83)
1035/13: %run ul_calc_traj.py
1035/14: calc_SPE(28.3,0.83)
1036/1: %run ul_calc_traj.py
1036/2: sc_sp = [2.6698,54.95,-4.04]
1036/3: e_sp = [1.002,124.2,-6.0]
1036/4: a_phi, a_theta = calc_asp_angles(sc_sp,e_sp,cs='rtn')
1036/5: e_sp - sc_sp
1036/6: e_sp = array(e_sp)
1036/7: sc_sp = array(sc_sp)
1036/8: e_sp - sc_sp
1036/9: a_phi, a_theta = calc_asp_angles(sc_sp,e_sp,cs='rtn')
1036/10: a_phi
1036/11: a_theta
1036/12: hg_to_rtn(e_sp,sc_sp,long_shift=0.)
1036/13: hg_to_rtn(sc_sp,sc_sp,long_shift=0.)
1036/14: a_phi, a_theta = calc_asp_angles(sc_sp,e_sp,cs='hg')
1036/15: a_phi
1036/16: a_theta
1036/17: calc_SPE(a_phi,a_theta)
1036/18: sc = [5.0667,265.34-180.,-22.75]
1036/19: e =[0.983,24.73,-3.04]
1036/20: a_phi, a_theta = calc_asp_angles(sc,e,cs='hg')
1036/21: calc_SPE(a_phi,a_theta)
1037/1: ls
1038/1: from traj_pooled import pool_traj_data
1038/2: pool_traj_data
1038/3: pool_traj_data()
1038/4: from traj_pooled import pool_traj_data
1038/5: pool_traj_data()
1039/1: from traj_pooled import pool_traj_data
1039/2: pool_traj_data()
1039/3: from traj_pooled import pool_traj_data
1039/4: pool_traj_data()
1040/1: from traj_pooled import pool_traj_data
1040/2: pool_traj_data()
1041/1: pool_traj_data()
1041/2: from traj_pooled import pool_traj_data
1041/3: pool_traj_data()
1042/1: from traj_pooled import pool_traj_data
1042/2: pool_traj_data()
1043/1: from traj_pooled import pool_traj_data
1043/2: pool_traj_data()
1043/3: fin_h
1044/1: %run ul_calc_traj.py
1044/2: %run traj_pooled.py
1044/3: %run traj_pooled.py
1044/4: %run traj_pooled.py
1044/5: sep_h
1044/6: sep_h[0]
1045/1: %run traj_pooled.py
1045/2: year_u
1045/3: doy_u[0]
1045/4: range(1)
1046/1: %run traj_pooled.py
1046/2: year_u-year_h
1047/1: %run traj_pooled.py
1047/2: year_u-year_h
1048/1: %run traj_pooled.py
1048/2: year_u-year_h
1048/3: len(year_u)
1048/4: len(year_h)
1048/5: 6814-6266
1049/1: %run traj_pooled.py
1049/2: year_u
1049/3: len(year_u)
1050/1: %run traj_pooled.py
1050/2: year_u
1050/3: len(year_u)
1050/4: len(year_h)
1051/1: %run traj_pooled.py
1051/2: len(year_h)
1051/3: year_u-year_h
1051/4: max(year_u-year_h)
1051/5: doy_h-doy_u
1051/6: max(doy_h-doy_u)
1051/7: esp_h-esp_u
1051/8: max(esp_h-esp_u)
1051/9: max(sep_h-sep_u)
1051/10: max(spe_h-spe_u)
1051/11: max(spe_h-sep_u)
1051/12: max(spe_h-esp_u)
1051/13: esp = esp_h-esp_u
1051/14: esp[:50]
1051/15: esp[:150]
1051/16: spe = spe_h-spe_u
1051/17: spe[:150]
1051/18: plot(range(len(spe),spe))
1051/19: spe
1051/20: len(spe)
1051/21: range(len(spe))
1051/22: plot(range(len(spe)),spe))
1051/23: plot(range(len(spe)),spe)
1051/24:
for i in range(3950,4100):
    print(spe[i])
    print(doy_h[i])
    print('\n')
1051/25:
for i in range(4000,4100):
    print(spe[i])
    print(doy_h[i])
    print('\n')
1051/26:
for i in range(4000,4100):
    print(spe[i])
    print(doy_h[i],year_h[i])
    print('\n')
1051/27: plot(range(len(spe_h)),spe_h)
1051/28: plot(range(len(spe_u)),spe_u)
1051/29: plot(range(len(spe_u)),spe_u)
1051/30: plot(range(len(spe_h)),spe_h)
1051/31: plot(range(len(spe_u)),spe_u)
1051/32: plot(range(len(spe)),spe)
1051/33:
    fig = pylab.figure()
    ax = pylab.subplot(111)
1052/1: %run traj_pooled.py
1053/1: %run traj_pooled.py
1054/1: %run traj_pooled.py
1055/1: %run traj_pooled.py
1055/2: pylab.show()
1056/1: %run traj_pooled.py
1057/1: %run traj_pooled.py
1057/2: pylab.show()
1058/1: %run traj_pooled.py
1058/2: pylab.show()
1059/1: %run traj_pooled.py
1059/2: pylab.show()
1059/3: pylab.show()
1059/4: %run traj_pooled.py
1059/5: pylab.show()
1060/1: %run traj_pooled.py
1061/1: %run traj_pooled.py
1062/1: %run traj_pooled.py
1063/1: %run traj_pooled.py
1063/2: write_new_file()
1064/1: %run traj_pooled.py
1064/2: write_new_file()
1065/1: %run traj_pooled.py
1065/2: write_new_file()
1066/1: a = ['eins','zwei','drei']
1066/2: join(a)
1067/1: %run traj_pooled.py
1067/2: write_new_file()
1067/3: %run traj_pooled.py
1067/4: write_new_file()
1067/5: %run traj_pooled.py
1067/6: write_new_file()
1067/7: %run traj_pooled.py
1067/8: write_new_file()
1067/9: %run traj_pooled.py
1067/10: write_new_file()
1067/11: %run traj_pooled.py
1067/12: write_new_file()
1068/1: %run traj_pooled.py
1068/2: %run traj_pooled.py
1068/3: write_new_file()
1068/4: f = open(path_u,'r')
1068/5: f.readline()
1068/6: f.readline()
1068/7: f.readline()
1068/8: f.readline()
1068/9: f.readline()
1068/10: f.readline()
1068/11: f.readline()
1068/12: f.readline()
1068/13: %run traj_pooled.py
1068/14: write_new_file()
1068/15: %run traj_pooled.py
1068/16: write_new_file()
1068/17: %run traj_pooled.py
1068/18: write_new_file()
1068/19: %run traj_pooled.py
1068/20: write_new_file()
1068/21: %run traj_pooled.py
1068/22: write_new_file()
1068/23: %run traj_pooled.py
1068/24: write_new_file()
1068/25: %run traj_pooled.py
1068/26: write_new_file()
1068/27: %run traj_pooled.py
1068/28: write_new_file()
1068/29: %run traj_pooled.py
1068/30: write_new_file()
1068/31: %run traj_pooled.py
1068/32: write_new_file()
1068/33: %run traj_pooled.py
1068/34: write_new_file()
1068/35: %run traj_pooled.py
1068/36: write_new_file()
1068/37: %run traj_pooled.py
1068/38: write_new_file()
1068/39: %run traj_pooled.py
1068/40: write_new_file()
1068/41: %run traj_pooled.py
1068/42: write_new_file()
1068/43: %run traj_pooled.py
1068/44: write_new_file()
1068/45: %run traj_pooled.py
1068/46: write_new_file()
1069/1: %run traj_pooled.py
1069/2: write_new_file()
1069/3: %run traj_pooled.py
1069/4: write_new_file()
1069/5: %run traj_pooled.py
1069/6: write_new_file()
1069/7: %run traj_pooled.py
1069/8: write_new_file()
1069/9: %run traj_pooled.py
1069/10: write_new_file()
1069/11: %run traj_pooled.py
1069/12: write_new_file()
1069/13: %run traj_pooled.py
1069/14: write_new_file()
1070/1: %run traj_pooled.py
1070/2: write_new_file()
1070/3: %run traj_pooled.py
1070/4: write_new_file()
1070/5: %run traj_pooled.py
1070/6: write_new_file()
1070/7: %run traj_pooled.py
1070/8: write_new_file()
1070/9: %run traj_pooled.py
1070/10: write_new_file()
1070/11: %run traj_pooled.py
1070/12: write_new_file()
1070/13: %run traj_pooled.py
1070/14: write_new_file()
1070/15: %run traj_pooled.py
1070/16: write_new_file()
1070/17: %run traj_pooled.py
1070/18: write_new_file()
1070/19: %run traj_pooled.py
1070/20: write_new_file()
1070/21: %run traj_pooled.py
1070/22: write_new_file()
1070/23: %run traj_pooled.py
1070/24: write_new_file()
1070/25: %run traj_pooled.py
1070/26: write_new_file()
1070/27: %run traj_pooled.py
1070/28: write_new_file()
1070/29: %run traj_pooled.py
1070/30: write_new_file()
1070/31: %run traj_pooled.py
1070/32: write_new_file()
1070/33: %run traj_pooled.py
1070/34: write_new_file()
1070/35: %run traj_pooled.py
1070/36: write_new_file()
1070/37: %run traj_pooled.py
1070/38: write_new_file()
1070/39: %run traj_pooled.py
1070/40: write_new_file()
1070/41: %run traj_pooled.py
1070/42: write_new_file()
1070/43: write_new_file()
1070/44: %run traj_pooled.py
1070/45: write_new_file()
1070/46: %run traj_pooled.py
1070/47: write_new_file()
1070/48: %run traj_pooled.py
1070/49: write_new_file()
1070/50: %run traj_pooled.py
1070/51: write_new_file()
1070/52: %run traj_pooled.py
1070/53: write_new_file()
1070/54: %run traj_pooled.py
1070/55: write_new_file()
1071/1: %run traj_pooled.py
1071/2: write_new_file()
1071/3: %run traj_pooled.py
1071/4: write_new_file()
1071/5: %run traj_pooled.py
1071/6: write_new_file()
1071/7: %run traj_pooled.py
1071/8: write_new_file()
1071/9: %run traj_pooled.py
1071/10: write_new_file()
1071/11: %run traj_pooled.py
1071/12: write_new_file()
1071/13: write_new_file()
1071/14: %run traj_pooled.py
1071/15: write_new_file()
1071/16: %run traj_pooled.py
1071/17: write_new_file()
1071/18: %run traj_pooled.py
1071/19: write_new_file()
1071/20: %run traj_pooled.py
1071/21: write_new_file()
1071/22: %run traj_pooled.py
1071/23: write_new_file()
1071/24: %run traj_pooled.py
1071/25: write_new_file()
1071/26: %run traj_pooled.py
1071/27: write_new_file()
1071/28: %run traj_pooled.py
1071/29: write_new_file()
1071/30: %run traj_pooled.py
1071/31: write_new_file()
1071/32: %run traj_pooled.py
1071/33: write_new_file()
1071/34: %run traj_pooled.py
1071/35: write_new_file()
1071/36: %run traj_pooled.py
1071/37: write_new_file()
1071/38: %run traj_pooled.py
1071/39: write_new_file()
1071/40: %run traj_pooled.py
1071/41: write_new_file()
1071/42: %run traj_pooled.py
1071/43: write_new_file()
1071/44: %run traj_pooled.py
1071/45: write_new_file()
1072/1: from ul_calc_traj import hg_to_hc hc_to_hg
1072/2: from ul_calc_traj import hg_to_hc
1072/3: from ul_calc_traj import hg_to_hc, hc_to_hg
1073/1: from ul_calc_traj import hg_to_hc, hc_to_hg
1073/2: vec = [1.059,49.88,1.2]
1073/3: hc_to_hg(vec)
1073/4: hc_to_hg(vec,spherical=True)
1074/1: from ul_calc_traj import hg_to_hc, hc_to_hg
1074/2: vec = [1.059,49.88,1.2]
1074/3: hc_to_hg(vec,spherical=True)
1074/4: rotate(vec,'z',-75.)
1074/5: from pylib.etCoord import *
1074/6: rotate(vec,'z',-75.)
1074/7: vec
1074/8: vec = [1.059,49.88,0]
1074/9: rotate(vec,'z',-75.)
1074/10:
cart2sph(rotate(vec,'z',-75)
)
1074/11: vec
1074/12: vec_cart = sph2cart(vec)
1074/13: vec_cart
1074/14: vec = [1.059,49.88,90]
1074/15: vec_cart = sph2cart(vec)
1074/16: vec_cart
1074/17: vec = [1.059,0,90]
1074/18: sph2cart(vec)
1074/19: sph2cart(vec,deg=True)
1075/1: from ul_calc_traj import hg_to_hc, hc_to_hg
1075/2: vec = [1.059,49.88,1.2]
1075/3: hc_to_hg(vec,spherical=True)
1075/4: from ul_calc_traj import hg_to_hc, hc_to_hg
1075/5: hc_to_hg(vec,spherical=True)
1076/1: from ul_calc_traj import hg_to_hc, hc_to_hg
1076/2: vec = [1.059,49.88,1.2]
1076/3: hc_to_hg(vec,spherical=True)
1076/4: 90-4.29
1077/1: from ul_calc_traj import hg_to_hc, hc_to_hg
1077/2: vec = [1.059,49.88,1.2]
1077/3: hc_to_hg(vec,spherical=True)
1078/1: from ul_calc_traj import hg_to_hc, hc_to_hg
1078/2: vec = [1.059,49.88,1.2]
1078/3: hc_to_hg(vec,spherical=True)
1078/4: -24-180
1078/5: -24+180
1079/1: %run traj_pooled.py
1079/2: from ul_calc_traj import hc_to_hg
1079/3: from ul_calc_traj import hc_to_hg
1079/4: vec = 1.221,73.14,1.73]
1079/5: vec = [1.221,73.14,1.73]
1079/6: vec_hg = hc_to_hg(vec)
1079/7: vec_hg
1079/8: cart2sph(vec_hg,deg=True)
1079/9: %run ul_calc_traj.py
1079/10: cart2sph(vec_hg,deg=True)
1079/11: vec_hc = [1.221,73.14,1.73]
1079/12: cart_hc = sph2cart([vec_hc[0],vec_hc[1],90-vec_hc[2]])
1079/13: cart_hc
1079/14: cart_hc = sph2cart([vec_hc[0],vec_hc[1],90-vec_hc[2]],deg=True)
1079/15: cart_hc
1079/16: int1 = rotate(cart_hc,'z',-75.062,deg=True)
1079/17: int1
1079/18: int2 = rotate(int1,'x',-7.25,deg=True)
1079/19: int2
1079/20: 178-180
1079/21: int3 = cart2sph(int2,deg=True)
1079/22: int3
1079/23: 90-int3[2]
1080/1: %run ul
1080/2: %run ul_calc_traj.py
1080/3: vec_hc = [1.221,73.14,1.73]
1080/4: hc_to_hg(vec_hc)
1080/5: hc_to_hg(vec_hc,long_shift=0.)
1080/6: %run ul_calc_traj.py
1080/7: hc_to_hg(vec_hc,long_shift=0.)
1080/8: hc_to_hg(vec_hc)
1080/9: %run ul_calc_traj.py
1080/10: vec_hg = [1.221,178.37,2.03]
1080/11: hg_to_hc(vec_hg)
1080/12: %run ul_calc_traj.py
1080/13: hg_to_hc(vec_hg)
1080/14: %run ul_calc_traj.py
1080/15: hg_to_hc(vec_hg)
1080/16: vec_hg
1080/17: sph2cart(vec_hg,deg=True)
1080/18: sph2cart([vec_hg[0],vec_hg[1],90-vec_hg[2]],deg=True)
1080/19: sph2cart([vec_hg[0],vec_hg[1],90-vec_hg[2]],deg=True)
1081/1: %run ul_calc_traj.py
1081/2: hg_to_hc(vec_hg)
1081/3: vec_hg = [1.221,178.37,2.03]
1081/4: hg_to_hc(vec_hg)
1081/5: cart_hg = sph2cart([vec_hg[0],vec_hg[1]-180,90-vec_hg[2]],deg = True])
1081/6: cart_hg = sph2cart([vec_hg[0],vec_hg[1]-180,90-vec_hg[2]],deg = True)
1081/7: cart_hg
1081/8: hc_to_hg(vec_hc)
1081/9: vec_hc = [1.221,73.14,1.73]
1081/10: hc_cart = sph2cart([vec_hc[0],vec_hc[1],90-vec_hc[2]],deg=True)
1081/11: hc_cart
1081/12: int1 = rotate(hc_cart,'z',-75.062,deg=True)
1081/13: int1
1081/14: int3 = cart2sph(int1,deg=True)
1081/15: int3
1081/16: vec_hc =[2.575,128.26,1.80]
1081/17: hc_cart = sph2cart([vec_hc[0],vec_hc[1],90-vec_hc[2]],deg=True)
1081/18: hc_cart
1081/19: int1 = rotate(hc_cart,'z',-75.062,deg=True)
1081/20: int1
1081/21: int3 = cart2sph(int1,deg=True)
1081/22: int3
1081/23: 53+180
1081/24: res1 = [int3[0],int3[1]+180,90-int3[2]]
1081/25: res1
1081/26: 233-180
1081/27: hc_cart = sph2cart([vec_hc[0],vec_hc[1]-180.,90-vec_hc[2]],deg=True)
1081/28: hc_cart
1081/29: vec_hc
1081/30: vec_hc =[2.575,128.26,90-1.8]
1081/31: vec_hc
1081/32: hc_cart = sph2cart([vec_hc[0],vec_hc[1],vec_hc[2]],deg=True)
1081/33: int1 = rotate(hc_cart,'z',-75.062,deg=True)
1081/34: int3 = cart2sph(int1,deg=True)
1081/35: int3
1081/36: int2 = rotate(int1,'x',-7.25,deg=True)
1081/37: int33 = cart2sph(int2,deg=True)
1081/38: int33
1081/39: clear all
1081/40: hg_vec = [2.575,233.18-180,-3.88]
1081/41: hg_vec
1081/42: hg_cart = sph2cart([hg_vec[0],hg_vec[1],90-hg_vec[2]])
1081/43: hg_cart
1081/44: hg_cart = sph2cart([hg_vec[0],hg_vec[1],90-hg_vec[2]],deg=True)
1081/45: hg_cart
1081/46: int1 = rotate(hc_cart,'z',75.062,deg=True)
1081/47: int2 = rotate(int1,'x',7.25,deg=True)
1081/48: int2
1081/49: int1
1081/50: hg_cart
1081/51: int1 = rotate(hg_cart,'z',75.062,deg=True)
1081/52: int1
1081/53: int2 = rotate(int1,'x',7.25,deg=True)
1081/54: int2
1081/55: cart2sph(int2,deg=True)
1081/56: 90-88.17975
1081/57: hg_cart
1081/58: int1 = rotate(hg_cart,'x',7.25,deg=True)
1081/59: int2 = rotate(int1,'z',75.062,deg=True)
1081/60: cart2sph(int2,deg=True)
1081/61: 90-88.0706
1081/62: cart2sph([0,1,0.2])
1081/63: cart2sph([0,1,0.2],deg=True)
1081/64: 90-78.69007
1081/65: int1 = rotate([0,1,0.2],'z',-75,deg=True)
1081/66: int1
1081/67: int2 = rotate(int1,'z',-30,deg=True)
1081/68: int2
1081/69: int2 = rotate(int1,'x',-30,deg=True)
1081/70: int2
1081/71: cart2sph(int2,deg=True)
1081/72: 90-87.5386
1081/73: int1 = rotate([0,1,0.2],'x',-7.25,deg=True)
1081/74: int1 = rotate([0,1,0.2],'x',-30,deg=True)
1081/75: int2 = rotate(int1,'z',-75,deg=True)
1081/76: int2
1081/77: cart2sph(int2,deg=True)
1081/78: 90-108
1081/79: vec = [0.97,0.32,0.044]
1081/80: int1 = rotate(vec,'x',30,deg=True)
1081/81: int2 = rotate(int1,'z',75,deg=True)
1081/82: int2
1081/83: vec = [0,1,0.5]
1081/84: int1 = rotate(vec,'z',-75,deg=True)
1081/85: int1
1081/86: int2 = rotate(int1,'x',-30,deg=True)
1081/87: int2
1081/88: int3 = rotate(int2,'x',30,deg=True)
1081/89: int4 = rotate(int3,'z',75,deg=True)
1081/90: int4
1081/91: vec
1081/92: int1 = rotate(vec,'x',-30,deg=True)
1081/93: int2 = rotate(int1,'z',-75,deg=True)
1081/94: int2
1081/95: int3 = rotate(int2,'z',75,deg=True)
1081/96: int4 = rotate(int3,'x',30,deg=True)
1081/97: int4
1081/98: vec = [2.575,233.18-180,90+3.88]
1081/99: vec
1081/100: vec_c = sph2cart(vec,deg=True)
1081/101: vec_c
1081/102: int 1 = rotate(vec_c,'x',7.25,deg=True)
1081/103: int1 = rotate(vec_c,'x',7.25,deg=True)
1081/104: int2 = rotate(int1,'z',-75.062,deg=True)
1081/105: int2
1081/106: int2 = rotate(int1,'z',75.062,deg=True)
1081/107: int2
1081/108: cart2sph(int2,deg=True)
1081/109: 90-88.0706
1081/110: vec_hc = [2.575,128.26,90-1.8]
1081/111: vec_hc_c = sph2cart(vec_hc,deg=True)
1081/112: vec_hc_c
1081/113: int1 = rotate(vec_hc_c,'z',-75.062,deg=True)
1081/114: int2 = rotate(int1,'x',-7.25,deg=True)
1081/115: int2
1081/116: int3 = rotate(int2,'x',7.25,deg=True)
1081/117: int4 = rotate(int3,'z',75.062,deg=True)
1081/118: int4
1081/119: int2
1081/120: cart2sph(int2,deg=True)
1082/1: %run ul_calc_traj.py
1082/2: vec = [2.575,233.18,-3.88]
1082/3: vec = [2.575,233.18-180,-3.88]
1082/4: vec
1082/5: hg_to_hc(vec)
1082/6: vec = [2.575,233.18,-3.88]
1082/7: hg_to_hc(vec,long_shift = 180.)
1083/1: %run ul_calc_traj.py
1083/2: %run ul_calc_traj.py
1083/3: plot_deviation
1083/4: plot_deviation()
1083/5: plot_deviation_hg()
1083/6: plot_deviation_hg
1083/7: cd ../pui
1083/8: cd ./pui
1083/9: pwd
1083/10: cd ...
1083/11: cd '..'
1083/12: cd '../..'
1084/1: cd './'
1084/2: cd '/'
1084/3: pwd
1084/4: cd
1084/5: ls
1085/1: cd '/pui'
1085/2: cd './pui'
1085/3: cd '../pui'
1085/4: cd '../../pui'
1085/5: cd '../../..pui'
1085/6: cd '../../../pui'
1086/1: cd '~'
1087/1: %run ul_calc_traj.py
1087/2: plot_deviation_hg()
1087/3: cd '~/pui'
1088/1: cd '~/pui/ulysses/Trajectory/'
1089/1: %run ul_calc_traj.py
1089/2: data = open('~/pui/ulysses/Trajectory/traj_data_ulysses_pool.dat','r')
1090/1: %run ul_calc_traj.py
1090/2: plot_deviation_hg()
1091/1: %run ul_calc_traj.py
1091/2: plot_deviation_hg()
1092/1: %run ul_calc_traj.py
1092/2: plot_deviation_hg()
1093/1: %run ul_calc_traj.py
1093/2: plot_deviation_hg()
1094/1: %run ul_calc_traj.py
1094/2: plot_deviation_hg()
1095/1: %run ul_calc_traj.py
1095/2: plot_deviation_hg()
1096/1: %run ul_calc_traj.py
1096/2: plot_deviation_hg()
1097/1: %run ul_calc_traj.py
1097/2: plot_deviation_hg()
1097/3: %run ul_calc_traj.py
1097/4: plot_deviation_hg()
1097/5: pylab.close('all')
1097/6: plot_deviation_hg()
1097/7: %run ul_calc_traj.py
1097/8: plot_deviation_hg()
1097/9: %run ul_calc_traj.py
1097/10: plot_deviation_hg()
1098/1: %run ul_calc_traj.py
1098/2: plot_deviation_hg()
1099/1: %run ul_calc_traj.py
1099/2: plot_deviation_hg()
1100/1: %run ul_calc_traj.py
1100/2: plot_deviation_hg()
1101/1: %run ul_calc_traj.py
1101/2: plot_deviation_hg()
1102/1: %run ul_calc_traj.py
1102/2: plot_deviation_hg()
1102/3: %run ul_calc_traj.py
1102/4: plot_deviation_hg()
1103/1: %run ul_calc_traj.py
1103/2: plot_deviation_hg()
1103/3: %run ul_calc_traj.py
1103/4: plot_deviation_hg()
1104/1: %run ul_calc_traj.py
1104/2: plot_deviation_hg()
1105/1: %run ul_calc_traj.py
1105/2: plot_deviation_hg()
1105/3: %run ul_calc_traj.py
1105/4: plot_deviation_hg()
1105/5: %run ul_calc_traj.py
1105/6: pylab.close('all')
1105/7: %run ul_calc_traj.py
1105/8: pylab.close('all')
1105/9: pylab.close('all')
1105/10: plot_deviation_hg()
1105/11: %run ul_calc_traj.py
1105/12: pylab.close('all')
1105/13: plot_deviation_hg()
1105/14: %run ul_calc_traj.py
1105/15: pylab.close('all')
1105/16: plot_deviation_hg()
1105/17: pylab.close('all')
1105/18: %run ul_calc_traj.py
1105/19: plot_deviation_hg()
1105/20: %run ul_calc_traj.py
1105/21: pylab.close('all')
1105/22: plot_deviation_hg()
1105/23: %run ul_calc_traj.py
1105/24: pylab.close('all')
1105/25: plot_deviation_hg()
1105/26: %run ul_calc_traj.py
1105/27: pylab.close('all')
1105/28: plot_deviation_hg()
1105/29: %run ul_calc_traj.py
1105/30: pylab.close('all')
1105/31: plot_deviation_hg()
1105/32: %run ul_calc_traj.py
1105/33: pylab.close('all')
1105/34: plot_deviation_hg()
1105/35: sc_vec = [3,0,0]
1105/36: e_vec = [1,-0.5,-1]
1105/37: calc_asp_angles(sc_vec,e_vec,cs="rtn")
1105/38: sc_vec =array( [3,0,0])
1105/39: e_vec = array([1,-0.5,-1])
1105/40: calc_asp_angles(sc_vec,e_vec,cs="rtn")
1105/41: e_vec = array([1,+0.5,0])
1105/42: calc_asp_angles(sc_vec,e_vec,cs="rtn")
1105/43: e_vec
1105/44: type(e_vec)
1105/45: isinstance(e_vec,list)
1105/46: isinstance(e_vec,numpy.ndarray)
1105/47: sc_vec
1105/48: phi, theta = calc_asp_angles(sc_vec,earth_vec,cs="rtn")
1105/49: phi, theta = calc_asp_angles(sc_vec,e_vec,cs="rtn")
1105/50: phi
1105/51: theta
1105/52: sc_vec = [1.059,155.19,4.29]
1105/53: e_vec = [0.992,325.88,4.08]
1105/54: calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1105/55: %run ul_calc_traj.py
1105/56: calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1105/57: phi, theta = calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1105/58: calc_SPE(phi,theta)
1106/1: %run ul_calc_traj.py
1106/2: e_vec = [0.992,325.88,4.08]
1106/3: phi, theta = calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1106/4: sc_vec = [1.059,155.19,4.29]
1106/5: phi, theta = calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1106/6: calc_SPE(phi,theta)
1107/1: %run ul_calc_traj.py
1107/2: e_vec = [0.992,325.88,4.08]
1107/3: sc_vec = [1.059,155.19,4.29]
1107/4: phi, theta = calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1107/5: calc_SPE(phi,theta)
1107/6: phi
1107/7: theta
1108/1: sc_vec = [1.059,155.19,4.29]
1108/2: e_vec = [0.992,325.88,4.08]
1108/3: %run ul_calc_traj.py
1108/4: calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1109/1: %run ul_calc_traj.py
1109/2: calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1109/3: sc_vec = [1.059,155.19,4.29]
1109/4: e_vec = [0.992,325.88,4.08]
1109/5: calc_asp_angles(sc_vec,e_vec,cs="hg",l_s = 180.)
1109/6: calc_asp_angles(sc_vec,e_vec,cs="hg",l_s_sc = 180.)
1109/7: phi, theta = calc_asp_angles(sc_vec,e_vec,cs="hg",l_s_sc = 180.)
1109/8: calc_SPE(phi,theta)
1109/9: sc_vec = [2.681,241.51,62.91]
1109/10: e_vec = [0.992, 325.59,4.11]
1109/11: phi, theta = calc_asp_angles(sc_vec,e_vec,cs="hg",l_s_sc = 180.)
1109/12: phi
1109/13: theta
1109/14: calc_SPE(phi,theta)
1111/1: from swics_collimator import collimator
1111/2: ls
1112/1: from swics_collimator import collimator
1112/2: c = collimator()
1112/3: c
1112/4: c.plot()
1113/1: range(0,45,3)
1114/1: %run swics_collimator.py
1114/2: c = collimator()
1114/3: c.plot()
1114/4: %run swics_collimator.py
1114/5: c = collimator()
1114/6: c.plot()
1114/7: c = collimator(aspphi = 0.0001, asptheta = 0.00001)
1114/8: c.plot()
1114/9: %run swics_collimator.py
1114/10: c = collimator(aspphi = 0.0001, asptheta = 0.00001)
1114/11: c.plot()
1114/12: c._calc_FoV()
1115/1: %run swics_collimator.py
1115/2: c = collimator(aspphi = 0.0001, asptheta = 0.00001)
1115/3: c.plot()
1115/4: c._calc_FoV()
1115/5: f = c._calc_FoV()
1115/6: shape(f)
1115/7: x = f[0,0,0,0]
1115/8: x
1115/9: x = f[0,0,0,10]
1115/10: x
1115/11: x = f[1,0,0,0]
1115/12: x
1115/13: sqrt(f[1,9,0,0]**2+f[1,9,1,0]**2+f[1,9,2,0]**2)
1115/14: sqrt(f[1,1,0,0]**2+f[1,1,1,0]**2+f[1,1,2,0]**2)
1115/15: c.plot_FoV()
1115/16: c.plot()
1115/17: c.plot_FoV()
1116/1: ls
1117/1: %run swics_collimator.py
1117/2: %run main2_backsub.py
1117/3: data
1117/4: shape(data)
1117/5: data.columns
1117/6: shape(data.columns)
1117/7: data.date_onset
1117/8:
for i in data.index:
    print(data.date_onset)
1117/9: clea
1117/10: rclear
1117/11: clear
1117/12: %run main2_backsub.py
1118/1: %run main2_backsub.py
1118/2: %run main2_backsub.py
1119/1: %run main2_backsub.py
1119/2: datetime.datetime(2010,1,1)
1119/3: d = datetime.datetime(2010,3,1)
1119/4: d
1119/5: type(d)
1119/6: data[0]
1119/7: data.index
1119/8: data.doy_onset[0]
1119/9: data.doy_onset[1]
1119/10: data.doy_onset[2]
1119/11:
for i in range(0,20):
    date = pd.to_datetime(data.date:onset,format="%Y-%m-%d")
1119/12:
for i in range(0,20):
    date = pd.to_datetime(data.date_onset,format="%Y-%m-%d")
    day = int(date[i].day)
    month = int(date[i].month)
    year = int(date[i].year)
    EventTime=int(data.hour_onset[i])

    date = datetime.datetime(year, month, day)
    doy = int(data.doy_onset[i])
    print(year,month,day,EventTime,doy)
1119/13:
for i in range(20):
    print(data.date_onset[i])
1119/14:
for i in range(20):
    print(data.date_onset[i])
    print(data.doy_onset[i])
1119/15:
for i in range(20):
    print(data.date_Ni_STA+[i])
    print(data.date_Ni_STB+[i])
1119/16:
for i in range(20):
    print(data.date_Ni_STA[i])
    print(data.date_Ni_STB[i])
1119/17:
for i in range(20):
    print(data.date_Ni_STA[i])
    print(data.date_Ni_STB[i])
    print('\n')
1119/18:
for i in range(20):
    print(data.date_Ni_STA[i])
    print(data.onset_Ni_STA[i])
    print(data.date_Ni_STB[i])
    print(data.date_Ni_STA[i])
    print('\n')
1119/19:
for i in range(20):
    print(data.date_Ni_STA[i])
    print(data.onset_Ni_STA[i])
    print(data.date_Ni_STB[i])
    print(data.onset_Ni_STA[i])
    print('\n')
1120/1: %run main2_backsub.py
1120/2: os.path.isdir("Output/"+str(year)):
1120/3: os.path.isdir("Output/"+str(year))
1120/4: "Output/"+str(year)
1120/5: os.path
1120/6: path
1120/7: path
1120/8: os.path
1120/9: os.path()
1120/10: os.path.basepath
1120/11: os.path.basename
1120/12: os.path.dirname
1120/13: print(os.path)
1120/14: os.path(path)
1120/15: path
1121/1: %run main2_backsub.py
1122/1: %run main2_backsub.py
1122/2: path
1122/3: pickel_path
1122/4: pickle_path
1123/1: %run main2_backsub.py
1123/2: pd.to_datetime(data.date_Ni_STA+' '+data.onset_Ni_STA,format="%Y-%m-%d %H:%M")
1123/3:
for i in range(20):
    print(data.date_Ni_STA)
1123/4: OnsetTime_A_Ni=pd.to_datetime(data.date_Ni_STA+' '+data.onset_Ni_STA,format="%Y-%m-%d %H:%M")
1123/5: OnsetTime_A_Ni[0]
1123/6: OnsetTime_A_Ni[1]
1123/7: OnsetTime_A_Ni[2]
1123/8: OnsetTime_A_Ni[0:20]
1123/9: type(OnsetTime_A_Ni[0])
1123/10: type(OnsetTime_A_Ni[10])
1123/11: type(OnsetTime_A_Ni[8])
1123/12: OnsetTime_A_Ni[8].year
1123/13: 15/1440. + 5/1440.
1123/14: 10/(60*24)
1123/15: 10/(60*24.)
1123/16: 60*24
1124/1: %run make_ani_STA_STB_plots_backsub.py
1125/1: %run make_ani_STA_STB_plots_backsub.py
1126/1: %run make_ani_STA_STB_plots_backsub.py
1127/1: %run make_ani_STA_STB_plots_backsub.py
1128/1: %run make_ani_STA_STB_plots_backsub.py
1129/1: %run make_ani_STA_STB_plots_backsub.py
1130/1: %run main2_backsub.py
1130/2: OnsetTime_A_Ni
1130/3: OnsetTime_A_Ni[8]
1130/4: OnsetTime_A_Ni[8]_hour
1130/5: OnsetTime_A_Ni[8].hour
1130/6: backsub_offset
1130/7: %run main2_backsub.py
1130/8: backsub_offset
1130/9: backsub_win
1130/10: backsub_start_A
1130/11: backsub_end_A
1130/12: backsub_start_A - backsub_end_A
1130/13: backsub_end_A
1130/14: backsub_start_A
1131/1: %run main2_backsub.py
1131/2: backsub_end_A
1131/3: backsub_start_A
1131/4: backsub_start_A - backsub_end_A
1131/5: doy = backsub_start_A - backsub_end_A
1131/6: doy *24
1131/7: doy *24 * 60
1132/1: angsteps = range(0,45,3)
1132/2: angsteps
1132/3: 0*150
1132/4: 1*150
1132/5: 2*150
1132/6: 90*5
1132/7: 450/3
1133/1: %run swics_collimator.py
1133/2: %run swics_collimator.py
1133/3: c = collimator(aspphi = 0.0001, asptheta = 0.00001)
1133/4: c.det1
1133/5: len(c.det1)
1133/6: shape(c.det1)
1133/7: c.FoV
1133/8: shape(c.FoV)
1133/9: c.FoV[0,0,0,0]
1133/10: c.FoV[0,0,0,0:20]
1133/11: shape(c.det1)
1133/12: det1[0,0]
1133/13: c.det1[0,0]
1133/14: c.det1[0,0:30]
1133/15: c.base_points
1133/16: c.det1[:,0:2]
1133/17: sqrt(c.det1[0,0]**2+c.det1[1,0]**2+c.det1[2,0]**2)
1133/18: F = c.FoV[0,0,:,0]
1133/19: F
1133/20: sqrt(F[0]**2+F[1]**2+F[2]**2)
1133/21: c.ang_perp
1133/22: shape(c.ang_perp)
1134/1: array([100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489])
1134/2:
len(array([100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489])
)
1134/3: around(1)
1134/4: around(1.445)
1134/5: around(1.0000009)
1134/6: around(1.9)
1134/7: around(1.5)
1134/8: around(1.49)
1134/9: arange(10.,30.+1.+0.0001,1.)
1134/10: arange(10.,30.+1.,1.)
1134/11: len(arange(300.,800.1,10.))
1134/12: sqrt(5.)
1134/13: sqrt(2)
1134/14: sqrt(6.**2+3.**2)
1134/15: sqrt(4.**2+3.**2)
1134/16: sqrt((4./2)**2+(3./2)**2)
1136/1: %run main2_backsub.py
1136/2: data+
1136/3: data+
1136/4: data
1137/1: %run main2_backsub.py
1138/1: %run main2_backsub.py
1138/2: len(data)
1140/1: %run main2_backsub.py
1141/1: %run main2_backsub.py
1138/3: data
1138/4: data[0]
1138/5: data.date_onset[0]
1138/6: date = pd.to_datetime(data.date_onset,format="%Y-%m-%d")
1138/7:
day = int(date[i].day)
    month = int(date[i].month)
    year = int(date[i].year)
1138/8:
day = int(date[i].day)
month = int(date[i].month)
year = int(date[i].year)
1138/9: day
1138/10: month
1138/11: year
1138/12: doy = int(data.doy_onset[0])
1138/13: doy
1138/14: data.date_onset[0]
1138/15: i
1138/16: i=0
1138/17:
day = int(date[i].day)
month = int(date[i].month)
year = int(date[i].year)
1138/18: year
1138/19: day
1138/20: date
1138/21: OnsetTime_A_Ni
1138/22: OnsetTime_A_Ni[0]
1138/23: OnsetTime_A_Ni[8]
1138/24: startDay[8]
1142/1: %run main2_backsub.py
1143/1: %run main2_backsub.py
1144/1: %run main2_backsub.py
1145/1: %run main2_backsub.py
1145/2: EventTime
1146/1: %run main2_backsub.py
1146/2: backsb_end_B
1146/3: backsub_type
1146/4: %run main2_backsub.py
1147/1: %run main2_backsub.py
1148/1: %run main2_backsub.py
1149/1: %run main2_backsub.py
1150/1: %run main2_backsub.py
1150/2: %run main2_backsub.py
1151/1: %run main2_backsub.py
1152/1: doy = np.array([5,6,7,8,9])
1152/2: doy = np.array([5,6,7])
1153/1: %run main2_backsub.py
1153/2: doy = np.arange([107,108,109])
1153/3: import numpy as np
1153/4: doy = np.arange([107,108,109])
1153/5: doy = np.arange([107,108,109])
1153/6: doy = np.array([107,108,109])
1153/7: doy
1153/8: backsub = np.array([108.809,108.809])
1153/9: np.where((doy>backsub[0]))
1153/10: a = np.arange(10)
1153/11: np.where(5>a)
1153/12: a = np.arange(10,20)
1153/13: a
1153/14: np.where(5>a)
1153/15: np.where(15>a)
1153/16: np.where((doy>backsub[0]))
1153/17: backsub
1153/18: doy
1153/19: np.where((doy > backsub[0]) & (doy < backsub[1]))
1154/1: %run STEREO_data_loader.py
1154/2: %run STEREO_data_loader.py
1155/1: %run main2_backsub.py
1155/2: data.index
1155/3: data.index.stop
1155/4: data.index(stop)
1155/5: len(data.index)
1156/1: len(data.index)
1156/2: %run main2_backsub.py
1157/1: %run main2_backsub.py
1158/1: %run main2_backsub.py
1159/1: %run main2_backsub.py
1160/1: %run main2_backsub.py
1160/2: STA_data
1160/3: doy_, I_sun_, I_asun_, I_north_, I_south_, channels, ch_string = STEREOData.sept_sec_loader_sf(sc, year, doys, res, ch = ch, par_t = par_t, corr = corr, path = path)
1161/1: %run STEREO_data_loader.py
1161/2: import STEREOData
1161/3: from STEREO_data_loader import STEREOData
1161/4: STEREOData.sept_sec_loader_sf('STA',2017,108,'1min',ch=[3,6],par_t='e',corr=0,path='')
1162/1: from STEREO_data_loader import STEREOData
1162/2: STEREOData.sept_sec_loader_sf('STA',2017,108,'1min',ch=[3,6],par_t='e',corr=0,path='')
1162/3: doy, I_sun, I_asun, I_north, I_south, channels, ch_string = STEREOData.sept_sec_loader_sf('STA',2017,108,'1min',ch=[3,6],par_t='e',corr=0,path='')
1162/4: doy
1162/5: len(doy)
1162/6: I_sun
1162/7: len(I_sun)
1162/8: channels
1162/9: ch_string
1162/10: type(doy)
1162/11: len(I_sun)
1162/12: 24*60
1162/13: doy
1162/14: backsub
1162/15: backsub = np.array([108.809,108.809])
1162/16: doy
1162/17: back_int   = np.where((doy > backsub[0]) & (doy < backsub[1]))[0]
1162/18: back_int
1163/1: %run main2_backsub.py
1164/1: %run main2_backsub.py
1165/1: %run main2_backsub.py
1166/1: %run main2_backsub.py
1167/1: %run main2_backsub.py
1162/19: backsub = np.array([108.80902777777777, 108.82291666666666])
1162/20: back_int   = np.where((doy > backsub[0]) & (doy < backsub[1]))[0]
1162/21: back_int
1168/1: import numpy as np
1168/2: np.array([1,3,4,0])
1168/3: a = np.array([1,3,4,0])
1168/4: nanmean(a)
1168/5: a = np.array([1,3,4,np.nan])
1168/6: nanmean(a)
1168/7: np.random.rand(5)
1169/1: %run test
1169/2: %run test
1169/3: %run test
1169/4: %run test
1169/5: %run test
1169/6: np.random.rand(5)
1169/7: %run test
1170/1: %run test
1170/2: %run test
1170/3: %run test
1170/4: %run test
1170/5: %run test
1170/6: %run test
1170/7: %run test
1170/8: %run test
1170/9: %run test
1170/10: %run test
1170/11: %run test
1170/12: %run test
1170/13: %run test
1170/14: %run test
1170/15: %run test
1170/16: a = np.array([1,3,4,0])
1170/17: a[0:2]
1170/18: %run test
1170/19: %run test
1170/20: %run test
1170/21: %run test
1170/22: %run test
1170/23: %run test
1170/24: %run test
1170/25: %run test
1170/26: %run test
1170/27: %run test
1170/28: %run test
1170/29: %run test
1171/1: %run test
1171/2: %run test
1171/3: %run test
1171/4: %run test
1171/5: %run test
1171/6: %run test
1171/7: %run test
1171/8: %run test
1171/9: %run test
1171/10: %run test
1171/11: %run test
1171/12: %run test
1171/13: %run test
1171/14: %run test
1171/15: %run test
1171/16: %run test
1171/17: %run test
1171/18: %run test
1171/19: %run test
1171/20: %run test
1171/21: %run test
1171/22: %run test
1171/23: %run test
1171/24: %run test
1171/25: %run test
1171/26: %run test
1171/27: %run test
1171/28: %run test
1171/29: %run test
1171/30: %run test
1171/31: %run test
1171/32: %run test
1171/33: %run test
1171/34: %run test
1171/35: %run test
1171/36: %run test
1172/1: %run main2_backsub.py
1173/1: %run main2_backsub.py
1174/1: %run main2_backsub.py
1174/2: %run main2_backsub.py
1174/3: %run main2_backsub.py
1174/4: %run main2_backsub.py
1174/5: %run main2_backsub.py
1174/6: %run main2_backsub.py
1175/1: %run main2_backsub.py
1176/1: %run main2_backsub.py
1177/1: %run main2_backsub.py
1177/2: %run main2_backsub.py
1178/1: %run main2_backsub.py
1179/1: %run main2_backsub.py
1180/1: %run main2_backsub.py
1181/1: %run main2_backsub.py
1182/1: %run main2_backsub.py
1183/1: %run main2_backsub.py
1185/1: cd ..
1185/2: %run main2_backsub.py
1186/1: %run main2_backsub.py
1187/1: %run main2_backsub.py
1188/1: %run main2_backsub.py
1188/2: %run main2_backsub.py
1189/1: %run main2_backsub.py
1190/1: %run main2_backsub.py
1191/1: %run main2_backsub.py
1191/2: clear
1191/3: %run main2_backsub.py
1192/1: %run main2_backsub.py
1193/1: %run main2_backsub.py
1194/1: %run main2_backsub.py
1195/1: %run main2_backsub.py
1196/1: %run main2_backsub.py
1197/1: %run main2_backsub.py
1198/1: %run main2_backsub.py
1199/1: %run main2_backsub.py
1200/1: %run main2_backsub.py
1200/2: a = arange(2:20)
1200/3: a = np.arange(2:20)
1200/4: a = np.arange(2,20)
1200/5: a
1200/6: a[len(a)]
1200/7: a[len(a)-1]
1200/8: a[16:len(a)-1]
1200/9: a[15:len(a)-1]
1200/10: len(a)
1200/11: a[18]
1200/12: a[17]
1200/13: a[16:17]
1200/14: a[15:17]
1200/15: a[16:18]
1200/16: len(a)
1200/17: a[16:19]
1200/18: a[16:219]
1200/19: a[16:18]
1200/20: a[-2:18]
1200/21: a[-20:18]
1200/22: a[-20:128]
1201/1: a[-20:128]
1202/1: %run main2_backsub.py
1203/1: %run main2_backsub.py
1204/1: %run main2_backsub.py
1205/1: %run main2_backsub.py
1205/2: a = np.array(82.30567676 78.94279337 80.81127094 81.84873455 81.5958316 )
1205/3: a = np.array([82.30567676, 78.94279337, 80.81127094, 81.84873455, 81.5958316])
1205/4: a
1205/5: np.nanmean(a)
1206/1: np.nanmean(a)
1206/2: %run main2_backsub.py
1207/1: %run main2_backsub.py
1208/1: %run main2_backsub.py
1208/2: 4320/5.
1208/3: 4320/7.
1209/1: 4320/7.
1209/2: %run main2_backsub.py
1209/3: 618*7.
1209/4: 4320/7.
1209/5: 617*7.
1210/1: %run main2_backsub.py
1210/2: a = np.array([82.30567676, 78.94279337, 80.81127094, 81.84873455, 81.5958316])
1210/3: a[len(a)]
1210/4: a[len(a)-10:len(a)]
1210/5: a
1211/1: a
1211/2: %run main2_backsub.py
1212/1: %run main2_backsub.py
1213/1: %run main2_backsub.py
1214/1: %run main2_backsub.py
1215/1: %run main2_backsub.py
1216/1: %run main2_backsub.py
1217/1: %run main2_backsub.py
1218/1: %run main2_backsub.py
1219/1: %run main2_backsub.py
1220/1: %run main2_backsub.py
1221/1: %run main2_backsub.py
1222/1: %run main2_backsub.py
1223/1: %run main2_backsub.py
1224/1: %run main2_backsub.py
1225/1: %run main2_backsub.py
1226/1: %run main2_backsub.py
1227/1: %run main2_backsub.py
1228/1: %run main2_backsub.py
1229/1: %run main2_backsub.py
1229/2: a = np.array([90.000243 90.000938 90.001632 90.002326 90.003021 90.003715 90.00441])
1229/3: a = np.array([90.000243, 90.000938, 90.001632, 90.002326, 90.003021, 90.003715, 90.00441])
1229/4: a
1229/5: len(a)
1229/6: np.arange(0,100,7)
1230/1: np.arange(0,100,7)
1230/2: %run main2_backsub.py
1231/1: %run main2_backsub.py
1232/1: %run main2_backsub.py
1233/1: %run main2_backsub.py
1234/1: %run main2_backsub.py
1235/1: %run main2_backsub.py
1236/1: %run main2_backsub.py
1237/1: %run main2_backsub.py
1238/1: %run main2_backsub.py
1239/1: %run main2_backsub.py
1240/1: %run main2_backsub.py
1241/1: %run main2_backsub.py
1242/1: %run main2_backsub.py
1243/1: %run main2_backsub.py
1244/1: %run main2_backsub.py
1245/1: %run main2_backsub.py
1246/1: %run main2_backsub.py
1247/1: %run main2_backsub.py
1247/2: %run main2_backsub.py
1248/1: %run main2_backsub.py
1249/1: %run main2_backsub.py
1250/1: %run main2_backsub.py
1251/1: %run main2_backsub.py
1252/1: %run main2_backsub.py
1253/1: %run main2_backsub.py
1254/1: %run main2_backsub.py
1256/1: %run main2_backsub.py
1257/1: %run main2_backsub.py
1257/2: np.arange(322,326)
1258/1: np.arange(322,326)
1258/2: %run main2_backsub.py
1259/1: %run main2_backsub.py
1260/1: %run main2_backsub.py
1261/1: %run main2_backsub.py
1262/1: %run main2_backsub.py
1263/1: %run main2_backsub.py
1263/2: a = "PICKLE"
1263/3: a = "PICKLE/"
1263/4: a[-1]
1263/5: a[0:-1]
1263/6: a[:-1]
1264/1: a[:-1]
1264/2: %run main2_backsub.py
1265/1: %run main2_backsub.py
1266/1: %run main2_backsub.py
1267/1: %run main2_backsub.py
1268/1: %run main2_backsub.py
1269/1: %run main2_backsub.py
1270/1: %run main2_backsub.py
1271/1: %run main2_backsub.py
1272/1: %run main2_backsub.py
1273/1: %run main2_backsub.py
1274/1: %run main2_backsub.py
1274/2: %run main2_backsub.py
1275/1: %run main2_backsub.py
1276/1: %run main2_backsub.py
1277/1: import numpy as np
1277/2: a = np.array([1,2,3,4,5,nan])
1277/3: np.nanmax(a)
1277/4: np.max(a)
1277/5: a - np.nanmax(a)
1277/6: diff_sun = a - np.nanmax(a)
1277/7: diff_sun = abs(a - np.nanmax(a))
1277/8: diff_sun
1277/9: ind_max = np.where(diff_sun == np.nanmin(diff_sun))
1277/10: ind_max
1277/11: a
1278/1: %run make_ani_STA_STB_plots_backsub.py
1278/2: data.index
1278/3: data.max
1278/4: data.index.max
1278/5: max(data.index)
1278/6: np.max(data.index)
1279/1: %run make_ani_STA_STB_plots_backsub.py
1280/1: %run make_ani_STA_STB_plots_backsub.py
1281/1: %run make_ani_STA_STB_plots_backsub.py
1282/1: %run make_ani_STA_STB_plots_backsub.py
1283/1: %run make_ani_STA_STB_plots_backsub.py
1284/1: %run make_ani_STA_STB_plots_backsub.py
1285/1: %run make_ani_STA_STB_plots_backsub.py
1286/1: %run make_ani_STA_STB_plots_backsub.py
1287/1: %run make_ani_STA_STB_plots_backsub.py
1288/1: %run make_ani_STA_STB_plots_backsub.py
1289/1: %run make_ani_STA_STB_plots_backsub.py
1290/1: %run make_ani_STA_STB_plots_backsub.py
1291/1: %run make_ani_STA_STB_plots_backsub.py
1293/1: %run make_ani_STA_STB_plots_backsub.py
1294/1: %run make_ani_STA_STB_plots_backsub.py
1295/1: %run make_ani_STA_STB_plots_backsub.py
1296/1: %run make_ani_STA_STB_plots_backsub.py
1297/1: %run make_ani_STA_STB_plots_backsub.py
1298/1: %run make_ani_STA_STB_plots_backsub.py
1299/1: %run main2_backsub.py
1300/1: %run main2_backsub.py
1300/2: %run make_ani_STA_STB_plots_backsub.py
1301/1: %run main2_backsub.py
1301/2: %run main2_backsub.py
1301/3: %run main2_backsub.py
1301/4: %run make_ani_STA_STB_plots_backsub.py
1302/1: %run make_ani_STA_STB_plots_backsub.py
1303/1: %run make_ani_STA_STB_plots_backsub.py
1304/1: %run make_sepangle_plot.py
1305/1: %run make_sepangle_plot.py
1306/1: %run make_sepangle_plot.py
1306/2:
for i in data_sta_backsub20.index:
    print(i)
1306/3: data_sta-nr
1306/4: data_sta.nr
1307/1: %run main2_backsub.py
1308/1: %run main2_backsub.py
1309/1: %run main2_backsub.py
1309/2: a = 1
1309/3:
if a == 1:
    c = 5.
1309/4: c
1310/1: %run main2_backsub.py
1311/1: 2+3+3+3+2+3+3+3+3+3+3+3+3+1
1310/2: %run make_ani_STA_STB_plots_backsub.py
1312/1: %run make_ani_STA_STB_plots_backsub.py
1312/2: %run make_sepangle_plot.py
1312/3: data_sta.nr
1312/4: data_sta_backsub20.nr
1312/5: np.where(data_sta.nr==data_sta_backsub20.nr[i])
1312/6:
for i in data_sta_backsub20.index:
    print(data_sta.nr)
1312/7:
for i in data_sta_backsub20.index:
    print(data_sta.nr[i],data_sta_backsub20.nr[i])
1312/8:
for i in data_sta_backsub20.index:
    print(np.where(data_sta.nr==data_sta_backsub20.nr[i])
    
    
    )
1312/9:
for i in data_sta_backsub20.index:
    if data_sta.nr[int(np.where(data_sta.nr == data_sta_backsub20.nr[i])[0])]:
        dummy = data_sta_backsub20.ani_max[i] - data_sta.ani_max[int(np.where(data_sta.nr==data_sta_backsub20.nr[i])[0])]
1312/10:
for i in data_sta_backsub20.index:
    if data_sta.nr[int(np.where(data_sta.nr == data_sta_backsub20.nr[i])[0])]:
        dummy = data_sta_backsub20.ani_max[i] - data_sta.ani_max[int(np.where(data_sta.nr==data_sta_backsub20.nr[i])[0])]
        dummy 2 = data_sta_backsub20.ani_max[i] - data.sta.ani_max[i]
1312/11:
for i in data_sta_backsub20.index:
    if data_sta.nr[int(np.where(data_sta.nr == data_sta_backsub20.nr[i])[0])]:
        dummy = data_sta_backsub20.ani_max[i] - data_sta.ani_max[int(np.where(data_sta.nr==data_sta_backsub20.nr[i])[0])]
        dummy2 = data_sta_backsub20.ani_max[i] - data.sta.ani_max[i]
        print(dummy, dummy2)
1312/12:
for i in data_sta_backsub20.index:
    if data_sta.nr[int(np.where(data_sta.nr == data_sta_backsub20.nr[i])[0])]:
        dummy = data_sta_backsub20.ani_max[i] - data_sta.ani_max[int(np.where(data_sta.nr==data_sta_backsub20.nr[i])[0])]
        dummy2 = data_sta_backsub20.ani_max[i] - data_sta.ani_max[i]
        print(dummy, dummy2)
1312/13:
for i in data_sta_backsub20.index:
    if data_sta.nr[int(np.where(data_sta.nr == data_sta_backsub20.nr[i])[0])]:
        dummy = data_sta_backsub20.ani_max[i] - data_sta.ani_max[int(np.where(data_sta.nr==data_sta_backsub20.nr[i])[0])]
        dummy2 = data_sta_backsub20.ani_max[i] - data_sta.ani_max[i]
        print(dummy- dummy2)
1312/14: np.array
1313/1: %run make_sepangle_plot.py
1314/1: %run make_sepangle_plot.py
1315/1: %run make_sepangle_plot.py
1316/1: %run make_sepangle_plot.py
1317/1: %run make_sepangle_plot.py
1318/1: %run make_ani_STA_STB_plots_backsub.py
1318/2: %run make_ani_STA_STB_plots_backsub.py
1319/1: %run make_ani_STA_STB_plots_backsub.py
1320/1: %run make_ani_STA_STB_plots_backsub.py
1321/1: %run make_ani_STA_STB_plots_backsub.py
1322/1: %run make_ani_STA_STB_plots_backsub.py
1323/1: %run make_ani_STA_STB_plots_backsub.py
1324/1: %run make_ani_STA_STB_plots_backsub.py
1325/1: %run make_ani_STA_STB_plots_backsub.py
1326/1: %run make_ani_STA_STB_plots_backsub.py
1327/1: %run make_ani_STA_STB_plots_backsub.py
1328/1: %run make_ani_STA_STB_plots_backsub.py
1329/1: %run make_ani_STA_STB_plots_backsub.py
1330/1: %run make_ani_STA_STB_plots_backsub.py
1331/1: %run make_ani_STA_STB_plots_backsub.py
1332/1: %run make_ani_STA_STB_plots_backsub.py
1333/1: %run make_ani_STA_STB_plots_backsub.py
1334/1: %run make_ani_STA_STB_plots_backsub.py
1335/1: %run make_ani_STA_STB_plots_backsub.py
1336/1: %run make_ani_STA_STB_plots_backsub.py
1337/1: %run make_ani_STA_STB_plots_backsub.py
1338/1: %run make_ani_STA_STB_plots_backsub.py
1339/1: %run make_ani_STA_STB_plots_backsub.py
1340/1: %run make_ani_STA_STB_plots_backsub.py
1341/1: %run make_ani_STA_STB_plots_backsub.py
1342/1: %run make_ani_STA_STB_plots_backsub.py
1343/1: %run make_ani_STA_STB_plots_backsub.py
1344/1: %run make_ani_STA_STB_plots_backsub.py
1345/1: %run make_ani_STA_STB_plots_backsub.py
1346/1: %run make_ani_STA_STB_plots_backsub.py
1347/1: %run make_ani_STA_STB_plots_backsub.py
1348/1: %run make_ani_STA_STB_plots_backsub.py
1348/2: %run make_ani_STA_STB_plots_backsub.py
1349/1: %run make_ani_STA_STB_plots_backsub.py
1350/1: %run make_ani_STA_STB_plots_backsub.py
1351/1: %run make_ani_STA_STB_plots_backsub.py
1352/1: %run make_ani_STA_STB_plots_backsub.py
1353/1: %run make_ani_STA_STB_plots_backsub.py
1353/2: pylab.close('all')
1354/1: pylab.close('all')
1354/2: %run make_ani_STA_STB_plots_backsub.py
1355/1: %run make_ani_STA_STB_plots_backsub.py
1356/1: %run make_ani_STA_STB_plots_backsub.py
1357/1: %run make_ani_STA_STB_plots_backsub.py
1358/1: %run make_ani_STA_STB_plots_backsub.py
1359/1: %run make_ani_STA_STB_plots_backsub.py
1360/1: %run make_ani_STA_STB_plots_backsub.py
1361/1: %run make_ani_STA_STB_plots_backsub.py
1362/1: %run make_ani_STA_STB_plots_backsub.py
1363/1: %run make_ani_STA_STB_plots_backsub.py
1364/1: %run make_ani_STA_STB_plots_backsub.py
1365/1: %run make_ani_STA_STB_plots_backsub.py
1366/1: %run make_ani_STA_STB_plots_backsub.py
1367/1: %run make_ani_STA_STB_plots_backsub.py
1368/1: %run make_ani_STA_STB_plots_backsub.py
1369/1: %run make_ani_STA_STB_plots_backsub.py
1370/1: %run make_ani_STA_STB_plots_backsub.py
1371/1: %run make_ani_STA_STB_plots_backsub.py
1372/1: %run make_ani_STA_STB_plots_backsub.py
1373/1: %run make_ani_STA_STB_plots_backsub.py
1374/1: %run make_ani_STA_STB_plots_backsub.py
1375/1: %run make_ani_STA_STB_plots_backsub.py
1376/1: %run make_ani_STA_STB_plots_backsub.py
1377/1: %run make_ani_STA_STB_plots_backsub.py
1377/2: %run make_ani_STA_STB_plots_backsub.py
1378/1: %run make_sepangle_plot.py
1378/2: %run make_sepangle_plot.py
1379/1: %run make_sepangle_plot.py
1380/1: %run make_sepangle_plot.py
1380/2: %run make_sepangle_plot.py
1381/1:
import numpy as np
import matplotlib.pyplot as plt
#import pylab as plb
#from STEREO_loaders import *
#from other_loaders import *
import ani_index_sept_backsub as ani_index_sept 
from DataLoadersNew import STEREO_data_loader
import datetime
import cPickle
import os
import pandas as pd
from Functions import my_func_new as myfunc
import csv
d = ani_index_sept.ani_index_sept()
1382/1:
import numpy as np
import matplotlib.pyplot as plt
#import pylab as plb
#from STEREO_loaders import *
#from other_loaders import *
import ani_index_sept_backsub as ani_index_sept 
from DataLoadersNew import STEREO_data_loader
import datetime
import cPickle
import os
import pandas as pd
from Functions import my_func_new as myfunc
import csv
d = ani_index_sept.ani_index_sept()
1382/2: d
1383/1:
import numpy as np
import matplotlib.pyplot as plt
#import pylab as plb
#from STEREO_loaders import *
#from other_loaders import *
import ani_index_sept_backsub as ani_index_sept 
from DataLoadersNew import STEREO_data_loader
import datetime
import cPickle
import os
import pandas as pd
from Functions import my_func_new as myfunc
import csv
d = ani_index_sept.ani_index_sept()
1384/1: %run make_ani_STA_STB_plots_backsub.py
1384/2: d
1384/3: d.zusatz
1384/4: d.year
1384/5: d.date
1384/6: d.backsub_time
1385/1: d.backsub_time
1385/2: %run make_ani_STA_STB_plots_backsub.py
1385/3: d
1385/4: d.date
1385/5: d.backsub_time
1388/1: %run make_ani_STA_STB_plots_backsub.py
1389/1: %run make_ani_STA_STB_plots_backsub.py
1390/1: %run make_ani_STA_STB_plots_backsub.py
1390/2: d
1390/3: d.date
1390/4: d.backsub_time
1391/1: %run make_ani_STA_STB_plots_backsub.py
1391/2: d.backsub_time
1391/3: d.I_data
1392/1: d.I_data
1392/2: %run make_ani_STA_STB_plots_backsub.py
1392/3: d.backsub_time
1392/4: d.I_data
1391/4: a = d.I_data
1391/5: %run make_ani_STA_STB_plots_backsub.py
1391/6: d.backsub_time
1391/7: b = d.I_data
1391/8: a-b
1391/9: a-b[0]
1391/10: a-b[:,0]
1391/11: shape(a)
1391/12: shape(b)
1391/13: a[:,0]-b[:,0]
1391/14: a[:,1]-b[:,1]
1391/15: a[:,2]-b[:,2]
1393/1: %run make_ani_STA_STB_plots_backsub.py
1393/2: d.backsub_time
1393/3: b = d.I_data
1393/4: %run make_ani_STA_STB_plots_backsub.py
1393/5: d.backsub_time
1393/6: a = d.I_data
1393/7: shape(a)
1393/8: shape(b)
1393/9: a[:,0]-b[:,0]
1393/10: a[:,2]-b[:,2]
1393/11: d.backsub_time
1393/12: d.backsub
1394/1: %run make_ani_STA_STB_plots_backsub.py
1394/2: d
1394/3: d.backsub_time
1394/4: d.backsub
1394/5: wid = d.backsub[i] - d.backsub[0]
1394/6: wid = d.backsub[1] - d.backsub[0]
1394/7: wid
1391/16: d.backsub_time
1391/17: d.backsub
1391/18: wid = d.backsub[1] - d.backsub[0]
1391/19: wid
1395/1: %run make_ani_STA_STB_plots_backsub.py
1395/2: %run make_ani_STA_STB_plots_backsub.py
1396/1: %run make_ani_STA_STB_plots_backsub.py
1397/1: %run main2_backsub.py
1397/2: STA_data
1398/1: STA_data
1398/2: %run main2_backsub.py
1398/3: STA_data
1399/1: %run main2_backsub.py
1399/2: STA_data
1400/1: STA_data
1400/2: %run main2_backsub.py
1401/1: %run main2_backsub.py
1402/1: %run main2_backsub.py
1403/1: %run main2_backsub.py
1403/2: STA_data
1403/3: sept_dic,backsub_average = STEREOData.sept_sec_loader(sc, year, doy1, "1min", doy2 = doy2, corr = corr, ch = ch, par_t = par_t, backsub = backsub)
1403/4: sept_dic,backsub_average = STA_data.sept_sec_loader(sc, year, doy1, "1min", doy2 = doy2, corr = corr, ch = ch, par_t = par_t, backsub = backsub)
1403/5: sept_dic,backsub_average = STA_data.sept_sec_loader(sc, year, doy1, "1min", doy2 = doy2, corr = corr, ch = ch, par_t = par_t, backsub = backsub)
1403/6: d.name
1403/7: d = STA.data
1403/8: d = STA_data
1403/9: d.name
1403/10: sept_dic,backsub_average = STA_data.sept_sec_loader(d.name, d.year,d.__ doy1__, "1min", d-__doy2__, corr = corr, ch = ch, par_t = par_t, backsub = backsub)
1404/1: %run main2_backsub.py
1405/1: %run main2_backsub.py
1405/2: a
1406/1: a
1406/2: %run main2_backsub.py
1406/3: STA_data.dic
1406/4: STA_data.bs_av
1406/5: I_no = STA_data.dic['I_data']
1406/6: I_no
1406/7: %run main2_backsub.py
1406/8: I_20 = STA_data.dic['I_data']
1406/9: STA_data.bs_av
1406/10: bs = STA_data.bs_av
1406/11: shape(I_20)
1406/12: I_20[:,0] - I_no[:,0]
1406/13: diff = I_20[:,0] - I_no[:,0]
1406/14: plot(range(len(diff)),diff)
1406/15: plot(range(len(diff)),diff)
1406/16: ax = plot(range(len(diff)),diff)
1406/17: ax.ylim[-10,10]
1406/18: ax.set_ylim[-10,10]
1406/19: ax.set_yrange[-10,10]
1406/20: ax =fig.gca()
1406/21: f, ax = plt.subplots(panels, sharex=True, sharey=False, figsize=(8.3, 11.7))
1406/22: f, ax = plt.subplots(sharex=True, sharey=False, figsize=(8.3, 11.7))
1406/23: ax.set_ylim[-10,10]
1406/24: ax.set_ylim(-10,10)
1406/25: pylab.show()
1406/26: ax.plot(range(len(diff)),diff)
1406/27: pylab.show()
1406/28: pylab.close('all')
1406/29: np.min(diff)
1406/30: np.nanmin(diff)
1406/31: np.nanmax(diff)
1408/1: %run main2_backsub.py
1409/1: %run main2_backsub.py
1409/2: STA_data
1409/3: STA_data.I_data
1409/4: shape(STA_data.I_data)
1409/5: STA_data.backsub_average
1409/6: bs20 = STA_data.backsub_average
1409/7: I20 = STA_data.I_data
1409/8: %run main2_backsub.py
1409/9: Ino = STA_data.I_data
1409/10: bsno = STA_data.backsub_average
1409/11: bsno
1409/12: Ino
1409/13: I20
1409/14: Ino - I20
1409/15: diff = Ino - I20
1409/16: plot(range(len(diff)),diff)
1409/17: plot(range(len(diff)),diff-20)
1409/18: pylab.close('all')
1409/19: plot(range(len(diff)),Ino)
1409/20: pylab.close('all')
1409/21: plot(range(len(diff)),Ino[:,0])
1409/22: plot(range(len(diff)),I20[:,0])
1409/23: diff = I_20[:,0] - I_no[:,0]
1409/24: diff = I20[:,0] - Ino[:,0]
1409/25: plot(range(len(diff)),diff)
1409/26: bsno
1409/27: ns20
1409/28: bs20
1409/29: pylab.close('all')
1409/30: plot(range(len(diff)),diff)
1410/1: %run main2_backsub.py
1411/1: %run main2_backsub.py
1412/1: %run main2_backsub.py
1413/1: %run main2_backsub.py
1414/1: %run main2_backsub.py
1415/1: %run main2_backsub.py
1416/1: %run main2_backsub.py
1417/1: %run main2_backsub.py
1418/1: %run main2_backsub.py
1418/2: %run main2_backsub.py
1419/1: %run main2_backsub.py
1420/1: %run main2_backsub.py
1421/1: %run main2_backsub.py
1422/1: %run main2_backsub.py
1423/1: %run main2_backsub.py
1424/1: %run main2_backsub.py
1425/1: %run main2_backsub.py
1426/1: %run main2_backsub.py
1426/2: SAP_data
1426/3: STA_data
1426/4: STA_data.I_data
1426/5: shape(STA_data.I_data)
1427/1: %run main2_backsub.py
1427/2: print(shape(STA_data.I_data))
1428/1: %run main2_backsub.py
1429/1: %run main2_backsub.py
1430/1: %run main2_backsub.py
1431/1: %run main2_backsub.py
1432/1: %run main2_backsub.py
1433/1: %run main2_backsub.py
1434/1: %run main2_backsub.py
1434/2: STA_data
1434/3: STA_data.I_data.shape
1435/1: STA_data.I_data.shape
1435/2: %run main2_backsub.py
1436/1: %run main2_backsub.py
1436/2: %run main2_backsub.py
1437/1: %run main2_backsub.py
1437/2: %run main2_backsub.py
1438/1: %run main2_backsub.py
1439/1: %run main2_backsub.py
1440/1: %run main2_backsub.py
1440/2: %run main2_backsub.py
1441/1: %run main2_backsub.py
1442/1: %run main2_backsub.py
1442/2: 60*24
1442/3: 2.5/1440
1442/4: 15.000127+0.001736
1443/1: 15.000127+0.001736
1443/2: %run main2_backsub.py
1443/3: 5/1440
1443/4: 5/1440.
1443/5: 15.000127+0.0034722222
1443/6: %run main2_backsub.py
1443/7: %run main2_backsub.py
1443/8: %run main2_backsub.py
1444/1: %run main2_backsub.py
1445/1: %run main2_backsub.py
1446/1: %run main2_backsub.py
1446/2: np.mean([14.89132501 12.88952326 18.93929235 16.30291733 16.21430505])
1446/3: np.mean(np.array([14.89132501 12.88952326 18.93929235 16.30291733 16.21430505]))
1446/4: np.mean(np.array([14.89132501, 12.88952326, 18.93929235, 16.30291733, 16.21430505]))
1447/1: np.mean(np.array([14.89132501, 12.88952326, 18.93929235, 16.30291733, 16.21430505]))
1447/2: %run main2_backsub.py
1448/1: %run main2_backsub.py
1448/2: np.mean([4.41021225      ,   nan,  6.03098725, 15.91151225,  4.71793725])
1448/3: np.nanmean([4.41021225      ,   nan,  6.03098725, 15.91151225,  4.71793725])
1449/1: %run main2_backsub.py
1449/2: np.mean([4.41021225,6.03098725, 15.91151225,  4.71793725])
1450/1: np.mean([4.41021225,6.03098725, 15.91151225,  4.71793725])
1450/2: %run main2_backsub.py
1450/3: %run main2_backsub.py
1451/1: %run main2_backsub.py
1452/1: %run main2_backsub.py
1453/1: %run main2_backsub.py
1454/1: %run main2_backsub.py
1455/1: %run main2_backsub.py
1456/1: %run main2_backsub.py
1457/1: %run main2_backsub.py
1458/1: %run main2_backsub.py
1459/1: %run main2_backsub.py
1460/1: %run main2_backsub.py
1461/1: %run main2_backsub.py
1462/1: %run main2_backsub.py
1463/1: %run main2_backsub.py
1464/1: %run main2_backsub.py
1465/1: %run main2_backsub.py
1466/1: %run main2_backsub.py
1467/1: %run main2_backsub.py
1468/1: %run main2_backsub.py
1469/1: %run main2_backsub.py
1470/1: %run main2_backsub.py
1470/2: STA_data
1470/3: STA_data.I_data
1470/4: STA_data.I_data_old
1470/5: STA_data.I_data_av
1470/6: STA_data.I_data_old_av
1470/7: i = STA_data.I_data[:,0]
1470/8: i
1470/9: io = STA_data.I_data_old
1470/10: io
1470/11: len(i)
1470/12: len(io)
1470/13: shape(io)
1470/14: shape(i)
1470/15: io = STA_data.I_data_old[:,0]
1470/16: io
1470/17: shape(io)
1470/18: i_a = STA_data.I_data_av[:,0]
1470/19: io_a = STA_data.I_data_old_av
1470/20: shape(io_a)
1470/21: shape(i_a)
1470/22: i_a
1470/23: io_a
1470/24: io_a = STA_data.I_data_old_av[:,0]
1470/25: io_a
1470/26: shape(i_a)
1470/27: shape(io_a)
1470/28: i[0:10]
1470/29: io[0:10]
1470/30: io[0:10]-i[0:10]
1470/31: io_a[0:10]-i_a[0:10]
1470/32: io_a
1470/33: io_a[0:10]
1470/34: i_a[0:10]
1470/35: io[0:10]
1470/36: o[0:10]
1470/37: i[0:10]
1470/38: i_o
1470/39: io
1470/40: i
1470/41: io[0:6]
1470/42: i[0:6]
1470/43:
np.nanmean([4.41021225,         nan,  6.03098725, 15.91151225,  4.71793725,
               nan])
1470/44: np.nanmean([4.41021225, 6.03098725, 15.91151225,  4.71793725])
1470/45: np.nanmean([11.50105 ,  0.      , 13.121825, 23.00235 , 11.808775,  4.94026 ])
1470/46: np.nanmean([11.50105  , 13.121825, 23.00235 , 11.808775,  4.94026 ])
1470/47: np.nanmean([11.50105  , 13.121825, 23.00235 , 11.808775 ])
1470/48: np.nanmean([0,1,3])
1470/49: np.nanmean([nan,1,3])
1470/50: np.nanmean([-1,1,3])
1470/51: io
1470/52: i
1472/1: i
1472/2: %run main2_backsub.py
1472/3: STA_data
1472/4: STA_data.mu_data
1472/5: STA_data.mu_data_old
1472/6: STA_data.mu_data_old - STA_data.mu_data
1472/7: STA_data.doy - STA_data.pad_doy
1472/8: STA_data.doy
1472/9: STA_data.pad_doy
1472/10: STA_data.I_data
1472/11: STA_data.I_data_old
1472/12: STA_data.I_data_old - STA_dta.I_data_old
1472/13: STA_data.I_data_old - STA_data.I_data_old
1472/14: diff = STA_data.I_data_old - STA_data.I_data_old
1472/15: np.nanmin(diff)
1472/16: diff = STA_data.I_data_old - STA_data.I_data
1472/17: diff
1472/18: np.nanmin(diff)
1472/19: np.nanmax(diff)
1473/1: %run main2_backsub.py
1474/1: %run main2_backsub.py
1475/1: %run main2_backsub.py
1476/1: %run main2_backsub.py
1477/1: %run main2_backsub.py
1478/1: %run main2_backsub.py
1479/1: I_a = STA_data.I_data_old
1479/2: STA_data
1479/3: %run main2_backsub.py
1479/4: STA_data
1479/5: I_a = STA_data.I_data_old
1479/6: I_a_backsub = STA_data.I_data
1479/7: I_a[0:10]
1479/8: I_a_backsub[0:10]
1479/9: %run main2_backsub.py
1479/10: I_backsub = STA_data.I_data
1479/11: I = STA_data.I_data_old
1479/12: I[0:20]
1479/13: I[:5]
1479/14: I[0:20,0]
1479/15: I[:5,0]
1479/16: I_a[:5,0]
1479/17: np.mean(11.50105 ,  0.      , 13.121825, 23.00235 , 11.808775)
1479/18: np.mean([11.50105 ,  0.      , 13.121825, 23.00235 , 11.808775])
1479/19: I_a_backsub[0:5,0]
1479/20: I_a[0:25,0]
1479/21: I-I_backsub
1479/22: I_a-I_backsub_a
1479/23: I_a-I_a_backsub
1479/24: I_a[:,0]-I_a_backsub[:,0]
1479/25: diff_a = I_a[:,0]-I_a_backsub[:,0]
1479/26: diff = I[:,0]-I_backsub[:,0]
1479/27: diff
1479/28: max(diff)
1479/29: min(diff)
1479/30: min(diff_a)
1479/31: max(diff_a)
1479/32: I_a-I_a_backsub
1479/33: diff_a = I_a-I_a_backsub
1479/34: np.nanmax(diff_a)
1479/35: np.nanmin(diff_a)
1479/36: np.nanmin(diff_a[:,0])
1479/37: np.nanmin(diff_a[:,1])
1479/38: np.nanmin(diff_a[:,2])
1479/39: np.nanmin(diff_a[:,3])
1480/1: np.nanmin(diff_a[:,3])
1480/2: %run main2_backsub.py
1481/1: %run main2_backsub.py
1482/1: %run main2_backsub.py
1483/1: %run main2_backsub.py
1484/1: %run main2_backsub.py
1485/1: %run main2_backsub.py
1486/1: %run main2_backsub.py
1487/1: %run make_ani_STA_STB_plots_backsub.py
1488/1: %run make_ani_STA_STB_plots_backsub.py
1489/1: %run make_ani_STA_STB_plots_backsub.py
1489/2: pylab.close('all')
1490/1: pylab.close('all')
1490/2: %run make_ani_STA_STB_plots_backsub.py
1491/1: %run make_ani_STA_STB_plots_backsub.py
1491/2: %run make_sepangle_plot.py
1492/1: %run make_sepangle_plot.py
1493/1: %run make_sepangle_plot.py
1494/1: %run make_sepangle_plot.py
1494/2: %run make_ani_STA_STB_plots_backsub.py
1495/1: %run make_ani_STA_STB_plots_backsub.py
1495/2: %run make_ani_STA_STB_plots_backsub.py
1495/3: %run make_sepangle_plot.py
1496/1: %run make_ani_STA_STB_plots_backsub.py
1496/2: d
1496/3: d.year
1496/4: d.backsub
1496/5: d.backsub_average
1496/6: d.A
1496/7: d.backsub_time
1497/1: %run make_ani_STA_STB_plots_backsub.py
1498/1: %run make_ani_STA_STB_plots_backsub.py
1499/1: %run main2_backsub.py
1501/1: %run main2_backsub.py
1501/2: %run main2_backsub.py
1502/1: %run main2_backsub.py
1502/2: %run main2_backsub.py
1502/3: %run main2_backsub.py
1503/1: %run main2_backsub.py
1503/2: 4320/8.
1503/3: 4320/5.
1503/4: %run main2_backsub.py
1504/1: %run main2_backsub.py
1505/1: %run main2_backsub.py
1505/2: %run make_ani_STA_STB_plots_backsub.py
1506/1: %run make_ani_STA_STB_plots_backsub.py
1507/1: %run make_ani_STA_STB_plots_backsub.py
1507/2: %run make_sepangle_plot.py
1508/1: %run make_ani_STA_STB_plots_backsub.py
1508/2: %run make_sepangle_plot.py
1509/1: %run make_sepangle_plot.py
1510/1: %run make_ani_STA_STB_plots_backsub.py
1510/2: %run make_sepangle_plot.py
1511/1: %run make_ani_STA_STB_plots_backsub.py
1512/1: %run make_ani_STA_STB_plots_backsub.py
1513/1: %run make_ani_STA_STB_plots_backsub.py
1514/1: %run make_ani_STA_STB_plots_backsub.py
1515/1: %run make_ani_STA_STB_plots_backsub.py
1515/2: STB_data
1515/3: d
1515/4: d.date
1515/5: d.year
1516/1: d.year
1516/2: %run make_ani_STA_STB_plots_backsub.py
1516/3: d
1516/4: d.year
1517/1: d.year
1517/2: %run make_ani_STA_STB_plots_backsub.py
1517/3: d.year
1517/4: d
1518/1: %run make_ani_STA_STB_plots_backsub.py
1519/1: %run make_ani_STA_STB_plots_backsub.py
1520/1: %run make_ani_STA_STB_plots_backsub.py
1521/1: %run make_ani_STA_STB_plots_backsub.py
1521/2: d
1521/3: d.year
1521/4: d.dat
1521/5: d.date
1521/6: d.sc
1521/7: d.backsub_average
1522/1: %run main2_backsub.py
1523/1: %run make_ani_STA_STB_plots_backsub.py
1524/1: %run make_ani_STA_STB_plots_backsub.py
1525/1: %run make_sepangle_plot.py
1526/1: %run make_sepangle_plot.py
1527/1: %run make_sepangle_plot.py
1528/1: %run make_sepangle_plot.py
1529/1: %run make_sepangle_plot.py
1530/1: %run make_sepangle_plot.py
1531/1: %run make_sepangle_plot.py
1531/2: data
1531/3: data_sta_backsub20_first
1531/4: data_sta_backsub20
1532/1: %run make_ani_STA_STB_plots_backsub.py
1533/1: %run make_ani_STA_STB_plots_backsub.py
1534/1: %run make_ani_STA_STB_plots_backsub.py
1534/2: d
1535/1: %run make_ani_STA_STB_plots_backsub.py
1536/1: %run make_sepangle_plot.py
1537/1: A = [[2,3],[4,5]]
1537/2: A
1537/3: import numpy as np
1537/4: A = np.array(A)
1537/5: B = A*2
1537/6: A
1537/7: B
1537/8: A-B/((A+B)^)
1537/9: A-B/((A+B)**2)
1537/10: A-B/((A+B)**(1/2))
1537/11: A-B/((A+B)**(1/2.))
1537/12: z = np.arange(27).reshape(3,3,3)
1537/13: z
1537/14: z[1,:,:]
1537/15: z[0,:,:]
1537/16: z = np.arange(81).reshape(3,3,3,3)
1537/17: z
1537/18: z = np.arange(120).reshape(3,5,8)
1537/19: z
1537/20: z = np.arange(81).reshape(3,3,3,3)
1537/21: z
1538/1: %run dist3D.py
1538/2: d
1538/3: d = uswipha(year=[1999],tf='all')
1538/4: from pylib import dbData
1538/5: d = uswipha(year=[1999],tf='all')
1539/1: %run uwipha
1539/2: %run uswipha.py
1539/3: from dist3d.py import Dist3d
1540/1: from uswipha import uswipha
1540/2: %run uswipha.py
1540/3: ls
1541/1: %run uswipha.py
1541/2: from uswipha import uswipha
1541/3: import uswipha
1541/4: import uswipha.py
1541/5: ls
1541/6: pwd
1542/1: import uswipha.py
1542/2: import uswipha
1542/3: import history_alex_plot
1543/1: import uswipha
1543/2: from swics/software import uswipha
1543/3: cd swics/
1543/4: from software import uswipha
1543/5: cd software/
1543/6: ls
1543/7: from libulpy import uswipha
1544/1: from swics.software.libulpy.uswipha import uswipha
1544/2: d = uswipha(year=[1999],tf='all')
1544/3: ls
1544/4: cd ../Ulysses/
1544/5: ls
1546/1: from Ulysses.swics
1546/2: from dist3D import Dist2D
1546/3: from dist3D import Dist3D
1547/1: cd swics/trunk/ace_dbd/
1547/2: ls
1547/3: from dist3D import Dist3D
1548/1: from swics.trunk.ace_dbd.dist3D import Dist3D
1549/1: from swics.trunk.ace_dbd.dist3D import Dist3D
1549/2: import numpy
1549/3: numpy.version.version
1550/1: cd PUI
1550/2: ls
1550/3: from swics.trunk.ace_dbd.dist3D import Dist3D
1550/4: from Ulysses.swics.software.libulpy.uswipha import uswipha
1550/5: d = uswipha(year=[1999],tf='all')
1550/6: Dist = Dist3D(d)
1551/1: from Ulysses.swics.software.libulpy.uswipha import uswipha
1551/2: from swics.trunk.ace_dbd.dist3D import Dist3D
1551/3: d = uswipha(year=[1999],tf='all')
1552/1: from ulysses_traj impot ulysses_traj
1552/2: from ulysses_traj import ulysses_traj
1552/3: t = ulysses_traj
1552/4: t
1552/5: t.timeframe
1552/6: t.calc_d90
1552/7: t.calc_d90()
1552/8: calc_d90(t)
1552/9: t = ulysses_traj(year=[2007],tf='all)
1552/10: t = ulysses_traj(year=[2007],tf='all')
1552/11: t = ulysses_traj(year=[2007],tf='all')
1553/1: t = ulysses_traj(year=[2007],tf='all')
1553/2: from ulysses_traj import ulysses_traj
1553/3: t = ulysses_traj(year=[2007],tf='all')
1553/4: fin
1554/1: t = ulysses_traj(year=[2007],tf='all')
1554/2: from ulysses_traj import ulysses_traj
1554/3: t = ulysses_traj(year=[2007],tf='all')
1555/1: from ulysses_traj import ulysses_traj
1555/2: t = ulysses_traj(year=[2007],tf='all')
1556/1: t = ulysses_traj(year=[2007],tf='all')
1556/2: from ulysses_traj import ulysses_traj
1556/3: t = ulysses_traj(year=[2007],tf='all')
1557/1: from ulysses_traj import ulysses_traj
1557/2: t = ulysses_traj(year=[2007],tf='all')
1557/3: from ulysses_traj import ulysses_traj
1557/4: t = ulysses_traj(year=[2007],tf='all')
1558/1: from ulysses_traj import ulysses_traj
1558/2: t = ulysses_traj(year=[2007],tf='all')
1558/3: k = ['Year', 'DOY', 'MM', 'DD', 'JD', 'ESP', 'SPE', 'SEP', 'R', 'HC_Lat', 'HC_Long', 'HG_Lat', 'HG_Long', 'HG_Long_wrt_E']
1558/4:
for key in k:
    print(key)
    print(key.split())
1558/5: t.data
1558/6: t.keys
1559/1: t.data
1559/2: from ulysses_traj import ulysses_traj
1559/3: t = ulysses_traj(year=[2007],tf='all')
1560/1: from ulysses_traj import ulysses_traj
1560/2: t = ulysses_traj(year=[2007],tf='all')
1561/1: from ulysses_traj import ulysses_traj
1561/2: t = ulysses_traj(year=[2007],tf='all')
1562/1: from ulysses_traj import ulysses_traj
1562/2: t = ulysses_traj(year=[2007],tf='all')
1563/1: t = ulysses_traj(year=[2007],tf='all')
1563/2: from ulysses_traj import ulysses_traj
1563/3: t = ulysses_traj(year=[2007],tf='all')
1564/1: from ulysses_traj import ulysses_traj
1564/2: t = ulysses_traj(year=[2007],tf='all')
1565/1: t = ulysses_traj(year=[2007],tf='all')
1565/2: from ulysses_traj import ulysses_traj
1565/3: t = ulysses_traj(year=[2007],tf='all')
1566/1: from ulysses_traj import ulysses_traj
1566/2: t = ulysses_traj(year=[2007],tf='all')
1567/1: from ulysses_traj import ulysses_traj
1567/2: t = ulysses_traj(year=[2007],tf='all')
1568/1: t = ulysses_traj(year=[2007],tf='all')
1568/2: from ulysses_traj import ulysses_traj
1568/3: t = ulysses_traj(year=[2007],tf='all')
1569/1: from ulysses_traj import ulysses_traj
1569/2: t = ulysses_traj(year=[2007],tf='all')
1570/1: from ulysses_traj import ulysses_traj
1570/2: t = ulysses_traj(year=[2007],tf='all')
1571/1: from ulysses_traj import ulysses_traj
1571/2: t = ulysses_traj(year=[2007],tf='all')
1572/1: from ulysses_traj import ulysses_traj
1572/2: t = ulysses_traj(year=[2007],tf='all')
1573/1: from ulysses_traj import ulysses_traj
1573/2: t = ulysses_traj(year=[2007],tf='all')
1574/1: from ulysses_traj import ulysses_traj
1574/2: t = ulysses_traj(year=[2007],tf='all')
1574/3: t = ulysses_traj(year=[2007],tf=[[1,2]])
1575/1: t = ulysses_traj(year=[2007],tf=[[1,2]])
1575/2: from ulysses_traj import ulysses_traj
1575/3: t = ulysses_traj(year=[2007],tf=[[1,2]])
1575/4: t = ulysses_traj(year=[2007],tf=[[1:2]])
1575/5: t = ulysses_traj(year=[2007],tf=[1,2])
1575/6: t = ulysses_traj(year=[2007],tf=[[1,3]])
1575/7: t.timeframe
1576/1: t = ulysses_traj(year=[2007],tf=[[1,3]])
1576/2: from ulysses_traj import ulysses_traj
1576/3: t = ulysses_traj(year=[2007],tf=[[1,3]])
1576/4: t.line
1576/5: from ulysses_traj import ulysses_traj
1576/6: t.line
1576/7: t = ulysses_traj(year=[2007],tf=[[1,3]])
1576/8: t.line
1577/1: from ulysses_traj import ulysses_traj
1577/2: t = ulysses_traj(year=[2007],tf=[[1,3]])
1577/3: t.line
1578/1: from ulysses_traj import ulysses_traj
1578/2: t = ulysses_traj(year=[2007],tf=[[1,3]])
1579/1: from ulysses_traj import ulysses_traj
1579/2: t = ulysses_traj(year=[2007],tf=[[1,3]])
1579/3: t.data
1580/1: from uswipha import uswipha
1580/2: d = uswipha(year=[1999],tf=[[1,3]])
1580/3: d.sync_traj
1580/4: d.sync_traj()
1580/5: d.data['d90']
1581/1: d = uswipha(year=[1999],tf=[[1,3]])
1581/2: from uswipha import uswipha
1581/3: d = uswipha(year=[1999],tf=[[1,3]])
1581/4: d.sync_traj()
1582/1: from uswipha import uswipha
1582/2: d = uswipha(year=[1999],tf=[[1,3]])
1582/3: d.sync_traj()
1583/1: from uswipha import uswipha
1583/2: d = uswipha(year=[1999],tf=[[1,3]])
1583/3: d.sync_traj()
1584/1: from uswipha import uswipha
1584/2: d = uswipha(year=[1999],tf=[[1,3]])
1584/3: d.sync_traj()
1584/4: t = ulysses_traj(year=[2007],tf=[[1,3]])
1585/1: from uswipha import uswipha
1585/2: t = ulysses_traj(year=[2007],tf=[[1,3]])
1585/3: from ulysses_traj import ulysses_traj
1585/4: t = ulysses_traj(year=[2007],tf=[[1,3]])
1585/5: t.data
1585/6: d = uswipha(year=[1990],tf=[[309]])
1585/7: d = uswipha(year=[1990],tf=[[309,310]])
1585/8: d = uswipha(year=[1990],tf=[[309,320]])
1585/9: d = uswipha(year=[1990],tf=[[315,320]])
1586/1: from uswipha import uswipha
1586/2: d = uswipha(year=[1990],tf=[[315,316]])
1586/3: from ulysses_traj import ulysses_traj
1586/4: t = ulysses_traj(year=[1990],tf=[[309]])
1586/5: t = ulysses_traj(year=[1990],tf=[[310]])
1586/6: t = ulysses_traj(year=[1990],tf=[[309,310]])
1586/7: t.data
1586/8: t = ulysses_traj(year=[1990],tf=[[309,320]])
1586/9: t.data
1586/10: t = ulysses_traj(year=[1990],tf=[[309,310]])
1586/11: t.data
1586/12: k = []
1586/13: k.append(5)
1586/14: k
1586/15: k.append(7)
1586/16: k
1587/1: from ulysses_traj import ulysses_traj
1588/1: from ulysses_traj import ulysses_traj
1588/2: t =
1588/3: t = ulysses_traj(year=[1990],tf=[[309,310]])
1588/4: t.data
1589/1: t = ulysses_traj(year=[1990],tf=[[309,310]])
1589/2: from ulysses_traj import ulysses_traj
1589/3: t = ulysses_traj(year=[1990],tf=[[309,310]])
1590/1: from ulysses_traj import ulysses_traj
1590/2: t = ulysses_traj(year=[1990],tf=[[309,310]])
1591/1: from ulysses_traj import ulysses_traj
1591/2: t = ulysses_traj(year=[1990],tf=[[309,310]])
1592/1: t = ulysses_traj(year=[1990],tf=[[309,310]])
1592/2: from ulysses_traj import ulysses_traj
1592/3: t = ulysses_traj(year=[1990],tf=[[309,310]])
1593/1: from ulysses_traj import ulysses_traj
1593/2: t = ulysses_traj(year=[1990],tf=[[309,310]])
1594/1: from ulysses_traj import ulysses_traj
1594/2: t = ulysses_traj(year=[1990],tf=[[309,310]])
1595/1: from ulysses_traj import ulysses_traj
1595/2: t = ulysses_traj(year=[1990],tf=[[309,310]])
1596/1: from ulysses_traj import ulysses_traj
1596/2: t = ulysses_traj(year=[1990],tf=[[309,310]])
1597/1: from ulysses_traj import ulysses_traj
1597/2: t = ulysses_traj(year=[1990],tf=[[309,310]])
1598/1: from ulysses_traj import ulysses_traj
1598/2: t = ulysses_traj(year=[1990],tf=[[309,310]])
1598/3: t.data
1599/1: from uswipha import uswipha
1599/2: d = uswipha(year=[1990],tf=[[315,316]])
1599/3: d = uswipha(year=[1990],tf=[[315,320]])
1599/4: getvelocity
1599/5: from uswiutils import getvelocity
1599/6: getvelocity(4.,1.,[1,2,3])
1600/1: from uswipha import uswipha
1600/2: d = uswipha(year=[1990],tf=[[315,320]])
1601/1: from uswipha import uswipha
1601/2: d = uswipha(year=[1990],tf=[[315,320]])
1601/3: d = uswipha(year=[1991],tf=[[315,320]])
1602/1: from uswipha import uswipha
1602/2: d = uswipha(year=[1991],tf=[[315,320]])
1602/3: d.sync_traj()
1603/1: d = uswipha(year=[1991],tf=[[315,320]])
1603/2: from uswipha import uswipha
1603/3: d = uswipha(year=[1991],tf=[[315,320]])
1603/4: d.sync_traj()
1604/1: d = uswipha(year=[1991],tf=[[315,320]])
1604/2: from uswipha import uswipha
1604/3: d = uswipha(year=[1991],tf=[[315,320]])
1604/4: d.sync_traj()
1605/1: from uswipha import uswipha
1605/2: d = uswipha(year=[1991],tf=[[315,320]])
1605/3: d.sync_traj()
1606/1: d.sync_traj()
1606/2: from uswipha import uswipha
1606/3: d = uswipha(year=[1991],tf=[[315,320]])
1606/4: d.sync_traj()
1607/1: from uswipha import uswipha
1607/2: d = uswipha(year=[1991],tf=[[315,320]])
1607/3: d.sync_traj()
1608/1: from uswipha import uswipha
1608/2: d = uswipha(year=[1991],tf=[[315,320]])
1608/3: d.sync_traj()
1609/1: from uswipha import uswipha
1609/2: d = uswipha(year=[1991],tf=[[315,320]])
1609/3: d = uswipha(year=[1991],tf=[[315,320]])
1609/4: d.sync_traj()
1610/1: from uswipha import uswipha
1610/2: d = uswipha(year=[1991],tf=[[315,320]])
1610/3: d.sync_traj()
1611/1: from uswipha import uswipha
1611/2: d = uswipha(year=[1991],tf=[[315,320]])
1611/3: d.sync_traj()
1611/4: d.data
1611/5: d.data['year']
1611/6: shape(d.data['year'])
1611/7: type(d.data['year'])
1612/1: from ulysses_traj import ulysses_traj
1612/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1612/3: t = ulysses_traj(year=[1990],tf=[[309,315]])
1613/1: t = ulysses_traj(year=[1990],tf=[[309,315]])
1613/2: from ulysses_traj import ulysses_traj
1613/3: t = ulysses_traj(year=[1990],tf=[[309,315]])
1613/4: len(t.data['ESP'])
1613/5: len(t.data['Year'])
1613/6: len(t.data['YYYY_E'])
1614/1: from ulysses_traj import ulysses_traj
1614/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1614/3: t.data
1614/4: len(t.data['YYYY_E'])
1615/1: from ulysses_traj import ulysses_traj
1615/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1615/3: t.data.keys()
1616/1: from ulysses_traj import ulysses_traj
1616/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1616/3: t.data
1617/1: from ulysses_traj import ulysses_traj
1617/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1617/3: t.data['DOY']
1617/4: a = array([1,2,3,4,5])
1617/5:
for i in a:
    print(i)
1617/6: d = t.data['DOY']
1617/7:
for i in d:
    print(i)
1617/8: range(len(d))
1618/1: from ulysses_traj import ulysses_traj
1618/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1618/3: d.data.keys()
1618/4: t.data.keys()
1619/1: from ulysses_traj import ulysses_traj
1619/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1620/1: from ulysses_traj import ulysses_traj
1620/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1621/1: from ulysses_traj import ulysses_traj
1621/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1622/1: from ulysses_traj import ulysses_traj
1622/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1622/3: t.data['R']
1622/4: t.data['R'][0]
1623/1: t = ulysses_traj(year=[1990],tf=[[309,315]])
1623/2: from ulysses_traj import ulysses_traj
1623/3: t = ulysses_traj(year=[1990],tf=[[309,315]])
1623/4: t.data['R']
1623/5: t.data['HG_Lat']
1624/1: from ulysses_traj import ulysses_traj
1624/2: t = ulysses_traj(year=[1990],tf=[[309,315]])
1624/3: t.data
1625/1: from ulysses_traj import ulysses_traj
1625/2: t = ulysses_traj(year=[1990],tf=[[309,355]])
1625/3: t.data['asp_phi']
1625/4: d
1625/5: t
1626/1: from ulysses_traj import ulysses_traj
1626/2: t = ulysses_traj(year=[1990],tf=[[309,355]])
1626/3: t.test_aspect_angle
1626/4: t.test_aspect_angle()
1626/5: d
1627/1: from ulysses_traj import ulysses_traj
1627/2: t = ulysses_traj(year=[1990],tf=[[309,355]])
1627/3: t.test_aspect_angle()
1628/1: t = ulysses_traj(year=[1990],tf=[[309,355]])
1628/2: from ulysses_traj import ulysses_traj
1628/3: t = ulysses_traj(year=[1990],tf=[[309,355]])
1628/4: t.test_aspect_angle()
1629/1: from ulysses_traj import ulysses_traj
1629/2: t = ulysses_traj(year=[1990],tf=[[309,355]])
1630/1: from ulysses_traj import ulysses_traj
1630/2: t = ulysses_traj(year=[1990],tf=[[309,355]])
1630/3: t
1631/1: from ulysses_traj import ulysses_traj
1631/2: t = ulysses_traj(year=[1990],tf=[[309,355]])
1632/1: from ulysses_traj import ulysses_traj
1632/2: t = ulysses_traj(year=[1990],tf=[[309,355]])
1632/3: calc_asp_angles([2.6698,54.95,-4.04],[1.002,124.2,-6.])
1632/4: from ul_calc_traj import calc_asp_angles
1632/5: calc_asp_angles([2.6698,54.95,-4.04],[1.002,124.2,-6.])
1632/6: from ul_calc_traj import calc_SPE
1632/7: calc_SPE(calc_asp_angles([2.6698,54.95,-4.04],[1.002,124.2,-6.]))
1632/8: phi, theta = calc_asp_angles([2.6698,54.95,-4.04],[1.002,124.2,-6.])
1632/9: calc_SPE(phi,theta)
1633/1: from ul_calc_traj import calc_SPE
1633/2: from ulysses_traj import ulysses_traj
1633/3: t = ulysses_traj(year=[1991],tf=[[100,101]])
1633/4: t.test_aspect_angle()
1634/1: t = ulysses_traj(year=[1991],tf=[[100,101]])
1634/2: from ulysses_traj import ulysses_traj
1634/3: t = ulysses_traj(year=[1991],tf=[[100,101]])
1635/1: from ulysses_traj import ulysses_traj
1635/2: t = ulysses_traj(year=[1991],tf=[[100,101]])
1635/3: t.test_aspect_angle()
1635/4: from ul_calc_traj import calc_asp_angles
1635/5: calc_asp_angles([2.67,54.95,-4.04],[1.002,124.2,-6.])
1635/6: calc_asp_angles([2.67,234.95,-4.04],[1.002,124.2,-6.])
1636/1: from ulysses_traj import ulysses_traj
1636/2: t = ulysses_traj(year=[1991],tf=[[100,101]])
1637/1: from ulysses_traj import ulysses_traj
1637/2: t = ulysses_traj(year=[1991],tf=[[100,101]])
1637/3: t.test_aspect_angle()
1637/4: from ul_calc_traj import calc_asp_angles
1637/5: from ul_calc_traj import calc_SPE
1637/6: phi, theta = calc_asp_angles([2.6698,54.95,-4.04],[1.002,124.2,-6.])
1637/7: calc_SPE(phi,theta)
1637/8: phi, theta = calc_asp_angles([2.6698,234.95,-4.04],[1.002,124.2,-6.])
1637/9: calc_SPE(phi,theta)
1638/1: from ul_calc_traj import calc_SPE
1638/2: from ulysses_traj import ulysses_traj
1638/3: t = ulysses_traj(year=[1991],tf=[[100,101]])
1638/4: t.data
1639/1: from numpy import array
1639/2: t = array([35,58,90,101,138,183,221,255,312,361])
1639/3: l_i = array(1.,0.7,0.7,0.4,1.1,1.4,0.7,1.0,1.8,1.2)
1639/4: l_i = array(1.,0.7,0.7,0.4,1.1,1.4,0.7,1.0,1.8,1.2])
1639/5: l_i = array([1.,0.7,0.7,0.4,1.1,1.4,0.7,1.0,1.8,1.2])
1639/6: L = array([])
1639/7: for in l_i:
1639/8:
for i in l_i:
    L.append(1)
1639/9: from numpy import append
1639/10:
for i in l_i:
    L.append(1)
1640/1: from agrarfunctions import testrennstrecke
1640/2: testrennstrecke
1640/3: testrennstrecke()
1641/1: testrennstrecke()
1641/2: from agrarfunctions import testrennstrecke
1641/3: testrennstrecke()
1642/1: from agrarfunctions import testrennstrecke
1642/2: testrennstrecke()
1642/3: from agrarfunctions import testrennstrecke
1642/4: testrennstrecke()
1643/1: from agrarfunctions import testrennstrecke
1643/2: testrennstrecke()
1644/1: from agrarfunctions import testrennstrecke
1644/2: testrennstrecke()
1645/1: from agrarfunctions import testrennstrecke
1645/2: testrennstrecke()
1645/3: append(1,3)
1646/1: from agrarfunctions import testrennstrecke
1646/2: append(1,3)
1646/3: testrennstrecke()
1647/1: append(1,3)
1647/2: from agrarfunctions import testrennstrecke
1647/3: testrennstrecke()
1647/4: L_i
1647/5: L_i = array([])
1647/6:
for i in range(5):
    append(L_i,i)
1647/7: L_i
1648/1: from agrarfunctions import testrennstrecke
1648/2: testrennstrecke()
1649/1: from agrarfunctions import testrennstrecke
1649/2: testrennstrecke()
1650/1: from agrarfunctions import testrennstrecke
1650/2: testrennstrecke()
1651/1: from agrarfunctions import testrennstrecke
1651/2: testrennstrecke()
1652/1: from agrarfunctions import testrennstrecke
1652/2: testrennstrecke()
1653/1: from agrarfunctions import testrennstrecke
1653/2: testrennstrecke()
1654/1: from agrarfunctions import testrennstrecke
1654/2: testrennstrecke()
1655/1: from agrarfunctions import testrennstrecke
1655/2: testrennstrecke()
1656/1: from agrarfunctions import testrennstrecke
1656/2: testrennstrecke()
1656/3: arange(0,11,0.5)
1657/1: from agrarfunctions import testrennstrecke
1657/2: arange(0,11,0.5)
1657/3: testrennstrecke()
1658/1: from agrarfunctions import testrennstrecke
1658/2: testrennstrecke()
1659/1: from agrarfunctions import testrennstrecke
1659/2: testrennstrecke()
1660/1: from agrarfunctions import testrennstrecke
1660/2: testrennstrecke()
1661/1: from agrarfunctions import testrennstrecke
1661/2: testrennstrecke()
1662/1: from agrarfunctions import testrennstrecke
1662/2: testrennstrecke()
1663/1: from agrarfunctions import testrennstrecke
1663/2: testrennstrecke()
1664/1: from agrarfunctions import testrennstrecke
1664/2: testrennstrecke()
1665/1: from agrarfunctions import testrennstrecke
1665/2: testrennstrecke()
1666/1: from agrarfunctions import testrennstrecke
1666/2: testrennstrecke()
1667/1: from agrarfunctions import testrennstrecke
1667/2: testrennstrecke()
1668/1: from agrarfunctions import testrennstrecke
1668/2: testrennstrecke()
1669/1: from agrarfunctions import testrennstrecke
1669/2: testrennstrecke()
1670/1: from agrarfunctions import testrennstrecke
1670/2: testrennstrecke()
1671/1: from agrarfunctions import testrennstrecke
1671/2: testrennstrecke()
1672/1: from agrarfunctions import testrennstrecke
1672/2: testrennstrecke()
1673/1: from agrarfunctions import testrennstrecke
1673/2: testrennstrecke()
1674/1: from agrarfunctions import testrennstrecke
1674/2: testrennstrecke()
1675/1: from agrarfunctions import testrennstrecke
1675/2: testrennstrecke()
1676/1: from agrarfunctions import testrennstrecke
1676/2: testrennstrecke()
1677/1: from agrarfunctions import testrennstrecke
1677/2: testrennstrecke()
1678/1: from agrarfunctions import testrennstrecke
1678/2: testrennstrecke()
1679/1: from agrarfunctions import testrennstrecke
1679/2: testrennstrecke()
1680/1: from agrarfunctions import testrennstrecke
1680/2: testrennstrecke()
1681/1: from agrarfunctions import testrennstrecke
1681/2: testrennstrecke()
1682/1: from agrarfunctions import testrennstrecke
1682/2: testrennstrecke()
1683/1: from agrarfunctions import testrennstrecke
1684/1: from agrarfunctions import testrennstrecke
1684/2: testrennstrecke()
1685/1: from agrarfunctions import testrennstrecke
1685/2: testrennstrecke()
1686/1: from agrarfunctions import testrennstrecke
1686/2: testrennstrecke()
1687/1: from agrarfunctions import testrennstrecke
1687/2: testrennstrecke()
1688/1: from agrarfunctions import testrennstrecke
1688/2: testrennstrecke()
1689/1: from agrarfunctions import testrennstrecke
1689/2: testrennstrecke()
1690/1: from agrarfunctions import testrennstrecke
1690/2: testrennstrecke()
1691/1: from agrarfunctions import testrennstrecke
1691/2: testrennstrecke()
1692/1: from agrarfunctions import testrennstrecke
1692/2: testrennstrecke()
1693/1: from agrarfunctions import testrennstrecke
1693/2: testrennstrecke()
1694/1: from agrarfunctions import testrennstrecke
1694/2: testrennstrecke()
1695/1: from agrarfunctions import testrennstrecke
1695/2: testrennstrecke()
1696/1: from agrarfunctions import testrennstrecke
1696/2: testrennstrecke()
1697/1: from agrarfunctions import testrennstrecke
1697/2: testrennstrecke()
1698/1: from agrarfunctions import testrennstrecke
1698/2: testrennstrecke()
1699/1: from agrarfunctions import testrennstrecke
1699/2: testrennstrecke()
1700/1: from agrarfunctions import testrennstrecke
1700/2: testrennstrecke()
1701/1: from ulysses_traj import ulysses_traj
1701/2: t = ulysses_traj(year=[1991],tf=[[100,101]])
1701/3: t.data
1702/1: from uswipha import uswipha
1702/2: d = uswipha(year=[1991],tf=[[315,320]])
1702/3: d.sync_swoops()
1702/4: d.data
1702/5: d.sync_traj()
1703/1: from uswipha import uswipha
1703/2: d = uswipha(year=[1991],tf=[[315,320]])
1703/3: d.data
1703/4: d.sync_traj()
1703/5: d.data
1704/1: from uswipha import uswipha
1704/2: d = uswipha(year=[1991],tf=[[315,320]])
1704/3: d.sync_traj()
1704/4: cd ..
1704/5: ls
1704/6: cd ..
1704/7: ls
1704/8: pwd
1704/9: cd ..
1704/10: cd ..
1704/11: from swics.trunk.ace_dbd.dist3D import Dist3D
1704/12: d
1704/13: d = uswipha(year=[1991],tf=[[315,320]])
1704/14: d.sync_traj()
1704/15: D = Dist3D(d)
1704/16: d.data['aspphi']
1705/1: pwd
1706/1: from Ulysses.swics.software.libulpy.uswipha import uswipha
1706/2: d = uswipha(year=[1991],tf=[[315,320]])
1706/3: d.sync_traj()
1707/1: from Ulysses.swics.software.libulpy.uswipha import uswipha
1707/2: d = uswipha(year=[1991],tf=[[315,320]])
1707/3: d.sync_traj()
1707/4: d.data['aspphi']
1707/5: from swics.trunk.ace_dbd.dist3D import Dist3D
1707/6: D = Dist3D(d)
1707/7: d.data
1708/1: %run swics_collimator.py
1708/2: rotate
1708/3: sys.path
1708/4: pwd
1708/5: %run swics_collimator.py
1708/6: c = collimator
1708/7: c = collimator()
1708/8: c
1708/9: d
1708/10: d = uswipha(year=[1991],tf=[[315,320]])
1708/11: from libulpy.uswipha import uswipha
1708/12: d = uswipha(year=[1991],tf=[[315,320]])
1708/13: d.sync_traj()
1708/14: D = Dist3D(d)
1708/15: from dist3D import Dist3D
1709/1: e = [100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489]
1709/2: len(e)
1709/3:
for i in range(len(e)):
    try:
        print(e[i]-e[i-1])
    except:
        pass
1709/4: e_diff = []
1709/5:
for i in range(len(e)):
    try:
       e_diff.append((e[i]-e[i-1]))
    except:
        pass
1709/6: e_diff
1709/7: pylab.plot(range(len(e_diff)),e_diff)
1709/8: pylab.plot(range(len(e)),e)
1709/9: pylab.close('all')
1709/10: pylab.plot(range(len(e)),e,'x')
1709/11: pylab.plot(range(len(e)),e,'x')
1709/12: e_diff
1709/13:
for i in range(len(e)):
    try:
       e_diff.append((e[i-1]-e[i]))
    except:
        pass
1709/14: e_diff
1709/15: e_diff = []
1709/16:
for i in range(len(e)):
    try:
       e_diff.append((e[i-1]-e[i]))
    except:
        pass
1709/17: e_diff
1709/18: e_diff = e_diff[1:]
1709/19: e_diff
1709/20: ln(e_diff)
1709/21: from numpy import ln
1709/22: log(e_diff)
1709/23: exp(e_diff)
1709/24: pylab.plot(range(len(e_diff)),e_diff,'x')
1709/25: e_diff
1709/26: pylab.plot(range(len(e)),e,'x')
1709/27: pylab.plot(range(len(e)),ln(e),'x')
1709/28: pylab.plot(range(len(e)),log(e),'x')
1709/29: log(e)
1709/30:
for i in len(range(e)):
    if i == 0:
        pass
    else:
        print(log(e[i-1]) - log(e[i]))
1709/31:
for i in range(len(e)):
    if i == 0:
        pass
    else:
        print(log(e[i-1]) - log(e[i]))
1709/32: e
1709/33: np.e
1709/34: log(np.e)
1709/35: exp(e[0])
1709/36: exp(e[1])
1709/37: exp(e[10])
1709/38: exp(e[10]) - exp(e[11])
1709/39: e
1709/40: log(e[10]) - log(e[11])
1709/41: e[10]-e[11]
1709/42: e[0:3]
1709/43: e[0]-e[1]
1709/44: e[1]-e[2]
1709/45: e[3]
1709/46: e[3]-e[2]
1709/47: e[1]*1.0744
1709/48: e[1]*1.144
1709/49: 75.0485*1.144
1709/50: pylab.plot(range(len(e)),exp(e),'x')
1709/51: pylab.plot(range(len(e)),exp(e),'x')
1709/52: e
1709/53: exp(e)
1709/54: pylab.plot(range(len(e)),exp(e),'x')
1709/55: e_exp = exp(e)
1709/56: e_exp
1709/57: pylab.plot(range(len(e)),e_exp,'x')
1709/58: e = e[1:]
1709/59: pylab.plot(range(len(e)),exp(e),'x')
1709/60: pylab.close('all')
1709/61: pylab.plot(range(len(e)),exp(e),'x')
1709/62: e
1709/63: e = []
1709/64: e = [100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489]
1709/65: pylab.plot(range(len(e)),exp(e),'x')
1709/66: pylab.close('all')
1709/67: pylab.plot(range(len(e)),exp(e),'x')
1709/68: e
1709/69: pylab.close('all')
1709/70: pylab.plot(range(len(e)),log(e),'x')
1709/71: log(e)
1709/72: diff(e)
1709/73: diff(log(e))
1709/74: log(e)
1709/75: pylab.close('all')
1709/76: pylab.plot(range(len(e)),log(e),'x')
1709/77: pylab.plot(range(len(e)),e,'x')
1709/78: x = arange(0,60)
1709/79: pylab.plot(range(len(x)),exp(x),'x')
1709/80: pylab.close('all')
1709/81: pylab.plot(range(len(x)),exp(x),'x')
1709/82: pylab.plot(range(len(x)),10**x,'x')
1709/83: pylab.close('all')
1709/84: pylab.plot(range(len(x)),10**x,'x')
1709/85: x = arange(0,10,100)
1709/86: pylab.close('all')
1709/87: pylab.plot(range(len(x)),10**x,'x')
1709/88: x
1709/89: x = arange(0,10,0.01)
1709/90: x
1709/91: pylab.close('all')
1709/92: pylab.plot(range(len(x)),10**x,'x')
1709/93: x = arange(0,10,0.1)
1709/94: pylab.plot(range(len(x)),10**x,'x')
1709/95: pylab.plot(range(len(x)),10**x,'x')
1709/96: pylab.plot(range(len(x)),exp(x),'x')
1709/97: e
1709/98: np.e
1709/99: pylab.plot(range(len(x)),np.e**x,'x')
1709/100: pylab.close('all')
1709/101: pylab.plot(arange(0,100,0.1),np.e**x,'x')
1709/102: pylab.plot(arange(0,100,0.01),np.e**x,'x')
1709/103: pylab.close('all')
1709/104: pylab.plot(arange(0,10,0.1),np.e**x,'x')
1709/105: pylab.plot(arange(0,10,0.1),np.10**x,'x')
1709/106: pylab.plot(arange(0,10,0.1),10**x,'x')
1709/107: np.e**6
1709/108: pylab.close('all')
1709/109: pylab.plot(arange(0,10,0.1),np.log(x),'x')
1709/110: e
1709/111: e = e[0:]
1709/112: e
1709/113: e = e[1:]
1709/114: e
1709/115: e_log = np.log(e)
1709/116: diff(e_log)
1709/117: np.exp(0.0718)
1709/118: np.exp(0.1436)
1709/119: log(1.15)
1709/120: log(1.0365)
1709/121: np.log(1.0744)
1709/122: np.log(1.0365)
1709/123: np.exp(1.0365)
1709/124: np.exp(0.144)
1709/125: e
1709/126: 0.911489*1.0744
1709/127: diff(e_log)
1709/128: e
1709/129: e_log
1709/130: e
1709/131: diff(e_log)
1709/132: e_log
1709/133: 4.4617-4.3181
1709/134: np.exp(0.1436)
1709/135: 75.0485*1.1544
1709/136: 1**0.14
1709/137: 2**0.14
1710/1: %run test.py
1710/2: e
1710/3: len(e)
1711/1: %run test.py
1712/1: %run test.py
1713/1: %run test.py
1713/2: plt.show()
1714/1: %run test.py
1715/1: %run test.py
1716/1: %run test.py
1717/1: %run test.py
1718/1: %run test.py
1719/1: %run test.py
1720/1: %run test.py
1721/1: %run test.py
1722/1: %run test.py
1723/1: %run test.py
1724/1: %run test.py
1725/1: %run test.py
1726/1: %run test.py
1727/1: %run test.py
1728/1: %run test.py
1729/1: %run test.py
1730/1: %run test.py
1731/1: %run test.py
1732/1: %run test.py
1733/1: %run test.py
1734/1: %run test.py
1735/1: %run test.py
1736/1: %run test.py
1737/1: %run test.py
1738/1: %run test.py
1739/1: %run test.py
1740/1: %run test.py
1741/1: %run test.py
1742/1: %run test.py
1743/1: %run test.py
1744/1: %run test.py
1745/1: %run test.py
1746/1: %run test.py
1747/1: %run test.py
1748/1: %run test.py
1749/1: %run test.py
1750/1: %run test.py
1751/1: %run test.py
1752/1: %run test.py
1753/1: %run test.py
1754/1: %run test.py
1754/2: a = array([25.,27.,26.,30.,25.,25.,28])
1754/3: len(a)
1754/4: sum = []
1754/5:
for i in range(7):
    sum.append(a[i])
1754/6: sum/7.
1754/7: sum
1754/8: clear sum
1754/9: sum = 0.
1754/10:
for i in range(7):
    sum += a[i]
1754/11: sum
1754/12: a
1754/13: std_array = []
1754/14: m = mean(a)
1754/15: m
1754/16: m = 26.57
1754/17:
for i in range(7):
    std_array.append((m-a[i])**2)
1754/18: std_array
1754/19: std_arr = 0.
1754/20:
for i in range(7):
    std_array+=((m-a[i])**2)
1754/21: std_arr
1754/22:
for i in range(7):
    std_array+=(m-a[i])**2
1754/23: std_arr
1754/24: a
1754/25: m
1754/26:
for i in range(7):
    std_array=std_array+(m-a[i])**2
1754/27: std_array
1754/28:
for i in range(7):
    std_arr+=(m-a[i])**2
1754/29: std_arr
1754/30: std_arr/6.
1754/31: std_arr/42.
1754/32: a
1754/33: m
1754/34: std_arr = 0.
1754/35:
for i in range(7):
    std_arr+=(m-a[i])**2
1754/36: std_arr
1754/37: std_arr/6.
1754/38: std_arr/7.
1754/39: a
1754/40:
for i in range(7):
    print(a[i])
1754/41: std_arr = 0.
1754/42:
for i in range(7):
    std_arr += (m-a[i])**2
1754/43: std_arr
1754/44: std_arr/7.
1754/45: sqrt(std_arr/7.)
1754/46: sqrt(std_arr/6.)
1754/47: 21.71/6.
1754/48: sqrt(3.618)
1754/49: 1.9/sqrt(7)
1754/50: a = [26.,27.,25.,25.,25.,27.,25.]
1754/51: len(a)
1754/52: mean(a)
1754/53: m = 25.71
1754/54: std_arr = 0.
1754/55:
for i in range(7):
    std_arr += (m-a[i])**2
1754/56: std_arr
1754/57: std_arr/6.
1754/58: sqrt(std_arr/6.)
1754/59: 0.95/sqrt(7.)
1754/60: sqrt(5.43/6)
1754/61: 5.43/6
1754/62: 5.43/7
1754/63: 0.95/sqrt(7)
1754/64: 60*0.36
1754/65: 60*0.72
1755/1: 86.6359 * 1.0744
1755/2: cd PUI
1755/3: ls
1755/4: cd Ulysses/
1755/5: ls
1756/1: %run tes
1756/2: %run test_epq_steps.py
1757/1: %run test_epq_steps.py
1758/1: %run test_epq_steps.py
1758/2: plt.show()
1759/1: plt.show()
1759/2: %run test_epq_steps.py
1760/1: %run test_epq_steps.py
1761/1: %run test_epq_steps.py
1761/2: steps_log
1761/3: 4.46171428*1.0744
1761/4: 4.46171428*1.0365
1761/5: 1.15938121*1.0365
1761/6: logspace(100.,0.611489)
1761/7: y = linspace(1,3,num=num,endpoint=endpoint)
1761/8: y = linspace(1,3)
1761/9: y
1761/10: y = linspace(1,3,num=10)
1761/11: y = linspace(1,3,num=10,endpoint=True)
1761/12: y
1761/13: y = linspace(1,10,num=10,endpoint=True)
1761/14: y
1761/15: power(1,y)
1761/16: power(1,y).astype(dtype)
1761/17: power(e,y).astype(dtype)
1761/18: log(1)
1761/19: log(e)
1761/20: logspace(1,3,num=10,base=e)
1761/21: y = linspace(1,3,num=10,endpoint=True)
1761/22: power(e,y).astype(dtype)
1762/1: %run test_epq_steps.py
1763/1: %run test_epq_steps.py
1764/1: %run test_epq_steps.py
1765/1: %run test_epq_steps.py
1766/1: %run test_epq_steps.py
1767/1: %run test_epq_steps.py
1768/1: %run test_epq_steps.py
1769/1: %run test_epq_steps.py
1770/1: %run test_epq_steps.py
1771/1: %run test_epq_steps.py
1772/1: %run test_epq_steps.py
1773/1: %run test_epq_steps.py
1773/2: %run test_epq_steps.py
1774/1: %run test_epq_steps.py
1775/1: %run test_epq_steps.py
1776/1: %run test_epq_steps.py
1777/1: %run test_epq_steps.py
1778/1: %run test_epq_steps.py
1778/2: %run test_epq_steps.py
1779/1: %run test_epq_steps.py
1780/1: %run test_epq_steps.py
1781/1: %run test_epq_steps.py
1782/1: %run test_epq_steps.py
1783/1: %run test_epq_steps.py
1784/1: %run test_epq_steps.py
1785/1: %run test_epq_steps.py
1786/1: %run test_epq_steps.py
1787/1: %run test_epq_steps.py
1788/1: %run test_epq_steps.py
1789/1: %run test_epq_steps.py
1789/2: steps_len
1790/1: steps_len
1790/2: %run test_epq_steps.py
1791/1: %run test_epq_steps.py
1792/1: %run test_epq_steps.py
1793/1: %run test_epq_steps.py
1794/1: %run test_epq_steps.py
1795/1: %run test_epq_steps.py
1795/2: logscale(0,3,num=10,base=e)
1795/3: from numpy import *
1795/4: logscale(0,3,num=10,base=e)
1795/5: logspace(1,3,num=10,base=e)
1795/6: 2**e
1795/7: e**2
1795/8: logspace(1,3,num=3,base=e)
1795/9: linsapce(0,3,3)
1795/10: linspace(0,3,3)
1795/11: linspace(0,3,num=3)
1795/12: linspace(1,3,num=3)
1795/13: logspace(1,3,num=3,base=e)
1795/14: e**2
1795/15: 2**3
1795/16: e**3
1795/17: l = logspace(1,3,num=30,base=e)
1795/18: l
1795/19: log(l)
1795/20: l = logspace(1,3,num=3,base=e)
1795/21: log(l)
1795/22: a = array([1.,2.,3.,4.])
1795/23: power(base=e,a)
1795/24: power(a,base=e)
1795/25: numpy.power
1795/26: numpy.power(base=e,np.linspace(1,3,num=3))
1795/27: power(e,a)
1795/28: a
1795/29: a2 = array([1.,2.,3.,4.,5.])
1795/30: power(e,a2)
1795/31: a3 = array([0.,1.,2.,3.,4.,5.])
1795/32: power(e,a3)
1796/1: %run test_epq_steps.py
1796/2: exp(4.60525985)
1796/3: exp(-0.14357557)
1796/4: steps
1796/5: 100*e**(-0.1436*steps)
1796/6: 3.953e-04*1.0744
1796/7: 3.953e-04*1.0365
1797/1: %run make_ani_STA_STB_plots_backsub.py
1798/1: %run make_ani_STA_STB_plots_backsub.py
1799/1: %run make_ani_STA_STB_plots_backsub.py
1800/1: %run make_ani_STA_STB_plots_backsub.py
1801/1: %run make_ani_STA_STB_plots_backsub.py
1802/1: %run make_ani_STA_STB_plots_backsub.py
1803/1: %run make_ani_STA_STB_plots_backsub.py
1804/1: %run make_ani_STA_STB_plots_backsub.py
1805/1: %run make_ani_STA_STB_plots_backsub.py
1806/1: %run make_ani_STA_STB_plots_backsub.py
1807/1: %run make_ani_STA_STB_plots_backsub.py
1808/1: %run make_ani_STA_STB_plots_backsub.py
1809/1: %run make_ani_STA_STB_plots_backsub.py
1810/1: %run make_ani_STA_STB_plots_backsub.py
1811/1: %run make_ani_STA_STB_plots_backsub.py
1812/1: %run make_ani_STA_STB_plots_backsub.py
1813/1: %run main2_backsub.py
1814/1: %run main2_backsub.py
1815/1: %run main2_backsub.py
1816/1: %run main2_backsub.py
1817/1: from libulpy.uswipha import uswipha
1817/2: from dist3D import Dist3D
1818/1: from dist3D import Dist3D
1818/2: zeros(3,4)
1818/3: from numpy import zeros
1818/4: zeros(3,4)
1818/5: zeros((3,4))
1818/6: D = Dist3D(d)
1818/7: d = uswipha(year=[1991],tf=[[315,320]])
1818/8: from libulpy.uswipha import uswipha
1818/9: d = uswipha(year=[1991],tf=[[315,320]])
1818/10: from libulpy.uswipha import uswipha
1818/11: D = Dist3D(d)
1818/12: d.sync_traj()
1818/13: d.sync_swoops()
1818/14: D = Dist3D(d)
1819/1: from dist3D import Dist3D
1819/2: from libulpy.uswipha import uswipha
1819/3: d = uswipha(year=[1991],tf=[[315,320]])
1819/4: D = Dist3D(d)
1819/5: d.sync_traj()
1819/6: D = Dist3D(d)
1819/7: D = Dist3D(d)
1820/1: from libulpy.uswipha import uswipha
1820/2: d = uswipha(year=[1991],tf=[[315,320]])
1820/3: d.sync_traj()
1820/4: from dist3D import Dist3D
1820/5: D = Dist3D(d)
1820/6: D.mass
1820/7: D.charge
1820/8: D.ion
1820/9: d.aspphistep
1820/10: D.aspphistep
1820/11: D.aspphi
1820/12: D.vels
1820/13: D.vswbins
1820/14: D.FoV
1820/15: D.vspace
1820/16: searchsorted(self.aspphi,around(self.d.data["aspphi"]))
1820/17: s.aspphi
1820/18: d.aspphi
1820/19: D.aspphi
1820/20: D.d.data['aspphi']
1820/21: searchsorted(D.aspphi,around(D.d.data["aspphi"]))
1820/22: searchsorted([10,11],[10.5,11.1,11.2,12,1])
1820/23: a = searchsorted(D.aspphi,around(D.d.data["aspphi"]))
1820/24: a
1820/25: max(a)
1820/26: min(a)
1820/27: searchsorted([10,11],[10.5,11.1,11.2,12.1])
1820/28: searchsorted([10],[10.5,11.1,11.2,12.1])
1820/29: searchsorted([12],[10.5,11.1,11.2,12.1])
1820/30: a = searchsorted(D.aspphi,around(D.d.data["aspphi"]))
1820/31: around(D.d.data["aspphi"])
1820/32: D.aspphi
1820/33: d.data['aspphi']
1820/34: searchsorted(D.asptheta,around(D.d.data["asptheta"]))
1820/35: max(searchsorted(D.asptheta,around(D.d.data["asptheta"])))
1820/36: D.d.data["epq"].astype(int)
1820/37: D.d.data["epq"]
1820/38:
D.d.data["epq"][0
]
1820/39: type(D.d.data["epq"][0])
1820/40: type(D.d.data["epq"].astype(int)[0])
1820/41: d.data['did']
1820/42: d.data
1820/43: D.d.data['vsw']
1820/44: d.sync_swoops()
1820/45: D.d.data['vsw']
1820/46: around(D.d.data['vsw'],-1)
1820/47: around(D.d.data['vsw'],-10)
1820/48: around([510,520,600,340,650,800],-10)
1820/49: around([510,520,600,1340,650,800],-10)
1820/50: around([510,520,600,1340,650,800],-1)
1820/51: around([510,520,600,1340,650,800],1)
1820/52: around([510,520,600,1340,650,800],10)
1820/53: around([5101,5201,6001,13401,6501,8001],10)
1820/54: around([5101,5201,6001,13401,6501,8001],1)
1820/55: around([5101,5201,6001,13401,6501,8001],-1)
1820/56: D.d.data['vsw']
1820/57: D.d.data['vxsw']
1821/1: D.d.data['vxsw']
1821/2: from dist3D import Dist3D
1821/3: from libulpy.uswipha import uswipha
1821/4: d = uswipha(year=[1991],tf=[[315,320]])
1821/5: d.sync_swoops()
1821/6: d.sync_traj()
1821/7: D = Dist3D(d)
1821/8: d.data
1822/1: from libulpy.uswipha import uswipha
1822/2: d = uswipha(year=[1991],tf=[[315,320]])
1822/3: d.sync_traj()
1822/4: d.sync_swoops()
1822/5: from dist3D import Dist3D
1822/6: D = Dist3D(d)
1823/1: from dist3D import Dist3D
1823/2: from libulpy.uswipha import uswipha
1823/3: d = uswipha(year=[1991],tf=[[315,320]])
1823/4: d.sync_swoops()
1823/5: d.sync_traj()
1823/6: D = Dist3D(d)
1823/7: D.phiind
1823/8: D.thetaind
1823/9: D.epqind
1823/10: D.detind
1823/11: len(D.detind)
1823/12: D.vspace[D.phiind,:,:,:,:,:]
1823/13: D.vspace[D.phiind,0,0,0,0,0]
1823/14: D.vspace[0,thetaind,0,0,0,0]
1823/15: D.vspace[0,D.thetaind,0,0,0,0]
1823/16: D.vspace[0,0,D.epqind,0,0,0]
1823/17: epqind
1823/18: d.data['epq']
1823/19:
len(array([100.,95.,93.,90.,89.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489])
)
1824/1: from libulpy.uswipha import uswipha
1824/2: d = uswipha(year=[1991],tf=[[315,320]])
1824/3: d.sync_traj()
1824/4: d.sync_swoops()
1824/5: from dist3D import Dist3D
1824/6: D = Dist3D(d)
1825/1: D = Dist3D(d)
1825/2: from dist3D import Dist3D
1825/3: from libulpy.uswipha import uswipha
1825/4: d = uswipha(year=[1991],tf=[[315,320]])
1825/5: d.sync_swoops()
1825/6: d.sync_traj()
1825/7: D = Dist3D(d)
1825/8: D.vspace[phiind,thetaind,epqind,detind,secind,0,0]
1825/9: D.vspace[D.phiind,D.thetaind,D.epqind,D.detind,D.secind,0,0]
1825/10: D.vspace[D.phiind,D.thetaind,D.epqind,D.detind,0,0,0]
1825/11: D.vspace[D.phiind,D.thetaind,D.epqind,0,0,0,0]
1825/12: d.data['det']
1825/13: max(d.data['det'])
1825/14: min(d.data['det'])
1825/15: unique(d.data['det'])
1825/16: d.data
1826/1: from libulpy.uswipha import uswipha
1826/2: d = uswipha(year=[1991],tf=[[315,320]])
1826/3: d.sync_traj()
1826/4: d.sync_swoops()
1826/5: from dist3D import Dist3D
1826/6: pwd
1826/7: from dist3D import Dist3D
1826/8: D = Dist3D(d)
1827/1: pwd
1827/2: ls
1827/3: cd libulpy
1827/4: %run pui_ulysses.py
1827/5: d = uswipha(year=[1991],tf=[[315,320]])
1827/6: polarplot(d,'det','sec')
1827/7: d = uswipha(year=[1991],tf=[[315,320]])
1827/8: polarplot(d,'det','sec')
1827/9: d.polarplot('det','sec')
1827/10: d
1827/11: polarplot(d)
1827/12: polarplot(d,det,sec))
1827/13: polarplot(d,det,sec)
1827/14: polarplot(d,"det","sec")
1827/15: %run pui_ulysses.py
1827/16: polarplot(d,"det","sec")
1828/1: load_pui_ulysses.py
1828/2: %run load_pui_ulysses.py
1828/3: %run load_pui_ulysses.py
1829/1: %run load_pui_ulysses.py
1829/2: %run /home/asterix/fischer/PUI/ulysses/swics/software/libulpy
1829/3: %run /home/asterix/fischer/PUI/ulysses/swics/software/libulpy/uswipha
1830/1: %run load_pui_ulysses.py
1830/2: d.polarplot()
1830/3: polarplot(d,"det","sec")
1830/4: cd ..
1830/5: %run pui_ulysses.py
1830/6: polarplot(d,"det","sec")
1830/7: histograms(1,1)
1830/8: histograms(d.get_data['det'],d.get_data["sec"])
1830/9: histograms(d.get_data['det'],d.get_data['sec'])
1830/10: d.data['det']
1830/11: histograms(d.data['det'],d.data['sec'])
1830/12: polarplot(d,"det","sec")
1831/1: polarplot(d,"det","sec")
1831/2: ls
1831/3: load_pui_ulysses.py
1831/4: %run load_pui_ulysses.py
1831/5: cd ..
1831/6: %run pui_ulysses.py
1831/7: %run pui_ulysses.py
1831/8: A = Animation('doy')
1831/9: A = Animation(d,'doy')
1831/10: d.get_data(['doy'])
1831/11: d.get_data(['ssd_0', 'det_0','epq_mask'],'doy')
1832/1: d.get_data(['ssd_0', 'det_0','epq_mask'],'doy')
1833/1: %run load_pui_ulysses.py
1833/2: %run ./diy/load_pui_ulysses.py
1833/3: %run pui_ulysses.py
1833/4: A = Animation(d,'doy')
1834/1: A = Animation(d,'doy')
1834/2: %run pui_ulysses.py
1834/3: A = Animation(d,'det','sec','doy')
1834/4: %run ./diy/load_pui_ulysses.py
1834/5: %run pui_ulysses.py
1834/6: A = Animation(d,'det','sec','doy')
1834/7: %run pui_ulysses.py
1834/8: %run pui_ulysses.py
1834/9: A = Animation(d,'det','sec','doy')
1834/10: A.animate_polar()
1834/11: A.plot
1834/12: A.plot()
1835/1: %run ./diy/load_pui_ulysses.py
1835/2: A = Animation(d,'det','sec','doy')
1835/3: %run pui_ulysses.py
1835/4: A = Animation(d,'det','sec','doy')
1835/5: A.plot
1835/6: A.plot()
1835/7: A.animate_polar()
1835/8: pylab.close('all')
1835/9: A.Hist
1835/10: A.Hist[:,:,0]
1835/11: A.Hist
1836/1: %run ./diy/load_pui_ulysses.py
1836/2: %run pui_ulysses.py
1836/3: A = Animation(d,'det','sec','doy')
1836/4: A.Hist
1836/5: A.animate_polar()
1837/1: %run ./diy/load_pui_ulysses.py
1837/2: %run pui_ulysses.py
1837/3: histograms(d.data['det'],d.data['sec'])
1839/1: %run ./diy/load_pui_ulysses.py
1839/2: d.show_mask
1839/3: d.show_mask()
1839/4: d.reset_mask('ssd_0')
1839/5: d.show_mask()
1839/6: histograms(d.data['det'],d.data['sec'])
1839/7: %run pui_ulysses.py
1839/8: histograms(d.data['det'],d.data['sec'])
1839/9: pylab.close('all')
1839/10: histograms(d.data['det'],d.data['sec'])
1839/11: pylab.hist(det, bins = [0,1,2,3,4])
1839/12: ax1.hist(det, bins = [0,1,2,3,4])
1839/13: ax = pylab.plot(1,2)
1839/14: ax.hist(det, bins = [0,1,2,3,4])
1839/15: det
1839/16: det = d.get_data(['epq_mask','ssd_0','det_0'],'det')
1839/17: det
1839/18: ax.hist(det, bins = [0,1,2,3,4])
1839/19: /home/asterix/fischer/PUI/Ulysses/swics/software/libulpy/pui_ulysses.py
1839/20: fig, (ax1,ax2) = pylab.subplots(1,2,figsize=(15,10))
1839/21: ax1.hist(det, bins = [0,1,2,3,4])
1839/22: pylab.histogram
1839/23: pylab.histogram(det)
1839/24: pylab.hist(det, bins = [0,1,2,3,4])
1839/25: pylab.show()
1839/26: pylab.close('all')
1839/27: pylab.hist(det, bins = [0,1,2,3,4])
1839/28: pylab.figure()
1839/29: pylab.hist(det, bins = [0,1,2,3,4])
1839/30:
x = np.arange(5)
y = np.exp(x)
1839/31: fig1,ax1 = plt.subplots()
1840/1: %run ./diy/load_pui_ulysses.py
1841/1: %run ./diy/load_pui_ulysses.py
1841/2: %run pui_ulysses.py
1841/3: d
1841/4: histograms(d.data['det'],d.data['sec'])
1842/1: histograms(d.data['det'],d.data['sec'])
1842/2: %run pui_ulysses.py
1842/3: %run ./diy/load_pui_ulysses.py
1842/4: histograms(d.data['det'],d.data['sec'])
1842/5: d.set_mask('ssd_0','ech',0,0)
1842/6: histograms(d.data['det'],d.data['sec'])
1842/7: data = d.get_data(['epq_mask','ssd_0','det_0'],'det')
1842/8: figure()
1842/9: fig1,ax1 = plt.subplots()
1842/10: ax1.hist(data, bins = [0,1,2,3,4])
1842/11: det = d.get_data(['epq_mask','ssd_0','det_0'],'det')
1842/12: histograms(det,sec)
1842/13: sec = d.get_data(['epq_mask','ssd_0','det_0'],'sec')
1842/14: histograms(det,sec)
1842/15: d.set_mask('ssd_0','ech',1,300)
1842/16: det = d.get_data(['epq_mask','ssd_0','det_0'],'det')
1842/17: histograms(det,sec)
1842/18: d.get_data(['epq_mask','ssd_0','det_0'],'det')
1842/19: d.get_data(['epq_mask','ssd_0','det_0'],'ech')
1842/20: d.set_mask('ssd_0','ech',1,300,reset=True)
1842/21: d.get_data(['epq_mask','ssd_0','det_0'],'ech')
1842/22: det = d.get_data(['epq_mask','ssd_0','det_0'],'det')
1842/23: histograms(det,sec)
1842/24: pylab.close('all')
1842/25: d
1842/26: d
1843/1: %run ./diy/load_pui_ulysses.py
1843/2: %run pui_ulysses.py
1843/3: det = d.get_data(['epq_mask','ssd_0','det_0'],'det')
1843/4: histograms(det,sec)
1843/5: sec = d.get_data(['epq_mask','ssd_0','det_0'],'sec')
1843/6: histograms(det,sec)
1843/7: d.set_mask('ssd_0','ech',1,300,reset=True)
1843/8: det = d.get_data(['epq_mask','ssd_0','det_0'],'det')
1843/9: histograms(det,sec)
1843/10: d.set_mask('test_m','det',3,3)
1843/11: d.get_data(['test_m'],'doy')
1843/12: d.get_data(['test_m'],'tch')
1843/13: d.get_data(['test_m'],'ech')
1843/14: d.data
1843/15: d.sync_swoops()
1843/16: d.data
1843/17: d.get_data(['test_m'],'wHe+')
1844/1: %run ./diy/load_pui_ulysses.py
1844/2: %run ./diy/load_pui_ulysses.py
1844/3: d.sync_swoops()
1844/4: %run pui_ulysses.py
1844/5: t = d.get_data(['epq_mask'],'wHe+')
1844/6: histograms2(t)
1844/7: t
1844/8: t[t==inf] = 0.
1844/9: t
1844/10: histograms2(t)
1844/11: len(data1)
1844/12: len(t)
1844/13: np.arange(1,10,100)
1844/14: np.arange(1,10,1)
1844/15: %run pui_ulysses.py
1844/16: histograms2(t)
1844/17: t
1844/18: min(t)
1844/19: max(t)
1844/20: unique(t)
1846/1: %run ./diy/load_pui_ulysses.py
1846/2: %run pui_ulysses.py
1846/3: sec = d.get_data(['epq_mask','ssd_0','det_0'],'sec')
1846/4: d.sync_swoops()
1846/5: t = d.get_data(['epq_mask'],'wHe+')
1846/6: histograms2(t)
1846/7: max(t)
1846/8: t[t==inf] = 0.
1846/9: max(t)
1846/10: %run pui_ulysses.py
1846/11: histograms2(t)
1846/12: pylab.close('all')
1846/13: %run pui_ulysses.py
1846/14: histograms2(t)
1846/15: v = d.get_data(['epq_mask'],'vHe+')
1846/16: v
1846/17: %run pui_ulysses.py
1846/18: histograms2(t)
1847/1: cd ..
1847/2: from uswipha import uswipha
1847/3: d = uswipha(year=[1995],tf='all')
1847/4: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/5: d.sync_swoops()
1847/6: d.set_mask('sw','vsw',400,500)
1847/7: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/8: d.set_mask('sw2','vsw',700,800)
1847/9: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/10: d.reset_mask('all')
1847/11: d.show_mask()
1847/12: d.remove_mask('all')
1847/13: d.show_mask()
1847/14: d.set_mask('w','wHe+',2,100)
1847/15: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/16: d.dara
1847/17: d.data
1847/18: d.set_mask('Master','ech',2,100)
1847/19: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/20: d.set_mask('Master','ech',1,100,reset=True)
1847/21: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/22: d.set_mask('w','wHe+',1,100,reset=True)
1847/23: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/24: pylab.close('all')
1847/25: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/26: d.set_mask('w','wHe+',1.5,100,reset=True)
1847/27: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/28: d.hist1d("whe+")
1847/29: d.hist1d("wHe+")
1847/30: d.show_mask()
1847/31: d.remove_mask('all')
1847/32: d.show_mask()
1847/33: d.reset_mask('Master')
1847/34: d.show_mask()
1847/35: pylab.close('all')
1847/36: d.hist1d("wHe+")
1847/37: d.reset_mask('all')
1847/38: d.remove_mask('all')
1847/39: d.set_mask('slow','vsw',1,200)
1847/40: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/41: d
1847/42: d.hist1d("wHe+")
1847/43: d.hist1d("wHe+",smask=["slow"])
1847/44: d.set_mask('slow','vsw',1,300,reset=True)
1847/45: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/46: d.set_mask('slow','vsw',1,350,reset=True)
1847/47: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/48: d.hist1d("vsw")
1847/49: d.set_mask('slow','vsw',1,550,reset=True)
1847/50: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/51: d.set_mask('fast','vsw',650,1550,reset=True)
1847/52: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1847/53: pylab.close('all')
1849/1: from uswipha import uswipha
1849/2: d = uswipha(year=[1995,1996,1997],tf='all')
1849/3: d.sync_swoops()
1849/4: d.data["rng"]
1849/5: unique(d.data["rng"])
1849/6: d.set_mask('rng','rng',0,0,reset=True)
1849/7: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1850/1: %run EQ_positions_SOHO_CTOF.py
1850/2: %run EQ_positions_gui_OOP.py
1850/3: %run EQ_positions_SOHO_CTOF.py
1851/1: from uswipha import uswipha
1851/2: d = uswipha(year=[1995,1996],tf='all')
1851/3: d.sync_swoops()
1851/4: d.set_mask('rng',2,2)
1851/5: d.set_mask('rng','rng',2,2)
1851/6: d.hist1d("vsw")
1851/7: d.hist1d("ech")
1851/8: d.hist1d("ech",smask=['rng'])
1851/9: unique(d.data['ech',smask=['rng']])
1851/10: unique(d.data['ech'],smask=['rng'])
1851/11: d.data['ech']
1851/12: d.data['ech',smask=['rng']]
1851/13: d.data['ech',smask='rng']
1851/14: pylab.close('all')
1851/15: d.hist1d("ech",smask=['rng'])
1851/16: d.set_mask('rng2',2,2,reset=True)
1851/17: d.set_mask('rng2','rng',2,2,reset=True)
1851/18: d.set_mask('rng0','rng',0,0,reset=True)
1851/19: d.set_mask('rng1','rng',1,1,reset=True)
1851/20: d.hist1d("ech")
1851/21: d.remove_mask('rng')
1851/22: d.hist1d("ech")
1851/23: d.hist1d("ech",smask=['rng0'])
1851/24: d.hist1d("ech",smask=['rng1'])
1851/25: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/26: pylab.close('all')
1851/27: d.hist2d("tch","ech",binx=arange(0,1024),biny=arange(0,200))
1851/28: pylab.close('all')
1851/29: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1852/1: %run EQ_positions_SOHO_CTOF.py
1851/30: d.set_mask2d
1851/31: d.set_mask2D('Master','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/32: d.set_mask2D('Master','tch','ech',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/33: d.remove_mask(all)
1851/34: d.remove_mask('all')
1851/35: d.reset_mask('all')
1851/36: pylab.close('all')
1851/37: d.show_mask()
1851/38: d.set_mask2D('Test','tch','ech',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/39: d.add_mask('Test')
1851/40: d.set_mask2D('Test','tch','ech',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/41: d.set_mask2D('Test','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/42: pylab.close('all')
1851/43: d.set_mask2D('Test','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/44: d.set_mask2D('Test','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/45: pylab.close('all')
1851/46: d.show_mask()
1851/47: d.remove_mask('all')
1851/48: d.add_mask('Test')
1851/49: d.set_mask2D('Test','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/50: d.hist1d("vsw",smask=['Test'])
1851/51: d.hist1d("epq",smask=['Test'])
1851/52: d.hist1d("wHe+",smask=['Test'])
1851/53: pylab.close('all')
1851/54: d.set_mask2D('Test2','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/55: d.reset_mask('Test')
1851/56: d.set_mask2D('Test','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/57: d.hist1d("wHe+",smask=['Test'])
1851/58: d.hist1d("wHe+",smask=['Master'])
1851/59: d.remove_mask('all')
1851/60: pylab.close('all')
1851/61: d.set_mask2D('Test','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/62: d.add_mask('Test')
1851/63: d.set_mask2D('Test','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/64: d.hist1d("wHe+",smask=['Master'])
1851/65: d.set_mask('rng1','rng',1,1,reset=True)
1851/66: d.hist1d("wHe+",smask=['rng1'])
1851/67: d.hist2d
1851/68: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax",smask=['rng1'])
1851/69: pylab.close('all')
1851/70: pylab.close('all')
1851/71: d.remove_mask('all')
1851/72: d.add_mask('Test')
1851/73: d.set_mask2D('Test','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/74: d.hist1d("wHe+",smask=['Test'])
1851/75: d.hist1d("vsw",smask=['Test'])
1851/76: d.remove_mask('all')
1851/77: d.hist1d("vsw")
1851/78: d.set_mask('v','vsw',750.,751.,reset=True)
1851/79: d.hist1d("wHe+",smask=['Test'])
1851/80: d.hist1d("wHe+")
1851/81: d.set_mask2D('v','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1851/82: d.hist1d("wHe+")
1851/83: pylab.close('all')
1853/1: from uswipha import uswipha
1853/2: d = uswipha(year=[1995,1996],tf='all')
1853/3: d.sync_swoops()
1853/4: d.sync_traj
1853/5: d.sync_traj()
1854/1: %run pui_ulysses.py
1854/2: d = uswipha(year=[1995,1996],tf='all')
1854/3: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1854/4: d.show_mask()
1854/5: d.set_mask('ech','ech',1.,65.,reset=True)
1854/6: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1854/7: d.hist1d("ech")
1854/8: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64))
1854/9: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1854/10: pylab.close('all')
1854/11: d.set_mask('epq','epq',0.,0.,reset=True)
1854/12: d.sync_traj()
1854/13: d.sync_swoops()
1854/14: d.hist1d("vHe+")
1854/15: d.reset_mask('all')
1854/16: d.remove_mask('all')
1854/17: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1854/18: get_velocity
1854/19: d.get_velocity
1854/20: d.set_mask('epq','epq',25.,25.,reset=True)
1854/21: d.hist1d("vHe+")
1854/22: pylab.close('all')
1854/23: d.remove_mask('all')
1854/24: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1855/1: %run pui_ulysses.py
1855/2: d = uswipha(year=[1992,1999],tf='all')
1855/3: d.sync_swoops()
1855/4: d.sync_traj()
1855/5: summary_traj(d)
1855/6: d.sync_traj()
1855/7: d.data
1855/8: %run pui_ulysses.py
1855/9: summary_traj(d)
1855/10: d.data
1855/11: %run pui_ulysses.py
1855/12: summary_traj(d)
1855/13: d.data
1855/14: %run pui_ulysses.py
1855/15: summary_traj(d)
1855/16: %run pui_ulysses.py
1855/17: summary_traj(d)
1855/18: d = uswipha(year=range[1992,1999],tf='all')
1855/19: d = uswipha(year=[range(1992,1999)],tf='all')
1855/20: d = uswipha(year=arange(1992,1999),tf='all')
1855/21: range(1992,1999)
1855/22: d = uswipha(year=range(1992,1999),tf='all')
1856/1: range(1992,1999)
1857/1: %run pui_ulysses.py
1857/2: d = uswipha(year=[1993,1994],tf='all')
1857/3: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1857/4: d = uswipha(year=range(1998),tf='all')
1858/1: %run pui_ulysses.py
1858/2: d = uswipha(year=[1998],tf='all')
1858/3: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1858/4: d = uswipha(year=[1992],tf=[[1,190]])
1858/5: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
1858/6: d.set_mask('','epq',0.,105.,reset=True)
1858/7: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax",smask=[''])
1858/8: d = uswipha(year=[1994],tf=all)
1858/9: d = uswipha(year=[1994],tf='all')
1858/10: d.set_mask('','epq',0.,105.,reset=True)
1858/11: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax",smask=[''])
1858/12: d = uswipha(year=[1996,1997],tf='all')
1858/13: d.set_mask('','epq',0.,105.,reset=True)
1858/14: d = uswipha(year=[1996,1997],tf='all')
1858/15: d.set_mask('','epq',0.,105.,reset=True)
1858/16: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax",smask=[''])
1858/17: pylab.close('all')
1858/18: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax",smask=[''])
1858/19: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax",smask=[''])
1859/1: ls
1859/2: cd ..
1859/3: ls
1859/4: from swics_collimator import collimator
1859/5: c = collimator()
1859/6: from swics_collimator import collimator
1859/7: c = collimator()
1859/8: c.plot_vspace()
1859/9: c.plot()
1859/10: c.plot_detsec()
1859/11: d.plot_FoV()
1859/12: c.plot_FoV()
1859/13: c.det1
1860/1: from swics_collimator import collimator
1861/1: from swics_collimator import collimator
1861/2: c = collimator()
1861/3: c.plot()
1861/4: c.plot_FoV()
1861/5: c.plot_vspace()
1862/1: c.plot_vspace()
1862/2: from swics_collimator import collimator
1862/3: c = collimator()
1862/4: c.plot_vspace()
1862/5: c.plot_FoV()
1863/1: c.plot_FoV()
1863/2: from swics_collimator import collimator
1863/3: c = collimator()
1863/4: c.plot_FoV()
1863/5: c.plot_vseg()
1863/6: c.plot_vspace()
1864/1: from swics_collimator import collimator
1864/2: c = collimator()
1864/3: c.plot_vspace()
1865/1: from swics_collimator import collimator
1866/1: from swics_collimator import collimator
1866/2: c = collimator()
1866/3: c.plot_vspace()
1866/4: c.plot_vspace(reduced=False)
1866/5: ax = c.plot_vspace()
1866/6: from swics_collimator import collimator
1866/7: ax = c.plot_vspace()
1866/8: %run swics_collimator.py
1866/9: c = collimator()
1866/10: c.plot_vspace(ax=ax)
1867/1: from swics_collimator import collimator
1867/2: c = collimator()
1867/3: c.plot_vspace()
1867/4: pylab.close('all')
1867/5: c = collimator(calc_full=True)
1867/6: ax = c.plot_vspace()
1867/7: cc = collimator(calc_full=False)
1867/8: cc.plot_vspace(ax=ax,reduced=True)
1868/1: from swics_collimator import collimator
1868/2: c = collimator(calc_full=True)
1868/3: c.plot_vspace()
1868/4: ax = c.plot_vspace()
1868/5: cc = collimator(calc_full=False)
1868/6: cc.plot_vspace(ax=ax,reduced=True)
1869/1: c = collimator(calc_full=True)
1869/2: from swics_collimator import collimator
1869/3: c = collimator(calc_full=True)
1869/4: ax = c.plot_vspace()
1869/5: cc = collimator(calc_full=False)
1869/6: cc.plot_vspace(ax=ax,reduced=True)
1870/1: from swics_collimator import collimator
1870/2: c = collimator(calc_full=True)
1870/3: ax = c.plot_vspace()
1870/4: c = collimator(aspphi=180.,calc_full=True)
1870/5: c.plot_vspace()
1870/6: c = collimator(asptheta=180.,calc_full=True)
1870/7: c.plot_vspace()
1870/8: c = collimator(asptheta=20.,aspphi=20.,calc_full=True)
1870/9: c.plot_vspace()
1870/10: c = collimator(asptheta=-20.,aspphi=20.,calc_full=True)
1870/11: c.plot_vspace()
1870/12: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1870/13: c.plot_vspace()
1871/1: %run pui_ulysses.py
1871/2: d = uswipha(year=[1991,1994],tf='all')
1871/3: d.sync_traj()
1871/4: d.sync_swoops()
1871/5: summary_traj(d)
1872/1: %run pui_ulysses.py
1872/2: d = uswipha(year=range(1991,1994),tf='all')
1872/3: d.sync_swoops()
1872/4: d.sync_traj()
1872/5: summary_traj(d)
1872/6: %run pui_ulysses.py
1872/7: summary_traj(d)
1872/8: %run pui_ulysses.py
1872/9: summary_traj(d)
1872/10: %run pui_ulysses.py
1872/11: summary_traj(d)
1872/12: %run pui_ulysses.py
1872/13: summary_traj(d)
1873/1: d = uswipha(year=[1992,1998],tf='all')
1873/2: %run pui_ulysses.py
1873/3: d = uswipha(year=[1992,1998],tf='all')
1873/4: d.sync_traj()
1873/5: summary_traj(d)
1873/6: d = uswipha(year=range(1992,1998),tf='all')
1874/1: %run pui_ulysses.py
1874/2: d = uswipha(year=range(1992,1998),tf='all')
1874/3: d.sync_traj()
1874/4: summary_traj(d)
1874/5: %run pui_ulysses.py
1874/6: summary_traj(d)
1874/7: %run pui_ulysses.py
1874/8: pylab.close('all')
1874/9: summary_traj(d)
1874/10: %run pui_ulysses.py
1874/11: summary_traj(d)
1874/12: %run pui_ulysses.py
1874/13: summary_traj(d)
1874/14: pylab.close('all')
1874/15: summary_traj(d)
1874/16: %run pui_ulysses.py
1874/17: summary_traj(d)
1874/18: pylab.close('all')
1874/19: %run pui_ulysses.py
1874/20: summary_traj(d)
1874/21: summary_traj(d)
1874/22: %run pui_ulysses.py
1874/23: pylab.close('all')
1874/24: summary_traj(d)
1874/25: summary_traj(d)
1874/26: %run pui_ulysses.py
1874/27: pylab.close('all')
1874/28: %run pui_ulysses.py
1874/29: summary_traj(d)
1874/30: %run pui_ulysses.py
1874/31: pylab.close('all')
1874/32: summary_traj(d)
1874/33: %run pui_ulysses.py
1874/34: pylab.close('all')
1874/35: summary_traj(d)
1874/36: %run pui_ulysses.py
1874/37: %run pui_ulysses.py
1874/38: summary_traj(d)
1874/39: %run pui_ulysses.py
1874/40: summary_traj(d)
1874/41: %run pui_ulysses.py
1874/42: summary_traj(d)
1874/43: %run pui_ulysses.py
1874/44: pylab.close('all')
1874/45: summary_traj(d)
1874/46: pylab.close('all')
1874/47: %run pui_ulysses.py
1874/48: summary_traj(d)
1874/49: %run pui_ulysses.py
1874/50: summary_traj(d)
1874/51: %run pui_ulysses.py
1874/52: pylab.close('all')
1874/53: summary_traj(d)
1874/54: %run pui_ulysses.py
1874/55: summary_traj(d)
1874/56: %run pui_ulysses.py
1874/57: summary_traj(d)
1874/58: %run pui_ulysses.py
1874/59: summary_traj(d)
1876/1: from swics_collimator import collimator
1876/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1876/3: c.plot_vspace()
1876/4: c.plot_vspace(reduce_False)
1876/5: c.plot_vspace(reduce=False)
1876/6: c.plot_vspace(reduced=False)
1876/7: c.plot_vspace(reduced=True)
1876/8: pylab.close('all')
1876/9: c.plot_vspace(reduced=True)
1876/10: pylab.close('all')
1876/11: c.plot_vspace()
1876/12: from swics_collimator import collimator
1876/13: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1876/14: from swics_collimator import collimator
1876/15: c.plot_vspace()
1876/16: from swics_collimator import collimator
1876/17: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1876/18: c.plot_vspace()
1876/19: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1876/20: from swics_collimator import collimator
1876/21: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1876/22: c.plot_vspace()
1877/1: from swics_collimator import collimator
1877/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1877/3: c.plot_vspace()
1878/1: from swics_collimator import collimator
1878/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1878/3: c.plot_vspace()
1879/1: from swics_collimator import collimator
1879/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1879/3: c.plot_vspace()
1880/1: from swics_collimator import collimator
1880/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1880/3: c.plot_vspace()
1881/1: from swics_collimator import collimator
1881/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1881/3: c.plot_vspace()
1882/1: from swics_collimator import collimator
1882/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1882/3: c.plot_vspace()
1883/1: from swics_collimator import collimator
1883/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1883/3: c.plot_vspace()
1884/1: from swics_collimator import collimator
1884/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1884/3: c.plot_vspace()
1885/1: from swics_collimator import collimator
1885/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1885/3: c.plot_vspace()
1885/4: from swics_collimator import collimator
1886/1: from swics_collimator import collimator
1886/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1886/3: c.plot_vspace()
1887/1: from swics_collimator import collimator
1887/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1887/3: c.plot_vspace()
1888/1: from swics_collimator import collimator
1888/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1888/3: c.plot_vspace()
1888/4: c.plot_vspace()
1889/1: from swics_collimator import collimator
1889/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1889/3: c.plot_vspace()
1890/1: from swics_collimator import collimator
1890/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1890/3: c.plot_vspace()
1891/1: from swics_collimator import collimator
1891/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1891/3: c.plot_vspace()
1892/1: from swics_collimator import collimator
1892/2: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1892/3: c.plot_vspace()
1893/1: c.plot_vspace()
1893/2: from swics_collimator import collimator
1893/3: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1893/4: c = collimator(calc_full=True)
1893/5: c.plot_vspace()
1894/1: c = collimator(asptheta=20.,aspphi=-20.,calc_full=True)
1894/2: from swics_collimator import collimator
1894/3: c = collimator(calc_full=True)
1894/4: c.plot_vspace()
1894/5: c.plot_vspace()
1895/1: from swics_collimator import collimator
1895/2: c = collimator(calc_full=True)
1895/3: c.plot_vspace()
1895/4: ax = c.plot_vspace()
1895/5: cc = collimator(calc_full=False)
1895/6: cc.plot_vspace(ax=ax,reduced=True)
1896/1: from swics_collimator import collimator
1896/2: c = collimator(calc_full=True)
1896/3: c.plot_vspace()
1897/1: from swics_collimator import collimator
1897/2: c = collimator(calc_full=True)
1897/3: c.plot_vspace()
1897/4: from swics_collimator import collimator
1897/5: c = collimator(calc_full=True)
1897/6: c.plot_vspace()
1898/1: from swics_collimator import collimator
1898/2: c = collimator(calc_full=True)
1898/3: c.plot_vspace()
1899/1: from swics_collimator import collimator
1899/2: c = collimator(calc_full=True)
1899/3: c.plot_vspace()
1899/4: from swics_collimator import collimator
1899/5: c = collimator(calc_full=True)
1899/6: c.plot_vspace()
1899/7: from swics_collimator import collimator
1899/8: c = collimator(calc_full=True)
1899/9: c.plot_vspace()
1900/1: from swics_collimator import collimator
1900/2: c = collimator(calc_full=True)
1900/3: c.plot_vspace()
1901/1: from swics_collimator import collimator
1901/2: c = collimator(calc_full=True)
1901/3: c.plot_vspace()
1902/1: from swics_collimator import collimator
1902/2: c = collimator(calc_full=True)
1902/3: c.plot_vspace()
1903/1: from swics_collimator import collimator
1903/2: c = collimator(calc_full=True)
1903/3: c.plot_vspace()
1903/4: c = collimator(calc_full=True)
1903/5: ax = c.plot_vspace()
1903/6: cc = collimator(calc_full=False)
1903/7: cc.plot_vspace(ax=ax,reduced=True)
1904/1: %run ul_calc_traj.py
1904/2: calc_SPE(-20,20)
1905/1: from swics_collimator import collimator
1905/2: c = collimator(calc_full=True)
1905/3: ax = c.plot_vspace()
1905/4: c.plot_vseg(sec=2)
1905/5: c.plot_vseg(det=1,sec=2)
1906/1: from swics_collimator import collimator
1906/2: c = collimator(calc_full=True)
1906/3: c.vel
1906/4: c.plot_vseg(det=1,sec=2)
1907/1: from swics_collimator import collimator
1907/2: c = collimator(calc_full=True)
1907/3: c.plot_vseg(det=1,sec=2)
1907/4: ax = c.plot_vseg(det=1,sec=2)
1907/5: c.plot_vseg(ax=ax,det=2,sec=2)
1907/6: c.plot_vseg(ax=ax,det=3,sec=2)
1907/7: c.plot_vseg(ax=ax,det=0,sec=2)
1907/8:
for i in [0,1,2]:
    ax.plot_vseg(ax=ax,det=i,sec=1)
1907/9:
for i in [0,1,2]:
   c.plot_vseg(ax=ax,det=i,sec=1)
1907/10:
for i in [0,1,2]:
   c.plot_vseg(ax=ax,det=i,sec=0)
1907/11:
for i in [0,1,2]:
   c.plot_vseg(ax=ax,det=i,sec=8)
1907/12:
for i in [0,1,2]:
   c.plot_vseg(ax=ax,det=i,sec=7)
1908/1: from swics_collimator import collimator
1908/2: c = collimator(calc_full=True)
1908/3: c.plot_vseg(ax=ax,det=0,sec=2)
1908/4: c.plot_vspace()
1909/1: from swics_collimator import collimator
1910/1: from swics_collimator import collimator
1910/2: c = collimator(calc_full=True)
1910/3: ax = c.plot_vspace()
1910/4: cc = collimator(calc_full=False)
1910/5: cc.plot_vspace(ax=ax,reduced=True)
1910/6: ax = c.plot_vspace()
1910/7: cc.plot_vspace(ax=ax,reduced=True)
1911/1: %run main2_backsub.py
1912/1: %run main2_backsub.py
1913/1: %run main2_backsub.py
1914/1: %run main2_backsub.py
1915/1: %run main2_backsub.py
1916/1: %run main2_backsub.py
1916/2: 261*2
1916/3: range(11)
1916/4: range(1,11)
1917/1: %run main2_backsub.py
1918/1: %run main2_backsub.py
1919/1: from determination-anisotropy import *
1920/1: from determination.PaDataLoaders.SEPT_Data_Loader import SEPTData
1920/2: import sys
1920/3: sys.path
1922/1: sys.path
1923/1: sys.path
1923/2: import sys
1923/3: sys.path
1924/1: import determination_anisotrpy
1924/2: import determination_anisotropy
1925/1: from PaDataLoaders import SEPT_Data_Loader
1926/1: from PaDataLoaders import SEPT_Data_Loader
1927/1: from PaDataLoaders import SEPT_Data_Loader
1927/2: pip list
1932/1: import numpy
1933/1: import numpy
1933/2: from PaDataLoaders import SEPT_Data_Loader
1935/1: from PaDataLoaders import SEPT_Data_Loader
1936/1: from PaDataLoaders import SEPT_Data_Loader
1937/1: from PaDataLoaders import SEPT_Data_Loader
1938/1: from PaDataLoaders import SEPT_Data_Loader
1939/1: from PaDataLoaders import SEPT_Data_Loader
1940/1: %run main2_backsub.py
1940/2: %run main_solli.py
1941/1: %run main_solli.py
1942/1: %run main_solli.py
1943/1: %run main_solli.py
1944/1: %run main_solli.py
1945/1: %run main_solli.py
1946/1: %run main_solli.py
1946/2: %run main_solli.py
1947/1: %run main_solli.py
1948/1: %run main_solli.py
1948/2: %run main_solli.py
1948/3: %run main_solli.py
1949/1: %run main_solli.py
1949/2: %run main_solli.py
1949/3: %run main_solli.py
1949/4: %run main_solli.py
1949/5: %run main_solli.py
1949/6: %run main_solli.py
1949/7: %run main_solli.py
1950/1: %run main_solli.py
1950/2: %run main_solli.py
1950/3: %run main_solli.py
1950/4: %run main_solli.py
1950/5: %run main_solli.py
1950/6: %run main_solli.py
1950/7: %run main_solli.py
1950/8: %run main_solli.py
1950/9: %run main_solli.py
1950/10: %run main_solli.py
1950/11: %run main_solli.py
1950/12: %run main_solli.py
1950/13: %run main_solli.py
1950/14: %run main_solli.py
1950/15: %run main_solli.py
1950/16: %run main_solli.py
1950/17: %run main_solli.py
1950/18: from PaDataLoaders.SEPT_Data_Loader import SEPTData
1951/1: from PaDataLoaders.SEPT_Data_Loader import SEPTData
1952/1: %run main_solli.py
1952/2: %run main_solli.py
1953/1: %run main_solli.py
1954/1: %run main_solli.py
1955/1: %run main_solli.py
1957/1: %run main_solli.py
1957/2: %run main_solli.py
1957/3: %run main_solli.py
1957/4: %run main_solli.py
1958/1: %run main_solli.py
1959/1: %run main_solli.py
1960/1: %run main_solli.py
1961/1: %run main_solli.py
1962/1: %run main_solli.py
1963/1: %run main_solli.py
1963/2: ls
1964/1: %run main_solli.py
1965/1: %run main_solli.py
1965/2: date_c
1965/3: from Miscellanious import date_conversions as date_c
1966/1: from Miscellanious import date_conversions as date_c
1966/2: %run main_solli.py
1967/1: %run main_solli.py
1967/2: %run main_solli.py
1968/1: %run main_solli.py
1969/1: %run main_solli.py
1970/1: %run main_solli.py
1971/1: %run main_solli.py
1972/1: %run main_solli.py
1973/1: %run main_solli.py
1974/1: %run main_solli.py
1974/2: %run main_solli.py
1975/1: %run main_solli.py
1976/1: %run main_solli.py
1976/2: %run main_solli.py
1977/1: %run main_solli.py
1977/2: myfunc.leap_year(2007)
1977/3: myfunc.leap_year(2007.)
1977/4: myfunc.leap_year(2000.)
1977/5: myfunc.leap_year(2010.)
1977/6: from my_func importport leap_year
1977/7: from my_func import leap_year
1977/8: ls
1977/9: from AlteFunktionenSolli.Functions.my_func_new import leap_year
1978/1: ls
1978/2: Functions/
1978/3: from Functions.my_func_new import leap_year
1978/4: leap_year(2007)
1978/5: leap_year(2007.)
1979/1: 2017/400
1978/6: 2007/400
1979/2: 2017%400
1979/3: 200%400
1979/4: 2000/400
1979/5: year= 2000
1979/6: (399+(int(year) % 400))/400 - (3+(int(year) % 4))/4
1979/7: year = 2004
1979/8: (399+(int(year) % 400))/400 - (3+(int(year) % 4))/4
1979/9: 2004%400
1979/10: 299+4
1979/11: 303/400
1979/12: 3+2004
1979/13: 2007%4
1979/14: 3/4
1979/15: (3+(int(year) % 4))/4
1979/16: (399+(int(year) % 400))/400
1979/17: 3/2
1979/18: 3//2
1979/19: 3%2
1978/7: 2&3
1978/8: 3%2
1978/9: from Functions.my_func_new import leap_year
1978/10: leap_year(2007.)
1978/11: leap_year(2007)
1980/1: from Functions.my_func_new import leap_year
1980/2: leap_year(2007)
1981/1: %run main_solli.py
1982/1: %run main_solli.py
1983/1: %run main_solli.py
1984/1: %run main_solli.py
1986/1: %run make_ani_STA_STB_plots_backsub.py
1987/1: %run make_ani_STA_STB_plots_backsub.py
1988/1: %run make_ani_STA_STB_plots_backsub.py
1988/2: %run make_ani_STA_STB_plots_backsub.py
1989/1: %run make_ani_STA_STB_plots_backsub.py
1990/1: %run make_ani_STA_STB_plots_backsub.py
1990/2: %run make_ani_STA_STB_plots_backsub.py
1991/1: %run make_ani_STA_STB_plots_backsub.py
1991/2: readinpickle
1991/3: d
1992/1: %run make_ani_STA_STB_plots_backsub.py
1992/2: type3_STB
1992/3: angle
1992/4: Angle
1992/5: data
1992/6: data.Angle
1992/7: data.Nr
1992/8: data.long_B
1992/9: data.datum_STA_Ni
1993/1: %run make_ani_STA_STB_plots_backsub.py
1993/2: sc
1994/1: %run test_new_pickle.py
1995/1: %run test_new_pickle.py
1996/1: %run test_new_pickle.py
1996/2: d+
1996/3: d
1997/1: %run test_new_pickle.py
1997/2: d
1997/3: d.doy
1997/4: len(d)
1997/5: d.shape()
1997/6: shape(d)
1997/7: type(d)
1997/8: len(d)
1997/9: d.len
1997/10: d.len()
1997/11: d.load_PaData()
1997/12: d.name
1997/13: d.year
1997/14: d.A_1
1997/15: d.I_omni
1997/16: len(d.doy)
1998/1: import datetime
1998/2: datetime.datetime(2010,01,01)
1998/3: datetime.datetime(2010,1,1)
1999/1: %run main_solli.py
1999/2: %run main_solli.py
2000/1: %run main_solli.py
2000/2: %run main_solli.py
2001/1: %run main_solli.py
2001/2: %run main_solli.py
2001/3: %run main_solli.py
2002/1: %run main_solli.py
2002/2: %run main_solli.py
2002/3: %run main_solli.py
2002/4: %run main_solli.py
2003/1: %run main_solli.py
2004/1: %run main_solli.py
2004/2: myfunc.doy2dt(2010,333.23232)
2005/1: myfunc.doy2dt(2010,333.23232)
2005/2: %run main_solli.py
2005/3: %run main_solli.py
2005/4: date
2005/5: 2007/24
2005/6: 2007/365
2005/7: %run main_solli.py
2005/8: %run main_solli.py
2005/9: myfunc.doy2dt(2010,1.)
2005/10: 365/60/24
2005/11: myfunc.doy2dt(2010,1.2535)
2005/12: 1/24
2005/13: myfunc.doy2dt(2010,1.0417)
2006/1: myfunc.doy2dt(2010,1.0417)
2006/2: %run main_solli.py
2006/3: myfunc.leadp_year(2007)
2006/4: myfunc.leap_year(2007)
2006/5: myfunc.leap_year(2010)
2006/6: myfunc.leap_year(2014)
2006/7: myfunc.leap_year(2016)
2006/8: d = datetime.datetime(2000,10,1)
2006/9: d.year
2006/10: d.strfrtime
2006/11: str(d)
2006/12: d.strftime(%y)
2006/13: d.strftime("%y")
2006/14: d.strftime("%Y")
2007/1: %run main_solli.py
2008/1: %run main_solli.py
2009/1: %run main_solli.py
2009/2: %run main_solli.py
2009/3: %run main_solli.py
2009/4: date
2009/5: startDate
2009/6: endDate
2009/7: datetime.timedelta(startDate,endDate)
2009/8: endDate-startDate
2009/9: td = endDate-startDate
2009/10: datetime.timedelta(td)
2009/11: datetime.timedelta(days = td)
2009/12: td
2009/13: td.min
2009/14: td.seconds
2009/15: td
2009/16: startDate
2009/17: endDate
2009/18: 2*24*3600
2009/19: d1 = datetime.datetime(2007,01,01,10,00,00)
2009/20: d1 = datetime.datetime(2007,1,1,10,00,00)
2009/21: d1
2009/22: d2 = datetime.datetime(2007,1,1,14,00,00)
2009/23: d1-d2
2009/24: d2-d1
2009/25: d3 = d2-d1
2009/26: d3.seconds
2009/27: d3.days
2009/28: timedelta.days
2009/29: from datetime import timedelta
2009/30: timedelta.days(d3)
2009/31: timedelta.day(d3)
2009/32: d3.day
2009/33: d3.days
2009/34: duration.days(d3)
2009/35: from datetime import duration
2009/36: d.days
2009/37: d3.days
2010/1: d3.days
2010/2: %run main_solli.py
2011/1: %run main_solli.py
2012/1: %run main_solli.py
2012/2: %run main_solli.py
2013/1: %run main_solli.py
2014/1: %run main_solli.py
2015/1: %run main_solli.py
2015/2: %run main_solli.py
2016/1: %run main_solli.py
2017/1: %run main_solli.py
2017/2: %run main_solli.py
2018/1: %run main_solli.py
2019/1: %run main_solli.py
2020/1: %run main_solli.py
2021/1: %run main_solli.py
2022/1: %run main_solli.py
2023/1: %run main_solli.py
2023/2: %run main_solli.py
2024/1: %run main_solli.py
2025/1: %run main_solli.py
2026/1: %run main_solli.py
2027/1: %run main_solli.py
2028/1: %run main_solli.py
2028/2: %run main_solli.py
2029/1: %run main_solli.py
2030/1: %run main_solli.py
2030/2: %run main_solli.py
2031/1: %run main_solli.py
2032/1: %run main_solli.py
2033/1: %run main_solli.py
2033/2: %run main_solli.py
2033/3: %run main_solli.py
2034/1: %run main_solli.py
2035/1: %run main_solli.py
2036/1: %run main_solli.py
2037/1: %run main_solli.py
2038/1: %run main_solli.py
2039/1: %run main_solli.py
2040/1: %run main_solli.py
2041/1: %run main_solli.py
2042/1: %run main_solli.py
2043/1: %run test_new_pickle.py
2044/1: %run test_new_pickle.py
2044/2: %run test_new_pickle.py
2044/3: d
2044/4: %run test_new_pickle.py
2044/5: %run test_new_pickle.py
2044/6: %run test_new_pickle.py
2044/7: %run test_new_pickle.py
2044/8: d
2044/9: d.I_data
2045/1: from test_new_pickle import event_SEPT
2045/2: plotpath = path+pickle_suf+"1_STA_2006-12-06_19"
2045/3:
path = '/home/asterix/fischer/ANI_backsub_and_methods_HIWI_Anne_zum_Basteln/backsub_analyse/'
filen = 'Listen/richardson_event_list_all_data_vergleich_neu_oct18_dt.csv'
# path to save pickle-files
pickle_suf = 'Output_pickle/'+backsub_type+'/'

#plotpath = path+pickle_suf+"%i_STA_%s_%i"%(i,date.strftime("%Y-%m-%d"),EventTime)
plotpath = path+pickle_suf+"1_STA_2006-12-06_19"
2045/4:
backsub_type ='backsub20' #'nobacksub' #

path = '/home/asterix/fischer/ANI_backsub_and_methods_HIWI_Anne_zum_Basteln/backsub_analyse/'
filen = 'Listen/richardson_event_list_all_data_vergleich_neu_oct18_dt.csv'
# path to save pickle-files
pickle_suf = 'Output_pickle/'+backsub_type+'/'

#plotpath = path+pickle_suf+"%i_STA_%s_%i"%(i,date.strftime("%Y-%m-%d"),EventTime)
plotpath = path+pickle_suf+"1_STA_2006-12-06_19"
2045/5: e = event_SEPT(plotpath)
2045/6: e
2045/7: e.data
2045/8: e.data?
2045/9: from test_new_pickle import event_SEPT
2045/10: e = event_SEPT(plotpath)
2045/11: e.name
2046/1:
path = '/home/asterix/fischer/ANI_backsub_and_methods_HIWI_Anne_zum_Basteln/backsub_analyse/'
filen = 'Listen/richardson_event_list_all_data_vergleich_neu_oct18_dt.csv'
# path to save pickle-files
pickle_suf = 'Output_pickle/'+backsub_type+'/'

#plotpath = path+pickle_suf+"%i_STA_%s_%i"%(i,date.strftime("%Y-%m-%d"),EventTime)
plotpath = path+pickle_suf+"1_STA_2006-12-06_19"
2046/2:
path = '/home/asterix/fischer/ANI_backsub_and_methods_HIWI_Anne_zum_Basteln/backsub_analyse/'
filen = 'Listen/richardson_event_list_all_data_vergleich_neu_oct18_dt.csv'
# path to save pickle-files
pickle_suf = 'Output_pickle/'+backsub_type+'/'

#plotpath = path+pickle_suf+"%i_S
2046/3:
backsub_type ='backsub20' #'nobacksub' #

path = '/home/asterix/fischer/ANI_backsub_and_methods_HIWI_Anne_zum_Basteln/backsub_analyse/'
filen = 'Listen/richardson_event_list_all_data_vergleich_neu_oct18_dt.csv'
# path to save pickle-files
pickle_suf = 'Output_pickle/'+backsub_type+'/'

#plotpath = path+pickle_suf+"%i_STA_%s_%i"%(i,date.strftime("%Y-%m-%d"),EventTime)
plotpath = path+pickle_suf+"1_STA_2006-12-06_19"
2046/4: from test_new_pickle import event_SEPT
2046/5: e = event_SEPT(plotpath)
2046/6: e
2047/1:
backsub_type ='backsub20' #'nobacksub' #

path = '/home/asterix/fischer/ANI_backsub_and_methods_HIWI_Anne_zum_Basteln/backsub_analyse/'
filen = 'Listen/richardson_event_list_all_data_vergleich_neu_oct18_dt.csv'
# path to save pickle-files
pickle_suf = 'Output_pickle/'+backsub_type+'/'

#plotpath = path+pickle_suf+"%i_STA_%s_%i"%(i,date.strftime("%Y-%m-%d"),EventTime)
plotpath = path+pickle_suf+"1_STA_2006-12-06_19"
2047/2: from test_new_pickle import event_SEPT
2047/3: e = event_SEPT(plotpath)
2047/4: e.pickled_data
2047/5: e.pickled_data.name
2047/6: e.pickled_data.I_data
2047/7: size(e.pickled_data.I_data)
2047/8: shape(e.pickled_data.I_data)
2047/9: e.pickled_data.I_data.shape
2048/1:
backsub_type ='backsub20' #'nobacksub' #

path = '/home/asterix/fischer/ANI_backsub_and_methods_HIWI_Anne_zum_Basteln/backsub_analyse/'
filen = 'Listen/richardson_event_list_all_data_vergleich_neu_oct18_dt.csv'
# path to save pickle-files
pickle_suf = 'Output_pickle/'+backsub_type+'/'

#plotpath = path+pickle_suf+"%i_STA_%s_%i"%(i,date.strftime("%Y-%m-%d"),EventTime)
plotpath = path+pickle_suf+"1_STA_2006-12-06_19"
2048/2:
backsub_type ='backsub20' #'nobacksub' #

path = '/home/asterix/fischer/ANI_backsub_and_methods_HIWI_Anne_zum_Basteln/backsub_analyse/'
filen = 'Listen/richardson_event_list_all_data_vergleich_neu_oct18_dt.csv'
# path to save pickle-files
pickle_suf = 'Output_pickle/'+backsub_type+'/'

#plotpath = path+pickle_suf+"%i_STA_%s_%i"%(i,date.strftime("%Y-%m-%d"),EventTime)
plotpath = path+pickle_suf+"1_STA_2006-12-06_19"
2049/1: %run make_ani_STA_STB_plots_backsub.py
2049/2: %run make_ani_STA_STB_plots_backsub.py
2050/1: %run make_ani_STA_STB_plots_backsub.py
2050/2: %run make_ani_STA_STB_plots_backsub.py
2050/3: %run make_ani_STA_STB_plots_backsub.py
2050/4: %run make_ani_STA_STB_plots_backsub.py
2050/5: %run make_ani_STA_STB_plots_backsub.py
2051/1: %run make_ani_STA_STB_plots_backsub.py
2052/1: %run make_ani_STA_STB_plots_backsub.py
2052/2: %run main_solli.py
2052/3: %run make_ani_STA_STB_plots_backsub.py
2053/1: %run make_ani_STA_STB_plots_backsub.py
2053/2: %run make_ani_STA_STB_plots_backsub.py
2054/1: %run make_ani_STA_STB_plots_backsub.py
2055/1: %run make_ani_STA_STB_plots_backsub.py
2056/1: %run make_ani_STA_STB_plots_backsub.py
2057/1: %run main_solli.py
2057/2: %run make_ani_STA_STB_plots_backsub.py
2057/3: import test_new_pickle
2058/1: %run make_ani_STA_STB_plots_backsub.py
2058/2: %run make_ani_STA_STB_plots_backsub.py
2059/1: %run make_ani_STA_STB_plots_backsub.py
2059/2: event
2059/3: event.doy
2060/1: event.doy
2060/2: %run make_ani_STA_STB_plots_backsub.py
2060/3: event
2061/1: %run make_ani_STA_STB_plots_backsub.py
2062/1: %run make_ani_STA_STB_plots_backsub.py
2062/2: event
2062/3: event.doy
2062/4: x = event.get_max_sc()
2063/1: %run make_ani_STA_STB_plots_backsub.py
2064/1: %run make_ani_STA_STB_plots_backsub.py
2064/2: x = event.get_max_sc()
2065/1: %run make_ani_STA_STB_plots_backsub.py
2065/2: x = event.get_max_sc()
2065/3: x = event.get_max_sc()
2065/4: %run make_ani_STA_STB_plots_backsub.py
2065/5: x = event.get_max_sc()
2066/1: %run make_ani_STA_STB_plots_backsub.py
2066/2: x = event.get_max_sc()
2066/3: x
2067/1: %run make_ani_STA_STB_plots_backsub.py
2067/2: x = event.get_max_sc()
2068/1: %run make_ani_STA_STB_plots_backsub.py
2068/2: x = event.get_max_sc()
2068/3: x
2068/4: x.test_find_max()
2068/5: event.test_find_max()
2068/6: np.max(x)
2068/7: y = np.array[x]
2068/8: y = np.array([range(x[0],x[-1]),NaN])
2068/9: y = np.array([range(x[0],x[-1])])
2068/10: range(y[0],x[-1])
2068/11: range(x[0],x[-1])
2068/12: x
2068/13: x[0]
2068/14: range(x[0])
2068/15: int(x[0])
2068/16: y = np.array([range(int(x[0]),int(x[-1]),NaN)])
2068/17: y = np.array([range(int(x[0]),int(x[-1]))])
2068/18: np.Nan
2068/19: np.nan
2068/20: y = np.array([range(int(x[0]),int(x[-1]),np.nan)])
2068/21: np.argmax(x)
2068/22: A = 1.
2068/23: B = 2.
2068/24: C = 3.
2068/25: np.max(A,B,C)
2068/26: np.max([A,B,C])
2068/27: np.argmax([A,B,C])
2068/28: [i for i in [1,2,3]]
2068/29: [i for i in [A,B,C]]
2068/30: max_ind_sun = 1.0
2068/31: max_ind_antisun = 2.0
2068/32: max_ind_north = 3.0
2068/33: max_ind_south = 4.0
2069/1: %run make_ani_STA_STB_plots_backsub.py
2069/2: event.test_find_max()
2069/3: event.get_max_sc()
2069/4: d = {}
2069/5: d['A'] = 1.
2069/6: d['B']=2.
2069/7: d['C']=3.
2069/8: [i for i in values(d)]
2069/9: [i for i in d.values]
2069/10: len(d)
2069/11: d.values
2069/12: d.values()
2069/13: [i for i in d.values()]
2069/14: np.max(d.values())
2069/15: np.max([i for i in d.values()])
2069/16: d.get
2069/17: d.get()
2069/18: max(d)
2069/19: max(d, kex=d.get)
2069/20: max(d, key=d.get)
2069/21: d['D']=2.1
2069/22: d
2069/23: np.max(d)
2069/24: max(d)
2069/25: max(d, key=d.get)
2069/26: [i for i in d.get]
2069/27: [i for i in d.get()]
2069/28: max(d, key=d.value)
2069/29: max(d, key=d.get)
2069/30: np.max(d,key=d.get)
2069/31: d['E']=1
2069/32: d
2069/33: d['E']=1.
2069/34: d
2069/35: a = np.array([i for i in d.value()])
2069/36: d.get
2069/37: d.get()
2069/38: d.values
2069/39: d.values()
2069/40: a = np.array([i for i in d.values()])
2069/41: a
2069/42: np.max(a)
2069/43: d.get_key
2069/44: d.get(key=3.0)
2069/45: dict.items()
2069/46: d.items()
2069/47: d.interitems()
2070/1: %run make_ani_STA_STB_plots_backsub.py
2070/2: event.get_max_sc()
2070/3: sun = {"i_max" = 2.0, 'c'='blue'}
2070/4: sun = {"i_max":2.0, 'c':'blue'}
2070/5: asun = {"i_max":1.0, 'c':'green'}
2070/6: north = {"i_max":3.0, 'c':'yellow'}
2070/7: north['c']
2070/8: [i['c'] for i in [sun,asun,north]]
2070/9:
for i in north.items():
    print(i)
2070/10:
for i in [sun,asun,north]:
    print(i['c'])
2071/1: %run make_ani_STA_STB_plots_backsub.py
2071/2: event.get_max_sc()
2072/1: %run main_solli.py
2073/1: %run main_solli.py
2073/2: sept_data
2073/3: sept_data.__dict__.keys()
2073/4: sept_data.help
2073/5: sept_data.help()
2073/6: vars(sept_data)
2073/7: vars(sept_data.keys())
2073/8: vars(sept_data).keys()
2073/9: sept_data.IoA
2073/10: type(sept_data.IoA)
2073/11: sept_data.IoA.Ani
2073/12: sept_data.IoA.A
2073/13: sept_data.IoA.Ani
2073/14: d
2074/1: %run make_ani_STA_STB_plots_backsub.py
2074/2: event.get_max_sc()
2074/3: event.ani
2074/4: len(event.ani)
2074/5: len(event.doy)
2075/1: %run make_ani_STA_STB_plots_backsub.py
2075/2: event.get_max_sc()
2076/1: %run make_ani_STA_STB_plots_backsub.py
2076/2: event.get_max_sc()
2076/3: event
2076/4: event.which_tele
2076/5: event.max_int
2077/1: %run make_ani_STA_STB_plots_backsub.py
2077/2: %run make_ani_STA_STB_plots_backsub.py
2077/3: %run make_ani_STA_STB_plots_backsub.py
2077/4: data
2077/5: data.Nr
2077/6: data[0]
2077/7: data.Nr[0]
2077/8: data.Nr[1]
2077/9: data.Nr[7]
2077/10: data.date[7]
2077/11: data.Date[7]
2077/12: data.Nina_ev_num[5]
2077/13: data.Nr[5]
2077/14: doy_Ni
2077/15: day
2077/16: doy
2077/17: date
2077/18: len(date)
2077/19: date[0]
2077/20: date[5]
2077/21: date[4]
2077/22: date[2]
2077/23: date[3]
2077/24: date[4]
2077/25: data.date_sol[4]
2077/26: data.date_sol[0]
2077/27: type(date[4])
2077/28: doy_NI
2077/29: doy_Ni
2077/30: EventADoy
2077/31: X1
2077/32: startDoy
2077/33: endDoy
2077/34: error('test')
2077/35: intensity_X1
2077/36: ani_X1
2077/37: datetime.datetime(1,1,1)
2078/1: 60/12
2078/2: 60/12.
2078/3: 5*24
2079/1: from swics_collimator import collimator
2079/2: c = collimator()
2079/3: c = collimator(aspphi=0.1)
2079/4: c
2079/5: c.plot()
2080/1: c = collimator(aspphi=0.1)
2080/2: from swics_collimator import collimator
2080/3: c = collimator(aspphi=0.1)
2080/4: c.plot()
2081/1: from swics_collimator import collimator
2081/2: c = collimator(aspphi=0.1)
2081/3: c.plot()
2081/4: from swics_collimator import collimator
2081/5: c.ang_para
2081/6: len(c.ang_para)
2081/7: c.ang_perp
2081/8: c.base_points
2082/1: from swics_collimator import collimator
2082/2: c = collimator(aspphi=0.1)
2082/3: c.test_plot()
2082/4: from swics_collimator import collimator
2082/5: c.test_plot()
2083/1: from swics_collimator import collimator
2083/2: c = collimator(aspphi=0.1)
2083/3: c.test_plot()
2083/4: c.base_points
2083/5: from swics_collimator import collimator
2083/6: c.test_plot()
2084/1: from swics_collimator import collimator
2084/2: c = collimator(aspphi=0.1)
2084/3: c.test_plot()
2085/1: c.test_plot()
2085/2: from swics_collimator import collimator
2085/3: c = collimator(aspphi=0.1)
2086/1: from swics_collimator import collimator
2086/2: c = collimator(aspphi=0.1)
2086/3: c.test_plot()
2086/4: c.rax
2086/5: from swics_collimator import collimator
2086/6: c.test_plot()
2087/1: c = collimator(aspphi=0.1)
2087/2: from swics_collimator import collimator
2087/3: c = collimator(aspphi=0.1)
2087/4: c.test_plot()
2088/1: from swics_collimator import collimator
2088/2: c = collimator(aspphi=0.1)
2088/3: c.test_plot()
2089/1: from swics_collimator import collimator
2089/2: c = collimator(aspphi=0.1)
2089/3: c.test_plot()
2089/4: c.det1[0,:]
2090/1: c = collimator(aspphi=0.1)
2090/2: from swics_collimator import collimator
2090/3: c = collimator(aspphi=0.1)
2090/4: c.test_plot()
2090/5: from swics_collimator import collimator
2090/6: c = collimator(aspphi=0.1)
2090/7: c.test_plot()
2091/1: from swics_collimator import collimator
2091/2: c = collimator(aspphi=0.1)
2091/3: c.test_plot()
2092/1: from swics_collimator import collimator
2092/2: c = collimator(aspphi=0.1)
2092/3: c.test_plot()
2093/1: from swics_collimator import collimator
2093/2: c = collimator(aspphi=0.1)
2093/3: c.test_plot()
2094/1: from swics_collimator import collimator
2094/2: c = collimator(aspphi=0.1)
2094/3: c.test_plot()
2095/1: from swics_collimator import collimator
2095/2: c = collimator(aspphi=0.1)
2095/3: c.test_plot()
2095/4: from swics_collimator import collimator
2095/5: c.test_plot()
2096/1: c.test_plot()
2096/2: from swics_collimator import collimator
2096/3: from swics_collimator import collimator
2096/4: c = collimator(aspphi=0.1)
2096/5: c.test_plot()
2097/1: from swics_collimator import collimator
2097/2: c = collimator(aspphi=0.1)
2097/3: c.test_plot()
2097/4: from swics_collimator import collimator
2097/5: c = collimator(aspphi=0.1)
2097/6: c.test_plot()
2098/1: from swics_collimator import collimator
2098/2: c = collimator(aspphi=0.1)
2098/3: c.test_plot()
2099/1: %run swics_collimator.py
2099/2: from swics_collimator import collimator
2099/3: c = collimator(aspphi=0.1)
2099/4: c.test_plot()
2100/1: from swics_collimator import collimator
2100/2: c = collimator(aspphi=0.1)
2100/3: from swics_collimator import collimator
2100/4: c.test_plot()
2100/5: c.test_plot()
2100/6: from swics_collimator import collimator
2100/7: c = collimator(aspphi=0.1)
2100/8: c.test_plot()
2101/1: from swics_collimator import collimator
2101/2: c = collimator(aspphi=0.1)
2101/3: c.test_plot()
2102/1: from swics_collimator import collimator
2102/2: c = collimator(aspphi=0.1)
2102/3: c.test_plot()
2103/1: from swics_collimator import collimator
2103/2: c = collimator(aspphi=0.1)
2103/3: c.test_plot()
2104/1: from swics_collimator import collimator
2104/2: c = collimator(aspphi=0.1)
2104/3: c.test_plot()
2105/1: from swics_collimator import collimator
2105/2: c = collimator(aspphi=0.1)
2105/3: c.test_plot()
2106/1: from swics_collimator import collimator
2106/2: c = collimator(aspphi=0.1)
2106/3: c.test_plot()
2107/1: from swics_collimator import collimator
2107/2: c = collimator(aspphi=0.1)
2107/3: c = collimator(aspphi=0.1)
2108/1: from swics_collimator import collimator
2108/2: c = collimator(aspphi=0.1)
2109/1: from swics_collimator import collimator
2109/2: c = collimator(aspphi=0.1)
2109/3: c.test_plot()
2110/1: from swics_collimator import collimator
2110/2: c = collimator(aspphi=0.1)
2110/3: c.test_plot()
2111/1: from swics_collimator import collimator
2111/2: c = collimator(aspphi=0.1)
2111/3: c.test_plot()
2112/1: from swics_collimator import collimator
2112/2: c = collimator(aspphi=0.1)
2112/3: c.test_plot()
2113/1: from swics_collimator import collimator
2113/2: c = collimator(aspphi=0.1)
2113/3: c.test_plot()
2114/1: from swics_collimator import collimator
2114/2: c = collimator(aspphi=0.1)
2114/3: c.test_plot()
2115/1: from swics_collimator import collimator
2115/2: c = collimator(aspphi=0.1)
2115/3: c.test_plot()
2116/1: from swics_collimator import collimator
2116/2: c = collimator(aspphi=10.1)
2116/3: c.test_plot()
2116/4: c = collimator(aspphi=10.1, asptheta = 25.0)
2116/5: c.test_plot()
2117/1: c.test_plot()
2117/2: c = collimator(aspphi=10.1, asptheta = 25.0)
2117/3: from swics_collimator import collimator
2117/4: c = collimator(aspphi=10.1, asptheta = 25.0)
2117/5: c.test_plot()
2118/1: from swics_collimator import collimator
2118/2: c = collimator(aspphi=10.1, asptheta = 25.0)
2118/3: c.test_plot()
2119/1: from swics_collimator import collimator
2119/2: c = collimator(aspphi=10.1, asptheta = 25.0)
2119/3: c.test_plot()
2120/1: from swics_collimator import collimator
2120/2: c = collimator(aspphi=10.1, asptheta = 25.0)
2120/3: c.test_plot()
2121/1: from swics_collimator import collimator
2121/2: c = collimator(aspphi=10.1, asptheta = 0)
2121/3: c = collimator(aspphi=10.1, asptheta = 10)
2121/4: c.test_plot()
2121/5: c = collimator(aspphi=10.1, asptheta = 20)
2121/6: c.test_plot()
2121/7: c = collimator(aspphi=10.1, asptheta = 40)
2121/8: c.test_plot()
2121/9: c = collimator(aspphi=0.1)
2121/10: c.test_plot()
2122/1: c.test_plot()
2122/2: from swics_collimator import collimator
2122/3: c = collimator(aspphi=0.1)
2122/4: from swics_collimator import collimator
2122/5: c = collimator(aspphi=0.1)
2122/6: c.test_plot()
2123/1: from swics_collimator import collimator
2123/2: c = collimator(aspphi=0.1)
2123/3: c.test_plot()
2124/1: from swics_collimator import collimator
2124/2: c = collimator(aspphi=0.1)
2124/3: c.test_plot()
2125/1: from swics_collimator import collimator
2125/2: c = collimator(aspphi=0.1)
2125/3: c.test_plot()
2125/4: c = collimator(aspphi=10.1, asptheta = 20)
2125/5: c.test_plot()
2125/6: c = collimator(aspphi=-10.1, asptheta = 20)
2125/7: c.test_plot()
2126/1: c = collimator(aspphi=-10.1, asptheta = 20)
2126/2: from swics_collimator import collimator
2126/3: c = collimator(aspphi=-10.1, asptheta = 20)
2126/4: c.plot()
2126/5: c.test_plot()
2126/6: c.nrp_det
2126/7: c.nrp_sec
2126/8: c.nrp_sec
2126/9: c.ang_sec
2126/10: c.nrp_sec
2126/11: c.nrs_sec
2126/12: c.nrs_para
2126/13: c.nrs_pe
2126/14: c.nrs_perp
2127/1: from swics_collimator import collimator
2127/2: c = collimator(aspphi=-10.1, asptheta = 20)
2127/3: c.plot_detsec()
2127/4: c.plot_detsec(1,1)
2127/5: c.plot_detsec(1:3,1)
2127/6: c.plot_detsec([1,2,3],1)
2127/7: c.plot_detsec([0,1,2],1)
2127/8: ax = c.plot_detsec(1,1)
2127/9: c.plot_detsec(1,1,ax=ax)
2127/10: pylab.show
2127/11: pylab.show()
2127/12: pylab.close('all')
2127/13: pylab.show()
2127/14: c.plot_detsec(1,1,ax=ax)
2127/15: pylab.show()
2128/1: pylab.show()
2128/2: from swics_collimator import collimator
2128/3: c = collimator(aspphi=-10.1, asptheta = 20)
2128/4: axx = c.plot_detsec(0,1)
2128/5: c.plot_detsec(1,1,ax=axx)
2128/6: c.plot_detsec(2,1,ax=axx)
2129/1: from swics_collimator import collimator
2129/2: c = collimator(aspphi=-10.1, asptheta = 20,nrs_sec = 1)
2129/3: c.plot_detsec(2,1,ax=axx)
2129/4: axx = c.plot_detsec(0,1)
2129/5: c.plot_detsec(2,1,ax=axx)
2129/6: c.plot_detsec(1,1,ax=axx)
2129/7: c.test_plot()
2129/8: axx = c.test_plot()
2129/9: c.plot_detsec(1,1,ax=axx)
2130/1: c.plot_detsec(1,1,ax=axx)
2130/2: from swics_collimator import collimator
2130/3: axx = c.test_plot()
2130/4: c = collimator(aspphi=-10.1, asptheta = 20,nrs_sec = 1)
2130/5: axx = c.test_plot()
2130/6: c.plot_detsec(1,1,ax=axx)
2130/7: c.plot_detsec(0,1,ax=axx)
2130/8: c.plot_detsec(0,0,ax=axx)
2130/9:
for i in range(8):
    c.plot_detsec(0,i,ax=axx)
2131/1: from swics_collimator import collimator
2131/2: c = collimator(aspphi=-0, asptheta = 0.01,nrs_sec = 1)
2131/3: axx = c.test_plot()
2131/4:
for i in range(8):
    c.plot_detsec(0,i,ax=axx)
2131/5: c.sec0ang
2131/6: 360-315
2131/7: c.FOV
2131/8: c.FoV
2131/9: c.ang_sec
2131/10: c = collimator(aspphi=-0, asptheta = 0.01,nrs_sec = 3)
2131/11:
for i in range(8):
    c.plot_detsec(0,i,ax=axx)
2131/12: c.FoV
2131/13: c.FoV[0,0,:]
2131/14: shape(c.FoV)
2131/15: c.FoV[0,0,:,0]
2131/16: v = c.FoV[0,0,:,0]
2131/17: sqrt(v[0]**2+v[1]**2+v[2]**2)
2131/18: c.det1
2131/19: c.det1[1,1,:]
2131/20: c.det1[1,:]
2131/21: c.det1[0,:,0]
2131/22: c.det1[0,0,:]
2131/23: c.det1[0,:]
2132/1: ls
2132/2: cd PUIs
2132/3: ls
2132/4: cd ace_swics_3d/
2132/5: from ace_swics_pha_puis import ace_swics_pha_puis.py
2132/6: from ace_swics_pha_puis import ace_swics_pha_puis
2133/1: cd PUIs/ace_swics_3d/
2133/2: from ace_swics_pha_puis import ace_swics_pha_puis
2133/3: fin
2134/1: cd PUIs/ace_swics_3d/
2134/2: from ace_swics_pha_puis import ace_swics_pha_puis
2134/3: d = ace_swics_pha_puis
2134/4: d
2134/5: d.keys
2134/6: d.load_data()
2134/7: d
2135/1: from ace_swics_pha_puis import ace_swics_pha_puis
2135/2: cd PUIs/ace_swics_3d/
2135/3: from ace_swics_pha_puis import ace_swics_pha_puis
2135/4: d = ace_swics_pha_puis
2135/5: d
2135/6: d.load_data()
2135/7: load_data(d)
2137/1: import ace_swics_pha_puis
2137/2: d = ace_swics_pha_puis
2137/3: d
2138/1: import ace_swics_pha_puis_c
2138/2: from ace_swics_pha_puis import ace_swics_pha_puis_c
2138/3: d = ace_swics_pha_puis_c
2138/4: d
2138/5: d.load_data()
2139/1: ls
2139/2: import ace_swics_pha_puis
2139/3: d = ace_swics_pha_puis.ace_swics_pha_puis_c()
2139/4: from ace_swics_pha_puis import ace_swics_pha_puis_c
2139/5: d = ace_swics_pha_puis_c
2139/6: d = ace_swics_pha_puis_c()
2140/1: from ace_swics_pha_puis import ace_swics_pha_puis_c
2140/2: d = ace_swics_pha_puis_c()
2140/3: d.keys
2140/4: d.keys()
2140/5: d
2140/6: d
2140/7: d.data
2140/8: linspace(0.985+0.015/self.nrs_epq,1.015-0.015/self.nrs_epq,self.nrs_epq)
2140/9: nrs_epq = 1.
2140/10: linspace(0.985+0.015/nrs_epq,1.015-0.015/nrs_epq,nrs_epq)
2140/11: nrs_epq = 2
2140/12: linspace(0.985+0.015/nrs_epq,1.015-0.015/nrs_epq,nrs_epq)
2140/13: 1-0.015
2140/14: d.dim
2141/1: zeros(1,1)
2141/2: from numpy import zeros
2141/3: zeros(1,1)
2141/4: zeros[1,1]
2141/5: zeros((1,1))
2141/6: zeros((2,4,6))
2141/7: zeros((2,4,6,8))
2142/1: ls
2142/2: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2142/3: d = ace_swics_pha_puis_c()
2143/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2143/2: d = ace_swics_pha_puis_c()
2144/1: d = ace_swics_pha_puis_c()
2144/2: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2144/3: d = ace_swics_pha_puis_c()
2144/4: d.data
2144/5: d.set_mask('Master','wHe+',0.9,10)
2144/6: d.data
2144/7: d.set_mask('Master','wHe1+',0.9,10)
2144/8: d.show_mask()
2144/9: d.set_mask2D()
2144/10: d.set_mask2D('Master')
2144/11: d.set_mask2D('Master','tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
2144/12: d.data
2144/13: d.set_mask2D('Master','tof','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
2144/14: c
2144/15: d.data
2144/16: d.set_mask2D('Master','tof','esd',binx=arange(200,500),biny = arange(0,64),norm="ymax")
2144/17: d.remove_mask('all')
2144/18: d.reset_mask('Master')
2144/19: d.show_mask()
2144/20: d.add_mask('subset')
2144/21: pylab.close('all')
2144/22: d.set_mask('subset','wHe1+',0.9,10)
2144/23: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/24: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/25: d.data
2144/26: unique(d.data['esd'])
2144/27: d.set_mask('subset','esd',1,100)
2144/28: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/29: d.set_mask('Master','esd',1,100)
2144/30: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/31: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/32: x = numpy.arange(0,100)
2144/33: y = 0.5 * 4 * x°°(-2)
2144/34: y = 0.5 * 4 * x**(-2)
2144/35: x = numpy.arange(0.,100.)
2144/36: y = 0.5 * 4 * x**(-2)
2144/37: plot(x,y)
2144/38: pylab.show()
2144/39: pylab.plot(x,y)
2144/40: pylab.close('all')
2144/41: pylab.plot(x,y)
2144/42: y
2144/43: x = arange(1,50)
2144/44: y = 0.5 * 4 * x**(-2)
2144/45: x = arange(1.,50.)
2144/46: y = 0.5 * 4 * x**(-2)
2144/47: pylab.plot(x,y)
2144/48: y = 1/(0.5 * 4 * x**(-2))
2144/49: pylab.plot(x,y)
2144/50: pylab.close('all')
2144/51: pylab.plot(x,y)
2144/52: y2 = 1/(0.5 * 2.5 * x**(-2))
2144/53: pylab.plot(x,y2)
2144/54: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/55: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/56: d.reset_mask('subset')
2144/57: d.set_mask('subset','wHe1+',0,0.5)
2144/58: d.set_mask('subset2','wHe1+',0.5,10)
2144/59: pylab.close('all')
2144/60: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/61: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/62: d.reset_mask('subset2')
2144/63: d.set_mask('subset2','wHe1+',0.8,10)
2144/64: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/65: d.remove_mask('all')
2144/66: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/67: d.set_mask('wHe_klein','wHe1+',0.0,0.4)
2144/68: d.set_mask('wHe_mittel','wHe1+',0.4,0.8)
2144/69: d.set_mask('wHe_groß','wHe1+',0.8,10.)
2144/70: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/71: d.remove_mask('wHe_groß')
2144/72: d.set_mask('wHe_gross','wHe1+',0.8,10.)
2144/73: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/74: d.reset_mask('wHe_klein')
2144/75: d.set_mask('wHe_klein','wHe1+',0.0,0.6)
2144/76: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/77: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/78: d.reset_mask('all')
2144/79: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/80: d.set_mask('wHe_klein','wHe1+',0.0,0.6,reset_True)
2144/81: d.set_mask('wHe_klein','wHe1+',0.0,0.6,reset=True)
2144/82: d.set_mask('wHe_mittel','wHe1+',0.0,1.0,reset=True)
2144/83: d.set_mask('wHe_gross','wHe1+',0.0,10.,reset=True)
2144/84: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/85: d.set_mask('wHe_gross','wHe1+',0.8,10.,reset=True)
2144/86: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/87: d.set_mask('wHe_gross','wHe1+',1.,10.,reset=True)
2144/88: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/89: d.remove_mask('all')
2144/90: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/91: d.set_mask('epq_low','epq',0,20)
2144/92: d.set_mask('epq_medium','epq',20,40)
2144/93: d.set_mask('epq_high','epq',40,60)
2144/94: d.hist2d('tof','epq',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/95: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/96: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100))
2144/97: d.set_mask('epq_high','esd',10,600)
2144/98: d.set_mask('epq_high','esd',1,600,reset=True)
2144/99: d.set_mask('epq_medium','esd',1,600,reset=True)
2144/100: d.set_mask('epq_low','esd',1,600,reset=True)
2144/101: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100))
2144/102: d.hist2d('tof','esd',binx=arange(200,500),biny=arange(0,100),norm="ymax")
2144/103: pylab.close('all')
2145/1: d = ace_swics_pha_puis_c()
2145/2: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2145/3: d = ace_swics_pha_puis_c()
2145/4: ls
2145/5: %run PUIs/ace_swics_3d/dist3D_pui.py
2146/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2146/2: d = ace_swics_pha_puis_c()
2146/3: %run PUIs/ace_swics_3d/dist3D_pui.py
2146/4: import pycwt
2147/1: import pycwt
2148/1: import pycwt
2149/1: import pycwt
2151/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2151/2: d = ace_swics_pha_puis_c()
2151/3: %run PUIs/ace_swics_3d/dist3D_pui.py
2151/4: import pycwt
2151/5: from pycwt import Morlet
2151/6: from pycwt import cwt_f
2152/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2152/2: d = ace_swics_pha_puis_c()
2152/3: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2152/4: D = Dist3D()
2152/5: from dist3D_pui import Dist3D
2152/6: D = Dist3D()
2152/7: D = Dist3D(d)
2152/8: D.nrs_para
2152/9: D.aspphi
2152/10: D.vels
2152/11: D.vels_fac
2152/12: D.FoV
2152/13: shape(D.FoV)
2152/14: D.FoV.shape()
2152/15: D.FoV.shape
2152/16: D.FoV[0,0,0,:,:,:]
2152/17: D.FoV.shape
2152/18: D.FoV[0,0,0,0,:,:]
2152/19: D.nrs_epq
2152/20: D.vels
2152/21: D.nrs_epq
2152/22: D.vels
2152/23: D.vels_fac
2152/24: D.vels_fac*60.
2153/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2153/2: %run PUIs/ace_swics_3d/dist3D_pui.py
2153/3: d = ace_swics_pha_puis_c()
2153/4: D = Dist3D(d)
2154/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2154/2: %run PUIs/ace_swics_3d/dist3D_pui.py
2154/3: d = ace_swics_pha_puis_c()
2154/4: D = Dist3D(d)
2155/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2155/2: %run PUIs/ace_swics_3d/dist3D_pui.py
2155/3: d = ace_swics_pha_puis_c()
2155/4: D = Dist3D(d)
2156/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2156/2: d = ace_swics_pha_puis_c()
2156/3: %run dist3D_pui.py
2156/4: D = Dist3D(d)
2157/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2157/2: d = ace_swics_pha_puis_c()
2157/3: %run dist3D_pui.py
2157/4: D = Dist3D(d)
2157/5: D.vspace
2158/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2158/2: d = ace_swics_pha_puis_c()
2158/3: %run dist3D_pui.py
2158/4: D = Dist3D(d)
2158/5: d.vspace
2158/6: D.vspace
2158/7: D.vspace.shape
2159/1: from dist3D_pui import Dist3D
2159/2: d = ace_swics_pha_puis_c()
2159/3: ls
2159/4: from ace_swics_pha_puis import ace_swics_pha_puis_c
2159/5: cd ACE
2159/6: ls
2159/7: cd ..
2159/8: cd PUIs/ace_swics_3d/
2159/9: %run ace_swics_pha_puis.py
2159/10: cd ../..
2159/11: ls
2159/12: d = ace_swics_pha_puis_c()
2159/13: D = Dist3D(d)
2159/14: D.vspace
2159/15: D.vspace.shape
2159/16: D.vswbins
2159/17: iv = 0
2159/18: v = 300.
2159/19: tmpspace = D.vspace
2159/20: tmpspace =1.* D.vspace
2159/21: tmpspace[0,0,0,0,0,:,0]
2159/22: zeros(3,2)
2159/23: from numpy import zeros
2159/24: zeros(3,2)
2159/25: zeros([3,2])
2159/26: a = np.array([[0, 2, 8], [0, 2, 7], [0, 2, 5], [2, 4, 5], [ 8, 4, 7]])
2159/27: a
2159/28: np.sum(a,axis=0)
2159/29: D.vswbins
2159/30: D.d.data['aspphi']
2159/31: D.d.data['aspphi'].shape
2159/32: D.asphi
2159/33: D.aspphi
2160/1: cd PUIs/ace_swics_3d/
2160/2: %run ace_swics_pha_puis.py
2160/3: cd ../..
2160/4: %run dist3D_pui.py
2160/5: d = ace_swics_pha_puis_c()
2160/6: D = Dist3D(d)
2160/7: phiind
2160/8: D.aspphi
2160/9: D.aspphi.shape()
2160/10: D.aspphi.shape
2160/11: unique(D.d.data['epq'])
2160/12: unique(D.d.data['eq'])
2160/13: unique(D.d.data['did'])
2160/14: unique(D.d.data['sec'])
2160/15: D.d.data['vx']
2160/16: D.d.data['vx'].shape
2160/17: D.d.data['vsw']
2160/18: D.d.data['vsw'].shape
2160/19: D.d.data['vx'].T
2160/20: D.d.data['vx'].T.shape
2160/21: D.d.data['vx'].T - D.d.data['vsw']
2160/22: A = D.d.data['vx'].T - D.d.data['vsw']
2160/23: A.shape
2160/24: A = arange(1,10)
2160/25: A
2160/26: A = zeros(3,5)
2160/27: A = zeros([3,5])
2160/28:
for i in range(2):
    for j in range(4):
        A[i,j] = j*i
2160/29: A
2160/30:
for i in range(2):
    for j in range(4):
        A[i,j] = (j+1)*(i+1)
2160/31: A
2160/32:
for i in range(2):
    for j in range(4):
        A[i,j] = (j+1)*(i+1)
        print(i,j)
2160/33:
for i in range(2):
    for j in range(4):
        A[i+1,j+1] = (j+1)*(i+1)
        print(i,j)
2160/34: A
2160/35:
for i in range(2):
    for j in range(4):
        A[i+1,j+1] = 5.
2160/36: A
2160/37:
for i in range(2):
    for j in range(4):
        A[i,j] = 5.
2160/38: A
2160/39: A[1,2] = 6.
2160/40: A
2161/1: A = zeros(3,5)
2161/2: A = zeros([3,5])
2161/3: A
2161/4:
for i in range(3):
    for j in range(5):
        print(i,j)
2161/5:
for i in range(3):
    for j in range(5):
        A[i,j] = 5.
2161/6: A
2161/7: cd PUIs/ace_swics_3d/
2161/8: %run ace_swics_pha_puis.py
2161/9: cd ../..
2161/10: %run dist3D_pui.py
2161/11: D = Dist3D(d)
2161/12: d = ace_swics_pha_puis_c()
2161/13: D = Dist3D(d)
2161/14: D.d.data['vx'].shape
2161/15: D.d.data['vsw'].shape
2161/16: A
2161/17: A.shape
2161/18: B = zeros(3)
2161/19: B.shape
2161/20: B[:] = 3.
2161/21: B
2161/22: A-B
2161/23: A-B.T
2161/24: A.T - B
2161/25: A
2161/26: A.T
2161/27: B
2161/28: D.vsw
2161/29: D.vels
2161/30: D.vels.shape
2161/31: D.vswbins
2161/32: D.vswbins.shape
2161/33: around(51.,-1)
2161/34: around(51.,-2)
2161/35: D.d.data['vsw']
2161/36: around(D.d.data['vsw'][0],-1)
2161/37: D.d.data['vsw'][0]
2161/38: around(54.,-1)
2161/39: around(55.,-1)
2161/40: around(54.5,-1)
2161/41: around(54.0005,-1)
2161/42: D.d.data['vsw']
2161/43: D.d.data['vsw'][:10]
2161/44: D.d.data['vsw'][:5]
2161/45: D.vswbins
2161/46: D.d.data['vsw'][:15]
2161/47: D.d.data['vxsw']
2161/48: D.d.data['vxsw2']
2161/49: D.d.data['vx']
2161/50: D.d.data['vx'].shape
2161/51: D.d.data['vx'][0:15,0]
2161/52: D.d.data['vsw'][0:15,0]
2161/53: D.d.data['vsw'][0:15]
2161/54: D.d.data['vxsw'][0:15]
2161/55: D.d.data['vxsw'][0:15][0]
2161/56: D.d.data['vxsw2'][0:15][0]
2161/57: D.d.data['vx'][0:15,0]
2161/58: D.d.data['vsw'][0:15]
2161/59: D.d.data['vxsw'][0:15]
2161/60: D.d.data['vx'][0:15,0]
2161/61: D.d.data['vsw'][0:15]
2161/62: D.d.data['vxsw'][0:15,0]
2161/63: D.d.data['vxsw2'][0:15,0]
2161/64: around(D.d.data['vsw'][0:15],-1)
2162/1: cd PUIs/ace_swics_3d/
2162/2: %run ace_swics_pha_puis.py
2162/3: cd ../..
2162/4: %run dist3D_pui.py
2162/5: d = ace_swics_pha_puis_c()
2162/6: D = Dist3D(d)
2163/1: cd PUIs/ace_swics_3d/
2163/2: %run ace_swics_pha_puis.py
2163/3: cd ../..
2163/4: %run dist3D_pui.py
2163/5: d = ace_swics_pha_puis_c()
2163/6: %run dist3D_pui.py
2163/7: D = Dist3D(d)
2163/8: D.nrs_epq
2163/9: D.vels
2164/1: cd PUIs/ace_swics_3d/
2164/2: %run ace_swics_pha_puis.py
2164/3: cd ../..
2164/4: %run dist3D_pui.py
2164/5: d = ace_swics_pha_puis_c()
2164/6: D = Dist3D(d)
2164/7: %run dist3D_pui.py
2164/8: D = Dist3D(d)
2164/9: eff = [45.,35.,64.,2.3,8.2,]
2164/10: ind = [1,1,3,2,1]
2164/11: eff[ind]
2164/12: eff = np.array(eff)
2164/13: ind = np.array(ind)
2164/14: eff[ind]
2164/15: ind = [1,1,3,2,1,1,1,1]
2164/16: ind = np.array(ind)
2164/17: eff[ind]
2164/18: D.vels
2164/19: d.swt
2164/20: d.data
2164/21: d.data['sqt']
2164/22: d.data['swt']
2164/23: unique(d.data['swt'])
2164/24: figure(),plot(d.data["swt"])
2164/25: figure(),hist(d.data["swt"])
2164/26: figure(),hist(d.data["swt"],arange(0,300,1))
2164/27: figure(),hist(d.data["swt"],arange(0,30,0.1))
2165/1: cd PUIs/ace_swics_3d/
2165/2: %run ace_swics_pha_puis.py
2165/3: cd ../..
2165/4: %run dist3D_pui.py
2165/5: d = ace_swics_pha_puis_c()
2165/6: D = Dist3D(d)
2165/7: figure(),plot(d.data["dsw"])
2165/8: d.data
2165/9: figure(),plot(d.data["doy"])
2165/10: figure(),hist(d.data["doy"])
2165/11: figure(),hist(d.data["year"])
2165/12: unique(d.data['year'])
2165/13: figure(),hist(d.data["dsw"],arange(0,70,2))
2165/14: pylab.close('all')
2166/1: cd PUIs/ace_swics_3d/
2166/2: %run ace_swics_pha_puis.py
2166/3: cd ../..
2166/4: %run dist3D_pui.py
2166/5: d = ace_swics_pha_puis_c()
2166/6: D = Dist3D(d)
2166/7: D.calc_wspec_norm(vsws=arange(495.,800.,10.),wbins=arange(-1.,5.1,.1),min_whe=0.9)
2166/8: D.calc_muspec(vsws=arange(495.,800.,10.),wbins=arange(0.,5.1,.1),min_whe=0.9,bphi=90.,btheta=0.,dbphi=10.,dbtheta=10.,cosmubins=arange(-1.,1.01,.1))
2166/9: D.calc_wspecs2(vswbins=arange(500.,800.1,10.),wbins=arange(-1.,2.01,0.1),min_whe=0.9)
2166/10: D.calc_wpecs2(vswbins=arange(500.,800.1,10.),wbins=arange(-1.,2.01,0.1),min_whe=0.9)
2166/11: %run dist3D_pui.py
2166/12: D = Dist3D(d)
2166/13: D.calc_wpecs2(vswbins=arange(500.,800.1,10.),wbins=arange(-1.,2.01,0.1),min_whe=0.9)
2167/1: cd PUIs/ace_swics_3d/
2167/2: %run dist3D_pui.py
2167/3: %run ace_swics_pha_puis.py
2167/4: cd ../..
2167/5: %run dist3D_pui.py
2167/6: d = ace_swics_pha_puis_c()
2167/7: D = Dist3D(d)
2167/8: D.calc_wpecs2(vswbins=arange(500.,800.1,10.),wbins=arange(-1.,2.01,0.1),min_whe=0.9)
2168/1: cd PUIs/ace_swics_3d/
2168/2: %run ace_swics_pha_puis.py
2168/3: cd ../..
2168/4: %run ace_swics_pha_puis.py
2168/5: %run dist3D_pui.py
2168/6: d = ace_swics_pha_puis_c()
2168/7: D = Dist3D(d)
2168/8: D.calc_wpecs2(vswbins=arange(500.,800.1,10.),wbins=arange(-1.,2.01,0.1),min_whe=0.9)
2168/9: D.test_s
2168/10: unique(D.test_s)
2168/11: unique(D.test_w)
2168/12: D.calc_w3dspecs(vswbins=arange(500.,800.1,10.),wxbins=arange(-2.,2.01,0.2),wybins=arange(-2.,2.01,0.2),wzbins=arange(-2.,2.01,0.2),min_whe=0.9,aspphi=(-20.,20.))
2168/13: norm_arr, H = D.calc_w3dspecs(vswbins=arange(500.,800.1,10.),wxbins=arange(-2.,2.01,0.2),wybins=arange(-2.,2.01,0.2),wzbins=arange(-2.,2.01,0.2),min_whe=0.9,aspphi=(-20.,20.))
2168/14: norm_arr[norm_arr==0]=1.
2168/15: H2 = H/norm_arr
2168/16: wbins = arange(-2,2,0.2)
2168/17: wbins = arange(-2,2.01,0.2)
2168/18: pcolormesh(H2[10,:,:].T,(wbins,wbins))
2168/19: pcolormesh((wbins,wbins),H2[10,:,:].T)
2168/20: pcolormesh(wbins,wbins,H2[10,:,:].T)
2168/21: pcolormesh(wbins,wbins,H2[11,:,:].T)
2168/22: pcolormesh(wbins,wbins,H2[:,11,:].T)
2168/23: H2.shape()
2168/24: shape(H2)
2168/25: shape(norm_arr)
2168/26: pcolormesh(wbins,wbins,norm_arr[:,11,:].T)
2168/27: pcolormesh(wbins,wbins,norm_arr[:,10,:].T)
2168/28: pcolormesh(wbins,wbins,norm_arr[:,1,:].T)
2169/1: wxbins=arange(-2.,2.01,0.2)
2169/2: wxbins.shape
2169/3: cd PUIs/ace_swics_3d/
2169/4: %run ace_swics_pha_puis.py
2169/5: cd ../..
2169/6: %run dist3D_pui.py
2169/7: d = ace_swics_pha_puis_c()
2169/8: D = Dist3D(d)
2169/9: uTall,Tallind = unique(D.d.get_data("Master","d00"),return_index=True)
2169/10: uTall
2169/11: Tallind
2169/12: D.d.get_data('Master','d00'),return_index = True
2169/13: D.d.get_data('Master','d00')
2169/14: dd = D.d.get_data('Master','d00')[0:10]
2169/15: dd
2169/16: uTall,Tallind = unique(dd,return_index = True)
2169/17: uTall
2169/18: Tallind
2169/19: D.vswbins
2169/20: int(around(500.-D.vswbins[0],-1)/10)
2169/21: around(500.-D.vswbins[0])
2169/22: around(500.-D.vswbins[0],-1)
2169/23: D.asptheta
2169/24: d.data
2169/25: unique(d.get_data['asptheta'])
2169/26: unique(d.data['asptheta'])
2169/27: unique(d.data['aspphi'])
2169/28: D.aspphi
2169/29: d.aspphi
2169/30: D.aspphi
2169/31: D.asptheta
2169/32: a = arange(,10)
2169/33: a = arange(0,10)
2169/34: a
2169/35: b = arange(10,20)
2169/36: b>12
2169/37: a[b>12]
2169/38: D.vspace.shape()
2169/39: shape(D.vspace)
2169/40: shape(D.wspace)
2169/41: shape(D.w3Dspace)
2169/42: shape(D.w3dspace)
2169/43: shape(D.vswbins)
2169/44: d.data['swt']
2169/45: unique(d.data['swt'])
2169/46: w = D.d.get_data("He1+","wxsw2")
2169/47: w = d.data['wxsw2]
2169/48: w = d.data['wxsw2']
2169/49: w
2169/50: w.shape
2169/51: d.data['aspang'].shape
2169/52: d.data['vxsw']
2169/53: d.data['vxsw'].shape
2169/54: D.vspace
2169/55: D.vspace.shape
2169/56: d.data['swt'].shape
2169/57: d.data['swt'][:10]
2169/58: d.data['swt'][:20]
2169/59: d.data['swt'][:30]
2169/60: d.data['swt'][:50]
2170/1: cd PUIs/ace_swics_3d/
2170/2: %run dist3D_pui.py
2170/3: %run dist3D_pui.py
2171/1: cd PUIs/ace_swics_3d/
2171/2: %run ace_swics_pha_puis.py
2171/3: d = ace_swics_pha_puis_c()
2171/4: cd ..
2171/5: cd ..
2171/6: %run dist3D_pui.py
2171/7: d = ace_swics_pha_puis_c()
2171/8: D = Dist3D(d)
2171/9: D.w3dspace.shape
2171/10: arange(300.,800.1,10.)
2171/11: arange(500.,800.1,10.)
2171/12: arange(300.,800.1,10.).shape
2171/13: arange(500.,800.1,10.).shape
2171/14: vswbins=arange(500.,800.1,10.)
2171/15: ivoffset = int(around(vswbins[0]-D.vswbins[0],-1)/10)
2171/16: ivoffset
2171/17:
for iv,v in enumerate(vswbins[:10]):
    print iv, v
    print(%f,iv+ivoffset)
2171/18:
for iv,v in enumerate(vswbins[:10]):
    print iv, v
    print("%f",iv+ivoffset)
2171/19:
for iv,v in enumerate(vswbins[:10]):
    print iv, v
    print("%f",%iv+ivoffset)
2171/20:
for iv,v in enumerate(vswbins[:10]):
    print iv, v
    print(iv+ivoffset)
2171/21:
for iv,v in enumerate(vswbins[:10]):
    print iv, v
    print(arange(300.,800.1,10.)[iv+ivoffset])
2171/22: norm, H = D.calc_w3dspecs()
2171/23: norm
2171/24: norm.shape
2171/25: D.w3dspace
2171/26: D.w3dspace.shape
2171/27: D.w3dspace[21,1,1,[50:60],...,0,:].shape]
2171/28: D.w3dspace[21,1,1,arange(50,60,1),...,0,:].shape
2171/29: whe = D.vels/(555)
2171/30: epqs = arange(0.60,1)[whe>50]
2171/31: epqs = arange(0,60,1)[whe>50]
2171/32: epqs
2171/33: epqs[0]
2171/34: epqs.shape
2171/35: epqs = arange(0,60,1)[whe>0.9]
2171/36: epqs
2171/37: D.w3dspace[21,1,1,epqs,...,0,:].shape
2171/38: epqs = arange(0,60,1)[whe>1.9]
2171/39: epqs
2171/40: D.w3dspace[21,1,1,epqs,...,0,:].shape
2171/41: epqs = arange(0,60,1)[whe>.9]
2171/42: D.w3dspace[21,1,1,epqs,...,0,:].shape
2172/1: cd PUIs/ace_swics_3d/
2172/2: %run ace_swics_pha_puis.py
2172/3: cd ../..
2172/4: %run dist3D_pui.py
2172/5: %run dist3D_pui.py
2172/6: d = ace_swics_pha_puis_c()
2172/7: D = Dist3D(d)
2172/8: norm, H = D.calc_w3dspecs()
2172/9: norm.shape
2172/10: %run dist3D_pui.py
2172/11: norm, H = D.calc_w3dspecs()
2173/1: %run PUIs/ace_swics_3d/ace_swics_pha_puis.py
2173/2: %run dist3D_pui.py
2173/3: d = ace_swics_pha_puis_c()
2173/4: D = Dist3D(d)
2173/5: norm, H = D.calc_w3dspecs()
2173/6: d.data["wxsw2"]
2173/7: d.data["wxsw2"].shape
2173/8: D.vspace.shape
2173/9: d.vx
2173/10: d.data['vx']
2173/11: d.data['vx'][0]
2173/12: d.data['vx'][0].shape
2174/1: %run swics_collimator.py
2175/1: %run swics_collimator.py
2175/2: %run swics_collimator.py
2175/3: c = collimator(aspphi=-0, asptheta = 0.01,nrs_sec = 3)
2175/4: c.test_plot()
2176/1: c.test_plot()
2176/2: %run swics_collimator.py
2176/3: c = collimator(aspphi=-0, asptheta = 0.01,nrs_sec = 3)
2176/4: c.test_plot()
2176/5: %run swics_collimator.py
2176/6: c = collimator(aspphi=-0, asptheta = 0.01,nrs_sec = 3)
2176/7: c.test_plot()
2176/8: %run swics_collimator.py
2176/9: c = collimator(aspphi=-0, asptheta = 0.01,nrs_sec = 3)
2176/10: %run swics_collimator.py
2176/11: c.test_plot()
2176/12: pylab.close('all')
2176/13: c.test_plot()
2176/14: c = collimator(aspphi=10., asptheta = 0.01,nrs_sec = 3)
2176/15: c.test_plot()
2176/16: %run Ulysses/swics_collimator_ulysses.py
2177/1: ls
2177/2: import Ulysses.swics_collimator_ulysses
2177/3: import Ulysses.swics_collimator_ulysses.swics_collimator
2177/4: from Ulysses.swics_collimator_ulysses import collimator as c_u
2177/5: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2177/6: %run swics_collimator.py
2177/7: c = collimator(aspphi=10., asptheta = 0.01,nrs_sec = 3)
2177/8: c_u = collimator_ul(aspphi=10., asptheta = 0.01,nrs_sec = 3)
2177/9: c.test_plot()
2177/10: c_u.test_plot()
2177/11: c_u = collimator_ul(aspphi=10., asptheta = 0.01,nrs_sec = 3)
2177/12: c_u.test_plot()
2178/1: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2178/2: %run swics_collimator.py
2178/3: c = collimator(aspphi=10., asptheta = 0.01,nrs_sec = 3)
2178/4: c_u = collimator_ul(aspphi=10., asptheta = 0.01,nrs_sec = 3)
2178/5: c_u.test_plot()
2178/6: c_u = collimator_ul(aspphi=10., asptheta =2 0.01,nrs_sec = 3)
2178/7: c_u = collimator_ul(aspphi=10., asptheta =20.01,nrs_sec = 3)
2178/8: c_u.test_plot()
2178/9: c_u = collimator_ul(aspphi=10., asptheta =-20.01,nrs_sec = 3)
2178/10: c_u.test_plot()
2178/11: c = collimator(aspphi=10., asptheta = 20.01,nrs_sec = 3)
2178/12: c.test_plot()
2178/13: c = collimator(aspphi=10., asptheta = 90.01,nrs_sec = 3)
2178/14: c.test_plot()
2178/15: c_u = collimator_ul(aspphi=10., asptheta =-90.01,nrs_sec = 3)
2178/16: c_u.
2178/17: c_u.test_plot()
2178/18: pylab.close('all')
2179/1: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2179/2: c_u.test_plot()
2180/1: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2180/2: c_u = collimator_ul(aspphi=10., asptheta =-90.01,nrs_sec = 3)
2180/3: c_u = collimator_ul(aspphi=45., asptheta =20.01,nrs_sec = 3)
2180/4: c_u.test_plot()
2180/5: c_u = collimator_ul(aspphi=35., asptheta =0.01,nrs_sec = 3)
2180/6: c_u.test_plot()
2180/7: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2180/8: pylab.close('all')
2180/9: c_u = collimator_ul(aspphi=35., asptheta =0.01,nrs_sec = 3)
2180/10: c_u.test_plot()
2181/1: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2181/2: c_u = collimator_ul(aspphi=35., asptheta =0.01,nrs_sec = 3)
2181/3: c_u.test_plot()
2182/1: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2182/2: c_u = collimator_ul(aspphi=35., asptheta =0.01,nrs_sec = 3)
2182/3: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2182/4: c_u = collimator_ul(aspphi=35., asptheta =0.01,nrs_sec = 3)
2183/1: from Ulysses.swics_collimator_ulysses import collimator as collimator_ul
2183/2: c_u = collimator_ul(aspphi=35., asptheta =0.01,nrs_sec = 3)
2183/3: c_u.test_plot()
2183/4: c_u = collimator_ul(aspphi=35., asptheta =0.01,nrs_sec = 3,offset_sp=90.)
2183/5: c_u.test_plot()
2184/1: cd Ulysses/
2184/2: %run swics_collimator.py
2184/3: %run swics_collimator_ulysses.py
2184/4: cd ..
2185/1: from Ulysses.dist3D_pui_ulysses import Dist3D
2185/2: from old_stuff.Ulysses.swics.software.libulpy.uswipha import uswipha
2185/3: d = uswipha(year=[1992,1993],tf=[[1,10]])
2186/1: from old_stuff.Ulysses.swics.software.libulpy.uswipha import uswipha
2186/2: from Ulysses.dist3D_pui_ulysses import Dist3D
2186/3: d = uswipha(year=[1992,1993],tf=[[1,10]])
2186/4: D = Dist3D(d)
2186/5: d.sync_swoops
2186/6: d.sync_swoops()
2186/7: d.calc_d90()
2186/8: d.sync_swoops()
2187/1: cd old_stuff/Ulysses/swics/software/libulpy/
2187/2: form uswipha import uswipha
2187/3: from uswipha import uswipha
2187/4: d = uswipha(year=[1993],tf=[[1,10]])
2187/5: d.sync_swoops()
2188/1: d = uswipha(year=[1993],tf=[[1,10]])
2188/2: from uswipha import uswipha
2189/1: cd old_stuff/Ulysses/swics/software/libulpy/
2189/2: from uswipha import uswipha
2189/3: d = uswipha(year=[1993],tf=[[1,10]])
2189/4: d.sync_swoops()
2190/1: from old_stuff.Ulysses.swics.software.libulpy.uswipha import uswipha
2190/2: d = uswipha(year=[1993],tf=[[1,10]])
2190/3: d.sync_swoops()
2190/4: d.sync_traj()
2190/5: from old_stuff.Ulysses.swics.software.libulpy.uswipha import uswipha
2191/1: from old_stuff.Ulysses.swics.software.libulpy.uswipha import uswipha
2191/2: d = uswipha(year=[1993],tf=[[1,10]])
2191/3: d.sync_traj()
2192/1: from old_stuff.Ulysses.swics.software.libulpy.uswipha import uswipha
2192/2: d = uswipha(year=[1993],tf=[[1,10]])
2192/3: d.sync_traj()
2192/4: d.sync_swoops()
2192/5: D = Dist3D(d)
2192/6: from Ulysses.dist3D_pui_ulysses import Dist3D
2192/7: D = Dist3D(d)
2193/1: from old_stuff.Ulysses.swics.software.libulpy.uswipha import uswipha
2193/2: d = uswipha(year=[1993],tf=[[1,10]])
2193/3: d.sync_swoops()
2193/4: d.sync_traj()
2193/5: from Ulysses.dist3D_pui_ulysses import Dist3D
2193/6: D = Dist3D(d)
2193/7: d.data
2193/8: d.data['det']
2193/9: unique(d.data['det'])
2193/10: d = uswipha(year=[1993],tf='all')
2193/11: d.hist2d('det')
2193/12: d.hist1d('det')
2193/13: d.hist1d('det',bins=arange(0,4))
2193/14: d.hist1D
2193/15: hist1d
2193/16: hist1D
2193/17: d.hist1d
2193/18: d.hist1d?
2193/19: arange(0,4)
2193/20: d.hist1d('det',binx=arange(0,5))
2193/21: d.hist1d('ech',binx=arange(0,50))
2193/22: d.hist1d('ech',binx=arange(0,500))
2193/23: d.set_mask('ech','ech',0,10)
2193/24: d.hist1d('det',binx=arange(0,5))
2193/25: d.set_mask('ech','ech',0,10)
2194/1: from old_stuff.Ulysses.swics.software.libulpy.uswipha import uswipha
2194/2: d = uswipha(year=[1993,1994,1995],tf='all')
2194/3: d.hist1d('det',binx=arange(0,5))
2194/4: d.show_mask()
2194/5: unique(d.data["det"],return_counts = true)
2194/6: unique(d.data["det"],return_counts = True)
2194/7: u,c = unique(d.data["det"],return_counts = True)
2194/8: c
2194/9: sum(c)
2194/10: d.set_mask('ech','ech',0,10)
2194/11: d.hist1d('det',binx=arange(0,5))
2194/12: d.get_data?
2194/13: d.get_data(masks=['ech'],prods = ['det'])
2194/14: d.get_data(masks=['ech'],prods = ['det','ech'])
2194/15: det = d.get_data(masks=['ech'],prods = ['det'])
2194/16: u,c = unique(det,return_counts = True)
2194/17: u
2194/18: c
2194/19: sum(c)
2195/1: cd Ulysses/
2195/2: %run load_pui_ulysses.py
2195/3: d
2195/4: d.data
2195/5: D = Dist3D(d)
2196/1: %run load_pui_ulysses.py
2197/1: %run load_pui_ulysses.py
2198/1: %run load_pui_ulysses.py
2199/1: %run load_pui_ulysses.py
2200/1: %run load_pui_ulysses.py
2201/1: %run load_pui_ulysses.py
2202/1: %run load_pui_ulysses.py
2203/1: %run load_pui_ulysses.py
2204/1: %run load_pui_ulysses.py
2204/2: %run load_pui_ulysses.py
2204/3: numpy.logspace(1,3)
2204/4: numpy.logspace(1,3,num=3)
2204/5: numpy.logspace(1,3,num=3,base=e)
2204/6: steps = [100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489])
2204/7: steps = [100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489]
2204/8: steps = np.array(steps)
2204/9: plot(steps)
2204/10: plot(log(steps))
2204/11: plot(exp(steps))
2204/12: pylab.close('all')
2204/13: plot(log(steps))
2204/14: plot(exp(steps))
2204/15: fig = plot(steps)
2204/16: fig2 = plot(log(steps))
2204/17: log(steps)
2204/18: ls = log(steps)
2204/19: plot(ls)
2204/20: D.vels
2204/21: D
2205/1: %run load_pui_ulysses.py
2206/1:
print('PyDev console: using IPython 5.8.0\n')

import sys; print('Python %s on %s' % (sys.version, sys.platform))
sys.path.extend(['/home/asterix/fischer/PUI/Ulysses'])
2207/1: %run load_pui_ulysses.py
2207/2: D
2207/3: D.vels
2207/4: D.vels_fac
2208/1: D.vels_fac
2208/2: %run load_pui_ulysses.py
2208/3: D.vels_fac
2209/1: %run load_pui_ulysses.py
2210/1: %run load_pui_ulysses.py
2211/1: %run load_pui_ulysses.py
2211/2: d.data
2212/1: d.data
2212/2: %run load_pui_ulysses.py
2212/3: D.d.data['aspphi']
2212/4: D
2212/5: d
2212/6: d.data['aspphie']
2212/7: d.data['aspphi']
2213/1: %run load_pui_ulysses.py
2213/2: D.aspphi
2213/3: d.data["epq"].astype(int)
2213/4: unque(d.data["epq"].astype(int))
2213/5: unique(d.data["epq"].astype(int))
2213/6: unique(d.data["sec"].astype(int))
2213/7: unique(d.data["det"].astype(int))
2213/8: d.set_mask('Master','det',0,2)
2213/9: d.show_mask()
2213/10: unique(d.data["det"].astype(int))
2213/11: d.get_data(masks=['Master'],prods = ['det'])
2213/12: unique(d.get_data(masks=['Master'],prods = ['det']))
2213/13: d = d.set_mask('Master','det',0,2)
2213/14: unique(d.data["det"].astype(int))
2213/15: d
2214/1: unique(d.data["det"].astype(int))
2214/2: %run load_pui_ulysses.py
2214/3: d
2214/4: d.set_mask('Master','det',0,1)
2214/5: d.hist1d('det',binx=arange(0,5))
2214/6: d.set_mask('Master','det',0,1,reset=True)
2214/7: d.hist1d('det',binx=arange(0,5))
2214/8: pylab.close('all')
2214/9: d.set_mask('Master','det',0,2)
2214/10: unique(d.data["det"].astype(int))
2214/11: d.set_mask('Master','det',0,2,reset=True)
2214/12: unique(d.data["det"].astype(int))
2214/13: d.hist1d('det',binx=arange(0,5))
2215/1: %run load_pui_ulysses.py
2215/2: d.set_mask('Master','det',1,2,reset=True)
2215/3: d.hist1d('det',binx=arange(0,5))
2215/4: unique(d.data["det"].astype(int))
2215/5: d.get_data?
2215/6: dd = d.get_data(masks=['Master'],prod='all')
2215/7: dd = d.get_data(masks=['Master'],prods='all')
2215/8: dd.hist1d('det',binx=arange(0,5))
2215/9: dd
2215/10: d['Master']
2215/11: d
2215/12: d.get_mask('Master')
2215/13: d.reset_mask('all')
2215/14: d.get_mask('Master')
2215/15: d.Master
2215/16: d.mask
2215/17: d.mask['Master']
2215/18: d.mask['Master'].get()
2216/1: %run load_pui_ulysses.py
2216/2: d.data
2216/3:
for prod in d.data:
    print(prod)
2216/4: for prod
2216/5: subset = {}
2216/6:
for prod in d.data:
    subset[prod] = 'hi'
2216/7: subset
2216/8: subset = {}
2216/9:
for prod in d.data:
    subset[prod] = d.data[prod]
2216/10: subset
2216/11: d.data[prod]
2216/12: d.data[prod][d.get_mask('all')]
2216/13: d.get_mask('Master')
2216/14: d.data[prod][d.get_mask('Master')]
2217/1: d.data[prod][d.get_mask('Master')]
2217/2: %run load_pui_ulysses.py
2217/3: subset
2217/4: subset = {}
2217/5: d
2217/6:
for prod in d.data:
    subset[prod] = d.data[prod][d.get_mask('Master')]
2217/7: subset
2217/8: subset.data['det']
2217/9: subset
2217/10: subset
2217/11: type(subset)
2217/12: type(d)
2218/1: %run load_pui_ulysses.py
2218/2: cd Ulysses/
2218/3: %run load_pui_ulysses.py
2219/1: %run load_pui_ulysses.py
2220/1: %run load_pui_ulysses.py
2220/2: %run load_pui_ulysses.py
2220/3: D.d
2220/4: D.d.data
2220/5: D.d.data['det']
2220/6: unique(D.d.data['det'])
2220/7: unique
2220/8: %run load_pui_ulysses.py
2220/9: d
2220/10: D.d
2220/11: unique(d.data['det'])
2220/12: d.set_mask('Master','det',1,2,reset=True)
2220/13: unique(d.data['det'])
2220/14: d.show_mask()
2220/15: d.data[prod][d.get_mask('Master')]
2220/16: d.data['det',smask='Master']
2220/17: d = d.set_mask('Master','det',0,2)
2220/18: unique(d.data['det'])
2220/19: d.show_mask()
2221/1: d.show_mask()
2221/2: %run load_pui_ulysses.py
2221/3: d.show_mask()
2221/4: unique(d.data['det'])
2221/5: d.hist1d('det',bins=arange(0,4))
2221/6: d.hist1d('det',binx=arange(0,4))
2221/7: d.hist1d('det',binx=arange(0,6))
2221/8: d = uswipha(year=[1993,1994,1995],tf=[[1,20]])
2221/9: d.sync_traj()
2221/10: d.sync_swoops()
2221/11: d.set_mask('Master','det',0,2,reset=True)
2221/12: d.save_subset('Master')
2221/13: d1 = d.load_subset()
2221/14: d1
2221/15: d
2221/16: unique(d.data['det'])
2221/17: d.show_mask()
2221/18: d.set_mask('Master','ech',0,61)
2221/19: d.show_mask()
2221/20: d.set_mask('Master','ech',0,61,reset=True)
2221/21: d.show_mask()
2221/22: d.show_mask()
2221/23: d.reset_mask('all')
2221/24: d.show_mask()
2221/25: d.set_mask('Master','det',0,2,reset=True)
2221/26: d.show_mask()
2221/27: unique(d.data['ech'])
2221/28: unique(d.data['epq'])
2221/29: d.set_mask('Master','epq',0,61)
2221/30: d.show_mask()
2221/31: unique(d.data['epq'])
2221/32: d.set_mask('Master','epq',0,60)
2221/33: d.set_mask('Master','epq',0,60)
2221/34: unique(d.data['epq'])
2221/35: d.set_mask('Master','epq',0,60,reset=True)
2221/36: d.show_mask()
2221/37: d.set_mask('Master','epq',0,50,reset=True)
2221/38: d.show_mask()
2221/39: d.set_mask('Master','epq',0,60,reset=True)
2221/40: d.show_mask()
2222/1: %run load_pui_ulysses.py
2223/1: %run load_pui_ulysses.py
2224/1: %run load_pui_ulysses.py
2225/1: %run load_pui_ulysses.py
2225/2: %run load_pui_ulysses.py
2226/1: %run load_pui_ulysses.py
2227/1: %run load_pui_ulysses.py
2228/1: %run load_pui_ulysses.py
2229/1: %run load_pui_ulysses.py
2230/1: %run load_pui_ulysses.py
2231/1: %run load_pui_ulysses.py
2232/1: d = uswipha(year=[1993,1994,1995],tf=[[1,20]])
2232/2: from uswipha import uswipha
2232/3:
import sys
sys.path.append('/home/asterix/fischer/PUI/old_stuff/Ulysses/swics/software/libulpy')
sys.path.append('/home/asterix/fischer/PUI')
from uswipha import uswipha
2232/4: d = uswipha(year=[1993,1994,1995],tf=[[1,20]])
2232/5: d.hist1d('ech',binx=arange(0,70))
2232/6: d = uswipha(year=[1993,1994,1995],tf=[[1,80]])
2232/7: d.hist1d('ech',binx=arange(0,70))
2232/8: d.hist1d('ech',binx=arange(0,700))
2234/1: %run load_pui_ulysses.py
2234/2: D.space
2234/3: D.wspace
2234/4: D.wspac
2234/5: D.wspac
2235/1: %run load_pui_ulysses.py
2235/2: D.wspace
2235/3: D.wspace.shape
2236/1: %run load_pui_ulysses.py
2237/1: %run load_pui_ulysses.py
2237/2:
fin = open("/data/projects/ace/efficencies/%s.eff"%(self.ion),"r")
        dat = loadtxt(fin)
2237/3:
fin = open("/data/projects/ace/efficencies/%s.eff"%(self.ion),"r")
dat = loadtxt(fin)
2237/4:
fin = open("/data/projects/ace/efficencies/%s.eff"%(d.ion),"r")
dat = loadtxt(fin)
2237/5: D.ion
2237/6:
fin = open("/data/projects/ace/efficencies/%s.eff"%(D.ion),"r")
dat = loadtxt(fin)
2237/7: dat
2237/8: dat.shape
2238/1: %run ace_swics_pha_puis.py
2238/2: ls
2238/3: cd ace_swics_3d/
2238/4: ls
2238/5: %run ace_swics_pha_puis.py
2238/6: D = Dist3D(d)
2238/7: d = ace_swics_pha_puis_c()
2238/8: cd ..
2239/1: cd
2239/2: ls
2240/1: ls
2240/2: cd PUIs/ace_swics_3d/
2240/3: from ace_swics_pha_puis import ace_swics_pha_puis_c
2240/4: from ace_swics_pha_puis import ace_swics_pha_puis
2240/5: from ace_swics_pha_puis import ace_swics_pha_puis_c
2240/6: cd ../..
2240/7: d = ace_swics_pha_puis_c()
2240/8: cd PUIs/ace_swics_3d/
2240/9: from dist3D_pui import Dist3D
2240/10: cd ../..
2240/11: ls
2240/12: %run PUIs/ace_swics_3d/dist3D_pui.py
2240/13: D = dist3D_pui(d)
2240/14: import Dist3D
2240/15: from dist3D_pui import Dist3D
2240/16: D = dist3D_pui(d)
2240/17: D = dist3D(d)
2240/18: D = Dist3D_pui(d)
2240/19: D = Dist3D(d)
2240/20: d.data
2240/21: d.data['epd']
2240/22: d.data['epq']
2240/23: unique(d.data['epq'])
2241/1: %run load_pui_ulysses.py
2241/2: D._calc_phspeff_wgt()
2241/3: D.wegt_sec
2241/4: D.wgts_sec
2241/5: d.wgst_sec
2241/6: d.wgts_sec
2241/7: d.data
2241/8: d.data['eff']
2241/9: unique(d.data['eff'])
2241/10: len(unique(d.data['eff']))
2241/11: d.data['wgts_sec']
2241/12: unique(d.data['wgts_sec'])
2241/13: unique(d.data['wgts_sec']).shape
2241/14: norm_arr, H2 = D.calc_w3dspecs()
2241/15: d.data
2241/16: norm_arr, H2 = D.calc_w3dspecs()
2242/1: d = uswipha(year=[1993,1994,1995],tf=[[1,20]])
2242/2:         twts=zeros(wxsw2.shape)
2242/3:
import sys
sys.path.append('/home/asterix/fischer/PUI/old_stuff/Ulysses/swics/software/libulpy')
sys.path.append('/home/asterix/fischer/PUI')
from uswipha import uswipha
2242/4: d = uswipha(year=[1993,1994,1995],tf=[[1,20]])
2242/5: d.set_mask('Master','det',0,2,reset=True)
2242/6: d.get_data('Master','det')
2242/7: unique(d.get_data('Master','det'))
2242/8: d1 = d.get_data('Master','det')
2242/9: d1
2242/10: d.reset_mask('all')
2242/11: d.data
2243/1: %run load_pui_ulysses.py
2243/2: norm_arr, H2 = D.calc_w3dspecs()
2243/3: unique(norm_arr)
2243/4: norm_arr[norm_arr==0] = 1
2243/5: norm_arr[norm_arr==0] = 1.
2243/6: H2 = H2 / norm_arr
2243/7: H2
2243/8: wbins = arange(-2.,2.01,0.2)
2243/9: norm_arr.shape
2243/10: pcolormesh(wbins,wbins,norm_arr[10,:,:].T)
2244/1: %run load_pui_ulysses.py
2245/1: %run load_pui_ulysses.py
2246/1: %run load_pui_ulysses.py
2247/1: %run load_pui_ulysses.py
2248/1: %run load_pui_ulysses.py
2249/1: %run load_pui_ulysses.py
2249/2: norm_arr, H2 = D.calc_w3dspecs()
2249/3: norm_arr[norm_arr==0] = 1.
2249/4: H2 = H2 / norm_arr
2249/5: pcolormesh(wbins,wbins,norm_arr[10,:,:].T)
2249/6: wbins = arange(-2.,2.01,0.2)
2249/7: pcolormesh(wbins,wbins,norm_arr[10,:,:].T)
2249/8: pcolormesh(wbins,wbins,norm_arr[:,1,:].T)
2249/9: pcolormesh(wbins,wbins,norm_arr[:,2,:].T)
2249/10: pcolormesh(wbins,wbins,norm_arr[:,2,1].T)
2249/11: pcolormesh(wbins,wbins,norm_arr[:,10,:].T)
2249/12: wbins
2249/13: wbins = arange(-2.,2.01,0.1)
2249/14: pcolormesh(wbins,wbins,norm_arr[:,10,:].T)
2249/15: wbins = arange(-2.,2.01,0.2)
2249/16: size(wbins)
2249/17: pcolormesh(wbins,wbins,norm_arr[:,10,:].T)
2249/18: pcolormesh(wbins,wbins,norm_arr[1,:,:].T)
2249/19: pcolormesh(wbins,wbins,norm_arr[2,:,:].T)
2249/20: pcolormesh(wbins,wbins,norm_arr[3,:,:].T)
2249/21: pcolormesh(wbins,wbins,norm_arr[5,:,:].T)
2249/22: pcolormesh(wbins,wbins,norm_arr[10,:,:].T)
2249/23: D.w3dspace
2249/24: D.w3dspace.shape
2249/25: D.vspace
2249/26: D.vspace.shape
2249/27: D.vspace[0,0,30,0,0,:,:]
2249/28: dd = D.vspace[0,0,30,0,0,:,:]
2249/29: dd
2249/30: plot(dd)
2249/31: dd
2249/32:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
2249/33: ax.plot(dd)
2249/34: ax.plot(dd[0],dd[1],dd[2])
2249/35: dd[0,1]
2249/36: ax.plot(dd[0,0],dd[1,0],dd[2,0])
2249/37: ax.scatter(dd[0],dd[1],dd[2])
2249/38: ax.scatter(dd[0],dd[1],dd[2])
2249/39:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
2249/40: ax.scatter(dd[0],dd[1],dd[2])
2249/41:
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
2249/42: pylab.close('all')
2249/43: ax.scatter(dd[0],dd[1],dd[2])
2249/44: pylab.show
2249/45:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
2249/46: ax.set_xlabel('x')
2249/47: ax.set_ylabel('y')
2249/48: ax.scatter(dd[0],dd[1],dd[2])
2249/49:
fig1 = plt.figure()
ax1 = fig1.add_subplot(111, projection='3d')
2249/50: D.FoV.shape
2249/51: f = D.FoV[0,0,0,0,:,:]
2249/52: ax.scater(f[0],f[1],f[2])
2249/53: ax.scatter(f[0],f[1],f[2])
2249/54: f[0]
2249/55: ax1.scatter(f[0],f[1],f[2])
2249/56: ax1.set_xlabel('x')
2249/57: ax1.set_ylabel('y')
2249/58: f1 = f[:,1]
2249/59: ax1.scatter(f1[0],f1[1],f1[2])
2249/60: dd1 = dd[:,1]
2249/61: ax.scatter(dd1[0],dd1[1],dd1[2])
2249/62: dd1
2249/63: d
2249/64: dd
2249/65: D.w3dspace.shape
2249/66: ww3 = D.w3dspace[20,0,0,20,0,0,:,:]
2249/67: ww3
2249/68: pylab.close('all')
2249/69:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
2249/70:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel('x')
ax.set_ylabel('y')
2249/71: ax.scatter(ww3[0],ww3[1],ww3[2])
2249/72: pylab.close('all')
2249/73:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel('x')
ax.set_ylabel('y')
2249/74: ax.scatter(ww3[0],ww3[1],ww3[2])
2249/75: D.wspace.shape
2249/76: ww = D.wspace[20,0,0,20,0,0,:,:]
2249/77: ww
2249/78: d.data[0]
2249/79: d.data
2249/80: d.data.keys
2249/81: d.data.keys()
2249/82: d.data['vzsw']
2249/83: d.data['vzsw'][0]
2249/84: D.vspace.shape
2249/85: D.vspace[0,0,0,0,0,1]
2249/86: norm_arr
2249/87: pcolormesh(wbins,wbins,norm_arr[:,:,:].T)
2249/88: pcolormesh(wbins,wbins,norm_arr[:,15,:].T)
2250/1: %run load_pui_ulysses.py
2250/2: norm_arr, H = D.calc_w3dpecs()
2250/3: norm_arr, H = D.calc_w3dspecs()
2250/4: norm_arr[norm_arr==0] = 1.
2250/5: H2 = H / norm_arr
2250/6: wbins = arange(-2.,2.01,0.2)
2250/7: pcolormesh(wbins,wbins,norm_arr[:,10,:].T)
2250/8: pcolormesh(wbins,wbins,norm_arr[1,:,:].T)
2250/9: pcolormesh(wbins,wbins,norm_arr[6,:,:].T)
2250/10: pcolormesh(wbins,wbins,norm_arr[4,:,:].T)
2250/11: pcolormesh(wbins,wbins,norm_arr[5,:,:].T)
2250/12: pcolormesh(wbins,wbins,norm_arr[6,:,:].T)
2250/13: pcolormesh(wbins,wbins,norm_arr[7,:,:].T)
2250/14: pcolormesh(wbins,wbins,norm_arr[8,:,:].T)
2250/15: pcolormesh(wbins,wbins,norm_arr[9,:,:].T)
2250/16: pcolormesh(wbins,wbins,norm_arr[12,:,:].T)
2250/17: pcolormesh(wbins,wbins,norm_arr[14,:,:].T)
2250/18: pcolormesh(wbins,wbins,H2[10,:,:].T)
2250/19: pcolormesh(wbins,wbins,H2[8,:,:].T)
2250/20: pcolormesh(wbins,wbins,H2[6,:,:].T)
2250/21: pcolormesh(wbins,wbins,H2[12,:,:].T)
2250/22: pcolormesh(wbins,wbins,H2[11,:,:].T)
2250/23: pcolormesh(wbins,wbins,H2[15,:,:].T)
2250/24: ww = D.wspace[20,0,0,20,0,0,:,:]
2250/25: ww
2250/26:
for i in range(10):
    ww = D.wspace[20,0,0,15+i,0,0,:,:]
    print(ww[0]-ww[-1])
2250/27:
for i in range(10):
    ww = D.wspace[20,0,0,15+i,0,0,:,:]
    print(ww)
    print(ww[0]-ww[-1])
2250/28: ww
2250/29: ww[0,0]
2250/30: ww[0,-1]
2250/31:
for i in range(10):
    ww = D.wspace[20,0,0,15+i,0,0,:,:]
    print(ww)
    print(ww[0,0]-ww[0,-1])
2250/32:
for i in range(10):
    ww = D.wspace[20,0,0,15+i,0,0,:,:]
    print(ww[0,0]-ww[0,-1])
2250/33:
for i in range(10):
    ww = D.wspace[20,0,0,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/34:
for i in range(10):
    ww = D.wspace[40,0,0,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/35:
for i in range(10):
    ww = D.wspace[50,0,0,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/36:
for i in range(10):
    ww = D.wspace[10,0,0,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/37: D.wspace.shape
2250/38:
for i in range(10):
    ww = D.wspace[5,0,0,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/39:
for i in range(10):
    ww = D.wspace[45,0,0,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/40:
for i in range(10):
    ww = D.wspace[45,5,5,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/41:
for i in range(10):
    ww = D.wspace[45,45,5,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/42:
for i in range(10):
    ww = D.wspace[45,25,5,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/43:
for i in range(10):
    ww = D.wspace[45,5,5,5+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/44:
for i in range(10):
    ww = D.wspace[45,5,5,25+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/45:
for i in range(10):
    ww = D.wspace[45,5,5,45+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/46:
for i in range(10):
    ww = D.wspace[45,5,5,1+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/47:
for i in range(10):
    ww = D.wspace[5,5,5,1+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/48:
for i in range(10):
    ww = D.wspace[45,0,0,1+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/49:
for i in range(10):
    ww = D.wspace[45,0,0,5+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/50:
for i in range(10):
    ww = D.wspace[45,0,0,35+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/51:
for i in range(10):
    ww = D.wspace[45,0,0,25+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/52:
for i in range(10):
    ww = D.wspace[45,0,0,15+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/53:
for i in range(10):
    ww = D.wspace[45,0,0,10+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/54:
for i in range(10):
    ww = D.wspace[15,0,0,10+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/55:
for i in range(10):
    ww = D.wspace[5,0,0,10+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/56:
for i in range(10):
    ww = D.wspace[5,0,0,20+i,0,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/57:
for i in range(10):
    ww = D.wspace[5,0,0,20+i,5,0,:,:]
    print(min(ww[0])-max(ww[0]))
2250/58:
for i in range(10):
    ww = D.wspace[5,0,0,20+i,0,5,:,:]
    print(min(ww[0])-max(ww[0]))
2250/59:
for i in range(10):
    ww = D.wspace[5,0,0,20+i,0,2,:,:]
    print(min(ww[0])-max(ww[0]))
2250/60:
for i in range(5):
    ww = D.wspace[5,0,0,20+i,0,5,:,:]
    print(min(ww[0])-max(ww[0]))
2250/61:
for i in range(5):
    ww = D.wspace[5,0,0,20+i,0,3,:,:]
    print(min(ww[0])-max(ww[0]))
2250/62:
for i in range(5):
    ww = D.wspace[5,0,0,20+i,0,4,:,:]
    print(min(ww[0])-max(ww[0]))
2250/63:
for i in range(5):
    ww = D.wspace[5,0,0,20+i,0,6,:,:]
    print(min(ww[0])-max(ww[0]))
2250/64:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel('x')
ax.set_ylabel('y')
2250/65: ax.scatter(ww3[0],ww3[1],ww3[2])
2250/66: ww3 = D.w3dspace[5,0,0,20,0,:,:,:]
2250/67: ax.scatter(ww3[0,0],ww3[0,1],ww3[0,2])
2250/68: ax.scatter(ww3[2,0],ww3[2,1],ww3[2,2])
2250/69: pylab.close('all')
2250/70:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel('x')
ax.set_ylabel('y')
2250/71:
for i in range(8):
    ax.scatter(ww3[i,0],ww3[i,1],ww3[i,2])
2250/72: ax.scatter(0,0,0,s=3)
2250/73: ax.scatter(0,0,0,s=5,c='k')
2250/74: ax.plot([0,2],[0,2],[0,2])
2250/75: ax.plot([0,2],[0,0],[0,0])
2250/76: ww2 = D.w3dspace[25,0,0,20,0,:,:,:]
2250/77:
for i in range(8):
    ax.scatter(ww2[i,0],ww2[i,1],ww2[i,2])
2250/78: ww2 = D.w3dspace[25,0,15,20,0,:,:,:]
2250/79:
for i in range(8):
    ax.scatter(ww2[i,0],ww2[i,1],ww2[i,2])
2250/80: ww2 = D.w3dspace[25,0,90,20,0,:,:,:]
2250/81: ww2 = D.w3dspace[25,35,0,20,0,:,:,:]
2250/82:
for i in range(8):
    ax.scatter(ww2[i,0],ww2[i,1],ww2[i,2])
2251/1: c = collimator(aspphi=10., asptheta = 0 ,nrs_sec = 1)
2251/2: from swics_collimator_ulysses import collimator
2251/3: c = collimator(aspphi=10., asptheta = 0 ,nrs_sec = 1)
2251/4: c.test_plot()
2251/5: %run load_pui_ulysses.py
2252/1: %run load_pui_ulysses.py
2252/2: ww2 = D.w3dspace[25,0,0,20,0,:,:,:]
2252/3: D.wspace.shape
2252/4: w = D.wspace[20,0,0,30,:,:,:]
2252/5: w
2252/6: w.shape
2252/7: ax
2252/8:
        fig = plt.figure()
        ax = fig.add_subplot(111,projection='3d')
        ax.set_xlim(-2.5, 2.5)
        ax.set_ylim(-2.5, 2.5)
        ax.set_zlim(-2.5, 2.5)
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_zlabel('z')
ax
2252/9: ax.scatter(w)
2252/10: ax.scatter(w[...,0,:],w[...,1,:],w[...,2,0])
2252/11: D.wspace.shape
2252/12: D.w3dspace.shape
2252/13: w = D.w3dspace[20,0,0,30,:,0,:,:]
2252/14: ax.scatter(w[...,0,:],w[...,1,:],w[...,2,0])
2252/15: ax.scatter(w[...,0,:],w[...,1,:],w[...,2,:])
2252/16:
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel('x')
ax.set_ylabel('y')
2252/17: ax.scatter(w[...,0,:],w[...,1,:],w[...,2,:])
2252/18: D.w3dspace.shape
2253/1: D.w3dspace.shape
2253/2: %run load_pui_ulysses.py
2253/3: D
2253/4: D.plot_wspace()
2253/5: import pylab as plt
2253/6: D.plot_wspace()
2253/7: import pylab as plt
2254/1: import pylab as plt
2255/1: %run load_pui_ulysses.py
2255/2: D.plot_wspace()
2256/1: %run load_pui_ulysses.py
2256/2: D.plot_wspace()
2257/1: %run load_pui_ulysses.py
2257/2: %run load_pui_ulysses.py
2257/3: D.plot_wspace()
2258/1: D.plot_wspace()
2258/2: %run load_pui_ulysses.py
2258/3: D.plot_wspace()
2258/4: w
2259/1: w
2259/2: %run load_pui_ulysses.py
2259/3: D.plot_wspace()
2260/1: %run load_pui_ulysses.py
2260/2: D.plot_wspace()
2260/3: D.w
2260/4: D.w.shape
2260/5: D.w.shpae[2]
2260/6: D.w.shape[2]
2260/7: range(D.w.shape[-2])
2260/8: range(D.w.shape[-3])
2261/1: %run load_pui_ulysses.py
2262/1: %run load_pui_ulysses.py
2262/2: D.plot_wspace()
2263/1: %run load_pui_ulysses.py
2263/2: D.plot_wspace()
2264/1: D.plot_wspace()
2264/2: %run load_pui_ulysses.py
2264/3: D.plot_wspace()
2265/1: %run test_col
2265/2: ls
2266/1: %run test_col
2266/2: scatter3d()
2266/3: scatter3d(1,1,1)
2266/4: scatter3d(1,1,1,'b')
2267/1: %run test_col
2267/2: scatter3d(1,1,1,'b')
2268/1: %run test_col
2268/2: scatter3d(1,1,1,'b')
2269/1: scatter3d(1,1,1,'b')
2269/2: %run test_col
2269/3: pylab.show()
2271/1: %run test_col
2271/2: pylab.show()
2271/3: scatter3d(1,1,1,'b')
2272/1: %run test_col
2272/2: scatter3d(1,1,1,'b')
2272/3: %run load_pui_ulysses.py
2272/4: D.plot_wspace()
2273/1: %run load_pui_ulysses.py
2273/2: D.plot_wspace()
2274/1: %run load_pui_ulysses.py
2274/2: D.plot_wspace()
2275/1: %run load_pui_ulysses.py
2275/2: D.plot_wspace()
2275/3: %run load_pui_ulysses.py
2275/4: D.plot_wspace()
2276/1: %run load_pui_ulysses.py
2276/2: D.plot_wspace()
2276/3: linspace(1,1,5)
2276/4: linspace(1,2,5)
2277/1: %run load_pui_ulysses.py
2277/2: D.plot_wspace()
2278/1: %run load_pui_ulysses.py
2278/2: D.plot_wspace()
2278/3: %run load_pui_ulysses.py
2278/4: D.plot_wspace()
2279/1: %run load_pui_ulysses.py
2279/2: D.plot_wspace()
2280/1: %run load_pui_ulysses.py
2280/2: D.plot_wspace()
2280/3: %run load_pui_ulysses.py
2280/4: D.plot_wspace()
2281/1: %run load_pui_ulysses.py
2281/2: D.plot_wspace()
2282/1: %run load_pui_ulysses.py
2282/2: %run load_pui_ulysses.py
2282/3: D.plot_wspace()
2283/1: %run load_pui_ulysses.py
2283/2: D.plot_wspace()
2284/1: %run load_pui_ulysses.py
2284/2: D.plot_wspace()
2285/1: %run load_pui_ulysses.py
2285/2: D.plot_wspace()
2285/3: [1,2,3]*4
2285/4: [[1,2,3]]*4
2286/1: %run load_pui_ulysses.py
2286/2: D.plot_wspace()
2287/1: %run load_pui_ulysses.py
2287/2: D.plot_wspace()
2288/1: %run load_pui_ulysses.py
2288/2: D.plot_wspace()
2289/1: %run load_pui_ulysses.py
2289/2: D.plot_wspace()
2290/1: %run load_pui_ulysses.py
2290/2: D.plot_wspace()
2291/1: %run load_pui_ulysses.py
2291/2: D.plot_wspace()
2292/1: %run load_pui_ulysses.py
2292/2: D.plot_wspace()
2293/1: %run load_pui_ulysses.py
2293/2: D.plot_wspace()
2293/3: %run load_pui_ulysses.py
2294/1: %run load_pui_ulysses.py
2294/2: D.plot_wspace()
2295/1: %run load_pui_ulysses.py
2295/2: D.plot_wspace()
2296/1: %run load_pui_ulysses.py
2296/2: D.plot_wspace()
2297/1: %run load_pui_ulysses.py
2297/2: D.plot_wspace()
2297/3: col_arr = array([[0,0,255],[127,0,255],[255,0,255],[255,0,127],[255,0,0],[255,128,0],[255,255,0],[128,255,0]])
2297/4: col_arr[0]/255.
2297/5: col_arr[0]/255.*10
2297/6: [col_arr[0]/255.]*10
2298/1: %run load_pui_ulysses.py
2298/2: D.plot_wspace()
2299/1: %run load_pui_ulysses.py
2299/2: D.plot_wspace()
2299/3: col_arr = array([[0,0,255],[127,0,255],[255,0,255],[255,0,127],[255,0,0],[255,128,0],[255,255,0],[128,255,0]])
2299/4: [col_arr[0]] * 10
2299/5: nrs_arr = linspace(0,1,nrs)
2299/6: nrs = 10
2299/7: nrs_arr = linspace(0,1,nrs)
2299/8: nrs_arr
2299/9: col_arr[i]
2299/10: col_arr[0]*nrs_arr
2299/11: col_arr[0]
2299/12: nrs_arr
2299/13: [col_arr[0]]*nrs_arr
2299/14: col_arr[0]/255. * nrs_arr[1]
2299/15: col_arr[0]/255. * nrs_arr[2]
2299/16: col_arr[0]/255. * nrs_arr[0]
2299/17: [col_arr[0]/255.] * nrs_arr[1]
2300/1: %run load_pui_ulysses.py
2300/2: D.plot_wspace()
2301/1: %run load_pui_ulysses.py
2301/2: D.plot_wspace()
2301/3: nrs = 10
2301/4: nrs_arr = linspace(0,1,nrs)
2301/5: len(nrs_arr)
2301/6: range(10)
2302/1: %run load_pui_ulysses.py
2302/2: D.plot_wspace()
2303/1: %run load_pui_ulysses.py
2303/2: D.plot_wspace()
2304/1: %run load_pui_ulysses.py
2304/2: D.plot_wspace()
2304/3: nrs_arr = logspace(0.2,1,nrs)
2304/4: logspace(0.2,1,10)
2304/5: logspace(0.2,1,num=10.)
2304/6: logspace(0.2,log(1),num=10.)
2304/7: logspace(log(0.2),log(1),num=10.)
2305/1: %run load_pui_ulysses.py
2305/2: D.plot_wspace()
2305/3: zeros(5,3)
2305/4: zeros((5,3))
2305/5: fgure(),plot(d.data["dsw"])
2306/1: %run testtt
2307/1: %run testtt
2308/1: %run testtt
2309/1: %run testtt
2310/1: %run testtt
2311/1: %run testtt
2311/2: A = lighten_color(1,2,3)
2311/3: A
2311/4: A = lighten_color(0,0,255)
2311/5: A
2311/6: colors = array([[0,0,255],[127,0,255],[255,0,255]])
2311/7: colors[1,0]
2312/1: %run testtt
2313/1: %run testtt
2313/2: r
2313/3: g
2313/4: b
2313/5: lighten_color
2313/6: lighten_color(r,g,b,factor=0.1)
2313/7:
for j in range(5):
    print(j)
2313/8: lighten_color(r,g,b,factor=0)
2313/9: lighten_color(r,g,b,factor=1)
2313/10: lighten_color(r,g,b,factor=2)
2314/1: %run testtt
2314/2: range(0.5)
2314/3: range(1)
2314/4: range(0,0.5)
2314/5: range(0,0.5,3)
2314/6: range(0,5,3)
2314/7: range(0,5)
2315/1: %run testtt
2316/1: %run testtt
2317/1: %run testtt
2318/1: %run testtt
2319/1: %run testtt
2320/1: %run testtt
2321/1: %run testtt
2322/1: %run testtt
2323/1: %run testtt
2324/1: %run testtt
2325/1: %run testtt
2325/2: colors = array([[0,0,255],[127,0,255],[255,0,255]])
2325/3: colors[0]
2326/1: colors[0]
2326/2: %run testtt
2327/1: %run testtt
2328/1: %run testtt
2329/1: %run testtt
2329/2: col_arr
2330/1: %run testtt
2331/1: %run testtt
2332/1: %run testtt
2333/1: %run testtt
2334/1: %run testtt
2335/1: %run testtt
2335/2: col_arr
2336/1: %run testtt
2336/2: col_arr
2336/3: col_arr[0,:]
2337/1: %run testtt
2338/1: %run testtt
2338/2: [0,0,230]/255.
2338/3: [0,0,230]/250
2339/1: %run testtt
2339/2: pylab.show()
2340/1: %run testtt
2340/2: [1 2 3]
2340/3: [1,2,3]
2341/1: %run testtt
2341/2: rgb
2341/3: rgb /255.
2342/1: %run testtt
2342/2: pylab.show()
2343/1: %run testtt
2344/1: %run testtt
2345/1: %run testtt
2345/2: %run testtt
2346/1: %run testtt
2346/2: %run testtt
2347/1: %run testtt
2348/1: %run load_pui_ulysses.py
2349/1: %run load_pui_ulysses.py
2350/1: %run load_pui_ulysses.py
2351/1: %run load_pui_ulysses.py
2351/2: D.plot_wspace()
2352/1: D.plot_wspace()
2352/2: %run load_pui_ulysses.py
2352/3: D.plot_wspace()
2353/1: %run load_pui_ulysses.py
2353/2: D.plot_wspace()
2354/1: %run load_pui_ulysses.py
2354/2: D.plot_wspace()
2355/1: %run load_pui_ulysses.py
2355/2: D.plot_wspace()
2357/1: D.plot_wspace()
2357/2: %run load_pui_ulysses.py
2357/3: D.plot_wspace()
2358/1: %run load_pui_ulysses.py
2358/2: D.plot_wspace()
2359/1: %run load_pui_ulysses.py
2359/2: D.plot_wspace()
2360/1: %run load_pui_ulysses.py
2360/2: D.plot_wspace()
2361/1: %run load_pui_ulysses.py
2361/2: D.plot_wspace()
2362/1: %run load_pui_ulysses.py
2362/2: D.plot_wspace()
2363/1: %run load_pui_ulysses.py
2363/2: D.plot_wspace()
2364/1: %run load_pui_ulysses.py
2364/2: D.plot_wspace()
2365/1: D.plot_wspace()
2365/2: %run load_pui_ulysses.py
2365/3: D.plot_wspace()
2366/1: %run load_pui_ulysses.py
2366/2: D.plot_wspace()
2367/1: %run load_pui_ulysses.py
2367/2: D.plot_wspace()
2368/1: %run load_pui_ulysses.py
2368/2: D.plot_wspace()
2369/1: %run load_pui_ulysses.py
2369/2: D.plot_wspace()
2370/1: %run load_pui_ulysses.py
2370/2: D.plot_wspace()
2371/1: %run load_pui_ulysses.py
2371/2: %run load_pui_ulysses.py
2371/3: D.plot_wspace()
2372/1: %run load_pui_ulysses.py
2372/2: D.plot_wspace()
2373/1: %run load_pui_ulysses.py
2373/2: D.plot_wspace()
2373/3: d
2373/4: d
2373/5: D.plot_wspace()
2374/1: %run load_pui_ulysses.py
2374/2: D.plot_wspace()
2375/1: %run load_pui_ulysses.py
2375/2: D.plot_wspace()
2376/1: %run load_pui_ulysses.py
2376/2: D.plot_wspace()
2377/1: %run load_pui_ulysses.py
2377/2: D.plot_wspace()
2377/3: D.plot_wspace(sec=[0])
2377/4: D.plot_wspace(sec=0)
2378/1: D.plot_wspace(sec=[0])
2378/2: %run load_pui_ulysses.py
2378/3: D.plot_wspace(sec=[0])
2378/4: D.plot_wspace(sec=0)
2379/1: %run load_pui_ulysses.py
2379/2: D.plot_wspace(sec=0)
2380/1: %run load_pui_ulysses.py
2380/2: D.plot_wspace(sec=0)
2381/1: %run load_pui_ulysses.py
2381/2: D.plot_wspace(sec=0)
2382/1: %run load_pui_ulysses.py
2382/2: D.plot_wspace(sec=0)
2383/1: %run load_pui_ulysses.py
2383/2: D.plot_wspace(sec=0)
2384/1: %run load_pui_ulysses.py
2384/2: D.plot_wspace(sec=0)
2385/1: %run load_pui_ulysses.py
2385/2: D.plot_wspace(sec=0)
2385/3: D.w3dspace
2385/4: D.w3dspace.shape
2385/5: D.w3dspace[0,0,0,...].shape
2385/6: D.w3dspace[0,0,0,0,...].shape
2385/7: D.w3dspace[0,0,0,0,;,...].shape
2385/8: D.w3dspace[0,0,0,0,:,...].shape
2385/9: D.w3dspace[0,0,0,0,:,:,:,:].shape
2385/10: D.w3dspace[0,0,0,0,:,0,:,:].shape
2386/1: %run load_pui_ulysses.py
2386/2: D.w3dspace[0,0,0,0,:,0,:,:].shape
2386/3: D.plot_wspace(sec=0)
2386/4: D.FoV.shape
2387/1: %run load_pui_ulysses.py
2387/2: D.plot_FoV()
2387/3: D.plot_FoV(sec=6)
2388/1: %run load_pui_ulysses.py
2388/2: D.plot_FoV(sec=6)
2388/3: D.plot_FoV(sec=0)
2389/1: D.plot_FoV(sec=6)
2389/2: %run load_pui_ulysses.py
2389/3: D.plot_FoV(sec=6)
2389/4: D.lot_FoV(sec=3)
2389/5: D.lot_FoV(sec=3)
2390/1: %run load_pui_ulysses.py
2390/2: D.plot_FoV(sec=3)
2390/3: a = D.plot_FoV(sec=3)
2390/4: D.plot_FoV(sec=6, ax = a)
2391/1: %run load_pui_ulysses.py
2391/2: a = D.plot_FoV(sec=3)
2391/3: D.plot_FoV(sec=6, ax = a)
2392/1: %run make_ani_STA_STB_plots_backsub.py
2393/1: %run make_ani_STA_STB_plots_backsub.py
2394/1: %run make_ani_STA_STB_plots_backsub.py
2394/2: event
2394/3: a = np.array([1,4,2,5,8,1,2])
2394/4: np.argmax(a)
2395/1: %run make_ani_STA_STB_plots_backsub.py
2395/2: event
2395/3: event.get_max_sc()
2395/4: event.max_int
2395/5: event.which_tele
2396/1: %run make_ani_STA_STB_plots_backsub.py
2396/2: year
2396/3: doy_Ni
2396/4: date[i]
2396/5: date[i].hour
2396/6: date[i].minute
2396/7: doy_Ni+(float(date[i].hour)/24.)+(float(date[i].minute)/24./60.)
2396/8: doy_Ni+(float(date[i].hour)/24.)+(float(date[i].minute)/24./60.)-0.5
2396/9: doy_Ni+(float(date[i].hour)/24.)+(float(date[i].minute)/24./60.)+0.5
2396/10: X1
2396/11: X2
2397/1: %run make_ani_STA_STB_plots_backsub.py
2398/1: %run make_ani_STA_STB_plots_backsub.py
2398/2: event
2398/3: event.get_max_sc()
2398/4: event.ani_multi_plot_sept()
2399/1: %run make_ani_STA_STB_plots_backsub.py
2399/2: event.get_max_sc()
2399/3: event.ani_multi_plot_sept()
2400/1: %run make_ani_STA_STB_plots_backsub.py
2400/2: event.ani_multi_plot_sept()
2401/1: %run make_ani_STA_STB_plots_backsub.py
2401/2: event.get_max_sc()
2401/3: %run make_ani_STA_STB_plots_backsub.py
2401/4: event.get_max_sc()
2401/5: event.get_max_sc()
2401/6: event.ani_multi_plot_sept()
2401/7: X¹
2401/8: X1
2402/1: %run make_ani_STA_STB_plots_backsub.py
2402/2: event.get_max_sc()
2402/3: event.ani_multi_plot_sept()
2403/1: %run make_ani_STA_STB_plots_backsub.py
2403/2: pickled_data
2404/1: %run make_ani_STA_STB_plots_backsub.py
2404/2: event.pcikled_data
2404/3: event.pickled_data
2404/4: event.pickled_data.data
2404/5: event.pickled_data
2404/6: event.pickled_data.keys
2404/7: event.pickled_data.name
2404/8: event.pickled_data.nr
2404/9: event.pickled_data.Nr
2405/1: %run make_ani_STA_STB_plots_backsub.py
2406/1: %run make_ani_STA_STB_plots_backsub.py
2407/1: %run make_ani_STA_STB_plots_backsub.py
2408/1: %run make_ani_STA_STB_plots_backsub.py
2408/2: EventTime
2408/3: date
2408/4: dateRich
2409/1: %run make_ani_STA_STB_plots_backsub.py
2410/1: %run make_ani_STA_STB_plots_backsub.py
2410/2: i = 1
2410/3: i += 1
2410/4: i
2411/1: %run make_ani_STA_STB_plots_backsub.py
2411/2: %run main_solli.py
2412/1: import sys
2412/2: sys
2412/3: sys?
2412/4: sys.path
2412/5: %run main_solli.py
2413/1: %run main_solli.py
2415/1: %run main_solli.py
2416/1: %run main_solli.py
2417/1: %run main_solli.py
2418/1: %run main_solli.py
2419/1: %run main_solli.py
2420/1: %run main_solli.py
2421/1: %run main_solli.py
2422/1: %run make_ani_STA_STB_plots_backsub.py
2422/2: event.pickled_data
2423/1: event
2424/1: %run make_ani_STA_STB_plots_backsub.py
2425/1: %run make_ani_STA_STB_plots_backsub.py
2425/2: event
2426/1: %run make_ani_STA_STB_plots_backsub.py
2426/2: event
2426/3: event.pickled_data
2426/4: event.pickled_data.date
2426/5: event.pickled_data.doy
2426/6: year
2426/7: dateRich
2427/1: %run main_solli.py
2428/1: %run make_ani_STA_STB_plots_backsub.py
2429/1: %run make_ani_STA_STB_plots_backsub.py
2430/1: %run make_ani_STA_STB_plots_backsub.py
2431/1: %run make_ani_STA_STB_plots_backsub.py
2432/1: %run make_ani_STA_STB_plots_backsub.py
2433/1: %run make_ani_STA_STB_plots_backsub.py
2434/1: %run make_ani_STA_STB_plots_backsub.py
2435/1: %run make_ani_STA_STB_plots_backsub.py
2436/1: %run make_ani_STA_STB_plots_backsub.py
2437/1: %run make_ani_STA_STB_plots_backsub.py
2437/2: event.pickled_data
2437/3: event.pickled_data.sc
2437/4: event.pickled_data.name
2438/1: event.pickled_data.name
2438/2: %run make_ani_STA_STB_plots_backsub.py
2438/3: outgile
2438/4: outfile
2439/1: %run make_ani_STA_STB_plots_backsub.py
2439/2: event
2439/3: event.pickled_data.date
2439/4: event.pickled_data.year
2439/5: event.pickled_data.date.size
2440/1: event.pickled_data.date.size
2440/2: %run make_ani_STA_STB_plots_backsub.py
2441/1: %run make_ani_STA_STB_plots_backsub.py
2441/2: event.date
2443/1: event.date
2443/2: %run make_ani_STA_STB_plots_backsub.py
2444/1: %run make_ani_STA_STB_plots_backsub.py
2444/2: event
2444/3: event.pickled_data.settings
2445/1: %run make_ani_STA_STB_plots_backsub.py
2446/1: %run make_ani_STA_STB_plots_backsub.py
2447/1: %run make_ani_STA_STB_plots_backsub.py
2448/1: %run make_ani_STA_STB_plots_backsub.py
2449/1: %run make_ani_STA_STB_plots_backsub.py
2449/2: doy
2449/3: doy_Ni
2449/4: 17.22-17.512
2449/5: 0.292/24.
2449/6: ani_X1
2449/7: ani_X1 - ani_X2
2449/8: (ani_X1 - ani_X2) *24
2449/9: (intensity_X1 - intensity_X2) *24
2450/1: %run make_ani_STA_STB_plots_backsub.py
2451/1: %run make_ani_STA_STB_plots_backsub.py
2452/1: %run main_solli.py
2453/1: %run main_solli.py
2454/1: %run make_ani_STA_STB_plots_backsub.py
2455/1: %run main_solli.py
2455/2: a = []
2455/3: a.append(1)
2455/4: a
2457/1: %run main_solli.py
2458/1: %run make_ani_STA_STB_plots_backsub.py
2459/1: %run make_ani_STA_STB_plots_backsub.py
2459/2: event
2459/3: event.pickled_data.pa_data
2457/2: fail
2457/3: range(7,20)
2457/4: a = range(7,20)
2457/5: a
2457/6: np.range(7,20)
2457/7: arange(7,20)
2457/8: range(7,20)
2457/9: a = range(7,20)
2457/10: a.len
2457/11: a
2457/12: a.type
2457/13: type(a)
2457/14: print(a)
2457/15:
for i in range(7,20):
    print(i)
2457/16:
for i in range(19,30):
    print(i)
2460/1: %run main_solli.py
2461/1: %run make_ani_STA_STB_plots_backsub.py
2462/1: %run make_ani_STA_STB_plots_backsub.py
2463/1: %run make_ani_STA_STB_plots_backsub.py
2464/1: %run make_ani_STA_STB_plots_backsub.py
2465/1: %run make_ani_STA_STB_plots_backsub.py
2466/1: %run make_ani_STA_STB_plots_backsub.py
2467/1: %run make_ani_STA_STB_plots_backsub.py
2468/1: %run make_ani_STA_STB_plots_backsub.py
2469/1: %run make_ani_STA_STB_plots_backsub.py
2470/1: %run make_ani_STA_STB_plots_backsub.py
2471/1: %run make_ani_STA_STB_plots_backsub.py
2471/2: energyrange
2472/1: %run make_ani_STA_STB_plots_backsub.py
2472/2: date
2472/3: date[0]
2472/4: date[5]
2472/5: myfunc.date2doy()
2472/6: date[5].day
2472/7: date[5].minute
2472/8: doy_Ni = myfunc.date2doy(date[i].year,date[i].month,date[i].day)
2472/9: doy_Ni
2472/10: doy_Ni = myfunc.date2doy(date[i].year,date[i].month,date[i].day)
2473/1: %run make_ani_STA_STB_plots_backsub.py
2474/1: %run make_ani_STA_STB_plots_backsub.py
2474/2: event.pickled_data.I_omni
2474/3: event.pickled_data.I_omni
2474/4: event.pickled_data.I_data
2474/5: event.pickled_data.IoA
2474/6: event.pickled_data.IoA.Iomni
2474/7: event.pickled_data
2475/1: %run make_ani_STA_STB_plots_backsub.py
2476/1: %run make_ani_STA_STB_plots_backsub.py
2477/1: %run make_ani_STA_STB_plots_backsub.py
2478/1: %run make_ani_STA_STB_plots_backsub.py
2478/2: event.pickled_data.IoA
2478/3: event.pickled_data.settings
2478/4: event.pickled_data.settings.backsub
2478/5: event.pickled_data.settings['backsub']
2478/6: d = event.pickled_data.settings['backsub']
2478/7: d
2478/8: d = d[0]
2478/9: d
2478/10: d
2478/11: d.timetuple()
2478/12: d.timetuple().tm_yday
2478/13: d.timetuple(year)
2478/14: d.timetuple()
2478/15: d.timetuple().year
2478/16: d.timetuple().tm_yday
2479/1: %run make_ani_STA_STB_plots_backsub.py
2480/1: %run make_ani_STA_STB_plots_backsub.py
2480/2: event.backsub
2480/3: event.backsub_to_doy()
2480/4: event.backsub
2481/1: %run make_ani_STA_STB_plots_backsub.py
2481/2: event.backsub_to_doy()
2481/3: event.backsub
2481/4: d
2481/5: event.backsub[0].timetuple()
2482/1: a = [2,1]
2482/2: a.sort()
2482/3: a
2483/1: %run make_ani_STA_STB_plots_backsub.py
2483/2: event.backsub_to_doy()
2483/3: a = event.backsub_to_doy()
2483/4: a[0] - a[1]
2483/5: (a[0] - a[1])/24
2483/6: (a[0] - a[1])*24
2483/7: (a[0] - a[1])*24*60
2484/1: %run make_ani_STA_STB_plots_backsub.py
2485/1: %run make_ani_STA_STB_plots_backsub.py
2486/1: %run make_ani_STA_STB_plots_backsub.py
2487/1: %run make_ani_STA_STB_plots_backsub.py
2488/1: %run make_ani_STA_STB_plots_backsub.py
2489/1: %run make_ani_STA_STB_plots_backsub.py
2490/1: %run make_ani_STA_STB_plots_backsub.py
2491/1: %run make_ani_STA_STB_plots_backsub.py
2492/1: %run make_ani_STA_STB_plots_backsub.py
2493/1: %run make_ani_STA_STB_plots_backsub.py
2493/2: event
2493/3: event.pickled_data.year
2493/4: event.pickled_data.date
2493/5: event.pickled_data.settings
2493/6: event.pickled_data.settings['date'].tiemtuple()
2493/7: event.pickled_data.settings['date'].timetuple()
2493/8: event.pickled_data.settings['date'].timetuple().tm_year
2494/1: %run make_ani_STA_STB_plots_backsub.py
2495/1: %run make_ani_STA_STB_plots_backsub.py
2496/1: %run make_ani_STA_STB_plots_backsub.py
2497/1: %run make_ani_STA_STB_plots_backsub.py
2498/1: %run make_ani_STA_STB_plots_backsub.py
2499/1: %run make_ani_STA_STB_plots_backsub.py
2500/1: %run make_ani_STA_STB_plots_backsub.py
2501/1: %run make_ani_STA_STB_plots_backsub.py
2502/1: %run make_ani_STA_STB_plots_backsub.py
2503/1: %run make_ani_STA_STB_plots_backsub.py
2504/1: %run make_ani_STA_STB_plots_backsub.py
2505/1: %run make_ani_STA_STB_plots_backsub.py
2506/1: %run make_ani_STA_STB_plots_backsub.py
2507/1: %run make_ani_STA_STB_plots_backsub.py
2507/2: %run make_ani_STA_STB_plots_backsub.py
2508/1: %run make_ani_STA_STB_plots_backsub.py
2509/1: %run make_ani_STA_STB_plots_backsub.py
2510/1: %run make_ani_STA_STB_plots_backsub.py
2511/1: %run make_ani_STA_STB_plots_backsub.py
2512/1: %run make_ani_STA_STB_plots_backsub.py
2512/2: pylab.show()
2512/3: pylab.close('all')
2513/1: pylab.close('all')
2513/2: %run make_ani_STA_STB_plots_backsub.py
2460/2: fail
2514/1: %run make_ani_STA_STB_plots_backsub.py
2515/1: %run make_ani_STA_STB_plots_backsub.py
2516/1: %run make_ani_STA_STB_plots_backsub.py
2517/1: %run make_ani_STA_STB_plots_backsub.py
2518/1: %run make_ani_STA_STB_plots_backsub.py
2519/1: %run make_ani_STA_STB_plots_backsub.py
2520/1: %run make_ani_STA_STB_plots_backsub.py
2521/1: %run make_ani_STA_STB_plots_backsub.py
2522/1: %run make_ani_STA_STB_plots_backsub.py
2523/1: %run make_ani_STA_STB_plots_backsub.py
2524/1: %run make_ani_STA_STB_plots_backsub.py
2525/1: %run make_ani_STA_STB_plots_backsub.py
2526/1: %run make_ani_STA_STB_plots_backsub.py
2527/1: %run make_ani_STA_STB_plots_backsub.py
2528/1: %run make_ani_STA_STB_plots_backsub.py
2529/1: %run main_solli.py
2528/2: 63/23.
2528/3: event
2528/4: event.ani
2528/5: event.ani.len
2528/6: event.ani.shape
2528/7: event.doy.shape
2531/1: %run main_solli.py
2532/1: %run make_ani_STA_STB_plots_backsub.py
2533/1: %run make_ani_STA_STB_plots_backsub.py
2534/1: %run make_ani_STA_STB_plots_backsub.py
2535/1: %run make_ani_STA_STB_plots_backsub.py
2536/1: %run make_ani_STA_STB_plots_backsub.py
2537/1: %run make_ani_STA_STB_plots_backsub.py
2537/2: event
2537/3: event.ani_at_Imax
2538/1: %run make_ani_STA_STB_plots_backsub.py
2539/1: %run make_ani_STA_STB_plots_backsub.py
2540/1: %run make_ani_STA_STB_plots_backsub.py
2540/2: time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg
2541/1: %run make_ani_STA_STB_plots_backsub.py
2542/1: %run make_ani_STA_STB_plots_backsub.py
2542/2: event.time_I_max
2543/1: %run make_ani_STA_STB_plots_backsub.py
2543/2: event.time_max_ani
2543/3: event.time_I_max
2544/1: %run make_ani_STA_STB_plots_backsub.py
2545/1: %run make_ani_STA_STB_plots_backsub.py
2546/1: %run make_ani_STA_STB_plots_backsub.py
2547/1: %run make_ani_STA_STB_plots_backsub.py
2548/1: %run make_ani_STA_STB_plots_backsub.py
2549/1: %run make_ani_STA_STB_plots_backsub.py
2550/1: %run make_ani_STA_STB_plots_backsub.py
2551/1: %run make_ani_STA_STB_plots_backsub.py
2552/1: %run make_ani_STA_STB_plots_backsub.py
2553/1: %run make_ani_STA_STB_plots_backsub.py
2554/1: %run make_ani_STA_STB_plots_backsub.py
2555/1: %run make_ani_STA_STB_plots_backsub.py
2556/1: %run make_ani_STA_STB_plots_backsub.py
2529/2: fail
2557/1: %run make_ani_STA_STB_plots_backsub.py
2558/1: %run main_solli.py
2559/1: %run main_solli.py
2560/1: %run main_solli.py
2560/2: backsub
2561/1: %run make_ani_STA_STB_plots_backsub.py
2561/2: backsub
2562/1: %run main_solli.py
2563/1: %run main_solli.py
2564/1: %run main_solli.py
2565/1: %run main_solli.py
2566/1: %run main_solli.py
2567/1: %run main_solli.py
2568/1: %run main_solli.py
2568/2: I = np.array[1,2,3,0,1,2,0]
2568/3: I = np.array([1,2,3,0,1,2,0])
2568/4: I[I==0]=NaN
2568/5: I[I==0]=np.nan
2568/6: np.nana
2568/7: np.nan
2568/8: I[I==0]
2568/9: I[I<1.} = np.nan
2568/10: I[I<1.] = np.nan
2568/11: I
2568/12: I.type
2568/13: type(I)
2568/14: I[I<1.] = 10.
2568/15: I
2568/16: I.append(1)
2568/17: np.append(I,I)
2568/18: np.append(I,10)
2568/19: np.append(I,np.nan)
2568/20: np.append(I,np.nan,I)
2568/21: np.append(np.nan, I)
2568/22: np.append(1,np.nan, 1)
2568/23: np.append(1,np.nan)
2568/24: I
2568/25: np.append(I,nan)
2568/26: np.append(I,np.nan)
2568/27: I2 = np.append(I,np.nan)
2568/28: np.append(I2,7)
2568/29: I2
2568/30: I2[I2 == 10.]
2568/31: I2[I2 == 10.] = np.nan
2568/32: I2
2569/1: %run make_ani_STA_STB_plots_backsub.py
2570/1: %run make_ani_STA_STB_plots_backsub.py
2571/1: %run main_solli.py
2572/1: %run main_solli.py
2572/2: fail_a
2572/3: fail_b
2573/1: %run make_ani_STA_STB_plots_backsub.py
2574/1: %run make_ani_STA_STB_plots_backsub.py
2575/1: %run make_ani_STA_STB_plots_backsub.py
2576/1: %run make_sepangle_plot.py
2577/1: %run make_sepangle_plot.py
2579/1: %run main_solli.py
2580/1: %run main_solli.py
2581/1: %run make_ani_STA_STB_plots_backsub.py
2580/2: fail
2580/3: fail_a
2580/4: fail_b
2580/5: data.index
2582/1: %run main_solli.py
2582/2: fail_a
2582/3: fail_b
2583/1: %run main_solli.py
2584/1: %run main_solli.py
2585/1: %run main_solli.py
2586/1: %run main_solli.py
2587/1: %run main_solli.py
2588/1: %run main_solli.py
2589/1: %run main_solli.py
2590/1: %run main_solli.py
2591/1: %run main_solli.py
2592/1: %run main_solli.py
2593/1: %run main_solli.py
2594/1: %run main_solli.py
2595/1: %run main_solli.py
2596/1: %run main_solli.py
2597/1: %run main_solli.py
2599/1: %run make_sepangle_plot.py
2599/2: data_sta
2599/3: date_sta
2599/4: file_STA
2599/5: data_sta_backsub20
2600/1: %run make_sepangle_plot.py
2600/2: data_sta_backsub20
2600/3: data_sta_backsub20.ani_max
2600/4: plot_backsub()
2600/5: plot_backsub20()
2601/1: %run make_sepangle_plot.py
2601/2: plot_backsub20()
2601/3: plot_backsub20(numbers=True)
2602/1: %run make_sepangle_plot.py
2602/2: plot_backsub20(numbers=True)
2602/3: plot_backsub20(numbers=False)
2603/1: plot_backsub20(numbers=True)
2603/2: %run make_sepangle_plot.py
2603/3: plot_backsub20(numbers=True)
2604/1: %run make_sepangle_plot.py
2604/2: plot_backsub20(numbers=True)
2605/1: %run make_sepangle_plot.py
2605/2: plot_backsub20(numbers=True)
2606/1: %run make_sepangle_plot.py
2606/2: plot_backsub20(numbers=True)
2607/1: plot_backsub20(numbers=True)
2607/2: %run make_sepangle_plot.py
2607/3: plot_backsub20(numbers=True)
2608/1: %run make_sepangle_plot.py
2608/2: plot_backsub20(numbers=True)
2609/1: plot_backsub20(numbers=True)
2609/2: %run make_sepangle_plot.py
2609/3: plot_backsub20(numbers=True)
2610/1: %run make_sepangle_plot.py
2610/2: plot_backsub20(numbers=True)
2611/1: %run make_sepangle_plot.py
2611/2: plot_backsub20(numbers=True)
2612/1: %run make_multiplots_SEPT.py
2612/2: d
2612/3: d
2613/1: %run make_multiplots_SEPT.py
2614/1: %run make_multiplots_SEPT.py
2615/1: %run make_multiplots_SEPT.py
2616/1: %run main_solli.py
2617/1: %run main_solli.py
2618/1: %run main_solli.py
2619/1: %run make_multiplots_SEPT.py
2619/2: event.ani
2620/1: %run make_multiplots_SEPT.py
2621/1: %run make_multiplots_SEPT.py
2621/2: event
2621/3: event.event_nr
2621/4: event.eventtime
2621/5: event.eventtime
2621/6: event.date
2622/1: %run make_multiplots_SEPT.py
2623/1: %run make_multiplots_SEPT.py
2624/1: %run make_multiplots_SEPT.py
2624/2: event
2624/3: event.s
2624/4: event.sc
2624/5: event.name
2624/6: event.pa_data
2624/7: event.date
2625/1: event.date
2625/2: %run make_multiplots_SEPT.py
2625/3: event.date
2625/4: event.pa_data
2625/5: event.pa_data.shape
2625/6: event.doy
2625/7: event.doy.shape
2625/8: event.pa_data.shape
2625/9: event.pa_data[400:,:]
2625/10: event.name
2625/11: event.time_I_max
2625/12: X1
2625/13: X2
2625/14: event.doy
2625/15: X2
2625/16: X1
2626/1: %run make_multiplots_SEPT.py
2626/2: event.doy
2626/3: X1
2626/4: X2
2626/5: event.doy.shape
2627/1: %run main_solli.py
2628/1: %run main_solli.py
2629/1: %run make_multiplots_SEPT.py
2629/2: event
2629/3: event.name
2630/1: %run make_multiplots_SEPT.py
2630/2: event.name
2630/3: X1
2630/4: X2
2630/5: event.doy.shape
2630/6: event.doy
2630/7: x1
2630/8: X1
2630/9: X2
2631/1: %run main_solli.py
2632/1: %run make_multiplots_SEPT.py
2633/1: %run main_solli.py
2634/1: %run make_multiplots_SEPT.py
2634/2: event.doy
2634/3: event.doy.shape
2635/1: %run main_solli.py
2636/1: %run main_solli.py
2637/1: %run main_solli.py
2638/1: %run make_multiplots_SEPT.py
2638/2: event.doy
2638/3: event.doy.shape
2638/4: X1
2638/5: X2
2639/1: %run main_solli.py
2640/1: %run main_solli.py
2641/1: %run make_multiplots_SEPT.py
2642/1: %run main_solli.py
2643/1: %run main_solli.py
2644/1: %run main_solli.py
2645/1: %run main_solli.py
2646/1: %run make_multiplots_SEPT.py
2647/1: %run make_multiplots_SEPT.py
2648/1: %run make_multiplots_SEPT.py
2649/1: %run main_solli.py
2650/1: %run main_solli.py
2651/1: %run main_solli.py
2652/1: %run main_solli.py
2653/1: %run main_solli.py
2654/1: %run main_solli.py
2655/1: %run main_solli.py
2656/1: %run main_solli.py
2657/1: %run main_solli.py
2657/2: fai_b
2657/3: fail_b
2658/1: %run make_multiplots_SEPT.py
2658/2: ls
2659/1: %run make_multiplots_SEPT.py
2660/1: %run make_multiplots_SEPT.py
2660/2: ls
2660/3: cd ..
2660/4: ls
2661/1: ls
2662/1: %run make_multiplots_SEPT.py
2662/2: fail_a
2662/3: fail_b
2663/1: %run main_solli.py
2664/1: %run main_solli.py
2665/1: %run main_solli.py
2666/1: %run make_multiplots_SEPT.py
2666/2: fail_a
2666/3: fail_b
2667/1: %run make_multiplots_SEPT.py
2668/1: %run main_solli.py
2669/1: %run main_solli.py
2670/1: %run make_multiplots_SEPT.py
2671/1: %run make_multiplots_SEPT.py
2672/1: %run make_multiplots_SEPT.py
2672/2: %run main_solli.py
2673/1: %run make_multiplots_SEPT.py
2675/1: %run main_solli.py
2674/1: %run main_solli_bs.py
2676/1: %run main_solli.py
2677/1: %run main_solli_bs.py
2679/1: %run main_solli_bs.py
2680/1: %run main_solli.py
2682/1: %run main_solli.py
2683/1: %run make_multiplots_SEPT.py
2684/1: %run make_multiplots_SEPT.py
2684/2:
for i in range(1,100):
    print(i)
2684/3: fail_a
2684/4: fail_b
2685/1: %run make_multiplots_SEPT.py
2685/2: fail_a
2685/3: fail_b
2686/1: %run make_multiplots_SEPT.py
2687/1: %run make_multiplots_SEPT.py
2687/2: %run make_sepangle_plot.py
2688/1: %run make_sepangle_plot.py
2689/1: %run make_sepangle_plot.py
2690/1: %run make_sepangle_plot.py
2690/2:
for i in data_sta_backsub20.index:
    print(data_sta_backsub20.nr[i])
2690/3: data_sta.nr
2690/4:
for i in data_sta_backsub20.index:
    np.where(data_sta.nr == data_sta_backsub20.nr[i])
2690/5:
for i in data_sta_backsub20.index:
    a = np.where(data_sta.nr == data_sta_backsub20.nr[i])
2690/6:
for i in data_sta_backsub20.index:
    a = np.where(data_sta.nr == data_sta_backsub20.nr[i])
    print(a)
2690/7:
for i in data_sta_backsub20.index:
    data_sta.nr[int(np.where(data_sta.nr == data_sta_backsub20.nr[i])[0])]
2690/8:
for i in data_sta_backsub20.index:
    print(data_sta.nr[int(np.where(data_sta.nr == data_sta_backsub20.nr[i])[0])])
2690/9:
for i in data_sta_backsub20.index:
    print(i)
2690/10:
for i in data_sta_backsub20.index:
    print(i)
    print(data_dta.nr[i])
2690/11:
for i in data_sta_backsub20.index:
    print(i)
    print(data_sta.nr[i])
    print(data_sta_backsub20-nr[i])
2690/12:
for i in data_sta_backsub20.index:
    print(i)
    print(data_sta.nr[i])
    print(data_sta_backsub20.nr[i])
2690/13:
for i in data_sta_backsub20.index:
    print(i)
    print(data_sta.nr[i])
    print(data_sta_backsub20.nr[i])
    print('\n')
2690/14:
for i in data_sta_backsub20.index:
    print(i)
    print(data_sta.nr[i])
    print(data_sta_backsub20.nr[i])
    print(data_sta_backsub20.index[i])
    print('\n')
2690/15:
for i in data_sta_backsub20.index:
    print(i)
    print(data_sta.nr[i])
    print(data_sta_backsub20.nr[i])
    print(data_sta_backsub20.index[i])
    print('\n')
2690/16: a = np.array([10,30,40,50])
2690/17: np.where(a == 10)
2690/18: np.where(a == 20)
2690/19: data_sta_backsub20 = np.array([10,20,30,40])
2690/20: data_sta_backsub20.nr = np.array([10,20,30,40])
2690/21: data_sta_backsub20 = np.array([10,20,30,40])
2690/22: data_sta = np.array([10,30,40])
2690/23:
for ib in data_sta_backsub20.index:
    print(ib)
2690/24:
for ib in range(len(data_sta_backsub20)):
    print(ib)
2690/25:
for ib in range(len(data_sta_backsub20)):
    wert = data_sta_backsub20[ib]
    print(wert)
    if data_sta[int(np.where(data_sta == wert)[0])]:
        i = np.where(data_sta == wert)
        print(i)
    print('\n')
2690/26: data_sta
2690/27: data_sta[np.where(data_sta == 10)]
2690/28:
for ib in range(len(data_sta_backsub20)):
    wert = data_sta_backsub20[ib]
    print(wert)
    if data_sta[np.where(data_sta == wert)]:
        i = np.where(data_sta == wert)
        print(i)
    print('\n')
2690/29:
for ib in range(len(data_sta_backsub20)):
    wert = data_sta_backsub20[ib]
    print(wert)
    if data_sta[np.where(data_sta == wert)]:
       print(wert)
    print('\n')
2690/30: data_sta
2690/31: data_stra.contains(10)
2690/32: data_sta.contains(10)
2690/33: 10 in data_sta
2690/34:
for ib in range(len(data_sta_backsub20)):
    wert = data_sta_backsub20[ib]
    print(wert)
    if wert in data_sta:
        i = np.where(data_sta == wert)
        print(ib)
        print(i)
2690/35:
for ib in range(len(data_sta_backsub20)):
    wert = data_sta_backsub20[ib]
    print(wert)
    if wert in data_sta:
        i = np.where(data_sta == wert)
        print(ib)
        print(i)
    print('\n')
2690/36:
for ib in range(len(data_sta_backsub20)):
    wert = data_sta_backsub20[ib]
    print(wert)
    if wert in data_sta:
        i = np.where(data_sta == wert)[0]
        print(ib)
        print(i)
    print('\n')
2690/37:
for ib in range(len(data_sta_backsub20)):
    wert = data_sta_backsub20[ib]
    print(wert)
    if wert in data_sta:
        i = np.where(data_sta == wert)[0][0]
        print(ib)
        print(i)
    print('\n')
2691/1: %run make_sepangle_plot.py
2691/2: data_sta_backsub20
2691/3: data_sta_backsub20.nr
2691/4: data_sta_backsub20.index
2692/1: data_sta_backsub20.index
2692/2: %run make_sepangle_plot.py
2693/1: %run make_sepangle_plot.py
2693/2: data_sta.nr
2693/3: np.where(data_sta == 32)
2693/4: np.where(data_sta.nr == 32)
2694/1: np.where(data_sta.nr == 32)
2694/2: %run make_sepangle_plot.py
2694/3: %run make_sepangle_plot.py
2694/4: i
2694/5: i[0]
2694/6: i[0,0]
2694/7: i[0][0]
2695/1: %run make_sepangle_plot.py
2696/1: %run make_sepangle_plot.py
2696/2: index_diff_sta
2696/3:
for ib in data_sta_backsub20.index:
    print(ib)
2696/4:
for ib in data_sta_backsub20.index:
    if data_sta_backsub20.nr[ib] in data_sta.nr:
        print(ib)
2696/5:
for ib in data_sta_backsub20.index:
    print(data_sta_backsub20.nr[ib])
2696/6: data_sta.nr
2696/7: data_sta_backsub20.nr
2696/8: data_sta_backsub20.nr.shape
2696/9:
for i in data_sta_backsub20.nr:
    print(i)
2696/10: data_sta_backsub20.nr
2696/11:
for i in data_sta.nr:
    print(i)
2696/12:
for ib in data_sta_backsub20.index:
    print(data_sta_backsub20.nr[ib])
2696/13: data_sta.nr
2696/14: 40 in data_sta.nr
2696/15: 5 in data_sta.nr
2696/16: 5 in data_sta.nr[1]
2696/17: type(data_sta.nr)
2696/18: data_sta.nr[:,1]
2696/19: data_sta.nr[:,0]
2696/20: data_sta.nr
2696/21: data_sta.nr.index
2696/22: data_sta.nr.value
2696/23: data_sta.nr.data
2696/24: data_sta.nr.values
2696/25:
for ib in data_sta_backsub20.index:
    if data_sta_backsub20.nr[ib] in data_sta.nr.values:
        print(ib)
2697/1: %run make_sepangle_plot.py
2697/2: index_diff_sta
2697/3: index_diff_stb
2697/4: data_stb_backsub20.nr
2697/5: data_stb.nr
2697/6: diff_ani_sta
2697/7: data_sta_backsub20[index_diff_st]
2697/8: index_diff_stb
2697/9: data_sta_backsub20[index_diff_sta]
2697/10: data_sta_backsub20
2697/11: data_sta_backsub20.sepAngle
2697/12: data_sta_backsub20.sepAngle.len
2697/13: data_sta_backsub20.sepAngle.shape
2697/14: diff_ani_sta.shape
2697/15: diff_ani_sta
2697/16: len(diff_ani_sta)
2697/17: data_sta_backsub20.sepAngle
2697/18: data_sta_backsub20.sepAngle[0]
2697/19: data_sta_backsub20.sepAngle[0,1,2,3]
2697/20: data_sta_backsub20.sepAngle[0]
2697/21: data_sta_backsub20.sepAngle[2]
2697/22: data_sta_backsub20.sepAngle[0,2]
2697/23: data_sta_backsub20.sepAngle[[0,2]]
2697/24: data_sta_backsub20.sepAngle[[index_diff_sta]]
2697/25: index_diff_sta
2697/26: data_sta_backsub20.sepAngle[index_diff_sta]
2697/27: shape(data_sta_backsub20.sepAngle[index_diff_sta])
2697/28: data_sta_backsub20.sepAngle[[index_diff_sta]].shape
2697/29: data_sta_backsub20.sepAngle[index_diff_sta].shape
2698/1: %run make_sepangle_plot.py
2698/2: plot_backsub20(numbers=True)
2698/3: pylab.show()
2698/4: plt.show()
2698/5: plot_backsub(numbers=True)
2698/6: plot_nobacksub()
2698/7: plt.show()
2698/8: plot_backsub_diff
2698/9: plot_backsub_diff()
2698/10: plt.show()
2699/1: %run make_sepangle_plot.py
2699/2: plot_backsub_diff()
2700/1: %run make_sepangle_plot.py
2700/2: plot_backsub_diff()
2700/3: plot_backsub_diff(numbers=True)
2701/1: %run make_sepangle_plot.py
2701/2: plot_backsub_diff(numbers=True)
2702/1: %run make_sepangle_plot.py
2702/2: plot_backsub_diff(numbers=True)
2703/1: %run make_sepangle_plot.py
2703/2: plot_backsub20()
2703/3: plot_nobacksub()
2703/4: plot_backsub_diff()
2704/1: %run make_sepangle_plot.py
2704/2: plot_backsub_diff()
2705/1: %run make_sepangle_plot.py
2705/2: plot_nobacksub()
2706/1: %run make_sepangle_plot.py
2706/2: plot_nobacksub()
2708/1: %run make_sepangle_plot.py
2708/2: plot_nobacksub()
2709/1: %run make_sepangle_plot.py
2709/2: plot_nobacksub()
2710/1: %run make_sepangle_plot.py
2710/2: index_diff_sta
2711/1: %run make_multiplots_SEPT.py
2713/1: %run make_multiplots_SEPT.py
2714/1: %run make_multiplots_SEPT.py
2715/1: ls
2715/2: ls
2715/3: %run load_el_data.py
2715/4: dataA.number
2715/5: dataA.Number
2715/6: dataA.Number[1]
2715/7: date = dataA.onset[1]
2715/8: date
2715/9: date = pd.to_datetime[dataA.onset,format="%Y-%M-%D"]
2715/10: date = pd.to_datetime(dataA.onset,format="%Y-%M-%D")
2715/11: date = pd.to_datetime(dataA.onset,format="%Y-%m-%d")
2715/12: date
2715/13: date[0]
2716/1: %run load_el_data.py
2717/1: %run load_el_data.py
2718/1: %run load_el_data.py
2718/2: dataA.onset
2718/3:
for i in dataA.index:
    print(dataA.onset[i])
2718/4:
for i in dataA.index:
    print(len(dataA.onset[i]))
2719/1: %run load_el_data.py
2719/2: onset
2720/1: %run load_el_data.py
2720/2:
for i in dataA.index:
   data = dataA[i]
2720/3: dataA
2720/4: dataA[0]
2720/5: dataA[1]
2720/6: dataA[:,1]
2720/7: dataA[1,:]
2679/2: fail_a
2679/3: fail_b
2680/2: fail_a
2720/8:
for i in dataA.index:
    print(dataA.onset[i], dataA.dt[i])
2720/9:
for i in dataA.index:
    print(dataA.onset[i], dataA.dt[i])
    print(dataA.backsub_t1[i], dataA.backsub_t2[i])
2720/10:
for i in dataA.index:
    print(dataA.onset[i], dataA.dt[i])
    print(dataA.backsub_t1[i], dataA.backsub_t2[i])
    print('\n')
2720/11:
for i in dataA.index:
    print(dataA.onset[i], dataA.dt[i])
    print(dataA.backsub_t1[i], dataA.backsub_t2[i])
    print('\n')
2722/1: %run load_el_data.py
2722/2: backsub_t1
2722/3: backsub_t1 - backsub_t2
2722/4: td = backsub_t1 - backsub_t2
2722/5: td.total_seconds()
2722/6: td.total_seconds()/60
2722/7:
for i in dataA.index:
    td = backsub_t1[i] - backsub_t2[i]
    print(td.total_seconds())
2722/8:
for i in dataA.index:
    td = backsub_t1[i] - backsub_t2[i]
2722/9:
for i in dataA.index:
    td =dataA.backsub_t1[i] -dataA.backsub_t2[i]
2722/10:
for i in dataA.index:
    td =dataA.backsub_t1[i] -dataA.backsub_t2[i]
2722/11:
for i in dataA.index:
    td =dataA.backsub_t1[i] -dataA.backsub_t2[i]
2723/1: %run load_el_data.py
2724/1: %run load_el_data.py
2724/2: timedelta
2724/3: datatime.timedelta
2724/4: datetime.timedelta
2724/5: from datetime import timedelta
2724/6: timedelta(microseconds = -2)
2724/7: 24*60*60
2724/8: timedelta(seconds = -2)
2725/1: %run load_el_data.py
2726/1: %run load_el_data.py
2727/1: %run load_el_data.py
2728/1: %run load_el_data.py
2729/1: %run load_el_data.py
2730/1: %run load_el_data.py
2731/1: %run load_el_data.py
2732/1: %run load_el_data.py
2733/1: %run load_el_data.py
2733/2:
for i in range(1):
    print(i)
2734/1: %run load_el_data.py
2735/1: %run load_el_data.py
2736/1: %run make_sepangle_plot.py
2736/2: plot_nobacksub()
2736/3: plot_backsub20
2736/4: plot_backsub20()
2736/5: plot_backsub_diff()
2739/1: %run load_el_data.py
2740/1: %run load_el_data.py
2741/1: %run teyt.py
2741/2: test_func()
2743/1: %run make_multiplots_SEPT.py
2744/1: %run make_multiplots_SEPT.py
2745/1: %run make_multiplots_SEPT.py
2745/2: data
2746/1: %run make_multiplots_SEPT.py
2747/1: %run make_multiplots_SEPT.py
2748/1: %run make_multiplots_SEPT.py
2749/1: %run make_multiplots_SEPT.py
2750/1: %run make_multiplots_SEPT.py
2751/1: %run make_multiplots_SEPT.py
2752/1: %run make_multiplots_SEPT.py
2753/1: from datetime import datetime
2753/2: date = datetime(year=2005,month=4,day=1)
2753/3: date
2753/4: date = datetime(year=2005,month=4,day=1,hour=14)
2753/5: date
2753/6: from process_event_SEPT_new import EventSEPT
2754/1: %run make_multiplots_new.py
2755/1: date = datetime(year=2005,month=4,day=1,hour=14)
2755/2: from datetime import datetime
2755/3: date = datetime(year=2005,month=4,day=1,hour=14)
2755/4: picklepath
2755/5: %run make_multiplots_SEPT.py
2755/6: EventTime
2756/1: %run make_multiplots_new.py
2757/1: %run make_multiplots_new.py
2757/2: %run make_multiplots_new.py
2758/1: %run make_multiplots_new.py
2759/1: %run make_multiplots_new.py
2760/1: %run make_multiplots_new.py
2761/1: %run make_multiplots_new.py
2762/1: %run make_multiplots_new.py
2763/1: %run make_multiplots_new.py
2764/1: %run make_multiplots_new.py
2765/1: %run make_multiplots_new.py
2765/2: event
2766/1: %run make_multiplots_new.py
2766/2: event
2766/3: event.date
2766/4: event.name
2766/5: event.sc
2767/1: event.sc
2767/2: %run make_multiplots_new.py
2767/3: event.doy
2767/4: pickled_data
2768/1: %run make_multiplots_new.py
2768/2: event
2768/3: event.doy
2769/1: %run make_multiplots_new.py
2770/1: %run make_multiplots_new.py
2771/1: %run make_multiplots_new.py
2772/1: %run make_multiplots_new.py
2773/1: %run make_multiplots_new.py
2773/2: event.pickled_data.doy
2774/1: event.pickled_data.doy
2774/2: %run make_multiplots_new.py
2775/1: %run make_multiplots_new.py
2775/2: event.pickled_data.doy
2775/3: event.pickled_data.date
2776/1: %run make_multiplots_SEPT.py
2777/1: %run make_multiplots_SEPT.py
2777/2: ani_X1
2777/3: ani_X2
2777/4: intensity_X1
2777/5: date = datetime(year=2005,month=4,day=1,hour=14)
2777/6: from datetime import datetime
2777/7: date = datetime(year=2005,month=4,day=1,hour=14)
2777/8: myfunc.date2doy(date)
2777/9: date.timetuple
2777/10: date.timetuple()
2777/11: date.timetuple().tm_yday
2778/1: %run make_multiplots_SEPT.py
2740/2: fail_a
2740/3: fail_b
2779/1: %run make_multiplots_SEPT.py
2779/2: date = datetime(year=2005,month=4,day=1,hour=14)
2779/3: date = datetime.datetime(year=2005,month=4,day=1,hour=14)
2779/4: date2 = datetime.datetime(year=2005,month=4,day=1,hour=14,sec = 2)
2779/5: date2 = datetime.datetime(year=2005,month=4,day=1,hour=14,min=2)
2779/6: date2 = datetime.datetime(year=2005,month=4,day=1,hour=14,0,2)
2779/7: date2 = datetime.datetime(2005,4,1,14,0,2)
2779/8: myfunc.datetime2doy(date)
2779/9: myfunc.datetime2doy(date2)
2780/1: %run make_multiplots_new.py
2781/1: %run make_multiplots_new.py
2782/1: %run make_multiplots_new.py
2783/1: %run make_multiplots_new.py
2783/2: event
2783/3: event.pickled_data.
2783/4: event.pickled_data.av
2783/5: event.pickled_data.settings['av']
2783/6: date
2783/7: from datetime import datetime
2783/8: date = datetime.datetime(year=2005,month=4,day=1,hour=14)
2783/9: date = datetime(year=2005,month=4,day=1,hour=14)
2783/10: strftime(date)
2783/11: datetime.strftime
2783/12: date.datetime.strftime('%Y-%m-%d')
2783/13: date.strftime('%Y-%m-%d')
2784/1: %run make_multiplots_new.py
2785/1: %run make_multiplots_new.py
2786/1: %run make_multiplots_new.py
2786/2: av
2787/1: %run make_multiplots_new.py
2787/2: "hallo_test/%s"%(av)
2787/3: date
2788/1: "hallo_test/%s"%(av)
2788/2: %run make_multiplots_new.py
2789/1: %run make_multiplots_new.py
2789/2: %run make_multiplots_new.py
2790/1: %run make_multiplots_new.py
2791/1: %run make_multiplots_new.py
2792/1: %run make_multiplots_new.py
2793/1: %run make_multiplots_new.py
2794/1: %run make_multiplots_new.py
2795/1: %run make_multiplots_new.py
2796/1: %run make_multiplots_new.py
2797/1: %run make_multiplots_new.py
2798/1: %run make_multiplots_new.py
2799/1: %run make_multiplots_new.py
2800/1: %run make_multiplots_new.py
2801/1: %run make_multiplots_new.py
2802/1: %run make_multiplots_new.py
2802/2: from datetime import datetime
2802/3: date = datetime(year=2005,month=4,day=1,hour=14)
2802/4: date.hour
2802/5: event
2803/1: %run make_multiplots_new.py
2803/2: event
2803/3: event1
2803/4: event1.doy
2803/5: event1.date
2804/1: %run make_multiplots_new.py
2804/2: event1
2805/1: event1
2805/2: %run make_multiplots_new.py
2805/3: event1
2805/4: event1.doy
2805/5: event1.doy[0]
2805/6: event1.doy[-1]
2806/1: %run load_el_data.py
2807/1: %run load_el_data.py
2808/1: %run load_el_data.py
2809/1: %run make_multiplots_new.py
2809/2: event1
2809/3: event1.doy
2810/1: %run load_el_data.py
2811/1: %run load_el_data.py
2811/2: sept_event
2811/3: sept_data
2811/4: sept_data.doy
2812/1: %run make_multiplots_new.py
2812/2: event
2812/3: event1
2812/4: event1.doy
2813/1: %run make_multiplots_new.py
2814/1: %run load_el_data.py
2815/1: %run make_multiplots_new.py
2814/2: fail_a
2814/3: fail_b
2814/4: fail_b+-+
2816/1: %run make_multiplots_new.py
2817/1: %run make_multiplots_new.py
2818/1: from datetime import datetime
2818/2: date =
2818/3: date = datetime(year=2005,month=4,day=1,hour=14)
2818/4: date + tiemdelta(-1)
2818/5: date + timedelta(-1)
2818/6: from datetime import datetime
2818/7: from datetime import timedelta
2818/8: date + timedelta(-1)
2818/9: date
2820/1: %run load_el_data.py
2821/1: %run load_el_data.py
2822/1: %run load_el_data.py
2822/2: event1
2822/3: sept_data
2822/4: sept_data.date
2822/5: onset
2824/1: %run load_el_data.py
2824/2: fail_a
2825/1: %run make_multiplots_new.py
2826/1: %run make_multiplots_new.py
2827/1: %run make_multiplots_new.py
2827/2: event1
2827/3: event1.doy
2828/1: event1.doy
2828/2: %run make_multiplots_new.py
2828/3: %run load_el_data.py
2829/1: %run load_el_data.py
2830/1: %run make_multiplots_new.py
2831/1: %run make_multiplots_new.py
2832/1: %run make_multiplots_new.py
2833/1: %run make_multiplots_new.py
2834/1: %run make_multiplots_new.py
2835/1: %run load_el_data.py
2834/2: fail_a
2836/1: %run load_el_data.py
2837/1: %run make_multiplots_new.py
2838/1: %run make_multiplots_new.py
2839/1: %run make_multiplots_new.py
2840/1: %run make_multiplots_new.py
2841/1: %run make_multiplots_new.py
2842/1: %run make_multiplots_new.py
2843/1: %run make_multiplots_new.py
2844/1: %run make_multiplots_new.py
2845/1: %run make_multiplots_new.py
2846/1: %run make_multiplots_new.py
2847/1: %run make_multiplots_new.py
2848/1: %run make_multiplots_new.py
2849/1: ls
2849/2: who
2850/1: %run make_multiplots_new.py
2852/1: %run make_multiplots_new.py
2854/1: %run make_multiplots_new.py
2863/1: hist(arange(10))
2864/1: %run make_multiplots_new.py
2865/1: pandas
2865/2: import pandas
2865/3: %run make_multiplots_new.py
2866/1: %run make_multiplots_new.py
2867/1: %run make_multiplots_new.py
2868/1: %run make_multiplots_new.py
2868/2: EventSEPT
2868/3:

            event = EventSEPT(picklepath, backsub_type, energyrange, event_nr, date,
                              [int_int[0], int_int[1]], [ani_int[0], ani_int[1]])
2868/4: event = EventSEPT(picklepath, backsub_type, energyrange, event_nr, date,[int_int[0],int_int[1]],[ani_int[0],anit_int[1]])
2868/5: picklepath
2868/6: picklepath = path_root + path_pickle+"%i_STA_%s_av%s"%(event_nr,date.strftime("%Y-%m-%d_%H"),av)
2868/7: dataA
2868/8: dataA.Number[0]
2869/1: %run make_multiplots_new.py
2869/2: event = main_func_A(dataA.Number[i],onset,ani_int,intensity_int)
2870/1: %run make_multiplots_new.py
2871/1: %run make_multiplots_new.py
2872/1: %run make_multiplots_new.py
2873/1: %run make_multiplots_new.py
2873/2: event
2874/1: event
2874/2: %run make_multiplots_new.py
2875/1: %run make_multiplots_new.py
2875/2: event.ani
2875/3: event.ani.shape
2876/1: event.ani.shape
2876/2: %run make_multiplots_new.py
2877/1: %run make_multiplots_new.py
2878/1: %run make_multiplots_new.py
2879/1: %run make_multiplots_new.py
2879/2: ani_i
2879/3: a = arange(5,10)
2879/4: a[1,2]
2879/5: a[1:2]
2880/1: a[1:2]
2880/2: %run make_multiplots_new.py
2881/1: %run make_multiplots_new.py
2882/1: %run make_multiplots_new.py
2883/1: %run make_multiplots_new.py
2884/1: %run make_multiplots_new.py
2885/1: %run load_el_data.py
2886/1: %run load_el_data.py
2886/2: %run make_multiplots_new.py
2887/1: %run load_el_data.py
2887/2: %run make_multiplots_new.py
2888/1: %run make_multiplots_new.py
2889/1: %run make_multiplots_new.py
2889/2: main_func_B(dataB.Number[i],onset,ani_int,intensity_int)
2889/3: picklepath
2889/4: picklepath = path_root + path_pickle+"%i_STB_%s_av%s"%(event_nr,date.strftime("%Y-%m-%d_%H"),av)
2889/5: dataB
2889/6: dataB.Number[i]
2889/7: main_func_B
2889/8: main_func_B(dataB.Number[i],onset,ani_int,intensity_int)
2889/9: ani_int
2889/10: int_int
2889/11: intensity_int
2889/12: onset
2889/13: main_func_B(1.,onset,ani_int,intensity_int)
2890/1: main_func_B(1.,onset,ani_int,intensity_int)
2890/2: %run make_multiplots_new.py
2891/1: %run make_multiplots_new.py
2892/1: %run make_sepangle_plot_new.py
2893/1: %run make_sepangle_plot_new.py
2894/1: %run make_sepangle_plot_new.py
2895/1: %run make_sepangle_plot_new.py
2896/1: %run make_multiplots_new.py
2896/2: %run make_sepangle_plot_new.py
2896/3: data_sta
2896/4: data_sta.index
2896/5: data_sta_backsub20
2896/6: data_sta_backsub20.nr
2896/7: data_sta_backsub20.Nr[0]
2896/8: data_sta_backsub20
2896/9: data_sta_backsub20.Nr
2896/10: data_sta.Nr
2896/11: data_sta.0
2897/1: data_sta.Nr
2897/2: %run make_sepangle_plot_new.py
2897/3: data_sta.Nr
2897/4: data_sta.Nr
2897/5: data_sta.values
2897/6: data_sta.Nr.values
2897/7: data_sta.Nr
2897/8: ib = 0
2897/9: data_sta_backsub20.Nr
2897/10: i = np.where(data_sta.Nr == data_sta_backsub20.Nr[ib])
2897/11: i
2897/12: i = np.where(data_sta.Nr == data_sta_backsub20.Nr[ib])[0][0]
2897/13: i
2897/14: data_sta
2898/1: %run make_sepangle_plot_new.py
2899/1: %run make_sepangle_plot_new.py
2899/2: data_sta
2899/3: data_sta.ani_max
2899/4: data_sta.sep_ang
2899/5: data_sta.sep_ang[0]
2899/6: isnan(data_sta.sep_ang[0])
2899/7: not isnan(data_sta.sep_ang[0])
2899/8: not isnan(data_sta.sep_ang[3])
2900/1: %run make_sepangle_plot_new.py
2900/2: isnan(3)
2900/3: isnan(data_sta_backsub20.sep_ang[ib])
2900/4: np.isnan
2901/1: np.isnan
2901/2: %run make_sepangle_plot_new.py
2901/3: sep_angle_sta
2901/4: diff_ani_sta
2901/5: ib
2901/6: data_sta
2901/7: data_sta.ani_max
2901/8: data_sta.sep_angle
2901/9: data_sta.sep_ang
2901/10: data_sta.ani_max
2901/11: data_sta_backsub20.ani_max
2902/1: %run load_el_data.py
2903/1: %run load_el_data.py
2904/1: %run load_el_data.py
2904/2: %run make_multiplots_new.py
2905/1: %run make_multiplots_new.py
2905/2: %run make_sepangle_plot_new.py
2905/3: sep_angle_sta
2905/4: numbr_diff_sta
2905/5: number_diff_sta
2905/6: number_diff_sta.shape
2905/7: len(number_diff_sta)
2906/1: number_diff_sta2
2906/2: number_diff_sta
2907/1: %run make_sepangle_plot_new.py
2907/2: number_diff_sta
2907/3: number_diff_sta2
2907/4: diff_ani_sta
2908/1: %run make_sepangle_plot_new.py
2909/1: %run make_sepangle_plot_new.py
2909/2: data_sta
2909/3: data_sta_backsub20
2909/4: data_sta_backsub20.sep_ang
2909/5: data_sta_backsub20.sep_ang[0]
2909/6: data_sta_backsub20.sep_ang[1]
2910/1: %run make_sepangle_plot_new.py
2911/1: %run make_sepangle_plot_new.py
2912/1: %run make_sepangle_plot_new.py
2912/2: data_sta_backsub20
2912/3: data_sta_backsub20.sep_angle
2912/4: data_sta_backsub20.sep_and
2912/5: data_sta_backsub20.sep_ang
2912/6: data_sta_backsub20.sep_ang[0]
2912/7: data_sta_backsub20.sep_ang[1]
2912/8: data_sta_backsub20.sep_ang[2]
2912/9: data_sta_backsub20.sep_ang[3]
2912/10: data_sta_backsub20.sep_ang[4]
2912/11: data_sta_backsub20.sep_ang[5]
2912/12: data_sta_backsub20.sep_ang[9]
2912/13: data_sta_backsub20.sep_ang[8]
2912/14: data_sta_backsub20.sep_ang
2913/1: %run make_multiplots_new.py
2913/2: %run make_sepangle_plot_new.py
2913/3: data_sta_backsub20.sep_ang
2914/1: %run make_sepangle_plot_new.py
2915/1: %run make_sepangle_plot_new.py
2915/2: diff_ani_sta
2915/3: number_diff_sta
2915/4: number_diff_sta2
2915/5: data_sta.Nr[number_diff_sta2]
2915/6: sep_angle_sta
2915/7: ib
2915/8: data_sta_backsub20
2915/9: data_sta_backsub20.sep_ang
2915/10: data_sta_backsub20.Nr[8]
2915/11: data_sta_backsub20.sep_ang[8]
2915/12: sep_angle_sta
2915/13: ib
2916/1: %run make_sepangle_plot_new.py
2916/2:
for ib in data_sta_backsub20.index:
    print(data_sta.sep_ang[ib])
2916/3:
for ib in data_sta_backsub20.index:
    print(ib)
2917/1: %run make_sepangle_plot_new.py
2918/1: %run make_sepangle_plot_new.py
2919/1: %run make_sepangle_plot_new.py
2920/1: %run make_sepangle_plot_new.py
2921/1: %run make_sepangle_plot_new.py
2922/1: %run make_sepangle_plot_new.py
2922/2: number_diff_sta
2922/3: sep_angle_sta
2922/4: diff_ani_sta
2922/5: %run make_multiplots_new.py
2923/1: %run make_multiplots_new.py
2924/1: %run make_sepangle_plot_new.py
2925/1: %run make_sepangle_plot_new.py
2925/2: pylab.show()
2926/1: %run make_sepangle_plot_new.py
2926/2: plt.show()
2927/1: %run make_sepangle_plot_new.py
2927/2: plot_nobacksub()
2927/3:
for i, txt in enumerate(data_sta.Nr):
    print(i, txt)
2927/4:
for i, txt in enumerate(data_sta.Nr):
    print(txt, data_sta.sep_ang[i])
2928/1: %run make_sepangle_plot_new.py
2928/2: plot_nobacksub(numbers=True)
2929/1: %run make_sepangle_plot_new.py
2930/1: %run make_sepangle_plot_new.py
2930/2: plot_nobacksub()
2931/1: plot_nobacksub()
2931/2: %run make_sepangle_plot_new.py
2931/3: plot_nobacksub()
2932/1: %run make_sepangle_plot_new.py
2933/1: %run make_sepangle_plot_new.py
2933/2: plot_backsub_diff()
2934/1: plot_backsub20()
2934/2: %run make_sepangle_plot_new.py
2934/3: plot_backsub20()
2934/4: plot_nobacksub()
2935/1: plot_nobacksub()
2935/2: %run make_sepangle_plot_new.py
2935/3: plot_nobacksub()
2936/1: plot_nobacksub(numbers=False)
2936/2: %run make_sepangle_plot_new.py
2936/3: plot_nobacksub(numbers=False)
2937/1: %run make_sepangle_plot_new.py
2937/2: plot_nobacksub()
2938/1: %run make_sepangle_plot_new.py
2938/2: plot_nobacksub()
2938/3: data_sta.sep_ang
2938/4: data_sta.sep_ang[0]
2939/1: %run make_sepangle_plot_new.py
2939/2: plot_nobacksub()
2940/1: %run make_sepangle_plot_new.py
2940/2: plot_nobacksub()
2940/3: plot_backsub20()
2940/4: plot_backsub_diff()
2941/1: %run make_sepangle_plot_new.py
2941/2: plot_backsub_diff()
2941/3: plot_backsub_diff(numbers=False)
2941/4:
for i in numbers_diff_sta:
    print(i)
2941/5:
for i in number_diff_sta:
    print(i)
2941/6: sep_angle_sta
2941/7:
for i,nr in enumerate(number_diff_sta):
    print(nr)
2941/8:
for i,nr in enumerate(number_diff_sta):
    print(i,nr)
2942/1: %run make_sepangle_plot_new.py
2942/2: plot_backsub_diff(numbers=False)
2942/3: plot_backsub_diff(numbers=True)
2943/1: %run make_sepangle_plot_new.py
2943/2: plot_backsub_diff(numbers=True)
2944/1: %run make_sepangle_plot_new.py
2944/2: plot_backsub_diff(numbers=True)
2945/1: %run make_sepangle_plot_new.py
2945/2: sep_angle_sta
2945/3: diff_ani_sta
2945/4: diff_ani_sta
2945/5: diff_ani_sta[0]
2945/6: diff_ani_sta[1]
2945/7:
        for i,nr in enumerate(number_diff_sta):
            print(nr)
            print(sep_angle_sta[i])
            print(diff_ani_sta[i])
2946/1: %run make_sepangle_plot_new.py
2946/2: plot_backsub_diff(numbers=True)
2947/1: %run make_sepangle_plot_new.py
2947/2: plot_backsub_diff(numbers=True)
2948/1: %run make_sepangle_plot_new.py
2949/1: %run make_sepangle_plot_new.py
2949/2: %run make_sepangle_plot_new.py
2950/1: %run make_multiplots_new.py
2951/1: %run make_multiplots_new.py
2952/1: %run make_multiplots_new.py
2953/1: %run make_multiplots_new.py
2954/1: %run make_multiplots_new.py
2955/1: %run make_multiplots_new.py
2956/1: %run make_multiplots_new.py
2957/1: %run make_multiplots_new.py
2958/1: %run make_multiplots_new.py
2959/1: %run make_multiplots_new.py
2960/1: %run make_multiplots_new.py
2961/1: %run make_multiplots_SEPT_old.py
2962/1: %run make_multiplots_new.py
2962/2: dataA
2962/3: dataA.index
2962/4: ange(1,len(dataA.index)+1)
2962/5: range(1,len(dataA.index)+1)
2963/1: %run make_multiplots_new.py
2965/1: %run load_el_data.py
2966/1: %run make_multiplots_new.py
2967/1: %run load_el_data.py
2968/1: %run load_el_data.py
2969/1: %run make_multiplots_new.py
2971/1: %run make_multiplots_new.py
2971/2: %run load_el_data.py
2972/1: %run load_el_data.py
2972/2: fail_a
2972/3: fail_b
2971/3: fail_a
2971/4: fail_b
2973/1: %run make_multiplots_new.py
2973/2: dataA.index
2973/3: event
2973/4: event.get_output
2973/5: event.get_output()
2973/6: event.time_max_ani
2973/7: event.max_ani_val
2973/8: event.I_at_max_ani
2974/1: %run make_multiplots_new.py
2975/1: %run make_multiplots_new.py
2976/1: %run make_multiplots_new.py
2977/1: %run make_multiplots_new.py
2978/1: %run make_multiplots_new.py
2979/1: %run make_multiplots_new.py
2979/2: dataA
2979/3: %run make_multiplots_new.py
2979/4: dataA.Number[:10]
2979/5: dataA.Number[:20]
2980/1: dataA.Number[:20]
2980/2: %run make_multiplots_new.py
2980/3: event
2980/4: event_nr
2980/5: event.event_nr
2980/6: event.nr
2981/1: %run make_multiplots_new.py
2982/1: %run make_multiplots_new.py
2983/1: %run make_multiplots_new.py
2984/1: %run make_multiplots_new.py
2985/1: %run make_multiplots_new.py
2986/1: %run make_multiplots_new.py
2987/1: %run make_multiplots_new.py
2988/1: %run make_multiplots_new.py
2988/2: event.time_I_max
2988/3: event.time_I_max > 0
2989/1: %run make_multiplots_new.py
2989/2: event.time_I_max > 0
2989/3: event.time_I_max
2990/1: event.time_I_max
2991/1: event.time_I_max
2991/2: %run make_multiplots_new.py
2992/1: %run make_multiplots_new.py
2992/2: event.get_max_sc()
2992/3: max_tele_dict
2993/1: %run make_multiplots_new.py
2994/1: %run make_multiplots_new.py
2995/1: %run make_multiplots_new.py
2996/1: %run make_multiplots_new.py
2996/2: event.I_data
2996/3: event.I_omni
2996/4: ind = np.where((event.doy >= event.i_interval[0]) & (event.doy <= event.i_interval[1]))[0]
2996/5: ind
2996/6: event.I_data[ind]
2996/7: I_sun = event.I_data[:,0][ind]
2996/8: I_sun
2996/9: I.data.shape
2996/10: event.I_data.shape
2996/11: event.I_data[:,0].shape
2996/12: event.I_data[:,0]
2996/13: event.I_data[:,0][ind]
2996/14: ind
2996/15: ind.shape
2996/16: event.I_data[:,0][ind].shape
2996/17: I.sun
2996/18: I_dun
2996/19: I_sun
2996/20: snp.argmax(I_sun)
2996/21: np.argmax(I_sun)
2996/22: I_sun[400]
2996/23: I_sun[390,410]
2996/24: I_sun[390:410]
2996/25: II = I_sun[390:410]
2996/26: np.argmax(II)
2996/27: np.nanargmax(II)
2997/1: %run make_multiplots_new.py
2998/1: %run make_multiplots_new.py
2998/2: data_type
2998/3: fit_method
2998/4: event.backsub_type
2998/5: outfile
2999/1: %run make_multiplots_new.py
3000/1: %run make_multiplots_new.py
3001/1: %run make_multiplots_new.py
3002/1: %run make_multiplots_new.py
3004/1: %run make_multiplots_new.py
3005/1: %run make_multiplots_new.py
3006/1: %run make_multiplots_new.py
3007/1: %run make_multiplots_new.py
3008/1: %run make_multiplots_new.py
3009/1: %run make_multiplots_new.py
3010/1: %run make_multiplots_new.py
3011/1: %run make_multiplots_new.py
3012/1: %run make_multiplots_new.py
3013/1: %run make_multiplots_new.py
3013/2: d
3014/1: d
3014/2: %run make_multiplots_new.py
3015/1: %run make_multiplots_new.py
3016/1: %run make_multiplots_new.py
3017/1: %run make_multiplots_new.py
3017/2: event.doy
3017/3: event.ani
3017/4: X1
3017/5: X2
3017/6: event.date.tiemtuple().tm_year
3017/7: event.date.timetuple().tm_year
3018/1: %run make_multiplots_new.py
3018/2: event.plot_A()
3018/3: X1
3018/4: X1,X2 = 1.0590277777777777, 2.0590277777777777
3018/5: X1
3018/6: self.plot_A(ax[3], self.doy, self.ani, X1, X2, self.date.timetuple().tm_year)
3018/7: evnt.plot_A(ax[3], event.doy, event.ani, X1, X2, event.date.timetuple().tm_year)
3018/8: event.plot_A(ax[3], event.doy, event.ani, X1, X2, event.date.timetuple().tm_year)
3019/1: %run make_multiplots_new.py
3020/1: %run make_multiplots_new.py
3021/1: %run make_multiplots_new.py
3022/1: %run make_multiplots_new.py
3023/1: %run make_multiplots_new.py
3024/1: %run make_multiplots_new.py
3025/1: %run make_multiplots_new.py
3026/1: %run make_multiplots_new.py
3027/1: %run make_multiplots_new.py
3028/1: %run make_multiplots_new.py
3028/2: myfunc.my_time_axis
3028/3: X2
3028/4: X1,X2 = 1.0590277777777777, 2.0590277777777777
3028/5: X2-X1
3029/1: %run make_multiplots_new.py
3030/1: %run make_multiplots_new.py
3031/1: %run make_multiplots_new.py
3032/1: %run make_multiplots_new.py
3033/1: %run make_multiplots_new.py
3034/1: %run make_multiplots_new.py
3035/1: %run make_multiplots_new.py
3036/1: %run make_multiplots_new.py
3037/1: %run make_multiplots_new.py
3038/1: %run make_multiplots_new.py
3039/1: %run make_multiplots_new.py
3040/1: %run make_multiplots_new.py
3040/2: DateFormatter
3040/3: years = YearLocator()
3040/4: years
3040/5: years_fmt = dateFormatter('%Y')
3040/6: years_fmt = DateFormatter('%Y')
3040/7: years_fmt
3040/8: fig, ax = plt.subplots()
3040/9:

years = mdates.YearLocator()   # every year
months = mdates.MonthLocator()  # every month
years_fmt = mdates.DateFormatter('%Y')
3040/10: import matplotlib.dates as mdates
3040/11:

years = mdates.YearLocator()   # every year
months = mdates.MonthLocator()  # every month
years_fmt = mdates.DateFormatter('%Y')
3040/12:
ax.xaxis.set_major_locator(years)
ax.xaxis.set_major_formatter(years_fmt)
ax.xaxis.set_minor_locator(months)
3041/1: %run make_multiplots_new.py
3041/2: majorlocator
3041/3: majorLocator
3041/4: ax
3042/1: ax
3042/2: %run make_multiplots_new.py
3043/1: %run make_multiplots_new.py
3044/1: %run make_multiplots_new.py
3045/1: %run tessst.py
3046/1: %run tessst.py
3046/2: xdata*2
3046/3: ydata
3046/4: xdata
3048/1: xdata
3048/2: %run tessst.py
3049/1: %run tessst.py
3050/1: %run tessst.py
3051/1: %run tessst.py
3052/1: %run tessst.py
3053/1: %run tessst.py
3053/2: ax
3053/3: ax.xaxis.get_majorticklocs()
3054/1: %run tessst.py
3054/2: ax.xaxis.get_majorticklocs()
3055/1: ax.xaxis.get_majorticklocs()
3055/2: %run tessst.py
3056/1: %run tessst.py
3056/2: ax.xaxis.get_major_locator
3056/3: ax.xaxis.get_major_ticks
3056/4: ax.xaxis.get_major_ticks()
3056/5: ax.xaxis.get_major_locator()
3056/6: ax.xaxis.get_majorticklines
3056/7: ax.xaxis.get_majorticklines()
3056/8: ax.xaxis.get_majorticklocs()
3057/1: ax.xaxis.get_majorticklocs()
3057/2: %run tessst.py
3057/3: ax.xaxis.get_majorticklocs()
3057/4: majorLocator
3057/5: majorLocator.axis
3057/6: majorLocator.MAXTICKS
3057/7: majorLocator.tick_values
3058/1: %run tessst.py
3059/1: %run tessst.py
3060/1: %run tessst.py
3061/1: %run tessst.py
3062/1: %run tessst.py
3063/1: %run tessst.py
3064/1: %run tessst.py
3065/1: %run tessst.py
3066/1: %run tessst.py
3067/1: %run tessst.py
3067/2: ax.xaxis.get_majorticklocs()
3067/3: ax.xaxis.get_majorticklocs()
3068/1: %run tessst.py
3068/2: ax.xaxis.get_majorticklocs()
3068/3: xdata
3069/1: xdata
3069/2: %run tessst.py
3069/3: ax.xaxis.get_majorticklocs()
3070/1: %run tessst.py
3070/2: ax.xaxis.get_majorticklocs()
3071/1: %run make_multiplots_new.py
3072/1: %run make_multiplots_new.py
3072/2: ax.xaxis.get_majorticklocs()
3073/1: %run make_multiplots_new.py
3074/1: %run make_multiplots_new.py
3075/1: %run make_multiplots_new.py
3076/1: %run make_multiplots_new.py
3077/1: %run make_multiplots_new.py
3078/1: %run make_multiplots_new.py
3079/1: %run make_multiplots_new.py
3080/1: %run make_multiplots_new.py
3081/1: %run make_multiplots_new.py
3082/1: %run make_multiplots_new.py
3083/1: %run make_multiplots_new.py
3086/1: %run make_multiplots_new.py
3087/1: %run make_multiplots_new.py
3088/1: %run make_multiplots_new.py
3089/1: %run main_solli.py
3090/1: %run main_solli.py
3090/2: data
3090/3: data.date_onset[i]
3090/4: data.date_onset[i]+data.hour_onset[i]
3090/5: data.date_onset[i]
3090/6: type(data.date_onset[i])
3090/7: type(data.hour_onset[i])
3090/8: data.date_onset[i]+str(data.hour_onset[i])
3090/9: data.date_onset[i]+' '+str(data.hour_onset[i])
3091/1: %run main_solli.py
3092/1: %run main_solli.py
3093/1: %run main_solli.py
3094/1: %run main_solli.py
3094/2: date_rich
3095/1: %run make_multiplots_new.py
3096/1: %run make_multiplots_new.py
3097/1: %run make_multiplots_new.py
3098/1: %run make_multiplots_new.py
3099/1: %run main_solli
3100/1: %run main_solli
3100/2: date_nina
3101/1: date_nina
3101/2: %run main_solli
3101/3: data.date_Ni_STA[i]
3102/1: %run main_solli
3103/1: %run main_solli
3103/2: date_nina
3104/1: %run make_multiplots_new.py
3103/3: date_nina.hour
3105/1: %run make_multiplots_new.py
3106/1: %run main_solli
3106/2: date_rich
3106/3: date_nina_A
3106/4: date_nina_b
3106/5: doy
3107/1: doy
3107/2: %run main_solli
3107/3: doy
3107/4: startDoy
3108/1: from datetime import timedetla
3108/2: from datetime import timedelta
3108/3: timedelta(1)
3108/4: timedelta(hours=1)
3108/5: timedelta(min=1)
3108/6: timedelta(minute=1)
3108/7: timedelta(minutes=1)
3110/1: %run main_solli
3111/1: %run main_solli
3111/2: date_rich
3111/3: backsub_start
3111/4: backsub_end_A
3111/5: backsub_end_A2
3111/6: backsub_end_A_2
3112/1: %run main_solli
3113/1: %run main_solli
3114/1: %run main_solli
3115/1: %run main_solli
3116/1: %run main_solli
3116/2: backsub_start_A
3116/3: backsub_start_A_2
3116/4: backsub_end_A_2
3116/5: backsub_end_A
3117/1: %run main_solli
3118/1: %run main_solli
3119/1: %run main_solli
3119/2: backsub_end_B_2
3119/3: backsub_end_B
3119/4: backsub_start_B
3119/5: backsub_start_B_2
3119/6: date_nina
3119/7: date_nina_A
3119/8: backsub_end_A
3119/9: backsub_start_B_2
3119/10: backsub_start_B
3119/11: backsub_end_B
3119/12: backsub_end_B_2
3119/13: backsub_start_A
3119/14: backsub_end_A
3119/15: backsub_start_B
3119/16: backsub_end_B
3119/17: backsub_end_B_2
3119/18: backsub_start_B
3120/1: %run main_solli
3121/1: %run main_solli
3121/2: startDoy
3121/3: datetime(year=2007,month=7,day=133)
3122/1: %run main_solli
3123/1: %run main_solli
3124/1: %run main_solli
3124/2: %run make_multiplots_new.py
3125/1: %run make_multiplots_new.py
3126/1: %run make_multiplots_new.py
3127/1: %run make_multiplots_new.py
3128/1: %run make_multiplots_new.py
3128/2: data
3129/1: %run make_multiplots_new.py
3129/2: data
3129/3: data.date_Ni_STA
3129/4: data.date_Ni_STA[i]
3130/1: %run make_multiplots_new.py
3131/1: %run make_multiplots_new.py
3132/1: %run make_multiplots_new.py
3132/2: data.date_t1_STA[i]
3133/1: data.date_t1_STA[i]
3133/2: %run make_multiplots_new.py
3134/1: %run make_multiplots_new.py
3135/1: %run main_solli
3135/2: %run make_multiplots_new.py
3136/1: %run make_multiplots_new.py
3137/1: %run make_multiplots_new.py
3138/1: %run make_multiplots_new.py
3139/1: %run make_multiplots_new.py
3139/2: 0.083 * 24
3139/3: 0.083 * 24 *60
3139/4: 20/60
3139/5: 20/60/24.
3139/6: 20/60/24.
3139/7: find_intervals(300)
3139/8: o = datetime(2000,1,1)
3139/9: o
3139/10: find_intervals(o)
3139/11: 1/24
3139/12: 1/24.
3139/13: 2/24.
3139/14: 7/24.
3140/1: %run make_multiplots_new.py
3141/1: %run make_multiplots_new.py
3142/1: %run make_multiplots_new.py
3143/1: %run main_solli
3144/1: %run make_multiplots_new.py
3146/1: %run make_multiplots_new.py
3146/2: onset
3147/1: %run main_solli
3148/1: %run main_solli
3148/2: date_nina
3149/1: %run make_multiplots_new.py
3150/1: %run main_solli
3150/2: %run make_multiplots_new.py
3151/1: %run make_multiplots_new.py
3152/1: %run make_multiplots_new.py
3153/1: %run make_multiplots_new.py
3154/1: %run make_multiplots_new.py
3155/1: %run make_multiplots_new.py
3156/1: %run make_multiplots_new.py
3157/1: %run make_multiplots_new.py
3158/1: %run make_multiplots_new.py
3159/1: %run make_multiplots_new.py
3159/2: dataB
3159/3: event
3159/4: type(event)
3160/1: %run make_multiplots_new.py
3160/2: event
3160/3: event.doy
3160/4: myfunc.date2doy
3160/5: event.doy[0]
3161/1: %run main_solli
3162/1: %run load_el_data.py
3163/1: %run load_el_data.py
3164/1: %run load_el_data.py
3165/1: %run load_sync_data_rich.py
3166/1: %run load_sync_data_rich.py
3167/1: %run make_multiplots.py
3168/1: %run make_multiplots.py
3169/1: %run make_multiplots.py
3170/1: %run make_multiplots.py
3171/1: %run make_multiplots.py
3172/1: %run make_multiplots.py
3173/1: %run make_multiplots.py
3174/1: %run make_multiplots.py
3175/1: %run make_multiplots.py
3175/2: event
3175/3: event.doy
3175/4: event.doy[1]
3175/5: event.doy[0]
3175/6: event.onset
3175/7: event.date
3175/8: myfunc.datetime2doy(event.date)
3175/9: event.doy[0]
3175/10: event.doy[1]
3175/11: event.doy[-1]
3176/1: %run load_sync_data_rich.py
3177/1: %run load_sync_data_rich.py
3178/1: %run make_sepangle_plot_new.py
3178/2: plot_backsub_diff(numbers=True)
3178/3: plot_backsub20()
3178/4: plot_nobacksub()
3178/5: %run make_sepangle_plot.py
3179/1: %run make_sepangle_plot_new.py
3179/2: diff_ani_sta
3179/3: data_stb_backsub20
3179/4: file_STA_nobacksub
3179/5: %run make_multiplots.py
3180/1: %run make_multiplots.py
3181/1: %run make_multiplots.py
3182/1: %run make_multiplots.py
3183/1: %run make_multiplots.py
3184/1: %run make_multiplots.py
3184/2: event
3184/3: event.date
3184/4: event.get_max_sc()
3184/5: event.ani
3184/6: event.I_data
3184/7: event.I_omni
3185/1: %run make_multiplots.py
3186/1: %run make_multiplots.py
3187/1: %run make_multiplots.py
3188/1: %run make_multiplots.py
3188/2: time_I_max_list
3188/3: time_I_max_list_A
3188/4: date_asciiA
3189/1: %run make_multiplots.py
3190/1: %run make_multiplots.py
3191/1: %run make_multiplots.py
3191/2: i
3191/3: date_asciiA
3191/4: date_asciiB
3191/5: len(date_asciiB)
3191/6: Nr_list_B
3191/7: sc_asciiB
3192/1: %run make_multiplots.py
3193/1: %run make_multiplots.py
3194/1: %run make_multiplots.py
3196/1: %run make_multiplots.py
3196/2: event
3196/3: event.doy
3196/4: event.doy[0]
3196/5: event.doy[-1]
3196/6: event.date
3196/7: myfunc.datetime2doy(event.date)
3197/1: %run load_sync_data_rich.py
3198/1: %run load_sync_data_rich.py
3200/1: %run load_sync_data_rich.py
3201/1: %run make_multiplots.py
3201/2: %run make_multiplots.py
3201/3: event.doy
3201/4: event.doy[0]
3201/5: event.doy[-1]
3201/6: myfunc.datetime2doy(event.date)
3202/1: %run load_sync_data_rich.py
3203/1: %run load_sync_data_rich.py
3204/1: %run load_sync_data_rich.py
3205/1: %run load_sync_data_rich.py
3206/1: %run make_multiplots.py
3207/1: %run make_multiplots.py
3208/1: %run load_sync_data_rich.py
3209/1: %run load_sync_data_rich.py
3210/1: %run make_multiplots.py
3211/1: %run make_multiplots.py
3212/1: %run make_multiplots.py
3213/1: %run make_multiplots.py
3214/1: %run make_multiplots.py
3215/1: %run make_sepangle_plot_new.py
3216/1: %run make_sepangle_plot_new.py
3216/2: plot_nobacksub()
3216/3: plot_backsub20()
3216/4: data_type
3216/5: fit_methof
3216/6: fit_method
3217/1: %run make_sepangle_plot_new.py
3217/2: plot_nobacksub()
3217/3: plot_backsub20()
3217/4: clear
3217/5: plot_backsub20()
3217/6: data_sta_backsub20
3217/7: data_sta_backsub20.sep_ang
3218/1: %run make_sepangle_plot_new.py
3218/2: plot_backsub20()
3219/1: %run make_sepangle_plot_new.py
3219/2: plot_backsub20()
3220/1: plot_backsub20()
3220/2: %run make_sepangle_plot_new.py
3220/3: plot_backsub20()
3221/1: %run make_sepangle_plot_new.py
3221/2: plot_backsub20()
3221/3: data_sta_backsub20.index
3221/4: data_sta_backsub20.sep_ang[46]
3221/5: data_sta_backsub20.sep_ang[47]
3222/1: %run make_sepangle_plot_new.py
3222/2: plot_backsub20()
3223/1: %run make_sepangle_plot_new.py
3223/2: plot_backsub20()
3224/1: %run make_sepangle_plot_new.py
3224/2: plot_backsub20()
3225/1: %run make_sepangle_plot_new.py
3225/2: plot_backsub20()
3226/1: %run make_sepangle_plot_new.py
3226/2: plot_backsub20()
3227/1: %run make_sepangle_plot_new.py
3227/2: plot_backsub20()
3227/3: data_sta_backsub20.sep_ang[29]
3228/1: %run make_sepangle_plot_new.py
3228/2: plot_backsub20()
3229/1: %run make_sepangle_plot_new.py
3229/2: plot_backsub20()
3230/1: plot_backsub20()
3230/2: %run make_sepangle_plot_new.py
3230/3: plot_backsub20()
3231/1: %run make_sepangle_plot_new.py
3231/2: plot_backsub20()
3232/1: plot_backsub20()
3232/2: %run make_sepangle_plot_new.py
3232/3: plot_backsub20()
3233/1: %run make_sepangle_plot_new.py
3233/2: plot_backsub20()
3234/1: %run make_sepangle_plot_new.py
3234/2: plot_backsub20()
3235/1: %run make_sepangle_plot_new.py
3235/2: plot_backsub20()
3236/1: %run make_sepangle_plot_new.py
3236/2: plot_backsub20()
3237/1: %run make_sepangle_plot_new.py
3237/2: plot_backsub20()
3238/1: %run make_sepangle_plot_new.py
3238/2: plot_backsub20()
3239/1: %run make_sepangle_plot_new.py
3239/2: plot_backsub20()
3240/1: %run make_sepangle_plot_new.py
3240/2: plot_backsub20()
3241/1: plot_backsub20()
3241/2: %run make_sepangle_plot_new.py
3241/3: plot_backsub20()
3242/1: %run make_sepangle_plot_new.py
3242/2: plot_backsub20()
3243/1: %run make_sepangle_plot_new.py
3243/2: plot_backsub20()
3244/1: %run make_sepangle_plot_new.py
3244/2: plot_backsub20()
3245/1: %run make_sepangle_plot_new.py
3245/2: plot_backsub20()
3245/3: plot_nobacksub()
3245/4: plot_backsub_diff()
3245/5: plot_backsub20()
3247/1: plot_backsub20()
3247/2: %run make_sepangle_plot_new.py
3248/1: %run make_sepangle_plot_new.py
3249/1: %run make_sepangle_plot_new.py
3250/1: %run make_sepangle_plot_new.py
3250/2: plt.show()
3251/1: %run make_sepangle_plot_new.py
3252/1: %run make_sepangle_plot_new.py
3253/1: %run make_sepangle_plot_new.py
3254/1: %run make_sepangle_plot_new.py
3255/1: %run make_sepangle_plot_new.py
3256/1: %run make_sepangle_plot_new.py
3257/1: %run make_sepangle_plot_new.py
3258/1: %run make_sepangle_plot_new.py
3259/1: %run make_sepangle_plot_new.py
3259/2: %run make_sepangle_plot_new.py
3260/1: %run make_sepangle_plot_new.py
3261/1: %run make_sepangle_plot_new.py
3262/1: %run make_sepangle_plot_new.py
3263/1: %run make_sepangle_plot_new.py
3264/1: %run make_sepangle_plot_new.py
3265/1: %run make_sepangle_plot_new.py
3266/1: %run make_sepangle_plot_new.py
3267/1: %run make_sepangle_plot_new.py
3268/1: %run make_sepangle_plot_new.py
3269/1: %run make_sepangle_plot_new.py
3270/1: %run make_sepangle_plot_new.py
3271/1: %run make_sepangle_plot_new.py
3272/1: %run make_sepangle_plot_new.py
3273/1: %run make_sepangle_plot_new.py
3274/1: %run make_sepangle_plot_new.py
3275/1: %run make_sepangle_plot_new.py
3275/2: plt.show()
3275/3: plot_backsub20()
3276/1: %run make_sepangle_plot_new.py
3277/1: %run make_sepangle_plot_new.py
3278/1: %run make_sepangle_plot_new.py
3279/1: %run make_sepangle_plot_new.py
3280/1: %run make_sepangle_plot_new.py
3281/1: %run make_sepangle_plot_new.py
3282/1: %run make_sepangle_plot_new.py
3283/1: %run make_sepangle_plot_new.py
3284/1: %run make_sepangle_plot_new.py
3285/1: %run make_sepangle_plot_new.py
3286/1: %run make_sepangle_plot_new.py
3287/1: %run make_sepangle_plot_new.py
3288/1: %run make_sepangle_plot_new.py
3289/1: %run make_sepangle_plot_new.py
3290/1: %run make_sepangle_plot_new.py
3291/1: %run make_sepangle_plot_new.py
3292/1: %run make_sepangle_plot_new.py
3293/1: %run make_sepangle_plot_new.py
3294/1: %run make_sepangle_plot_new.py
3295/1: %run make_sepangle_plot_new.py
3296/1: %run make_sepangle_plot_new.py
3297/1: %run make_sepangle_plot_new.py
3298/1: %run make_sepangle_plot_new.py
3299/1: %run make_sepangle_plot_new.py
3300/1: %run make_sepangle_plot_new.py
3301/1: %run make_sepangle_plot_new.py
3301/2: data_sta_backsub20.Nr[:7]
3301/3: i
3301/4: (data_sta_backsub20.sep_ang[i], data_sta_backsub20.ani_max[i])
3301/5: (data_stb_backsub20.sep_ang[i], data_stb_backsub20.ani_max[i])
3301/6: %run make_sepangle_plot_new.py
3301/7: plt.show()
3302/1: plt.show()
3302/2: %run make_sepangle_plot_new.py
3302/3: plt.show()
3302/4: data_stb_
3302/5: data_stb
3302/6: data_stb.sep_ang
3302/7: data_stb.sep_ang[0]
3302/8: data_stb.sep_ang[0] > -0.5
3303/1: data_stb.sep_ang[0] > -0.5
3303/2: %run make_sepangle_plot_new.py
3304/1: %run make_sepangle_plot_new.py
3305/1: %run make_sepangle_plot_new.py
3306/1: %run make_sepangle_plot_new.py
3307/1: %run make_sepangle_plot_new.py
3308/1: %run make_sepangle_plot_new.py
3309/1: %run make_sepangle_plot_new.py
3310/1: %run make_sepangle_plot_new.py
3311/1: %run make_sepangle_plot_new.py
3312/1: %run make_sepangle_plot_new.py
3313/1: %run make_sepangle_plot_new.py
3313/2: sep_angle_sta
3313/3: diff_ani_sta
3313/4: number_diff_sta
3313/5: number_diff_sta.shape
3313/6: len(number_diff_sta)
3313/7: len(sep_angle_sta)
3313/8: len(number_diff_sta)
3313/9: i
3313/10: sep_angle_sta
3313/11: sep_angle_sta[21]
3313/12: diff_ani_sta[21]
3314/1: %run make_sepangle_plot_new.py
3314/2: diff_ani_sta
3314/3: diff_ani_sta[22]
3314/4: enumerate(number_diff_sta)
3314/5:
for i, nr in enumerate(number_diff_sta):
    print(i,nr)
3314/6:
for i, nr in enumerate(number_diff_sta):
    print(i,nr)
    print(sep_angle_sta[i], diff_ani_sta[i])
3315/1: %run make_sepangle_plot_new.py
3316/1: %run make_sepangle_plot_new.py
3317/1: %run make_sepangle_plot_new.py
3318/1: %run make_sepangle_plot_new.py
3318/2: diff_ani_sta
3319/1: %run make_sepangle_plot_new.py
3319/2: data_stb
3320/1: %run make_multiplots.py
3321/1: %run make_multiplots.py
3322/1: %run make_multiplots.py
3322/2: dataB.date_Ni_STB[i]
3322/3: dataA
3322/4: dataB
3322/5: dataA
3322/6: dataB
3322/7: dataA
3322/8: dataA.date_Ni_STA_
3322/9: dataA.date_Ni_STA
3322/10: dataA.date_Ni_STB
3323/1: %run make_multiplots.py
3323/2: sc_asciiB
3324/1: %run make_multiplots.py
3324/2: date_asciiB
3324/3: date_asciiA
3325/1: date_asciiA
3325/2: %run make_multiplots.py
3325/3: date_asciiA
3325/4: date_asciiB
3327/1: %run make_multiplots.py
3328/1: %run make_sepangle_plot_new.py
3329/1: %run make_multiplots.py
3329/2: %run make_sepangle_plot_new.py
3331/1: %run make_multiplots.py
3331/2: %run make_sepangle_plot_new.py
3332/1: %run make_sepangle_plot_new.py
3333/1: %run make_multiplots.py
3333/2: %run make_sepangle_plot_new.py
3334/1: %run make_sepangle_plot_new.py
3335/1: %run make_multiplots.py
3336/1: %run make_multiplots.py
3337/1: %run make_multiplots.py
3338/1: %run make_multiplots.py
3339/1: %run make_multiplots.py
3340/1: %run make_multiplots.py
3341/1: %run make_multiplots.py
3342/1: %run make_multiplots.py
3343/1: %run make_multiplots.py
3344/1: %run make_multiplots.py
3345/1: %run make_multiplots.py
3346/1: %run make_multiplots.py
3347/1: %run make_multiplots.py
3348/1: %run make_multiplots.py
3349/1: %run make_multiplots.py
3350/1: %run make_multiplots.py
3351/1: %run make_multiplots.py
3352/1: %run make_multiplots.py
3353/1: %run make_multiplots.py
3354/1: %run make_multiplots.py
3355/1: %run make_multiplots.py
3356/1: %run make_multiplots.py
3357/1: %run make_multiplots.py
3358/1: %run make_multiplots.py
3359/1: %run make_multiplots.py
3360/1: %run make_multiplots.py
3360/2: event
3360/3: event.get_output()
3360/4: event
3360/5: event.plot_pa
3360/6: event.plot_pa()
3361/1: event.plot_pa()
3361/2: %run make_multiplots.py
3362/1: %run make_multiplots.py
3363/1: %run make_multiplots.py
3364/1: %run make_multiplots.py
3365/1: %run make_multiplots.py
3366/1: %run make_multiplots.py
3367/1: %run make_multiplots.py
3368/1: %run make_multiplots.py
3369/1: %run make_multiplots.py
3370/1: %run make_multiplots.py
3371/1: %run make_multiplots.py
3372/1: %run make_multiplots.py
3373/1: %run make_multiplots.py
3374/1: %run make_multiplots.py
3375/1: %run make_multiplots.py
3376/1: %run make_multiplots.py
3377/1: %run make_multiplots.py
3378/1: %run make_multiplots.py
3378/2: event.pa_data
3378/3: event.pa_data.flatten()
3378/4: np.unique(event.pa_data.flatten())
3378/5: p = event.pa_data.flatten()
3378/6: p.shape
3378/7: np.unique(p)
3378/8: a = np.array([1,2,3,4,nan,nan])
3378/9: np.unique(a)
3378/10: a = np.array([1,2,3,4,4,nan,nan])
3378/11: np.unique(a)
3378/12: p
3378/13: event.pa_data
3378/14: a = np.array([1.,inf,inf,nan,nan])
3378/15: np.unique(a)
3378/16: a = np.array([1.,inf,inf,inf,inn,nan,nan])
3378/17: clear
3378/18: event.pa_data
3378/19: event.pa_data.shape
3378/20: A = np.ones(3,5)
3378/21: A = np.ones((3,5))
3378/22: A
3378/23: A[:,0] = nan
3378/24: A
3378/25: np.all(nan)
3378/26: np.all(1)
3378/27: np.isnan(A)
3378/28: np.all(np.isnan(A))
3378/29: np.all(np.isnan(A),axis=0)
3378/30: np.all(np.isnan(A),axis=1)
3379/1: np.all(np.isnan(A),axis=1)
3379/2: %run make_multiplots.py
3380/1: %run make_multiplots.py
3380/2: event
3380/3: event.ani
3380/4: event.max_ani_val
3380/5: event.time_I_max
3380/6: event.time_max_ani
3380/7: event.doy
3380/8: event.date
3380/9: myfunc.datetime2doy(event.date)
3381/1: myfunc.datetime2doy(event.date)
3381/2: event.date
3381/3: %run make_multiplots.py
3382/1: %run make_multiplots.py
3383/1: %run make_multiplots.py
3384/1: %run make_multiplots.py
3385/1: %run make_multiplots.py
3386/1: %run make_multiplots.py
3386/2: event
3386/3: event.time_max_ani
3386/4: not event.time_max_ani
3386/5: np.isnan(event.time_max_ani)
3387/1: np.isnan(event.time_max_ani)
3387/2: %run make_multiplots.py
3388/1: %run make_multiplots.py
3389/1: %run make_multiplots.py
3390/1: %run make_multiplots.py
3390/2: event.max_ani_val
3391/1: event.max_ani_val
3391/2: %run make_multiplots.py
3391/3: event.max_ani_val
3392/1: event.max_ani_val
3392/2: %run make_multiplots.py
3393/1: %run make_multiplots.py
3394/1: %run make_multiplots.py
3395/1: %run load_sync_data_rich.py
3397/1: %run load_el_data.py
3398/1: %run make_multiplots.py
3399/1: %run make_multiplots.py
3400/1: %run make_multiplots.py
3400/2: event.y
3400/3: event.i_data
3400/4: event.I_data
3400/5: np.unique(event.y)
3401/1: %run make_multiplots.py
3402/1: %run make_multiplots.py
3403/1: %run make_multiplots.py
3404/1: %run make_multiplots.py
3405/1: %run make_multiplots.py
3405/2: 10*0.5+10
3406/1: 10*0.5+10
3406/2: %run make_multiplots.py
3407/1: %run make_multiplots.py
3407/2: event.backsub
3407/3: event.pa_data
3408/1: %run make_multiplots.py
3409/1: %run load_el_data.py
3410/1: %run load_el_data.py
3411/1: %run load_el_data.py
3412/1: %run load_el_data.py
3413/1: %run load_el_data.py
3414/1: %run load_el_data.py
3415/1: %run load_el_data.py
3416/1: %run load_el_data.py
3417/1: %run load_el_data.py
3418/1: %run load_el_data.py
3419/1: %run load_el_data.py
3420/1: %run load_el_data.py
3421/1: %run load_el_data.py
3422/1: %run load_el_data.py
3423/1: %run load_el_data.py
3424/1: %run load_el_data.py
3425/1: %run load_el_data.py
3426/1: %run make_multiplots.py
3427/1: %run load_el_data.py
3428/1: %run load_el_data.py
3429/1: %run make_sepangle_plot_new.py
3429/2: %run make_sepangle_plot.py
3430/1: %run make_sepangle_plot.py
3430/2: %run make_sepangle_plot.py
3431/1: %run make_multiplots.py
3431/2: dataA
3431/3: dataA.t2
3432/1: %run make_multiplots.py
3433/1: %run make_multiplots.py
3434/1: %run make_multiplots.py
3435/1: %run make_multiplots.py
3436/1: %run make_multiplots.py
3437/1: %run make_multiplots.py
3437/2: diff
3437/3: diff.seconds
3437/4: diff.seconds / 60
3437/5: diff.seconds / 60.
3438/1: %run make_multiplots.py
3439/1: %run make_multiplots.py
3439/2: %run make_multiplots.py
3440/1: %run make_multiplots.py
3441/1: %run make_multiplots.py
3442/1: %run make_multiplots.py
3442/2: 3/24.
3442/3: 4/24.
3443/1: %run make_multiplots.py
3444/1: %run make_multiplots.py
3445/1: %run load_sync_data_rich.py
3446/1: %run load_sync_data_rich.py
3447/1: %run load_sync_data_rich.py
3448/1: %run load_sync_data_rich.py
3449/1: %run load_sync_data_rich.py
3450/1: %run load_sync_data_rich.py
3451/1: %run make_multiplots.py
3452/1: %run make_multiplots.py
3453/1: %run make_multiplots.py
3454/1: %run make_multiplots.py
3455/1: %run make_multiplots.py
3455/2: 0.2*24
3456/1: 0.2*24
3456/2: %run make_multiplots.py
3457/1: %run make_multiplots.py
3458/1: %run make_multiplots.py
3459/1: %run make_multiplots.py
3460/1: %run make_multiplots.py
3460/2: event.time_I_max
3460/3: event.time_max_ani
3460/4: event.time_I_max
3460/5: event.time_I_max_sec
3461/1: %run load_el_data.py
3462/1: %run load_el_data.py
3463/1: 02.*24
3463/2: 0.2*24
3463/3: 0.1*24
3463/4: 0.15*24
3466/1: %run make_multiplots.py
3467/1: %run make_multiplots.py
3468/1: %run make_multiplots.py
3469/1: %run make_multiplots.py
3470/1: %run make_multiplots.py
3471/1: %run load_el_data.py
3472/1: %run make_multiplots.py
3472/2: event.time_I_max
3472/3: event.time_I_max_sec
3472/4: event.time_max_ani
3473/1: event.time_max_ani
3474/1: %run make_multiplots.py
3475/1: %run make_multiplots.py
3476/1: %run make_multiplots.py
3477/1: %run make_multiplots.py
3478/1: %run make_multiplots.py
3479/1: %run make_multiplots.py
3480/1: %run make_multiplots.py
3481/1: %run make_multiplots.py
3480/2: fail
3482/1: %run make_multiplots.py
3483/1: %run make_multiplots.py
3483/2: %run make_multiplots.py
3484/1: %run load_el_data.py
3485/1: %run make_multiplots.py
3486/1: %run make_multiplots.py
3486/2: event.date
3486/3: event.Nr
3486/4: event.nr
3487/1: %run make_multiplots.py
3488/1: %run make_multiplots.py
3488/2: failfail
3488/3: fail
3489/1: %run make_multiplots.py
3490/1: %run make_multiplots.py
3491/1: %run make_multiplots.py
3491/2: fail
3492/1: %run make_multiplots.py
3493/1: %run make_multiplots.py
3494/1: %run make_multiplots.py
3495/1: %run make_multiplots.py
3495/2: diff_t2
3495/3: diff
3495/4: diff_t2 > diff
3495/5: diff_t2 < diff
3495/6: onset
3495/7: diff_t2 - onset
3495/8: diff_t2
3495/9: diff_t2.minutes
3495/10: diff_t2.seconds
3495/11: diff_t2.seconds / 60
3495/12: diff_t2.seconds / 60 / 24
3495/13: diff_t2.seconds / 60 / 60
3495/14: diff_t2.seconds / 60 / 60 / 24
3495/15: diff
3496/1: %run make_multiplots.py
3497/1: %run make_multiplots.py
3497/2: %run make_multiplots.py
3498/1: %run make_multiplots.py
3498/2: fail
3499/1: %run make_multiplots.py
3499/2: fail
3500/1: %run make_multiplots.py
3501/1: %run make_multiplots.py
3501/2: fail
3502/1: %run make_multiplots.py
3503/1: %run make_multiplots.py
3504/1: %run make_multiplots.py
3505/1: %run make_multiplots.py
3506/1: %run make_multiplots.py
3506/2: dataB
3506/3: dataB.onset[i]
3506/4: i
3506/5: len(dataB.onset[i])
3506/6: len(dataB.onset[i])
3506/7: dataB.Nr[i]
3506/8: dataB.Numbr
3506/9: dataB.Number
3506/10: dataB.Number[i]
3507/1: %run make_multiplots.py
3508/1: %run make_multiplots.py
3509/1: %run make_multiplots.py
3510/1: %run make_multiplots.py
3511/1: %run make_multiplots.py
3512/1: %run make_multiplots.py
3513/1: %run make_multiplots.py
3514/1: %run make_multiplots.py
3515/1: %run make_multiplots.py
3516/1: %run make_multiplots.py
3517/1: %run make_multiplots.py
3519/1: %run make_multiplots.py
3520/1: %run make_multiplots.py
3521/1: %run make_multiplots.py
3522/1: %run make_multiplots.py
3522/2: event
3522/3: a,b,c,d = event.get_max_sc()
3522/4: a
3522/5: event.ani_multi_plot_sept(data_type=data_type, fit_method=fit_method)_
3522/6: event.ani_multi_plot_sept(data_type=data_type, fit_method=fit_method)
3522/7: event.ani_multi_plot_sept(data_type= data_type, fit_method = fit_method)
3522/8: event.time_I_max_sec
3523/1: event.time_I_max_sec
3523/2: %run make_multiplots.py
3524/1: %run make_multiplots.py
3525/1: %run make_multiplots.py
3526/1: %run make_multiplots.py
3527/1: clear
3527/2: %run make_multiplots.py
3528/1: %run make_multiplots.py
3529/1: %run make_multiplots.py
3530/1: %run make_multiplots.py
3531/1: %run make_multiplots.py
3532/1: %run make_multiplots.py
3532/2: event
3532/3: event.time_I_max
3532/4: event.I_omni
3532/5: unique(event.I_omni)
3533/1: unique(event.I_omni)
3533/2: %run make_multiplots.py
3533/3: np.all(np.isnan(event.I_omni))
3533/4: event.ani_at_max
3534/1: event.ani_at_max
3534/2: %run make_multiplots.py
3535/1: %run make_multiplots.py
3536/1: %run make_multiplots.py
3537/1: %run make_multiplots.py
3538/1: %run make_multiplots.py
3539/1: %run make_multiplots.py
3540/1: %run make_multiplots.py
3541/1: %run make_multiplots.py
3542/1: %run make_multiplots.py
3542/2: time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg
3542/3: np.isnan(time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg)
3542/4: isnan(time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg)
3542/5: np.isnan
3542/6: np.isnan([1,2,3])
3542/7: np.isnan([time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg])
3542/8: all(np.isnan([time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg]))
3543/1: %run make_multiplots.py
3544/1: %run make_multiplots.py
3545/1: %run make_multiplots.py
3545/2: all(np.isnan([time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg]))
3545/3: np.isnan([time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg])
3546/1: np.isnan([time_I_max_sg, max_I_sg, which_tele_sg, max_ani_sg])
3546/2: %run make_multiplots.py
3547/1: %run make_multiplots.py
3547/2: a,b,c,d,e = event.get_max_sc()
3547/3: a
3548/1: a
3548/2: %run make_multiplots.py
3549/1: %run make_multiplots.py
3550/1: %run make_multiplots.py
3551/1: %run make_multiplots.py
3552/1: %run make_sepangle_plot.py
3553/1: %run make_multiplots.py
3554/1: %run make_multiplots.py
3555/1: %run make_multiplots.py
3556/1: %run make_multiplots.py
3557/1: %run make_sepangle_plot.py
3558/1: %run make_sepangle_plot.py
3559/1: %run make_multiplots.py
3560/1: %run make_multiplots.py
3561/1: %run make_multiplots.py
3562/1: %run make_multiplots.py
3563/1: %run make_multiplots.py
3564/1: %run make_multiplots.py
3565/1: %run make_sepangle_plot.py
3567/1: %run load_el_data.py
3568/1: %run load_el_data.py
3569/1: %run make_multiplots.py
3570/1: %run make_multiplots.py
3571/1: nrs_para = 5
3571/2: nrs_perp = 3
3571/3: ang_para = 30. / nrs_para /2
3571/4: ang_para
3571/5: 30/5
3571/6: linspace(-3,-30. + 3, 5)
3571/7: from numpy import linspace
3571/8: linspace(-3,-30. + 3, 5)
3571/9: a = zeros(3,3,3)
3571/10: from numpy import zeros
3571/11: a = zeros(3,3,3)
3571/12: a = zeros([3,3,3])
3571/13: a
3571/14:
for i in range(3):
    for j in range(3):
        for k in range(3):
            a[i,j,k] = (i+1)*(j+1)*(k+1)
3571/15: a
3571/16: a.shape
3571/17: a = zeros([2,2,2])
3571/18:
for i in range(2):
    for j in range(2):
        for k in range(2):
            a[i,j,k] = (i+1)*(j+1)*(k+1)
3571/19: a
3571/20: a.shape
3571/21: a = zeros([2,3,4])
3571/22:
for i in range(2):
    for j in range(3):
        for k in range(4):
            a[i,j,k] = (i+1)*(j+1)*(k+1)
3571/23: a
3571/24: a.shape
3571/25: sum(a,axis=1)
3571/26: numpy.sum
3571/27: from numpy import sum
3571/28: sum(a,axis=1)
3571/29: a
3571/30: sum(a,axis=0)
3572/1: %run load_pui_ulysses.py
3572/2: %run load_pui_ulysses.py
3572/3: %run load_pui_ulysses.py
3572/4: %run load_pui_ulysses.py
3572/5: d
3572/6: d.get_data("Master","d00")
3572/7: d.data
3572/8: d.get_data("Master", "d90")
3572/9: uTall, Tallind = unique(d.get_data("Master", "d90"), return_index=True)
3572/10: uTall
3572/11: Tallind
3572/12: Tallind.shape
3572/13: uTall.shape
3572/14: uasphi = d.get_data("Master","aspphi")[Tallind]
3572/15: uasphi
3572/16: uasphi.shape
3572/17: uvsw = d.get_data("Master","vsw")[Tallind]
3572/18: uvsw
3572/19: d.get_data("Master", "d90")
3572/20: unique(d.get_data("Master", "d90"))
3572/21: unique(d.get_data("Master", "d90"),return_inverse = True)
3572/22: a,b = unique(d.get_data("Master", "d90"),return_inverse = True)
3572/23: b
3572/24: b[:]
3572/25: b[0:30]
3572/26: b[0:50]
3572/27: vswbins=arange(500.,800.1,10.)
3572/28: around(vswbins[0]-self.vswbins[0],-1)/10
3572/29: vswbins2=arange(300.,800.1,10.)
3572/30: around(vswbins[0]-self.vswbins2[0],-1)/10
3572/31: around(vswbins[0]-vswbins2[0],-1)/10
3572/32: vswbins
3572/33: vswbins2
3572/34: around(vswbins[0]-vswbins2[0],-1)
3572/35: a
3572/36: a.shape
3572/37: b
3573/1: %run load_pui_ulysses.py
3574/1: %run load_pui_ulysses.py
3574/2: d
3574/3: e = d.set_mask('Master','det',0,2,reset=True))
3574/4: e = d.set_mask('Master','det',0,2,reset=True)
3574/5: e.show_mask
3574/6: e.show_mask()
3574/7: d.show_mask
3574/8: d.show_mask()
3574/9: D= Dist3D(d)
3575/1: %run load_pui_ulysses.py
3575/2: D
3575/3: norm_arr, H = D.calc_w3dspecs()
3575/4: norm_arr
3575/5: H
3575/6: unique(norm_arr)
3575/7: d.data
3575/8: norm_arr, H = D.calc_w3dspecs()
3576/1: %run load_pui_ulysses.py
3577/1: %run load_pui_ulysses.py
3577/2: D
3577/3: D.wspace
3577/4: unique(D.wspace)
3577/5: norm_arr, H = D.calc_w3dspecs()
3577/6: norm_arr[norm_arr==0]=1
3577/7: H2 = H/norm_arr
3577/8: wbins = arange(-2,2.01,0.2)
3577/9: pcolormesh(wbins,wbins,H2[10::,:])
3577/10: pcolormesh(wbins,wbins,H2[10:,:])
3577/11: pcolormesh(wbins,wbins,H2[10,:,:])
3577/12: pcolormesh(wbins,wbins,H2[10,:,:].T)
3577/13: H2
3577/14: H2.shape
3577/15: H2[10,:,:]
3577/16: H2[10,:,:].shape
3577/17: D.w3dspace
3577/18: D.w3dspace.shape
3577/19: D.aspphi
3577/20: D.w3dspace(vsw=20,aspphi=0,asptheta=0,epq=30)
3577/21: D.w3dspace(20,0,0,)
3577/22: D.plot_wspace()
3577/23: D.wsdspace.shape
3577/24: D.w3dspace
3577/25: D.w3dspace.shape
3578/1: %run load_pui_ulysses.py
3578/2: ls
3579/1: %run load_pui_ulysses.py
3579/2: D.wspace
3579/3: D.wspace.shape
3579/4: D.w3dspace.shape
3579/5: A = D.w3dspace[0,0,0,20,...]
3579/6: A
3579/7: a.shape
3579/8: A.shape
3579/9: D.w3dspace.shape
3579/10: D.wspace.shape
3579/11: A = D.wspace[10,0,0,20,...]
3579/12: A
3579/13: A.shape
3579/14: A[0,0,0,:]
3579/15: %run swics_collimator_ulysses.py
3579/16: c = collimator()
3579/17: c
3579/18: c.FoV
3579/19: unique(c.FoV)
3580/1: %run swics_collimator_ulysses.py
3580/2: c = collimator()
3580/3: c.FoV
3580/4: unique(c.FoV)
3580/5: c.det1
3581/1: c.det1
3581/2: %run swics_collimator_ulysses.py
3581/3: c = collimator()
3581/4: c.det1
3581/5: %run swics_collimator_ulysses.py
3581/6: %run swics_collimator_ulysses.py
3582/1: %run swics_collimator_ulysses.py
3582/2: c = collimator()
3582/3: c.FoV
3582/4: c.FoV.shape
3583/1: %run swics_collimator_ulysses.py
3583/2: c.FoV.shape
3583/3: c = collimator()
3583/4: c.FoV.shape
3583/5: c.FoV
3583/6: c.FoV.shape
3583/7: from numpy import sum, sqrt
3583/8: sqrt(sum(c.Fov.shape**2),axis = 2)
3583/9: sqrt(sum(c.FoV.shape**2),axis = 2)
3583/10: sqrt(sum(c.FoV.shape)**2,axis = 2)
3583/11: sqrt(sum((c.FoV.shape)**2,axis = 2))
3583/12: sqrt(sum(c.FoV ** 2 , axis = 2))
3583/13: D
3583/14: %run load_pui_ulysses.py
3583/15: D.FoV.shape
3583/16: sqrt(sum(D.FoV ** 2 , axis = 4))
3583/17: unique(sqrt(sum(D.FoV ** 2 , axis = 4)))
3583/18: D.nrs_epq
3583/19: D.vels
3583/20: D.vels.shape
3583/21: D.vels_fac
3583/22: -D.FoV * 500 * 1
3583/23: v = -D.FoV * 500 * 1
3583/24: v
3583/25: v.shape
3583/26: sqrt(sum(v ** 2 , axis = 4))
3583/27: D.vspace.shape
3583/28: v2 = D.vspace[:,:,2,...]
3583/29: v2.shape
3583/30: sqrt(sum(v2 ** 2 , axis = 4))
3583/31: D.space
3583/32: D.wspace.shape
3583/33:
for i in range(60):
    p1 = D.wspace[10,0,0,i,0,0,0,0]
    p2 = D.wspace[10,0,0,i,0,0,0,8]
    print('\n')
    print(i, p2-p1, p2, p1)
3583/34: D.wspace.shape
3583/35: D.wspace[10,0,0,10,0,0,0,:]
3583/36: D.wspace[10,0,0,50,0,0,0,:]
3583/37: arr = []
3583/38:
for i in range(60):
    p1 = D.wspace[10,0,0,i,0,0,0,0]
    p2 = D.wspace[10,0,0,i,0,0,0,8]
    print('\n')
    print(i, p2-p1, p2, p1)
    arr.append(p2-p1)
3583/39: print(len(arr),arr)
3583/40: plot(len(arr),arr)
3583/41: plot(range(len(arr)),arr)
3583/42: %run test_dies_das.py
3583/43: D
3583/44: %run test_dies_das.py
3583/45: test(D)
3584/1: %run load_pui_ulysses.py
3584/2: D
3584/3: %run test_dies_das.py
3584/4: test(D)
3584/5: ax = test(D)
3584/6: %run test_dies_das.py
3584/7: pylab.close('all')
3584/8: ax = test(D,0)
3584/9: ax = test(D,5)
3584/10: ax = test(D,4)
3584/11: ax = test(D,1)
3585/1: %run load_pui_ulysses.py
3585/2: %run test_dies_das.py
3585/3: %run test_dies_das.py
3585/4: test(D)
3586/1: %run load_pui_ulysses.py
3586/2: %run test_dies_das.py
3586/3: test(D)
3586/4: %run test_dies_das.py
3586/5: test(D)
3586/6: %run test_dies_das.py
3586/7: test(D)
3587/1: %run load_pui_ulysses.py
3587/2: D.plot_wspace()
3587/3: %run test_dies_das.py
3587/4: test(D)
3587/5: %run test_dies_das.py
3587/6: test(D)
3587/7: %run test_dies_das.py
3587/8: test(D)
3587/9: %run test_dies_das.py
3587/10: test(D)
3587/11: D.aspphi
3587/12: D.asptheta
3587/13: D.plot_FoV()
3587/14: D.FoV
3587/15: %run swics_collimator_ulysses.py
3587/16: c = collimator()
3587/17: c.plot_FoV()
3587/18: pylab.close('all')
3587/19: D.plot_FoV()
3587/20: %run test_dies_das.py
3587/21: %run swics_collimator_ulysses.py
3588/1: %run load_pui_ulysses.py
3589/1: %run load_pui_ulysses.py
3589/2: D.plot_wspace()
3590/1: %run load_pui_ulysses.py
3590/2: D.plot_wspace()
3591/1: D.plot_wspace()
3591/2: %run load_pui_ulysses.py
3591/3: D.plot_wspace()
3592/1: %run load_pui_ulysses.py
3592/2: D.plot_vspace()
3593/1: D.plot_vspace()
3593/2: %run load_pui_ulysses.py
3593/3: D.plot_vspace()
3594/1: D.plot_vspace()
3594/2: %run load_pui_ulysses.py
3594/3: %run load_pui_ulysses.py
3594/4: D.plot_vspace()
3595/1: %run load_pui_ulysses.py
3595/2: D.plot_vspace()
3596/1: %run load_pui_ulysses.py
3596/2: D.plot_vspace()
3597/1: %run load_pui_ulysses.py
3597/2: D.plot_vspace()
3598/1: %run load_pui_ulysses.py
3598/2: D
3598/3:
for i in range(60):
    p1 = D.wspace[10,0,0,i,0,0,0,0]
    p2 = D.wspace[10,0,0,i,0,0,0,8]
    print('\n')
    print(i, p2-p1, p2, p1)
3598/4: D.wspace.shape
3598/5: D.wspace.shape[...:]
3598/6: D.wspace.shape[...,:]
3598/7: D.wspace[...,:]
3598/8: unique(D.wspace[...,:])
3598/9: D.wspace.shape
3598/10: D.vspace
3598/11: D.vspace.shape
3598/12: v2 = D.vspace[:,:,20,...]
3598/13: sqrt(sum(v2 ** 2 , axis = 4))
3598/14: unique(sqrt(sum(v2 ** 2 , axis = 4)))
3598/15: D.vspace.shape
3598/16: D.wspace.shape
3598/17: D.wspace.shape[20,0,0,20,0,0,0,:]
3598/18: D.wspace[20,0,0,20,0,0,0,:]
3598/19: D.vswbins[20]
3598/20: D.vspace.shape
3598/21: v = sqrt(sum(D.vspace ** 2 , axis = 5))
3598/22: v.shape
3598/23: v[0,0,20,0,0,0,:]
3598/24: v = zeros(2,3,60,3,8,1,9)
3598/25: v = zeros((2,3,60,3,8,1,9))
3598/26: v[...,0,:] = sqrt(sum(D.vspace ** 2 , axis = 5))
3598/27: v.shape
3599/1: %run load_pui_ulysses.py
3599/2: sqrt(sum(D.vspace ** 2, axis = 5))
3600/1: %run load_pui_ulysses.py
3601/1: %run load_pui_ulysses.py
3601/2: D.vasbsspace
3601/3: D.vabsspace
3601/4: D.vabsspace.shape
3601/5: D.vabsspace[:,:,20,...]
3601/6: D.vspace
3601/7: D.vspace.shape
3601/8: v = sqrt(sum(D.vspace ** 2 , axis = 5))
3601/9: v =D.vabsspace[:,:,20,...]
3601/10: v
3601/11: v = sqrt(sum(D.vspace ** 2 , axis = 5))
3601/12: v2 = D.vspace[:,:,20,...]
3601/13: sqrt(sum(v2 ** 2 , axis = 4))
3602/1: %run load_pui_ulysses.py
3602/2: D.vabsspace.shape
3602/3: D.vabsspace[:,:,20,...]
3602/4: D.wspace[20,0,0,20,0,0,0,:]
3602/5: val = D.vabsspace[0,0,20,0,0,0,0]
3602/6: val
3602/7: wal = val*1.
3602/8: wal[...,0,:] -= 505.
3602/9: wal[...,0,:] -= 505
3602/10: wal[...,0,:]
3602/11: wal.shape
3602/12: val
3602/13: wal = 1.*val
3602/14: wal -= 505.
3602/15: wal
3602/16: val
3602/17: wal /= 505.
3602/18: wal
3602/19: D.wspace[20,0,0,20,0,0,0,:]
3602/20: norm_arr, H = D.calc_w3dspecs()
3602/21: norm_arr[norm_arr==0]=1
3602/22: H2 = H/norm_arr
3602/23: wbins = arange(-2,2.01,0.2)
3602/24: pcolormesh(wbins,wbins,H2[10,:,:].T)
3602/25: %run test_dies_das.py
3602/26: test
3602/27: test(D)
3603/1: %run test_dies_das.py
3603/2: %run load_pui_ulysses.py
3603/3: test(D)
3603/4: %run test_dies_das.py
3603/5: test(D)
3604/1: %run load_pui_ulysses.py
3604/2: %run test_dies_das.py
3604/3: test(D)
3604/4: %run test_dies_das.py
3604/5: test(D)
3604/6: %run test_dies_das.py
3604/7: test(D)
3604/8: pylab.close('all')
3604/9: %run test_dies_das.py
3604/10: test(D)
3604/11: %run test_dies_das.py
3604/12: test(D)
3604/13: %run test_dies_das.py
3604/14: test(D)
3604/15: pylab.close('all')
3604/16: %run test_dies_das.py
3604/17: test(D)
3604/18: %run test_dies_das.py
3604/19: test(D)
3604/20: %run test_dies_das.py
3604/21: test(D)
3605/1: %run test_dies_das.py
3605/2: test(D)
3605/3: %run load_pui_ulysses.py
3605/4: test(D)
3605/5: %run load_pui_ulysses.py
3605/6: %run test_dies_das.py
3605/7: test(D)
3606/1: test(D)
3606/2: %run test_dies_das.py
3606/3: test(D)
3606/4: %run load_pui_ulysses.py
3606/5: test(D)
3606/6: range(8)+3
3606/7: range(8)
3606/8: [3*2]
3606/9: [3]*2
3606/10: range(8) + [3] * 8
3606/11: arange
3606/12: range(8)
3606/13: %run test_dies_das.py
3606/14: test(D)
3606/15: pylab.close('all')
3606/16: %run test_dies_das.py
3606/17: test(D)
3606/18: %run test_dies_das.py
3606/19: test(D)
3607/1: %run test_dies_das.py
3607/2: %run load_pui_ulysses.py
3607/3: test(D)
3608/1: %run load_pui_ulysses.py
3608/2: %run test_dies_das.py
3608/3: test(D)
3608/4: D.plot_wspace()
3608/5: %run test_dies_das.py
3608/6: test(D)
3608/7: test2(D)
3608/8: range(5)
3608/9: anarnge(5)
3608/10: arange(5)
3608/11: %run test_dies_das.py
3608/12: test2(D)
3608/13: %run test_dies_das.py
3608/14: test2(D)
3609/1: %run test_dies_das.py
3609/2: %run test_dies_das.py
3609/3: test2(D)
3609/4: %run load_pui_ulysses.py
3609/5: test2(D)
3609/6: D.wspace.shape
3609/7: D.vsw
3609/8: D.vswbins
3609/9: D.vswbins.shape
3609/10: %run load_pui_ulysses.py
3609/11: %run test_dies_das.py
3609/12: test2(D)
3609/13: %run test_dies_das.py
3609/14: test2(D)
3609/15: pylab.close('all')
3609/16: %run test_dies_das.py
3609/17: pylab.close('all')
3609/18: test2(D)
3609/19: %run test_dies_das.py
3609/20: test2(D)
3610/1: %run test_dies_das.py
3610/2: %run load_pui_ulysses.py
3610/3: test2(D)
3610/4: %run test_dies_das.py
3610/5: test2(D)
3610/6: %run test_dies_das.py
3610/7: test2(D)
3610/8: %run test_dies_das.py
3610/9: test2(D)
3610/10: pylab.close('all')
3610/11: %run test_dies_das.py
3610/12: test2(D)
3610/13: %run test_dies_das.py
3610/14: test2(D)
3610/15: %run test_dies_das.py
3610/16: test2(D)
3610/17: test(D)
3610/18: test(D)
3610/19: %run test_dies_das.py
3610/20: test(D)
3610/21: %run test_dies_das.py
3610/22: test(D)
3610/23: %run test_dies_das.py
3610/24: test(D)
3610/25: %run test_dies_das.py
3610/26: test(D)
3611/1: %run test_dies_das.py
3611/2: %run load_pui_ulysses.py
3611/3: test(D)
3611/4: test_diff_sec(D)
3611/5: %run test_dies_das.py
3611/6: test_diff_sec(D)
3611/7: %run test_dies_das.py
3611/8: test_diff_sec(D)
3612/1: %run load_pui_ulysses.py
3612/2: %run test_dies_das.py
3612/3: test_diff_sec(D)
3612/4: %run test_dies_das.py
3612/5: test_diff_vsw(D)
3613/1: %run load_pui_ulysses.py
3613/2: %run test_dies_das.py
3613/3: test_diff_vsw(D)
3613/4: D.wspace.shape
3613/5: D.wspace[20,0,0,20,:,0,0,;]
3613/6: D.wspace[20,0,0,20,:,0,0,:]
3613/7: test_diff_sec(D)
3613/8: pylab.close('all')
3613/9: %run test_dies_das.py
3613/10: test_diff_sec(D)
3613/11: %run test_dies_das.py
3613/12: test_diff_sec(D)
3613/13: %run test_dies_das.py
3614/1: %run load_pui_ulysses.py
3615/1: %run load_pui_ulysses.py
3615/2: D.plot_wspace()
3615/3: D.wspace.shape
3615/4: %run dist3D_pui_ulysses.py
3615/5: DD = Dis3D(d)
3615/6: DD = Dist3D(d)
3616/1: %run load_pui_ulysses.py
3616/2: D.wspace.shape
3617/1: %run load_pui_ulysses.py
3617/2: wbins = arange(-2,2.01,0.2)
3617/3: norm_arr, H = D.calc_w3dspecs()
3617/4: norm_arr[norm_arr==0]=1
3617/5: histogram(norm_arr)
3617/6: plt.plot(histogram(norm_arr))
3617/7: plt.hist(norm_arr)
3617/8: norm_arr
3617/9: norm_arr.shape
3617/10: plt.hist(norm_arr.flatten())
3617/11: plt.hist(norm_arr.flatten(),bins =range(0,40000,100))
3617/12: pylab.close('all')
3617/13: plt.hist(norm_arr.flatten(),bins =range(0,40000,100))
3617/14: pcolormesh(wbins,wbins,norm_arr)
3617/15: pcolormesh(wbins,wbins,norm_arr[0,:,:])
3617/16: pylab.close('all')
3617/17: pcolormesh(wbins,wbins,norm_arr[0,:,:])
3617/18: pcolormesh(wbins,wbins,norm_arr[10,:,:])
3617/19: pcolormesh(wbins,wbins,norm_arr[:,10,:])
3617/20: pcolormesh(wbins,wbins,norm_arr[:,10,:].T)
3617/21: pcolormesh(wbins,wbins,norm_arr[:,:,10].T)
3617/22: pcolormesh(wbins,wbins,norm_arr[:,:,10])
3617/23: wbins = arange(-2,2.01,0.2)
3617/24: H2 = H/norm_arr
3617/25: ax = pcolormesh(wbins,wbins,H2[10,:,:].T)
3617/26: ax = pcolormesh(wbins,wbins,H2[11,:,:].T)
3617/27: ax = pcolormesh(wbins,wbins,H2[12,:,:].T)
3617/28: ax = pcolormesh(wbins,wbins,H2[13,:,:].T)
3617/29: ax = pcolormesh(wbins,wbins,H2[14,:,:].T)
3617/30: ax = pcolormesh(wbins,wbins,H2[15,:,:].T)
3617/31: ax = pcolormesh(wbins,wbins,H2[16,:,:].T)
3617/32: ax = pcolormesh(wbins,wbins,H2[:,11,:].T)
3617/33: ax = pcolormesh(wbins,wbins,H2[:,12,:].T)
3617/34: ax = pcolormesh(wbins,wbins,H2[:,13,:].T)
3617/35: ax = pcolormesh(wbins,wbins,H2[:,14,:].T)
3617/36: ax = pcolormesh(wbins,wbins,H2[:,9,:].T)
3617/37: ax = pcolormesh(wbins,wbins,H2[11,:,:]))
3617/38: ax = pcolormesh(wbins,wbins,H2[11,:,:])
3617/39: ax = pcolormesh(wbins,wbins,H2[12,:,:])
3617/40: ax = pcolormesh(wbins,wbins,H2[14,:,:])
3617/41: ax = pcolormesh(wbins,wbins,H2[13,:,:])
3617/42: DD = Dist3D(d,offset_sp = 10.)
3617/43: norm_arr, H = DD.calc_w3dspecs()
3617/44: norm_arr[norm_arr==0]=1
3617/45: H2 = H/norm_arr
3617/46: ax2 = pcolormesh(wbins,wbins,H2[13,:,:])
3617/47: ax2 = pcolormesh(wbins,wbins,H2[11,:,:])
3617/48: ax2 = pcolormesh(wbins,wbins,H2[12,:,:])
3617/49: ax2 = pcolormesh(wbins,wbins,H2[9,:,:])
3617/50: ax2 = pcolormesh(wbins,wbins,H2[7,:,:])
3617/51: fig = plt.figure()
3617/52: ax = fig.add_subplot(111)
3617/53: norm_arr, H = D.calc_w3dspecs()
3617/54: norm_arr[norm_arr==0]=1
3617/55: H2 = H/norm_arr
3617/56: pcolormesh(ax=ax, wbins,wbins,norm_arr[:,:,10])
3617/57: pcolormesh(wbins,wbins,norm_arr[:,:,10])
3617/58: pcolormesh(wbins,wbins,norm_arr[10,:,:])
3617/59: ax2 = pcolormesh(wbins,wbins,H2[10,:,:])
3617/60: pcolormesh(wbins,wbins,norm_arr[10,:,:])
3617/61: ax.pcolormesh(wbins,wbins,H2[10,:,:])
3617/62: pylab.close('all')
3617/63: norm_arr_1, H_1 = D.calc_w3dspecs()
3617/64: norm_arr_2, H_2 = DD.calc_w3dspecs()
3617/65: norm_arr_2[norm_arr_2==0]=1
3617/66: norm_arr_1[norm_arr_1==0]=1
3617/67: H2 = H_2/norm_arr_2
3617/68: H1 = H_1/norm_arr_1
3617/69: ax2 = pcolormesh(wbins,wbins,H2[10,:,:])
3617/70: ax1 = pcolormesh(wbins,wbins,H1[10,:,:])
3617/71: ax2 = pcolormesh(wbins,wbins,H2[10,:,:])
3617/72: ax1 = pcolormesh(wbins,wbins,H1[10,:,:])
3617/73: ax2 = figure.axis
3617/74: ax2 = plt.figure().add_subplot(111)
3617/75: ax2.pcolormesh(wbins,wbins,H2[10,:,:])
3617/76: ax1.pcolormesh(wbins,wbins,H1[10,:,:])
3617/77: ax1 = plt.figure().add_subplot(111)
3617/78: ax1.pcolormesh(wbins,wbins,H1[10,:,:])
3617/79: ax2.pcolormesh(wbins,wbins,H2[10,:,:])
3617/80: ax1.pcolormesh(wbins,wbins,H1[10,:,:])
3617/81: ax1.pcolormesh(wbins,wbins,H1[9,:,:])
3617/82: ax2.pcolormesh(wbins,wbins,H2[9,:,:])
3617/83: ax2.pcolormesh(wbins,wbins,H2[8,:,:])
3617/84: plt.show()
3617/85: pcolormesh(wbins,wbins,H2[8,:,:])
3617/86: pylab.close('all')
3617/87: pcolormesh(wbins,wbins,H2[8,:,:])
3617/88: pcolormesh(wbins,wbins,H1[8,:,:])
3617/89: pcolormesh(wbins,wbins,H1[10,:,:])
3617/90: pcolormesh(wbins,wbins,H1[12,:,:])
3617/91: pcolormesh(wbins,wbins,H2[12,:,:])
3617/92: pcolormesh(wbins,wbins,H2[13,:,:])
3617/93: pcolormesh(wbins,wbins,H1[13,:,:])
3617/94: pcolormesh(wbins,wbins,H1[14,:,:])
3617/95: pcolormesh(wbins,wbins,H2[14,:,:])
3617/96: fig,ax = plt.subplots()
3617/97: ax1.pcolormesh(wbins,wbins,H1[8,:,:])
3617/98: ax.pcolormesh(wbins,wbins,H1[8,:,:])
3617/99: fig,ax = plt.subplots()
3617/100: ax.pcolormesh(wbins,wbins,H2[8,:,:])
3617/101: fig, (a,b) = plt.subplots(1,2)
3617/102: a.pcolormesh(wbins,wbins,H1[14,:,:])
3617/103: b.pcolormesh(wbins,wbins,H2[14,:,:])
3617/104: b.pcolormesh(wbins,wbins,H2[13,:,:])
3617/105: b.pcolormesh(wbins,wbins,H2[12,:,:])
3617/106: a.pcolormesh(wbins,wbins,H1[12,:,:])
3617/107: a.pcolormesh(wbins,wbins,H1[10,:,:])
3617/108: b.pcolormesh(wbins,wbins,H2[10,:,:])
3617/109: D.plot_wspace()
3617/110: D.wspace
3617/111: unique(D.wspace)
3617/112: unique(D.w3dspace)
3617/113: DD.plot_wspace()
3617/114: D.plot_vspace()
3617/115: %run dist3D_pui_ulysses.py
3617/116: DD = Dis3D(d)
3617/117: DD = Dist3D(d)
3617/118: DD.plot_wspace()
3617/119: %run dist3D_pui_ulysses.py
3617/120: DD = Dist3D(d)
3617/121: DD.plot_wspace()
3617/122: pylab.close('all')
3618/1: %run swics_collimator_ulysses.py
3619/1: %run swics_collimator_ulysses.py
3619/2: c = collimator()
3619/3: c.test_plot()
3619/4: %run swics_collimator_ulysses.py
3619/5: c = collimator()
3619/6: c.test_plot()
3619/7: %run swics_collimator_ulysses.py
3619/8: c = collimator()
3619/9: c.test_plot()
3619/10: c.test_plot()
3619/11: %run swics_collimator_ulysses.py
3619/12: c = collimator()
3619/13: c.test_plot()
3619/14: %run swics_collimator_ulysses.py
3619/15: c = collimator()
3619/16: c.test_plot()
3619/17: %run swics_collimator_ulysses.py
3619/18: c = collimator()
3619/19: c.test_plot()
3619/20: c = collimator(aspphi = 30)
3619/21: c.test_plot()
3619/22: %run swics_collimator_ulysses.py
3619/23: c = collimator(aspphi = 30)
3619/24: c.test_plot()
3619/25: c = collimator(aspphi = -30)
3619/26: c.test_plot()
3619/27: %run swics_collimator_ulysses.py
3619/28: c = collimator(aspphi = -30)
3619/29: c.test_plot()
3619/30: c = collimator(aspphi = -30, offset_sp = 90.)
3619/31: c.test_plot()
3619/32: c = collimator(aspphi = -30, offset_sp = -90.)
3619/33: c.test_plot()
3619/34: pylab.close('all')
3619/35: c = collimator(aspphi = -30, offset_sp = 10)
3619/36: c.test_plot()
3620/1: %run load_pui_ulysses.py
3620/2: %run load_pui_ulysses.py
3621/1: %run load_pui_ulysses.py
3621/2: d.data
3621/3: d.data.keys
3621/4: d.data.keys()
3621/5: d.data['aspphi']
3621/6: unique(d.data['aspphi'])
3621/7: unique(d.data['asptheta'])
3621/8: cc1 = collimator(aspphi = 14, asptheta = 5, offset_sp = 135.)
3621/9: from swics_collimator_ulysses import collimator
3621/10: cc1 = collimator(aspphi = 14, asptheta = 5, offset_sp = 135.)
3621/11: cc1.test_plot()
3621/12: cc2 = collimator(aspphi = 14, asptheta = 5, offset_sp = 10.)
3621/13: cc2.test_plot()
3621/14: D1 = Dist3D(d)
3621/15: D2 = Dist3D(d,offset_sp=10.)
3621/16: %run dist3D_pui_ulysses.py
3621/17: %run dist3D_pui_ulysses.py
3621/18: D1.plot_wspec()
3622/1: D1.plot_wspec()
3622/2: %run load_pui_ulysses.py
3622/3: D1 = Dist3D(d)
3622/4: D2 = Dist3D(d,offset_sp=10.)
3622/5: D1.plot_wspec()
3622/6: %run load_pui_ulysses.py
3622/7: D1 = Dist3D(d)
3622/8: D1.plot_wspec()
3623/1: %run load_pui_ulysses.py
3623/2: D1 = Dist3D(d)
3623/3: D1.plot_wspec()
3624/1: %run load_pui_ulysses.py
3624/2: D1 = Dist3D(d)
3624/3: D1.plot_wspec()
3625/1: %run load_pui_ulysses.py
3625/2: D1 = Dist3D(d)
3625/3: D1.plot_wspec()
3625/4: D2 = Dist3D(d,offset_sp=10.)
3625/5: D2.plot_wspec()
3626/1: %run load_pui_ulysses.py
3626/2: %run load_pui_ulysses.py
3626/3: D2 = Dist3D(d,offset_sp=10.)
3626/4: D2.plot_wspec()
3626/5: D1 = Dist3D(d)
3626/6: D1.plot_wspec()
3626/7: D1.plot_wspec(cut_x = 11)
3627/1: %run load_pui_ulysses.py
3627/2: D1 = Dist3D(d)
3627/3: D1.plot_wspec(cut_x = 11)
3628/1: %run load_pui_ulysses.py
3628/2: D1 = Dist3D(d)
3628/3: D1.plot_wspec(cut_x = 11)
3629/1: %run load_pui_ulysses.py
3629/2: D1 = Dist3D(d)
3629/3: D1.plot_wspec(cut_x = 11)
3629/4: pcolormesh(wbins,wbins,H2[11,:,:])
3629/5: wbins = arange(-2,2.01,0.2)
3629/6: pcolormesh(wbins,wbins,H2[11,:,:])
3629/7: norm_arr_1, H_1 = D.calc_w3dspecs()
3629/8: norm_arr_1[norm_arr_1==0]=1
3629/9: pcolormesh(wbins,wbins,H2[11,:,:])
3629/10: pcolormesh(wbins,wbins,H_1[11,:,:])
3630/1: %run load_pui_ulysses.py
3630/2: D
3630/3: D.plot_wspec()
3630/4: D.plot_wspec_fancy()
3630/5: %run load_pui_ulysses.py
3630/6: D.plot_wspec_fancy()
3630/7: D.plot_wspec()
3631/1: %run load_pui_ulysses.py
3631/2: D.plot_wspec()
3631/3: D.plot_wspec_fancy()
3632/1: D.plot_wspec()
3632/2: %run load_pui_ulysses.py
3632/3: D.plot_wspec()
3632/4: D.plot_wspec(cut_x = 11)
3632/5: D.plot_wspec(cut_x = 12)
3633/1: %run load_pui_ulysses.py
3633/2: D.plot_wspec()
3633/3: D.plot_wspec(cut_x = 11)
3633/4: D1 = Dist3D(d, offset_sp= 10.)
3633/5: D1.plot_wspec(cut_x = 11)
3633/6: D1 = Dist3D(d, offset_sp= 45)
3633/7: D1.plot_wspec(cut_x = 11)
3633/8: D.plot_wspec(cut_x = 11)
3633/9: D.offset_sp
3633/10: D1.offset_sp
3633/11: D1 = Dist3D(d, offset_sp= 45.)
3633/12: D1.offset_sp
3633/13: D.plot_wspec(cut_x = 11)
3633/14: pylab.close('all')
3633/15: D.plot_wspec(cut_x = 11)
3633/16: D1.plot_wspec(cut_x = 11)
3633/17: from swics_collimator_ulysses import collimator
3633/18: cc1 = collimator(aspphi = 14, asptheta = 5, offset_sp = 135.)
3633/19: cc2 = collimator(aspphi = 14, asptheta = 5, offset_sp = 45.)
3633/20: cc1.test_plot()
3633/21: cc2.test_plot()
3634/1: %run load_pui_ulysses.py
3634/2: D.plot_wspec(cut_x = 11)
3634/3: D1 = Dist3D(d, offset_sp= 45.)
3634/4: D1.plot_wspec(cut_x = 11)
3634/5: D1 = Dist3D(d, offset_sp= 5.)
3634/6: D1.plot_wspec(cut_x = 11)
3634/7: D1 = Dist3D(d, offset_sp= 45.)
3634/8: D1.plot_wspec(cut_x = 6)
3634/9: D.plot_wspec(cut_x = 6)
3634/10: pylab.close('all')
3634/11: D.plot_wspec(cut_x = 6)
3634/12: D1.plot_wspec(cut_x = 6)
3634/13: D1.offset_sp
3634/14: D.offset_sp
3635/1: %run load_pui_ulysses.py
3635/2: D.plot_wspec(cut_x = 6)
3635/3: D1 = Dist3D(d, offset_sp= 45.)
3635/4: D1.plot_wspec(cut_x = 6)
3635/5: D1.plot_wspace()
3635/6: D.plot_wspace()
3635/7: D1.wspace.shape
3635/8: D1.vspace[0,0,20,0,5,0,0]
3635/9: D.vspace[0,0,20,0,7,0,0]
3635/10: D.vspace[0,0,20,0,3,0,0]
3635/11: D.wspace[20,0,0,20,4,0,0,0]
3635/12: D.wspace[20,0,0,20,2,4,0,0]
3635/13: D1.wspace[20,0,0,20,2,6,0,0]
3635/14: D1.wspace[20,0,0,20,2,6,2,2]
3635/15: D.d.data
3635/16: D.d.data['year']
3635/17: D.d.data['year'].shape
3635/18: D.d.data['sec']
3635/19: D.d.data['sec'][:10]
3635/20: D.d.data[:10]
3635/21: D.d.data
3635/22: D.d.data['sec'][:10]
3635/23: D.d.data[wsw]
3635/24: D.d.data['wsw']
3635/25: D.d.data['wsw'].shape
3635/26: D.d.data['wsw'][0:10,:]
3635/27: D.d.data['sec'][:10]
3635/28: D1.d.data['wsw'][0:10,:]
3635/29: D1.d.data['sec'][:10]
3635/30: D1.offset_sp
3635/31: D.offset_sp
3635/32: D1.d.data['vx'][:10]
3635/33: D1.d.data['vx'].shape
3636/1: %run load_pui_ulysses.py
3636/2: D= Dist3D(d)
3636/3: D1 = Dist3D(d, offset_sp= 45.)
3636/4: D.plot_wspec(cut_x = 6)
3636/5: D.plot_wspec(cut_x = 6)
3636/6: D.plot_wspec(cut_x = 6)
3637/1: %run load_pui_ulysses.py
3637/2: D.plot_wspec(cut_x = 6)
3637/3: D1 = Dist3D(d, offset_sp= 45.)
3637/4: D1.plot_wspec(cut_x = 6)
3638/1: %run load_pui_ulysses.py
3638/2: D.plot_wspec(cut_x = 6)
3638/3: D = Dist3D()
3638/4: D = Dist3D(d)
3638/5: D.plot_wspec(cut_x = 6)
3638/6: D1 = Dist3D(d, offset_sp= 45.)
3638/7: D1.plot_wspec(cut_x = 6)
3638/8: D.plot_wspec(cut_x = 6)
3638/9: D = Dist3D(d)
3638/10: D.plot_wspec(cut_x = 6)
3638/11: D.d.data['sec'][:10]
3638/12: D.d.data['vx'][:10]
3638/13: D1.d.data['sec'][:10]
3638/14: D1.d.data['vx'][:10]
3639/1: %run load_pui_ulysses.py
3640/1: %run load_pui_ulysses.py
3639/2: D1 = Dist3D(d, offset_sp= 45.)
3639/3: D1.plot_wspec(cut_x = 6)
3640/2: D.plot_wspec(cut_x = 6)
3639/4: D.vspace[0,0,20,0,3,0,0]
3639/5: D1.vspace[0,0,20,0,5,0,0]
3640/3: D.vspace[0,0,20,0,5,0,0]
3640/4: D.vspace[0,0,20,0,3,0,0]
3640/5: D.vspace.shape
3640/6: D.vspace[0,0,20,0,2,0]
3639/6: D1.vspace[0,0,20,0,2,0,0]
3639/7: D1.vspace[0,0,20,0,2,0]
3639/8: D1.d.data['vx'][:5]
3640/7: D.d.data['vx'][:5]
3640/8: sum(D.d.data['vx'][:5])
3639/9: sum(D1.d.data['vx'][:5])
3639/10: D1.d.data['sec'][:5]
3641/1: %run load_pui_ulysses.py
3641/2: d
3641/3: d.data
3642/1: %run load_pui_ulysses.py
3642/2: d.data
3643/1: %run load_pui_ulysses.py
3643/2: d.data
3644/1: %run load_pui_ulysses.py
3645/1: %run load_pui_ulysses.py
3645/2: d.data
3646/1: %run load_pui_ulysses.py
3647/1: %run load_pui_ulysses.py
3648/1: %run load_pui_ulysses.py
3649/1: %run load_pui_ulysses.py
3649/2:
for i in range(20):
    print(D.d.data['det'][i])
3650/1: %run load_pui_ulysses.py
3650/2: D.plot_wspec(cut_x = 10)
3650/3: D1 = Dist3D(d, offset_sp= 45.)
3650/4: D1.plot_wspec(cut_x = 10)
3651/1: %run load_pui_ulysses.py
3651/2: D.plot_wspec(cut_x = 10)
3652/1: %run load_pui_ulysses.py
3652/2: %run dist3D_pui_ulysses.py
3652/3: D = Dist3D(d)
3652/4: D.plot_wspec(cut_x = 10)
3652/5: %run dist3D_pui_ulysses.py
3652/6: D = Dist3D(d)
3652/7: D.plot_wspec(cut_x = 10)
3652/8: %run dist3D_pui_ulysses.py
3652/9: D = Dist3D(d)
3652/10: D.plot_wspec(cut_x = 10)
3652/11: %run dist3D_pui_ulysses.py
3652/12: D = Dist3D(d)
3652/13: D.plot_wspec(cut_x = 10)
3652/14: %run dist3D_pui_ulysses.py
3652/15: D = Dist3D(d)
3652/16: D.plot_wspec(cut_x = 10)
3653/1: %run load_pui_ulysses.py
3653/2: %run dist3D_pui_ulysses.py
3653/3: D1 = Dist3D(d)
3653/4: %run dist3D_pui_ulysses.py
3653/5: D1 = Dist3D(d)
3654/1: %run load_pui_ulysses.py
3654/2: D.plot_wspec(cut_x = 10)
3654/3: D1 = Dist3D(d, offset_sp=45)
3654/4: D1.plot_wspec(cut_x = 10)
3654/5: from swics_collimator_ulysses import collimator
3654/6: c = collimator(aspphi = -30, offset_sp = 10)
3654/7: c.test_plot()
3654/8: D.plot_wspace()
3654/9: D1.plot_wspace()
3654/10: D1.plot_wspace(aspphi = 10)
3654/11: D1.plot_wspace(aspphi = 100)
3654/12: D1.plot_wspace(aspphi = 35)
3654/13: %run dist3D_pui_ulysses.py
3654/14: D = Dist3D(d)
3654/15: D.plot_wspec(cut_x = 10)
3654/16: pylab.close('all')
3654/17: D.plot_wspec(cut_x = 10)
3654/18: d.show_mask()
3654/19: D.d.show_mask()
3654/20: D.d.data.keys()
3654/21: d.data['year'].shape
3654/22: d.set_mask("He1+", "wHe1+2", min_whe, 10., reset=True)
3654/23: d.set_mask("He1+", "wHe1+2", 0.9,  10., reset=True)
3654/24: d.data['year'].shape
3654/25: d.set_mask("Master", "wHe1+2", 0.9,  10., reset=True)
3654/26: d.data['year'].shape
3654/27: d.hist1d('wHe1+2')
3654/28: d.data['wHe1+2']
3654/29: unique(d.data['wHe1+2'])
3654/30: D.d.data['year'].shape
3654/31: d.data['year'].shape
3654/32: d.set_mask("Master", "wHe1+2", 1., 10., reset=True)
3654/33: d.data['year'].shape
3654/34: d.get_data('Master','year')
3654/35: d.get_data('Master','year').shape
3654/36: D.d.get_data('Master','year').shape
3655/1: %run load_pui_ulysses.py
3655/2: D
3655/3: D.plot_wspec(cut_x = 10)
3656/1: %run load_pui_ulysses.py
3656/2: D.plot_wspec(cut_x = 10)
3655/4: D.d.get_data('Master','year').shape
3655/5: D.d.get_data('He1+','year').shape
3656/3: D.d.get_data('He1+','year').shape
3657/1: D.d.get_data('He1+','year').shape
3657/2: %run load_pui_ulysses.py
3657/3: D.plot_wspec(cut_x = 10)
3657/4: D.d.get_data('He1+','year').shape
3658/1: %run load_pui_ulysses.py
3658/2: D.plot_wspec(cut_x = 10)
3658/3: D.d.get_data('He1+','year').shape
3659/1: %run load_pui_ulysses.py
3659/2: D.plot_wspec(cut_x = 10)
3659/3: D.plot_wspec(cut_x = 10)
3659/4: pylab.close('all')
3659/5: D.plot_wspec(cut_x = 10)
3658/4: D.plot_wspec(cut_x = 10)
3659/6: D.d.get_data('He1+','year').shape
3658/5: D.d.get_data('He1+','year').shape
3658/6: D.plot_wspec(cut_x = 10)
3662/1: %run load_pui_ulysses.py
3662/2: D.plot_wspec(cut_x = 10)
3663/1: %run load_pui_ulysses.py
3663/2: D.d.get_data('He1+','year').shape
3663/3: D.d.set_mask("He1+", "wHe1+2", 0., 10., reset=True)
3663/4: D.d.get_data('He1+','year').shape
3663/5: D.plot_wspec(cut_x = 10)
3663/6: D.d.get_data('He1+','year').shape
3662/3: D.d.get_data('He1+','year').shape
3662/4: H
3664/1: %run load_pui_ulysses.py
3664/2: D.plot_wspec(cut_x = 10)
3665/1: %run load_pui_ulysses.py
3665/2: D.plot_wspec(cut_x = 10)
3665/3: D.d.get_data('He1+','year').shape
3664/3: D.d.get_data('He1+','year').shape
3666/1: %run load_pui_ulysses.py
3666/2: D.plot_wspec(cut_x = 10)
3667/1: pylab.close('all')
3667/2: %run load_pui_ulysses.py
3667/3: D.plot_wspec(cut_x = 10)
3667/4: D.Quadmesh
3667/5: D.Quadmesh.shape
3667/6: D.Quadmesh.get_array
3667/7: D.Quadmesh.get_array()
3667/8: D.Quadmesh.ZData
3667/9: D.Quadmesh.CData
3667/10: D.Quadmesh.contains()
3667/11: D.Quadmesh.get_array().shape
3667/12: 20*20
3667/13: D.Quadmesh.get_array()
3668/1: %run load_pui_ulysses.py
3668/2: D.Quadmesh.get_array()
3668/3: D.plot_wspec(cut_x = 10)
3668/4: D.Quadmesh.get_array()
3668/5: D.d.get_data('He1+','year').shape
3667/14: D.d.get_data('He1+','year').shape
3667/15: D.d.get_data('Master','wHe1+2')
3667/16: D.d.get_data('Master','wHe1+')
3667/17: D.d.get_data('Master','wHe1+1')
3667/18: d.data
3667/19: d.data.keys()
3667/20: D.d.get_data('Master','wHe+')
3667/21: D.d.get_data('Master','wHe1+2')
3669/1: %run load_pui_ulysses.py
3670/1: %run load_pui_ulysses.py
3670/2: norm1, H1 = D.calc_w3dspecs()
3670/3: H1
3670/4: H1.shape
3670/5: H1[H1!=0.]
3670/6: H1[H1!=0.].shape
3670/7: H1[10,10,10]
3670/8: H1[10,:,:]
3670/9: norm2, H2 = D.calc_w3dspecs(min_whe = 0.1)
3670/10: H2
3670/11: H1[10,:,:]
3670/12: H1[10,10,:]
3670/13: H2[10,10,:]
3670/14: H2[16,10,:]
3670/15: H1[16,10,:]
3670/16: D.d.set_mask('H','wHe1+2',1,10,reset=True)
3670/17: wx = D.d.get_data('H','wxsw2')
3670/18: wx
3670/19: D.d.remove_submask('H','wHe1+2")
3670/20: D.d.remove_submask('H','wHe1+2')
3670/21: D.d.set_mask('H','wHe1+2',.1,10,reset=True)
3670/22: wx = D.d.get_data('H','wxsw2')
3670/23: wx
3670/24: clear
3670/25: D.d.remove_submask('H','wHe1+2')
3670/26: D.d.show_mask()
3670/27: D.d.set_mask('H','wHe1+2',1,10,reset=True)
3670/28: D.d.show_mask()
3670/29: D.d.get_data('H','year').shape
3670/30: D.d.remove_submask('H','wHe1+2')
3670/31: D.d.show_mask()
3670/32: D.d.set_mask('H','wHe1+2',.1,10,reset=True)
3670/33: D.d.get_data('H','year').shape
3670/34: D.d.get_data('H','wxsw2').shape
3670/35: D.d.remove_submask('H','wHe1+2')
3670/36: D.d.set_mask('H','wHe1+2',1,10,reset=True)
3670/37: D.d.show_mask()
3670/38: D.d.get_data('H','wxsw2').shape
3670/39: D.d.get_data('H','wxsw2')
3670/40: A = D.d.get_data('H','wxsw2')
3670/41: D.d.remove_submask('H','wHe1+2')
3670/42: D.d.set_mask('H','wHe1+2',.1,10,reset=True)
3670/43: D.d.show_mask()
3670/44: B = D.d.get_data('H','wxsw2')
3670/45: A
3670/46: B
3670/47: B-shape
3670/48: B.shape
3670/49: clear
3670/50: norm1, H1 = D.calc_w3dspecs()
3670/51: norm2, H2 = D.calc_w3dspecs(min_whe = 0.1)
3670/52: H1
3670/53: H1-H2
3670/54: unique(H1-H2)
3670/55: H1.shape
3670/56: H1[H1!=0.].shape
3670/57: H2[H2!=0.].shape
3670/58: norm1[norm1!=0].shape
3670/59: norm2[norm2!=0].shape
3671/1: %run load_pui_ulysses.py
3672/1: %run load_pui_ulysses.py
3672/2: D.plot_wspec()
3673/1: D.plot_wspec()
3673/2: %run load_pui_ulysses.py
3673/3: D.plot_wspec()
3674/1: %run load_pui_ulysses.py
3674/2: D.plot_wspec()
3674/3: D.plot_wspec(dim='y',slice=10)
3674/4: D.plot_wspec(dim='y',slice=10,min_wHe = 0.1)
3674/5: D.plot_wspec(dim='y',slice=10,min_wHe = 1.2)
3674/6: pylab.close('all')
3675/1: %run load_pui_ulysses.py
3675/2: d.remove_submask('all')
3675/3: d.reset_mask('all')
3675/4: d.show_mask()
3675/5: unique(d.get_data['epq'])
3675/6: unique(d.get_data('epq'))
3675/7: unique(d.get_data('Master','epq'))
3675/8: unique(d.get_data('Master','epq')).shape
3676/1: %run load_pui_ulysses.py
3677/1: %run load_pui_ulysses.py
3677/2: d.get_data('Master','epq')
3677/3: unique(d.get_data('Master','epq'))
3677/4: epq_arr = array([ 60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056, 34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249, 19.18507355, 17.85605316, 16.6190989, 15.46783299, 14.39631949, 13.39903366, 12.47083347, 11.60693312, 10.80287831, 10.05452332, 9.35800963, 8.709746, 8.10638996, 7.54483061, 7.02217253, 6.53572089, 6.08296755, 5.66157808, 5.26937981, 4.90435056, 4.56460821, 4.24840107, 3.95409875, 3.68018383, 3.42524401, 3.1879648, 2.96712279, 2.76157931, 2.57027459, 2.39222225, 2.22650424, 2.07226613, 1.92871266, 1.79510366, 1.67075025, 1.55501125, 1.44728992, 1.34703084, 1.25371708, 1.1668675, 1.08603431, 1.01080073, 0.94077886, 0.87560766, 0.81495111, 0.75849646, 0.70595263, 0.6570487 ])
3677/5: epq_arr.shape
3679/1: %run load_pui_ulysses.py
3680/1: %run load_pui_ulysses.py
3680/2: epq_arr = array([ 60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056, 34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249, 19.18507355, 17.85605316, 16.6190989, 15.46783299, 14.39631949, 13.39903366, 12.47083347, 11.60693312, 10.80287831, 10.05452332, 9.35800963, 8.709746, 8.10638996, 7.54483061, 7.02217253, 6.53572089, 6.08296755, 5.66157808, 5.26937981, 4.90435056, 4.56460821, 4.24840107, 3.95409875, 3.68018383, 3.42524401, 3.1879648, 2.96712279, 2.76157931, 2.57027459, 2.39222225, 2.22650424, 2.07226613, 1.92871266, 1.79510366, 1.67075025, 1.55501125, 1.44728992, 1.34703084, 1.25371708, 1.1668675, 1.08603431, 1.01080073, 0.94077886, 0.87560766, 0.81495111, 0.75849646, 0.70595263, 0.6570487 ])
3680/3: plot(epq_arr)
3680/4: plot(log(epq_arr))
3680/5: a =epq_arr[0]
3680/6: a
3680/7: b =epq_arr[1]
3680/8: b*1.07
3680/9: b*1.0744
3680/10: D.nrs_epq
3680/11: D.nrs_epq = 3
3680/12: linspace(0.985 + 0.015 / D.nrs_epq, 1.015 - 0.015 / D.nrs_epq, D.nrs_epq)
3680/13: D.nrs_epq = 1
3680/14: linspace(0.985 + 0.015 / D.nrs_epq, 1.015 - 0.015 / D.nrs_epq, D.nrs_epq)
3680/15: 1. - 0.025
3681/1: %run test_dies_das.py
3682/1: %run test_dies_das.py
3682/2: plt.show()
3682/3: ax
3682/4: test = ax.plot(1)
3682/5: test.get_xdata()
3683/1: %run test_dies_das.py
3683/2: test_event_handle()
3684/1: %run load_pui_ulysses.py
3684/2: WS = WSpec(D)
3684/3: from WSpec import WSpec
3684/4: WS = WSpec(D)
3684/5: WS.plot_wspec()
3685/1: %run load_pui_ulysses.py
3685/2: D.calc_w3dspecs()
3685/3: from WSpec import WSpec
3685/4: WS = WSpec(D)
3685/5: WS.plot_wspec()
3686/1: %run load_pui_ulysses.py
3686/2: ws.plot_wspec()
3687/1: %run load_pui_ulysses.py
3687/2: ws.plot_wspec()
3688/1: ws.plot_wspec()
3688/2: %run load_pui_ulysses.py
3689/1: %run load_pui_ulysses.py
3689/2: ws.plot()
3689/3: ws.update_plot(dir='+')
3690/1: %run load_pui_ulysses.py
3690/2: ws.plot()
3690/3: ws.plot()
3691/1: %run load_pui_ulysses.py
3691/2: ws.plot()
3691/3: ws.update_plot(dir='+')
3692/1: %run load_pui_ulysses.py
3692/2: ws.plot()
3692/3: ws.update_plot(dir='+')
3692/4: ws.update_plot(dir='+')
3693/1: %run load_pui_ulysses.py
3693/2: ws.plot()
3693/3: ws.update_plot(dir='+')
3694/1: %run load_pui_ulysses.py
3694/2: ws.plot()
3694/3: ws.update_plot(dir='+')
3695/1: %run load_pui_ulysses.py
3695/2: ws.plot()
3696/1: %run load_pui_ulysses.py
3696/2: ws.plot()
3696/3: ws.init_plot()
3697/1: %run load_pui_ulysses.py
3697/2: ws.init_plot()
3698/1: %run load_pui_ulysses.py
3698/2: ws.init_plot()
3698/3: ws.update_plot()
3698/4: ws.update_plot('-')
3699/1: %run load_pui_ulysses.py
3699/2: ws.init_plot()
3699/3: ws.update_plot('-')
3699/4: ws.update_plot('-')
3699/5: ws.update_plot('-')
3699/6: ws.update_plot('-')
3699/7: ws.update_plot('+')
3699/8: ws.update_plot('+')
3699/9: ws.update_plot('+')
3699/10: ws.update_plot('+')
3699/11: ws.update_plot('+')
3699/12: ws.update_plot('+')
3699/13: ws.update_plot('+')
3699/14: ws.update_plot('+')
3699/15: ws.update_plot('+')
3699/16: ws.slice
3700/1: %run load_pui_ulysses.py
3700/2: ws.init_plot()
3700/3: ws.slice
3700/4: ws.update_plot('-')
3700/5: ws.update_plot('-')
3700/6: ws.update_plot('-')
3700/7: ws.update_plot('-')
3700/8: ws.update_plot('-')
3700/9: ws.update_plot('-')
3700/10: ws.update_plot('+')
3700/11: ws.update_plot('+')
3700/12: ws.update_plot('+')
3700/13: ws.update_plot('+')
3700/14: ws.update_plot('+')
3700/15: ws.rot_plot()
3700/16: ws.rot_plot()
3700/17: ws.rot_plot()
3700/18: ws.rot_plot()
3700/19: ws.rot_plot()
3701/1: %run load_pui_ulysses.py
3701/2: ws.init_plot()
3701/3: ws.update_plot('-')
3701/4: ws.update_plot('-')
3701/5: ws.rot_plot()
3701/6: ws.dim
3701/7: ws.rot_plot()
3701/8: ws.dim
3702/1: %run load_pui_ulysses.py
3702/2: ws.init_plot()
3702/3: ws.update_plot('-')
3702/4: ws.rot_plot()
3703/1: %run load_pui_ulysses.py
3703/2: ws.init_plot()
3703/3: ws.update_plot('-')
3703/4: ws.update_plot('-')
3703/5: ws.rot_plot()
3703/6: ws.rot_plot()
3703/7: ws.rot_plot()
3703/8: ws.rot_plot()
3703/9: ws.rot_plot()
3703/10: ws.rot_plot()
3703/11: ws.rot_plot()
3703/12: ws.rot_plot()
3703/13: ws.rot_plot()
3704/1: %run load_pui_ulysses.py
3704/2: ws.init_plot()
3705/1: %run load_pui_ulysses.py
3705/2: ws.init_plot()
3706/1: %run load_pui_ulysses.py
3706/2: ws.init_plot()
3707/1: %run load_pui_ulysses.py
3708/1: %run load_pui_ulysses.py
3708/2: ws.init_plot()
3709/1: %run load_pui_ulysses.py
3709/2: ws.init_plot()
3710/1: %run load_pui_ulysses.py
3710/2: ws.init_plot()
3711/1: %run load_pui_ulysses.py
3711/2: ws.init_plot()
3712/1: %run load_pui_ulysses.py
3712/2: ws.init_plot()
3713/1: %run load_pui_ulysses.py
3713/2: ws.init_plot()
3715/1: %run load_pui_ulysses.py
3715/2: ws.init_plot()
3716/1: pylab.close('all')
3717/1: pylab.close('all')
3717/2: %run load_pui_ulysses.py
3717/3: ws.init_plot()
3717/4: ws.plot()
3717/5: ws.init_plot()
3717/6: ws.init_plot()
3719/1: %run load_pui_ulysses.py
3719/2: ws.init_plot()
3720/1: %run load_pui_ulysses.py
3720/2: ws.init_plot()
3721/1: ws.init_plot()
3721/2: %run load_pui_ulysses.py
3722/1: %run load_pui_ulysses.py
3722/2: ws.init_plot()
3723/1: ws.init_plot()
3723/2: %run load_pui_ulysses.py
3723/3: ws.init_plot()
3724/1: %run load_pui_ulysses.py
3724/2: ws.init_plot()
3725/1: %run load_pui_ulysses.py
3725/2: ws.init_plot()
3726/1: %run load_pui_ulysses.py
3726/2: ws.init_plot()
3727/1: %run load_pui_ulysses.py
3727/2: ws.init_plot()
3728/1: %run load_pui_ulysses.py
3728/2: ws.init_plot()
3729/1: %run load_pui_ulysses.py
3729/2: ws.init_plot()
3730/1: %run load_pui_ulysses.py
3730/2: ws.init_plot()
3731/1: %run load_pui_ulysses.py
3731/2: ws.init_plot()
3732/1: %run load_pui_ulysses.py
3733/1: ws.init_plot()
3733/2: %run load_pui_ulysses.py
3733/3: ws.init_plot()
3734/1: %run load_pui_ulysses.py
3734/2: ws.init_plot()
3735/1: %run load_pui_ulysses.py
3735/2: ws.init_plot()
3736/1: %run load_pui_ulysses.py
3736/2: ws.init_plot()
3737/1: %run load_pui_ulysses.py
3737/2: ws.init_plot()
3738/1: %run load_pui_ulysses.py
3738/2: ws.init_plot()
3739/1: %run load_pui_ulysses.py
3739/2: ws.init_plot()
3740/1: %run load_pui_ulysses.py
3740/2: ws.init_plot()
3741/1: %run load_pui_ulysses.py
3741/2: ws.init_plot()
3742/1: %run load_pui_ulysses.py
3742/2: ws.init_plot()
3743/1: %run load_pui_ulysses.py
3743/2: ws.init_plot()
3744/1: %run load_pui_ulysses.py
3744/2: ws.init_plot()
3745/1: %run load_pui_ulysses.py
3745/2: ws.init_plot()
3746/1: %run load_pui_ulysses.py
3746/2: ws.init_plot()
3747/1: %run load_pui_ulysses.py
3747/2: ws.init_plot()
3748/1: %run load_pui_ulysses.py
3748/2: ws.init_plot()
3749/1: %run load_pui_ulysses.py
3749/2: ws.init_plot()
3750/1: %run load_pui_ulysses.py
3750/2: ws.init_plot()
3751/1: %run load_pui_ulysses.py
3751/2: ws.init_plot()
3752/1: %run load_pui_ulysses.py
3752/2: ws.init_plot()
3753/1: %run load_pui_ulysses.py
3753/2: ws.init_plot()
3754/1: D.wspace.shape
3754/2: %run load_pui_ulysses.py
3754/3: D.wspace.shape
3754/4: D.w3dspace.shape
3754/5: D.plot_wspace()
3754/6: D.plot_FoV()
3754/7: norm_arr
3754/8: norm2, H2 = D.calc_w3dspecs(min_whe = 0.1)
3754/9: norm2.shape
3754/10: ws.init_plot()
3755/1: norm2.shape
3755/2: %run load_pui_ulysses.py
3755/3: D.w3dspace
3755/4: D.w3dspace.shape
3755/5: ws.init_plot()
3756/1: %run load_pui_ulysses.py
3756/2: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3756/3: D.plot_wspec(dim='x',slice=9,min_wHe = 1.2)
3757/1: %run load_pui_ulysses.py
3757/2: D.plot_wspec(dim='x',slice=9,min_wHe = 1.2)
3758/1: %run load_pui_ulysses.py
3758/2: D.plot_wspec(dim='x',slice=9,min_wHe = 1.2)
3758/3: D.plot_wspec(dim='x',slice=8,min_wHe = 1.2)
3758/4: D.plot_wspec(dim='x',slice=12,min_wHe = 1.2)
3758/5: D.plot_wspec(dim='x',slice=13,min_wHe = 1.2)
3758/6: D.plot_wspec(dim='x',slice=15,min_wHe = 1.2)
3758/7: D.plot_wspec(dim='x',slice=19,min_wHe = 1.2)
3758/8: D.plot_wspec(dim='x',slice=18,min_wHe = 1.2)
3758/9: D.plot_wspec(dim='x',slice=17,min_wHe = 1.2)
3758/10: pylab.close('all')
3758/11: D.plot_wspec(dim='x',slice=16,min_wHe = 1.2)
3758/12: pylab.close('all')
3758/13: D.plot_wspec(dim='x',slice=8,min_wHe = 1.2)
3758/14: D.plot_wspec(dim='y',slice=8,min_wHe = 1.2)
3758/15: pylab.close('all')
3758/16: D.plot_wspec(dim='y',slice=8,min_wHe = 1.2)
3758/17: H
3759/1: pylab.close('all')
3759/2: %run load_pui_ulysses.py
3759/3: D.plot_wspec(dim='x',slice=8,min_wHe = 1.2)
3759/4: D.plot_wspec(dim='y',slice=8,min_wHe = 1.2)
3759/5: D.plot_wspec(dim='y',slice=6,min_wHe = 1.2)
3759/6: D.plot_wspec(dim='y',slice=4,min_wHe = 1.2)
3760/1: %run load_pui_ulysses.py
3760/2: D.plot_wspec(dim='y',slice=4,min_wHe = 1.2)
3760/3: D.plot_wspec(dim='x',slice=4,min_wHe = 1.2)
3760/4: pylab.close('all')
3760/5: D.plot_wspec(dim='x',slice=14,min_wHe = 1.2)
3760/6: D.plot_wspec(dim='x',slice=16,min_wHe = 1.2)
3760/7: D.plot_wspec(dim='x',slice=17,min_wHe = 1.2)
3760/8: pylab.close('all')
3760/9: D.plot_wspec(dim='x',slice=15,min_wHe = 1.2)
3760/10: pylab.close('all')
3760/11: D.plot_wspec(dim='x',slice=18,min_wHe = 1.2)
3760/12: pylab.close('all')
3760/13: D.plot_wspec(dim='y',slice=10,min_wHe = 1.2)
3760/14: H1 = H[]
3760/15: H1 = H[:]
3760/16: norm2, H = D.calc_w3dspecs(min_whe = 0.1)
3760/17: H2 = H[:]
3760/18: H2 = H[8:10,8:10,8:10]
3760/19: H2
3760/20: H2 = H[10:12,8:10,8:10]
3760/21: H2
3760/22: G = numpy.zeros((3,3,3))
3760/23: G
3760/24: G[0,:,:] = 1
3760/25: G[0,:,:] = 1
3760/26: G[1,:,:] = 20
3760/27: G[2,:,:] = 300
3760/28: G
3760/29: G[:,:,2] += 1
3760/30: G
3760/31: G[0,:,:] = 10
3760/32: G[2,:,:] = 30
3760/33: G[1,:,:] = 20
3760/34: G[:,:,2] += 1
3760/35: G
3760/36: G[0,:,:]
3760/37: G[:,1,:]
3760/38: pcolormesh(G[:1:])
3760/39: pcolormesh(G[:,1,:])
3760/40: pylab.close('all')
3760/41: pcolormesh(G[:,1,:])
3760/42: G[:,1,:]
3760/43: G
3760/44: G[:,:,0]
3760/45: G[1,:,:]
3760/46: G[1,:,:].T
3760/47: G[:,1:]
3760/48: G[:,1,:]
3760/49: G[:,1,:].T
3760/50: G[:,:,1]
3761/1: %run load_pui_ulysses.py
3762/1: %run load_pui_ulysses.py
3762/2: D.plot_wspec(dim='y',slice=10,min_wHe = 1.2)
3762/3: D.plot_wspec(dim='z',slice=10,min_wHe = 1.2)
3762/4: pylab.close('all')
3762/5: D.plot_wspec(dim='z',slice=10,min_wHe = 1.2)
3763/1: %run load_pui_ulysses.py
3763/2: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3763/3: wbins = arange(-2,2.01,0.2)
3763/4: wbins[-1:0]
3763/5: wbins
3763/6: reversed(wbins)
3763/7: a = reversed(wbins)
3763/8: a
3763/9: wbins[::-1]
3764/1: %run load_pui_ulysses.py
3764/2: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3764/3: D.plot_wspec(dim='z',slice=10,min_wHe = 1.2)
3765/1: %run load_pui_ulysses.py
3765/2: D.plot_wspec(dim='z',slice=10,min_wHe = 1.2)
3765/3: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3766/1: %run load_pui_ulysses.py
3766/2: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3766/3: wbins = arange(-2,2.01,0.2)
3766/4: wbins[::-1]
3767/1: wbins = arange(-2,2.01,0.2)
3767/2: %run load_pui_ulysses.py
3767/3: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3768/1: %run load_pui_ulysses.py
3768/2: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3769/1: %run load_pui_ulysses.py
3769/2: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3770/1: %run load_pui_ulysses.py
3770/2: D.plot_wspec(dim='x',slice=10,min_wHe = 1.2)
3770/3: D.plot_wspec(dim='y',slice=10,min_wHe = 1.2)
3770/4: D.plot_wspec(dim='y',slice=16,min_wHe = 1.2)
3770/5: D.plot_wspec(dim='z',slice=10,min_wHe = 1.2)
3771/1: %run load_pui_ulysses.py
3771/2: D.plot_wspec(dim='z',slice=10,min_wHe = 1.2)
3771/3: D.plot_wspec(dim='y',slice=10,min_wHe = 1.2)
3772/1: %run load_pui_ulysses.py
3772/2: ws.init_plot()
3773/1: %run load_pui_ulysses.py
3773/2: ws.init_plot()
3774/1: %run load_pui_ulysses.py
3774/2: ws.init_plot()
3775/1: %run load_pui_ulysses.py
3775/2: ws.H
3776/1: %run load_pui_ulysses.py
3776/2: ws.init_plot()
3777/1: %run load_pui_ulysses.py
3777/2: ws.init_plot()
3778/1: %run load_pui_ulysses.py
3778/2: ws.init_plot()
3779/1: %run load_pui_ulysses.py
3779/2: ws.init_plot()
3780/1: %run load_pui_ulysses.py
3780/2: ws.init_plot()
3781/1: %run load_pui_ulysses.py
3781/2: ws.init_plot()
3782/1: %run load_pui_ulysses.py
3783/1: %run load_pui_ulysses.py
3783/2: ws.init_plot()
3784/1: %run load_pui_ulysses.py
3784/2: ws.init_plot()
3785/1: %run load_pui_ulysses.py
3785/2: ws.init_plot()
3786/1: %run load_pui_ulysses.py
3786/2: ws.init_plot()
3787/1: %run load_pui_ulysses.py
3787/2: ws.init_plot()
3787/3: D.plot_wspec(dim='x',slice=7,min_wHe = 1.2)
3788/1: %run load_pui_ulysses.py
3788/2: ws.init_plot()
3789/1: %run load_pui_ulysses.py
3789/2: ws.init_plot()
3790/1: %run load_pui_ulysses.py
3790/2: ws.init_plot()
3791/1: %run load_pui_ulysses.py
3791/2: ws.init_plot()
3792/1: %run load_pui_ulysses.py
3792/2: ws.init_plot()
3793/1: %run load_pui_ulysses.py
3793/2: ws.init_plot()
3794/1: %run load_pui_ulysses.py
3794/2: ws.init_plot()
3794/3: cmin
3794/4: ws.Quadmesh.get_clim()
3795/1: %run load_pui_ulysses.py
3795/2: ws.init_plot()
3796/1: %run load_pui_ulysses.py
3796/2: ws.init_plot()
3797/1: %run load_pui_ulysses.py
3797/2: ws.init_plot()
3798/1: %run load_pui_ulysses.py
3798/2: ws.init_plot()
3799/1: %run load_pui_ulysses.py
3799/2: ws.init_plot()
3800/1: %run load_pui_ulysses.py
3800/2: ws.init_plot()
3801/1: %run load_pui_ulysses.py
3801/2: ws.init_plot()
3802/1: %run load_pui_ulysses.py
3802/2: ws.init_plot()
3803/1: %run load_pui_ulysses.py
3803/2: ws.init_plot()
3804/1: %run load_pui_ulysses.py
3804/2: ws.init_plot()
3804/3: ws.cb
3805/1: %run load_pui_ulysses.py
3805/2: ws.init_plot()
3806/1: %run load_pui_ulysses.py
3806/2: ws.init_plot()
3807/1: %run load_pui_ulysses.py
3807/2: ws.init_plot()
3808/1: %run load_pui_ulysses.py
3808/2: ws.init_plot()
3809/1: %run load_pui_ulysses.py
3809/2: ws.init_plot()
3810/1: %run load_pui_ulysses.py
3810/2: ws.init_plot()
3811/1: %run load_pui_ulysses.py
3811/2: ws.init_plot()
3812/1: %run load_pui_ulysses.py
3812/2: ws.init_plot()
3812/3: d
3813/1: %run load_pui_ulysses.py
3813/2: ws.init_plot()
3814/1: %run load_pui_ulysses.py
3814/2: ws.init_plot()
3814/3: H
3814/4: norm2, H = D.calc_w3dspecs(min_whe = 0.1)
3814/5: H.shape
3814/6: H[19,7:12,7:12]
3815/1: %run load_pui_ulysses.py
3815/2: ws.init_plot()
3816/1: %run load_pui_ulysses.py
3816/2: D.plot_wspec(dim='y',slice=1,min_wHe = 1.2)
3816/3: D.plot_wspec(dim='z',slice=1,min_wHe = 1.2)
3816/4: pylab.close('all')
3816/5: D.plot_wspec(dim='z',slice=1,min_wHe = 1.2)
3817/1: pylab.close('all')
3817/2: %run load_pui_ulysses.py
3817/3: D.plot_wspec(dim='z',slice=1,min_wHe = 1.2)
3817/4: ws.init_plot()
3817/5: d
3817/6: d
3818/1: %run load_pui_ulysses.py
3818/2: ws.init_plot()
3819/1: %run load_pui_ulysses.py
3819/2: ws.init_plot()
3820/1: %run load_pui_ulysses.py
3820/2: ws.init_plot()
3821/1: %run load_pui_ulysses.py
3821/2: ws.init_plot()
3822/1: %run load_pui_ulysses.py
3822/2: ws.init_plot()
3823/1: %run load_pui_ulysses.py
3823/2: ws.init_plot()
3824/1: %run load_pui_ulysses.py
3824/2: ws.init_plot()
3825/1: %run load_pui_ulysses.py
3825/2: ws.init_plot()
3825/3: ws.Quadmesh
3825/4: ws.Quadmesh_get_array()
3825/5: ws.Quadmesh.get_array()
3825/6: unique(ws.Quadmesh.get_array())
3826/1: %run load_pui_ulysses.py
3826/2: ws.init_plot()
3826/3: pylab.close('all')
3826/4: ws.init_plot(normm = 'sg')
3826/5: ws.init_plot(norm = 'sg')
3826/6: ws.init_plot(color_norm = 'sg')
3826/7: ws = WSpec(D,color_norm='sg')
3826/8: ws.init_plot()
3827/1: %run load_pui_ulysses.py
3827/2: ws.init_plot()
3828/1: %run load_pui_ulysses.py
3828/2: ws.init_plot()
3829/1: %run load_pui_ulysses.py
3829/2: ws.init_plot()
3829/3: D = Dist3D(d, offset_sp = 45.)
3829/4: ws = WSpec(D,min_wHe= 0.9)
3829/5: ws.init_plot()
3829/6: min_wHe
3829/7: D.w3dspace.shape
3829/8: D.vels
3829/9: d.hist1d('asp_phi')
3829/10: d.data.keys()
3829/11: d.hist1d('aspphi')
3829/12: d.hist1d('vsw')
3829/13: d.hist1d('vx')
3829/14: d.hist1d('vx',mask='He1')
3829/15: d.hist1d('vx',smask='He1')
3829/16: d.show_mask()
3829/17: d.hist1d('vx',smask='He1+')
3829/18: d.hist1d('vx')
3829/19: d.hist1d('wsw')
3829/20: d.hist1d('asptheta')
3829/21: d.hist1d('asptheta',bins=[0,100])
3829/22: d.hist1d('asptheta',xbins=[0,100])
3829/23: d.hist1d('asptheta',xbin=[0,100])
3829/24: d.hist1d('asptheta',bin=[0,100])
3829/25: d.data.keys()
3829/26: d.data.wHe1+2()
3829/27: d.hist1d('wHe1+2')
3829/28: d.hist1d('vHe+')
3829/29: pylab.close('all')
3829/30: ws.init_plot()
3831/1: %run load_pui_ulysses.py
3831/2: ws = WSpec(min_wHe = 0.9)
3831/3: ws = WSpec(D, min_wHe = 0.9)
3831/4: ws1 = WSpec(D, min_wHe = 0.1)
3831/5: ws.init_plot()
3831/6: ws1.init_plot()
3832/1: %run load_pui_ulysses.py
3832/2: ws = WSpec(min_wHe = 0.9)
3832/3: ws = WSpec(D, min_wHe = 0.9)
3832/4: ws1 = WSpec(D, min_wHe = 0.1)
3832/5: ws.init_plot()
3832/6: ws1.init_plot()
3832/7: pylab.close('all')
3832/8: %run WSpec.py
3832/9: ws1 = WSpec(D, min_wHe = 0.1)
3832/10: ws1.init_plot()
3833/1: %run WSpec.py
3834/1: %run load_pui_ulysses.py
3834/2: ws1 = WSpec(D, min_wHe = 0.1)
3834/3: ws1.init_plot()
3835/1: %run load_pui_ulysses.py
3835/2: ws1 = WSpec(D, min_wHe = 0.1)
3835/3: ws1.init_plot()
3835/4: ws = WSpec(D, min_wHe = 0.9)
3835/5: ws.init_plot()
3836/1: %run load_pui_ulysses.py
3836/2: ws = WSpec(D, min_wHe = 0.9)
3836/3: ws.init_plot()
3837/1: %run load_pui_ulysses.py
3837/2: ws = WSpec(D, min_wHe = 0.9)
3837/3: ws.init_plot()
3838/1: %run load_pui_ulysses.py
3838/2: ws = WSpec(D, min_wHe = 0.9)
3838/3: ws.init_plot()
3838/4: ws.H
3838/5: max(ws.H)
3838/6: max(ws.H.flatten())
3838/7: unique(ws.H)
3838/8: ws.H.shape
3838/9:
for i in range(20):
    print(unique(ws.H[i,...]))
    print(max(ws.H[i,...]))
    print(i)
    print('\n')
3838/10:
for i in range(20):
    print(unique(ws.H[i,...]))
    print(max(ws.H[i,...].flatten()))
    print(i)
    print('\n')
3838/11:
for i in range(20):
    print(unique(ws.H[i,...])[0:4])
    print(max(ws.H[i,...].flatten()))
    print(i)
    print('\n')
3839/1: %run load_pui_ulysses.py
3839/2: ws = WSpec(D, min_wHe = 0.9)
3839/3: ws.init_plot()
3840/1: %run load_pui_ulysses.py
3840/2: ws = WSpec(D, min_wHe = 0.1)
3840/3: ws1 = WSpec(D, min_wHe = 0.9)
3840/4: ws.init_plot()
3840/5: ws1.init_plot()
3841/1: %run load_pui_ulysses.py
3841/2: ws = WSpec(D, min_wHe = 0.1)
3841/3: ws.init_plot()
3842/1: %run load_pui_ulysses.py
3842/2: ws = WSpec(D, min_wHe = 0.1)
3842/3: %run load_pui_ulysses.py
3842/4: ws = WSpec(D, min_wHe = 0.1)
3842/5: ws.init_plot()
3843/1: %run load_pui_ulysses.py
3843/2: ws = WSpec(D, min_wHe = 0.1)
3843/3: ws.init_plot()
3844/1: %run load_pui_ulysses.py
3844/2: ws = WSpec(D, min_wHe = 0.1)
3844/3: ws1 = WSpec(D, min_wHe = 0.9)
3844/4: ws.init_plot()
3844/5: ws1.init_plot()
3844/6: d.hist2d
3844/7: d.hist2d()
3844/8: d.hist2d?
3844/9: d.hist2d('tch','epq')
3844/10: d.hist2d('tch','epq',norm='ymax')
3844/11: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3846/1: %run uswipha.py
3846/2: d = uswipha()
3846/3: d = uswipha(year=1993, tf=[[1,50]])
3846/4: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3847/1: d = uswipha(year=1993, tf=[[1,50]])
3847/2: %run uswipha.py
3847/3: d = uswipha(year=1993, tf=[[1,50]])
3847/4: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3848/1: %run uswipha.py
3848/2: d = uswipha(year=1993, tf=[[1,50]])
3848/3: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3849/1: %run uswipha.py
3849/2: d = uswipha(year=1993, tf=[[1,15]])
3849/3: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3851/1: %run uswipha.py
3851/2: d = uswipha(year=1993, tf=[[1,15]])
3851/3: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3851/4: matplotlib
3851/5: matplotlib.version
3851/6: print mpl.__version__
3851/7: matplotlib.colors.Colormap
3851/8: matplotlib.colors.Colormap
3851/9: matplotlib.colors.Colormap()
3851/10: colormaps
3851/11: colormaps.spectral
3851/12: plt.register_cmap(name='spectral', cmap = cmaps.spectral)
3851/13: plt.register_cmap(name='spectral',cmap=colormaps.spectral)
3851/14: colormaps.viridis
3851/15: import colormaps as cmaps
3851/16: import colormaps
3851/17: colormaps
3852/1: import colormaps as cmaps
3852/2: register_cmap(name=spectral,smap=spectral)
3852/3: register_cmap(name=spectral,cmap=spectral)
3852/4: register_cmap(name="spectral",cmap=spectral)
3852/5: d = uswipha(year=1993, tf=[[1,15]])
3852/6: %run uswipha.py
3852/7: d = uswipha(year=1993, tf=[[1,15]])
3852/8: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3853/1: %run uswipha.py
3854/1: print mpl.__version__
3854/2: cmap = cm.get_cmap('spe')
3854/3: cmap = cm.get_cmap('Spectal')
3854/4: cmap = cm.get_cmap('Spectral')
3855/1: %run uswipha.py
3855/2: d = uswipha(year=1993, tf=[[1,15]])
3855/3: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3857/1: %run load_pui_ulysses.py
3857/2: ws.init_plot()
3857/3: ws = WSpec(D, min_wHe = 0.9)
3857/4: ws.init_plot()
3859/1: %run load_pui_ulysses.py
3859/2: ws.init_plot()
3859/3: ws1 = WSpec(D, min_wHe = 0.9)
3859/4: ws1.init_plot()
3860/1: %run load_pui_ulysses.py
3861/1: %run load_pui_ulysses.py
3862/1: %run load_pui_ulysses.py
3862/2: ws.init_plot()
3862/3: d.data
3862/4: d.data.keys()
3862/5: d.
3862/6: ws.init_plot()
3863/1: %run load_pui_ulysses.py
3863/2: ws.init_plot()
3863/3: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax")
3863/4: d.data.keys()
3863/5: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax",weights='brw')
3863/6: d.data.keys()
3863/7: d.set_mask('rng0','rng',0,0)
3863/8: d.set_mask('rng1','rng',1,1)
3863/9: d.hist2d('tch','epq',binx=arange(200,500),biny = arange(0,64),norm="ymax",weights='brw')
3863/10: d.hist2d('tch','epq',binx=arange(100,500),biny = arange(0,64),norm="ymax",weights='brw')
3863/11: d.show_mask()
3863/12: d.hist2d('tch','ech',binx=arange(100,500),biny = arange(0,64),norm="ymax",weights='brw')
3863/13: unique(d.get_data['rng'])
3863/14: unique(d.get_data('rng'))
3863/15: unqiue(d.data['rng'])
3863/16: unique(d.data['rng'])
3863/17: d.animate2d('tch','ech',prodz='epq',binx=arange(100,500),biny = arange(0,64),binz=arange(0,50),norm="ymax")
3864/1: %run uswiutils.py
3864/2: getvelocity(4,1,range(0,50))
3864/3: vhe=getvelocity(4,1,range(0,50))
3864/4: vhe[16]
3864/5: d.reset_mask('Master','ech')
3864/6: unique(d.data['vsw'])
3863/18: unique(d.data['vsw'])
3863/19: histogam(unique(d.data['vsw']))
3863/20: histogram(unique(d.data['vsw']))
3863/21: d.animate2d('tch','ech',prodz='epq',binx=arange(100,500),biny = arange(0,64),binz=arange(0,50),norm="ymax")
3863/22: 900./800.
3863/23: ws1 = WSpec(D, min_wHe = 1)
3863/24: d.hist2d('tch','ech',binx=arange(100,500),biny = arange(0,64),norm="ymax",weights='brw')
3863/25: d.animate2d('tch','ech',prodz='epq',binx=arange(100,500),biny = arange(0,64),binz=arange(0,50),norm="ymax")
3863/26: pylab.close('all')
3866/1: %run load_pui_ulysses.py
3866/2: fin = open("/data/projects/ace/efficencies/He1+.eff",'r')
3866/3: dat = loadtxt(fin)
3866/4: dat
3866/5: eff = dat[:,1]
3866/6: eff
3866/7: eff = append(array([0]),eff)
3866/8: eff
3866/9: eff[1]
3867/1: 3/4
3867/2: %run make_multiplots.py
3869/1: %run make_multiplots.py
3870/1: %run make_multiplots.py
3871/1: %run make_multiplots.py
3871/2:
for i in dataA.index:
    print(i)
3872/1: %run make_multiplots.py
3873/1: %run make_multiplots.py
3874/1: %run make_multiplots.py
3874/2: from process_event_SEPT import EventSEPT
3874/3: pickelpath
3874/4: picklepath
3874/5: %debug
3874/6: %run make_multiplots.py
3874/7: %debug
3875/1: %run make_multiplots.py
3876/1: epq_ace = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
3876/2: import numpy as np
3876/3: epq_ace = np.array(epq_ace)
3876/4: epq_ul = np.array([ 60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056, 34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249, 19.18507355, 17.85605316, 16.6190989, 15.46783299, 14.39631949, 13.39903366, 12.47083347, 11.60693312, 10.80287831, 10.05452332, 9.35800963, 8.709746, 8.10638996, 7.54483061, 7.02217253, 6.53572089, 6.08296755, 5.66157808, 5.26937981, 4.90435056, 4.56460821, 4.24840107, 3.95409875, 3.68018383, 3.42524401, 3.1879648, 2.96712279, 2.76157931, 2.57027459, 2.39222225, 2.22650424, 2.07226613, 1.92871266, 1.79510366, 1.67075025, 1.55501125, 1.44728992, 1.34703084, 1.25371708, 1.1668675, 1.08603431, 1.01080073, 0.94077886, 0.87560766, 0.81495111, 0.75849646, 0.70595263, 0.6570487 ])
3876/5: epq_ul.shape
3876/6: epq_ace.shape
3876/7: ax = pylab.plot(range(len(epq_ul)),epq_ul)
3876/8: ax.plot(range(len(epq_ul)),epq_ace)
3876/9: pylab.plot(range(len(epq_ul)),epq_ace)
3876/10: pylab.plot(range(len(epq_ace)),epq_ace)
3876/11: fout = open('uly_ef.txt','w')
3876/12:
for i in range(len(epq_ul)):
    fout.write(epq_ul[i])
3876/13:
for i in range(len(epq_ul)):
    fout.write(str(epq_ul[i]))
3876/14:
for i in range(len(epq_ul)):
    print(str(epq_ul[i]))
3876/15:
for i in range(len(epq_ul)):
    fout.write(str(epq_ul[i]))
3876/16: fout.close
3876/17: fout.close()
3876/18: fout = open('uly_ef.txt','w')
3876/19:
for i in range(len(epq_ul)):
    fout.write(str(epq_ul[i]), '\n')
3876/20:
for i in range(len(epq_ul)):
    fout.write('%s\n'%str(epq_ul[i]))
3876/21: fout.close()
3877/1: %run guess_ul_eff.py
3878/1: %run guess_ul_eff.py
3879/1: %run guess_ul_eff.py
3880/1: %run guess_ul_eff.py
3880/2: plt.show()
3881/1: %run guess_ul_eff.py
3881/2: plt.show()
3881/3: from lmfit.models import PolynomialModel
3881/4: pmodel = PolynomialModel
3881/5: pmodel.param_names
3881/6:
print('parameter names: {}'.format(pmodel.param_names))
print('independent variables: {}'.format(pmodel.independent_vars))
3881/7: print('parameter names: {}'.format(pmodel.param_names))
3881/8: pmodel
3881/9: pmodel?
3881/10: pmodel([1,2,3])
3881/11: pmodel(3,[1,2,3])
3882/1: from lmfit import Model
3882/2: from lmfit.models import PolynomialModel
3882/3: pmodel = PolynomialModel
3882/4: pmodel?
3882/5: pmodel.independent_vars
3882/6: PolynomialModel
3882/7: PolynomialModel?
3882/8:

data = loadtxt('model1d_gauss.dat')
3882/9:

data = loadtxt('model1d_gauss.dat')
3883/1: %run guess_ul_eff.py
3883/2: from lmfit.models import PolynomialModel
3883/3: pmodel = PolynomialModel()
3883/4: pmodel = PolynomialModel(3)
3883/5: pars = pmodel.guess(eff_ace,x=epq_ace)
3883/6: pars
3883/7: out = pmodel.fit(eff_ace,pars,x=epq_ace)
3883/8: print(out.fit_report)
3883/9: print(out.fit_report(min_correl=0.25))
3883/10: out
3883/11: out.var_names
3883/12: out.best_fit
3883/13: out.best_values
3884/1: %run guess_ul_eff.py
3885/1: %run guess_ul_eff.py
3886/1: %run guess_ul_eff.py
3887/1: %run guess_ul_eff.py
3888/1: %run guess_ul_eff.py
3888/2: best_vals
3889/1: %run guess_ul_eff.py
3890/1: %run guess_ul_eff.py
3890/2: best_vals
3891/1: %run guess_ul_eff.py
3891/2: plt.show()
3891/3: best_vals
3892/1: %run guess_ul_eff.py
3892/2: plt.show()
3893/1: %run guess_ul_eff.py
3894/1: %run guess_ul_eff.py
3895/1: %run guess_ul_eff.py
3895/2: plt.show()
3895/3: best_vals
3896/1: %run guess_ul_eff.py
3896/2: best_vals
3896/3: plt.show()
3897/1: %run guess_ul_eff.py
3897/2: plt.show()
3897/3: best_vals
3897/4: best_vals[:]
3897/5: best_vals[1]
3897/6: best_vals[:-1]
3898/1: %run guess_ul_eff.py
3899/1: %run guess_ul_eff.py
3900/1: %run guess_ul_eff.py
3901/1: %run guess_ul_eff.py
3902/1: %run guess_ul_eff.py
3903/1: %run guess_ul_eff.py
3904/1: %run guess_ul_eff.py
3904/2: %run guess_ul_eff.py
3905/1: %run guess_ul_eff.py
3906/1: %run guess_ul_eff.py
3907/1: %run guess_ul_eff.py
3908/1: %run guess_ul_eff.py
3909/1: %run load_pui_ulysses.py
3909/2: array([ 60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056, 34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249, 19.18507355, 17.85605316, 16.6190989, 15.46783299, 14.39631949, 13.39903366, 12.47083347, 11.60693312, 10.80287831, 10.05452332, 9.35800963, 8.709746, 8.10638996, 7.54483061, 7.02217253, 6.53572089, 6.08296755, 5.66157808, 5.26937981, 4.90435056, 4.56460821, 4.24840107, 3.95409875, 3.68018383, 3.42524401, 3.1879648, 2.96712279, 2.76157931, 2.57027459, 2.39222225, 2.22650424, 2.07226613, 1.92871266, 1.79510366, 1.67075025, 1.55501125, 1.44728992, 1.34703084, 1.25371708, 1.1668675, 1.08603431, 1.01080073, 0.94077886, 0.87560766, 0.81495111, 0.75849646, 0.70595263, 0.6570487 ])
3909/3: e = array([ 60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056, 34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249, 19.18507355, 17.85605316, 16.6190989, 15.46783299, 14.39631949, 13.39903366, 12.47083347, 11.60693312, 10.80287831, 10.05452332, 9.35800963, 8.709746, 8.10638996, 7.54483061, 7.02217253, 6.53572089, 6.08296755, 5.66157808, 5.26937981, 4.90435056, 4.56460821, 4.24840107, 3.95409875, 3.68018383, 3.42524401, 3.1879648, 2.96712279, 2.76157931, 2.57027459, 2.39222225, 2.22650424, 2.07226613, 1.92871266, 1.79510366, 1.67075025, 1.55501125, 1.44728992, 1.34703084, 1.25371708, 1.1668675, 1.08603431, 1.01080073, 0.94077886, 0.87560766, 0.81495111, 0.75849646, 0.70595263, 0.6570487 ])
3909/4: e.shape
3911/1: %run load_pui_ulysses.py
3912/1: %run load_pui_ulysses.py
3913/1: %run load_pui_ulysses.py
3913/2: d
3913/3: d[0]
3913/4: d.get_data[0]
3913/5: d.get_data
3913/6: d.get_data?
3913/7: d.get_data('all','all')[0]
3913/8: d.get_data('all','all')
3913/9: d.get_data('all','epq')[0]
3913/10: d.get_data('all','epq')[0:5]
3913/11: d.get_data('all','eff')[0:5]
3914/1: %run load_pui_ulysses.py
3914/2: d.show_mask()
3914/3: d.reset_mask('all')
3914/4: d.show_mask()
3914/5: d.remove_submask('all')
3914/6: d.remove_mask('all')
3914/7: d.remove_submask('all')
3914/8: d.show_mask()
3914/9: d.set_mask('Master','epq',10,30)
3914/10: d.show_mask()
3914/11: d.set_mask('Master','ech',20,100)
3914/12: d.show_mask()
3914/13: d.remove_submask('Master','vsw')
3914/14: d.show_mask()
3914/15: pylab.close('all')
3914/16: d.show_mask()
3915/1: %run load_pui_ulysses.py
3916/1: %run load_pui_ulysses.py
3916/2: d.show_mask()
3917/1: d.show_mask()
3917/2: %run load_pui_ulysses.py
3917/3: d.show_mask()
3918/1: d.show_mask()
3918/2: %run load_pui_ulysses.py
3918/3: unique(d.data['ech'])
3919/1: %run load_pui_ulysses.py
3919/2: unique(d.data['ech'])
3920/1: %run load_pui_ulysses.py
3920/2: unique(d.data['ech'])
3921/1: %run load_pui_ulysses.py
3921/2: unique(d.data['ech'])
3922/1: %run load_pui_ulysses.py
3922/2: unique(d.data['ech'])
3923/1: %run load_pui_ulysses.py
3923/2: d.show_mask()
3924/1: %run load_pui_ulysses.py
3924/2: d.show_mask()
3925/1: %run load_pui_ulysses.py
3925/2: d.show_mask()
3926/1: %run load_pui_ulysses.py
3926/2: d.show_mask()
3927/1: %run load_pui_ulysses.py
3927/2: d.show_mask()
3927/3: d.hist1d('ech')
3927/4: d.reset_mask('all')
3927/5: d.show_mask()
3927/6: d.hist1d('ech')
3927/7: unique(d.data['ech'])
3928/1: %run load_pui_ulysses.py
3928/2: d.show_mask()
3928/3: D._calc_FoV()
3928/4: d.show_mask()
3929/1: %run load_pui_ulysses.py
3930/1: %run load_pui_ulysses.py
3930/2: d.show_mask()
3930/3: D._add_3Dv()
3931/1: %run load_pui_ulysses.py
3931/2: d.show_mask()
3931/3: unique(d.data['ech'])
3932/1: %run load_pui_ulysses.py
3932/2: d.show_mask()
3932/3: D._add_3Dv()
3932/4: D.d.data['epq']
3932/5: D.d.data['epq'].astype(int)
3932/6: D.d.get_data('Master','epq')
3932/7: D.d.get_data('Master','epq').astype(int)
3932/8: phiind = searchsorted(self.aspphi, around(self.d.data["aspphi"]))
3932/9: phiind = searchsorted(D.aspphi, around(D.d.data["aspphi"]))
3932/10: phiind
3932/11: phiind.shape
3933/1: %run load_pui_ulysses.py
3933/2: D._add_3Dv()
3934/1: %run load_pui_ulysses.py
3934/2: D._add_3Dv()
3934/3: D.d.data["vsw"].shape
3934/4: D.d.data["vx"].shape
3935/1: %run load_pui_ulysses.py
3935/2: d.data.leys()
3935/3: d.data.keys()
3936/1: %run load_pui_ulysses.py
3936/2: ws.init_plot()
3937/1: %run load_pui_ulysses.py
3937/2: ws.init_plot()
3938/1: %run load_pui_ulysses.py
3938/2: D.vels
3938/3: D.vels-shape
3938/4: D.vels.shape
3939/1: %run load_pui_ulysses.py
3939/2: ws.init_plot()
3941/1: %run load_pui_ulysses.py
3941/2: ws.init_plot()
3941/3: ws.init_plot()
3942/1: %run load_pui_ulysses.py
3942/2: ws.init_plot()
3943/1: %run load_pui_ulysses.py
3944/1: %run load_pui_ulysses.py
3944/2: ws.init_plot()
3944/3: min(D.H)
3944/4: min(ws.H)
3944/5: amin(ws.H)
3944/6: min(ws.H[ws.H>0])
3945/1: %run load_pui_ulysses.py
3945/2: ws.init_plot()
3946/1: %run load_pui_ulysses.py
3946/2: ws.init_plot()
3947/1: %run load_pui_ulysses.py
3947/2: ws.init_plot()
3948/1: %run load_pui_ulysses.py
3948/2: ws.init_plot()
3948/3: max(ws.H)
3948/4: amax(ws.H)
3948/5: ws.H
3948/6: ws.H[ws.H>0]
3948/7: ws.H[ws.H>0].shape
3948/8: ws.H.shape
3948/9: norm_arr,H2 = D.calc_w3dspecs()
3948/10: norm_arr
3948/11: unique(norm_arr)
3948/12: amax(norm_arr)
3948/13: amax(H2)
3948/14: d.brw
3948/15: d.data['brw']
3948/16: unique(d.data['brw'])
3948/17: amax(d.data['brw'])
3948/18: amin(d.data['brw'])
3948/19: d.hist1d('brw')
3949/1: %run load_pui_ulysses.py
3949/2: d.hist1d('brw')
3949/3: d.data['year']
3949/4: d.data['year'].shape
3949/5: d.hist1d('brw')
3949/6: d.hist1d('brw',bins=arange(0,10,1))
3949/7: d.hist1d('brw',binx=arange(0,10,1))
3949/8: d.hist1d('brw',binx=arange(0,10,.1))
3949/9: amax(d.data['brw'])
3950/1: %run load_pui_ulysses.py
3950/2: amax(d.data['brw'])
3951/1: %run load_pui_ulysses.py
3951/2: amax(d.data['brw'])
3952/1: %run load_pui_ulysses.py
3952/2: amax(d.data['brw'])
3953/1: %run load_pui_ulysses.py
3953/2: amax(d.data['brw'])
3954/1: %run load_pui_ulysses.py
3955/1: %run load_pui_ulysses.py
3955/2: amax(d.data['brw'])
3955/3: inf
3955/4: np.inf
3957/1: %run load_pui_ulysses.py
3957/2: d.hist1d('brw',binx=arange(0,10,.1))
3957/3: ws.H.shape
3957/4: ws.init_plot()
3957/5: min(ws.H)
3957/6: min(ws.H[ws.H>0])
3958/1: %run load_pui_ulysses.py
3958/2: ws.init_plot()
3959/1: %run load_pui_ulysses.py
3959/2: ws.init_plot()
3960/1: %run load_pui_ulysses.py
3960/2: ws.init_plot()
3961/1: %run load_pui_ulysses.py
3961/2: ws.init_plot()
3962/1: %run load_pui_ulysses.py
3962/2: ws.init_plot()
3963/1: %run load_pui_ulysses.py
3963/2: ws.init_plot()
3963/3: ws.H[10,:,:]
3963/4: ws.H[:,10,:]
3963/5: amax(ws.H[:,10,:])
3963/6: amax(ws.H[:,:,10])
3963/7: amax(ws.H[10,:,:])
3964/1: %run load_pui_ulysses.py
3964/2: ws.init_plot()
3964/3: amax(ws.H[10,:,:])
3964/4: amax(ws.H[:,10,:])
3964/5: amax(ws.H[:,:,10])
3964/6: ws.H[:,10,:]
3964/7: norm_arr,H2 = D.calc_w3dspecs()
3964/8: amax(norm_arr)
3964/9: amax(H2)
3964/10: unique(d.get_data('brw'))
3964/11: unique(d.get_data('He1+','brw'))
3964/12: unique(d.get_data('He1+','wgts_sec'))
3964/13: unique(d.get_data('Master','eff'))
3964/14:
for i in range(20):
    print(d.data['eff'][i])
3964/15: d.set_mask('Test','eff',0.0,0.0)
3964/16: d.hist1d(smasks='Test','epq',binx=arange(0,10,.1))
3964/17: d.hist1d('epq',binx=arange(0,10,.1))
3964/18: d.hist1d('epq',binx=arange(0,10,.1),smask='Test')
3964/19: d.get_data('Test','epq')
3964/20: d.hist1d('epq',binx=arange(0,10,1),smask='Test')
3964/21: d.hist1d('epq',binx=arange(0,10,1))
3964/22: d.hist1d('epq',binx=arange(0,10,1),smask='He1+')
3964/23: d.get_data('He1+','epq')
3964/24: unique(d.get_data('Master','epq'))
3964/25: unique(d.get_data('Master','eff'))
3964/26: unique(d.get_data('Master','eff')).shape
3964/27: %run dist3D_pui_ulysses.py
3964/28: D._calc_phspeff_wgt()
3964/29: D.deff
3965/1: %run dist3D_pui_ulysses.py
3965/2: %run load_pui_ulysses.py
3965/3: D.deff
3966/1: %run load_pui_ulysses.py
3966/2: d.get_data('Master','eff')
3966/3: unique(d.get_data('Master','eff'))
3966/4: ws.init_plot()
3967/1: %run load_pui_ulysses.py
3967/2: ws.init_plot()
3968/1: %run load_pui_ulysses.py
3968/2: ws.init_plot()
3969/1: %run load_pui_ulysses.py
3969/2: ws.init_plot()
3969/3: max(ws.H[:,19,:)]
3969/4: max(ws.H[:,19,:])
3969/5: amax(ws.H[:,19,:])
3969/6: 0.0 < 1.
3969/7: 0 < 1.
3969/8: amax(ws.H[:,19,:])
3969/9: max(ws.H[:,19,:])
3970/1: %run load_pui_ulysses.py
3970/2: ws.init_plot()
3971/1: %run load_pui_ulysses.py
3972/1: %run load_pui_ulysses.py
3972/2: ws.init_plot()
3973/1: %run load_pui_ulysses.py
3973/2: ws = WSpec(D, color_norm = 'all')
3973/3: ws.init_plot()
3973/4: ws1 = WSpec(D, color_norm = 'all')
3973/5: ws1.color_norm
3973/6: ws1.init_plot()
3973/7: arange(-2.,2.01,0.2)
3973/8: arange(-2.,2.01,0.2).shape
3974/1: %run load_pui_ulysses.py
3974/2: ws.init_plot()
3974/3: ws1 = WSpec(D, color_norm = 'all')
3974/4: ws1.init_plot()
3974/5: ws
3974/6: ws.wbins
3974/7: ws.wbins[0]
3974/8: ws.wbins[0+1]
3975/1: %run load_pui_ulysses.py
3975/2: ws1 = WSpec(D, color_norm = 'all')
3975/3: ws1.init_plot()
3975/4: ws1.wbins[10]
3975/5: ws1.wbins[11]
3975/6: ws1.wbins[12]
3975/7: ws1.wbins[9]
3975/8: a = ws1.wbins[10]
3975/9: arange(-2.,2.01,0.2).shape
3975/10: arange(-2.,2.01,0.2)
3975/11: around(a,decimals=1)
3975/12: around(arange(-2.,2.01,0.2))
3975/13: around(arange(-2.,2.01,0.2),decimals=1)
3976/1: %run load_pui_ulysses.py
3976/2: ws.init_plot()
3976/3: slice = 10
3976/4: print('w_x = %2.1f - %2.1f' % (int(wbins[slice]), int(wbins[slice+1])))
3976/5: wbins = arange(-2,2.01,0.2)
3976/6: print('w_x = %2.1f - %2.1f' % (int(wbins[slice]), int(wbins[slice+1])))
3976/7: wbins(11)
3976/8: wbins[11]
3977/1: %run load_pui_ulysses.py
3977/2: ws.init_plot()
3978/1: %run load_pui_ulysses.py
3978/2: ws.init_plot()
3979/1: %run load_pui_ulysses.py
3979/2: ws.init_plot()
3980/1: %run load_pui_ulysses.py
3980/2: ws.init_plot()
3981/1: %run load_pui_ulysses.py
3981/2: ws.init_plot()
3982/1: %run load_pui_ulysses.py
3982/2: ws.init_plot()
3983/1: %run load_pui_ulysses.py
3983/2: ws.init_plot()
3984/1: cd Trajectory/
3984/2: cd..
3984/3: cd ..
3984/4: %run ul_calc_traj.py
3984/5: hg1 = [5.067,265.34-180,90.+22.5]
3984/6: hg2 = [5.065,265.36-180.,90.+22.8]
3984/7: sph2cart(hg1,deg=True)
3984/8: hg1_cart = sph2cart(hg1,deg=True)
3984/9: hg2_cart = sph2cart(hg2,deg=True)
3984/10: hg2_cart
3984/11: hg2_cart-hg1_cart
3984/12: hg1
3984/13: hg2
3984/14: hg2 - hg1
3984/15: array(hg2) - array(hg1)
3984/16: d = array(hg2) - array(hg1)
3984/17: hg_to_rtn(hg1,d,long_shift_r = 180.)
3984/18: hg1
3984/19: hg2
3984/20: d
3984/21: rtn1 = hg_to_rtn(hg1,hg1,long_shift_r = 0)
3984/22: rtn1
3984/23: rtn1 = hg_to_rtn(hg1,hg1,long_shift_r = 180)
3984/24: rtn1
3984/25: hg1
3984/26: hg2
3984/27: hg2-hg1
3984/28: pyl
3984/29: pylab.close('all')
3985/1: from uswipha import uswipha
3985/2: d = uswipha(year=1993, tf=[[1,10]])
3985/3: d.sync_swoops()
3985/4: d.sync_traj()
3985/5: d
3985/6: d.data.keys()
3985/7: d.data['lat_hg']
3985/8: d.data['long_hg']
3985/9: hg_long_1 = d.data['long_hg][0]
3985/10: hg_long_1 = d.data['long_hg'][0]
3985/11: hg_long_2 = d.data['long_hg'][4]
3985/12: hg_long_1
3985/13: hg_long_2
3985/14: d.data['long_hg']
3985/15: -22.97+22.75
3985/16: 0.058-0.067
3985/17: hg_long_1 = 265.34
3985/18: hg_long_2 = 265.36
3985/19: hg_lat_1 = -22.75
3985/20: hg_lat_2 = -22.97
3985/21: hg_r_1 = 5.067
3985/22: hg_r_2 = 5.058
3985/23: hg_1 = [hg_r_1, hg_long_1, hg_lat_1]
3985/24: hg_2 = [hg_r_2, hg_long_2, hg_lat_2]
3985/25: hg_diff = hg2 - hg1
3985/26: hg_diff = hg_2 - hg_1
3985/27: hg_2 = numpy.array([hg_r_2, hg_long_2, hg_lat_2])
3985/28: hg_1 = numpy.array([hg_r_1, hg_long_1, hg_lat_1])
3985/29: hg_diff = hg_2 - hg_1
3985/30: hg_diff
3985/31: %run ul_calc_traj.py
3985/32: rtn1 = hg_to_rtn(hg_diff, hg_2, long_shift = 0.)
3985/33: rtn1
3985/34: RTN1 = hg_to_rtn(hg_1,hg_1,long_shift=0.)
3985/35: RTN1
3985/36: RTN2 = hg_to_rtn(hg_1,hg_2,long_shift=0.)
3985/37: RTN2
3985/38: R = numpy.array([5,110,20])
3985/39: hg_1 = numpy.array([4,45,0])
3985/40: hg_2 = numpy.array([4,60,10])
3985/41: hg_delta = hg_2 - hg_1
3985/42: hg_delta
3985/43: hg_to_rtn(hg_1,R,long_shift = 0.)
3985/44: hg_to_rtn(hg_2,R,long_shift = 0.)
3985/45: hg_to_rtn(hg_delta,R,long_shift = 0.)
3985/46: hg_delta
3985/47: R
3986/1: R = numpy.array([5,110,20])
3986/2: hg_1 = numpy.array([4,45,0])
3986/3: hg_2 = numpy.array([4,60,10])
3986/4: hg_delta = hg_2 - hg_1
3986/5: hg_delta
3986/6: hg_to_rtn(hg_delta,R,long_shift = 0.)
3986/7: %run ul_calc_traj.py
3986/8: hg_to_rtn(hg_delta,R,long_shift = 0.)
3986/9: hg_to_rtn(hg_delta,R,long_shift = 0.)
3986/10: %run ul_calc_traj.py
3986/11: hg_to_rtn(hg_delta,R,long_shift = 0.)
3986/12: sph2cart()
3986/13: RTN1 = hg_to_rtn(hg_1,R,long_shift=0.)
3986/14: RTN1
3986/15: RTN2 = hg_to_rtn(hg_2,R,long_shift=0.)
3986/16: RTN2 - RTN1
3986/17: RTN1 = hg_to_rtn(hg_1,hg_1,long_shift=0.)
3986/18: RTN2 = hg_to_rtn(hg_2,hg_1,long_shift=0.)
3986/19: RTN1
3986/20: RTN2
3986/21: hg_to_rtn(numpy.array([4,-1,0]),numpy.array([5,0,0]),long_shift = 0.)
3986/22: hg_to_rtn(numpy.array([4,-1,0]),numpy.array([5,0,0]),long_shift = 0.,spherical=False)
3986/23: hg_to_rtn(numpy.array([4,-1,0]),numpy.array([5,0,0]),long_shift = 0.)
3986/24: hg_to_rtn(numpy.array([4,-14.48,0]),numpy.array([5,0,0]),long_shift = 0.)
3986/25: numpy.arccos
3986/26: numpy.arcsin(1./4.)
3986/27: numpy.arcsin(1./4.) *180./pi
3986/28: phi = numpy.arcsin(1./4.) *180./pi
3986/29: hg_to_rtn(numpy.array([4,phi,0]),numpy.array([5,0,0]),long_shift = 0.)
3986/30: sph2cart
3986/31: sph2cart([4,numpy.arcsin(1/4.),0])
3986/32: sph2cart([4,numpy.arcsin(1/4.),0],deg = True)
3986/33: phi
3986/34: sph2cart([4,-phi,0],deg = True)
3986/35: sph2cart
3986/36: r = numpy.array([4,-phi,0])
3986/37: sph2cart(r,deg = True)
3986/38: r = numpy.array([4,-phi,90])
3986/39: sph2cart(r,deg = True)
3986/40: from numpy import sin, cos, pi, array
3986/41: r
3986/42: r_vec = r
3986/43:
  r = r_vec[0]
  phi = r_vec[1]
  theta = r_vec[2]
3986/44: phi = phi/180.*pi
3986/45: phi
3986/46: r_vec = array([4,-phi,90])
3986/47: phi
3986/48: phi = numpy.arcsin(1/4.)
3986/49: phi
3986/50: phi = numpy.arcsin(1/4.)*180/phi
3986/51: phi
3986/52: phi = numpy.arcsin(1/4.)*180/pi
3986/53: phi
3986/54: r_vec = array([4,-phi,90])
3986/55:
  r = r_vec[0]
  phi = r_vec[1]
  theta = r_vec[2]
3986/56: phi = phi/180.*pi
3986/57: theta = theta/180.*pi
3986/58: r*cos(phi)*sin(theta)
3986/59: phi = numpy.arcsin(1/4.)*180/pi
3986/60: r = numpy.array([400,-phi,90])
3986/61: sph2cart(r,deg = True)
3986/62: phi = 90.
3986/63: r_vec = array([4,-phi,90])
3986/64: sph2cart(r,deg = True)
3986/65: r_vec = array([4,-pi/2.,pi/2.])
3986/66: sph2cart(r,deg = True)
3986/67: r
3986/68: r_vec
3986/69: sph2cart(r_vec)
3986/70: r_vec
3986/71: pi/2 * 180./pi
3986/72: r_vec
3986/73: phi = arcsin(0.5)
3986/74: phi
3986/75: r_vec = array([4,-phi,pi/2.])
3986/76: sph2cart(r_vec)
3986/77: arctan
3986/78: arctan(1/4)
3986/79: arctan(1/4.)
3986/80: arctan(1/4.)*180/pi
3986/81: phi = arctan(1/4.)*180/pi
3986/82: sqrt(4**2+1**2)
3986/83: hg_to_rtn(numpy.array([4.12311,-phi,0]),numpy.array([5,0,0]),long_shift = 0.)
3986/84: cd Trajectory/
3986/85: %run calc_delta_v.py
3986/86: %run calc_delta_v.py
3987/1: cd Trajectory/
3987/2: %run calc_delta_v.py
3988/1: cd Trajectory/
3988/2: %run calc_delta_v.py
3989/1: cd Trajectory/
3989/2: %run calc_delta_v.py
3990/1: cd Trajectory/
3990/2: %run calc_delta_v.py
3991/1: cd Trajectory/
3991/2: %run calc_delta_v.py
3992/1: cd Trajectory/
3992/2: %run calc_delta_v.py
3993/1: cd Trajectory/
3993/2: %run calc_delta_v.py
3993/3: data
3993/4: data[0,1]
3994/1: cd Trajectory/
3994/2: %run calc_delta_v.py
3994/3: R
3994/4: Hg_lat
3994/5: HG_lat
3994/6: HG_Lat
3994/7: HG_Long
3994/8: HG_Long
3995/1: cd Trajectory/
3995/2: %run calc_delta_v.py
3996/1: %run calc_delta_v.py
3996/2: cd Trajectory/
3996/3: %run calc_delta_v.py
3997/1: cd Trajectory/
3997/2: %run calc_delta_v.py
3997/3: pwd
3997/4: from Ulysses import *
3998/1: pwd
3998/2: cd Trajectory/
3998/3: %run calc_delta_v.py
3999/1: cd Trajectory/
3999/2: %run calc_delta_v.py
3999/3: v1 = array([1.585,98.52,1.99])
3999/4: v1 = array([1.684,103.08,1.99])
3999/5: v2 = array([1.684,103.08,1.99])
3999/6: v1 = array([1.684,103.08,1.99])
3999/7: v1 = array([1.585,98.52,1.99])
3999/8: v1
3999/9: v2
3999/10: t = 24*60*60
3999/11: a,b,c = calc_v(v1,v2,t)
4000/1: cd Trajectory/
4000/2: %run calc_delta_v.py
4000/3: v1 = array([1.585,98.52,1.99])
4000/4: v2 = array([1.684,103.08,1.99])
4000/5: t = 24*60*60
4000/6: a,b,c = calc_v(v1,v2,t)
4000/7: a
4000/8: b
4000/9: c
4000/10: v1
4000/11: v2+
4000/12: v2
4000/13: from pylib.etCoord import rotate, sph2cart, cart2sph
4000/14: sph2cart(v1)
4000/15: sph2cart(v1,deg=True)
4000/16: v1
4000/17: sph2cart(v1[0],v1[1],90-v1[2],deg=True)
4000/18: sph2cart(array(v1[0],v1[1],90-v1[2]),deg=True)
4000/19: v1_1 = array([v1[0],v1[2],90.-v1[2]])
4000/20: v1_1
4000/21: v1
4000/22: v2_1 = array([v2[0],v2[2],90.-v2[2]])
4000/23: sph2cart(v1_1,deg=True)
4000/24: sph2cart(v2_1,deg=True)
4000/25: v1_1
4000/26: v1_1 = array([v1[0],v1[1],90.-v1[2]])
4000/27: v2_1 = array([v2[0],v2[1],90.-v2[2]])
4000/28: sph2cart(v2_1,deg=True)
4000/29: sph2cart(v1_1,deg=True)
4000/30: a,b,c = calc_v(v1,v2,t)
4000/31: a
4000/32: b
4000/33: c
4000/34: a
4001/1: %run calc_delta_v.py
4001/2: cd Trajectory/
4001/3: %run calc_delta_v.py
4001/4: v1 = array([1.585,98.52,1.99])
4001/5: v2 = array([1.684,103.08,1.99])
4001/6: t = 24*60*60
4001/7: a,b,c = calc_v(v1,v2,t)
4001/8: a
4001/9: b
4001/10: c
4001/11: sqrt(a**2+b**2)
4001/12: %run calc_delta_v.py
4001/13: a,b,c = calc_v(v1,v2,t)
4001/14: a
4001/15: b
4001/16: c
4001/17: %run calc_delta_v.py
4001/18: a,b,c = calc_v(v1,v2,t)
4001/19: b
4001/20: a
4001/21: v1[0] + t*a
4001/22: v1
4001/23: v2
4001/24: v1[0] + t*b
4001/25: v1[1] + t*b
4001/26: v1[2] + t*c
4001/27: v1
4001/28: v2
4001/29: hg_to_rtn(v2,v1,long_shift_r=180)
4001/30: rtn = hg_to_rtn(v2,v1,long_shift_r=180)
4001/31: rtn
4001/32: v1 = array([1.585,203.58,-0.8])
4001/33: v3 = array([1.996,219.31,-2.52])
4001/34: v1
4001/35: v3
4001/36: v1_1 = array([v1[0],v1[1],90.-v1[2]])
4001/37: v2_1 = array([v2[0],v2[1],90.-v2[2]])
4001/38: sph2cart(v1_1,deg=True)
4001/39: from pylib.etCoord import rotate, sph2cart, cart2sph
4001/40: sph2cart(v1_1,deg=True)
4001/41: sph2cart(v2_1,deg=True)
4001/42: v1_1 = array([v1[0],v1[1]-180.,90.-v1[2]])
4001/43: v2_1 = array([v2[0],v2[1]-180.,90.-v2[2]])
4001/44: sph2cart(v1_1,deg=True)
4001/45: sph2cart(v2_1,deg=True)
4001/46: v1
4001/47: v2
4001/48: v2 = array([1.996,219.31,-2.52])
4001/49: v2_1 = array([v2[0],v2[1]-180.,90.-v2[2]])
4001/50: v1
4001/51: v2
4001/52: sph2cart(v2_1,deg=True)
4001/53: sph2cart(v1_1,deg=True)
4001/54: v1
4001/55: v2
4001/56: %run calc_delta_v.py
4001/57: a,b,c = calc_v(v1,v2,t)
4001/58: %run calc_delta_v.py
4001/59: a,b,c = calc_v(v1,v2,t)
4002/1: cd Trajectory/
4002/2: %run calc_delta_v.py
4002/3: v1 = array([1.585,203.58,-0.8])
4002/4: v2 = array([1.996,219.31,-2.52])
4002/5: a,b,c = calc_v(v1,v2,t)
4002/6: t = 24*60*60
4002/7: a,b,c = calc_v(v1,v2,t)
4002/8: vec1_RTN
4002/9: %run calc_delta_v.py
4002/10: RTN1, RTN2 = calc_v(v1,v2,t)
4002/11: TRN1
4002/12: RTN1
4002/13: RTN2
4002/14: RTN2 - RTN1
4002/15: d = RTN2 - RTN1
4002/16: d/t
4002/17: 3.88229e-06 * dt + RTN1[0]
4002/18: 3.88229e-06 * t + RTN1[0]
4002/19: RTN2
4003/1: cd Trajectory/
4003/2: %run calc_delta_v.py
4003/3: v1 = array([1.585,203.58,-0.8])
4003/4: v2 = array([1.996,219.31,-2.52])
4003/5: v2 - v1
4003/6: (v2 - v1) /t * 1.496e08
4003/7: (v2 - v1) /(24*60*60) * 1.496e08
4003/8: 149497071.034
4003/9: 149497071.034 - 149301115.851
4003/10: d = 149497071.034 - 149301115.851
4003/11: d/t
4003/12: t = 24*60*60
4003/13: d/t
4003/14: clear
4003/15: v1 = array([1.585,203.58,-0.8])
4003/16: v2 = array([1.996,219.31,-2.52])
4003/17: delta_hg = v2 -v1
4003/18: delta_hg
4003/19: rtn1 = hg_to_rtn(v1, v1, long_shift = 180., long_shift_r= 180.)
4003/20: rtn2 = hg_to_rtn(v2, v1, long_shift = 180., long_shift_r= 180.)
4003/21: rtn1
4003/22: rtn2
4003/23: rtn_diff = rtn2 - rtn1
4003/24: rtn_diff
4003/25: sum(rtn_diff**2)
4003/26: sqrt(sum(rtn_diff**2))
4003/27: sqrt(rtn_diff[0]**2+rtn_diff[1]**2 + rtn_diff[2]**2)
4003/28: sqrt(sum(delta_hg**2))
4003/29: v1
4003/30: from pylib.etCoord import rotate, sph2cart, cart2sph
4003/31: v1_1 = array([v1[0],v1[1]-180.,90.-v1[2]])
4003/32: v2_1 = array([v2[0],v2[1]-180.,90.-v2[2]])
4003/33: v1_c = sph2cart(v1_1,deg=True)
4003/34: v2_c = sph2cart(v2_1, deg =True)
4003/35: v1_c
4003/36: v2_c
4003/37: hg_dif = v2_c - v1_c
4003/38: hg_diff = v2_c - v1_c
4003/39: sqrt(sum(hg_diff**2))
4003/40: sqrt(sum(rtn_diff**2))
4003/41: clear
4003/42: v1 = array([1.059,155.19,4.29])
4003/43: v2 = array([1.065,156.38,4.19])
4003/44: v1_1 = array([v1[0],v1[1]-180.,90.-v1[2]])
4003/45: v2_1 = array([v2[0],v2[1]-180.,90.-v2[2]])
4003/46: v1_c = sph2cart(v1_1,deg=True)
4003/47: v2_c = sph2cart(v2_1, deg =True)
4003/48: v1_c
4003/49: hg_diff = v2_c - v1_c
4003/50: hg_diff
4003/51: sqrt(sum(hg_diff**2))
4003/52: sqrt(sum(v1_c**2))
4003/53: sqrt(sum(v2_c**2))
4003/54: t = 24*60*60
4003/55: hg_diff /t *1.496e08
4003/56: d2 = hg_diff /t *1.496e08
4003/57: sqrt(sum(d2**2))
4003/58: %run calc_delta_v.py
4003/59: a,b,c = calc_v(v1,v2,t)
4003/60: a
4003/61: b
4003/62: c
4003/63: sqrt(a**2+b**2+c**2)
4004/1: cd Trajectory/
4004/2: %run calc_delta_v.py
4005/1: cd Trajectory/
4005/2: %run calc_delta_v.py
4005/3: vx_list
4005/4: v_abs
4005/5: i
4005/6: R[i]
4005/7: R[0:10]
4006/1: cd Tr
4006/2: cd Trajectory/
4006/3: %run traj_pooled.py
4007/1: %run traj_pooled.py
4007/2: cd Trajectory/
4007/3: %run traj_pooled.py
4007/4: v_u.shape
4007/5: r_u.shape
4007/6: fin_u.shape
4007/7: hg_lat_u.shape
4007/8: sep_u.shape
4007/9: v_u[0]
4007/10: r_u[0]
4008/1: cd Trajectory/
4008/2: %run traj_pooled.py
4009/1: cd Trajectory/
4009/2: %run traj_pooled.py
4009/3: diff
4009/4: plt
4009/5: plt.plot(range(len(diff)),diff)
4009/6: v:abs
4009/7: v_abs
4009/8: v_abs[0:10]
4009/9: v_u[0:10]
4009/10: pylab.show()
4009/11: %run traj_pooled.py
4009/12: plt.plot(range(len(diff)),diff)
4009/13: plt.plot(range(len(v_abs)),v_abs)
4009/14: plt.show()
4009/15: pylab.show()
4009/16: pylab.close('all')
4009/17: plt.plot(range(len(v_abs)),v_abs)
4009/18: pylab.close('all')
4009/19: plt.plot(range(len(vx)),vx)
4009/20: plt.plot(range(len(vx_list)),vx_list)
4009/21: plt.plot(range(len(vy_list)),vy_list)
4010/1: cd Trajectory/
4010/2: %run traj_pooled.py
4010/3: %run traj_pooled.py
4011/1: cd Trajectory/
4011/2: %run traj_pooled.py
4012/1: cd Trajectory/
4012/2: %run traj_pooled.py
4013/1: cd Trajectory/
4013/2: %run traj_pooled.py
4014/1: cd Trajectory/
4014/2: %run traj_pooled.py
4015/1: cd Trajectory/
4015/2: %run traj_pooled.py
4016/1: cd Trajectory/
4016/2: %run traj_pooled.py
4016/3: v1 = array([1.059,155.19,4.29])
4016/4: v2 = array([1.065,156.38,4.19])
4016/5: calc_v(v1,v2,t)
4016/6: t = 24*60*60
4016/7: calc_v(v1,v2,t)
4016/8:
for i in range(4056,4057):
    print(i)
4017/1: cd Trajectory/
4017/2: %run traj_pooled.py
4018/1: %run traj_pooled.py
4018/2: cd Trajectory/
4018/3: %run traj_pooled.py
4018/4: diff
4018/5: v_abs
4018/6: v_x
4018/7: vx
4018/8: vx_list
4019/1: cd Trajectory/
4019/2: %run traj_pooled.py
4020/1: cd Trajectory/
4020/2: %run traj_pooled.py
4021/1: cd Trajectory/
4021/2: %run traj_pooled.py
4022/1: cd Trajectory/
4022/2: %run traj_pooled.py
4023/1: %run traj_pooled.py
4024/1: cd Trajectory/
4024/2: %run traj_pooled.py
4025/1: cd Trajectory/
4025/2: %run traj_pooled.py
4026/1: %run traj_pooled.py
4026/2: v_abs
4026/3: v_x
4026/4: vx
4027/1: %run traj_pooled.py
4028/1: %run traj_pooled.py
4029/1: %run traj_pooled.py
4029/2: vx
4030/1: %run traj_pooled.py
4030/2: %run traj_pooled.py
4030/3: delta_RTN
4030/4: %run traj_pooled.py
4031/1: %run traj_pooled.py
4032/1: %run traj_pooled.py
4032/2: write_new_file()
4034/1: %run traj_pooled.py
4034/2: write_new_file()
4036/1: %run traj_pooled.py
4036/2: write_new_file()
4037/1: %run traj_pooled.py
4037/2: write_new_file()
4038/1: %run traj_pooled.py
4038/2: write_new_file()
4039/1: %run traj_pooled.py
4039/2: write_new_file()
4040/1: %run traj_pooled.py
4040/2: write_new_file()
4041/1: %run traj_pooled.py
4041/2: write_new_file()
4042/1: %run traj_pooled.py
4042/2: write_new_file()
4043/1: %run traj_pooled.py
4043/2: write_new_file()
4044/1: %run traj_pooled.py
4044/2: write_new_file()
4045/1: %run traj_pooled.py
4045/2: %run traj_pooled.py
4045/3: write_new_file()
4046/1: %run traj_pooled.py
4046/2: write_new_file()
4047/1: %run traj_pooled.py
4047/2: write_new_file()
4048/1: %run traj_pooled.py
4048/2: write_new_file()
4049/1: %run traj_pooled.py
4049/2: write_new_file()
4050/1: %run traj_pooled.py
4050/2: write_new_file()
4051/1: %run traj_pooled.py
4051/2: write_new_file()
4052/1: %run traj_pooled.py
4052/2: write_new_file()
4053/1: %run traj_pooled.py
4053/2: write_new_file()
4054/1: %run traj_pooled.py
4054/2: write_new_file()
4055/1: %run traj_pooled.py
4055/2: write_new_file()
4056/1: %run traj_pooled.py
4056/2: write_new_file()
4057/1: %run traj_pooled.py
4057/2: write_new_file()
4058/1: %run traj_pooled.py
4058/2: write_new_file()
4059/1: %run traj_pooled.py
4059/2: write_new_file()
4060/1: %run traj_pooled.py
4060/2: write_new_file()
4061/1: %run traj_pooled.py
4061/2: write_new_file()
4062/1: %run traj_pooled.py
4062/2: write_new_file()
4063/1: %run traj_pooled.py
4063/2: write_new_file()
4064/1: %run traj_pooled.py
4064/2: write_new_file()
4065/1: %run traj_pooled.py
4065/2: write_new_file()
4066/1: %run traj_pooled.py
4066/2: write_new_file()
4067/1: %run traj_pooled.py
4067/2: write_new_file()
4067/3: %run ul_calc_traj.py
4067/4: hc_vec = array([1.059,49.88,1.2])
4067/5: hc_to_hg(hc_vec)
4068/1: %run traj_pooled.py
4069/1: %run traj_pooled.py
4070/1: %run traj_pooled.py
4071/1: %run traj_pooled.py
4072/1: %run traj_pooled.py
4073/1: %run traj_pooled.py
4074/1: hc_to_hg(hc_vec)
4074/2: %run traj_pooled.py
4074/3: write_new_file()
4075/1: %run traj_pooled.py
4075/2: write_new_file()
4076/1: %run traj_pooled.py
4076/2: write_new_file()
4076/3: plt.plot(range(0,100),hg_long_h[4000:4100])
4076/4: plt.plot(range(4000,4100),hg_long_h[4000:4100])
4076/5: pylab.close('all')
4076/6: plt.plot(range(4000,4100),hg_long_h[4000:4100])
4076/7: %run traj_pooled.py
4076/8: plt.plot(range(4000,4100),hg_long_h[4000:4100])
4078/1: %run traj_pooled.py
4078/2: write_new_file()
4079/1: %run traj_pooled.py
4079/2: write_new_file()
4080/1: %run traj_pooled.py
4080/2: write_new_file()
4080/3: plt.plot(range(len(v)),v)
4080/4: plt.plot(range(len(v)),v_abs)
4080/5: plt.plot(range(len(v_abs)),v_abs)
4080/6: plt.plot(range(len(vx_list)),vx_list)
4080/7: plt.plot(range(len(vx)),vx)
4080/8: plt.plot(range(len(vr_list)),vr_list)
4080/9: plt.plot(range(len(vt_list)),vt_list)
4080/10: plt.plot(range(len(vn_list)),vn_list)
4081/1: %run uswipha.py
4082/1: %run uswipha
4082/2: from DataLoader import uswipha
4083/1: from DataLoader import uswipha
4084/1: from DataLoader import uswipha
4085/1: from DataLoader import uswipha
4086/1: %run uswipha
4086/2: from DataLoader import uswipha
4086/3: u = uswipha(year=1994,tf=[[1,10]])
4086/4: from DataLoader.uswipha import uswipha
4086/5: u = uswipha(year=1994,tf=[[1,10]])
4086/6: u.sync_swoops()
4086/7: u.sync_traj()
4086/8: traj
4087/1: from DataLoader.uswipha import uswipha
4087/2: u = uswipha(year=1994,tf=[[1,10]])
4087/3: u.sync_swoops()
4087/4: u.data
4087/5: u.sync_traj()
4087/6: u.traj
4087/7: u.traj.data
4088/1: from DataLoader.uswipha import uswipha
4088/2: u = uswipha(year=1994,tf=[[1,10]])
4088/3: u.sync_swoops()
4088/4: u.sync_traj()
4088/5: u.data
4089/1: from Trajectory.ulysses_traj import ulysses_traj
4089/2: traj = ulysses_traj(year=1993,tf='all')
4089/3: traj
4089/4: traj.data
4089/5: traj.data.keys
4089/6: traj.data
4089/7: traj.data(keys)
4089/8: traj.keys
4089/9: pwd
4089/10: from DataLoader.pui_ulysses import plot_eigen_velocities
4089/11: plot_eigen_velocities(traj)
4089/12: from DataLoader.pui_ulysses import plot_eigen_velocities
4089/13: plot_eigen_velocities(traj)
4090/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4090/2: from Trajectory.ulysses_traj import ulysses_traj
4090/3: traj = ulysses_traj(year=1993,tf='all')
4090/4: plot_eigen_velocities(traj)
4090/5: plot_eigen_velocities(traj)
4090/6: from DataLoader.pui_ulysses import plot_eigen_velocities
4090/7: plot_eigen_velocities(traj)
4091/1: from Trajectory.ulysses_traj import ulysses_traj
4091/2: traj = ulysses_traj(year=1993,tf='all')
4091/3: from DataLoader.pui_ulysses import plot_eigen_velocities
4091/4: plot_eigen_velocities(traj)
4092/1: from Trajectory.ulysses_traj import ulysses_traj
4092/2: traj = ulysses_traj(year=1993,tf='all')
4092/3: from DataLoader.pui_ulysses import plot_eigen_velocities
4092/4: plot_eigen_velocities(traj)
4092/5: traj
4092/6: traj.data
4092/7: traj.keys
4092/8: traj.calc_d90()
4092/9: traj.keys
4092/10: traj.data['d90']
4093/1: from Trajectory.ulysses_traj import ulysses_traj
4093/2: traj = ulysses_traj(year=1993,tf='all')
4093/3: traj.calc_d90()
4093/4: traj.keys
4094/1: from Trajectory.ulysses_traj import ulysses_traj
4094/2: traj = ulysses_traj(year=1993,tf='all')
4094/3: traj.keys
4096/1: from Trajectory.ulysses_traj import ulysses_traj
4096/2: traj = ulysses_traj(year=1993,tf='all')
4096/3: traj.data
4096/4: traj.data['d90']
4096/5: traj.calc_d90()
4096/6: traj.data['d90']
4097/1: from Trajectory.ulysses_traj import ulysses_traj
4097/2: from DataLoader.pui_ulysses import plot_eigen_velocities
4097/3: plot_eigen_velocities()
4097/4: from DataLoader.pui_ulysses import plot_eigen_velocities
4097/5: plot_eigen_velocities()
4098/1: plot_eigen_velocities()
4098/2: from DataLoader.pui_ulysses import plot_eigen_velocities
4098/3: plot_eigen_velocities()
4099/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4099/2: plot_eigen_velocities()
4100/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4100/2: plot_eigen_velocities()
4101/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4101/2: plot_eigen_velocities()
4102/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4102/2: plot_eigen_velocities()
4103/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4103/2: plot_eigen_velocities()
4103/3: traj.data
4103/4: from Trajectory.ulysses_traj import ulysses_traj
4103/5: traj = ulysses_traj(year=1993,tf='all')
4103/6: traj.data
4103/7: traj.data[keys]
4103/8: traj.data(keys)
4103/9: traj.data['keys']
4103/10: traj.keys
4103/11: traj.data['DOY]
4103/12: traj.data['DOY']
4103/13: traj.data['DOY_E']
4103/14: traj.data['v_R']
4103/15: traj.data['v']
4103/16: traj.data['year']
4103/17: traj.data['YEAR']
4103/18: traj.keys
4103/19: traj = ulysses_traj(year=1993,tf='all')
4103/20: traj.data#
4103/21: traj.data['v_R']
4104/1: from Trajectory.ulysses_traj import ulysses_traj
4104/2: plot_eigen_velocities()
4104/3: from DataLoader.pui_ulysses import plot_eigen_velocities
4104/4: plot_eigen_velocities()
4105/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4105/2: plot_eigen_velocities()
4105/3: from DataLoader.pui_ulysses import plot_eigen_velocities
4105/4: plot_eigen_velocities()
4106/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4106/2: plot_eigen_velocities()
4107/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4107/2: plot_eigen_velocities()
4108/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4108/2: plot_eigen_velocities()
4109/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4109/2: plot_eigen_velocities()
4110/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4110/2: plot_eigen_velocities()
4111/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4111/2: plot_eigen_velocities()
4112/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4112/2: plot_eigen_velocities()
4113/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4113/2: plot_eigen_velocities()
4114/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4114/2: plot_eigen_velocities()
4115/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4115/2: plot_eigen_velocities()
4116/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4116/2: plot_eigen_velocities()
4117/1: plot_eigen_velocities()
4117/2: from DataLoader.pui_ulysses import plot_eigen_velocities
4117/3: plot_eigen_velocities()
4118/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4118/2: plot_eigen_velocities()
4119/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4119/2: plot_eigen_velocities()
4119/3: from Trajectory.ulysses_traj import ulysses_traj
4119/4: traj = ulysses_traj(year=1996,tf=[[1,10]])
4119/5: traj.keyx
4119/6: traj.keyy
4119/7: traj.keys
4119/8: traj.data['v_R']
4119/9:
for i in range(3):
    vec1 = array(traj.data['R'],traj.data['HG_Long'],traj.data['HG_Lat])
4119/10:
for i in range(3):
    vec1 = array(traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i])
    vec2 = array(traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1])
4119/11:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
4120/1: from Trajectory.ulysses_traj import ulysses_traj
4120/2: traj = ulysses_traj(year=1996,tf=[[1,10]])
4120/3:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
4120/4:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4120/5: from Trajectory.ul_calc_traj import calc_v
4120/6:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4122/1: from Trajectory.ul_calc_traj import calc_v
4122/2: from Trajectory.ulysses_traj import ulysses_traj
4122/3: traj = ulysses_traj(year=1996,tf=[[1,10]])
4122/4:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4122/5: from Trajectory.ul_calc_traj import calc_v
4122/6:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4123/1: from Trajectory.ul_calc_traj import calc_v
4123/2: from Trajectory.ulysses_traj import ulysses_traj
4123/3: traj = ulysses_traj(year=1996,tf=[[1,10]])
4123/4:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4123/5: d
4123/6: d
4124/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4124/2: plot_eigen_velocities()
4124/3: from Trajectory.ulysses_traj import ulysses_traj
4124/4: from Trajectory.ul_calc_traj import calc_v
4124/5:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4124/6: traj = ulysses_traj(year=1996,tf=[[1,10]])
4125/1: %run Trajectory/traj_pooled.py
4126/1: %run Trajectory/traj_pooled.py
4126/2: pwd
4126/3: cd Trajectory/
4126/4: %run Trajectory/traj_pooled.py
4126/5: %run traj_pooled.py
4127/1: cd Trajectory/
4127/2: %run traj_pooled.py
4128/1: cd Trajectory/
4128/2: %run traj_pooled.py
4128/3: write_new_file()
4129/1: cd Trajectory/
4129/2: %run traj_pooled.py
4129/3: write_new_file()
4130/1: %run traj_pooled.py
4130/2: cd Trajectory/
4130/3: %run traj_pooled.py
4130/4: write_new_file()
4131/1: cd Trajectory/
4131/2: %run traj_pooled.py
4131/3: cd Trajectory/
4131/4: write_new_file()
4131/5: from DataLoader.pui_ulysses import plot_eigen_velocities
4131/6: cd ..
4131/7: from DataLoader.pui_ulysses import plot_eigen_velocities
4131/8: plot_eigen_velocities()
4132/1: from DataLoader.pui_ulysses import plot_eigen_velocities
4132/2: plot_eigen_velocities()
4133/1: %run traj_pooled.py
4133/2: cd Trajectory/
4133/3: %run traj_pooled.py
4133/4: write_new_file()
4134/1: cd Trajectory/
4134/2: %run traj_pooled.py
4134/3: cd Trajectory/
4134/4: write_new_file()
4135/1: cd Trajectory/
4135/2: cd Trajectory/
4135/3: %run traj_pooled.py
4135/4: write_new_file()
4136/1: cd Trajectory/
4136/2: %run traj_pooled.py
4136/3: write_new_file()
4139/1: %run test_dies_das.py
4139/2: checken_ob_r()
4140/1: checken_ob_r()
4140/2: %run test_dies_das.py
4140/3: checken_ob_r()
4140/4: traj
4141/1: %run test_dies_das.py
4141/2: traj
4141/3: checken_ob_r()
4142/1: %run test_dies_das.py
4142/2: checken_ob_r()
4143/1: %run test_dies_das.py
4143/2: checken_ob_r()
4144/1: %run test_dies_das.py
4144/2: checken_ob_r()
4145/1: %run test_dies_das.py
4145/2: checken_ob_r()
4146/1: %run test_dies_das.py
4146/2: checken_ob_r()
4147/1: %run test_dies_das.py
4147/2: checken_ob_r()
4148/1: %run test_dies_das.py
4148/2: checken_ob_r()
4149/1: %run test_dies_das.py
4149/2: checken_ob_r()
4150/1: %run test_dies_das.py
4150/2: checken_ob_r()
4151/1: %run test_dies_das.py
4151/2: checken_ob_r()
4152/1: %run test_dies_das.py
4152/2: checken_ob_r()
4153/1: %run test_dies_das.py
4153/2: checken_ob_r()
4154/1: cd Trajectory/
4154/2: %run traj_pooled.py
4154/3: write_new_file()
4154/4: %run traj_pooled.py
4154/5: write_new_file()
4155/1: %run traj_pooled.py
4155/2: cd Trajectory/
4155/3: %run traj_pooled.py
4155/4: write_new_file()
4157/1: from DataLoader.uswipha import uswipha
4157/2: u = uswipha(year=1994,tf=[[1,10]])
4157/3: u.sync_traj()
4157/4: u.sync_swoops()
4157/5: u.data
4157/6: u.keys
4157/7: u.data[keys]+
4157/8: u.data.keys
4157/9: u.data.keys()
4157/10: u.data['r']
4157/11: from DataLoader.pui_ulysses import plot_eigen_velocities
4157/12: plot_eigen_velocities()
4157/13:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4157/14: traj = ulysses_traj(year=1996,tf=[[1,10]])
4157/15: from Trajectory.ulysses_traj import ulysses_traj
4157/16: traj = ulysses_traj(year=1996,tf=[[1,10]])
4157/17:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4157/18: from Trajectory.ul_calc_traj import calc_v
4157/19: from Trajectory.ul_calc_traj import calc_v
4157/20:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4158/1: from Trajectory.ul_calc_traj import calc_v
4158/2: from Trajectory.ulysses_traj import ulysses_traj
4158/3: traj = ulysses_traj(year=1996,tf=[[1,10]])
4158/4:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4158/5:
for i in range(1):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4158/6:
for i in range(1):
    vec1 = array([traj.data['R_km'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R_km'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4159/1: cd Trajectory/
4159/2: %run traj_pooled.py
4160/1: cd Trajectory/
4160/2: %run traj_pooled.py
4160/3: write_new_file()
4161/1: %run traj_pooled.py
4161/2: cd Trajectory/
4161/3: %run traj_pooled.py
4161/4: write_new_file()
4161/5: %run traj_pooled.py
4161/6: write_new_file()
4162/1: %run traj_pooled.py
4162/2: cd Trajectory/
4162/3: %run traj_pooled.py
4162/4: write_new_file()
4162/5: %run traj_pooled.py
4162/6: write_new_file()
4162/7: %run traj_pooled.py
4162/8: write_new_file()
4162/9: %run traj_pooled.py
4162/10: write_new_file()
4163/1: cd Trajectory/
4163/2: %run traj_pooled.py
4163/3: write_new_file()
4163/4: %run traj_pooled.py
4163/5: write_new_file()
4163/6: %run traj_pooled.py
4163/7: write_new_file()
4163/8: %run traj_pooled.py
4163/9: write_new_file()
4163/10: %run traj_pooled.py
4163/11: write_new_file()
4163/12: %run traj_pooled.py
4163/13: write_new_file()
4163/14: %run traj_pooled.py
4163/15: write_new_file()
4163/16: %run traj_pooled.py
4163/17: write_new_file()
4163/18: %run traj_pooled.py
4163/19: write_new_file()
4163/20: %run traj_pooled.py
4163/21: write_new_file()
4163/22: %run traj_pooled.py
4163/23: write_new_file()
4163/24: %run traj_pooled.py
4163/25: write_new_file()
4163/26: %run traj_pooled.py
4163/27: write_new_file()
4163/28: %run traj_pooled.py
4163/29: write_new_file()
4163/30: %run traj_pooled.py
4163/31: write_new_file()
4163/32: %run traj_pooled.py
4163/33: write_new_file()
4163/34: %run traj_pooled.py
4163/35: write_new_file()
4163/36: %run traj_pooled.py
4163/37: write_new_file()
4164/1: from Trajectory.ulysses_traj import ulysses_traj
4164/2: from Trajectory.ul_calc_traj import calc_v
4164/3: traj = ulysses_traj(year=1996,tf=[[1,10]])
4164/4: traj.data
4164/5: traj.keys
4164/6:
for i in range(1):
    vec1 = array([traj.data['R_km'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R_km'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4165/1: from Trajectory.ul_calc_traj import calc_v
4165/2: from Trajectory.ulysses_traj import ulysses_traj
4165/3: traj = ulysses_traj(year=1996,tf=[[1,10]])
4165/4:
for i in range(1):
    vec1 = array([traj.data['R_km'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R_km'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4165/5:
for i in range(3):
    vec1 = array([traj.data['R_km'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R_km'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4166/1: from Trajectory.ulysses_traj import ulysses_traj
4166/2: from Trajectory.ul_calc_traj import calc_v
4166/3: traj = ulysses_traj(year=1996,tf=[[1,10]])
4166/4:
for i in range(3):
    vec1 = array([traj.data['R_km'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R_km'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4166/5:
for i in range(3):
    vec1 = array([traj.data['R'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4166/6:
for i in range(3):
    vec1 = array([traj.data['R_km'][i],traj.data['HG_Long'][i],traj.data['HG_Lat'][i]])
    vec2 = array([traj.data['R_km'][i+1],traj.data['HG_Long'][i+1],traj.data['HG_Lat'][i+1]])
    calc_v(vec1,vec2,24*60*60)
4166/7: from DataLoader.pui_ulysses import plot_eigen_velocities
4166/8: plot_eigen_velocities()
4167/1: cd Trajectory/
4167/2: %run traj_pooled.py
4167/3: from Trajectory.ulysses_traj import ulysses_traj
4167/4: cd ..
4167/5: from Trajectory.ulysses_traj import ulysses_traj
4167/6: from Trajectory.ul_calc_traj import calc_v
4167/7: traj = ulysses_traj(year=1996,tf=[[1,10]])
4168/1: %run test_dies_das.py
4168/2: analyse_why_eigen_v_wackelt()
4169/1: %run test_dies_das.py
4169/2: analyse_why_eigen_v_wackelt()
4170/1: %run test_dies_das.py
4170/2: analyse_why_eigen_v_wackelt()
4170/3: from DataLoader.pui_ulysses import plot_eigen_velocities
4170/4: plot_eigen_velocities()
4170/5: analyse_why_eigen_v_wackelt()
4170/6: %run test_dies_das.py
4170/7: analyse_why_eigen_v_wackelt()
4171/1: %run test_dies_das.py
4171/2: analyse_why_eigen_v_wackelt()
4171/3: %run test_dies_das.py
4172/1: %run test_dies_das.py
4172/2: analyse_why_eigen_v_wackelt(R='AU')
4172/3: analyse_why_eigen_v_wackelt(R='km')
4173/1: %run test_dies_das.py
4173/2: analyse_why_eigen_v_wackelt(R='km')
4174/1: %run test_dies_das.py
4174/2: analyse_why_eigen_v_wackelt(R='AU')
4176/1: %run test_dies_das.py
4176/2: analyse_why_eigen_v_wackelt(R='AU')
4176/3: analyse_why_eigen_v_wackelt(R='km')
4176/4: analyse_why_eigen_v_wackelt(R='AU')
4177/1: %run test_dies_das.py
4177/2: %run test_dies_das.py
4177/3: analyse_why_eigen_v_wackelt(R='km')
4178/1: analyse_why_eigen_v_wackelt(R='km')
4178/2: %run test_dies_das.py
4178/3: analyse_why_eigen_v_wackelt(R='km')
4179/1: analyse_why_eigen_v_wackelt(R='km')
4179/2: %run test_dies_das.py
4179/3: analyse_why_eigen_v_wackelt(R='km')
4180/1: %run test_dies_das.py
4180/2: analyse_why_eigen_v_wackelt(R='km')
4180/3: analyse_why_eigen_v_wackelt(R='AU')
4181/1: analyse_why_eigen_v_wackelt(R='km')
4182/1: %run test_dies_das.py
4182/2: analyse_why_eigen_v_wackelt(R='km')
4183/1: %run test_dies_das.py
4183/2: analyse_why_eigen_v_wackelt(R='km')
4184/1: %run test_dies_das.py
4184/2: analyse_why_eigen_v_wackelt(R='km')
4184/3: analyse_why_eigen_v_wackelt(R='AU')
4185/1: %run test_dies_das.py
4185/2: analyse_why_eigen_v_wackelt(R='AU')
4185/3: analyse_why_eigen_v_wackelt(R='km')
4185/4: %run test_dies_das.py
4185/5: analyse_why_eigen_v_wackelt(R='km')
4186/1: %run test_dies_das.py
4186/2: analyse_why_eigen_v_wackelt(R='km')
4186/3: %run test_dies_das.py
4186/4: analyse_why_eigen_v_wackelt(R='km')
4186/5: %run test_dies_das.py
4186/6: analyse_why_eigen_v_wackelt(R='km')
4187/1: %run test_dies_das.py
4187/2: analyse_why_eigen_v_wackelt(R='km')
4188/1: %run test_dies_das.py
4188/2: analyse_why_eigen_v_wackelt(R='km')
4189/1: %run test_dies_das.py
4189/2: analyse_why_eigen_v_wackelt(R='km')
4190/1: %run test_dies_das.py
4190/2: analyse_why_eigen_v_wackelt(R='km')
4191/1: %run test_dies_das.py
4191/2: analyse_why_eigen_v_wackelt(R='km')
4191/3: analyse_why_eigen_v_wackelt(R='AU')
4192/1: analyse_why_eigen_v_wackelt(R='km')
4192/2: %run test_dies_das.py
4192/3: analyse_why_eigen_v_wackelt(R='AU')
4192/4: analyse_why_eigen_v_wackelt(R='km')
4192/5: from DataLoader.pui_ulysses import plot_eigen_velocities
4192/6: plot_eigen_velocities()
4193/1: %run test_dies_das.py
4193/2: analyse_why_eigen_v_wackelt(R='km')
4194/1: %run test_dies_das.py
4194/2: analyse_why_eigen_v_wackelt(R='km')
4194/3: from DataLoader.pui_ulysses import plot_eigen_velocities
4194/4: plot_eigen_velocities()
4194/5: analyse_why_eigen_v_wackelt(R='AU')
4194/6: %run Trajectory/ul_calc_traj.py
4194/7: hc_vec_AU = array([1.059,49.88,1.2])
4194/8: hc_vec_km = array([158468424.4,49.88,1.2])
4194/9: hc_vec_AU/hc_vec_km
4194/10: hc_vec_AU/hc_vec_km[0]**-1
4194/11: AU2km = 149597870.8
4194/12: AU2km
4194/13: 1.059*AU2km
4194/14: hc_vec_km[0] / AU2km
4194/15: hc_to_hg(hc_vec_AU)
4194/16: hc_to_hg(hc_vec_km)
4194/17: hg_vec_AU = array([1.059, 155.19, 4.29])
4194/18: hg_vec_km = array([158468424.4, 155.19, 4.29])
4194/19: hg_to_hc(hg_vec_km)
4194/20: hg_to_hc(hg_vec_AU)
4194/21: %run DataLoader/uswiutils.py
4194/22: getvelocity(4,1,arange(50))
4195/1: %run load_pui_ulysses.py
4196/1: %run load_pui_ulysses.py
4197/1: %run load_pui_ulysses.py
4197/2: d
4197/3: d.data
4198/1: %run load_pui_ulysses.py
4199/1: %run load_pui_ulysses.py
4200/1: %run load_pui_ulysses.py
4201/1: %run load_pui_ulysses.py
4202/1: %run load_pui_ulysses.py
4202/2: D.temp
4202/3: D
4203/1: D.temp
4203/2: %run load_pui_ulysses.py
4203/3: D.temp.shape
4203/4: D.vspace.shape
4203/5: D.aspphi.shape
4203/6: D.asptheta.shape
4203/7: from DataLoader.pui_ulysses import plot_eigen_velocities
4203/8: plot_eigen_velocities()
4203/9: 630/600.
4204/1: %run load_pui_ulysses.py
4205/1: %run load_pui_ulysses.py
4206/1: %run load_pui_ulysses.py
4207/1: %run load_pui_ulysses.py
4208/1: %run load_pui_ulysses.py
4209/1: %run load_pui_ulysses.py
4209/2: D.vspace
4210/1: %run load_pui_ulysses.py
4211/1: %run load_pui_ulysses.py
4211/2: D._add_3Dv()
4211/3: D.vspace.shape
4211/4: D.vspace[2,2,20,2,2,2,0]
4212/1: %run load_pui_ulysses.py
4212/2: D.phiind
4213/1: %run load_pui_ulysses.py
4213/2: D._add_3Dv()
4213/3: D.phiind
4213/4: D.phiind.shape
4213/5: D.d.data['vr_sc'].shape
4214/1: %run load_pui_ulysses.py
4214/2: D._add_3Dv()
4215/1: %run load_pui_ulysses.py
4215/2: D._add_3Dv()
4216/1: D._add_3Dv()
4216/2: %run load_pui_ulysses.py
4216/3: D._add_3Dv()
4216/4: D.vx
4216/5: d.data['vx']
4216/6: d.data['vx3']
4216/7: d.data['vx3'].shape
4216/8: d.data['vx'].shape
4216/9: d.data['vx2'].shape
4216/10: d.data['vx2']
4217/1: %run load_pui_ulysses.py
4217/2: d.data
4217/3: d.data-shape
4217/4: d.data.shape
4217/5: d.data['year'].shape
4217/6: phiind = searchsorted(D.aspphi, around(D.d.get_data('Master',"aspphi")))
4217/7: phiind
4217/8: phiind.shape
4217/9: testind = [1]
4217/10: D.vspace[testind,testind,testind,testind,testind,0]
4217/11: D.d.data['vr_sc'][ß]
4217/12: D.d.data['vr_sc'][0]
4217/13: D.vspace[testind,testind,testind,testind,testind,0] + 1.
4217/14: testind = [1,1,2]
4217/15: D.vspace[testind,testind,testind,testind,testind,0]
4217/16: testind = [0,1,0]
4217/17: D.vspace[testind,testind,testind,testind,testind,0]
4217/18: D.vspace[testind,testind,testind,testind,testind,0] + [1,1,1]
4217/19: D.vspace[testind,testind,testind,testind,testind,0][0] + [1,1,1]
4218/1: %run load_pui_ulysses.py
4218/2: D.d.data['vr_sc']
4218/3: D.d.data['vx']
4218/4: D._add_3Dv()
4218/5: D.d.data['vx']
4218/6: D.d.data['vx2']
4218/7: D.d.data['vx3']
4218/8: D.d.data['vr_sc']
4218/9: -313.193 - 9.65
4219/1: %run load_pui_ulysses.py
4219/2: self.vr
4219/3: D.vr
4219/4: searchsorted(D.vr, around(D.d.get_data('Master', "vr_sc")))
4219/5: D.vr
4219/6: D.d.get_data('Master','vr_sc')
4219/7: searchsorted(D.vr, [-11,-10,-10.5,-9.5,-9.0])
4219/8: searchsorted(D.vr, [-11,-10.5,10.,-9.5,-9.0])
4219/9: searchsorted(D.vr, [-11,-10.5,-10.,-9.5,-9.0])
4219/10: searchsorted(D.vr, [-11,-10.5,-10.,-9.5,-9.0,8.5])
4219/11: searchsorted(D.vr, [-11,-10.5,-10.,-9.5,-9.0,-8.5])
4219/12: D._add_3Dv()
4219/13: D.d.data['vx'][0]
4219/14: D.d.data['vx2'][0]
4219/15: D.d.data['vx3'][0]
4220/1: ls
4220/2: %run swics_collimator_ulysses.py
4220/3: c = collimator()
4220/4: c.test_plot()
4220/5: c = collimator(aspphi= 20)
4220/6: c.test_plot()
4220/7: c = collimator(asptheta= 20)
4220/8: c.test_plot()
4220/9: c.test_plot()
4220/10: pylab.close('all')
4220/11: c = collimator(asptheta= 20)
4220/12: pylab.close('all')
4220/13: pylab.close('all')
4220/14: c.test_plot()
4220/15: c = collimator(aspphi= 20)
4220/16: c.test_plot()
4220/17: c.FoV
4220/18: c = collimator(asptheta= 20)
4220/19: c.FoV
4220/20: c = collimator(asptheta= 20, aspphi = 10.)
4220/21: c.FoV
4220/22: c.test_plot()
4221/1: %run load_pui_ulysses.py
4222/1: %run load_pui_ulysses.py
4222/2: D.d.get_data('Master','vr_sc')
4222/3: D.d.get_data('Master','v')
4222/4: D.d.get_data('Master','vx')
4222/5: D.d.get_data('Master','vy')
4222/6: D.d.get_data('Master','vz')
4223/1: %run load_pui_ulysses.py
4224/1: %run load_pui_ulysses.py
4224/2: D.d.get_data('Master','vy')
4224/3: unique(D.d.get_data('Master','vy'))
4224/4: unique(D.d.get_data('Master','aspphi'))
4225/1: %run load_pui_ulysses.py
4226/1: %run load_pui_ulysses.py
4226/2: D.asptheta
4226/3: D.d.get_data('Master','aspphi')
4226/4: unique(D.d.get_data('Master','aspphi'))
4226/5: unique(D.d.get_data('Master','vy'))
4227/1: D.d.get_data('Master','aspphi')
4227/2: %run load_pui_ulysses.py
4227/3: unique(D.d.get_data('Master','vy'))
4228/1: %run load_pui_ulysses.py
4228/2: unique(D.d.get_data('Master','vy'))
4229/1: %run load_pui_ulysses.py
4229/2: unique(D.d.get_data('Master','aspphi'))
4229/3: unique(D.d.get_data('Master','vy'))
4229/4: unique(D.d.get_data('Master','vr_sc'))
4229/5: unique(D.d.get_data('Master','vt_sc'))
4230/1: %run load_pui_ulysses.py
4231/1: %run test_dies_das.py
4231/2: evolution_RTN()
4232/1: %run test_dies_das.py
4232/2: evolution_RTN()
4232/3: v1 = array(5., 0., 0.)
4232/4: v1 = array([5., 0., 0.])
4232/5: v2 = array([5.,-10,-10])
4232/6: hg_to_rtn(v1,v2)
4232/7: from Trajectory.ul_calc_traj import hg_to_rtn
4232/8: hg_to_rtn(v1,v2)
4233/1: %run test_dies_das.py
4233/2: evolution_RTN()
4234/1: %run test_dies_das.py
4234/2: %run load_pui_ulysses.py
4234/3: D._add_3Dv()
4235/1: %run load_pui_ulysses.py
4235/2: D._add_3Dv(sc_vel = False)
4235/3: D.d.get_data('Master','vr')
4235/4: D.d.get_data('Master','vx')
4236/1: D._add_3Dv(sc_vel = False)
4236/2: %run load_pui_ulysses.py
4236/3: D._add_3Dv(sc_vel = False)
4236/4: D.d.get_data('Master','vx')
4236/5: D.d.get_data('Master','vy')
4236/6: D.d.get_data('Master','vt')
4236/7: D.d.get_data('Master','vz')
4236/8: unique(D.d.get_data('Master','vz'))
4236/9: D.d.get_data('Master','vz')[0:3]
4236/10: D.d.get_data('Master','aspphi')[0:3]
4236/11: D._add_3Dv(sc_vel = True)
4236/12: D.d.get_data('Master','aspphi')[0:3]
4236/13: %run test_dies_das.py
4236/14: evolution_RTN()
4237/1: %run load_pui_ulysses.py
4237/2: D._add_3Dv(sc_vel = False)
4237/3: D.d.get_data('Master','vt')[0]
4237/4: D.d.get_data('Master','vz')[0]
4237/5: D.d.get_data('Master','vn_sc')[0]
4238/1: %run load_pui_ulysses.py
4238/2: D._add_3Dv(sc_vel = True)
4238/3: D.d.get_data('Master','vn_sc')[0]
4238/4: D.d.get_data('Master','vz')[0]
4238/5: D.d.get_data('Master','asptheta')[0]
4238/6: D.d.get_data('Master','aspphi')[0]
4238/7: %run swics_collimator_ulysses.py
4238/8: c = collimator(asptheta= -13, aspphi = -20.)
4238/9: c.test
4238/10: c.test_plot()
4239/1: %run load_pui_ulysses.py
4239/2: D._add_3Dv(sc_vel = False)
4239/3: D.d.get_data('Master','vy')[0]
4239/4: from Trajectory.ul_calc_traj import hg_to_rtn
4239/5: v0 = array([5.,265.,-80])
4239/6: v1 = array([5., 275., -80.])
4239/7: v2 = array([5.5,-10,-10])
4239/8: v3 = array([5.5,272.,-80])
4239/9: v2 = array([5.5,267,-80])
4239/10: hg_to_rtn(v0,v2)
4239/11: hg_to_rtn(v1,v3)
4239/12: D.d.get_data('Master','hg_long')[0]
4239/13: D.d.data.keys
4239/14: D.d.data.keys()
4239/15: D.d.get_data('Master','long_hg')[0]
4240/1: %run load_pui_ulysses.py
4240/2: D.d.get_data('Master','long_hg')[0]
4240/3: D.d.get_data('Master','vy')[0]
4240/4: D.d.get_data('Master','vt_sc')[0]
4240/5: unique(D.d.get_data('Master','vt_sc')[0])
4240/6: unique(D.d.get_data('Master','vt_sc'))
4241/1: %run load_pui_ulysses.py
4241/2: D.d.get_data('Master','vn_sc')[0]
4241/3: D.d.get_data('Master','vz')[0]
4241/4: D._add_3Dv(sc_vel = False)
4241/5: D.d.get_data('Master','vz')[0]
4241/6: D.d.get_data('Master','asptheta')[0]
4242/1: %run load_pui_ulysses.py
4242/2: D._add_3Dv(sc_vel = False)
4242/3: D.d.get_data('Master','vz')[0]
4243/1: %run load_pui_ulysses.py
4243/2: D._add_3Dv(sc_vel = False)
4243/3: D.d.get_data('Master','vz')[0]
4244/1: %run load_pui_ulysses.py
4245/1: %run load_pui_ulysses.py
4245/2: D.d.get_data('Master','aspphi')[0]
4245/3: D.d.get_data('Master','asptheta')[0]
4245/4: D.d.get_data('Master','vx')[0]
4245/5: D.d.get_data('Master','vy')[0]
4245/6: D.d.get_data('Master','vz')[0]
4246/1: %run load_pui_ulysses.py
4246/2: unique(D.d.get_data('Master','aspphi'))
4246/3: unique(D.d.get_data('Master','asptheta'))
4246/4: unique(D.d.get_data('Master','vx'))
4246/5: unique(D.d.get_data('Master','vy'))
4246/6: unique(D.d.get_data('Master','vz'))
4247/1: %run load_pui_ulysses.py
4247/2: unique(D.d.get_data('Master','aspphi'))
4247/3: unique(D.d.get_data('Master','asptheta'))
4247/4: unique(D.d.get_data('Master','vy'))
4247/5: unique(D.d.get_data('Master','vz'))
4247/6: D._add_3Dv(sc_vel = False)
4247/7: unique(D.d.get_data('Master','vz'))
4247/8: unique(D.d.get_data('Master','vz')).shape
4247/9:
D._add_3Dv(sc_vel = True
)
4247/10: unique(D.d.get_data('Master','vz')).shape
4247/11: testind = [0,1,0]
4247/12: D.vspace[testind,testind,testind,testind,testind,0]
4247/13: D._add_3Dv(sc_vel = False)
4247/14: D.vspace[testind,testind,testind,testind,testind,0]
4248/1: %run load_pui_ulysses.py
4248/2: D.d.get_data('Master','vz').shape
4249/1: %run load_pui_ulysses.py
4249/2: %run load_pui_ulysses.py
4249/3: D._add_3Dv(sc_vel = False)
4249/4: D.d.get_data('Master','vz').shape
4249/5: D._add_3Dv(sc_vel = True)
4249/6: D.d.get_data('Master','vz').shape
4251/1: %run load_pui_ulysses.py
4251/2: phiind = searchsorted(self.aspphi, around(self.d.get_data('Master',"aspphi")))
4251/3: phiind = searchsorted(D.aspphi, around(D.d.get_data('Master',"aspphi")))
4251/4: phiind.shape
4251/5: D.vspace[phiind,phiind,phiind,phiind,phiind,0]
4251/6: D.vspace[phiind,phiind,phiind,phiind,phiind,0].shape
4251/7: D.d.data['vr_sc']
4251/8: D.d.data['vr_sc'].shape
4252/1: %run load_pui_ulysses.py
4252/2: D.d.data['vr_sc'].shape
4252/3: D
4253/1: %run load_pui_ulysses.py
4253/2: D.d.data['vr_sc'].shape
4253/3: D.vspace[phiind,phiind,phiind,phiind,phiind,0].shape
4253/4: phiind = searchsorted(D.aspphi, around(D.d.get_data('Master',"aspphi")))
4253/5: D.vspace[phiind,phiind,phiind,phiind,phiind,0].shape
4253/6: a = array([1,2,3,4])
4253/7: b = np.repeat(a)
4253/8: b = np.repeat(a,5)
4253/9: b
4253/10: b = np.repeat(a,5, axis = 1)
4253/11: np.repeat(a,5, axis = 0)
4253/12: np.repeat(a,[5], axis = 0)
4253/13: np.repeat(a[:,np.newaxis],5, axis = 1)
4253/14: np.repeat(a[:,np.newaxis],5, axis = 2)
4253/15: np.repeat(a[np.newaxis,:],5, axis = 1)
4253/16: np.repeat(a[:,np.newaxis],5, axis = 1)
4253/17: np.repeat(a[:,np.newaxis],5, axis = 0)
4253/18: np.repeat(a[:,np.newaxis],5, axis = 1)
4253/19: np.repeat(a[:],5, axis = 0)
4253/20: np.tile(a,2)
4253/21: np.tile(a,[1,5])
4253/22: np.tile(a,(2,5))
4253/23: np.tile(a,(5,1))
4254/1: %run load_pui_ulysses.py
4255/1: %run load_pui_ulysses.py
4256/1: %run load_pui_ulysses.py
4256/2: a = array([1,2,3,4])
4256/3: a.shape
4256/4: phiind = searchsorted(D.aspphi, around(D.d.get_data('Master',"aspphi")))
4256/5: np.tile(a,[1,5])
4256/6: np.tile(a,(5,1))
4256/7: np.tile(a,(5,1)).shape
4256/8: np.tile(a,(1,5)).shape
4256/9: np.tile(a,(1,5))
4256/10: np.tile(a,(5,1))
4256/11: np.tile(a,(5,1)).T
4257/1: %run load_pui_ulysses.py
4257/2: D
4258/1: %run load_pui_ulysses.py
4259/1: %run load_pui_ulysses.py
4259/2: phiind = searchsorted(D.aspphi, around(D.d.get_data('Master',"aspphi")))
4259/3: D.vspace[phiind,phiind,phiind,phiind,phiind,0].shape
4259/4: D.vspace[phiind,phiind,phiind,phiind,phiind,0][0]
4259/5:
tile(self.d.data[
                    'vr_sc'],(9,1)).T)
4259/6: tile(D.d.data['vr_sc'],(9,1)).T)
4259/7: tile(D.d.data['vr_sc'],(9,1)).T
4259/8: tile(D.d.data['vr_sc'],(9,1)).T.shape
4259/9: tile(D.d.data['vr_sc'],(9,1)).T[0]
4260/1: %run load_pui_ulysses.py
4261/1: %run load_pui_ulysses.py
4262/1: %run load_pui_ulysses.py
4263/1: %run load_pui_ulysses.py
4264/1: %run load_pui_ulysses.py
4265/1: %run load_pui_ulysses.py
4265/2: tile(D.d.data['vr_sc'],(self.col_dim,1)).T[0]
4265/3: tile(D.d.data['vr_sc'],(D.col_dim,1)).T[0]
4265/4: tile(D.d.data['vr_sc'],(D.col_dim,1)).T[0].shape
4266/1: %run load_pui_ulysses.py
4266/2: d.hist1d('det')
4266/3: d.hist1d('ech')
4266/4: d.hist1d('ech', bin = arange(0,200,1))
4266/5: d.hist1d('ech', binx = arange(0,200,1))
4266/6: d.hist1d('ech', binx = arange(0,20,1))
4267/1: %run load_pui_ulysses.py
4268/1: %run load_pui_ulysses.py
4269/1: %run load_pui_ulysses.py
4270/1: %run load_pui_ulysses.py
4270/2: np.arange(1992,2000)
4270/3: range(1992,1999)
4271/1: %run load_pui_ulysses.py
4272/1: %run load_pui_ulysses.py
4273/1: %run load_pui_ulysses.py
4274/1: %run load_pui_ulysses.py
4275/1: %run load_pui_ulysses.py
4276/1: %run load_pui_ulysses.py
4277/1: %run load_pui_ulysses.py
4278/1: %run load_pui_ulysses.py
4279/1: %run load_pui_ulysses.py
4280/1: %run load_pui_ulysses.py
4280/2: from Trajectory.ulysses_traj import ulysses_traj
4280/3: traj = ulysses_traj(year= [1992,1994], tf = [[1.4]])
4280/4: traj = ulysses_traj(year= [1992,1994], tf = [[1,4]])
4280/5: traj.data
4280/6: traj.data['v_R']
4280/7: traj.data['v_R']-shape
4280/8: traj.data['v_R'].shape
4280/9: traj.data['v_T'].shape
4280/10: traj.data['v_N'].shape
4280/11: traj.data["d90"]
4280/12: traj.calc_d90()
4280/13: traj.data["d90"]
4280/14: traj.data["d90"].shape
4280/15: u = uswipha(year=[1994,1996],tf=[[1,5]])
4280/16: u.sync_traj()
4280/17: u = uswipha(year=[1994,1996],tf=[[1,15]])
4280/18: u.sync_traj()
4280/19: u = uswipha(year=[1998,2000],tf=[[1,5]])
4280/20: u.sync_traj()
4280/21: traj = ulysses_traj(year= [1998,2000], tf = [[1,4]])
4280/22: traj = ulysses_traj(year= [1998,2000], tf = [[1,5]])
4280/23: traj.data["d90"].shape
4280/24: traj.calc_d90()
4280/25: traj.data["d90"].shape
4280/26: traj.data['v_T'].shape
4280/27: traj.data["d90"]
4280/28: traj.data['v_T']
4280/29: u.data['d90']
4280/30: u.data['d90'].shape
4280/31: uTi_int, index_int = unique(u.data['d90'].astype(int),return_inverse=True)
4280/32: uTi_int
4280/33: index_int
4280/34: mask = traj.data['v_T'] != 0.
4280/35: mask
4280/36: traj.data['d90']
4280/37: traj.data['d90'][mask]
4280/38: traj_data['v_T']
4280/39: traj.data['v_T']
4280/40: uTi_int
4280/41: v_T, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_T"])
4280/42: v_T
4280/43: x
4280/44: uTi_int
4280/45: traj.data['d90']
4280/46: v_T, x = histogram(traj.data["d90"], bins=uTi_int)
4280/47: x
4280/48: v_T
4280/49: v_T, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_T"])
4280/50: v_T
4280/51: traj.data['v_T']
4280/52: x
4280/53: traj.data['d_90]
4280/54: traj.data['d_90']
4280/55: traj.data['d90']
4280/56: traj.data['v_T']
4280/57: u.data['d90'][-1]
4280/58: u.data['d90'][-10]
4280/59: u.data['v_T'][-10]
4281/1: u = uswipha(year=[1998,2000],tf=[[1,5]])
4281/2: from DataLoader import uswipha
4281/3: u = uswipha(year=[1998,2000],tf=[[1,5]])
4281/4: from DataLoader.uswipha import uswipha
4281/5: u = uswipha(year=[1998,2000],tf=[[1,5]])
4281/6: from Trajectory.ulysses_traj import ulysses_traj
4281/7: traj.data['v_T']
4281/8: traj = ulysses_traj(year= [1998,2000], tf = [[1,5]])
4281/9: u.sync_traj()
4281/10: u.data['v_T'][-10]
4281/11: u.data['d90'][-10]
4281/12: u.data.keys
4281/13: u.data.keys()
4281/14: u.data['vr_sc'][-10]
4281/15: u.data['vt_sc'][-10]
4281/16: v_T, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_T"])
4281/17: u.sync_traj()
4281/18: v_T, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_T"])
4281/19: traj.calc_d90()
4281/20: v_T, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_T"])
4281/21: uTi_int, index_int = unique(u.data['d90'].astype(int),return_inverse=True)
4281/22: v_T, x = histogram(traj.data["d90"], bins=uTi_int, weights=traj.data["v_T"])
4281/23: v_T
4281/24: index_int
4281/25: i = index_int[-10:]
4281/26: i
4281/27: v_T[i]
4281/28: v_T[index_int]
4281/29: u.data['vt_sc']
4282/1: from DataLoader.uswipha import uswipha
4282/2: u = uswipha(year=[1998,2000],tf=[[1,5]])
4282/3: from Trajectory.ulysses_traj import ulysses_traj
4282/4: u.sync_traj()
4282/5: u.timeframe
4282/6: t = ulysses_traj(year = u.year, tf = u.timeframe)
4282/7: t
4282/8: t.data
4282/9: t.calc_d90()
4282/10: t.data['d90']
4282/11: traj.data['d90']
4282/12: traj = ulysses_traj(year= [1998,2000], tf = [[1,5]])
4282/13: traj.data['d90']
4282/14: traj.calc_d90()
4282/15: t.data['d90']
4282/16: traj.calc_d90()
4282/17: traj.data['d90']
4283/1: from DataLoader.uswipha import uswipha
4283/2: u = uswipha(year=[1998,2000],tf=[[1,5]])
4283/3: u.sync_traj()
4283/4: %run load_pui_ulysses.py
4284/1: %run load_pui_ulysses.py
4284/2: d.hist1d('ech', binx = arange(0,20,1))
4285/1: %run load_pui_ulysses.py
4285/2: d.hist1d('ech', binx = arange(0,20,1))
4286/1: %run load_pui_ulysses.py
4286/2: d.hist1d('ech', binx = arange(0,20,1))
4287/1: %run load_pui_ulysses.py
4287/2: d.hist1d('ech', binx = arange(0,20,1))
4287/3: d.set_mask('12', 'ech', 12,12)
4287/4: d.get_data('12', 'year')
4287/5: d.get_data('12')
4287/6: d.data
4287/7: d.data(smask="12")
4287/8: d.get_data('12', 'sec')
4287/9: d.get_data('12', 'det')
4287/10: d.get_data('12', 'vsw')
4287/11: d.data.keys()
4287/12: d.get_data('12', 'tch')
4287/13: d.get_data('12', 'epq')
4287/14: d.set_mask('14', 'ech', 14,14)
4287/15: d.get_data('14', 'epq')
4287/16: d.get_data('14', 'det')
4287/17: d.get_data('14', 'sec')
4288/1: %run load_pui_ulysses.py
4288/2: d.hist1d('ech', binx = arange(0,20,1))
   1: from DataLoader.uswipha import uswipha
   2: u = uswipha(year=[1998],tf='all')
   3: d
   4: u
   5: u = hist1d('ech')
   6: u = hist1D('ech')
   7: u.sync_traj()
   8: u.sync_swoops()
   9: u.hist1d()
  10: u.hist1d('ech')
  11: u.hist2d
  12: u.hist2d?
  13: u.hist2d?
  14: u.set_mask('Master','ech',13,200)
  15: u.hist2d('tch','epq',binx=arange(200,500), biny = arange(0,64), norm = "ymax")
  16: u.hist2d('tch','epq',binx=arange(200,600), biny = arange(0,64), norm = "ymax")
  17: u.hist2d('tch','epq',binx=arange(200,900), biny = arange(0,64), norm = "ymax")
  18: u.hist2d('tch','epq',binx=arange(200,660), biny = arange(0,70), norm = "ymax")
  19: %history -g
  20: %hist -o -g -f ipython_history.md