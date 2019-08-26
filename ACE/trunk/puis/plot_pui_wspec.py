from numpy import loadtxt,array,arange,zeros,histogram,linspace,amax,mean,sqrt,arccos,cos,pi
from libacepy.swepamdata import swepamdata
from libacepy.mag import magdata
from libacepy.fluxes import getvelocity
from Gnuplot import Gnuplot,Data

path="/data/etph/ace/pui/12mdata/"
swepampath="/data/etph/ace/swepam/"
magpath="/data/wimmer/ace/mag/"
swepampath="/data/etph/ace/swepam/"
years=[2006,2007,2008,2009,2010]
doys=[365,365,366,365,365]
#years=[2006,2007,2008,2010]
#doys=[365,365,366,365]
#years=[2006]
#doys=[365]
start=100
stop=150


def getinstrcorr(v):
    # Mus efficiencies + 0.15. reproduces mean countrates well
    corrarr=array([[ 200.0 , 5.49043483295 ],[ 225.0 , 5.67983733619 ],[ 250.0 , 5.68227155074 ],[ 275.0 , 5.56193846422 ],[ 300.0 , 5.8442144413 ],[ 325.0 , 5.37170390505 ],[ 350.0 , 5.51616229145 ],[ 375.0 , 5.48969782001 ],[ 400.0 , 6.15855302221 ],[ 425.0 , 6.09834530612 ],[ 450.0 , 5.8778300313 ],[ 475.0 , 6.37243586564 ],[ 500.0 , 5.39150817977 ],[ 525.0 , 5.22520842997 ],[ 550.0 , 5.10068013994 ],[ 575.0 , 4.5366337662 ],[ 600.0 , 3.5623656857 ],[ 625.0 , 3.26938069237 ],[ 650.0 , 3.76627813166 ],[ 675.0 , 3.50477821859 ],[ 700.0 , 3.94211947081 ],[ 725.0 , 3.66596461895 ],[ 750.0 , 4.11088663212 ],[ 775.0 , 3.72749123149 ],[ 800.0 , 4.24417441485 ],[ 825.0 , 3.53773234342 ],[ 850.0 , 4.31035803605 ],[ 875.0 , 4.61747840259 ],[ 900.0 , 4.29183966838 ],[ 925.0 , 4.72521771599 ],[ 950.0 , 4.94615529973 ],[ 975.0 , 4.69948229037 ],[ 1000.0 , 5.0640806196 ]])
    corrarr[:,1]/=2.
    if v>corrarr[-1,0]:
        return corrarr[-1,1]
    if v<corrarr[0,0]:
        return corrarr[0,1]
    # find position of smallest velocity in corrarr greater than v
    i=0
    while corrarr[i,0]<v:
        i+=1
    #linear interpolate and return value
    dx=corrarr[i,0]-corrarr[i-1,0]
    dy=corrarr[i,1]-corrarr[i-1,1]
    m=dy/dx
    x=v-corrarr[i-1,0]
    y0=corrarr[i-1,1]
    return y0+m*x

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

ycount=0
wcarr=[]
magtheta=[]
vswarr=[]
timearr=[]
magarr=[]
for year in years:
    print year
    for doy in range(start,doys[ycount]+1):
    #for doy in range(start,stop+1):#doys[ycount]+1):
        try:
            listin=open(path+"%.4i/%.3i/list.in"%(year,doy),"r")
            hesum=0.
            hesumeff=0.
            hesumeff2=0.
            magdoy=magdata(1.,year,[[doy,doy+0.999999]],magpath)
            swepamdoy=swepamdata(64.,year,[[doy,doy+0.999999]],swepampath)
            for s in listin:
                k=s.split()
                tmpdat,tmptime,tmpvsw=read_pui(path+"%.4i/%.3i/He1+_%s"%(year,doy,k[0]))
                vswepam=mean(swepamdoy.vel[(swepamdoy.time>tmptime)*(swepamdoy.time<tmptime+12./1440.)*(swepamdoy.vel>0.)])
                if vswepam>0.:
                    v=tmpdat[:,0]
                    #w=tmpdat[:,1]
                    w=v/vswepam
                    dcr=tmpdat[:,2]
                    tcr=tmpdat[:,3]
                    mag=mean(magdoy.magb[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)*(magdoy.magb>0.)])
                    magang=mean(arccos(cos(magdoy.phi[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])*cos(magdoy.theta[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])))
                    wcarr.append([w[(w>1.)*(w<2.5)],dcr[(w>1.)*(w<2.5)]+tcr[(w>1.)*(w<2.5)]])
                    magtheta.append(magang)
                    vswarr.append(vswepam)
                    timearr.append(tmptime)
                    magarr.append(mag)
        except:
            print "No Data for DoY ",doy
    ycount+=1

