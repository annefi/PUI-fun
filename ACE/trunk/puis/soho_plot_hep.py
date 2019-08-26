from numpy import loadtxt,array,arange,zeros,histogram,linspace,amax,mean,sqrt,arccos,cos,pi
from libacepy.swepamdata import swepamdata
from libacepy.mag import magdata
from libacepy.fluxes import getvelocity
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
start=1
stop=365


def getinstrcorr(v):
    # Mus efficiencies
    #corrarr=array([[ 200.0 , 0.659602784427 ],[ 225.0 , 0.717033372965 ],[ 250.0 , 0.759407533271 ],[ 275.0 , 0.7936388544 ],[ 300.0 , 0.879674085996 ],[ 325.0 , 0.869830678623 ],[ 350.0 , 0.951308820525 ],[ 375.0 , 1.01103162501 ],[ 400.0 , 1.19175759625 ],[ 425.0 , 1.2683953168 ],[ 450.0 , 1.31139259553 ],[ 475.0 , 1.49419271084 ],[ 500.0 , 1.33474635059 ],[ 525.0 , 1.34475716561 ],[ 550.0 , 1.37908345339 ],[ 575.0 , 1.26844494039 ],[ 600.0 , 1.09268326256 ],[ 625.0 , 1.07162790984 ],[ 650.0 , 1.25564733908 ],[ 675.0 , 1.24834720041 ],[ 700.0 , 1.423284788 ],[ 725.0 , 1.40993268454 ],[ 750.0 , 1.60076928594 ],[ 775.0 , 1.53646882007 ],[ 800.0 , 1.77275135693 ],[ 825.0 , 1.54394398124 ],[ 850.0 , 1.91954437436 ],[ 875.0 , 2.06943506871 ],[ 900.0 , 2.02427701213 ],[ 925.0 , 2.24707459741 ],[ 950.0 , 2.36189953798 ],[ 975.0 , 2.3566358586 ],[ 1000.0 , 2.55361392986 ]])
    # Mus efficiencies + 0.15 reproduces mean observations well
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
    #print v,corrarr[i,0],i
    dx=corrarr[i,0]-corrarr[i-1,0]
    dy=corrarr[i,1]-corrarr[i-1,1]
    m=dy/dx
    x=v-corrarr[i-1,0]
    y0=corrarr[i-1,1]
    return y0+m*x

def load_eff(ionname):
    effin=open("/data/etph/ace/efficencies/%s_dcr.eff"%(ionname),"r")
    effin.readline()
    effprob=loadtxt(effin)
    eff=effprob[:,0]*effprob[:,1]*effprob[:,2]
    return eff

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

eff=load_eff("He1+")

hedata=[]
vswarr=[]
hedoydata=zeros([len(years),365,2])
hedoydata[:,:,0]=arange(1,366)
ycount=0
wspecarrl=[]
wspecarrr=[]
vswarrl=[]
vswarrr=[]
corrarr=[]
corrarr2=[]

for year in years:
    print year
    for doy in range(start,doys[ycount]+1):
        try:
            listin=open(path+"%.4i/%.3i/list.in"%(year,doy),"r")
            hesum=0.
            for s in listin:
                k=s.split()
                tmpdat,tmptime,tmpvsw=read_pui(path+"%.4i/%.3i/He1+_%s"%(year,doy,k[0]))
                v=tmpdat[:,0]
                w=tmpdat[:,1]
                dcr=tmpdat[:,2]
                tcr=tmpdat[:,3]
                hedata.append([tmptime,(sum(dcr[(w>1.5)*(w<2.)])+sum(tcr[(w>1.5)*(w<2.)]))])#/corrfac/sqrt(mag)])
                hesum+=sum(dcr[(w>1.5)*(w<2.)])+sum(tcr[(w>1.5)*(w<2.)])
            hedoydata[ycount,doy-1,1]=hesum
        except:
            print "No Data for DoY ",doy
    ycount+=1
hedata=array(hedata)

hetsdata=zeros([len(years)*365+1,2])
hetsdata[:,0]=arange(len(years)*365.+1.)
for i in range(len(years)):
    hetsdata[sum(doys[0:i]):sum(doys[0:i])+365,1]=hedoydata[i,:,1]



herunav=zeros([len(years)*365+1,2])
herunav[:,0]=arange(len(years)*365.+1.)
for i in range(14,len(herunav)-13):
    herunav[i,1]=sum(hetsdata[i-13:i+14,1])/27.


