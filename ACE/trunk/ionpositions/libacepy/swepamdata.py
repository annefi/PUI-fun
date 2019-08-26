from numpy import *
from pylib import dbData

class dbswepam(dbData):
    def load_data(self,*args,**kwargs):
        if not(("res" in kwargs.keys()) and ("year" in kwargs.keys()) and ("tf" in kwargs.keys())) and not("data" in kwargs.keys()):
            print "Need res,year,tf! or data"
            return
        if ("data" in kwargs.keys()):
            print "generate dbmag with direct data input"
            self.ion="H1+"                            #  str -> name of ion  
            self.mass=1.                              #  float -> ion mass
            self.charge=1.                            #  float -> ion charge
            dat=kwargs["data"]
            self.data["time"]=dat[0]
            self.data["vel"]=dat[1]
            self.data["velx"]=dat[2]
            self.data["vely"]=dat[3]
            self.data["velz"]=dat[4]
            self.data["dens"]=dat[5]
            self.data["temp"]=dat[6]
            self.data["heh"]=dat[7]
            self.data["vth"]=dat[8]
            self.data["dvel"]=dat[9]
            self.data["dvelx"]=dat[10]
            self.data["dvely"]=dat[11]
            self.data["dvelz"]=dat[12]
            self.data["ddens"]=dat[13]
            self.data["dtemp"]=dat[14]
            self.data["dheh"]=dat[15]
            self.data["dvth"]=dat[16]
            return
        if not("path" in kwargs.keys()):
            path="/data/etph/ace/swepam/"
        else:
            path=kwargs["path"]
        self.ion="H1+"                            #  str -> name of ion  
        self.path=path                            #  str -> path of data
        self.mass=1.                              #  float -> ion mass
        self.charge=1.                            #  float -> ion charge
        self.res=kwargs["res"]                    #  int -> time resolution of magdata in s  
        self.year=kwargs["year"]                  #  int -> year of magdata
        self.timeframe=array(kwargs["tf"])        #  n x 2 array : [[start1,stop1],....,[startn,stopn]] periods should be arranged by ascending time 
        # format of swepam data file names : resolution[s]+year+.dat
        # e.g. "720s2007.dat" stands for 2007 data in 720s resolution
        inname=self.path+"%i"%(self.res)+"s"+str(self.year)+".dat"
        print "Reading : ",inname
        swepamdatain=open(inname)
        s=swepamdatain.readline()
        k=s.split()
        # fast-forward header
        while (k[0]!="BEGIN" or k[1]!="DATA"):
            s=swepamdatain.readline()
            k=s.split()
            if (len(k)<2):
                k=["*","*"]
        # start reading data
        dat=loadtxt(swepamdatain)
        dat[dat<=-999.]=nan
        mask=zeros(dat.shape[0],bool)
        for tf in self.timeframe:
            mask+=(dat[:,1]>=tf[0])*(dat[:,1]<=tf[1])
        
        self.data["time"]=dat[:,1][mask]          #  vector [time]
        self.data["vel"]=dat[:,5][mask]           #  vector [vel]
        self.data["velx"]=dat[:,6][mask]          #  vector [vel]
        self.data["vely"]=dat[:,7][mask]          #  vector [vel]
        self.data["velz"]=dat[:,8][mask]          #  vector [vel]
        self.data["dens"]=dat[:,2][mask]          #  vector [dens]
        self.data["temp"]=dat[:,3][mask]          #  vector [temp]
        self.data["heh"]=dat[:,4][mask]           #  vector [heh]
        self.data["vth"]=self.calc_vth(self.data["temp"])
        print "SWEPAM-data loaded"

    def calc_vth(self,temp):
        "Calculates thermal velocities from temperatures"
        from scipy.constants import Bolzmann as kb
        from scipy.constants import atomic_mass as u
        return sqrt(temp*kb/(self.mass*u))/1000.

    def bin_swepam(self,tbins):
        self.add_mask("valid")
        self.set_mask("valid","time",tbins[0],tbins[-1],reset=True)
        time=self.get_data("valid","time")
        vel=self.get_data("valid","vel")
        velx=self.get_data("valid","velx")
        vely=self.get_data("valid","vely")
        velz=self.get_data("valid","velz")
        dens=self.get_data("valid","dens")
        temp=self.get_data("valid","temp")
        heh=self.get_data("valid","heh")
        vth=self.get_data("valid","vth")
        mask=(~isnan(vel))
        tbtime,x=histogram(time[mask],tbins)
        bvel,x=histogram(time[mask],tbins,weights=vel[mask])
        bvel/=tbtime
        mask=(~isnan(velx))
        tbtime,x=histogram(time[mask],tbins)
        bvelx,x=histogram(time[mask],tbins,weights=velx[mask])
        bvelx/=tbtime
        mask=(~isnan(vely))
        tbtime,x=histogram(time[mask],tbins)
        bvely,x=histogram(time[mask],tbins,weights=vely[mask])
        bvely/=tbtime
        mask=(~isnan(velz))
        tbtime,x=histogram(time[mask],tbins)
        bvelz,x=histogram(time[mask],tbins,weights=velz[mask])
        bvelz/=tbtime
        mask=(~isnan(dens))
        tbtime,x=histogram(time[mask],tbins)
        bdens,x=histogram(time[mask],tbins,weights=dens[mask])
        bdens/=tbtime
        mask=(~isnan(temp))
        btemp,x=histogram(time[mask],tbins,weights=temp[mask])
        btemp/=tbtime
        mask=(~isnan(heh))
        tbtime,x=histogram(time[mask],tbins)
        bheh,x=histogram(time[mask],tbins,weights=heh[mask])
        bheh/=tbtime
        bvth=self.calc_vth(btemp)

        ind=searchsorted(tbins[:],time,side="right")-1
        ind=ind[(ind>=0)*(ind<bvel.shape[0])]
        dvel=(vel-bvel[ind])**2
        mask=(~isnan(dvel))
        tbtime,x=histogram(time[mask],tbins)
        dvel,x=histogram(time[mask],tbins,weights=dvel[mask])
        dvel=sqrt(dvel/tbtime)
        dvelx=(velx-bvelx[ind])**2
        mask=(~isnan(dvelx))
        tbtime,x=histogram(time[mask],tbins)
        dvelx,x=histogram(time[mask],tbins,weights=dvelx[mask])
        dvelx=sqrt(dvelx/tbtime)
        dvely=(vely-bvely[ind])**2
        mask=(~isnan(dvely))
        tbtime,x=histogram(time[mask],tbins)
        dvely,x=histogram(time[mask],tbins,weights=dvely[mask])
        dvely=sqrt(dvely/tbtime)
        dvelz=(velz-bvelz[ind])**2
        mask=(~isnan(dvelz))
        tbtime,x=histogram(time[mask],tbins)
        dvelz,x=histogram(time[mask],tbins,weights=dvelz[mask])
        dvelz=sqrt(dvelz/tbtime)
        ddens=(dens-bdens[ind])**2
        mask=(~isnan(ddens))
        tbtime,x=histogram(time[mask],tbins)
        ddens,x=histogram(time[mask],tbins,weights=ddens[mask])
        ddens=sqrt(ddens/tbtime)
        dtemp=(temp-btemp[ind])**2
        mask=(~isnan(dtemp))
        tbtime,x=histogram(time[mask],tbins)
        dtemp,x=histogram(time[mask],tbins,weights=dtemp[mask])
        dtemp=sqrt(dtemp/tbtime)
        dheh=(heh-bheh[ind])**2
        mask=(~isnan(dheh))
        tbtime,x=histogram(time[mask],tbins)
        dheh,x=histogram(time[mask],tbins,weights=dheh[mask])
        dheh=sqrt(dheh/tbtime)
        dvth=(vth-bvth[ind])**2
        mask=(~isnan(dvth))
        tbtime,x=histogram(time[mask],tbins)
        dvth,x=histogram(time[mask],tbins,weights=dvth[mask])
        dvth=sqrt(dvth/tbtime)
        
        return dbswepam(data=(tbins[:-1],bvel,bvelx,bvely,bvelz,bdens,btemp,bheh,bvth,dvel,dvelx,dvely,dvelz,ddens,dtemp,dheh,dvth))




