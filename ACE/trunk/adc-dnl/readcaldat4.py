#!/usr/bin/python
from scipy.linalg import inv
from scipy import zeros, Float, matrixmultiply
from Gnuplot import Gnuplot, GridData

data=zeros([1024,256],Float)
sp=zeros([1000,100],Float)
pp=zeros([1000],Float)
ediff=zeros([1000],Float)
tdiff=zeros([1000],Float)
peak=zeros([1000,3],Float)
locatedpeak=zeros([1000,3],Float)
vektor=zeros([1000,2],Float)
abstand=zeros([1000],Float)
param=zeros([1000,2],Float)
mid=zeros([1000,2],Float)
ssd=zeros([3],Float)
gp=Gnuplot()
datagrid=None
counter=0
esum=0
tsum=0
gkp=zeros([100],Float)

r=0
ff=open("/home/kleopatra/mu/Desktop/testsi")
for i in ff:
    ss=i.split()
    for j in range(5):
        sp[r,j]=float(ss[j])
#        print r,j,sp[r,j]
    r+=1
#read data from file "x"
def einlesen(x):
    for i in range(3):
        x.readline()

    for i in x:
        s=i.split()
        data[int(s[1]),int(s[0])]+=1
        if int(s[2]) == 1:
            ssd[0]+=1
        if int(s[2]) == 2:
            ssd[1]+=1   
        if int(s[2]) == 3:
            ssd[2]+=1
#    print ssd[0]
#    print ssd[1]
#    print ssd[2]
    global datagrid
    datagrid=GridData(data)
  
def plotten():
    gp("set logscale z")
    gp("set zrange[1:1000]")
    #gp("set palette rgbformula -3,-3,-3")
    #gp("test palette")
    gp("set xrange[0:1024]")
    gp("set yrange[0:256]")
    gp("set pm3d map")
    gp.splot(datagrid)


    
def maxfinder():
    for i in range(1,1024):
        for j in range(1,256):
            if peak[0,2] < data[i,j]:
                peak[0,0] = i
                peak[0,1] = j
                peak[0,2] = data[i,j]
                
def peakfinder():
    global d
    d=3
    global k
    k = 1
    print k
    for i in range(d,1024-d):
        for j in range(d,256-d):
            ll=0
            if not data[i,j] < (peak[0,2])/5:
                m = 0
                for u in range((i-d),(i+d+1)):
                    for v in range((j-d),(j+d+1)):
#                        if not data[i,j] < data[u,v]:
                        m+=1
                if m == ((2*d)+1)**2:
                    peak[k,0] = i
                    peak[k,1] = j
                    peak[k,2] = data[i,j]
                    k+=1

                    
def peakchecker():
    global l
    l = 0                                           
    for i in range(1,k):
        vektor[i,0] = peak[i,0] - peak[0,0]
        vektor[i,1] = peak[i,1] - peak[0,1]
#        print vektor[i,0], vektor[i,1]
        abstand[i]=((vektor[i,0])**2+(vektor[i,1])**2)**0.5
#        print abstand[i]
    
#        print abstand[i]
        if abstand[i] > 10:
#            print i
            param[i,0] = int((peak[i,0]-peak[0,0])/2+0.5)
            param[i,1] = int((peak[i,1]-peak[0,1])/2+0.5)
            mid[i,0] = peak[0,0] + param[i,0]
            mid[i,1] = peak[0,1] + param[i,1]
#            print mid[i,0], mid[i,1]
#            print data[int(mid[i,0]),int(mid[i,1])],data[int(peak[i,0]),int(peak[i,1])]
            if data[int(mid[i,0]),int(mid[i,1])] < data[int(peak[i,0]),int(peak[i,1])]:
                locatedpeak[l,0]=peak[i,0]
                locatedpeak[l,1]=peak[i,1]
                locatedpeak[l,2]=peak[i,2]
                l+=1

def auswurf():
    if l > 0:
        print "CONTAMINATION!!! Es gibt ",l+1," Peaks"
        print "Der Haupt-Peak ist am Punkt  [",peak[0,0],",",peak[0,1],"] und hat ",peak[0,2]," Counts." 
        for i in range(l):
            print "Peak ",i+1," ist am Punkt [",locatedpeak[i,0],",",locatedpeak[i,1],"] und hat ",locatedpeak[i,2]," Counts." 
    else:
        print "SAUBER ---> KEINE CONTAMINATION."
        print "Der Peak ist am Punkt  [",peak[0,0],",",peak[0,1],"] und hat ",peak[0,2]," Counts." 

        
def nullen():
    for i in range(1024):
        for j in range(256):
            data[i,j]=0.
    for i in range(100):
        abstand[i]=0.
        for j in range(3):
            peak[i,j]=0
            locatedpeak[i,j]=0.
        for j in range(2):
            vektor[i,j]=0.
            param[i,j]=0.
            mid[i,j]=0.
    for i in range(3):
        ssd[i]=0.
    datagrid=None
    
