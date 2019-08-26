#!/usr/bin/python
from scipy import sqrt,exp
from numpy import array

def getvd(vp,vi,beta,polarity):
    """
    Calculates absolute value of the velocity difference vector between protons and ion species.
    vp \t-> proton velocity (absolute value)
    vi \t-> ion velocity (absolute value)
    beta \t-> angle between magnetic field vector and proton velocity vector
    polarity \t-> magnetic field polarity (1 outward, -1 inward) 
    """
    from numpy import cos,sqrt,pi
    if (polarity==1.):
        if vp**2*cos(pi-beta)**2+vi**2-vp**2>=0.:
            vd1=vp*cos(pi-beta)+sqrt(vp**2*cos(pi-beta)**2+vi**2-vp**2)
            vd2=vp*cos(pi-beta)-sqrt(vp**2*cos(pi-beta)**2+vi**2-vp**2)
            #print beta*180./pi,vd1,vd2
            if (beta<pi/2. and vd1>0.):
                return vd1
            elif (beta>=pi/2. and vd2>0.):
                return vd2
            else:
                return 0.
        else:
            return 0.
    elif (polarity==-1.):
        if vp**2*cos(beta)**2+vi**2-vp**2>=0.:
            vd1=vp*cos(beta)+sqrt(vp**2*cos(beta)**2+vi**2-vp**2)
            vd2=vp*cos(beta)-sqrt(vp**2*cos(beta)**2+vi**2-vp**2)
            #print beta*180./pi,vd1,vd2
            if (beta>pi/2. and vd1>0.):
                return vd1
            elif (beta<=pi/2. and vd2>0.):
                return vd2
            else:
                return 0.
        else:
            return 0.
    else:
        return 0.

def getvelocity(mass,charge,step,frac=1.):
    epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
    energy=(epq_arr[step]*charge*1.60217646e-19*1000.)*frac
    tmpmass=mass*1.66053886e-27
    velocity=sqrt(2.*energy)/sqrt(tmpmass)
    velocity=velocity/1000.
    return velocity

def getvelocity_allsteps(mass,charge,step,frac=1.):
    epq_arr = array([100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489])
    energy=(epq_arr[step]*charge*1.60217646e-19*1000.)*frac
    tmpmass=mass*1.66053886e-27
    velocity=sqrt(2.*energy)/sqrt(tmpmass)
    velocity=velocity/1000.
    return velocity

def getdvarr(vp,vi,ang,polarity):
    from numpy import zeros
    dvarr=zeros((len(vp)))
    for i in range(len(vp)):
        dvarr[i]=getvd(vp[i],vi[i],ang[i],polarity)
    return dvarr

def getlocaltime():
    # returns local time as string
    from time import localtime
    tmptime=localtime()
    timestr="%.2i.%.2i.%.4i %.2i:%.2i:%.2i"%(tmptime.tm_mday,tmptime.tm_mon,tmptime.tm_year,tmptime.tm_hour,tmptime.tm_min,tmptime.tm_sec)
    return timestr

def int2str(i):
    if (i<10):
        return "00%i"%(i)
    elif (i<100):
        return "0%i"%(i)
    else:
        return "%i"%(i)

def ergname(path,name):
    infile=name.split()
    outname=path+"erg_"+infile[0]
    return outname

def fluxname(path,name):
    infile=name.split()
    tmpname=infile[0]
    outname=path+"flux_"+tmpname
    return outname

def resname(path,name):
    infile=name.split()
    tmpname=infile[0]
    outname=path+"res_"+tmpname
    return outname

def elemname(path,name):
    infile=name.split()
    tmpname=infile[0]
    outname=path+"elem_"+tmpname
    return outname

def dataname(path,name):
    infile=name.split()
    tmpname=infile[0]
    dataname=path+tmpname
    return dataname

def buildnames(path,name,inname,outname,dataname):
    infile=name.split()
    inname=path+infile[0]
    tmpname=infile[0]
    tmp2name=tmpname[3:len(tmpname)]
    outname=path+"flux"+tmp2name
    tmp2name=tmpname[4:len(tmpname)]
    dataname=path+tmp2name

def ion2elem(ionname):
    go=1
    i=1
    firstchar=0
    while(go):
        try:
            int(ionname[0:i])
        except ValueError:
            firstchar=i-1
            go=0
        i=i+1
    go=1
    i=firstchar
    while(go):
        go=0
        try:
            int(ionname[i:i+1])
        except ValueError:
            i=i+1
            go=1
    return ionname[0:i]

def ionname2charge(ionname):
    go=1
    i=1
    firstchar=0
    while(go):
        try:
            int(ionname[0:i])
        except ValueError:
            firstchar=i-1
            go=0
        i=i+1
    go=1
    i=firstchar
    while(go):
        go=0
        try:
            int(ionname[i:i+1])
        except ValueError:
            i=i+1
            go=1
    start=i
    i=0
    go=1
    while(go):
        i=i+1
        try:
            int(ionname[start:start+i])
        except ValueError:
            i=i-1
            go=0
    return float(ionname[start:start+i])

