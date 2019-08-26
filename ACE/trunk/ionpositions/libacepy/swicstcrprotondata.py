from libacepy.ancil import int2str
from Gnuplot import Gnuplot,Data
from numpy import array,zeros,mean
from math import sqrt
import sys

class swicstcrprotondata:
    """
    Class for swics iondata. Ionname, timeresolution, year, timeframe, and path of data are needed to initialise class. 
    Data is loaded and some further quantities (e.g. thermal velocities, kortosis ...) are calculated automatically.

    important methods :
    getvals([list of keywords],start,stop) returns specified set of data (s. ?swicsiondata.getvals for further information)
    getspec(keywords,start,stop) returns specified set of data (s. ?swicsiondata.getspec for further information)
    """
    def __init__(self,ionname,res,year,timeframe,path): 
        """
        Input :
        ionname -> str (e.g. 'He2+')
        res -> int,float,or str (valid 720,720.,'12m',3600,3600.,'1h',86400,86400.,'1d')
        year -> int (e.g. 2007)
        timeframe -> list,array (e.g. [[1.,5.],[7.2,9.5],[100.6,150.])
        path -> str (e.g. '/data/wimmer/ace/')
        """
        self.name=ionname                            #  str -> name of ion  
        self.res=self.convres(res)                   #  timeresolution of data in s
        self.year=year                               #  year of data
        self.time=[]                                 #  vector [time]
        self.countspec=[]                            #  vector of [[step][vel,counts,cr-error,+eff-error,-eff-error]]
        self.path=path+self.convresname(res)+"data/"+str(year)+"/" #  str -> path of data repository 
                                                                   # e.g. "/data/wimmer/ace/" resolution and year added from input
        self.mass=1.                                 #  float -> ion mass
        self.charge=1.                               #  float -> ion charge
        self.aspang=[]                               #  vector [aspang]. Aspect angle information
        self.vsws=[]                                 #  vector [vsws]. Proton speed from michigan analysis
        self.timeframe=array(timeframe)              #  vector -> [[start,stop]]
        self.load()

    def getvals(self,liste,start=0,stop=-9999):
        """
        Returns array that contains values that are defined in liste
        input :
        liste -> list with keywords e.g. ['time','dens'] ; Attention ! If liste has only 1 entry output is different s. output
        start,stop -> set to full lenght by default; (index corresponds to time self.time[index])
                      optional define start and stop index for returned array e.g. start=10,stop=15 returns from index 10 to index 24

        valid keywords for liste are :
        'time' -> time information [doy] 
        'vel','velerr' -> velocity [km/s] and corresponding error from countrates
        'dens','denscrerr','densefferr' -> total density [1/cm^3] and corresponding errors from countrates 'cr' and efficiencies 'eff'
        'flux','fluxcrerr','fluxefferr' -> total flux [fix] and corresponding errors from countrates 'cr' and efficiencies 'eff'
        'temp','tempcrerr','tempefferr' -> temperature [K] and corresponding errors from countrates 'cr' and efficiencies 'eff'
        'vth' -> thermal velocity [km/s]
        'crvel' -> velocity [km/s] from raw counts
        'crvth' -> thermal velocity [km/s] from raw counts
        'crdens' -> total density [#/cm^3] from raw counts 
        'crtemp' -> temperature [K] from raw counts

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

    def getspec(self,type,start=0,stop=-9999):
        """
        Returns array that contains spectra from index start to index start+stop-1 (index corresponds to time self.time[index])
        input :
        type -> keyword e.g. 'densspec'
        valid keywords for type are :
        'densspec' -> density spectrum [[start+stop-1][step][vel,diffdens,cr-error,+eff-error,-eff-error]]
        'fluxspec' -> flux spectrum [[start+stop-1][step][vel,diffflux,cr-error,+eff-error,-eff-error]]
        'countspec' -> count spectrum [[start+stop-1][step][vel,counts,cr-error,+eff-error,-eff-error]]
        
        start,stop -> set to full lenght by default; optional define start and stop index for returned array
                      e.g. start=10,stop=15 returns from index 10 to index 24


        output :
        array -> [stop-start,len(liste)] ; first val from liste is first column, ... last val from liste is last column 
        """
        if (stop==-9999):
            stop=len(self.time)-start
        if (type=="densspec"):
            return self.densspec[start:stop]
        elif (type=="fluxspec"):
            return self.fluxspec[start:stop]
        elif (type=="countspec"):
            return self.countspec[start:stop]
        else:
            raise Exception, "Wrong keyword '%s' ! Valid Keywords are 'densspec','fluxspec',countspec'"%(type) 


    def getcol(self,col,start=0,stop=-9999):
        if (stop==-9999):
            stop=len(self.time)-start
        if (col=="time"):
            return self.time[start:stop]
        elif (col=="dens"):
            return self.dens[start:stop,0]
        elif (col=="denscrerr"):
            return self.dens[start:stop,1]
        elif (col=="densefferr"):
            return self.dens[start:stop,2]
        elif (col=="temp"):
            return self.temp[start:stop,0]
        elif (col=="tempcrerr"):
            return self.temp[start:stop,1]
        elif (col=="tempefferr"):
            return self.temp[start:stop,2]
        elif (col=="flux"):
            return self.flux[start:stop,0]
        elif (col=="fluxcrerr"):
            return self.flux[start:stop,1]
        elif (col=="fluxefferr"):
            return self.flux[start:stop,2]
        elif (col=="vel"):
            return self.vel[start:stop]
        elif (col=="velerr"):
            return self.velerr[start:stop]
        elif (col=="vth"):
            return self.vth[start:stop]
        elif (col=="crvel"):
            return self.crvel[start:stop]
        elif (col=="crvth"):
            return self.crvth[start:stop]
        elif (col=="crtemp"):
            return self.crtemp[start:stop]
        elif (col=="crdens"):
            return self.crdens[start:stop]
        elif (col=="skewness"):
            return self.skewness[start:stop]
        elif (col=="kortosis"):
            return self.kortosis[start:stop]
        else:
            raise Exception, "Wrong keyword '%s' ! Valid Keywords are 'time','vel','velerr','dens','denscrerr','densefferr','flux','fluxcrerr','fluxefferr','temp','tempcrerr','tempefferr','vth','crvel','crvth','crdens','crtemp'. For more details s. ?swicsiondata.getvals!"%(col) 
        
    def load(self):
        """
        Loads data from the defined timeframe
        """
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1])+1):
                doystr=int2str(day)
                ergdaypath=self.path+doystr+"/"
                # look if data for doy is present!
                lpresent=0
                try:
                    open(ergdaypath+"list.in")
                    lpresent=1
                except:
                    print "doy ",doystr," no list.in"
                if (lpresent==1):
                    listin=open(ergdaypath+"list.in")
                    s=listin.readline()
                    for s in listin:
                        k=s.split()
                        time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.))
                        if (time>=tf[0] and time<=tf[1]):
                            ergname=ergdaypath+"erg_"+k[0]
                            fpresent=1
                            try:
                                open(ergname)
                            except:
                                print "Could not open : ",ergname
                                fpresent=0
                            if (fpresent):
                                tmptime=-9999.
                                tmptemp=-9999.
                                tmpcountspec=[]
                                tmpasp=-9999.
                                tmpvsws=-9999.
                                # first try to read in data in tmpvariables
                                try:
                                    tmptime=time
                                    ergin=open(ergname)
                                    k=["**"]
                                    while (k[0]!="*****"):
                                        s=ergin.readline()
                                        k=s.split()
                                        if k[0]=="Aspang":
                                            tmpasp=float(k[2])
                                        if k[0]=="SWSpeed":
                                            tmpvsws=float(k[2])
                                    tmpstep=0
                                    tmpcountspec=[]
                                    # protons bis step 22 !
                                    while (tmpstep<22):
                                        s=ergin.readline()
                                        k=s.split()
                                        if (k[0]==self.name):
                                            tmpcountspec.append([float(k[7]),float(k[11])])
                                            tmpstep+=1
                                    ergin.close()
                                    if (tmptime<-999. or len(tmpcountspec)<2):
                                        raise Exception
                                    self.time.append(tmptime)
                                    self.countspec.append(array(tmpcountspec))
                                    self.aspang.append(tmpasp)
                                    self.vsws.append(tmpvsws)
                                except:
                                    print "Data from ",ergname," incomplete or contains bad values"

        self.time=array(self.time)
        self.countspec=array(self.countspec)
        print self.name+" loaded"

    def bindata(self,fac):
        newtime=[]
        newcountspec=[]
        newvsw=[]
        newaspang=[]
        for i in range(len(self.time)/int(fac)):
            newtime.append(self.time[i*fac])
            tmpcountspec=self.countspec[i*fac]
            for j in range(fac-1):
                tmpcountspec[:,1]+=self.countspec[i*fac+1+j][:,1]
            newcountspec.append(tmpcountspec)
            newvsw.append(mean(self.vsws[i*fac:(i+1)*fac]))
            newaspang.append(mean(self.aspang[i*fac:(i+1)*fac]))
        self.countspec=newcountspec
        self.time=newtime
        self.vsws=newvsw
        self.aspang=newaspang
        self.res=self.res*fac
        
    def convres(self,res):
        """
        Converts resolution input in time in s. Valid values are '12m','1h','1d',720,3600,86400 -> output is 720.,3600.,or 86400.
        """
        try:
            if (str(res)=="12m"):
                return 720.
            elif (str(res)=="1h"):
                return 3600.
            elif (str(res)=="1d"):
                return 86400.
            elif (float(res)==720.):
                return 720.
            elif (float(res)==3600.):
                return 3600.
            elif (float(res)==86400.):
                return 86400.
            else:
                raise Exception
        except:
            raise Exception, "Wrong resolution! Possible values are '12m','1h','1d',720,3600,86400"
            
    def convresname(self,res):
        """
        Converts resolution input in time in string. Valid values are '12m','1h','1d',720,3600,86400 -> output is '12m','1h',or '1d'
        """
        try:
            if (str(res)=="12m"):
                return "12m"
            elif (str(res)=="1h"):
                return "1h"
            elif (str(res)=="1d"):
                return "1d"
            elif (float(res)==720.):
                return "12m"
            elif (float(res)==3600.):
                return "1h"
            elif (float(res)==86400.):
                return "1d"
            else:
                raise Exception
        except:
            raise Exception, "Wrong resolution! Possible values are '12m','1h','1d',720,3600,86400"


