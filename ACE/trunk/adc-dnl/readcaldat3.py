#!/usr/bin/python
from scipy.linalg import inv
from scipy import zeros, Float, matrixmultiply
from Gnuplot import Gnuplot, GridData

data=zeros([1024,256],Float)
data2=zeros([1024,256],Float)
peak=zeros([100,3],Float)
locatedpeak=zeros([100,3],Float)
vektor=zeros([100,2],Float)
abstand=zeros([100],Float)
param=zeros([100,2],Float)
mid=zeros([100,2],Float)
ssd=zeros([3],Float)
gp=Gnuplot()
datagrid=None
data2grid=None

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
    global data2grid
    datagrid=GridData(data)
    data2grid=GridData(data)
  
def plotten():
    gp("set logscale z")
    gp("set zrange[1:1000]")
    #gp("set palette rgbformula -3,-3,-3")
    #gp("test palette")
    gp("set xrange[300:600]")
    gp("set yrange[0:100]")
    gp("set pm3d map")
    gp.splot(datagrid,data2grid)

def nullen():
    for i in range(1,1024):
        for j in range(1,256):
            data[i,j]=0.
    for i in range(1,100):
        abstand[i]=0.
        for j in range(1,3):
            peak[i,j]=0
            locatedpeak[i,j]=0.
        for j in range(1,2):
            vektor[i,j]=0.
            param[i,j]=0.
            mid[i,j]=0.
    for i in range(1,3):
        ssd[i]=0.
    datagrid=None
    
    
def maxfinder():
    for i in range(1,1024):
        for j in range(1,256):
            if peak[0,2] < data[i,j]:
                peak[0,0] = i
                peak[0,1] = j
                peak[0,2] = data[i,j]

anfang=106
ende=106
intervall=ende-anfang+1
for j in range(intervall):
    try:
        f=open("/home/kleopatra/mu/daten/giessen/swxli"+str(j+anfang)+".pha")
        print "loading data",j+anfang
#        nullen()
        einlesen(f)
#        plotten()
    
    except StandardError:
        print "Datei",j+anfang,"existiert nicht"
        
plotten()

for i in range(1,1024):
    for j in range(1,256):
        if peak[0,2] < data[i,j]:
            peak[0,0] = i
            peak[0,1] = j
            peak[0,2] = data[i,j]

#print peak[0,0], peak[0,1], peak[0,2]
k = 1


for i in range(1,1024):
    for j in range(1,256):
        if not data[i,j] < (peak[0,2])/5:
            m = 0
            for u in range((i-3),(i+3)):
                for v in range((j-3),(j+3)):
                    if not data[i,j] < data[u,v]:
                        m+=1
            if m == 36:
                peak[k,0] = i
                peak[k,1] = j
                peak[k,2] = data[i,j]
                k+=1

#print k
l = 0                                           
for i in range(1,k):
    vektor[i,0] = peak[i,0] - peak[0,0]
    vektor[i,1] = peak[i,1] - peak[0,1]
#    print vektor[i,0], vektor[i,1]
    abstand[i]=((vektor[i,0])**2+(vektor[i,1])**2)**0.5
#    print abstand[i]
    
#    print abstand[i]
    if abstand[i] > 10:
#        print i
        param[i,0] = int((peak[i,0]-peak[0,0])/2+0.5)
        param[i,1] = int((peak[i,1]-peak[0,1])/2+0.5)
        mid[i,0] = peak[0,0] + param[i,0]
        mid[i,1] = peak[0,1] + param[i,1]
#        print mid[i,0], mid[i,1]
#        print data[int(mid[i,0]),int(mid[i,1])],data[int(peak[i,0]),int(peak[i,1])]
        if data[int(mid[i,0]),int(mid[i,1])] < data[int(peak[i,0]),int(peak[i,1])]:
            locatedpeak[l,0]=peak[i,0]
            locatedpeak[l,1]=peak[i,1]
            locatedpeak[l,2]=peak[i,2]
            l+=1
            

#print l
if l > 0:
    print "CONTAMINATION!!! Es gibt ",l+1," Peaks"
    print "Der Haupt-Peak ist am Punkt  [",peak[0,0],",",peak[0,1],"] und hat ",peak[0,2]," Counts." 
    for i in range(l):
        print "Peak ",i+1," ist am Punkt [",locatedpeak[i,0],",",locatedpeak[i,1],"] und hat ",locatedpeak[i,2]," Counts." 
else:
    print "SAUBER ---> KEINE CONTAMINATION."
    print "Der Peak ist am Punkt  [",peak[0,0],",",peak[0,1],"] und hat ",peak[0,2]," Counts." 
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
    

