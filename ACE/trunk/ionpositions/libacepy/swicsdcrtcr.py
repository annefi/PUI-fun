from numpy import array,loadtxt


class swicsdcrtcr(object):
    """
    to be done
    """
    def __init__(self,ionname,year,timeframe,path):
        self.name=ionname                            #  str -> name of ion  
        self.year=year                               #  year of data
        self.timeframe=array(timeframe)              #  period -> [[t0,t1],..[tn-1,tn]]
        self.path=path

        self.time=[]
        self.vsw=[]
        self.velspec=[]
        self.dcrspec=[]
        self.tcrspec=[]
        self.aspang=[]
        self.load()
    def load(self):
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1])+1):
                ergdaypath=self.path+"%.4i/"%(self.year)+"%.3i/"%(day)
                # look if data for doy is present!
                lpresent=0
                try:
                    open(ergdaypath+"list.in")
                    lpresent=1
                except:
                    print "doy %.3i no list.in"%(day)
                if (lpresent==1):
                    listin=open(ergdaypath+"list.in")
                    s=listin.readline()
                    for s in listin:
                        k=s.split()
                        time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.))
                        if (time>=tf[0] and time<=tf[1]):
                            dataname=ergdaypath+"%s_"%(self.name)+k[0]
                            fpresent=1
                            try:
                                open(dataname)
                            except:
                                print "Could not open : ",dataname
                                fpresent=0
                            if (fpresent):
                                # first try to read in data in tmpvariables
                                try:
                                    tmptime=time
                                    # get aspect angle and SWS speed (SWICS protons) from erg_* file
                                    datain=open(dataname)
                                    k=["**"]
                                    while (k[0]!="*****"):
                                        s=datain.readline()
                                        k=s.split()
                                        if k[0]=="Aspang":
                                            tmpasp=float(k[2])
                                        if k[0]=="SWSpeed":
                                            tmpvsw=float(k[2])
                                    data=loadtxt(datain,skiprows=1)
                                    datain.close()
                                    #print data
                                    if len(data)==58:
                                        self.time.append(tmptime)
                                        self.aspang.append(tmpasp)
                                        self.vsw.append(tmpvsw)
                                        if len(self.velspec)==0:
                                            self.velspec=data[:,0]
                                        self.dcrspec.append(data[:,2])
                                        self.tcrspec.append(data[:,3])
                                except:
                                    print "Data from %s incomplete or contains bad values"%(dataname)

        self.time=array(self.time)
        self.velspec=array(self.velspec)
        self.dcrspec=array(self.dcrspec)
        self.tcrspec=array(self.tcrspec)
        self.aspang=array(self.aspang)
        self.vsw=array(self.vsw)
        print self.name+" loaded"