def getwspec(w,c):
    wchist,wxhist=histogram(w,linspace(1.,2.5,16),weights=c)
    return [wchist,wxhist[:-1]]

magtheta=array(magtheta)
vswarr=array(vswarr)

wspecarr=[]
i=0.
for val in wcarr:
    wspecarr.append(getwspec(val[0],val[1]))
    i+=1

wspecarr=array(wspecarr)
timearr=array(timearr)
timemask=(timearr>30.)*(timearr<300.)
velmask=(vswarr>600.)*(vswarr<700.)*timemask
mask1=(magtheta>80.*pi/180.)*(magtheta<100.*pi/180)*velmask
mask2=(magtheta>60.*pi/180.)*(magtheta<80.*pi/180)*velmask
mask3=(magtheta>100.*pi/180.)*(magtheta<120.*pi/180)*velmask
mask4=(magtheta>40.*pi/180.)*(magtheta<60.*pi/180)*velmask
mask5=(magtheta>120.*pi/180.)*(magtheta<140.*pi/180)*velmask
mask6=(magtheta>20.*pi/180.)*(magtheta<40.*pi/180)*velmask
mask7=(magtheta>140.*pi/180.)*(magtheta<160.*pi/180)*velmask
mask8=(magtheta>0.*pi/180.)*(magtheta<20.*pi/180)*velmask
mask9=(magtheta>160.*pi/180.)*(magtheta<180.*pi/180)*velmask
wxhist=linspace(1.,2.5,16)
wxhist=wxhist[:-1]
wc1hist=sum(wspecarr[mask1][:,0])
wc2hist=sum(wspecarr[mask2][:,0])
wc3hist=sum(wspecarr[mask3][:,0])
wc4hist=sum(wspecarr[mask4][:,0])
wc5hist=sum(wspecarr[mask5][:,0])
wc6hist=sum(wspecarr[mask6][:,0])
wc7hist=sum(wspecarr[mask7][:,0])
wc8hist=sum(wspecarr[mask8][:,0])
wc9hist=sum(wspecarr[mask9][:,0])
wc1hist=wc1hist/float(len(wspecarr[mask1][:,0]))
wc2hist=wc2hist/float(len(wspecarr[mask2][:,0]))
wc3hist=wc3hist/float(len(wspecarr[mask3][:,0]))
wc4hist=wc4hist/float(len(wspecarr[mask4][:,0]))
wc5hist=wc5hist/float(len(wspecarr[mask5][:,0]))
wc6hist=wc6hist/float(len(wspecarr[mask6][:,0]))
wc7hist=wc7hist/float(len(wspecarr[mask7][:,0]))
wc8hist=wc8hist/float(len(wspecarr[mask8][:,0]))
wc9hist=wc9hist/float(len(wspecarr[mask9][:,0]))
#gp4=Gnuplot()
#gp4.plot(Data(wxhist,wc1hist/sum(wc1hist),with_="steps lt 1"),Data(wxhist,(wc2hist+wc3hist)/sum(wc2hist+wc3hist),with_="steps lt 3"),Data(wxhist,wc1hist/sum(wc1hist)-(wc2hist+wc3hist)/sum(wc2hist+wc3hist),with_="steps lt 4"))#,Data(wxhist,wc3hist,with_="steps lt 4"))
gp4.plot(Data(wxhist,(wc1hist/sum(wc1hist)-(wc2hist+wc3hist)/sum(wc2hist+wc3hist))/wc1hist,with_="steps lt 1"),Data(wxhist,(wc1hist/sum(wc1hist)-(wc4hist+wc5hist)/sum(wc4hist+wc5hist))/wc1hist,with_="steps lt 3"),Data(wxhist,(wc1hist/sum(wc1hist)-(wc6hist+wc7hist)/sum(wc6hist+wc7hist))/wc1hist,with_="steps lt 4"),Data(wxhist,(wc1hist/sum(wc1hist)-(wc8hist+wc9hist)/sum(wc8hist+wc9hist))/wc1hist,with_="steps lt 5"),"0 with l lt -1")#,Data(wxhist,wc3hist,with_="steps lt 4"))

