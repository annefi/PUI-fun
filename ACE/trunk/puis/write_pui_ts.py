from numpy import loadtxt,array,arange,zeros,histogram,linspace,amax,mean,sqrt,arccos,cos,pi,savetxt,isnan
from libacepy.mag import magdata
from libacepy.swepamdata import swepamdata
from Gnuplot import Gnuplot,Data

path="/data/etph/ace/pui/12mdata/"
swepampath="/data/etph/ace/swepam/"
magpath="/data/wimmer/ace/mag/"
years=[2006,2007,2008,2009,2010]
doys=[365,365,366,365,365]
#years=[2006,2007,2008,2010]
#doys=[365,365,366,365]
#years=[2006]
#doys=[365]
#years=[2001]
#doys=[50]
start=1
stop=365


def read_pui(filename):
    datain=open(filename,"r")
    k=[""]
    while k[0]!="*****":
        s=datain.readline()
        k=s.split()
        if k[0]=="SWSpeed":
            vsw=float(k[2])
        if k[0]=="DoY":
            time=float(k[2])
    datain.readline()
    data=loadtxt(datain)
    return data,time,vsw


yeararr=[]
time=[]
hedata=[]
vswarr=[]
magb=[]
magtheta=[]

ycount=0

for year in years:
    print year
    for doy in range(start,doys[ycount]+1):
        try:
            listin=open(path+"%.4i/%.3i/list.in"%(year,doy),"r")
            magdoy=magdata(1.,year,[[doy,doy+0.999999]],magpath)
            swepamdoy=swepamdata(64.,year,[[doy,doy+0.999999]],swepampath)
            for s in listin:
                k=s.split()
                tmpdat,tmptime,tmpvsw=read_pui(path+"%.4i/%.3i/He1+_%s"%(year,doy,k[0]))
                vswepam=mean(swepamdoy.vel[(swepamdoy.time>tmptime)*(swepamdoy.time<tmptime+12./1440.)*(swepamdoy.vel>0.)])
                v=tmpdat[:,0]
                w=v/vswepam
                #w=tmpdat[:,1]
                if vswepam>0.:
                    dcr=tmpdat[:,2]
                    tcr=tmpdat[:,3]
                    counts=sum(dcr[(w>1.5)*(w<2.)])+sum(tcr[(w>1.5)*(w<2.)])
                    mag=mean(magdoy.magb[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])
                    #magphi=mean(magdoy.phi[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])
                    #magtheta=mean(magdoy.theta[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])
                    #magang=mean(arccos(cos(magphi)*cos(magtheta)))
                    magang=mean(arccos(cos(magdoy.phi[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])*cos(magdoy.theta[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])))

                    #print year,tmptime,counts,tmpvsw,mag,magang
                    yeararr.append(year)
                    time.append(tmptime)
                    hedata.append(counts)
                    vswarr.append(vswepam)
                    magb.append(mag)
                    magtheta.append(magang)
        except:
            print "No Data for DoY ",doy
    ycount+=1


yeararr=array(yeararr)
time=array(time)
hedata=array(hedata)
vswarr=array(vswarr)
magb=array(magb)
magtheta=array(magtheta)
yeararr[isnan(yeararr)]=0.
time[isnan(time)]=0.
hedata[isnan(hedata)]=0.
vswarr[isnan(vswarr)]=0.
magb[isnan(magb)]=0.
magtheta[isnan(magtheta)]=0.
if len(yeararr)==len(time)==len(hedata)==len(vswarr)==len(magb)==len(magtheta):
    masterarr=zeros([len(time),6])
    masterarr[:,0]=yeararr
    masterarr[:,1]=time
    masterarr[:,2]=hedata
    masterarr[:,3]=vswarr
    masterarr[:,4]=magb
    masterarr[:,5]=magtheta
    outfile=open("/data/etph/ace/tmp/hepswepam.dat","w")
    outfile.write("year\tdoy\t\tcts\tvsw\tB\ttheta\n")
    savetxt(outfile,masterarr,fmt="%.4i\t%f\t%.1f\t%.2f\t%.2f\t%.4f")
    outfile.close()
