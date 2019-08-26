#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float


path="/data/wimmer/berger/fpII/2007057_059_12m/" #unser aktueller messordner
"""
get list of ions
"""

ionnames=[]
iondens=[] # dichte 
ionvelocity=[]# geschwindigkeit
ionmaxdens=[] # dichte 
ionmaxvelocity=[]# geschwindigkeit
iontemp=[]# temperatur
meancharge=[] # mittlerer ladungszustand
elemnames=[]
listin=open(path+"list.in") #list der fertigen daten zur auswertung
s=listin.readline()
s=listin.readline()
k=s.split()
#resname=path+"res_"+k[0]
resname=path+"res_"+k[0]
resfile=open(resname)
s=resfile.readline()
for s in resfile: # erzeugen der vektoren
    k=s.split()
    ionnames.append(k[0])
    iondens.append([])
    ionvelocity.append([])
    ionmaxdens.append([])
    ionmaxvelocity.append([])
    iontemp.append([])
listin.close()
listin=open(path+"list.in") #list der fertigen daten zur auswertung
s=listin.readline()
s=listin.readline()
k=s.split()
resname=path+"elem_"+k[0]
resfile=open(resname)
s=resfile.readline()
for s in resfile: # erzeugen der vektoren
    k=s.split()
    elemnames.append(k[0])
    meancharge.append([])
listin.close()
                   
"""
get ion data
"""
listin=open(path+"list.in")
s=listin.readline()
step=-1
for s in listin:
    step=step+1
    k=s.split()
    print k[0]
    day=float(k[0][21:24])#Tag der Messung
    min=float(k[0][28:30])#Minuten der Messung
    hour=float(k[0][25:27])#Stunden der Messung
#    day=float(k[0][25:28])#Tag der Messung
#    min=float(k[0][32:34])#Minuten der Messung
#    hour=float(k[0][29:31])#Stunden der Messung
    time=(min+6.)/1440.+day+hour*60./1440. #Prozentualer Anteil des Tages
    #resname=path+"res_"+k[0]
    resname=path+"res_"+k[0]
    resfile=open(resname)
    s=resfile.readline()
    ion=-1
    for s in resfile:
        ion=ion+1
        k=s.split()
        velfac=1000. # skalierungs faktor der geschwindigkeit zum gemeinsamen plotten
        densfac=10000000. # skalierungs faktor für dichte zum plotten
        if (float(k[11])>0. and float(k[11])<100.):
            ionmaxdens[ion].append([float(time),float(k[11])*densfac])
        if (float(k[9])>0. and float(k[9])<100.):
            iondens[ion].append([float(time),float(k[9])*densfac])
        if (float(k[3])>0.):
            ionmaxvelocity[ion].append([float(time),float(k[3])*velfac])
        if (float(k[1])>0.):
            ionvelocity[ion].append([float(time),float(k[1])*velfac])
        if (float(k[4])>0.):
            iontemp[ion].append([float(time),float(k[4])])
    resfile.close()
listin.close()

listin=open(path+"list.in")
s=listin.readline()
step=-1
for s in listin:
    step=step+1
    k=s.split()
    print k[0]
    day=float(k[0][21:24])#Tag der Messung
    min=float(k[0][28:30])#Minuten der Messung
    hour=float(k[0][25:27])#Stunden der Messung
#    day=float(k[0][25:28])#Tag der Messung
#    min=float(k[0][32:34])#Minuten der Messung
#    hour=float(k[0][29:31])#Stunden der Messung
    time=(min+6.)/1440.+day+hour*60./1440. #Prozentualer Anteil des Tages
    #resname=path+"res_"+k[0]
    elemname=path+"elem_"+k[0]
    elemfile=open(elemname)
    s=elemfile.readline()
    elem=-1
    for s in elemfile:
        elem=elem+1
        k=s.split()
        if (float(k[8])>0. and float(k[8])<14.):
            meancharge[elem].append([float(time),float(k[8])])
    elemfile.close()
listin.close()

"""
generate gnuplot data
"""

#erzeugt plotdaten
plotdens=[]
for ion in range(len(ionnames)):
    if (len(iondens[ion])>1):
        tmpplotdens=Data(iondens[ion])
    else:
        tmpplotdens=Data([[0.,0.]])
    tmpplotdens.set_option_colonsep("using", "1:2 ")
    tmpplotdens.set_option_colonsep("title",  "'%s density*10^7'" %(ionnames[ion]))
    tmpplotdens.set_option_colonsep("with",  "points")
    plotdens.append(tmpplotdens)
plotmaxdens=[]
for ion in range(len(ionnames)):
    if (len(ionmaxdens[ion])>1):
        tmpplotmaxdens=Data(ionmaxdens[ion])
    else:
        tmpplotmaxdens=Data([[0.,0.]])
    tmpplotmaxdens.set_option_colonsep("using", "1:2 ")
    tmpplotmaxdens.set_option_colonsep("title",  "'%s density*10^7'" %(ionnames[ion]))
    tmpplotmaxdens.set_option_colonsep("with",  "points")
    plotmaxdens.append(tmpplotmaxdens)
plotvelocity=[]
for ion in range(len(ionnames)):
    if (len(ionvelocity[ion])>1):
        tmpplotvelocity=Data(ionvelocity[ion])
    else:
        tmpplotvelocity=Data([[0.,0.]])
#    tmpplotvelocity=Data(ionvelocity[ion])
#    tmpplotdata.set_option_colonsep("using", "1:4 ")
    tmpplotvelocity.set_option_colonsep("title",  "'%s velocity*10^3'" %(ionnames[ion]))
    tmpplotvelocity.set_option_colonsep("with",  "lines")
    plotvelocity.append(tmpplotvelocity)
