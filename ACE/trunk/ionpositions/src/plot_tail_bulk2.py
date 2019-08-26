#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from math import atan

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

def getbulkdens(data):
    diff=100.
    bulkpos=0
    for i in range(len(data)):
        if (sqrt((1.-data[i][0])**2)<diff):
            diff=sqrt((1.-data[i][0])**2)
            bulkpos=i
    return data[bulkpos][1]

def gettaildens(data):
    tailsum=0.
    for i in range(len(data)):
        if (data[i][0]>=1.5 and data[i][0]<=1.69):
            tailsum+=data[i][1]
    return tailsum



dim=58
ion_name=["He2+","C5+","C6+","N6+","N7+","O6+","O7+","O8+","Ne8+","Mg9+","Mg10+","Mg11+","Mg12+","Fe11+","Si8+","Si9+","Si10+","S8+","S9+","S10+"]
#"O6+","Ne8+","Mg9+","Si10+","Fe11+","C6+",,"O7+","O8+","N7+",]
mass=[4.,12.,12.,14.,14.,16.,16.,16.,20.,24.,24.,24.,24.,56.,28.,28.,28.,32.,32.,32.]
charge=[2.,5.,6.,6.,7.,6.,7.,8.,8.,9.,10.,11.,12.,11.,8.,9.,10.,8.,9.,10.]
#ion_name=["O6+","O7+","O8+"]
#mass=[16.,16.,16.]
#charge=[6.,7.,8.]
#ion_name=["He2+","C5+","O6+"]
#mass=[4.,12.,16.]
#charge=[2.,5.,6.]
sis=[[1.96,1.e1],[15.45,1.e1],[29.41,1.e1],[43.45,1.e1],[58.30,1.e1],[70.87,1.e1],[71.30,1.e1],[71.53,1.e1],[84.35,1.e1],[91.10,1.e1],[99.10,1.e1],[117.60,1.e1],[127.70,1.e1],[127.90,1.e1],[138.4,1.e1],[144.00,1.e1],[152.60,1.e1],[164.4,1.e1],[172.40,1.e1],[184.90,1.e1]]
#ergpath="/data/wimmer/ace/12mdata/2007/"
A=[[1.96,1.e1],[29.41,1.e1],[58.30,1.e1],[84.35,1.e1],[111.30,1.e1],[138.4,1.e1],[164.4,1.e1]]
B=[[8.00,1.e1],[37.00,1.e1],[62.10,1.e1],[91.10,1.e1],[117.60,1.e1],[144.00,1.e1],[172.4,1.e1]]
C=[[15.45,1.e1],[43.45,1.e1],[71.30,1.e1],[99.10,1.e1],[127.90,1.e1],[152.6,1.e1],[180.0,1.e1]]
D=[[105.90,1.e1],[135.0,1.e1],[159.00,1.e1],[184.9,1.e1]]


ergpath="/data/kleopatra/ace/1hdata/2007/"
startdoy=3
stopdoy=50
alliondata=[]
allionvel=[]
alliontemp=[]
allionmach=[]
allionspth=[]
alliondens=[]
for ion in range(len(ion_name)):
    alldata=[]
    allvel=[]
    alltemp=[]
    allmach=[]
    allspth=[]
    alldens=[]
    for doy in range(startdoy,stopdoy+1):
        print doy
        if (doy<10):
            doystr="00"+str(doy)
        if (doy>9 and doy<100):
            doystr="0"+str(doy)
        if (doy>99):
            doystr=str(doy)
        ergdaypath=ergpath+doystr+"/"

        ergl=open(ergdaypath+"list.in")
        s=ergl.readline()
        k=s.split()
        numberfiles=int(k[0])

        # load data
        daydata=[]
        dayfiles=[]
        dayvel=[]
        daytemp=[]
        daymach=[]
        dayspth=[]
        daydens=[]
        hour=0
        for s1 in ergl:
            hour+=1
            k=s1.split()
            resname=ergdaypath+"res_"+k[0]
            ergname=ergdaypath+"flux_"+k[0]
            f=open(resname)
            s=f.readline()
            k=s.split()
            while (k[0]!=ion_name[ion]):
                s=f.readline()
                k=s.split()
            ionvel=float(k[1])
            iondens=float(k[10])
            iontemp=float(k[4])
            f.close()
            counts=[]
            suprath=[]
            f=open(ergname)
            k=["*"]
            while (k[0]!=ion_name[ion]):
                s=f.readline()
                k=s.split()
            s=f.readline()
            s=f.readline()
            s=f.readline()
            for step in range(dim):
                s=f.readline()
                k=s.split()
                if (ionvel!=0.):
                    counts.append([float(k[0])/ionvel,float(k[7]),float(k[8])])
                if (ionvel!=0. and float(k[0])>=1.5*ionvel):
                    suprath.append([float(k[0]),float(k[7]),float(k[8])])
            if (ionvel!=0.):
                dayvel.append(float(ionvel)*1.e-2)
                daytemp.append(float(iontemp)/100000000.)
                vth=sqrt((8314.5/mass[ion])*float(iontemp))/1000.
                daymach.append(atan(vth/ionvel)/(2*3.14)*360)
                #        plotcounts=Data(counts)
            spdens=0.
            for i in range(len(suprath)):
                if (i==0):
                    spdens+=(suprath[i][0]-suprath[i+1][0])*1000.*suprath[i][1]
                elif (i==len(suprath)-1):
                    spdens+=(suprath[i-1][0]-suprath[i][0])*1000.*suprath[i][1]
                else:
                    spdens+=((suprath[i-1][0]-suprath[i][0])+(suprath[i][0]-suprath[i+1][0]))*500.*suprath[i][1]
            dayspth.append(spdens)
            daydata.append(counts)
            if (1):
            #if (iondens>10.e-6):
                daydens.append(iondens)
            else:
                print "daydens = ",len(daydens)
                daydens.append(daydens[len(daydens)-1])

            #        dayfiles.append(plotcounts)
            f.close()
        allmach.append(daymach)
        allvel.append(dayvel)
        alltemp.append(daytemp)
        alldata.append(daydata)
        allspth.append(dayspth)
        alldens.append(daydens)

    
    alliondata.append(alldata)
    allionvel.append(allvel)
    alliontemp.append(alltemp)
    allionmach.append(allmach)
    allionspth.append(allspth)
    alliondens.append(alldens)



