#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean
from Gnuplot import Gnuplot, GridData, Data

def loadsrim(ionname,tofpos,epos):
    dim=58
    tmpname="/home/ivar/berger/projects/ionpositions/srimdata/"
    tmpname=tmpname+"srim"+ionname[:len(ionname)-1]
    etmpname=tmpname+"dl500ft25.mu"
    ttmpname=tmpname+"ft25.mu"
#    print etmpname,ttmpname
    f=open(etmpname)
    for i in range(dim):
        s=f.readline()
        k=s.split()
#        print "k[2]=",k[2]
        if k[2]=="NAN":
#            print "k[2]=",k[2]
            epos[i]=200.
        else:
            epos[i]=float(k[2])
        if epos[i]>252.:
            epos[i]=200.
        epos[i]=0.5*epos[i]+0.75
#        print "epos[",i,"]=",epos[i]
    f.close()
    f=open(ttmpname)
    for i in range(dim):
        s=f.readline()
        k=s.split()
        if k[2]=="NAN":
#            print "k[2]=",k[2]
            tofpos[i]=1000.
        else:
            tofpos[i]=float(k[2])
        tofpos[i]=0.5*tofpos[i]+0.75
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

def writeion(file,name,mass,charge,tpos,epos,peakh,velocity):
    file.write("%s\t\t%f\t%f\t%f\t%f\t%f\t%f\n" %(name,mass,charge,tpos,epos,peakh,velocity))

def writeheader(file,numions,step):
    file.write("E/Q-Step :\t"+str(step)+"\tNumber Ions :\t"+str(numions)+"\n")
    file.write("Name\t\tMass\t\tCharge\t\tTCH\t\tECH\t\tPeak\t\tVeloc.\n")

def getpeakh(xpos,ypos,step):
    data=open("/home/ivar/berger/projects/ionpositions/axlv2_sumwhol_asp_00.0-15.0_bin.dat")
#    print "loading axlv2_sumwhol_asp_00.0-15.0_bin.dat"
    xdim=512
    ydim=128
    peakh=1.

    et_mat=zeros([xdim,ydim],Float)
    for j in range(step-1):
        s=data.readline()
        for i in range(xdim):
            s=data.readline()

    s=data.readline()
    for i in range(xdim):
        s=data.readline()
        line=s.split()
        for k in range(ydim):
            if (float(line[k]) > -1.):
                et_mat[i][k]=float(line[k])
    peakh=et_mat[int(xpos)][int(ypos)]
    if peakh==0.:
        peakh=1.        
    return peakh

def getvelocity(velocity,mass,charge,dim,ion):
    epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
    energy=zeros([dim],Float)
    for i in range(dim):
        energy[i]=epq_arr[i]*charge*1.60217646e-19*1000.
    tmpmass=mass*1.66053886e-27
    for i in range(dim):
#        print "tmpmass = ",tmpmass
        velocity[i][ion]=sqrt(2.*energy[i])/sqrt(tmpmass)
        velocity[i][ion]=velocity[i][ion]/1000.

def writefile(name):
    file=open(name,"w")

    dim=58
    numions=getnumions()
    masses=zeros([numions],Float)
    charges=zeros([numions],Float)
    velocities=zeros([dim,numions],Float)
    peakh=zeros([numions,dim],Float)
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
        x=zeros([dim],Float)
        y=zeros([dim],Float)
        for ion in range(numions):
            x=zeros([dim],Float)
            y=zeros([dim],Float)
            loadsrim(names[ion],x,y)
            peakh=getpeakh(x[step],y[step],step)
#            print "main : ",peakh
            writeion(file,names[ion],masses[ion],charges[ion],x[step],y[step],peakh,velocities[step][ion])
        file.write("*******************************************************\n")    
    file.close()
                
filename="/home/ivar/berger/projects/ionpositions/ion_pos_41.dat"
writefile(filename)
