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
    for j in range(ma-1,-1,-1):
        if (ia[j]):
            for i in range(ma):
                SWAPC(covar,i,k,j)
            for i in range(ma):
                SWAPR(covar,k,j,i)
            k-=1

class dutyfit:
    "Class for dutycycle fitting"

    def __init__(self,swicspath,swepampath,swicsprotonpath,magpath,effpath,ionname,timeframe,para):
        self.swicspath=swicspath
        self.swepampath=swepampath
        self.swicsprotonpath=swicsprotonpath
        self.magpath=magpath
        self.effpath=effpath
        self.ionname=ionname
        self.timeframe=timeframe
        self.swepamres=720
        self.magres=240
        self.year=2007
        self.nrhist=8
        self.histstep=1.6/float(self.nrhist)
        self.para=para
        self.swepamorswics=0  # use swepam (0) or swics (1) proton data

    def load(self):
        self.load_swepam()
        self.load_swicsprotons()
        self.load_mag()
        self.load_att()
        self.load_swics()
        self.sync_data()

    def load_swicsprotons(self):
        from libacepy.swicsprotondata import swicsprotondata
        self.swicsprotons=swicsprotondata("H1+",self.timeframe,self.swicsprotonpath)
        self.swicsprotons.load()
        
    def load_swics(self):
        from libacepy.swicsiondata import swicsiondata
        self.iondata=swicsiondata(self.ionname,self.timeframe,self.swicspath)
        self.iondata.load()
        
    def load_swepam(self):
        from libacepy.swepamdata import swepamdata
        self.swepam=swepamdata(self.swepamres,self.year,self.timeframe[0][0],self.timeframe[len(self.timeframe)-1][1]+1.,self.swepampath)
        self.swepam.load()

    def load_mag(self):
        from libacepy.mag import magdata
        self.mag=magdata(self.magres,self.year,self.timeframe[0][0],self.timeframe[len(self.timeframe)-1][1]+1.,self.magpath)
        self.mag.load()

    def load_att(self):
        from libacepy.attitude import attdata
        self.att=attdata(self.year,self.magpath)
        self.att.load()
        
    def sync_data(self):
        from libacepy.swepamdata import sync_h
        from libacepy.mag import sync_mag
        from libacepy.attitude import sync_attitude
        self.syncmag=sync_mag(self.mag,self.iondata)
        self.syncswepam=sync_h(self.swepam,self.iondata)
        self.syncatt=sync_attitude(self.att,self.iondata)

    def calc_newasp(self,bx,bz,ax,az):
        "Calculates new aspect angle in respect to magnetic field direction beta based on bx,bz. This is used to calculate dutycycle only based on one magnetic field angle bx=beta (bz is set to zero)"
        from math import pi,cos,sin,atan,tan,acos,asin,sqrt
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

    def hist_data(self):
        from math import acos,cos,sqrt,pi
        from libacepy.ancil import histogram,sig_histogram
        from Gnuplot import Data
        from numpy import array
        from scipy import zeros
        self.sumspec=zeros([15,2],float)
        self.sumspecprotons=zeros([15,2],float)
        for i in range(15):
            self.sumspec[i][0]=-0.9+i*0.2
            self.sumspecprotons[i][0]=-0.9+i*0.2
        dvarr=[]
        swicsdvarr=[]
        swicsvarr=[]
        vtharr=[]
        valfarr=[]
        barr=[]
        axarr=[]
        azarr=[]
        varr=[]
        for i in range(len(self.iondata.time)):
            # calculate mag angle
            if (self.syncmag.phi[i][1]>=0. and self.syncmag.theta[i][1]!=0.):
                tmpmag=acos(abs(cos(self.syncmag.phi[i][1])*cos(self.syncmag.theta[i][1])))
            else:
                tmpmag=0.
            # calculate alfvenspeed
            if (self.syncswepam.dens[i][1]>0.):
                valf=21.8*self.syncmag.magb[i][1]/sqrt(self.syncswepam.dens[i][1])
            else:
                valf=0.
            if (self.iondata.vel[i]>100. and self.iondata.vel[i]<1000. and self.syncswepam.vel[i][1]>600. and valf>0. and tmpmag>0. and tmpmag<1.6 and self.syncmag.phi[i][1]*self.syncmag.dpp[i][1]<pi/180.*11.5 and self.syncmag.theta[i][1]*self.syncmag.dtt[i][1]<pi/180.*11.5 and self.iondata.crvth[i]>10.):
                tmpasp=self.calc_newasp(self.syncmag.phi[i][1],self.syncmag.theta[i][1],self.syncatt.phi[i],self.syncatt.theta[i])
                dvarr.append([tmpmag,(self.iondata.crvel[i]-self.syncswepam.vel[i][1])/valf])
                vtharr.append([tmpmag,self.iondata.crvth[i]])
                valfarr.append([tmpmag,valf])
                barr.append([tmpmag,tmpmag])
                axarr.append([tmpmag,tmpasp[0]])
                azarr.append([tmpmag,tmpasp[1]])
                varr.append([tmpmag,self.syncswepam.vel[i][1]])
                swicsdvarr.append([tmpmag,(self.iondata.crvel[i]-self.swicsprotons.crvel[i])/valf])
                swicsvarr.append([tmpmag,self.swicsprotons.crvel[i]])
            if (self.iondata.vel[i]>100. and self.iondata.vel[i]<1000. and self.syncswepam.vel[i][1]>600. and valf>0. and tmpmag>0. and tmpmag<0.2 and self.syncmag.phi[i][1]*self.syncmag.dpp[i][1]<pi/180.*11.5 and self.syncmag.theta[i][1]*self.syncmag.dtt[i][1]<pi/180.*11.5 and self.iondata.crvth[i]>10.):
                for j in range(len(self.iondata.countspec[i])):
                    vtemp=(self.iondata.countspec[i][j][0]-self.syncswepam.vel[i][1])/valf
                    #vtemp=(self.iondata.countspec[i][j][0]-self.iondata.vel[i])/valf
                    vtempprotons=(self.swicsprotons.countspec[i][j][0]-self.syncswepam.vel[i][1])/valf
                    if (j==0):
                        deltav=2*(self.iondata.countspec[i][j][0]-self.iondata.countspec[i][j+1][0])/valf
                        deltavp=2*(self.swicsprotons.countspec[i][j][0]-self.swicsprotons.countspec[i][j+1][0])/valf
                    elif (j==len(self.iondata.countspec[i])-1):
                        deltav=2*(self.iondata.countspec[i][j-1][0]-self.iondata.countspec[i][j][0])/valf
                        deltavp=2*(self.swicsprotons.countspec[i][j-1][0]-self.swicsprotons.countspec[i][j][0])/valf
                    else:
                        deltav=(self.iondata.countspec[i][j-1][0]-self.iondata.countspec[i][j+1][0])/valf
                        deltavp=(self.swicsprotons.countspec[i][j-1][0]-self.swicsprotons.countspec[i][j+1][0])/valf
                    rrange=vtemp+deltav/2.
                    lrange=vtemp-deltav/2.
                    rrangep=vtempprotons+deltavp/2.
                    lrangep=vtempprotons-deltavp/2.
                    if (lrange<self.sumspec[14][0] and rrange>self.sumspec[0][0]):
                        for k in range(15):
                            if (rrange<=self.sumspec[k][0]+0.1 and lrange>=self.sumspec[k][0]-0.1):
                                self.sumspec[k][1]+=self.iondata.countspec[i][j][1]
                            elif (rrange>=self.sumspec[k][0]+0.1 and lrange<=self.sumspec[k][0]+0.1):
                                fac=(self.sumspec[k][0]+0.1-lrange)/(rrange-lrange)
                                self.sumspec[k][1]+=self.iondata.countspec[i][j][1]*fac
                            elif (rrange>=self.sumspec[k][0]-0.1 and lrange<=self.sumspec[k][0]-0.1):
                                fac=(rrange-(self.sumspec[k][0]-0.1))/(rrange-lrange)
                                self.sumspec[k][1]+=self.iondata.countspec[i][j][1]*fac
                    if (lrangep<self.sumspec[14][0] and rrangep>self.sumspec[0][0]):
                        for k in range(15):
                            if (rrangep<=self.sumspec[k][0]+0.1 and lrangep>=self.sumspec[k][0]-0.1):
                                self.sumspecprotons[k][1]+=self.swicsprotons.countspec[i][j][1]
                            elif (rrangep>=self.sumspec[k][0]+0.1 and lrangep<=self.sumspec[k][0]+0.1):
                                fac=(self.sumspec[k][0]+0.1-lrangep)/(rrangep-lrangep)
                                self.sumspecprotons[k][1]+=self.swicsprotons.countspec[i][j][1]*fac
                            elif (rrangep>=self.sumspec[k][0]-0.1 and lrangep<=self.sumspec[k][0]-0.1):
                                fac=(rrangep-(self.sumspec[k][0]-0.1))/(rrangep-lrangep)
                                self.sumspecprotons[k][1]+=self.swicsprotons.countspec[i][j][1]*fac

        nrsumspec=0
        for val in self.sumspec:
            nrsumspec+=val[1]
        for val in self.sumspec:
            val[1]=val[1]/nrsumspec
        nrsumspecprotons=0
        for val in self.sumspecprotons:
            nrsumspecprotons+=val[1]
        for val in self.sumspecprotons:
            val[1]=val[1]/nrsumspecprotons
        valfhist=histogram(valfarr,0.,self.histstep,self.nrhist,3)
        bhist=histogram(barr,0.,self.histstep,self.nrhist,3)
        axhist=histogram(axarr,0.,self.histstep,self.nrhist,3)
        azhist=histogram(azarr,0.,self.histstep,self.nrhist,3)
        if (self.swepamorswics==0):
            vhist=histogram(varr,0.,self.histstep,self.nrhist,3)
            dvhist=histogram(dvarr,0.,self.histstep,self.nrhist,4)
        else:
            vhist=histogram(swicsvarr,0.,self.histstep,self.nrhist,3)
            dvhist=histogram(swicsdvarr,0.,self.histstep,self.nrhist,4)
        sigdvhist=sig_histogram(dvarr,dvhist,4)
        vthhist=histogram(vtharr,0.,self.histstep,self.nrhist,4)
        sigvthhist=sig_histogram(vtharr,vthhist,4)

        self.dverr=[]
        for i in range(len(dvhist)):
            if (sigdvhist[i][2]>0.):
                self.dverr.append([dvhist[i][0],dvhist[i][1],sigdvhist[i][1]/sqrt(sigdvhist[i][2])])
            else:
                self.dverr.append([dvhist[i][0],dvhist[i][1],0.])
        self.vtherr=[]
        for i in range(len(dvhist)):
            if (sigvthhist[i][2]>0.):
                self.vtherr.append([vthhist[i][0],vthhist[i][1],sigvthhist[i][1]/sqrt(sigvthhist[i][2])])
            else:
                self.vtherr.append([vthhist[i][0],vthhist[i][1],0.])

        self.pdvhist=(Data(self.dverr))
        self.pdvhist.set_option_colonsep("title","'Observations'")
        #self.pdvhist.set_option_colonsep("title","'Beobachtung'")
        self.pdvhist.set_option_colonsep("with","yerrorbars lt 1 lw 3")
        self.pdvhist.set_option_colonsep("using","1:2:3")
        self.pvthhist=(Data(self.vtherr))
        self.pvthhist.set_option_colonsep("title","'Observations'")
        #self.pvthhist.set_option_colonsep("title","'Beobachtung'")
        self.pvthhist.set_option_colonsep("with","yerrorbars lt 1 lw 3")
        self.pvthhist.set_option_colonsep("using","1:2:3")

        # build array of x values for fitting 

        xvals=[]
        for i in range(len(vhist)):
            xvals.append([vhist[i][1],valfhist[i][1],bhist[i][1],0.,axhist[i][1],azhist[i][1],0.1,self.iondata.countspec[0],self.iondata.name,self.iondata.mass,self.iondata.charge,self.effpath])
        self.xvals=xvals
        
        # build array of y and sig values for fitting

        yvals=[]
        sigvals=[]
        for i in range(len(vhist)):
            yvals.append([self.dverr[i][1],self.vtherr[i][1]])
            sigvals.append([self.dverr[i][2],self.vtherr[i][2]])
        self.yvals=array(yvals)
        self.sigvals=array(sigvals)



    def mrqmin(self):
        from numpy import array,zeros

        # initialisation
        if (self.alamda<0.):
            self.alamda=0.001
            for i in range(len(self.para)):
                self.paratry[i]=self.para[i]
            self.mrqcof(1,1)
            for i in range(self.ma):
                for j in range(self.ma):
                    self.alpha[i][j]=self.covar[i][j]
                self.beta[i]=self.da[i]
            print "Initial values : "
            print "chisq = ",self.chisq
            self.ochisq=self.chisq
            for i in range(len(self.para)):
                print "para[%i] = "%(i),self.para[i]
            return
        
        for j in range(self.mfit):
            for k in range(self.mfit):
                self.covar[j][k]=self.alpha[j][k]
            self.covar[j][j]=self.alpha[j][j]*(1.+self.alamda)
            self.oneda[j][0]=self.beta[j]
        gaussj(self.covar,self.mfit,self.oneda,1)

        for j in range(self.mfit):
            self.da[j]=self.oneda[j][0]

        if (self.alamda==0.):
            covsrt(self.covar,self.ma,self.ia,self.mfit)
            covsrt(self.alpha,self.ma,self.ia,self.mfit)
            return 

        j=0
        for l in range(self.ma):
            if (self.ia[l]):
                self.paratry[l]=self.para[l]+self.da[j]
                # if parameters out of boundaries set them to min,max values !!!
                if ((l==1) and self.paratry[l]<0.0):
                    self.paratry[l]=0.0
                if ((l==1) and self.paratry[l]>4.0):
                    self.paratry[l]=2.
                #if ((l==0 or l==1) and self.paratry[l]>2.0):
                #    self.paratry[l]=2.
                if ((l==2 or l==3) and self.paratry[l]<7.):
                    self.paratry[l]=7.
                if ((l==2 or l==3) and self.paratry[l]>60.):
                    self.paratry[l]=60.
                    
                j+=1
            else:
                self.paratry[l]=self.para[l]
        self.mrqcof(0,1)
        print "ochisq,chisq = ",self.ochisq,self.chisq
        for i in range(len(self.para)):
            print "para[%i],paratry[%i] = "%(i,i),self.para[i],self.paratry[i]
        if (self.chisq<self.ochisq):
            self.mrqcof(1,0)
            self.alamda*=0.1
            self.ochisq=self.chisq
            for j in range(self.mfit):
                for k in range(self.mfit):
                    self.alpha[j][k]=self.covar[j][k]
                self.beta[j]=self.da[j]
            for l in range(self.ma):
                self.para[l]=self.paratry[l]
        else:
            self.alamda*=10.
            self.chisq=self.ochisq
        return 

    def mrqcof(self,deriv,plot):
        from numpy import array,zeros
        from Gnuplot import Data
        dim=len(self.yvals[0])
        dyda=zeros([self.ma,dim])
        tmpdv=[]
        tmpvth=[]
        self.chisq=0.
        for j in range(self.ma):
            for k in range(self.ma):
                self.covar[j][k]=0.
            self.da[j]=0.
        for i in range(self.ndata):
            ymod=self.func(self.xvals[i],self.paratry,dyda,deriv,self.ia)
            if (plot==1):
                tmpdv.append([i*0.2,ymod[0]])
                tmpvth.append([i*0.2,ymod[1]])
            sig2i=[]
            for j in range(dim):
                if (self.sigvals[i][j]!=0.):
                    sig2i.append(1./(self.sigvals[i][j]**2))
                else:
                    sig2i.append(1.)
            dy=[]
            for j in range(dim):
                dy.append(self.yvals[i][j]-ymod[j])

            if (deriv==1):
                j=0
                for l in range(self.ma):
                    if (self.ia[l]):
                        wt=[]
                        for n in range(dim):
                            wt.append(dyda[l][n]*sig2i[n])               
                        k=0
                        for m in range(l+1):
                            if (self.ia[m]):
                                for n in range(dim):
                                    self.covar[j][k]+=wt[n]*dyda[m][n]
                                k+=1
                        for n in range(dim):
                            self.da[j]+=dy[n]*wt[n]
                        j+=1
            for n in range(dim):
                self.chisq+=dy[n]*dy[n]*sig2i[n]
        for j in range(1,self.mfit):
            for k in range(j):
                self.covar[k][j]=self.covar[j][k]
        if (plot==1):
            tmpdv.append([1.6,0.0])
            tmpdvplot=Data(tmpdv)
