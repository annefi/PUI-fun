#!/usr/bin/python
from scipy import zeros, sqrt,mean,log
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from libacepy.readdata import readelem,readres 

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0


fip=[24.6,11.3,14.5,13.6,21.6,7.6,8.1,10.3,6.1,7.9]
cabund=[10.93,8.5,7.9,8.8,8.08,7.6,7.6,7.2,6.3,7.6]
mass=[4.,12.,14.,16.,20.,24.,28.,32.,40.,56.]
pathl=open("pathlist2.in")
data=[]
for p in pathl:
    k=p.split()
    path=k[0]
    filelist=open(path+"list.in")
    s=filelist.readline()
    for s in filelist:
        k=s.split()
        datafilename=path+"elem_"+k[0]
        tmpdata=readelem(datafilename)
        data.append(tmpdata)
pathl.close()

pathl=open("pathlist2.in")
resdata=[]
for p in pathl:
    k=p.split()
    path=k[0]
    filelist=open(path+"list.in")
    s=filelist.readline()
    for s in filelist:
        k=s.split()
        datafilename=path+"res_"+k[0]
        tmpdata=readres(datafilename)
        resdata.append(tmpdata)
pathl.close()

gpvdata=[]
for elem in range(len(data[0])):
    tmpvdata=[]
    for time in range(len(data)):
        tmpvdata.append([279.+(0.00833*time*5.),resdata[time][elem][2]])
    gpvdata.append(Data(tmpvdata))
    
gpplotdata=[]
for elem in range(len(data[0])):
    tmpplotdata=[]
    for time in range(len(data)):
        tmpplotdata.append([279.+(0.00833*time*5.),data[time][elem][5]])
    gpplotdata.append(Data(tmpplotdata))
    gpplotdata[elem].set_option_colonsep("title",  "'%s fip %f'" %(data[0][elem][0],fip[elem]))

mpc=[]
for elem in range(len(data[0])):
    tmpmpc=0.
    for time in range(len(data)):
        if (data[time][elem][8]):
            tmpmpc=tmpmpc+mass[elem]/data[time][elem][8]
    tmpmpc=tmpmpc/float(len(data))
    mpc.append(tmpmpc)
    
gpplotratio=[]
for elem in range(len(data[0])):
    tmpplotdata=[]
    for time in range(len(data)):
        if (data[time][elem][3] and data[time][0][3]):
            tmpplotdata.append([279.+(0.00833*time*5.),(10**(cabund[0]-cabund[elem]))/(data[time][0][3]/data[time][elem][3])])
        else:
            tmpplotdata.append([279.+(0.00833*time*5.),0.])
    gpplotratio.append(Data(tmpplotdata))
    gpplotratio[elem].set_option_colonsep("title",  "'%s fip %f'" %(data[0][elem][0],fip[elem]))


gp=Gnuplot()
gp("set logscale y")
#gp("set yrang[10000:100000000]")    
gp("f(x)=10**(10.93-7.6)")
gpvdata[0].set_option_colonsep("with","l")
gp.plot(gpplotratio[1],gpvdata[0])
for i in range(len(data[0])-2):
    gp.replot(gpplotratio[i+2])

#gp.plot(gpplotdata[1],gpvdata[0])
#for i in range(len(data[0])-2):
#    gp.replot(gpplotdata[i+2])
#gp.plot(gpplotdata[0],gpplotdata[1])
