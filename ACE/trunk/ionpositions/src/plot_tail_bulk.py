#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from libacepy.readdata import readflux,readres
from libacepy.fluxes import getmaxflux

pathl=open("pathlist2.in")
ion_list=[]
s=pathl.readline()
p=s.split()
liste=open(p[0]+"list.in")
s=liste.readline()
s=liste.readline()
k=s.split()
listeion=readres(p[0]+"res_"+k[0])
for ion in range(len(listeion)-1):
    ion_list.append(listeion[ion+1][0])
print ion_list
pathl.close()
liste.close()

ion_list=["He2+","O6+","C5+","C6+","Fe13+"]
ion_list=["He2+","O6+","C6+","N5+","Ne8+","S9+"]

pathl=open("pathlist2.in")
data=[]
print "readinding data"
for s in pathl:
    p=s.split()
    liste=open(p[0]+"list.in")
    s2=liste.readline()
    for s2 in liste:
        filen=s2.split()
        tmpdata=readflux(p[0]+"flux_"+filen[0])
        data.append(tmpdata)
    print "finished reading",p[0]

sdata=[]
for ion in range(len(ion_list)):
    tmpion=[]
    for time in range(len(data)):
        tmpionstep=[]
        for step in range(len(data[time])):
            for ion2 in range(len(data[time][step])):
                if (data[time][step][ion2][0]==ion_list[ion]):
                    tmpionstep.append(data[time][step][ion2])
        tmpion.append(tmpionstep)
    sdata.append(tmpion)
print "len(sdata)=",len(sdata)

tailbulkdist=[]
first=1
for ion in range(len(sdata)):
    tailbulkdisttmp=[]
    for time in range(len(sdata[ion])):
        tmpsumme=0.
        maxflux=0
        if (len(sdata[ion][time])>0):
            for step in range(len(sdata[ion][time])):
                if (sdata[ion][time][step][12]>sdata[ion][time][maxflux][12]):
                    maxflux=step
            for step in range(len(sdata[ion][time])):
                if ((sdata[ion][time][step][7]>=1.5*sdata[ion][time][maxflux][7]) and (sdata[ion][time][step][7]<=1.69*sdata[ion][time][maxflux][7])):
                    tmpsumme+=sdata[ion][time][step][12]
            if (sdata[ion][time][maxflux][12]):
                tailbulk=tmpsumme/sdata[ion][time][maxflux][12]
            else:
                tailbulk=0.
        else:
            tailbulk=0.
        tailbulkdisttmp.append([(279.+time*5.*0.00833),tailbulk])
    tailbulkdist.append(tailbulkdisttmp)
gptailbulkdist=[]
for ion in range(len(sdata)):
    tmpgptailbulk=Data(tailbulkdist[ion])
    tmpgptailbulk.set_option_colonsep("using", "1:2")
    tmpgptailbulk.set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
    gptailbulkdist.append(tmpgptailbulk)


gp=Gnuplot()
gp("set autoscale")
gp("set yrange[0.00001:1.]")
gp("set logscale y")
gp("set xlabel 'DoY'")
gp("set ylabel 'tail/bulk ratio' ")

for ion in range(len(sdata)):
    if (first):
        gp.plot(gptailbulkdist[ion])
        first=0
    else:
        gp.replot(gptailbulkdist[ion])

gp("set term postscript color 18 lw 2 eps")
gp.hardcopy("tailbulk.ps",color=True, fontsize=18)
