#!/usr/bin/python
from numpy import float
from scipy import zeros,sqrt

def loadsrim(ionname,tofpos,epos):
    dim=58
    tmpname="/home/ivar/berger/projects/ionpositions/mudata/paps24/"
    tmpname=tmpname+ionname
    etmpname=tmpname+".en"
    ttmpname=tmpname+".tof"
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
    f.close()
    f=open(ttmpname)
    for i in range(dim):
        s=f.readline()
        k=s.split()
        if k[2]=="NAN":
            tofpos[i]=1200.
        else:
            tofpos[i]=float(k[2])
    f.close()

    
        
def getnumions():
    f=open("/home/ivar/berger/projects/ionpositions/ions.dat")
    s=f.readline()
    s=f.readline()
    k=s.split()
    print "Number of ions = ",int(k[0])
    f.close()
    return int(k[0])

def getions(numions,names,masses,charges):
    f=open("/home/ivar/berger/projects/ionpositions/ions.dat")
    for i in range(4):
        s=f.readline()
    for i in range(numions):
        s=f.readline()
        k=s.split()
        names[i]=str(k[0])
        masses[i]=float(k[1])
        charges[i]=float(k[2])
        print "loaded ",names[i]
    f.close()

def writeheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\typos\tsigxp\tsigxm\tsigyp\tsigym\tvel\tmass\tcharge\t\tpeakhigh\n")

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh):
    file.write("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh))


def getvelocity(velocity,mass,charge,dim,ion):
    epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
    energy=zeros([dim],float)
    for i in range(dim):
        energy[i]=epq_arr[i]*charge*1.60217646e-19*1000.
    tmpmass=mass*1.66053886e-27
    for i in range(dim):
#        print "tmpmass = ",tmpmass
        velocity[i][ion]=sqrt(2.*energy[i])/sqrt(tmpmass)
        velocity[i][ion]=velocity[i][ion]/1000.

def getsig(dim,xpos,ypos,sigx,sigy):
    for i in range(dim):
        sigx[i]=0.02*xpos[i]
        sigy[i]=0.10*ypos[i]
        if (sigy[i]<1.5):
            sigy[i]=1.5
        if (sigx[i]<1.5):
            sigx[i]=1.5
                


def writefile(name):
    file=open(name,"w")

    dim=58
    numions=getnumions()
    masses=zeros([numions],float)
    charges=zeros([numions],float)
    velocities=zeros([dim,numions],float)
    peakh=zeros([numions,dim],float)
    tmpstr=""
    for i in range(numions):
        tmpstr=tmpstr+"x "
    names=tmpstr.split()

    getions(numions,names,masses,charges)
    for i in range(numions):
        getvelocity(velocities,masses[i],charges[i],dim,i)
    for step in range(dim):
        print "writing step ",step+1
        writeheader(file,numions,step+1)
        x=zeros([dim],float)
        y=zeros([dim],float)
        for ion in range(numions):
            x=zeros([dim],float)
            y=zeros([dim],float)
            sigx=zeros([dim],float)
            sigy=zeros([dim],float)
            loadsrim(names[ion],x,y)
            getsig(dim,x,y,sigx,sigy)
            peakh=0.
#            print "main : ",peakh
            writeion(file,names[ion],x[step],y[step],sigx[step],sigx[step],sigy[step],sigy[step],velocities[step][ion],masses[ion],charges[ion],peakh)
    file.close()
                
filename="/home/ivar/berger/projects/ionpositions/paramfiles/ion_para_new.dat"
writefile(filename)