# calculate tail/bulk
plottb=[]
plotvel=[]
plottemp=[]
plotmach=[]
plotspth=[]
plotdens=[]
plottbr=[]
tbr=[]
for ion in range(len(ion_name)):
    tailbulk=[]
    tailbulkratio=[]
    vel=[]
    temp=[]
    mach=[]
    spth=[]
    dens=[]
    tmpionsp=0.
    tmpiondens=0.
    for i in range(len(alliondata[ion])):
        for j in range(len(alliondata[ion][i])):
            time=float(startdoy)+float(i)+float(j)/24.+1./48.
            #        time=float(startdoy)+float(i)+float(j)/120.+1./240.
            tmpionsp+=allionspth[ion][i][j]
            tmpiondens+=alliondens[ion][i][j]
            if (len(alliondata[ion][i][j])>0.):
                bdens=getbulkdens(alliondata[ion][i][j])
                tdens=gettaildens(alliondata[ion][i][j])
                if (bdens>0.):
                    if (tdens/bdens>1.e-7):
                        tailbulk.append([time,tdens/bdens])
            if (i<len(allionvel[ion])):
                if (j<len(allionvel[ion][i])):
                    vel.append([time,allionvel[ion][i][j]])
                    temp.append([time,alliontemp[ion][i][j]])
                    mach.append([time,allionmach[ion][i][j]])
                    dens.append([time,alliondens[ion][i][j]])
                    
                    if (allionspth[ion][i][j]!=0 and alliondens[ion][i][j]!=0):
                        spth.append([time,allionspth[ion][i][j]])
                        #tailbulkratio.append([time,(allionspth[ion][i][j]/alliondens[ion][i][j])/5.e-5])
                        tailbulkratio.append([time,(allionspth[ion][i][j]/alliondens[ion][i][j])])
    if (tmpiondens!=0):
        tbr.append([mass[ion]/charge[ion],tmpionsp/tmpiondens])
    else:
        tbr.append([mass[ion]/charge[ion],0.])

    #plottb.append(Data(tailbulk))
    #plottbr.append(Data(tailbulkratio))
    #plotvel.append(Data(vel))
    #plottemp.append(Data(temp))
    #plotmach.append(Data(mach))
    #plotspth.append(Data(spth))
    #plotdens.append(Data(dens))
    #plotdens[0].set_option_colonsep("with", "lines")
    #plotvel[0].set_option_colonsep("with", "lines")
    #plottbr[0].set_option_colonsep("with", "lines")
    

#print "tbr = ",tbr

for sp in plotspth:
    sp.set_option_colonsep("with", "lines ls 3")
plotA=Data(A)
plotB=Data(B)
plotC=Data(C)
plotD=Data(D)
plotA.set_option_colonsep("title", "'A'")
plotB.set_option_colonsep("title", "'B'")
plotC.set_option_colonsep("title", "'C'")
plotD.set_option_colonsep("title", "'D'")

#plotspth.set_option_colonsep("with", "lines")
#gp=Gnuplot()
#gp.plot(plotvel,plotmach)
#gp("set log y")
#gp("set log x")
#first=1
#i=1
#gp.plot(dayfiles[i])
#for k in range(4):
#    gp.replot(dayfiles[i+k+1])

gp2=Gnuplot()
gp2("set log y")
gp2("set format y '10^{%T}'")

#gp2("set xrange[%i:%i]"%(startdoy,stopdoy))
gp2("set xrange[1:5.5]")
gp2("set xlabel 'DoY 2007")
gp2("set ylabel 'Density [cm^{-3}]")
#gp2("set ylabel 'Solar Wind Speed [km^{1}s^{-1}]")
#gp2.plot(plottbr[0],plotvel[0],plotA,plotB,plotC,plotD)
gp2.plot(tbr)
#gp2("set yrange[1.e-7:1.]")
#first=1
#for i in range(len(plotspth)):
#    plotspth[i].set_option_colonsep("title", "'%s'"%(ion_name[i]))
#    if (first==1):
#        plotspth[i].set_option_colonsep("with", "lines")
#        gp2.plot(plotspth[i])
#        first=0
#    else:
#        gp2.replot(plotspth[i])
                      
gp2("set term postscript color 18 lw 2 eps")
gp2.hardcopy("tailbulk14_15.ps",color=True, fontsize=18)
                   
