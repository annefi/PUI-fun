#!/usr/bin/python
from numpy import float
from scipy import zeros
#from Gnuplot import Gnuplot, GridData, Data

def loadmu(ionname,tofpos,epos):
    dim=58
    tmpname="/home/ivar/berger/projects/ionpositions/mudata/paps24/"
    tmpname=tmpname+ionname
    #[:len(ionname)]
    etmpname=tmpname+".en"
    ttmpname=tmpname+".tof"
#    print etmpname,ttmpname
    f=open(etmpname)
    for i in range(dim):
        s=f.readline()
        k=s.split()
#        print "k[2]=",k[2]
        if k[2]=="NAN":
#            print "k[2]=",k[2]
            epos[i]=300.
        else:
            epos[i]=float(k[2])
#        print "epos[",i,"]=",epos[i]
    f.close()
    f=open(ttmpname)
    for i in range(dim):
        s=f.readline()
        k=s.split()
        if k[2]=="NAN":
#            print "k[2]=",k[2]
            tofpos[i]=1200.
        else:
            tofpos[i]=float(k[2])
    f.close()


def getionname(filen,ionname):
    s=filen.readline()
    k=s.split()
    return k[0]
    

def writeheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\typos\tsigxp\tsigxm\tsigyp\tsigym\tvel\tmass\tcharge\t\tpeakhigh\n")

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh):
    file.write("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh))


dim=58
ionlist=open("/home/ivar/berger/projects/ionpositions/mudata/ions.dat")
cpin=open("/home/ivar/berger/projects/ionpositions/paramfiles/ion_para_fmjim.dat")
cpout=open("/home/ivar/berger/projects/ionpositions/paramfiles/ion_para_fmjim_tmp.dat","w")
for line in cpin:
    cpout.write(line)
cpin.close()
cpout.close()

for ions in ionlist:
    s=ions.split()
    if (len(s)>0):
        ionname=s[0]
        print ionname
        tpos=zeros([dim],float)
        epos=zeros([dim],float)
        loadmu(ionname,tpos,epos)
        parain=open("/home/ivar/berger/projects/ionpositions/paramfiles/ion_para_fmjim_tmp.dat")
        paraout=open("/home/ivar/berger/projects/ionpositions/paramfiles/ion_para_fmjim_mu.dat","w")
        step=0
        for line in parain:
            k=line.split()
            if (ionname==k[0]):
                if ((tpos[step]!=1200.)and(epos[step]!=300.)):
                    writeion(paraout,k[0],tpos[step],epos[step],float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]))
                else:
                    paraout.write(line)
                step=step+1
            else:
                paraout.write(line)
        parain.close()
        paraout.close() 
        cpin=open("/home/ivar/berger/projects/ionpositions/paramfiles/ion_para_fmjim_mu.dat")
        cpout=open("/home/ivar/berger/projects/ionpositions/paramfiles/ion_para_fmjim_tmp.dat","w")
        for line in cpin:
            cpout.write(line)
        cpin.close()
        cpout.close()