def auswertung(nummer):
    dd=5
    if (abs((sp[nummer,4])-(peak[0,0])))>dd and (abs((sp[nummer,2])-(peak[0,1])))>dd:
        print "!!!!!!!!!!!!!!PEAK VERSCHOBEN!!!!!!!!!!!!!"
        print "Die erwartete Position des Peaks ist [",sp[nummer,4],",",sp[nummer,2],"]"
        print "Der Position des Kalibrationspeaks ist [",peak[0,0],",",peak[0,1],"]"
        print "Die Abweichung beträgt [",((sp[nummer,4])-(peak[0,0])),",",((sp[nummer,2])-(peak[0,1])),"]"
        print "                                                                 "
    elif (abs((sp[nummer,4])-(peak[0,0])))>dd:
        print "!!!!!!!!!!!!!!PEAK VERSCHOBEN!!!!!!!!!!!!!"
        print "Die erwartete Position des Peaks ist [",sp[nummer,4],",",sp[nummer,2],"]"
        print "Der Position des Kalibrationspeaks ist [",peak[0,0],",",peak[0,1],"]"
        print "Die Abweichung beträgt [",((sp[nummer,4])-(peak[0,0])),",",((sp[nummer,2])-(peak[0,1])),"]"
        print "                                                                 "
    elif (abs((sp[nummer,2])-(peak[0,1])))>dd:
        print "!!!!!!!!!!!!!!PEAK VERSCHOBEN!!!!!!!!!!!!!"
        print "Die erwartete Position des Peaks ist [",sp[nummer,4],",",sp[nummer,2],"]"
        print "Der Position des Kalibrationspeaks ist [",peak[0,0],",",peak[0,1],"]"
        print "Die Abweichung beträgt [",((sp[nummer,4])-(peak[0,0])),",",((sp[nummer,2])-(peak[0,1])),"]"
        print "                                                                 "
    else:
        print "*****************OK**************"
        print "Die erwartete Position des Peaks ist [",sp[nummer,4],",",sp[nummer,2],"]"
        print "Der Position des Kalibrationspeaks ist [",peak[0,0],",",peak[0,1],"]"
        print "Die Abweichung beträgt [",((sp[nummer,4])-(peak[0,0])),",",((sp[nummer,2])-(peak[0,1])),"]"
        print "                                                                 "
        global counter
        global esum
        global tsum
        gkp[counter]=pp[nummer]
        tdiff[counter]=((sp[nummer,4])-(peak[0,0]))
        ediff[counter]=((sp[nummer,2])-(peak[0,1]))
        counter+=1
        print counter
        

r=0
p=open("/home/kleopatra/mu/Desktop/swics/efficiencies/pha/sipha.f")
for i in p:
    ss=i.split()
    pp[r]=float(ss[0])
#    print pp[r]
    r+=1
#print "hier ist pp1", pp[1]

anfang=1
ende=99
intervall=ende-anfang+1
for z in range(intervall):
    try:
        f=open("/home/kleopatra/mu/daten/giessen/swxli"+str(int(pp[z]))+".pha")
    except IOError:
        print "Datei",pp[z],"existiert nicht"
        continue
    print "loading data",pp[z]
    nullen()
    einlesen(f)
    maxfinder()
    peakfinder()
    peakchecker()
    auswurf()
    auswertung(z)
    plotten()

for i in range(counter):
    tsum=tsum+tdiff[i]
    esum=esum+ediff[i]
    print gkp[i]
    
#print esum/counter
#print tsum/counter
        
#plotten()
    
############### anfang so sah es früher aus#####################    
#anfang=127
#ende=127
#intervall=ende-anfang+1
#for z in range(intervall):
#    try:
#        f=open("/home/kleopatra/mu/daten/giessen/swxli"+str(z+anfang)+".pha")
#        print "loading data",z+anfang
#        nullen()
#        einlesen(f)
#        maxfinder()
#        peakfinder()
#        peakchecker()
#        auswurf()
#        plotten()
#    
#    except StandardError:
#        print "Datei",z+anfang,"existiert nicht"
        
#plotten()
############### ende so sah es früher aus#####################     
    
#gp("set term postscript")
#gp("set outp X11")
#gp("set data style line")
#gp("set xrange[580:800]")
#gp.plot(summe,corrsumme)
#gp.plot(summe,corrsumme, corrsumme_left)

#example how to write a file

#cfile=open("ramp.corr", "w")
#for i in range(1024):
#    for j in range(1024):
#        cfile.write("%f\t" % corrmtx_norm[i,j])
#    cfile.write("\n")
    

