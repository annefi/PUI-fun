from Gnuplot import Gnuplot,Data
from math import atan,pi,acos,cos,asin
from numpy import *
from pylib import dbData

class dbmag(dbData): 
    def load_data(self,*args,**kwargs):
        if not(("year" in kwargs.keys()) and ("tf" in kwargs.keys())) and not("data" in kwargs.keys()):
            print "need year and tf or data"
            return
        if ("data" in kwargs.keys()):
            print "generate dbmag with direct data input"
            dat=kwargs["data"]
            self.data["B"]=dat[0]
            self.data["Bx"]=dat[1]
            self.data["By"]=dat[2]
            self.data["Bz"]=dat[3]
            self.data["phi"]=dat[4]
            self.data["theta"]=dat[5]
            self.data["time"]=dat[6]
            self.data["alpha"]=dat[7]
            self.data["dB"]=dat[8]
            self.data["dBx"]=dat[9]
            self.data["dBy"]=dat[10]
            self.data["dBz"]=dat[11]
            self.data["dphi"]=dat[12]
            self.data["dtheta"]=dat[13]
            self.data["dalpha"]=dat[14]
            return

        if not("path" in kwargs.keys()):
            path="/data/etph/ace/mag/"
        else:
            path=kwargs["path"]
        time=array([])
        B=array([])
        Bx=array([])
        By=array([])
        Bz=array([])

        print "Reading Mag data from : ",path," ; Year : ",kwargs["year"]," ; Resolution 1s ; timeframe : ",kwargs["tf"]
        for tf in kwargs["tf"]:
            for DoY in range(int(tf[0]),int(tf[1])+1):
                inname=path+"1sdata/"+str(kwargs["year"])+"/%.3i"%(DoY)
                data = loadtxt(inname,skiprows=2)
                # data is fit into timeframe
                if data.shape[0]>0.:
                    timemask=(data[:,0]>=tf[0])*(data[:,0]<=tf[1])
                    data=data[timemask]

                    # append data
                    time=append(time,data[:,0])
                    B=append(B,data[:,1])
                    Bx=append(Bx,data[:,2]*(-1.))
                    By=append(By,data[:,3])
                    Bz=append(Bz,data[:,4])
        print "MAG-data loaded"
        # cut away bad values (indicated by -999.)
        mask=(B>0.)
        time=time[mask]
        B=B[mask]
        Bx=Bx[mask]
        By=By[mask]
        Bz=Bz[mask]
        phi=arctan2(By,Bx)
        theta=arctan2(Bz,sqrt(Bx**2+By**2))
        alpha=arccos(cos(phi)*cos(theta))
        # if tbins is not given -> no binning is applied, if tbins is given data is binned and standard deviations are calculated
        if not("tbins" in kwargs.keys()):
            self.data["B"]=B
            self.data["Bx"]=Bx
            self.data["By"]=By
            self.data["Bz"]=Bz
            self.data["phi"]=phi
            self.data["theta"]=theta
            self.data["time"]=time
            self.data["alpha"]=alpha
        else:
            tbins=kwargs["tbins"]
            mask=(phi!=0.)*(theta!=0.)*(time>=tbins[0])*(time<tbins[-1])
            time=time[mask]
            B=B[mask]
            Bx=Bx[mask]
            By=By[mask]
            Bz=Bz[mask]
            phi=phi[mask]
            theta=theta[mask]
            btime,x=histogram(time,tbins)
            bBx,x=histogram(time,tbins,weights=Bx)
            bBy,x=histogram(time,tbins,weights=By)
            bBz,x=histogram(time,tbins,weights=Bz)
            bBx/=btime
            bBy/=btime
            bBz/=btime
            bB=sqrt(bBx**2+bBy**2+bBz**2)
            bphi=arctan2(bBy,bBx)
            btheta=arctan2(bBz,sqrt(bBx**2+bBy**2))
            balpha=arccos(cos(bphi)*cos(btheta))
            ind=searchsorted(tbins,time)-1
            dB=(B-bB[ind])**2
            dBx=(Bx-bBx[ind])**2
            dBy=(By-bBy[ind])**2
            dBz=(Bz-bBz[ind])**2
            dphi=(phi-bphi[ind])**2
            dtheta=(theta-btheta[ind])**2
            dalpha=(alpha[mask]-balpha[ind])**2
            dB,x=histogram(time,tbins,weights=dB)
            dB=sqrt(dB/btime)
            dBx,x=histogram(time,tbins,weights=dBx)
            dBx=sqrt(dBx/btime)
            dBy,x=histogram(time,tbins,weights=dBy)
            dBy=sqrt(dBy/btime)
            dBz,x=histogram(time,tbins,weights=dBz)
            dBz=sqrt(dBz/btime)
            dphi,x=histogram(time,tbins,weights=dphi)
            dphi=sqrt(dphi/btime)
            dtheta,x=histogram(time,tbins,weights=dtheta)
            dtheta=sqrt(dtheta/btime)
            dalpha,x=histogram(time,tbins,weights=dalpha)
            dalpha=sqrt(dalpha/btime)
            
            self.data["B"]=bB
            self.data["Bx"]=bBx
            self.data["By"]=bBy
            self.data["Bz"]=bBz
            self.data["phi"]=bphi
            self.data["theta"]=btheta
            self.data["time"]=tbins[:-1]
            self.data["alpha"]=balpha
            self.data["dB"]=dB
            self.data["dBx"]=dBx
            self.data["dBy"]=dBy
            self.data["dBz"]=dBz
            self.data["dphi"]=dphi
            self.data["dtheta"]=dtheta
            self.data["dalpha"]=dalpha


    def bin_mag(self,tbins):
        self.add_mask("valid")
        self.set_mask("valid","phi",0.,op="ne",reset=True)
        self.set_mask("valid","theta",0.,op="ne",reset=True)
        self.set_mask("valid","time",tbins[0],tbins[-1],reset=True)
        time=self.get_data("valid","time")
        B=self.get_data("valid","B")
        Bx=self.get_data("valid","Bx")
        By=self.get_data("valid","By")
        Bz=self.get_data("valid","Bz")
        phi=self.get_data("valid","phi")
        theta=self.get_data("valid","theta")
        alpha=self.get_data("valid","alpha")
        mask=~isnan(Bx)
        btime,x=histogram(time[mask],tbins)
        bBx,x=histogram(time[mask],tbins,weights=Bx[mask])
        bBx/=btime
        mask=~isnan(By)
        btime,x=histogram(time[mask],tbins)
        bBy,x=histogram(time[mask],tbins,weights=By[mask])
        bBy/=btime
        mask=~isnan(Bz)
        btime,x=histogram(time[mask],tbins)
        bBz,x=histogram(time[mask],tbins,weights=Bz[mask])
        bBz/=btime
        bB=sqrt(bBx**2+bBy**2+bBz**2)
        bphi=arctan2(bBy,bBx)
        btheta=arctan2(bBz,sqrt(bBx**2+bBy**2))
        balpha=arccos(cos(bphi)*cos(btheta))
        ind=searchsorted(tbins,time,side="right")-1
        ind=ind[(ind>=0)*(ind<bB.shape[0])]
        dB=(B-bB[ind])**2
        dBx=(Bx-bBx[ind])**2
        dBy=(By-bBy[ind])**2
        dBz=(Bz-bBz[ind])**2
        dphi=(phi-bphi[ind])**2
        dtheta=(theta-btheta[ind])**2
        dalpha=(alpha-balpha[ind])**2
        dB,x=histogram(time,tbins,weights=dB)
        dB=sqrt(dB/btime)
        dBx,x=histogram(time,tbins,weights=dBx)
        dBx=sqrt(dBx/btime)
        dBy,x=histogram(time,tbins,weights=dBy)
        dBy=sqrt(dBy/btime)
        dBz,x=histogram(time,tbins,weights=dBz)
        dBz=sqrt(dBz/btime)
        dphi,x=histogram(time,tbins,weights=dphi)
        dphi=sqrt(dphi/btime)
        dtheta,x=histogram(time,tbins,weights=dtheta)
        dtheta=sqrt(dtheta/btime)
        dalpha,x=histogram(time,tbins,weights=dalpha)
        dalpha=sqrt(dalpha/btime)
        self.remove_mask("valid")
        return dbmag(data=(bB,bBx,bBy,bBz,bphi,btheta,tbins,balpha,dB,dBx,dBy,dBz,dphi,dtheta,dalpha))


