#!/usr/bin/python
from scipy import sqrt
from numpy import float
from libacepy.fluxes import dutycycle

def writeheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\typos\tsigxp\tsigxm\tsigyp\tsigym\tvel\tmass\tcharge\t\tpeakh\tnormh\tflux\t\tdens\n")

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh,normh,flux,dens):
    file.write("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\t%.2f\t%.4e\t%.4e\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh,normh,flux,dens))


def getvelocityp(mass,charge,step):
    epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
    energy=(epq_arr[step]*charge*1.60217646e-19*1000.)*1.03
    tmpmass=mass*1.66053886e-27
    velocity=sqrt(2.*energy)/sqrt(tmpmass)
    velocity=velocity/1000.
    return velocity

def getvelocitym(mass,charge,step):
    epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
    energy=(epq_arr[step]*charge*1.60217646e-19*1000.)*0.97
    tmpmass=mass*1.66053886e-27
    velocity=sqrt(2.*energy)/sqrt(tmpmass)
    velocity=velocity/1000.
    return velocity

def getdeltav(mass,charge,step):
    vp=0.
    vm=0.
    vp=getvelocityp(mass,charge,step)
    vm=getvelocitym(mass,charge,step)
    deltav=vp-vm
#    if (step==30):
#        print "deltav = ",deltav
    return deltav

dim=58
geomf=0.0225

liste =open("erglist.dat")
s=liste.readline()
k=s.split()
path=k[0]
print "path = ",path
for s in liste:
    eff=0.
    infile=s.split()
    print infile[0]
    infilename=path+infile[0]
    print infile[0][3:len(infile)-1]
    tmpname=infile[0]
    tmp2name=tmpname[3:len(tmpname)]
    outfilename=path+"flux"+tmp2name
    tmp2name=tmpname[4:len(tmpname)]
    print tmp2name
    datafilename=path+tmp2name
    f=open(datafilename)
    s=f.readline()
    k=s.split()
    cycles=int(k[2])
    f.close()
    print outfilename
    f=open(infilename)
    fluxf=open(outfilename,"w")

    for step in range(dim):
        s=f.readline()
        k=s.split()
        s=f.readline()
        numions=int(k[5])
        writeheader(fluxf,numions,step+1)
        for ion in range(numions):
            deltav=0.
            s=f.readline()
            k=s.split()
            efff=open("/data/wimmer/ace/efficencies/"+k[0]+".eff")
            for stepeff in range(step+1):
                s2=efff.readline()
                k2=s2.split()
                eff=float(k2[1])
            if (eff>0.):
                flux=(float(k[11])*(1./(float(cycles)*12.*dutycycle(3.0,0.0))))/(0.0225*eff)
            else:
                flux=0.
            dens=flux/(float(k[7])*100000.)
            deltav=getdeltav(float(k[8]),float(k[9]),step)
            flux=flux/(deltav*1000.)
            dens=dens/(deltav*1000.)
            if (k[0]=="Fe9+"):
                print "step = ",step,"velocity = ",float(k[7]),"deltav = ",deltav*1000.," flux = ",flux," dens = ",dens," fit = ",float(k[10])," norm = ",float(k[11])," eff = ",float(eff) 
            writeion(fluxf,k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]),float(k[11]),flux,dens)
            efff.close()

    f.close()
    fluxf.close()


