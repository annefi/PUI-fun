def SWAPR(a,r,c,l):
    temp=a[r][l]
    temp2=a[c][l]
    a[r][l]=temp2
    a[c][l]=temp
def SWAPC(a,k,r,c):
    temp=a[k][r]
    temp2=a[k][c]
    a[k][r]=temp2
    a[k][c]=temp
    

def gaussj(a,n,b,m):
    from numpy import zeros
    indxc=zeros([n],int)
    indxc+=1
    indxr=zeros([n],int)
    indxr+=1
    ipiv=zeros([n],int)
    for i in range(n):
        big=0.0
        for j in range(n):
            if (ipiv[j] != 1):
                for k in range(n):
                    if (ipiv[k]==0):
                        if (abs(a[j][k]) >= big):
                            big=abs(a[j][k])
                            irow=j
                            icol=k
                    elif (ipiv[k]>1):
                        print "gaussj: Singular Matrix-1"
        ipiv[icol]+=1
        if (irow!=icol):
            for l in range(n):
                SWAPR(a,irow,icol,l)
            for l in range(m):
                SWAPR(b,irow,icol,l)
        indxr[i]=irow
        indxc[i]=icol
        if (a[icol][icol]==0.):
            print "gaussj: Singular Matrix-2"
            pivinv=1.
        else:
            pivinv=1./a[icol][icol]
        
        a[icol][icol]=1.
        for l in range(n):
            a[icol][l]*=pivinv
        for l in range(m):
            b[icol][l]*=pivinv
        for ll in range(n):
            if (ll != icol):
                dum=a[ll][icol]
                a[ll][icol]=0.
                for l in range(n):
                    a[ll][l]-=a[icol][l]*dum
                for l in range(m):
                    b[ll][l]-=b[icol][l]*dum
    for l in range(n-1,-1,-1):
        if (indxr[l] != indxc[l]):
            for k in range(n):
                SWAPC(a,k,indxr[l],indxc[l])
    del ipiv
    del indxr
    del indxc

def covsrt(covar,ma,ia,mfit):
    for i in range(mfit,ma):
        for j in range(i):
            covar[i][j]=covar[j][i]=0.
    k=mfit-1
    #rint "covsrt : covar1 ",covar
    for j in range(ma-1,-1,-1):
        if (ia[j]):
            for i in range(ma):
                #print "covsrt : i,j,k ",i,j,k
                SWAPC(covar,i,k,j)
                #print "covsrt : covar3 ",covar
            for i in range(ma):
                SWAPR(covar,k,j,i)
            #print "covsrt : covar3 ",covar
            k-=1

class dutyfit:
    "Class for dutycycle fitting"
    from math import pi,cos,sin,atan,tan,acos,asin,sqrt
    from libacepy.swicsiondata import swicsiondata
    from libacepy.mag import magdata,sync_mag
    from libacepy.attitude import attdata,sync_attitude
    from libacepy.swepamdata import swepamdata,sync_h
    from libacepy.ancil import histogram,sig_histogram

    def __init__(self,swicspath,swepampath,magpath,effpath,ionname,timeframe):
        self.swicspath=swicspath
        self.swepampath=swepampath
        self.magpath=magpath
        self.effpath=effpath
        self.ionname=ionname
        self.timeframe=timeframe
        self.swepamres=720
        self.magres=240
        self.year=2007
        swepam=swepamdata(720,2007,timeframe[0][0],timeframe[len(timeframe)-1][1]+1.,swepampath)
        swepam.load()
        mag=magdata(240,2007,float(daylist[0]),float(daylist[len(daylist)-1]),magpath)
        mag.load()
        att=attdata(mag.year,mag.path)
        att.load()


    def calc_newasp(bx,bz,ax,az):
        "Calculates new aspect angle in respect to magnetic field direction beta based on bx,bz. This is used to calculate dutycycle only based on one magnetic field angle bx=beta (bz is set to zero)"
        b=acos(cos(bx)*cos(bz))
        a=acos(cos(bx-ax)*cos(bz-az))
        an0=acos((cos(bz)*sin(ax)*sin(az)-sin(bx)*sin(bz)*cos(az))/sqrt(cos(bz)**2+(sin(bx)*sin(bz))**2))
        if (an0<=pi/2.):
            anz=pi/2.-an0
        else:
            anz=an0-pi/2.
        i=0
        j=0
        if (cos(a)/cos(anz)>1.):
            while (cos(a)/cos(anz)-float(i)>1.):
                i+=1
        if (cos(a)/cos(anz)<-1):
            while (cos(a)/cos(anz)+float(j)<-1.):
                j+=1
        if (cos(anz)!=0.):
            anx=b-acos(cos(a)/cos(anz)-float(i)+float(j))
        else:
            anx=b
        return [anx,anz]

    