class magdata:
    def __init__(self,res,year,timeframe,path): 
        self.res=res                       #  int -> time resolution of magdata in s  
        self.year=year                     #  int -> year of magdata
        self.timeframe=array(timeframe)    #  float -> start doy (float e.g. 13.5)
        self.path=path                     #  str -> path of mag data files
        self.time=[]                       #  vector with time for magdata
        self.magbx=[]                      #  Bx in GSE coord, nT 
        self.magby=[]                      #  By in GSE coord, nT
        self.magbz=[]                      #  Bz in GSE coord, nT
        self.magb=[]                       #  |B| in nT
        self.dbb=[]                        #  deltaB/B
        self.magbbinned=[]                 #  |B| in nT (binned by get_dbb.
        self.phi=[]                        #  vector [time,phi]
        self.theta=[]                      #  vector [time,theta]
        self.dpp=[]                        #  vector [time,dtphi/phi]
        self.dtt=[]                        #  vector [time,dtheta/theta]
        self.dbb=[]                        #  vector [time,dB/B]
        tmpstr=""
        for tf in self.timeframe:
            tmpstr+="_"+str(tf[0])+":"+str(tf[1])
        self.cpicklename=path+"cpickle/mag_"+str(self.res)+"_"+str(self.year)+"_"+tmpstr+".cpic"   # location for cpickle dumps
        self.load()
        
    def getvals(self,liste,start=0,stop=-9999):
        """
        Returns array that contains values that are defined in liste
        input :
        liste -> list with keywords e.g. ['time','magb']; Attention ! If liste has only 1 entry output is different s. output.
        start,stop -> set to full lenght by default; (index corresponds to time self.time[index])
                      optional define start and stop index for returned array e.g. start=10,stop=15 returns from index 10 to index 24

        valid keywords for liste are :
        'time' -> time information [doy] 
        'magb' -> |B| [nT]
        'magbx' -> Bx [nT] 
        'magby' -> By [nT] 
        'magbz' -> Bz [nT] 
        'phi' -> in-ecliptic angle between vec(B) and Sun-Earth line; vec(B) always Sun-Earth pointing 
        'theta' -> out-ecliptic angle between vec(B) and Sun-Earth line; vec(B) always Sun-Earth pointing  
        'dbb' -> sig(|B|)/|B| ; only for syncronised (binned) data  
        'dpp' -> sig(phi)/phi ; only for syncronised (binned) data  
        'dtt' -> sig(theta)/theta ; only for syncronised (binned) data  
        'prdbb' -> sqrt(sum[i=1..N](( (vec(Bi)*vec(B)/|B|)-|B|)**2) / N) ; db projected to mean vec(B); only for syncronised (binned) data  
        
        output :
        normal case liste has more than one entry ->
        array -> [stop-start,len(liste)] ; first val from liste is first column, ... last val from liste is last column 
        if liste has only a single entry ->
        array -> [stop-start] ; only vector containing the data is returned 
        """
        if (stop==-9999):
            stop=len(self.time)-start
        if len(liste)>1:
            tmpvals=zeros([stop-start,len(liste)])
            i=0
            for col in liste:
                tmpvals[:,i]=self.getcol(col,start,stop)
                i+=1
            return tmpvals
        else:
            return self.getcol(liste[0],start,stop)


    def getcol(self,col,start=0,stop=-9999):
        if (stop==-9999):
            stop=len(self.time)-start
        if (col=="time"):
            return self.time[start:stop]
        elif (col=="magb"):
            return self.magb[start:stop]
        elif (col=="magbx"):
            return self.magbx[start:stop]
        elif (col=="magby"):
            return self.magby[start:stop]
        elif (col=="magbz"):
            return self.magbz[start:stop]
        elif (col=="phi"):
            return self.phi[start:stop]
        elif (col=="theta"):
            return self.theta[start:stop]
        elif (col=="dpp"):
            return self.dpp[start:stop]
        elif (col=="dtt"):
            return self.dtt[start:stop]
        elif (col=="dbb"):
            return self.dbb[start:stop]
        elif (col=="prdbb"):
            return self.prdbb[start:stop]
        else:
            raise Exception, "Wrong keyword '%s' ! Valid Keywords are 'time','magb','magbx','magby','magbz','phi','theta'. For more details s. ?swicsiondata.getvals!"%(col) 


    def load(self):
        # format of swepam data file names : resolution[s]+year+.dat
        # e.g. "720s2007.dat" stands for 2007 data in 720s resolution
        # 02.08.10 changed data format to path/resolution/year/DoY e.g. /data/wimmer/ace/mag/1sdata/2007/001 contains data for DoY 1 of year 2007 in 1s resolution!
        # Now data is read much faster!!!!

        print "Reading Mag data from : ",self.path," ; Year : ",self.year," ; Resolution ",self.res,"s ; timeframe : ",self.timeframe
        for tf in self.timeframe:
            for DoY in range(int(tf[0]),int(tf[1])+1):
                inname=self.path+"/%isdata/"%(self.res)+str(self.year)+"/%.3i"%(DoY)
                data = loadtxt(inname,skiprows=2)
                # data is fit into timeframe
                if tf[0]<data[0,0]:
                    start=0
                else:
                    start=0
                    while tf[0]<data[0,start]:
                        start+=1
                if tf[1]>data[0,-1]:
                    end=len(data)-1
                else:
                    end=start
                    while data[0,end]<tf[1]:
                        end+=1
                data=data[start:end+1]

                # create filter to set bad values (data gaps are marked by -9999.) to 0. 
                # idea : bad value -> |B|=-9999. (+1. to avoid divison by 0.)
                #filt= (data[:,1]+1.)/abs(data[:,1]+1.)
                #filt=filt.clip(0.,1.)
                
                # append data
                if len(self.time)==0:
                    self.time=data[:,0]
                    self.magb=data[:,1]
                    self.magbx=data[:,2]*(-1.)
                    self.magby=data[:,3]
                    self.magbz=data[:,4]
                else:
                    self.time=append(self.time,data[:,0])
                    self.magb=append(self.magb,data[:,1])
                    self.magbx=append(self.magbx,data[:,2]*(-1.))
                    self.magby=append(self.magby,data[:,3])
                    self.magbz=append(self.magbz,data[:,4])

        mask=self.magb<0.
        self.magb[mask]=0.
        self.magbx[mask]=0.
        self.magby[mask]=0.
        self.magbz[mask]=0.


        self.dpp=zeros([len(self.time)])
        self.dtt=zeros([len(self.time)])
        self.dbb=zeros([len(self.time)])

        self.calc_angles()
        print "MAG-data loaded"


    def load_old(self):
        # format of swepam data file names : resolution[s]+year+.dat
        # e.g. "720s2007.dat" stands for 2007 data in 720s resolution
        # 02.08.10 changed data format to path/resolution/year/DoY e.g. /data/wimmer/ace/mag/1sdata/2007/001 contains data for DoY 1 of year 2007 in 1s resolution!
        # Now data is read much faster!!!!

        print "Reading Mag data from : ",self.path," ; Year : ",self.year," ; Resolution ",self.res,"s ; timeframe : ",self.timeframe
        for tf in self.timeframe:
            for DoY in range(int(tf[0]),int(tf[1])+1):
                inname=self.path+"/%isdata/"%(self.res)+str(self.year)+"/%.3i"%(DoY)
                data = loadtxt(inname,skiprows=2)
                # data is fit into timeframe
                if tf[0]<data[0,0]:
                    start=0
                else:
                    start=0
                    while tf[0]<data[0,start]:
                        start+=1
                if tf[1]>data[0,-1]:
                    end=len(data)-1
                else:
                    end=start
                    while data[0,end]<tf[1]:
                        end+=1
                data=data[start:end+1]

                # create filter to set bad values (data gaps are marked by -9999.) to 0. 
                # idea : bad value -> |B|=-9999. (+1. to avoid divison by 0.)
                filt= (data[:,1]+1.)/abs(data[:,1]+1.)
                filt=filt.clip(0.,1.)
                
                # append data
                if len(self.time)==0:
                    self.time=data[:,0]
                    self.magb=data[:,1]*filt
                    self.magbx=data[:,2]*filt*(-1.)
                    self.magby=data[:,3]*filt
                    self.magbz=data[:,4]*filt
                else:
                    self.time=append(self.time,data[:,0])
                    self.magb=append(self.magb,data[:,1]*filt)
                    self.magbx=append(self.magbx,data[:,2]*filt*(-1.))
                    self.magby=append(self.magby,data[:,3]*filt)
                    self.magbz=append(self.magbz,data[:,4]*filt)

        self.dpp=zeros([len(self.time)])
        self.dtt=zeros([len(self.time)])
        self.dbb=zeros([len(self.time)])

        self.calc_angles()
        print "MAG-data loaded"
        

    def get_dbb(self,bin):
        self.dbb=[]                        #  deltaB/B
        self.magbbinned=[]                 #  |B| in nT (binned by get_dbb.
        for i in range(int(len(self.magb)/bin)):
            meanb=0.
            db=0.
            time=(self.magb[(i+1)*bin-1][0]+self.magb[i*bin][0])/2.
            N=0
            for j in range(bin):
                if (self.magb[i*bin+j][1]!=0.):
                    meanb+=self.magb[i*bin+j][1]
                    N+=1
            if (N!=0):
                meanb=meanb/float(N)
                for j in range(bin):
                    db+=(self.magb[i*bin+j][1]-meanb)**2
                db=sqrt(db)/float(N)
            self.dbb.append([time,db])        
            self.magbbinned.append([time,meanb])        
      
    def calc_angles(self):
        self.phi=zeros(self.magbx.shape[0])
        self.theta=zeros(self.magbx.shape[0])
        self.THETA=zeros(self.magbx.shape[0])

        mask=(self.magbx>0.)*(self.magby<0.)
        self.phi[mask]=arctan(self.magby[mask]/self.magbx[mask])

        mask=(self.magbx>0.)*(self.magby>0.)
        self.phi[mask]=arctan(self.magby[mask]/self.magbx[mask])

        mask=(self.magbx<0.)*(self.magby<0.)
        self.phi[mask]=-arctan(self.magbx[mask]/self.magby[mask])-pi/2.

        mask=(self.magbx<0.)*(self.magby>0.)
        self.phi[mask]=pi/2.+arctan(abs(self.magbx[mask])/abs(self.magby[mask]))

        mask=(self.magbx==0.)*(self.magby>0.)
        self.phi[mask]=pi/2.

        mask=(self.magbx==0.)*(self.magby<0.)
        self.phi[mask]=-pi/2.

        # calculate theta
        mask=((self.magbx**2+self.magbz**2)!=0.)
        self.theta[mask]=arctan(self.magbz[mask]/sqrt(self.magbx[mask]**2+self.magby[mask]**2))
        mask=(self.magbx==0.)*(self.magby==0.)*(self.magbz>0.)
        self.theta[mask]=pi/2.
        mask=(self.magbx==0.)*(self.magby==0.)*(self.magbz<0.)
        self.theta[mask]=-pi/2.

        self.THETA=(arccos(cos(self.phi)*cos(self.theta)))

    def calc_angles_old(self):
        self.phi=[]
        self.theta=[]
        self.THETA=[]
        for i in range(len(self.magbx)):
            #if ((self.magbx[i]<0. and self.magby[i]<0.) or (self.magbx[i]>0. and self.magby[i]>0.)):

            # calculate phi
            if (self.magbx[i]>0. and self.magby[i]<0.):
                phi=atan(self.magby[i]/self.magbx[i])
            elif (self.magbx[i]>0. and self.magby[i]>0.):
                phi=atan(self.magby[i]/self.magbx[i])
            elif (self.magbx[i]<0. and self.magby[i]<0.):
                phi=-atan(self.magbx[i]/self.magby[i])-pi/2.
            elif (self.magbx[i]<0. and self.magby[i]>0.):
                phi=pi/2.+atan(abs(self.magbx[i])/abs(self.magby[i]))
            elif (self.magbx[i]==0.and self.magby[i]>0.):
                phi=pi/2.
            elif (self.magbx[i]==0.and self.magby[i]<0.):
                phi=-pi/2.
            else:
                phi=0.
            # calculate theta
            if (self.magbx[i]!=0. or self.magbz[i]!=0.):
                theta=atan(self.magbz[i]/sqrt(self.magbx[i]**2+self.magby[i]**2))
            elif (self.magbx[i]==0. and self.magby[i]==0. and self.magbz[i]>0.):
                theta=pi/2.
            elif (self.magbx[i]==0. and self.magby[i]==0. and self.magbz[i]<0.):
                theta=-pi/2.
            else:
                theta=0.
            self.phi.append(phi)
            self.theta.append(theta)
            self.THETA.append(acos(cos(phi)*cos(theta)))
        self.phi=array(self.phi)
        self.theta=array(self.theta)
        self.THETA=array(self.THETA)
            
    def get_dppdtt(self,bin):
        self.calc_angles()
        self.phibinned=[]
        self.thetabinned=[]
        self.dpp=[]
        self.dtt=[]
        for i in range(int(len(self.phi)/bin)):
            meanp=0.
            meant=0.
            dp=0.
            dt=0.
            time=(self.time[(i+1)*bin-1]+self.time[i*bin])/2.
            N=0
            M=0
            for j in range(bin):
                if (self.phi[i*bin+j][1]!=0.):
                    meanp+=self.phi[i*bin+j][1]
                    N+=1
                if (self.theta[i*bin+j][1]!=0.):
                    meant+=self.theta[i*bin+j][1]
                    M+=1
            if (N!=0):
                meanp=meanp/float(N)
                for j in range(bin):
                    dp+=(self.phi[i*bin+j][1]-meanp)**2
                dp=sqrt(dp)/float(N)
            if (M!=0):
                meant=meant/float(M)
                for j in range(bin):
                    dt+=(self.phi[i*bin+j][1]-meant)**2
                dt=sqrt(dt)/float(M)
            self.dpp.append([time,dp])        
            self.dtt.append([time,dt])        
            self.phibinned.append([time,meanp])        
            self.thetabinned.append([time,meant])        


    def sync_mag(self,iondata):
        """Syncronizes MAG to SWICS data!
        Warning user should be aware that the binning of the mag data is not a trivial task!
        Depending on what is needed different binning methods can be applied to the mag data resulting in different phi,theta, |B|, and vec(B).
        This routine uses:
        |B|=(sum[i=1-N] (|B|i))/N
        vec(B)=(sum[i=1-N] (vec(B)i))/N
        tan(phi) = By/Bx     (using the already calculated |B| and vec(B))
        sin(theta) = Bz/|B|  (using the already calculated |B| and vec(B)) 
        from this procedure vec(B) is not consistent with |B| and the mean angles 
        input:
        iondata -> class swicsiondata, mag data is syncronised to the time and resolution of this object!"""

        print "synchronizing MAG to SWICS data"
        offset=(self.res/2.)/86400.
        timestep=iondata.res/86400.
        newtime=iondata.time
        newmagb=zeros([len(newtime)])
        newmagbx=zeros([len(newtime)])
        newmagby=zeros([len(newtime)])
        newmagbz=zeros([len(newtime)])
        newphi=zeros([len(newtime)])
        newtheta=zeros([len(newtime)])
        newTHETA=zeros([len(newtime)])
        newdpp=zeros([len(newtime)])
        newdtt=zeros([len(newtime)])
        newdbb=zeros([len(newtime)])
        newprdbb=zeros([len(newtime)])
        newsigTHETA=zeros([len(newtime)])

        ti=0
        j=0
        newi=0
        for time in newtime:
            mask=(self.time>=time-offset)*(self.time<time+timestep-offset)*(self.magb>0.)
            newmagb[ti]=mean(self.magb[mask])
            newmagbx[ti]=mean(self.magbx[mask])
            newmagby[ti]=mean(self.magby[mask])
            newmagbz[ti]=mean(self.magbz[mask])
            newsigTHETA[ti]=std(self.THETA[mask])
            newdbb[ti]=std(self.magb[mask])/newmagb[ti]
            ti+=1

        self.time=newtime
        self.magb=newmagb
        self.magbx=newmagbx
        self.magby=newmagby
        self.magbz=newmagbz
        self.sigTHETA=newsigTHETA
        self.dpp=newdpp
        self.dtt=newdtt
        self.dbb=newdbb
        self.prdbb=newprdbb
        self.calc_angles()
        print "done"


    def sync_mag_old(self,iondata):
        """Syncronizes MAG to SWICS data!
        Warning user should be aware that the binning of the mag data is not a trivial task!
        Depending on what is needed different binning methods can be applied to the mag data resulting in different phi,theta, |B|, and vec(B).
        This routine uses:
        |B|=(sum[i=1-N] (|B|i))/N
        vec(B)=(sum[i=1-N] (vec(B)i))/N
        tan(phi) = By/Bx     (using the already calculated |B| and vec(B))
        sin(theta) = Bz/|B|  (using the already calculated |B| and vec(B)) 
        from this procedure vec(B) is not consistent with |B| and the mean angles 
        input:
        iondata -> class swicsiondata, mag data is syncronised to the time and resolution of this object!"""

        print "synchronizing MAG to SWICS data"
        offset=(self.res/2.)/86400.
        timestep=iondata.res/86400.
        newtime=iondata.time
        newmagb=zeros([len(newtime)])
        newmagbx=zeros([len(newtime)])
        newmagby=zeros([len(newtime)])
        newmagbz=zeros([len(newtime)])
        newphi=zeros([len(newtime)])
        newtheta=zeros([len(newtime)])
        newTHETA=zeros([len(newtime)])
        newdpp=zeros([len(newtime)])
        newdtt=zeros([len(newtime)])
        newdbb=zeros([len(newtime)])
        newprdbb=zeros([len(newtime)])
                       
        j=0
        newi=0
        for time in newtime:
            while (self.time[j]<time-offset and j<len(self.time)-2):
                j+=1
            N1=0.
            tmpmag=0.
            tmpmagx=0.
            tmpmagy=0.
            tmpmagz=0.
            tmpphi=0.
            tmptheta=0.
            tmpTHETA=0.
            tmpsigphi=0.
            tmpsigtheta=0.
            tmpsigmag=0.
            tmpmagarr=[]
            tmpphiarr=[]
            tmpthetaarr=[]
            tmpmagxarr=[]
            tmpmagyarr=[]
            tmpmagzarr=[]
            prb=0.
            
            while (self.time[j]<time+timestep-offset and j<len(self.time)-2):
                if (self.magb[j]>0.):
                    tmpmag+=self.magb[j]
                    tmpmagx+=self.magbx[j]
                    tmpmagy+=self.magby[j]
                    tmpmagz+=self.magbz[j]
                    if self.phi[j]>0.:
                        tmpphi+=self.phi[j]
                    elif self.phi[j]<0.:
                        tmpphi+=self.phi[j]+2.*pi
                    tmptheta+=self.theta[j]
                    tmpTHETA+=self.THETA[j]
                    tmpmagarr.append(self.magb[j])
                    tmpmagxarr.append(self.magbx[j])
                    tmpmagyarr.append(self.magby[j])
                    tmpmagzarr.append(self.magbz[j])
                    tmpphiarr.append(self.phi[j])
                    tmpthetaarr.append(self.theta[j])
                    N1+=1.
                j+=1
            if (N1>0.):
                tmpmagx/=N1
                tmpmagy/=N1
                tmpmagz/=N1
                tmpmag/=N1
                #tmpmag=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
                # calculate phi
                if (tmpmagx>0. and tmpmagy<0.):
                    tmpphi=atan(tmpmagy/tmpmagx)
                elif (tmpmagx>0. and tmpmagy>0.):
                    tmpphi=atan(tmpmagy/tmpmagx)
                elif (tmpmagx<0. and tmpmagy<0.):
                    tmpphi=-atan(tmpmagx/tmpmagy)-pi/2.
                elif (tmpmagx<0. and tmpmagy>0.):
                    tmpphi=pi/2.+atan(abs(tmpmagx)/tmpmagy)
                elif (tmpmagx==0.and tmpmagy>0.):
                    tmpphi=pi/2.
                elif (tmpmagx==0.and tmpmagy<0.):
                    tmpphi=-pi/2.
                else:
                    tmpphi=0.
                # calculate theta
                if (tmpmag>0.):
                    #print newtime[newi],tmpmagz,tmpmag
                    tmptheta=atan(tmpmagz/sqrt(tmpmagx**2+tmpmagy**2))
                else:
                    tmptheta=0.
                tmpTHETA=acos(cos(tmpphi)*cos(tmptheta))
                N2=0.
                meanb=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
                for l in range(len(tmpmagarr)):
                    if (tmpmagarr[l]>0.):
                        N2+=1.
                        prb+=(((tmpmagxarr[l]*tmpmagx+tmpmagyarr[l]*tmpmagy+tmpmagzarr[l]*tmpmagz)/meanb**2)-1.)**2
                if (N2>0.):
                    prb=sqrt(prb/N2)
                    
                for mag in tmpmagarr:
                    tmpsigmag+=(mag-tmpmag)**2
                for phi in tmpphiarr:
                    tmpsigphi+=(phi-tmpphi)**2
                for theta in tmpthetaarr:
                    tmpsigtheta+=(theta-tmptheta)**2
                tmpsigmag=sqrt(tmpsigmag/N1)
                tmpsigphi=sqrt(tmpsigphi/N1)
                tmpsigtheta=sqrt(tmpsigtheta/N1)
            # put meanvals into new arrays
            newmagb[newi]=tmpmag
            newmagbx[newi]=tmpmagx
            newmagby[newi]=tmpmagy
            newmagbz[newi]=tmpmagz
            newphi[newi]=tmpphi
            newtheta[newi]=tmptheta
            newTHETA[newi]=tmpTHETA
            if (tmpmag!=0.):
                newdbb[newi]=tmpsigmag/tmpmag
            if (tmpphi!=0.):
                newdpp[newi]=tmpsigphi/tmpphi
            if (tmptheta!=0.):
                newdtt[newi]=tmpsigtheta/tmptheta
            newprdbb[newi]=prb
            newi+=1

        self.time=newtime
        self.magb=newmagb
        self.magbx=newmagbx
        self.magby=newmagby
        self.magbz=newmagbz
        self.phi=newphi
        self.theta=newtheta
        self.THETA=newTHETA
        self.dpp=newdpp
        self.dtt=newdtt
        self.dbb=newdbb
        self.prdbb=newprdbb

        print "done"

    def sync_mag_hires(self,iondata):
        """Syncronizes MAG to SWICS data!
        hires means that timeresolution is higher than 12 minutes, this is achieved by using the fact that SWICS measurements of VDFs is done
        in a subinterval of the 12 minutes duty cycle.
        A 64s interval around the time of the bulk velocity measurement is used to get mean mag values (64s = resolution of SWEPAM data)!
        This should work only if resolution of mag data is 1 s !!!!
        Warning user should be aware that the binning of the mag data is not a trivial task!
        Depending on what is needed different binning methods can be applied to the mag data resulting in different phi,theta, |B|, and vec(B).
        This routine uses:
        |B|=(sum[i=1-N] (|B|i))/N
        vec(B)=(sum[i=1-N] (vec(B)i))/N
        tan(phi) = By/Bx     (using the already calculated |B| and vec(B))
        sin(theta) = Bz/|B|  (using the already calculated |B| and vec(B)) 
        from this procedure vec(B) is not consistent with |B| and the mean angles 
        input:
        iondata -> class swicsiondata, mag data is syncronised to the time and resolution of this object!"""

        print "synchronizing MAG to SWICS data"

        from libacepy.mag import get_wpspec
        from libacepy.ancil import numint

        offset=(self.res/2.)/86400. # offset from mag resolution
        timestep=64./86400.         # define time resolution (here 64s because of SWEPAM resolution

        newtime=iondata.time
        newrealtime=zeros([len(newtime)])
        newmagb=zeros([len(newtime)])
        newmagbx=zeros([len(newtime)])
        newmagby=zeros([len(newtime)])
        newmagbz=zeros([len(newtime)])
        newphi=zeros([len(newtime)])
        newtheta=zeros([len(newtime)])
        newTHETA=zeros([len(newtime)])
        newdpp=zeros([len(newtime)])
        newdtt=zeros([len(newtime)])
        newdbb=zeros([len(newtime)])
        newwp1=zeros([len(newtime)])
        newwp2=zeros([len(newtime)])
        newwp3=zeros([len(newtime)])
        newprdbb=zeros([len(newtime)])
        newdang=zeros([len(newtime)])

                       
        j=0
        newi=0
        end=0
        for time in newtime:
            # search ESA step of bulk velocity
            k=0
            while iondata.vel[newi]<=iondata.countspec[newi][k][0] and k<57:
                k+=1
            tmpnewtime=time+float(k)*12./86400.
            newrealtime[newi]=tmpnewtime
            while (self.time[j]<tmpnewtime-3.*timestep/2.-offset and j<len(self.time)-2):
                j+=1
            N1=0.
            tmpmag=0.
            tmpmagx=0.
            tmpmagy=0.
            tmpmagz=0.
            tmpphi=0.
            tmptheta=0.
            tmpTHETA=0.
            tmpsigphi=0.
            tmpsigtheta=0.
            tmpsigmag=0.
            tmpmagarr=[]
            tmpphiarr=[]
            tmpthetaarr=[]
            tmpmagxarr=[]
            tmpmagyarr=[]
            tmpmagzarr=[]
            prb=0.
            
            # get mean phi and theta from 64s interval before bulk velocity : prevphi,prevtheta

            while (self.time[j]<tmpnewtime-timestep/2.-offset and j<len(self.time)-2):
                if (self.magb[j]>0.):
                    tmpmag+=self.magb[j]
                    tmpmagx+=self.magbx[j]
                    tmpmagy+=self.magby[j]
                    tmpmagz+=self.magbz[j]
                    N1+=1.
                j+=1

            if (N1>0.):
                tmpmagx/=N1
                tmpmagy/=N1
                tmpmagz/=N1
                tmpmag/=N1
                #tmpmag=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
                # calculate phi
                if (tmpmagx>0. and tmpmagy<0.):
                    tmpphi=atan(tmpmagy/tmpmagx)
                elif (tmpmagx>0. and tmpmagy>0.):
                    tmpphi=atan(tmpmagy/tmpmagx)
                elif (tmpmagx<0. and tmpmagy<0.):
                    tmpphi=-atan(tmpmagx/tmpmagy)-pi/2.
                elif (tmpmagx<0. and tmpmagy>0.):
                    tmpphi=pi/2.+atan(abs(tmpmagx)/tmpmagy)
                elif (tmpmagx==0.and tmpmagy>0.):
                    tmpphi=pi/2.
                elif (tmpmagx==0.and tmpmagy<0.):
                    tmpphi=-pi/2.
                else:
                    tmpphi=0.
                # calculate theta
                if (tmpmag>0.):
                    tmptheta=asin(tmpmagz/tmpmag)
                else:
                    tmptheta=0.

            prevphi=tmpphi
            prevtheta=tmptheta
            N1=0.
            tmpphi=0.
            tmptheta=0.
            tmpmag=0.
            tmpmagx=0.
            tmpmagy=0.
            tmpmagz=0.
            tmpphi=0.
            tmptheta=0.
            tmpTHETA=0.
            
            if (j==len(self.time)-2):
                end=1
            if (end==0):
                # calculate mean values in 64s time intervall of bulk velocity
                while (self.time[j]<tmpnewtime+timestep/2.-offset and j<len(self.time)-2):
                    if (self.magb[j]>0.):
                        tmpmag+=self.magb[j]
                        tmpmagx+=self.magbx[j]
                        tmpmagy+=self.magby[j]
                        tmpmagz+=self.magbz[j]
                        tmpmagarr.append(self.magb[j])
                        tmpmagxarr.append(self.magbx[j])
                        tmpmagyarr.append(self.magby[j])
                        tmpmagzarr.append(self.magbz[j])
                        if self.phi[j]>0.:
                            tmpphi+=self.phi[j]
                        elif self.phi[j]<0.:
                            tmpphi+=self.phi[j]+2.*pi
                        tmptheta+=self.theta[j]
                        tmpTHETA+=self.THETA[j]
                        tmpphiarr.append(self.phi[j])
                        tmpthetaarr.append(self.theta[j])
                        N1+=1.
                    j+=1

                wp1=0.
                wp2=0.
                wp3=0.
                if (N1>0.):
                    psdx=get_wpspec(tmpmagxarr,1.)
                    psdy=get_wpspec(tmpmagyarr,1.)
                    psdz=get_wpspec(tmpmagzarr,1.)
                    intx1=numint(psdx,0.01,0.1)
                    intx2=numint(psdx,0.1,1.)
                    intx3=numint(psdx,0.01,.075)+numint(psdx,0.09,1.)
                    inty1=numint(psdy,0.01,0.1)
                    inty2=numint(psdy,0.1,1.)
                    inty3=numint(psdy,0.01,.075)+numint(psdy,0.09,1.)
                    intz1=numint(psdz,0.01,0.1)
                    intz2=numint(psdz,0.1,1.)
                    intz3=numint(psdz,0.01,.075)+numint(psdz,0.09,1.)
                    wp1=(intx1+inty1+intz1)
                    wp2=(intx2+inty2+intz2)
                    wp3=(intx3+inty3+intz3)

                    tmpmagx/=N1
                    tmpmagy/=N1
                    tmpmagz/=N1
                    tmpmag/=N1
                    #tmpmag=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
                    # calculate phi
                    if (tmpmagx>0. and tmpmagy<0.):
                        tmpphi=atan(tmpmagy/tmpmagx)
                    elif (tmpmagx>0. and tmpmagy>0.):
                        tmpphi=atan(tmpmagy/tmpmagx)
                    elif (tmpmagx<0. and tmpmagy<0.):
                        tmpphi=-atan(tmpmagx/tmpmagy)-pi/2.
                    elif (tmpmagx<0. and tmpmagy>0.):
                        tmpphi=pi/2.+atan(abs(tmpmagx)/tmpmagy)
                    elif (tmpmagx==0.and tmpmagy>0.):
                        tmpphi=pi/2.
                    elif (tmpmagx==0.and tmpmagy<0.):
                        tmpphi=-pi/2.
                    else:
                        tmpphi=0.
                    # calculate theta
                    if (tmpmag>0.):
                        tmptheta=atan(tmpmagz/sqrt(tmpmagx**2+tmpmagy**2))
                    else:
                        tmptheta=0.

                    tmpTHETA=acos(cos(tmpphi)*cos(tmptheta))
                    N2=0.
                    meanb=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
                    for l in range(len(tmpmagarr)):
                        if (tmpmagarr[l]>0.):
                            N2+=1.
                            prb+=(((tmpmagxarr[l]*tmpmagx+tmpmagyarr[l]*tmpmagy+tmpmagzarr[l]*tmpmagz)/meanb**2)-1.)**2
                    if (N2>0.):
                        prb=sqrt(prb/N2)

                    for mag in tmpmagarr:
                        tmpsigmag+=(mag-tmpmag)**2
                    for phi in tmpphiarr:
                        tmpsigphi+=(phi-tmpphi)**2
                    for theta in tmpthetaarr:
                        tmpsigtheta+=(theta-tmptheta)**2
                    tmpsigmag=sqrt(tmpsigmag/N1)
                    tmpsigphi=sqrt(tmpsigphi/N1)
                    tmpsigtheta=sqrt(tmpsigtheta/N1)

                # get mean phi and theta from 64s interval after bulk velocity : nextphi,nexttheta

                tmpmag2=0.
                tmpmagx2=0.
                tmpmagy2=0.
                tmpmagz2=0.
                N12=0.
                while (self.time[j]<tmpnewtime+3*timestep/2.-offset and j<len(self.time)-2):
                    if (self.magb[j]>0.):
                        tmpmag2+=self.magb[j]
                        tmpmagx2+=self.magbx[j]
                        tmpmagy2+=self.magby[j]
                        tmpmagz2+=self.magbz[j]
                        N12+=1.
                    j+=1

                tmpphi2=0.
                tmptheta2=0.
                if (N12>0.):
                    tmpmagx2/=N12
                    tmpmagy2/=N12
                    tmpmagz2/=N12
                    tmpmag2=sqrt(tmpmagx2**2+tmpmagy2**2+tmpmagz2**2)
                    # calculate phi
                    if (tmpmagx2>0. and tmpmagy2<0.):
                        tmpphi2=atan(tmpmagy2/tmpmagx2)
                    elif (tmpmagx2>0. and tmpmagy2>0.):
                        tmpphi2=atan(tmpmagy2/tmpmagx2)
                    elif (tmpmagx2<0. and tmpmagy2<0.):
                        tmpphi2=-atan(tmpmagx2/tmpmagy2)-pi/2.
                    elif (tmpmagx2<0. and tmpmagy2>0.):
                        tmpphi2=pi/2.+atan(abs(tmpmagx2)/tmpmagy2)
                    elif (tmpmagx2==0.and tmpmagy2>0.):
                        tmpphi2=pi/2.
                    elif (tmpmagx2==0.and tmpmagy2<0.):
                        tmpphi2=-pi/2.
                    else:
                        tmpphi2=0.
                    # calculate theta
                    if (tmpmag2>0.):
                        tmptheta2=asin(tmpmagz2/tmpmag2)
                    else:
                        tmptheta2=0.

                nextphi=tmpphi2
                nexttheta=tmptheta2

                dang=max(acos(cos(prevphi-tmpphi)*cos(prevtheta-tmptheta)),acos(cos(nextphi-tmpphi)*cos(nexttheta-tmptheta)))

                # put meanvals into new arrays
                newmagb[newi]=tmpmag
                newmagbx[newi]=tmpmagx
                newmagby[newi]=tmpmagy
                newmagbz[newi]=tmpmagz
                newphi[newi]=tmpphi
                newtheta[newi]=tmptheta
                newTHETA[newi]=tmpTHETA
                if (tmpmag!=0.):
                    newdbb[newi]=tmpsigmag/tmpmag
                if (tmpphi!=0.):
                    newdpp[newi]=tmpsigphi/tmpphi
                if (tmptheta!=0.):
                    newdtt[newi]=tmpsigtheta/tmptheta
                newprdbb[newi]=prb
                newwp1[newi]=wp1
                newwp2[newi]=wp2
                newwp3[newi]=wp3
                newdang[newi]=dang
                newi+=1

        self.time=newtime
        self.realtime=newrealtime
        self.magb=newmagb
        self.magbx=newmagbx
        self.magby=newmagby
        self.magbz=newmagbz
        self.phi=newphi
        self.theta=newtheta
        self.THETA=newTHETA
        self.dpp=newdpp
        self.dtt=newdtt
        self.dbb=newdbb
        self.prdbb=newprdbb
        self.wp1=newwp1
        self.wp2=newwp2
        self.wp3=newwp3
        self.dang=newdang

        print "done"

    def sync_mag_swepam(self,iondata):
        """Syncronizes MAG to SWEPAM data!
        input:
        iondata -> class swepamdata, mag data is syncronised to the time and resolution of this object!"""

        print "synchronizing MAG to SWEPAM data"

        from libacepy.ancil import numint

        offset=(self.res/2.)/86400. # offset from mag resolution
        timestep=64./86400.         # define time resolution (here 64s because of SWEPAM resolution

        newtime=iondata.time
        newrealtime=zeros([len(newtime)])
        newmagb=zeros([len(newtime)])
        newmagbx=zeros([len(newtime)])
        newmagby=zeros([len(newtime)])
        newmagbz=zeros([len(newtime)])
        newphi=zeros([len(newtime)])
        newtheta=zeros([len(newtime)])
        newTHETA=zeros([len(newtime)])
        newdpp=zeros([len(newtime)])
        newdtt=zeros([len(newtime)])
        newdbb=zeros([len(newtime)])
        newwp1=zeros([len(newtime)])
        newwp2=zeros([len(newtime)])
        newwp3=zeros([len(newtime)])
        newprdbb=zeros([len(newtime)])
        newdang=zeros([len(newtime)])

                       
        j=0
        newi=0
        end=0
        for time in newtime:
            # search ESA step of bulk velocity
            
            #while (self.time[j]<time-offset and j<len(self.time)-2):
            while (self.time[j]<time-timestep/2.-offset and j<len(self.time)-2):
                j+=1
            newrealtime[newi]=time
            N1=0.
            tmpmag=0.
            tmpmagx=0.
            tmpmagy=0.
            tmpmagz=0.
            tmpphi=0.
            tmptheta=0.
            tmpTHETA=0.
            tmpsigphi=0.
            tmpsigtheta=0.
            tmpsigmag=0.
            tmpmagarr=[]
            tmpphiarr=[]
            tmpthetaarr=[]
            tmpmagxarr=[]
            tmpmagyarr=[]
            tmpmagzarr=[]
            prb=0.
            
            if (j==len(self.time)-2):
                end=1
            if (end==0):
                # calculate mean values in 64s time intervall of bulk velocity
                while (self.time[j]<time+timestep/2.-offset and j<len(self.time)-2):
                #while (self.time[j]<time+timestep-offset and j<len(self.time)-2):
                    if (self.magb[j]>0.):
                        tmpmag+=self.magb[j]
                        tmpmagx+=self.magbx[j]
                        tmpmagy+=self.magby[j]
                        tmpmagz+=self.magbz[j]
                        tmpmagarr.append(self.magb[j])
                        tmpmagxarr.append(self.magbx[j])
                        tmpmagyarr.append(self.magby[j])
                        tmpmagzarr.append(self.magbz[j])
                        if self.phi[j]>0.:
                            tmpphi+=self.phi[j]
                        elif self.phi[j]<0.:
                            tmpphi+=self.phi[j]+2.*pi
                        tmptheta+=self.theta[j]
                        tmpTHETA+=self.THETA[j]
                        tmpphiarr.append(self.phi[j])
                        tmpthetaarr.append(self.theta[j])
                        N1+=1.
                    j+=1

                if (N1>0.):
                    tmpmagx/=N1
                    tmpmagy/=N1
                    tmpmagz/=N1
                    tmpmag/=N1
                    #tmpmag=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
                    # calculate phi
                    if (tmpmagx>0. and tmpmagy<0.):
                        tmpphi=atan(tmpmagy/tmpmagx)
                    elif (tmpmagx>0. and tmpmagy>0.):
                        tmpphi=atan(tmpmagy/tmpmagx)
                    elif (tmpmagx<0. and tmpmagy<0.):
                        tmpphi=-atan(tmpmagx/tmpmagy)-pi/2.
                    elif (tmpmagx<0. and tmpmagy>0.):
                        tmpphi=pi/2.+atan(abs(tmpmagx)/tmpmagy)
                    elif (tmpmagx==0.and tmpmagy>0.):
                        tmpphi=pi/2.
                    elif (tmpmagx==0.and tmpmagy<0.):
                        tmpphi=-pi/2.
                    else:
                        tmpphi=0.
                    # calculate theta
                    if (tmpmag>0.):
                        tmptheta=atan(tmpmagz/sqrt(tmpmagx**2+tmpmagy**2))
                    else:
                        tmptheta=0.

                    tmpTHETA=acos(cos(tmpphi)*cos(tmptheta))
                    N2=0.
                    meanb=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
                    for l in range(len(tmpmagarr)):
                        if (tmpmagarr[l]>0.):
                            N2+=1.
                            prb+=(((tmpmagxarr[l]*tmpmagx+tmpmagyarr[l]*tmpmagy+tmpmagzarr[l]*tmpmagz)/meanb**2)-1.)**2
                    if (N2>0.):
                        prb=sqrt(prb/N2)

                    for mag in tmpmagarr:
                        tmpsigmag+=(mag-tmpmag)**2
                    for phi in tmpphiarr:
                        tmpsigphi+=(phi-tmpphi)**2
                    for theta in tmpthetaarr:
                        tmpsigtheta+=(theta-tmptheta)**2
                    tmpsigmag=sqrt(tmpsigmag/N1)
                    tmpsigphi=sqrt(tmpsigphi/N1)
                    tmpsigtheta=sqrt(tmpsigtheta/N1)

                # put meanvals into new arrays
                newmagb[newi]=tmpmag
                newmagbx[newi]=tmpmagx
                newmagby[newi]=tmpmagy
                newmagbz[newi]=tmpmagz
                newphi[newi]=tmpphi
                newtheta[newi]=tmptheta
                newTHETA[newi]=tmpTHETA
                if (tmpmag!=0.):
                    newdbb[newi]=tmpsigmag/tmpmag
                if (tmpphi!=0.):
                    newdpp[newi]=tmpsigphi/tmpphi
                if (tmptheta!=0.):
                    newdtt[newi]=tmpsigtheta/tmptheta
                newprdbb[newi]=prb
                newi+=1

        self.time=newtime
        self.realtime=newrealtime
        self.magb=newmagb
        self.magbx=newmagbx
        self.magby=newmagby
        self.magbz=newmagbz
        self.phi=newphi
        self.theta=newtheta
        self.THETA=newTHETA
        self.dpp=newdpp
        self.dtt=newdtt
        self.dbb=newdbb
        self.prdbb=newprdbb
        self.dang=newdang

        print "done"


    def sync_mag_uw(self,iondata):
        """Syncronizes MAG to SWICS data!
        Warning user should be aware that the binning of the mag data is not a trivial task!
        Depending on what is needed different binning methods can be applied to the mag data resulting in different phi,theta, |B|, and vec(B).
        This routine uses:
        |B|=(sum[i=1-N] (|B|i))/N
        vec(B)=(sum[i=1-N] (vec(B)i))/N
        tan(phi) = By/Bx     (using the already calculated |B| and vec(B))
        sin(theta) = Bz/|B|  (using the already calculated |B| and vec(B)) 
        from this procedure vec(B) is not consistent with |B| and the mean angles 
        input:
        iondata -> class swicsiondata, mag data is syncronised to the time and resolution of this object!"""

        print "synchronizing MAG to SWICS data"
        offset=(self.res/2.)/86400.
        timestep=iondata.res/86400.
        newtime=iondata.time
        newmagb=zeros([len(newtime)])
        newmagbx=zeros([len(newtime)])
        newmagby=zeros([len(newtime)])
        newmagbz=zeros([len(newtime)])
        newphi=zeros([len(newtime)])
        newtheta=zeros([len(newtime)])
        newdpp=zeros([len(newtime)])
        newdtt=zeros([len(newtime)])
        newdbb=zeros([len(newtime)])
        newprdbb=zeros([len(newtime)])
                       
        j=0
        newi=0
        for time in newtime:
            while (self.time[j]<time-offset and j<len(self.time)-2):
                j+=1
            N1=0.
            tmpmag=0.
            tmpmagx=0.
            tmpmagy=0.
            tmpmagz=0.
            tmpphi=0.
            tmptheta=0.
            tmpsigphi=0.
            tmpsigtheta=0.
            tmpsigmag=0.
            tmpmagarr=[]
            tmpphiarr=[]
            tmpthetaarr=[]
            tmpmagxarr=[]
            tmpmagyarr=[]
            tmpmagzarr=[]
            
            while (self.time[j]<time+timestep-offset and j<len(self.time)-2):
                if (self.magb[j]>0.):
                    tmpmag+=self.magb[j]
                    tmpmagx+=self.magbx[j]
                    tmpmagy+=self.magby[j]
                    tmpmagz+=self.magbz[j]
                    if self.phi[j]>0.:
                        tmpphi+=self.phi[j]
                    elif self.phi[j]<0.:
                        tmpphi+=self.phi[j]+2*pi
                    tmptheta+=self.theta[j]
                    tmpmagarr.append(self.magb[j])
                    tmpmagxarr.append(self.magbx[j])
                    tmpmagyarr.append(self.magby[j])
                    tmpmagzarr.append(self.magbz[j])
                    tmpphiarr.append(self.phi[j])
                    tmpthetaarr.append(self.theta[j])
                    N1+=1.
                j+=1
            if (N1>0.):
                tmpmag/=N1
                tmpmagx/=N1
                tmpmagy/=N1
                tmpmagz/=N1
                tmpphi/=N1
                tmptheta/=N1
                    
                N2=0.
                meanb=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
                prb=0.
                for i in range(len(tmpmagarr)):
                    if (tmpmagarr[i]>0.):
                        N2+=1.
                        prb+=(((tmpmagxarr[i]*tmpmagx+tmpmagyarr[i]*tmpmagy+tmpmagzarr[i]*tmpmagz)/meanb)-meanb)**2
                if (N2>0.):
                    prb=sqrt(prb/N2)
                for mag in tmpmagarr:
                    tmpsigmag+=(mag-tmpmag)**2
                for phi in tmpphiarr:
                    tmpsigphi+=(phi-tmpphi)**2
                for theta in tmpthetaarr:
                    tmpsigtheta+=(theta-tmptheta)**2
                tmpsigmag=sqrt(tmpsigmag/N1)
                tmpsigphi=sqrt(tmpsigphi/N1)
                tmpsigtheta=sqrt(tmpsigtheta/N1)
            # put meanvals into new arrays
            newmagb[newi]=tmpmag
            newmagbx[newi]=tmpmagx
            newmagby[newi]=tmpmagy
            newmagbz[newi]=tmpmagz
            newphi[newi]=tmpphi
            newtheta[newi]=tmptheta
            newprdbb[newi]=prb
            if (tmpmag!=0.):
                newdbb[newi]=tmpsigmag/tmpmag
            if (tmpphi!=0.):
                newdpp[newi]=tmpsigphi/tmpphi
            if (tmptheta!=0.):
                newdtt[newi]=tmpsigtheta/tmptheta
            newi+=1

        self.time=newtime
        self.magb=newmagb
        self.magbx=newmagbx
        self.magby=newmagby
        self.magbz=newmagbz
        self.phi=newphi
        self.theta=newtheta
        self.dpp=newdpp
        self.dtt=newdtt
        self.dbb=newdbb
        self.prdbb=newprdbb

        print "done"