"""
function
returns the position of the maximumvalue of array arr!
"""
def getmaxpos(arr):
    maxpos=0
    for step in range(len(arr)):
            if (arr[step]>arr[maxpos]):
                maxpos=step
    return maxpos

def buildelemlist(ion_list):
    elemlist=[]
    for ion in range(len(ion_list)):
        elemname=ion2elem(ion_list[ion])
        da=0
        for elem in range(len(elemlist)):
            if (elemlist[elem]==elemname):
                da=1
        if (not da):
            elemlist.append(elemname)
    return elemlist


def fgauss(x,ph,sig,x0):
    pi=3.14159265
    return ph*sqrt(1/(2.*pi))*(1/sig)*exp(-((x-x0)**2.)/(2.*sig**2))


"""
syncronizes mag to swics data
"""
def sync_mag(mag,iondata):
    print "synchronizing mag to ace data"
    syncmag=[]
    # timeres 240. -> 12m data ; 48. -> 1h data
    timeres=240.
    j=0
    for time in iondata.time:
        while (mag.magb[j][0]<time-1./timeres and j<len(mag.magb)-2):
            j+=1
        N1=0.
        N2=0.
        tmpmag=0.
        tmpalpha=0.
        tmpbeta=0.
        tmpsigalpha=0.
        tmpsigbeta=0.
        tmpalphaarr=[]
        tmpbetaarr=[]
        while (mag.magb[j][0]<time+1./timeres and j<len(mag.magb)-2):
            if (mag.magb[j][1]>0.):
                tmpmag+=mag.magb[j][1]
                N1+=1.
            if (mag.phi[j][1]<pi/2.):
                N2+=1.
                tmpalpha+=mag.phi[j][1]
                tmpbeta+=mag.theta[j][1]
                tmpalphaarr.append(mag.phi[j][1])
                tmpbetaarr.append(mag.theta[j][1])
            j+=1
        if (N1>0.):
            tmpmag=tmpmag/N1
        if (N2>0.):
            tmpalpha=tmpalpha/N2
            tmpbeta=tmpbeta/N2
            for alpha in tmpalphaarr:
                tmpsigalpha+=(alpha-tmpalpha)**2
            for beta in tmpbetaarr:
                tmpsigbeta+=(beta-tmpbeta)**2
            tmpsigalpha=sqrt(tmpsigalpha/N2)
            tmpsigbeta=sqrt(tmpsigbeta/N2)
        if (tmpalpha!=0. and tmpbeta!=0.):
            #print time,att[int(time)-1][0]
            syncmag.append([time,tmpmag,0.,tmpalpha,tmpbeta,acos(abs(cos(tmpalpha-att[int(time)-1][1])*cos(tmpbeta-att[int(time)-1][2]))),tmpsigalpha,tmpsigbeta])
        else:
            syncmag.append([time,tmpmag,0.,0.,0.,0.,0.,0.])
    j=0
    for i in range(len(syncmag)):
        while (mag.magb[j][0]<syncmag[i][0]-1./timeres and j<len(mag.magb)-2):
            j+=1
        N=0.
        tmpmag=0.
        while (mag.magb[j][0]<syncmag[i][0]+1./timeres and j<len(mag.magb)-2):
           N+=1.
           tmpmag+=(mag.magb[j][1]-syncmag[i][1])**2
           j+=1
        if (N>0.):
            syncmag[i][2]=sqrt(tmpmag/N)
    print "done"
    return syncmag

