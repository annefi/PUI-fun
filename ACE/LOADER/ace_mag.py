from ace_utils import calc_day00
from pylib import dbData
from numpy import *
#from pycwt import cwt_f,Morlet #auskommentier von A
from pylib.etTools import fftPlot
import os

class ace_mag(dbData):
    def load_data(self,*args,**kwargs):
        if kwargs.has_key("year"):
            if isinstance(kwargs["year"],list):
                self.year=kwargs["year"]
            elif isinstance(kwargs["year"],int) or isinstance(kwargs["year"],float):
                self.year=[kwargs["year"]]
        else:
            self.year=[2007]
        if kwargs.has_key("tf"):
            if isinstance(kwargs["tf"],list) or isinstance(kwargs["tf"],ndarray):
                self.timeframe=kwargs["tf"]
            elif kwargs["tf"]=="all":
                self.timeframe=[[1.,367]]
            else:
                print "periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded"
                self.timeframe==[]
        else:
            print "periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded"
            self.timeframe==[]
        if kwargs.has_key("fmt"):
            self.fmt=kwargs["fmt"]
        else:
            self.fmt="new"
        if kwargs.has_key("path"):
            self.path=kwargs["path"]
        else:
            if self.fmt=="new":
                self.path="/data/ivar/ace/mag/12mindata_meanfield/"
            else:
                self.path="/data/ivar/ace/mag/1sdata/"

        if self.fmt=="old":
            # fmt old means 1s data downloaded from the ACE science center is loaded. This data is in GSE coordinates, so the loader inverts Bx,By to convert to SunEarthEcliptic coordinates (x : Sun -> Earth,y : tangential to Earthorbit (with Earths rotation), z : North)
            time=[]
            years=[]
            B=[]
            Bx=[]
            By=[]
            Bz=[]

            for year in self.year:
                flist=os.listdir(self.path+str(year)+"/")
                for tf in self.timeframe:
                    for doy in arange(tf[0],tf[1]+0.1,1.):
                        #print doy
                        tmpname="%.3i"%(doy)
                        for f in flist:
                            if tmpname in f:
                                fin=open(self.path+str(year)+"/"+f,"r")
                                fin.readline() # skip header
                                fin.readline()
                                for l in fin:
                                    s=l.split()
                                    years.append(year)
                                    time.append(float(s[0]))
                                    B.append(float(s[1]))
                                    Bx.append(float(s[2]))
                                    By.append(float(s[3]))
                                    Bz.append(float(s[4]))                            
            self.data["year"]=array(years)
            self.data["time"]=array(time)
            self.data["B"]=array(B)
            self.data["Bx"]=-1.*array(Bx)
            self.data["Bx"][self.data["Bx"]>900.]=-999.
            self.data["By"]=-1.*array(By)
            self.data["Bz"]=array(Bz)
            self.calc_angles()
            self.data["d00"]=calc_day00(self.data["year"],self.data["time"])
        elif self.fmt=="new":
            self.data["year"]=[]
            self.data["time"]=[]
            self.data["d00"]=[]
            self.data["B"]=[]
            self.data["Bx"]=[]
            self.data["By"]=[]
            self.data["Bz"]=[]
            self.data["sB"]=[]
            self.data["sBx"]=[]
            self.data["sBy"]=[]
            self.data["sBz"]=[]
            self.data["phi"]=[]
            self.data["theta"]=[]
            self.data["alpha"]=[]
            self.data["sphi"]=[]
            self.data["stheta"]=[]
            self.data["salpha"]=[]
            self.data["sBxm"]=[]
            self.data["sBym"]=[]
            self.data["sBzm"]=[]
            for year in self.year:
                flist=os.listdir(self.path+str(year)+"/")
                for tf in self.timeframe:
                    for doy in arange(tf[0],tf[1]+0.1,1.):
                        #print doy
                        tmpname="%.3i"%(doy)
                        for f in flist:
                            if tmpname in f:
                                fin=open(self.path+str(year)+"/"+f,"r")
                                fin.readline() # skip header
                                for l in fin:
                                    k=l.split()
                                    self.data["year"].append(year)
                                    self.data["time"].append(float(k[0]))
                                    self.data["d00"].append(float(k[1]))
                                    self.data["B"].append(float(k[2]))
                                    self.data["Bx"].append(float(k[3]))
                                    self.data["By"].append(float(k[4]))
                                    self.data["Bz"].append(float(k[5]))
                                    self.data["sB"].append(float(k[6]))
                                    self.data["sBx"].append(float(k[7]))
                                    self.data["sBy"].append(float(k[8]))
                                    self.data["sBz"].append(float(k[9]))
                                    self.data["phi"].append(float(k[10]))
                                    self.data["theta"].append(float(k[11]))
                                    self.data["alpha"].append(float(k[12]))
                                    self.data["sphi"].append(float(k[13]))
                                    self.data["stheta"].append(float(k[14]))
                                    self.data["salpha"].append(float(k[15]))
                                    self.data["sBxm"].append(float(k[16]))
                                    self.data["sBym"].append(float(k[17]))
                                    self.data["sBzm"].append(float(k[18]))
            for key in self.data.keys():
                self.data[key]=array(self.data[key])
        else:
            print "load_data: unrecognized format!"
            print "fmt='new' -> 12min data (syncronized with ace swics data)!!!! Bx is already inverted!!!!"
            print "fmt='old' -> 1s data"
    def calc_angles(self):
        self.data["phi"]=arctan2(self.data["By"],self.data["Bx"])
        self.data["theta"]=arctan2(self.data["Bz"],sqrt(self.data["Bx"]**2+self.data["By"]**2))
        self.data["alpha"]=arccos(cos(self.data["theta"])*cos(self.data["phi"]))
        self.data["phi"]*=180./pi
        self.data["theta"]*=180./pi
        self.data["alpha"]*=180./pi
    def calc_sigma_angles(self):
        phi1=abs(arctan2(self.data["By"]+self.data["sBy"],self.data["Bx"]+self.data["sBx"])*180./pi-self.data["phi"])
        phi2=abs(arctan2(self.data["By"]-self.data["sBy"],self.data["Bx"]+self.data["sBx"])*180./pi-self.data["phi"])
        mask=phi1>180.
        phi1[mask]=phi2[mask]
        if self.data.has_key("sphi"):
            self.data["sphi"]=phi1
        else:
            self.add_data("sphi",phi1)
        if self.data.has_key("stheta"):
            self.data["stheta"]=arctan2(self.data["sBz"],sqrt(self.data["sBx"]**2+self.data["sBy"]**2))*180./pi
        else:
            self.add_data("stheta",arctan2(self.data["sBz"],sqrt(self.data["sBx"]**2+self.data["sBy"]**2))*180./pi)

    def transform_data(self,time,prodt="d00"):
        indT=searchsorted(time,self.get_data("Master",prodt))-1
        indT[indT>=time.shape[0]-1]=time.shape[0]-2
        self.set_mask("Master","Bx",-900.,op="gt",reset=True)
        self.set_mask("Master","By",-900.,op="gt",reset=True)
        self.set_mask("Master","Bz",-900.,op="gt",reset=True)
        self.set_mask("Master",prodt,time[0],time[-1])
        nrT,x=histogram(self.get_data("Master",prodt),time)
        meanBx,x=histogram(self.get_data("Master",prodt),time,weights=self.get_data("Master","Bx"))
        meanBy,x=histogram(self.get_data("Master",prodt),time,weights=self.get_data("Master","By"))
        meanBz,x=histogram(self.get_data("Master",prodt),time,weights=self.get_data("Master","Bz"))
        meanb=array([meanBx/nrT,meanBy/nrT,meanBz/nrT]).T
        ebx=array([meanb[:,0]/(sqrt(meanb[:,0]**2+meanb[:,1]**2+meanb[:,2]**2)),meanb[:,1]/(sqrt(meanb[:,0]**2+meanb[:,1]**2+meanb[:,2]**2)),meanb[:,2]/(sqrt(meanb[:,0]**2+meanb[:,1]**2+meanb[:,2]**2))]).T
        by=array([0.,0.,1.])
        eby=cross(ebx,by)
        eby=array([eby[:,0]/sqrt(sum(eby**2,axis=1)),eby[:,1]/sqrt(sum(eby**2,axis=1)),eby[:,2]/sqrt(sum(eby**2,axis=1))]).T
        ebz=cross(ebx,eby)
        ebz=array([ebz[:,0]/sqrt(sum(ebz**2,axis=1)),ebz[:,1]/sqrt(sum(ebz**2,axis=1)),ebz[:,2]/sqrt(sum(ebz**2,axis=1))]).T
        self.add_data("Bxm",sum(ebx[indT]*array([self.data["Bx"],self.data["By"],self.data["Bz"]]).T,axis=1))
        self.add_data("Bym",sum(eby[indT]*array([self.data["Bx"],self.data["By"],self.data["Bz"]]).T,axis=1))
        self.add_data("Bzm",sum(ebz[indT]*array([self.data["Bx"],self.data["By"],self.data["Bz"]]).T,axis=1))
        self.data["Bym"][self.data["Bx"]<-900.]=0
        self.data["Bzm"][self.data["Bx"]<-900.]=0
        nrT,x=histogram(self.get_data("Master",prodt),time)
        meannbx,x=histogram(self.get_data("Master",prodt),time,weights=self.get_data("Master","Bxm"))
        meannbx=meannbx/nrT
        meannbx[isnan(meannbx)]=0.
        self.remove_submask("Master","Bx")
        self.remove_submask("Master","By")
        self.remove_submask("Master","By")
        self.set_mask("Master","Bx",-900,op="<",reset=True)
        indT=searchsorted(time,self.get_data("Master",prodt))-1
        indT=indT[(indT>=0)*indT<time.shape[0]-1]
        self.data["Bxm"][self.get_mask("Master")]=meannbx[indT]
        self.reset_mask("Master")
        indT=searchsorted(time,self.get_data("Master",prodt))-1
        #indT=indT[(indT>=0)*indT<time.shape[0]-1]
        indT[indT>=time.shape[0]-1]=time.shape[0]-2
        self.add_data("dBxm",self.data["Bxm"]-meannbx[indT])
    def bin_data(self,time1,time2,year,prod1="d00",prod2="time"):
        """
        time1 and prod1 are used for the binning. !!! time1 should have added one point in the end to give a serious bin for the last 'real' timestep
        time2 and prod2 are alternative timestamps (DoY vs. d00)
        """
        self.set_mask("Master","Bx",-900.,op="gt")
        self.set_mask("Master","By",-900.,op="gt")
        self.set_mask("Master","Bz",-900.,op="gt")
        self.set_mask("Master",prod1,time1[0],time1[-1])
        B = self.get_data("Master","B")
        Bx = self.get_data("Master","Bx")
        By = self.get_data("Master","By")
        Bz = self.get_data("Master","Bz")
        dBxm = self.get_data("Master","dBxm")
        Bym = self.get_data("Master","Bym")
        Bzm = self.get_data("Master","Bzm")
        alpha = self.get_data("Master","alpha")
        times = self.get_data("Master",prod1)
        nrT,x = histogram(times,time1)
        nrT[nrT==0.]=1.
        mBx,x = histogram(times,time1,weights=Bx)
        mBy,x = histogram(times,time1,weights=By)
        mBz,x = histogram(times,time1,weights=Bz)
        mBx = mBx/nrT
        mBy = mBy/nrT
        mBz = mBz/nrT
        mB = sqrt(mBx**2+mBy**2+mBz**2)
        sB,x=histogram(times,time1,weights=B**2)
        sBx,x=histogram(times,time1,weights=Bx**2)
        sBy,x=histogram(times,time1,weights=By**2)
        sBz,x=histogram(times,time1,weights=Bz**2)
        sB = sqrt(sB/nrT-mB**2)
        sBx = sqrt(sBx/nrT-mBx**2)
        sBy = sqrt(sBy/nrT-mBy**2)
        sBz = sqrt(sBz/nrT-mBz**2)
        malpha,x = histogram(times,time1,weights=alpha)
        malpha = malpha/nrT
        salpha,x = histogram(times,time1,weights=alpha**2)
        salpha = sqrt(salpha/nrT-malpha**2)
        sBxm,x=histogram(times,time1,weights=dBxm**2)
        sBym,x=histogram(times,time1,weights=Bym**2)
        sBzm,x=histogram(times,time1,weights=Bzm**2)
        sBxm = sqrt(sBxm/nrT)
        sBym = sqrt(sBym/nrT)
        sBzm = sqrt(sBzm/nrT)
        self.data[prod1]=time1[:-1]
        self.data[prod2]=time2
        self.data["B"]=mB
        self.data["Bx"]=mBx
        self.data["By"]=mBy
        self.data["Bz"]=mBz
        self.calc_angles()
        if self.data.has_key("sB"):
            self.data["sB"]=sB
        else:
            self.add_data("sB",sB)
        if self.data.has_key("sBx"):
            self.data["sBx"]=sBx
        else:
            self.add_data("sBx",sBx)
        if self.data.has_key("sBy"):
            self.data["sBy"]=sBy
        else:
            self.add_data("sBy",sBy)
        if self.data.has_key("sBz"):
            self.data["sBz"]=sBz
        else:
            self.add_data("sBz",sBz)
        if self.data.has_key("salpha"):
            self.data["salpha"]=salpha
        else:
            self.add_data("salpha",salpha)
        if self.data.has_key("sBxm"):
            self.data["sBxm"]=sBxm
        else:
            self.add_data("sBxm",sBxm)
        if self.data.has_key("sBym"):
            self.data["sBym"]=sBym
        else:
            self.add_data("sBym",sBym)
        if self.data.has_key("sBzm"):
            self.data["sBzm"]=sBzm
        else:
            self.add_data("sBzm",sBzm)
        self.calc_sigma_angles()
        self.data["year"]=year
        self.reset_mask("all")

    def save_bin(self,path="/data/ivar/ace/mag/12mindata_meanfield/"):
        for year in self.year:
            self.reset_mask("Master")
            self.set_mask("Master","year",year,op="eq",reset=True)
            doys=self.get_data("Master","time")
            if doys.shape[0]>0:
                for day in range(int(amin(doys)),int(amax(doys))+1):
                    self.set_mask("Master","time",day,day+0.999999,reset=True)
                    fout=open(path+str(year)+"/%.3i"%(day),"w")
                    fout.write("DoY\t\td00\t\tB\tBx\tBy\tBz\tsB\tsBx\tsBy\tsBz\tphi\ttheta\talpha\tsphi\tstheta\tsalpha\tsBxm\tsBym\tsBzm\n")
                    nrvals=self.get_data("Master","time").shape[0]
                    dat=zeros((nrvals,19))
                    dat[:,0]=self.get_data("Master","time")
                    dat[:,1]=self.get_data("Master","d00")
                    dat[:,2]=self.get_data("Master","B")
                    dat[:,3]=self.get_data("Master","Bx")
                    dat[:,4]=self.get_data("Master","By")
                    dat[:,5]=self.get_data("Master","Bz")
                    dat[:,6]=self.get_data("Master","sB")
                    dat[:,7]=self.get_data("Master","sBx")
                    dat[:,8]=self.get_data("Master","sBy")
                    dat[:,9]=self.get_data("Master","sBz")
                    dat[:,10]=self.get_data("Master","phi")
                    dat[:,11]=self.get_data("Master","theta")
                    dat[:,12]=self.get_data("Master","alpha")
                    dat[:,13]=self.get_data("Master","sphi")
                    dat[:,14]=self.get_data("Master","stheta")
                    dat[:,15]=self.get_data("Master","salpha")
                    dat[:,16]=self.get_data("Master","sBxm")
                    dat[:,17]=self.get_data("Master","sBym")
                    dat[:,18]=self.get_data("Master","sBzm")
                    savetxt(fout,dat,fmt=["%.8f","%.8f","%.3f","%.3f","%.3f","%.3f","%.3f","%.3f","%.3f","%.3f","%.2f","%.2f","%.2f","%.2f","%.2f","%.2f","%.3f","%.3f","%.3f"],delimiter="\t")
        self.reset_mask("all")


    def plot_wavelet(self,nrfreq=120,freq0=0.5,tf=[[1.,1.+1./24./5.]],morletwidth=1.,freqarr=None):
        for t in tf:
            self.set_mask("Master","time",t[0],t[1],reset=True)
            freqs=zeros([nrfreq])
            freqs[0]=freq0
            for i in range(1,nrfreq):
                freqs[i]=freqs[i-1]/1.05
            if freqarr!=None:
                freqs=freqarr
                nrfreq=freqs.shape[0]
            resx=cwt_f(self.get_data("Master","dBxm"),freqs,wavelet=Morlet(f0=morletwidth))
            resy=cwt_f(self.get_data("Master","Bym"),freqs,wavelet=Morlet(f0=morletwidth))
            resz=cwt_f(self.get_data("Master","Bzm"),freqs,wavelet=Morlet(f0=morletwidth))
            tdim=self.get_data("Master","dBxm").shape[0]
            polxy=zeros([nrfreq,tdim])
            polxz=zeros([nrfreq,tdim])
            polyz=zeros([nrfreq,tdim])
            for i in range(tdim):
                polxy[:,i]=(arctan2(resx[:,i].imag,resx[:,i].real)-arctan2(resy[:,i].imag,resy[:,i].real))
                polxz[:,i]=(arctan2(resx[:,i].imag,resx[:,i].real)-arctan2(resz[:,i].imag,resz[:,i].real))
                polyz[:,i]=(arctan2(resy[:,i].imag,resy[:,i].real)-arctan2(resz[:,i].imag,resz[:,i].real))
            polxy[polxy>pi]=(2*pi-polxy[polxy>pi])
            polxy[polxy<-pi]=(-2*pi-polxy[polxy<-pi])
            polxy[(polxy<=pi)*(polxy>=-pi)]/=pi
            polxz[polxz>pi]=(2*pi-polxz[polxz>pi])
            polxz[polxz<-pi]=(-2*pi-polxz[polxz<-pi])
            polxz[(polxz<=pi)*(polxz>=-pi)]/=pi
            polyz[polyz>pi]=(2*pi-polyz[polyz>pi])
            polyz[polyz<-pi]=(-2*pi-polyz[polyz<-pi])
            polyz[(polyz<=pi)*(polyz>=-pi)]/=pi
            psdx=fftPlot(self.get_data("Master","dBxm"))
            psdy=fftPlot(self.get_data("Master","Bym"))
            psdz=fftPlot(self.get_data("Master","Bzm"))
            time=self.get_data("Master","time")
        self.reset_mask("Master")
        return array(psdx),array(psdy),array(psdz),abs(resx),abs(resy),abs(resz),polxy,polxz,polyz,time,freqs
