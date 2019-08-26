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
    ochisq=mrqcof(x,y,sig,ndata,a,ia,ma,alpha,beta,func)
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
    chisq=mrqcof(x,y,sig,ndata,atry,ia,ma,covar,beta,func)
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

def mrqcof(x,y,sig,ndata,a,ia,ma,alpha,beta,func):
    from numpy import array,zeros
    mfit=0
    dyda=zeros([ma])
    chisq=0.
    for j in range(ma):
        if (ia[j]):
            mfit+=1
    for j in range(mfit):
        for k in range(j):
            alpha[j][k]=0.
            beta[j]=0.
    for i in range(ndata):
        ymod=func(x[i],a,dyda)
        if (sig[i]!=0.):
            sig2i=1./(sig[i]*sig[i])
        else:
            sig2i=1.
        dy=y[i]-ymod
        j=0
        for l in range(ma):
           if (ia[l]):
               wt=dyda[l]*sig2i               
               k=0
               for m in range(l+1):
                   if (ia[m]):
                       alpha[j][k]+=wt*dyda[m]
                       k+=1
               beta[j]+=dy*wt
               j+=1
        chisq+=dy*dy*sig2i
    for j in range(1,mfit):
        for k in range(j):
            alpha[k][j]=alpha[j][k]
    del dyda
    print "mrqcof : chisq ",chisq
    return chisq


def maxlifit(x,y,sig,a,ia,covar,alpha,merit,func):
    from numpy import zeros
    thisprogram="maxlifit : "
    dbglvl=1
    alamda = -1.
    omerit = 1.e20 
    itst = 0
    passed = 0
    max_test = 500
    max_pass = 5
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
    ochisq=chisq
    deltachisq=1.
    
    while (itst < max_test and passed < max_pass and deltachisq>0.01):
        if (dbglvl >= 1):
            print thisprogram,"calling mrqmin  ",itst,"  ",passed
        chisq,alamda=mrqmin(x, y, sig,a,ia, covar, alpha, chisq, func, alamda)

        if (dbglvl >= 1):
            print thisprogram,"leaving mrqmin"
        if (chisq > ochisq):
            passed+=1
        else:
            passed = 0
            itst+=1
            deltachisq=(ochisq-chisq)/ochisq
            ochisq = chisq

    alamda = 0.
    if (dbglvl >= 1):
        print thisprogram,"final call of mrqmin"
    chisq,alamda=mrqmin(x, y, sig,a,ia, covar, alpha, merit, func, alamda)
    if (dbglvl >= 1):
        print thisprogram,"leaving mrqmin"
    print "maxlifit : final covar ",covar
    print "maxlifit : final alpha ",alpha
    return chisq

