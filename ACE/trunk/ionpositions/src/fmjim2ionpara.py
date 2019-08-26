#!/usr/bin/python
from scipy import zeros,sqrt
from numpy import float
from sys import stdin

def velocity(E,q,m):
    elq=1.60217653*10**(-19)         # elementarladung
    pm=1.67262158*10**(-27)          # protonenmasse
    return ((sqrt((E*10**(3)*q*2*elq)/(m*pm)))/10**(3))

def writeheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\typos\tsigxp\tsigxm\tsigyp\tsigym\tvel\tmass\tcharge\t\tpeakhigh\n")

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh):
    file.write("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh))


dim=58
nrionsjim=77

fmfilename="/data/ivar/berger/work/america/runs/1999001_1d/axlv2_fmcomp.dat"
parafilename="/home/ivar/berger/projects/ionpositions/paramfiles/ion_para_fmjim_21.dat"

# determine number of ions per step

numberions=zeros([dim])
iondat=zeros([dim,nrionsjim,11],float)
ionuse=zeros([dim,nrionsjim])
ionnames=[]

mass=[1.,3.,3.,4.,4.,12.,12.,12.,12.,12.,12.,14.,14.,14.,14.,14.,14.,14.,16.,16.,16.,16.,16.,16.,16.,16.,20.,20.,20.,20.,24.,24.,24.,24.,24.,24.,24.,28.,28.,28.,28.,28.,28.,28.,32.,32.,32.,32.,32.,32.,32.,32.,32.,56.,56.,56.,56,56.,56.,56.,56,56.,56.,56.,56,56.,56.,56.,56,56.,56.,56.,56,56.,56.,56.,56]
charge=[1.,1.,2.,1.,2.,1.,2.,3.,4.,5.,6.,1.,2.,3.,4.,5.,6.,7.,1.,2.,3.,4.,5.,6.,7.,8.,6.,7.,8.,9.,6.,7.,8.,9.,10.,11.,12.,6.,7.,8.,9.,10.,11.,12.,6.,7.,8.,9.,10.,11.,12.,13.,14.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.,17.,18.,19.,20.,21.,22.,23.,24.]

fmin=open(fmfilename)
paraout=open(parafilename,"w")

fmin.readline()
fmin.readline()
fmin.readline()

for step in range(dim):
    writeheader(paraout,nrionsjim,step+1)
    for ion in range(nrionsjim):
        s=fmin.readline()
        k=s.split()
        iondat[step][ion][8]=mass[ion]
        iondat[step][ion][9]=charge[ion]
        vel=velocity(float(k[1]),iondat[step][ion][9],iondat[step][ion][8])
        iondat[step][ion][7]=float(vel)
        ionnames.append(k[2])
        iondat[step][ion][1]=((float(k[3])/2.)+0.75)
        iondat[step][ion][2]=((float(k[5])/2.)+0.75)
        iondat[step][ion][3]=((float(k[4])/2.))
        iondat[step][ion][4]=((float(k[4])/2.))
        iondat[step][ion][5]=((float(k[6])/2.))
        iondat[step][ion][6]=((float(k[6])/2.))
        iondat[step][ion][10]=(0.)

        writeion(paraout,ionnames[ion],iondat[step][ion][1],iondat[step][ion][2],iondat[step][ion][3],iondat[step][ion][4],iondat[step][ion][5],iondat[step][ion][6],iondat[step][ion][7],iondat[step][ion][8],iondat[step][ion][9],iondat[step][ion][10])

    print ionnames[ion],iondat[step][ion]
paraout.close()


print len(mass)
#for step in range(1,dim+1):
#    s=fmin.readline()
#    k=s.split()
    
