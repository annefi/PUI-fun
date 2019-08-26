from numpy import zeros,loadtxt,array

def loadtcr(filename,ion):
    cycles=0.
    aspang=0.
    swspeed=0.

    hedata=zeros([58])
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
        for step in range(58):
            s=datain.readline()
            k=s.split()
            #print step+1,int(k[2])
            if step+1!=int(k[2]):
                return hedata,0.
            nions=int(k[5])
            for i in range(nions+1):
                s=datain.readline()
                k=s.split()
                if (k[0]==ion):
                    hedata[step]=float(k[11])
        return hedata,swspeed
    except:
        print "Problems reading : ",filename
        return hedata,0.