def mrqmin(x,y,sig,a,ia,covar,alpha,chisq,func,alamda):
    from numpy import array,zeros
    mfit=0
    ma=len(a)
    for j in range(ma):
        if (ia[j]):
            mfit+=1
    ndata=len(y)
    oneda=zeros([mfit,1])
    atry=zeros([ma])
    beta=zeros([ma])
    da=zeros([ma])
    ochisq=mrqcof(x,y,sig,a,ia,ma,alpha,beta,func)
    # initialisation
    if (alamda<0.):
        alamda=0.001
        for j in range(ma):
            atry[j]=a[j]
    
    for j in range(mfit):
        for k in range(mfit):
            covar[j][k]=alpha[j][k]
        covar[j][j]=alpha[j][j]*(1.+alamda)
        oneda[j][0]=beta[j]
    print "mrqmin : alpha ",alpha
    print "mrqmin : oneda ",oneda
    gaussj(covar,mfit,oneda,1)
    for j in range(mfit):
        da[j]=oneda[j][0]
    if (alamda==0.):
        covsrt(covar,ma,ia,mfit)
        covsrt(alpha,ma,ia,mfit)
        del oneda
        del da
        del beta
        del atry
        """
        print "mrqmin : covar ",covar
        print "mrqmin : alpha ",alpha
        print "mrqmin : para ",a
        print "mrqmin : chisq,alamda ",ochisq,alamda
        """
        return ochisq,alamda
    j=0
    for l in range(ma):
        if (ia[l]):
            atry[l]=a[l]+da[j]
            j+=1
        else:
            atry[l]=a[l]
    beta=zeros([ma])
    covar=zeros([ma,ma])
    chisq=mrqcof(x,y,sig,atry,ia,ma,covar,beta,func)
    print "mrqmin : ochisq,chisq",ochisq,chisq
    print "mrqmin : a ",a
    print "mrqmin : atry ",atry
    
    if (chisq<ochisq):
        alamda*=0.1
        ochisq=chisq
        for j in range(mfit):
            for k in range(mfit):
                alpha[j][k]=covar[j][k]
            beta[j]=da[j]
        for l in range(ma):
            a[l]=atry[l]
    else:
        alamda*=10.
        chisq=ochisq
    print "mrqmin : chisq,alamda ",chisq,alamda
    print "mrqmin : para ",a
    return chisq,alamda

def mrqcof(x,y,sig,a,ia,ma,alpha,beta,func):
    from numpy import array,zeros
    mfit=0
    dim=len(y[0])
    dyda=zeros([ma,dim])
    chisq=0.
    ndata=len(x)
    for j in range(ma):
        if (ia[j]):
            mfit+=1
    for j in range(mfit):
        for k in range(j):
            alpha[j][k]=0.
            beta[j]=0.
    for i in range(ndata):
        ymod=func(x[i],a,dyda)
        sig2i=[]
        for j in range(dim):
            if (sig[i][j]!=0.):
                sig2i.append(1./(sig[i][j]*sig[i][j]))
            else:
                sig2i.append(1.)
        dy=[]
        for j in range(dim):
            dy.append(y[i][j]-ymod[j])
        j=0
        for l in range(ma):
           if (ia[l]):
               wt=[]
               for n in range(dim):
                   wt.append(dyda[l][n]*sig2i[n])               
               k=0
               for m in range(l+1):
                   if (ia[m]):
                       for n in range(dim):
                           alpha[j][k]+=wt[n]*dyda[m][n]
                       k+=1
               for n in range(dim):
                   beta[j]+=dy[n]*wt[n]
               j+=1
        for n in range(dim):
            chisq+=dy[n]*dy[n]*sig2i[n]
    for j in range(1,mfit):
        for k in range(j):
            alpha[k][j]=alpha[j][k]
    del dyda
    print "mrqcof : chisq ",chisq
    return chisq


def maxlifit(x,y,sig,a,ia,covar,alpha,func):
    from numpy import zeros
    thisprogram="maxlifit : "
    dbglvl=1
    alamda = -1.
    itst = 0
    passed = 0
    max_test = 20
    max_pass = 10
    ma = len(a)
    mfit = 0;
    for j in range(ma):
        if (ia[j]):
            mfit+=1
    if (mfit==0):
        return true

    atry=zeros([ma])
    beta=zeros([ma])
    da=zeros([ma])
    oneda=zeros([mfit,0])

    chisq = 1.e20;
    ochisq = chisq

    while (itst < max_test and passed < max_pass):
        if (dbglvl >= 1):
            print thisprogram,"calling mrqmin  ",itst,"  ",passed
        chisq,alamda=mrqmin(x, y, sig,a,ia, covar, alpha, chisq, func, alamda)

        if (dbglvl >= 1):
            print thisprogram,"leaving mrqmin"
        print "ochisq,chisq = ",ochisq,chisq
        for i in range(len(a)):
            print "p[%i] = "%(i),a[i]
        if (chisq > ochisq):
            passed+=1
        else:
            passed = 0
            itst+=1
            ochisq = chisq
    alamda = 0.
    if (dbglvl >= 1):
        print thisprogram,"final call of mrqmin"
    chisq,alamda=mrqmin(x, y, sig,a,ia, covar, alpha, chisq, func, alamda)
    if (dbglvl >= 1):
        print thisprogram,"leaving mrqmin"
    print "maxlifit : final covar ",covar
    print "maxlifit : final alpha ",alpha
    return chisq