class swepamdata:
    """
    Class for swepam protondata. Timeresolution, year, timeframe, and path of data are needed to initialise class. 
    Data is loaded and thermal velocities are calculated automatically.

    important methods :
    getvals([list of keywords],start,stop) returns specified set of data (s. ?swicsiondata.getvals for further information)
    """
    def __init__(self,res,year,timeframe,path):
        self.name="H1+"                            #  str -> name of ion  
        self.time=[]                               #  vector [time]
        self.vel=[]                                #  vector [vel]
        self.velx=[]                                #  vector [vel]
        self.vely=[]                                #  vector [vel]
        self.velz=[]                                #  vector [vel]
        self.dens=[]                               #  vector [dens]
        self.temp=[]                               #  vector [temp]
        self.heh=[]                                #  vector [heh]
        self.vth=[]
        self.path=path                             #  str -> path of data
        self.mass=1.                               #  float -> ion mass
        self.charge=1.                             #  float -> ion charge
        self.res=res                               #  int -> time resolution of magdata in s  
        self.year=year                             #  int -> year of magdata
        self.timeframe=array(timeframe)            #  n x 2 array : [[start1,stop1],....,[startn,stopn]] periods should be arranged by ascending time 
        self.load()
                
    def getvals(self,liste,start=0,stop=-9999):
        """
        Returns array that contains values that are defined in liste
        input :
        liste -> list with keywords e.g. ['time','dens']; Attention ! If liste has only 1 entry output is different s. output.
        start,stop -> set to full lenght by default; (index corresponds to time self.time[index])
                      optional define start and stop index for returned array e.g. start=10,stop=15 returns from index 10 to index 24

        valid keywords for liste are :
        'time' -> time information [doy] 
        'vel' -> velocity [km/s] and corresponding error from countrates
        'dens' -> total density [1/cm^3] 
        'temp' -> temperature [K] 
        'heh' -> alpha to proton ratio
        'vth' -> thermal velocity [km/s]

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
        elif (col=="dens"):
            return self.dens[start:stop]
        elif (col=="temp"):
            return self.temp[start:stop]
        elif (col=="vel"):
            return self.vel[start:stop]
        elif (col=="velx"):
            return self.velx[start:stop]
        elif (col=="vely"):
            return self.vely[start:stop]
        elif (col=="velz"):
            return self.velz[start:stop]
        elif (col=="vth"):
            return self.vth[start:stop]
        elif (col=="heh"):
            return self.heh[start:stop]
        else:
            raise Exception, "Wrong keyword '%s' ! Valid Keywords are 'time','vel','dens','temp','vth','heh'. For more details s. ?swicsiondata.getvals!"%(col) 

    def load(self):
        # format of swepam data file names : resolution[s]+year+.dat
        # e.g. "720s2007.dat" stands for 2007 data in 720s resolution
        inname=self.path+"%i"%(self.res)+"s"+str(self.year)+".dat"
        print "Reading : ",inname
        swepamdatain=open(inname)
        s=swepamdatain.readline()
        k=s.split()
        # fast-forward header
        while (k[0]!="BEGIN" or k[1]!="DATA"):
            s=swepamdatain.readline()
            k=s.split()
            if (len(k)<2):
                k=["*","*"]
        # start reading data
        s=swepamdatain.readline()
        k=s.split()
        for i in range(len(self.timeframe)):
            while (float(k[1])<self.timeframe[i,0]):
                s=swepamdatain.readline()
                k=s.split()
            self.time.append(float(k[1]))
            if (float(k[5])>-999.):
                self.vel.append(float(k[5]))
            else:
                self.vel.append(0.)
            if (float(k[2])>-999.):
                self.dens.append(float(k[2]))
            else:
                self.dens.append(0.)
            if (float(k[3])>-999.):
                self.temp.append(float(k[3]))
            else:
                self.temp.append(0.)
            if (float(k[4])>-999.):
                self.heh.append(float(k[4]))
            else:
                self.heh.append(0.)
            if (float(k[6])>-999.):
                self.velx.append(-float(k[6]))
            else:
                self.velx.append(0.)
            if (float(k[7])>-999.):
                self.vely.append(-float(k[7]))
            else:
                self.vely.append(0.)
            if (float(k[8])>-999.):
                self.velz.append(-float(k[8]))
            else:
                self.velz.append(0.)
            while (float(k[1])<self.timeframe[i,1]):
                s=swepamdatain.readline()
                k=s.split()
                self.time.append(float(k[1]))
                if (float(k[5])>-999.):
                    self.vel.append(float(k[5]))
                else:
                    self.vel.append(0.)
                if (float(k[6])>-999.):
                    self.velx.append(-float(k[6]))
                else:
                    self.velx.append(0.)
                if (float(k[7])>-999.):
                    self.vely.append(-float(k[7]))
                else:
                    self.vely.append(0.)
                if (float(k[8])>-999.):
                    self.velz.append(-float(k[8]))
                else:
                    self.velz.append(0.)
                if (float(k[2])>-999.):
                    self.dens.append(float(k[2]))
                else:
                    self.dens.append(0.)
                if (float(k[3])>-999.):
                    self.temp.append(float(k[3]))
                else:
                    self.temp.append(0.)
                if (float(k[4])>-999.):
                    self.heh.append(float(k[4]))
                else:
                    self.heh.append(0.)
        swepamdatain.close()
        self.time=array(self.time)
        self.vel=array(self.vel)
        self.velx=array(self.velx)
        self.vely=array(self.vely)
        self.velz=array(self.velz)
        self.dens=array(self.dens)
        self.temp=array(self.temp)
        self.heh=array(self.heh)
        self.calc_vth()
        print "SWEPAM-data loaded"
            
    def calc_vth(self):
        "Calculates thermal velocities from temperatures"
        self.vth=[]
        kb = 1.38065e-23
        u = 1.660538e-27
        for i in range(len(self.temp)):
            tmp=(self.temp[i]*kb)/(self.mass*u)
            if tmp>0.:
                self.vth.append(sqrt(tmp)/1000.)
            else:
                self.vth.append(0.)
        self.vth=array(self.vth)

    def sync_h(self,iondata):
        "Syncronizes SWEPAM to SWICS data! \n swepam -> class swepamdata \n iondata -> class swicsiondata \n output is up to now not of class swepamdata! Should be changed asap ..."
        print "synchronizing SWEPAM to SWICS data"
        offset=(self.res/2.)/86400.
        timestep=iondata.res/86400.
        newtime=iondata.getvals(['time'])
        newvel=zeros([len(newtime)])
        newvelx=zeros([len(newtime)])
        newvely=zeros([len(newtime)])
        newvelz=zeros([len(newtime)])
        newdens=zeros([len(newtime)])
        newtemp=zeros([len(newtime)])
        newheh=zeros([len(newtime)])
        newvth=zeros([len(newtime)])
        newdeltavel=zeros([len(newtime)])
        newdeltadens=zeros([len(newtime)])

        j=0
        newstep=-1 # time step in new syncronised data 
        for time in newtime:
            newstep+=1
            while (self.time[j]<time-offset and j<len(self.time)-2):
                j+=1
            Ndens=0.
            Nvel=0.
            Ntemp=0.
            Nheh=0.
            tmpdens=0.
            tmpvel=0.
            tmpvelx=0.
            tmpvely=0.
            tmpvelz=0.
            tmptemp=0.
            tmpheh=0.
            tmpdeltadens=0.
            tmpdeltavel=0.
            tmpvecdens=[]
            tmpvecvelx=[]
            tmpvecvely=[]
            tmpvecvelz=[]

            while (self.time[j]<time+timestep-offset and j<len(self.time)-2):
                if (self.dens[j]>0.):
                    Ndens+=1.
                    tmpdens+=self.dens[j]
                    tmpvecdens.append(self.dens[j])
                if (self.vel[j]>0.):
                    Nvel+=1.
                    tmpvel+=self.vel[j]
                    tmpvelx+=self.velx[j]
                    tmpvely+=self.vely[j]
                    tmpvelz+=self.velz[j]
                    tmpvecvelx.append(self.velx[j])
                    tmpvecvely.append(self.vely[j])
                    tmpvecvelz.append(self.velz[j])
                if (self.temp[j]>0.):
                    Ntemp+=1.
                    tmptemp+=self.temp[j]
                if (self.heh[j]>0.):
                    Nheh+=1.
                    tmpheh+=self.heh[j]
                j+=1
            if (Ndens>0.):
                tmpdens=tmpdens/Ndens
            if (Nvel>0.):
                tmpvel=tmpvel/Nvel
                tmpvelx=tmpvelx/Nvel
                tmpvely=tmpvely/Nvel
                tmpvelz=tmpvelz/Nvel
            if (Ntemp>0.):
                tmptemp=tmptemp/Ntemp
            if (Nheh>0.):
                tmpheh=tmpheh/Nheh
            if Ndens>0.:
                tmpdeltadens=0.
                for i in range(int(Ndens)-1):
                    tmpdens2=abs(tmpvecdens[i]-tmpvecdens[i+1])/tmpdens
                    tmpdeltadens=max(abs(tmpdeltadens),abs(tmpdens2))
            if Nvel>0.:
                tmpdeltavel=0.
                for i in range(int(Nvel)-1):
                    tmpdelta=sqrt((tmpvecvelx[i]-tmpvecvelx[i+1])**2+(tmpvecvely[i]-tmpvecvely[i+1])**2+(tmpvecvelz[i]-tmpvecvelz[i+1])**2)
                    tmpdeltavel=max(abs(tmpdeltavel),abs(tmpdelta))
                    """
                    for k in range(Nvel-1-i):
                        tmpdelta=sqrt((tmpvecvelx[i]-tmpvecvelx[i+k+1])**2+(tmpvecvely[i]-tmpvecvely[i+k+1])**2+(tmpvecvelz[i]-tmpvecvelz[i+k+1])**2)
                        tmpdeltavel=max(tmpdeltavel,tmpdelta)
                    """
            newdeltadens[newstep]=tmpdeltadens
            newdeltavel[newstep]=tmpdeltavel
            newvel[newstep]=tmpvel
            newvelx[newstep]=tmpvelx
            newvely[newstep]=tmpvely
            newvelz[newstep]=tmpvelz
            newdens[newstep]=tmpdens
            newtemp[newstep]=tmptemp
            newheh[newstep]=tmpheh
        self.time=newtime
        self.temp=newtemp
        self.vel=newvel
        self.velx=newvelx
        self.vely=newvely
        self.velz=newvelz
        self.dens=newdens
        self.heh=newheh
        self.dvel=newdeltavel
        self.ddens=newdeltadens
        self.calc_vth()
        print "done"


    def sync_h_hires(self,iondata):
        "Syncronizes SWEPAM to SWICS data in high time resolution!\n The real time resolution of SWICS is not 12 minutes but the fraction of a 12 minutes period in which the bulk of the VDF is measured.\n This means for each ion the syncronisation must be done separately!\n swepam -> class swepamdata \n iondata -> class swicsiondata \n output is up to now not of class swepamdata! Should be changed asap ..."
        print "synchronizing SWEPAM to SWICS data"
        offset=(self.res/2.)/86400.
        timestep=iondata.res/86400.
        newtime=iondata.getvals(['time'])
        newrealtime=zeros([len(newtime)])
        newvel=zeros([len(newtime)])
        newvelx=zeros([len(newtime)])
        newvely=zeros([len(newtime)])
        newvelz=zeros([len(newtime)])
        newdens=zeros([len(newtime)])
        newtemp=zeros([len(newtime)])
        newheh=zeros([len(newtime)])
        newvth=zeros([len(newtime)])
        newdeltavel=zeros([len(newtime)])
        newdeltadens=zeros([len(newtime)])

        j=0
        newstep=-1 # time step in new syncronised data 
        for time in newtime:
            newstep+=1
            # search ESA step of bulk velocity
            k=0
            while iondata.vel[newstep]<=iondata.countspec[newstep][k][0] and k<57:
                k+=1
            tmpnewtime=time+float(k)*12./86400.
            newrealtime[newstep]=tmpnewtime
               
            while (self.time[j]+offset<tmpnewtime-offset and j<len(self.time)-2):
                j+=1
            fac1=((self.time[j]+offset)-(tmpnewtime-offset))/(self.res/86400.)
            fac2=((tmpnewtime+offset)-(self.time[j+1]-offset))/(self.res/86400.)
            #fac1*=1./(fac1+fac2)
            #fac2*=1./(fac1+fac2)
            fac2=1.
            fac1=0.
            tmpdens=fac1*self.dens[j]+fac2*self.dens[j+1]
            tmpvel=fac1*self.vel[j]+fac2*self.vel[j+1]
            tmpvelx=fac1*self.velx[j]+fac2*self.velx[j+1]
            tmpvely=fac1*self.vely[j]+fac2*self.vely[j+1]
            tmpvelz=fac1*self.velz[j]+fac2*self.velz[j+1]
            tmptemp=fac1*self.temp[j]+fac2*self.temp[j+1]
            tmpvel=sqrt(tmpvelx**2+tmpvely**2+tmpvelz**2)
            tmpheh=fac1*self.heh[j]+fac2*self.heh[j+1]

            if (j>0 and self.velx[j]>0.):
                tmpdeltavel=max(sqrt((self.velx[j]-self.velx[j+1])**2+(self.vely[j]-self.vely[j+1])**2+(self.velz[j-1]-self.velz[j])**2),sqrt((self.velx[j-1]-self.velx[j])**2+(self.vely[j-1]-self.vely[j])**2+(self.velz[j-1]-self.velz[j])**2))
            elif (j==0 and self.velx[j]>0.):
                tmpdeltavel=sqrt((self.velx[j]-self.velx[j+1])**2+(self.velz[j]-self.velz[j+1])**2+(self.velz[j]-self.velz[j+1])**2)
            else:
                tmpdeltavel=0.
            if (j>0 and self.dens[j]>0.):
                tmpdeltadens=max(abs(self.dens[j]-self.dens[j+1])/self.dens[j],abs(self.dens[j-1]-self.dens[j])/self.dens[j])
            elif (j==0 and self.velx[j]>0.):
                tmpdeltadens=abs(self.dens[j]-self.dens[j+1])/self.dens[j]
            else:
                tmpdeltadens=0.

            newdeltadens[newstep]=tmpdeltadens
            newdeltavel[newstep]=tmpdeltavel
            newvel[newstep]=tmpvel
            newvelx[newstep]=tmpvelx
            newvely[newstep]=tmpvely
            newvelz[newstep]=tmpvelz
            newdens[newstep]=tmpdens
            newtemp[newstep]=tmptemp
            newheh[newstep]=tmpheh
        self.time=newtime
        self.realtime=newrealtime
        self.temp=newtemp
        self.vel=newvel
        self.velx=newvelx
        self.vely=newvely
        self.velz=newvelz
        self.dens=newdens
        self.heh=newheh
        self.dvel=newdeltavel
        self.ddens=newdeltadens
        self.calc_vth()
        print "done"