def get_wpspec(magdat,timeres):
    """Returns wave-power spectrum of input (mag)data\ninput:\nmagdat\t->\t list or array 1D\ntimeres\t->\ttimeresolution of the data"""

    from numpy.fft import fft
    from numpy import array
    
    rawpsd=fft(magdat)

    N=len(magdat)
    psd=[]
    for i in range(len(rawpsd)/2+1):
        psd.append([(float(i)/(float(N)*timeres)),2.*abs(rawpsd[i].imag**2)/N+2.*abs(rawpsd[i].real**2)/N])

    psd=array(psd)
    return psd

def loadmagdata(res,year,timeframe,path,dump=1,loaddump=1):
    """
    loads magdata, prefers cpickled data
    """

    from os.path import isfile
    from libacepy.mag import magdata
    import cPickle
    tmpstr=""
    for tf in timeframe:
        tmpstr+="_"+str(tf[0])+":"+str(tf[1])
        
    cpicklename=path+"cpickle/mag_"+str(res)+"_"+str(year)+"_"+tmpstr+".cpic"   # location for cpickle dumps
    #print "load : ",cpicklename
    if isfile(cpicklename) and loaddump:
        inf=open(cpicklename,"r")
        tmp=cPickle.load(inf)
        inf.close()
        print cpicklename+" loaded"
        return tmp
    else:
        mag=magdata(res,year,timeframe,path)
        if dump:
            dumpmagdata(mag)
        return mag
    
def dumpmagdata(data):
    """
    cpickles object of type swicsiondata
    """
    from libacepy.mag import magdata
    import cPickle
    out=open(data.cpicklename,"w")
    cPickle.dump(data,out)
    out.close()
    print "Dumped "+data.cpicklename
