from Gnuplot import Gnuplot
from math import sqrt
from libacepy.lv2data import lv2data
from scipy import zeros

ionlist=["H1+","3He1+","He1+","C1+","N1+","O1+","Ne1+","Mg1+","Si1+","S1+","Ca1+","Fe1+"]
m=1.66053886e-27
e=1.60217646e-19
path="./"

ion_pos=[]
posname=path+"ion_para.dat"
for ion in ionlist:
    ion_pos.append([])
    posin=open(posname)
    for step in range(58):
        posin.readline()
        posin.readline()
        for tmpion in range(len(ionlist)):
            s=posin.readline()
            k=s.split()
            if (k[0]==ion):
                print ion,step
                xpos=float(k[1])
                ypos=float(k[2])
                sigx=float(k[3])
                sigy=float(k[5])
                vel=float(k[7])
                mass=float(k[8])
                charge=float(k[9])
                if (xpos+sigx>512 or ypos<5.):
                    xpos=0.
                    ypos=0.
                    sigx=0.
                    sigy=0.
                ion_pos[len(ion_pos)-1].append([xpos,ypos,sigx,sigy,vel,mass,charge])



listname=path+"list.in"
listin=open(listname)
s=listin.readline()
data=[]
for k in listin:
    name=k.split()
    tmplv2dat=lv2data(path,name[0],ionlist)
    tmplv2dat.setions()
    for i in range(len(ion_pos)):
        tmplv2dat.ions[i].mass=ion_pos[i][0][5]
        tmplv2dat.ions[i].charge=ion_pos[i][0][6]
    dataname=path+name[0]
    datain=open(dataname)
    k2=["++"]
    while (k2[0]!="*****"):
        s=datain.readline()
        k2=s.split()
        if (k2[0]=="Cycles"):
            for i in range(len(ion_pos)):
                tmplv2dat.ions[i].cycles=float(k2[2])
                print "cycles = ",float(k2[2])
                print tmplv2dat.ions[i].cycles
        if (k2[0]=="Aspang"):
            for i in range(len(ion_pos)):
                tmplv2dat.ions[i].aspang=float(k2[2])
    tmpdata=[]
    for step in range(58):
        for i in range(len(ion_pos)):
            tmplv2dat.ions[i].velocity[step]=ion_pos[i][step][4]
        s=datain.readline()
        k2=s.split()
        print "ydim = ",int(k2[0])
        print "xdim = ",int(k2[1])
        etmat=zeros([int(k2[0]),int(k2[1])])
        s=datain.readline()
        for j in range(1,int(k2[0])):
            s=datain.readline()
            k3=s.split()
            for i in range(int(k2[1])):
                etmat[j][i]=float(k3[i])
        for i in range(len(ion_pos)):
            tmpsum=0.
            srange=2.
            xmin=int(max(ion_pos[i][step][0]-srange*ion_pos[i][step][2],0)+0.5)
            xmax=int(min(ion_pos[i][step][0]+srange*ion_pos[i][step][2],511)+1.5)
            ymin=int(max(ion_pos[i][step][1]-srange*ion_pos[i][step][3],0)+0.5)
            ymax=int(min(ion_pos[i][step][1]+srange*ion_pos[i][step][3],127)+1.5)
            for x in range(xmin,xmax):
                for y in range(ymin,ymax):
                    tmpsum+=etmat[y][x]
            tmplv2dat.ions[i].counts[step]=tmpsum
    #tmplv2dat.calcdifffluxes()
    #tmplv2dat.numint()
    tmplv2dat.writefluxfile()
    tmplv2dat.writeresfile()
    data.append(tmplv2dat)

#for i in range(len(data)):
#    print data[i].ions[0].totdensnumint, data[i].ions[0].iontempdensnumint, data[i].ions[0].bulkspeeddensnumint
#gp=Gnuplot()
#gp("set xrange[80:150]")
