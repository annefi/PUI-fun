from libacepy.swicsiondata import swicsiondata
from libacepy.swepamdata import swepamdata,sync_h
from libacepy.swicselemdata import swicselemdata
from libacepy.swicsprotondata import swicsprotondata
from libacepy.mag import magdata,sync_mag
from math import cos,acos
from Gnuplot import Gnuplot
swicspath="/data/wimmer/ace/1hdata/2001/"
ppath="/data/wimmer/ace/1hdataprotons/2001/"
magpath="/data/ivar/ace/mag/"
swepampath="/data/ivar/ace/swepam/"
timeframequietplot=[[4.,9.],[17.4,25.25],[30.5,35.],[45.5,55.],[60.,63.],[65.5,70.],[73.25,80.5],[93.,97.5],[103.,107.],[119.,126.5],[129.,131.],[134.,135.],[145.25,151.1]]
timeframequietplot=[[1.,360.]]

he=swicsiondata("He2+",timeframequietplot,swicspath)
he.load()
h=swepamdata(720,2001,1.,362.,swepampath)
h.load()
hsync=sync_h(h,he)

"""
hswics=swicsprotondata("H1+",timeframequietplot,ppath)
hswics.load()
"""
mag=magdata(240,2007,1.,362.,magpath)
mag.load()
magsync=sync_mag(mag,he)

o=swicselemdata("O",timeframequietplot,swicspath)
fe=swicselemdata("Fe",timeframequietplot,swicspath)
o.load()
fe.load()
feoheh=[]
feoheh2=[]
feoheh3=[]
feoheh4=[]
feoheh5=[]

gp=Gnuplot()
hehmag=[]
mfe=0.
mhe=0.
nm=0.
mfe2=0.
mhe2=0.
nm2=0.
"""
for i in range(len(he.time)):
    if (hswics.dens[i][0]>0. and o.dens[i][1]>0. and he.vel[i]>600. and fe.dens[i][1]>0.):
        hehmag.append([acos(abs(cos(magsync.phi[i][1])*cos(magsync.theta[i][1]))),he.dens[i][0]/hswics.dens[i][0]])
acos(abs(cos(magsync.phi[i][1])*cos(magsync.theta[i][1])))
"""
for i in range(len(he.time)):
    if (hsync.dens[i][1]>0. and he.vel[i]>600. and he.vel[i]>600.):
        feoheh.append([he.dens[i][0]/hsync.dens[i][1],hsync.heh[i][1]])


for i in range(len(he.time)):
    if (hsync.dens[i][1]>0. and he.vel[i]>500. and he.vel[i]<600.):
        feoheh2.append([he.dens[i][0]/hsync.dens[i][1],hsync.heh[i][1]])


for i in range(len(he.time)):
    if (hsync.dens[i][1]>0. and he.vel[i]>400. and he.vel[i]<500.):
        feoheh3.append([he.dens[i][0]/hsync.dens[i][1],hsync.heh[i][1]])

for i in range(len(he.time)):
    if (hsync.dens[i][1]>0. and he.vel[i]>350. and he.vel[i]<400.):
        feoheh4.append([he.dens[i][0]/hsync.dens[i][1],hsync.heh[i][1]])

for i in range(len(he.time)):
    if (hsync.dens[i][1]>0. and he.vel[i]>300. and he.vel[i]<350.):
        feoheh5.append([he.dens[i][0]/hsync.dens[i][1],hsync.heh[i][1]])
#gp("set xrange[0:1.]")
#gp("set yrange[0:.1]")
gp("set size square")
gp("set xrange[0:0.5]")
gp("set yrange[0:0.5]")

gp.plot(feoheh,feoheh2,feoheh2,feoheh3,feoheh4,feoheh5)
"""
gp2=Gnuplot()
gp2.plot(hehmag)
"""
        
