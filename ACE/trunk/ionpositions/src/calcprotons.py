from Gnuplot import Gnuplot
from math import sqrt
from libacepy.lv2data import lv2data 

ionlist=["H1+"]
m=1.66053886e-27
e=1.60217646e-19
path="./"




posname=path+"1H1+.tof"
posin=open(posname)
pos=[]
for s in posin:
    k=s.split()
    v=sqrt((2*float(k[0])*e*1000.)/m)
    pos.append([v/1000.,int(float(k[2]))])

listname=path+"list.in"
listin=open(listname)
s=listin.readline()
data=[]
for k in listin:
    name=k.split()
    tmplv2dat=lv2data(path,name[0],ionlist)
    tmplv2dat.setions()
    tmplv2dat.ions[0].mass=1.
    tmplv2dat.ions[0].charge=1.
    dataname=path+name[0]
    datain=open(dataname)
    k2=["++"]
    while (k2[0]!="*****"):
        s=datain.readline()
        k2=s.split()
        if (k2[0]=="Cycles"):
            tmplv2dat.ions[0].cycles=float(k2[2])
            print "cycles = ",float(k2[2])
            print tmplv2dat.ions[0].cycles
        if (k2[0]=="Aspang"):
            tmplv2dat.ions[0].aspang=float(k2[2])
    tmpdata=[]
    for step in range(58): 
        tmplv2dat.ions[0].velocity[step]=pos[step][0]
        s=datain.readline()
        k2=s.split()
        s=datain.readline()
        k3=s.split()
        tmpsum=0.
        for i in range(pos[step][1]-20,pos[step][1]+20):
            tmpsum+=float(k3[i])
        tmplv2dat.ions[0].counts[step]=tmpsum
        for j in range(int(k2[0])-1):
            s=datain.readline()
    tmplv2dat.calcdifffluxes()
    tmplv2dat.numint()
    tmplv2dat.writefluxfile()
    tmplv2dat.writeresfile()
    data.append(tmplv2dat)

#for i in range(len(data)):
#    print data[i].ions[0].totdensnumint, data[i].ions[0].iontempdensnumint, data[i].ions[0].bulkspeeddensnumint
#gp=Gnuplot()
#gp("set xrange[80:150]")
