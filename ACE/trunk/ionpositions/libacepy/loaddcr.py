#from numpy import zeros,loadtxt,array
from numpy import *
def loaddcr(filename):
    cycles=0.
    aspang=0.
    swspeed=0.

    #read header
    dataarr=zeros([58,512])
    try:
        datain=open(filename,"r")
        tmp=""
        while(tmp!="*****"):
            s=datain.readline()
            k=s.split()
            tmp=k[0]
            if (tmp=="Cycles"):
                cycles=int(k[2])
            if (tmp=="Aspang"):
                aspang=float(k[2])
            if (tmp=="SWSpeed"):
                swspeed=float(k[2])
        data=loadtxt(datain)
        x=array(data[0],dtype='int32')
        y=array(data[1],dtype='int32')
        dataarr[x,y]=data[2]
    except:
        print "Problems reading : ",filename
    return dataarr,swspeed,aspang,cycles

def loaddcr_new(filename):
    cycles=0.
    aspang=0.
    swspeed=0.

    #read header
    try:
        datain=open(filename,"r")
        tmp=""
        while(tmp!="*****"):
            s=datain.readline()
            k=s.split()
            tmp=k[0]
            if (tmp=="Cycles"):
                cycles=int(k[2])
            if (tmp=="Aspang"):
                aspang=float(k[2])
            if (tmp=="SWSpeed"):
                swspeed=float(k[2])
        data=loadtxt(datain)
        epq=array(data[0])
        tof=array(data[1])
        cts=array(data[2])
        swspeed=ones(epq.shape)*swspeed
        aspang=ones(epq.shape)*aspang
    except:
        print "Problems reading : ",filename
        epq=array([]) 
        tof=array([]) 
        cts=array([]) 
        swspeed=array([]) 
        aspang=array([]) 
    return epq,tof,cts,swspeed,aspang