#            tmpdvplot.set_option_colonsep("title","'chisq=%.2f,bp=%.2f,pb=%.2f,vpara=%.2f,vperp=%.2f'"%(self.chisq,self.paratry[0],self.paratry[1],self.paratry[2],self.paratry[3]))
            tmpdvplot.set_option_colonsep("title","'Model'")
            tmpdvplot.set_option_colonsep("with","steps lt 3 lw 3")
            tmpvth.append([1.6,0.0])
            tmpvthplot=Data(tmpvth)
            tmpvthplot.set_option_colonsep("title","'Model'")
            tmpvthplot.set_option_colonsep("with","steps lt 3 lw 3")
            self.pthdv.append(tmpdvplot)
            self.pthvth.append(tmpvthplot)
        del dyda
        return 


    def fit(self,ia):
        from numpy import zeros
        from libacepy.dutyfunc import dutyfunc 
        self.load()
        self.hist_data()
        thisprogram="fit : "
        dbglvl=1
        itst = 0
        passed = 0
        max_test = 1
        max_pass = 1
        self.pthdv=[]
        self.pthvth=[]
        self.ndata=len(self.yvals)
        self.func=dutyfunc
        self.alamda = -1.
        self.ma = len(self.para)
        self.ia=ia
        self.mfit = 0;
        for j in range(self.ma):
            if (self.ia[j]):
                self.mfit+=1
        self.paratry=zeros([self.ma])
        self.beta=zeros([self.ma])
        self.da=zeros([self.ma])
        self.oneda=zeros([self.mfit,1])
        self.alpha=zeros([self.ma,self.ma])
        self.covar=zeros([self.ma,self.ma])
        if (self.mfit==0):
            print "No parameter to fit!"
            return true

        self.chisq = 1.e20;
        self.ochisq = self.chisq

        while (itst < max_test and passed < max_pass):
            if (dbglvl >= 1):
                print thisprogram,"calling mrqmin  ",itst,"  ",passed
            self.mrqmin()

            if (dbglvl >= 1):
                print thisprogram,"leaving mrqmin"
            if (self.chisq > self.ochisq):
                passed+=1
            else:
                passed = 0
                itst+=1
                self.ochisq = self.chisq
        self.alamda = 0.
        if (dbglvl >= 1):
            print thisprogram,"final call of mrqmin"
        self.mrqmin()
        if (dbglvl >= 1):
            print thisprogram,"leaving mrqmin"
        print "fit : final covar ",self.covar
        print "fit : final alpha ",self.alpha