plotmaxvelocity=[]
for ion in range(len(ionnames)):
    if (len(ionmaxvelocity[ion])>1):
        tmpplotmaxvelocity=Data(ionmaxvelocity[ion])
    else:
        tmpplotmaxvelocity=Data([[0.,0.]])
#    tmpplotvelocity=Data(ionvelocity[ion])
#    tmpplotdata.set_option_colonsep("using", "1:4 ")
    tmpplotmaxvelocity.set_option_colonsep("title",  "'%s velocity*10^3'" %(ionnames[ion]))
    tmpplotmaxvelocity.set_option_colonsep("with",  "lines")
    plotmaxvelocity.append(tmpplotmaxvelocity)
plottemp=[]
for ion in range(len(ionnames)):
    if (len(iontemp[ion])>1):
        tmpplottemp=Data(iontemp[ion])
    else:
        tmpplottemp=Data([[0.,0.]])
#    tmpplottemp=Data(iontemp[ion])
#    tmpplotdata.set_option_colonsep("using", "1:4 ")
    tmpplottemp.set_option_colonsep("title",  "'%s Temperatur'" %(ionnames[ion]))
    tmpplottemp.set_option_colonsep("with",  "points")
    plottemp.append(tmpplottemp)
    



gp=Gnuplot()
#gp("set yrange[0:1000]")
gp("set style data dots")
gp("set xlabel 'Day'")
gp("set ylabel 'Density[1/cm³]*10^10,Velocity[km/s]*10^3,Temperatur[K]'")
gp("set logscale y")
#bestimmte Ionen plotten

o6pos=0
o7pos=0
o7o6fac=100000000.
for ion in range(len(ionnames)):
    if (ionnames[ion]=="O6+"):
        o6pos=ion
    if (ionnames[ion]=="O7+"):
        o7pos=ion
o7o6ratio=[]
for o6 in range(len(ionmaxdens[o6pos])):
    for o7 in range(len(ionmaxdens[o7pos])):
        if (ionmaxdens[o6pos][o6][0]==ionmaxdens[o7pos][o7][0]):
            o7o6ratio.append([ionmaxdens[o6pos][o6][0],o7o6fac*ionmaxdens[o7pos][o7][1]/ionmaxdens[o6pos][o6][1]])

plotratio=Data(o7o6ratio)
plotratio.set_option_colonsep("title",  "'O7/O6'")
plotratio.set_option_colonsep("with",  "points")

c5pos=0
c6pos=0
c6c5fac=100000000.
for ion in range(len(ionnames)):
    if (ionnames[ion]=="C5+"):
        c5pos=ion
    if (ionnames[ion]=="C6+"):
        c6pos=ion
c6c5ratio=[]
for c5 in range(len(ionmaxdens[c5pos])):
    for c6 in range(len(ionmaxdens[c6pos])):
        if (ionmaxdens[c5pos][c5][0]==ionmaxdens[c6pos][c6][0]):
            c6c5ratio.append([ionmaxdens[c6pos][c6][0],c6c5fac*ionmaxdens[c6pos][c6][1]/ionmaxdens[c5pos][c5][1]])

plotcratio=Data(c6c5ratio)
plotcratio.set_option_colonsep("title",  "'C6/C5'")
plotcratio.set_option_colonsep("with",  "points")


plotion=[0]
name=["He2+"]
for i in range(len(name)):
    for ion in range(len(ionnames)):
        if (ionnames[ion]==name[i]):
            plotion[i]=ion

plotelem=[]
elemname=["C","N","O","Ne","Mg","Si","S","Fe"]
for i in range(len(elemname)):
    plotelem.append(0)
for i in range(len(elemname)):
    for elem in range(len(elemnames)):
        if (elemnames[elem]==elemname[i]):
            plotelem[i]=elem


gp.plot(plotvelocity[plotion[0]])
for ion in range(len(name)-1):
    gp.replot(plotvelocity[plotion[ion+1]])

gp.replot(plotdens[plotion[0]])
for ion in range(len(name)-1):
    gp.replot(plotdens[plotion[ion+1]])
    
gp.replot(plottemp[plotion[0]])
for ion in range(len(name)-1):
    gp.replot(plottemp[plotion[ion+1]])

gp.replot(plotmaxdens[plotion[0]])
for ion in range(len(name)-1):
    gp.replot(plotmaxdens[plotion[ion+1]])

gp.replot(plotmaxvelocity[plotion[0]])
for ion in range(len(name)-1):
    gp.replot(plotmaxvelocity[plotion[ion+1]])

gp.replot(plotratio)
gp.replot(plotcratio)
plotmeancharge=[]
print "plotelem = ",plotelem
for elem in plotelem:
    print "elem = ",elem
    tmpplotmeancharge=Data(meancharge[elem])
    tmpplotmeancharge.set_option_colonsep("title",  "'meancharge %s'" %(elemnames[elem]))
    tmpplotmeancharge.set_option_colonsep("with",  "points")
    plotmeancharge.append(tmpplotmeancharge)
gp("unset logscale y")
gp.plot(plotmeancharge[0])
for elem in range(len(plotelem)-1):
    gp.replot(plotmeancharge[elem+1])
#Alle Ionen in Range plotten

"""
for ion in range(8):
    gp.replot(plotdata[ion+1])
    gp.replot(plotvelocity[ion+1])
    gp.replot(plottemp[ion+1])
gp.hardcopy("test.ps",color="true")
"""
gp.hardcopy("meancharge.ps",color="true")