namesem="/data/etph/soho/celias/sem/sem_data.dat"
semin=open(namesem,"r")
semtot=loadtxt(semin)
semdat=zeros([len(years)*365+1,2])
semdat[:,0]=arange(len(years)*365.+1.)
for i in range(len(years)):
    tmpsemdat=semtot[semtot[:,1]==years[i]]
    if (years[i]!=2008):
        semdat[sum(doys[0:i]):sum(doys[0:i])+doys[i],1]=tmpsemdat[:,15]
    else:
        semdat[sum(doys[0:i]):sum(doys[0:i])+doys[i]-2,1]=tmpsemdat[:,15]
semdat2=zeros([len(years)*365+1,2])
semdat2[:,0]=arange(len(years)*365.+1.)
for i in range(len(years)):
    tmpsemdat=semtot[semtot[:,1]==years[i]]
    if (years[i]!=2008):
        semdat2[sum(doys[0:i]):sum(doys[0:i])+doys[i],1]=tmpsemdat[:,14]
    else:
        semdat2[sum(doys[0:i]):sum(doys[0:i])+doys[i]-2,1]=tmpsemdat[:,14]

semdat[:,1]/=1e8
semdat[:,1]*=1.5


gp2=Gnuplot()
gp2("set style data histeps")
gp2("set yrange[0:2000]")
gp2("set xlabel 'Date'")
gp2("set ylabel 'He^{1+} 1.5<w<2.0 / scaled UV-flux'")
gp2("set xtics ('2006' 1,'' 31+1 1,'' 31+28+1 1,'' 31+28+31+1 1,'' 31+28+31+30+1 1,'' 31+28+31+30+31+1 1,'' 31+28+31+30+31+30+1 1,'' 31+28+31+30+31+30+31+1 1,'' 31+28+31+30+31+30+31+31+1 1,'' 31+28+31+30+31+30+31+31+30+1 1,'' 31+28+31+30+31+30+31+31+30+31+1 1,'' 31+28+31+30+31+30+31+31+30+31+30+1 1,'2007' 365+1,'' 365+31+1 1,'' 365+31+28+1 1,'' 365+31+28+31+1 1,'' 365+31+28+31+30+1 1,'' 365+31+28+31+30+31+1 1,'' 365+31+28+31+30+31+30+1 1,'' 365+31+28+31+30+31+30+31+1 1,'' 365+31+28+31+30+31+30+31+31+1 1,'' 365+31+28+31+30+31+30+31+31+30+1 1,'' 365+31+28+31+30+31+30+31+31+30+31+1 1,'' 365+31+28+31+30+31+30+31+31+30+31+30+1 1,'2008' 2*365+1,'' 2*365+31+1 1,'' 2*365+31+29+1 1,'' 2*365+31+29+31+1 1,'' 2*365+31+29+31+30+1 1,'' 2*365+31+29+31+30+31+1 1,'' 2*365+31+29+31+30+31+30+1 1,'' 2*365+31+29+31+30+31+30+31+1 1,'' 2*365+31+29+31+30+31+30+31+31+1 1,'' 2*365+31+29+31+30+31+30+31+31+30+1 1,'' 2*365+31+29+31+30+31+30+31+31+30+31+1 1,'' 2*365+31+29+31+30+31+30+31+31+30+31+30+1 1,'2009' 3*365+2,'' 3*365+31+2 1,'' 3*365+31+28+2 1,'' 3*365+31+28+31+2 1,'' 3*365+31+28+31+30+2 1,'' 3*365+31+28+31+30+31+2 1,'' 3*365+31+28+31+30+31+30+2 1,'' 3*365+31+28+31+30+31+30+31+2 1,'' 3*365+31+28+31+30+31+30+31+31+2 1,'' 3*365+31+28+31+30+31+30+31+31+30+2 1,'' 3*365+31+28+31+30+31+30+31+31+30+31+2 1,'' 3*365+31+28+31+30+31+30+31+31+30+31+30+3 1,'2010' 4*365+2,'' 4*365+31+2 1,'' 4*365+31+28+2 1,'' 4*365+31+28+31+2 1,'' 4*365+31+28+31+30+2 1,'' 4*365+31+28+31+30+31+2 1,'' 4*365+31+28+31+30+31+30+2 1,'' 4*365+31+28+31+30+31+30+31+2 1,'' 4*365+31+28+31+30+31+30+31+31+2 1,'' 4*365+31+28+31+30+31+30+31+31+30+2 1,'' 4*365+31+28+31+30+31+30+31+31+30+31+2 1,'' 4*365+31+28+31+30+31+30+31+31+30+31+30+3 1)")
gp2.plot(Data(hetsdata,title='He^{1+} [cts/day]',with_='histeps lt 1'),Data(herunav,title='He@_{RM}^{1+} (+-13 Days)',with_='l lt 3 lw 3'),Data(semdat,title="SEM UV",with_="l lt 4"))
gp2.hardcopy("He1+_soho.ps",color=True)