def histogram(data,start,step,nrsteps,mode):
    "mode 1 : no offset, no meanval \n mode 2 : offset, no meanval \n mode 3 : no offset, meanval \n mode 4 : offset, meanval\n mode 5 : no offset, median \n mode 6 : offset, median"
    from scipy import median
    hist=[]
    if (mode==1 or mode==3 or mode==5):
        offset=0.
    else:
        offset=0.5*step
    if (len(data[0])==1):
        for i in range(nrsteps):
            hist.append([start+offset+float(i)*step,0.])
        for val in data:
            for val2 in hist:
                if (val[0]>val2[0]-offset and val[0]<val2[0]-offset+step):
                    val2[1]+=1.
        return hist
    if (len(data[0])==2):
        for i in range(nrsteps):
            hist.append([start+offset+float(i)*step,0.,0.])

        if (mode==1 or mode==2 or mode==3 or mode==4): 
            for val in data:
                for val2 in hist:
                    if (val[0]>val2[0]-offset and val[0]<val2[0]-offset+step):
                        val2[1]+=val[1]
                        val2[2]+=1.
            if (mode==3 or mode==4):
                for val in hist:
                    if (val[2]>0.):
                        val[1]=val[1]/val[2]
            return hist
        
        if (mode==5 or mode==6): 
            tmpdat=[]
            for val in hist:
                tmpdat.append([])
            for val in data:
                i=-1
                for val2 in hist:
                    i+=1
                    if (val[0]>val2[0]-offset and val[0]<val2[0]-offset+step):
                        tmpdat[i].append(val[1])
            for i in range(len(hist)):
                hist[i][1]=median(tmpdat[i])
            return hist
            
    if (len(data[0])==3):
        for i in range(nrsteps):
            hist.append([start+offset+float(i)*step,0.,0.])

        if (mode==1 or mode==2 or mode==3 or mode==4): 
            for val in data:
                for val2 in hist:
                    if (val[0]>val2[0]-offset and val[0]<val2[0]-offset+step and val[2]>0.):
                        val2[1]+=val[1]/val[2]
                        val2[2]+=1/val[2]
            if (mode==3 or mode==4):
                for val in hist:
                    if (val[2]>0.):
                        val[1]=val[1]/val[2]
            return hist

        if (mode==5 or mode==6): 
            tmpdat=[]
            for val in hist:
                tmpdat.append([])
            for val in data:
                i=-1
                for val2 in hist:
                    i+=1
                    if (val[0]>val2[0]-offset and val[0]<val2[0]-offset+step):
                        tmpdat[i].append(val[1])
            for i in range(len(hist)):
                hist[i][1]=median(tmpdat[i])
            return hist


def sig_histogram(data,hist,mode):
    "mode 3 : no offset, meanval \n mode 4 : offset, meanval"
    sig_hist=[]
    if (len(hist)==1):
        sig_hist=[hist[0][0],0.,len(data)]
        for d in data:
            sig_hist[0][1]+=(d[1]-hist[0][1])**2
        if (sig_hist[0][2]>0):
            sig_hist[0][1]=sqrt(sig_hist[0][1]/float(sig_hist[0][2]))
    elif (len(hist)>1):
        for h in hist:
            sig_hist.append([h[0],0.,0])
        step=hist[1][0]-hist[0][0]
        for d in data:
            i=0
            if (mode==3):
                while i<len(hist)-1 and d[0]>hist[i][0]+step :
                    i+=1
            if (mode==4):
                while i<len(hist)-1 and d[0]>hist[i][0]+step/2. :
                    i+=1
            sig_hist[i][1]+=(d[1]-hist[i][1])**2
            sig_hist[i][2]+=1
        for sig in sig_hist:
            if (sig[2]>0):
                sig[1]=sqrt(sig[1]/float(sig[2]))
        return sig_hist

def circle(x,y,r,dim):
    "x,y -> float; position of center \n r -> float; radius\n dim -> integer; number of points (should be odd)\n returns array containing circle"  
    dim=41
    carr=[]
    for i in range(dim):
        dx=1.-float(i)/float((dim-1)/2.)
        dy=sqrt(1.-dx**2)
        carr.append([x+dx*r,y+dy*r])
    for i in range(dim):
        dx=-1.+float(i)/float((dim-1)/2.)
        dy=sqrt(1.-dx**2)
        carr.append([x+dx*r,y-dy*r])
    carr.append([x+r,y])
    return carr

def test():
    "does nothing ... just for testing reasons ..."
    return 1

def numint(dat,x0,x1):
    "returns numerical integral of data\ninput:\ndat\t->\tarray[N,2]\nx0,x1\t->\tlower and upper limit for integration"
    integral=0.
    for i in range(len(dat)):
        if i==0:
            dx=dat[i][0]-dat[i][0]
        elif i==len(dat)-1:
            dx=dat[-1][0]-dat[-2][0]
        else:
            dx=(dat[i+1][0]-dat[i-1][0])/2.
        if (dat[i][0]>=x0 and dat[i][0]<=x1):
            integral+=dx*dat[i][1]
    return integral

def getnewex(phi,theta):
    x=sqrt(1./(1+tan(phi)**2+tan(theta)**2+tan(phi)**2*tan(theta)**2))
    y=tan(phi)*x
    z=tan(theta)*sqrt(x**2*(1+tan(phi)**2))
    if phi==pi/2.:
        x,y,z=0.,1.,0.
    if phi==-pi/2.:
        x,y,z=0.,-1.,0.
    return array([x,y,z])
def getnewey(phi):
    y=1./sqrt(1+tan(phi)**2)
    x=-tan(phi)*y
    return array([x,y,0.])

def getnewez(x,y):
    z1=x[1]*y[2]-x[2]*y[1]
    z2=x[2]*y[0]-x[0]*y[2]
    z3=x[0]*y[1]-x[1]*y[0]
    return array([z1,z2,z3])

def rot2d(x0,y0,ang):
    """
    rotiert in x0,y0 Ebene um Winkel ang
    """
    from numpy import cos,sin
    x=x0*cos(ang)-y0*sin(ang)
    y=y0*cos(ang)+x0*sin(ang)
    return x,y
