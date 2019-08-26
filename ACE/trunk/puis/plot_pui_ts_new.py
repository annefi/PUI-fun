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

hedata=[]
vswarr=[]
hedoydata=zeros([len(years),365,2])
hedoydata[:,:,0]=arange(1,366)
magdoydata=zeros([len(years),365,2])
magdoydata[:,:,0]=arange(1,366)
magphidoydata=zeros([len(years),365,2])
magphidoydata[:,:,0]=arange(1,366)
magangdoydata=zeros([len(years),365,2])
magangdoydata[:,:,0]=arange(1,366)
magthetadoydata=zeros([len(years),365,2])
magthetadoydata[:,:,0]=arange(1,366)
hedoydataeff=zeros([len(years),365,2])
hedoydataeff[:,:,0]=arange(1,366)
hedoydataeff2=zeros([len(years),365,2])
hedoydataeff2[:,:,0]=arange(1,366)
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
    #for doy in range(start,stop+1):#doys[ycount]+1):
        try:
            listin=open(path+"%.4i/%.3i/list.in"%(year,doy),"r")
            hesum=0.
            hesumeff=0.
            hesumeff2=0.
            magsum=0.
            magangsum=0.
            magphisum=0.
            magthetasum=0.
            magdoy=magdata(1.,year,[[doy,doy+0.999999]],magpath)
            nr=0.
            for s in listin:
                k=s.split()
                tmpdat,tmptime,tmpvsw=read_pui(path+"%.4i/%.3i/He1+_%s"%(year,doy,k[0]))
                v=tmpdat[:,0]
                w=tmpdat[:,1]
                dcr=tmpdat[:,2]
                tcr=tmpdat[:,3]
                mag=mean(magdoy.magb[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])
                magphi=mean(magdoy.phi[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])
                magtheta=mean(magdoy.theta[(magdoy.time>tmptime)*(magdoy.time<tmptime+12./1440.)])
                magang=arccos(cos(magphi)*cos(magtheta))
                corrfac=getinstrcorr(tmpvsw)
                hedata.append([tmptime,(sum(dcr[(w>1.5)*(w<2.)])+sum(tcr[(w>1.5)*(w<2.)]))])#/corrfac/sqrt(mag)])
                corrarr.append([tmptime,mag])
                corrarr2.append([tmpvsw,(sum(dcr[(w>1.5)*(w<2.)])+sum(tcr[(w>1.5)*(w<2.)])),mag,corrfac])
                hesum+=sum(dcr[(w>1.5)*(w<2.)])+sum(tcr[(w>1.5)*(w<2.)])
                hesumeff+=(sum(dcr[(w>1.5)*(w<2.)])+sum(tcr[(w>1.5)*(w<2.)]))/corrfac
                hesumeff2+=(sum(dcr[(w>1.5)*(w<2.)])+sum(tcr[(w>1.5)*(w<2.)]))/corrfac/mag
                magsum+=mag
                magangsum+=magang
                magphisum+=magphi
                magthetasum+=magtheta
                nr+=1.
                if (tmpvsw>300. and tmpvsw<350.):
                #if (magang>0.*pi/180. and magang<20*pi/180.) or (magang>160.*pi/180. and magang<180.*pi/180):
                    wspecarrl.append([w[(w>1.5)*(w<2.5)],dcr[(w>1.5)*(w<2.5)]+tcr[(w>1.5)*(w<2.5)]])
                    vswarrl.append(tmpvsw)
                #if magang>70.*pi/180. and magang<110*pi/180.:
                if (tmpvsw>600. and tmpvsw<650.):
                    wspecarrr.append([w[(w>1.5)*(w<2.5)],dcr[(w>1.5)*(w<2.5)]+tcr[(w>1.5)*(w<2.5)]])
                    vswarrr.append(tmpvsw)
            if nr>0.:
                hedoydata[ycount,doy-1,1]=hesum/nr
                magdoydata[ycount,doy-1,1]=magsum/nr
                magphidoydata[ycount,doy-1,1]=magphisum/nr
                magthetadoydata[ycount,doy-1,1]=magthetasum/nr
                magangdoydata[ycount,doy-1,1]=magangsum/nr
                hedoydataeff[ycount,doy-1,1]=hesumeff/nr
                hedoydataeff2[ycount,doy-1,1]=hesumeff2/nr
        except:
            print "No Data for DoY ",doy
    ycount+=1
hedata=array(hedata)
corrarr=array(corrarr)
corrarr2=array(corrarr2)


histvswcounts,vswbins=histogram(corrarr2[:,0],linspace(200,1000,41),weights=corrarr2[:,1])
histvswmag,vswbins=histogram(corrarr2[:,0],linspace(200,1000,41),weights=corrarr2[:,2])
histvswcorrfac,vswbins=histogram(corrarr2[:,0],linspace(200,1000,41),weights=corrarr2[:,3])
normvswcounts,x=histogram(corrarr2[:,0],linspace(200,1000,41))
histvswcounts/=normvswcounts
histvswmag/=normvswcounts
histvswcorrfac/=normvswcounts
vswbins=vswbins[:-1]
gp6=Gnuplot()
gp6.plot(Data(vswbins[histvswcounts>0.],histvswcounts[histvswcounts>0.],with_="steps lt 1"),Data(vswbins[histvswmag>0.],histvswmag[histvswmag>0.],with_="steps lt 3"),Data(vswbins[histvswcorrfac>0.],histvswcorrfac[histvswcorrfac>0.],with_="steps lt 4"),Data(vswbins[histvswcorrfac>0.],histvswcorrfac[histvswcorrfac>0.]*histvswmag[histvswcorrfac>0.],with_="steps lt 5"))
gp5=Gnuplot()
#gp5.plot(Data(vswbins[histvswcorrfac>0.],histvswcounts[histvswcorrfac>0.]/histvswcorrfac[histvswcorrfac>0.]*histvswmag[histvswcorrfac>0.],with_="steps lt 3"))
gp5.plot(Data(vswbins[histvswcorrfac>0.],histvswcounts[histvswcorrfac>0.]/histvswcorrfac[histvswcorrfac>0.],with_="steps lt 3"))

# Build w histograms
steps=10
histl=zeros([steps,2])
histr=zeros([steps,2])
stepw=1./float(steps)
histl[:,0]=linspace(1.5+stepw/2.,2.5-stepw/2.,steps)
histr[:,0]=linspace(1.5+stepw/2.,2.5-stepw/2.,steps)
for val in wspecarrl:
    for j in range(len(val[0])):
        for i in range(steps):
            if val[0][j]-(1.5+float(i)*stepw)>=0. and val[0][j]-(1.5+float(i)*stepw)<stepw:
                histl[i,1]+=val[1][j]

vswhistl,vswxl=histogram(vswarrl,linspace(200,1000,41))
vswhistr,vswxr=histogram(vswarrr,linspace(200,1000,41))
vswxl=vswxl[:-1]+0.5*(vswxl[1]-vswxl[0])
vswxr=vswxr[:-1]+0.5*(vswxr[1]-vswxr[0])

for val in wspecarrr:
    for j in range(len(val[0])):
        for i in range(steps):
            if val[0][j]-(1.5+float(i)*stepw)>=0. and val[0][j]-(1.5+float(i)*stepw)<stepw:
                histr[i,1]+=val[1][j]

histl[:,1]/=amax(histl[:,1])
histr[:,1]/=amax(histr[:,1])

gp4=Gnuplot()
gp4.plot(Data(histl,with_="histeps"),Data(histr,with_="histeps"))
gp5=Gnuplot()
gp5.plot(Data(vswxl,vswhistl,with_="histeps"),Data(vswxr,vswhistr,with_="histeps"))

hetsdata=zeros([len(years)*365+1,2])
hetsdata[:,0]=arange(len(years)*365.+1.)
for i in range(len(years)):
    hetsdata[sum(doys[0:i]):sum(doys[0:i])+365,1]=hedoydata[i,:,1]

hetsdataeff=zeros([len(years)*365+1,2])
hetsdataeff[:,0]=arange(len(years)*365.+1.)
for i in range(len(years)):
    hetsdataeff[sum(doys[0:i]):sum(doys[0:i])+365,1]=hedoydataeff[i,:,1]

hetsdataeff2=zeros([len(years)*365+1,2])
hetsdataeff2[:,0]=arange(len(years)*365.+1.)
for i in range(len(years)):
    hetsdataeff2[sum(doys[0:i]):sum(doys[0:i])+365,1]=hedoydataeff2[i,:,1]

hesumdata=hedoydata[0]
for i in range(1,len(hedoydata)):
    hesumdata[:,1]+=hedoydata[i,:,1]

herunavsum=zeros([366,2])
herunavsum[:,0]=arange(366.)
for i in range(14,len(herunavsum)-13):
    herunavsum[i,1]=sum(hesumdata[i-13:i+14,1])/27.

herunav=zeros([len(years)*365+1,2])
herunav[:,0]=arange(len(years)*365.+1.)
for i in range(14,len(herunav)-13):
    herunav[i,1]=sum(hetsdata[i-13:i+14,1])/27.

herunaveff=zeros([len(years)*365+1,2])
herunaveff[:,0]=arange(len(years)*365.+1.)
for i in range(14,len(herunaveff)-13):
    herunaveff[i,1]=sum(hetsdataeff[i-13:i+14,1])/27.

herunaveff2=zeros([len(years)*365+1,2])
herunaveff2[:,0]=arange(len(years)*365.+1.)
for i in range(14,len(herunaveff2)-13):
    herunaveff2[i,1]=sum(hetsdataeff2[i-13:i+14,1])/27.

hecardata=zeros([len(years),73,2])
for year in range(len(years)):
    for i in range(73):
        nr=0.
        tmpsum=0.
        for j in range(5):
            if hedoydata[year,i*5+j,1]>0.:
                nr+=1.
            tmpsum+=hedoydata[year,i*5+j,1]
        hecardata[year,i,0]=float(i)*5.+2.5
        if nr>0.:
            hecardata[year,i,1]=tmpsum/nr

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

gp7=Gnuplot()
gp7.plot(Data(hedata,with_="p lt 1"),Data(corrarr,with_="p lt 3"),Data(semdat,with_="l lt 4"))
gp7.plot(Data(hedata,with_="p lt 1"),Data(corrarr,with_="p lt 3"),Data(hedoydata[0,:,0]+0.5,hedoydata[0,:,1],with_="histeps lt 4"))#,Data(semdat,with_="l lt 4"))
gp8=Gnuplot()
gp8.plot(Data(hedoydata[0,:,0]+0.5,hedoydata[0,:,1],with_="histeps lt 1"),Data(magdoydata[0,:,0]+0.5,magdoydata[0,:,1],with_="histeps lt 3"),Data(magangdoydata[0,:,0]+0.5,magangdoydata[0,:,1],with_="histeps lt 4"))

gp=Gnuplot()
gp("set style data histeps")
#gp("set yrange[0:2000]")
gp.plot(Data(hesumdata,with_="histeps lt 1"),Data(herunavsum,with_="histeps lt 3"))


gp2=Gnuplot()
gp2("set style data histeps")
#gp2("set yrange[0:2000]")
gp2("set xlabel 'Days since 01.01.2001'")
gp2("set xlabel 'Date'")
gp2("set ylabel 'Counts/Day (He^{1+} 1.5<w<2.)'")
gp2("set xtics ('2006' 1,'' 31+1 1,'' 31+28+1 1,'' 31+28+31+1 1,'' 31+28+31+30+1 1,'' 31+28+31+30+31+1 1,'' 31+28+31+30+31+30+1 1,'' 31+28+31+30+31+30+31+1 1,'' 31+28+31+30+31+30+31+31+1 1,'' 31+28+31+30+31+30+31+31+30+1 1,'' 31+28+31+30+31+30+31+31+30+31+1 1,'' 31+28+31+30+31+30+31+31+30+31+30+1 1,'2007' 365+1,'' 365+31+1 1,'' 365+31+28+1 1,'' 365+31+28+31+1 1,'' 365+31+28+31+30+1 1,'' 365+31+28+31+30+31+1 1,'' 365+31+28+31+30+31+30+1 1,'' 365+31+28+31+30+31+30+31+1 1,'' 365+31+28+31+30+31+30+31+31+1 1,'' 365+31+28+31+30+31+30+31+31+30+1 1,'' 365+31+28+31+30+31+30+31+31+30+31+1 1,'' 365+31+28+31+30+31+30+31+31+30+31+30+1 1,'2008' 2*365+1,'' 2*365+31+1 1,'' 2*365+31+29+1 1,'' 2*365+31+29+31+1 1,'' 2*365+31+29+31+30+1 1,'' 2*365+31+29+31+30+31+1 1,'' 2*365+31+29+31+30+31+30+1 1,'' 2*365+31+29+31+30+31+30+31+1 1,'' 2*365+31+29+31+30+31+30+31+31+1 1,'' 2*365+31+29+31+30+31+30+31+31+30+1 1,'' 2*365+31+29+31+30+31+30+31+31+30+31+1 1,'' 2*365+31+29+31+30+31+30+31+31+30+31+30+1 1,'2009' 3*365+2,'' 3*365+31+2 1,'' 3*365+31+28+2 1,'' 3*365+31+28+31+2 1,'' 3*365+31+28+31+30+2 1,'' 3*365+31+28+31+30+31+2 1,'' 3*365+31+28+31+30+31+30+2 1,'' 3*365+31+28+31+30+31+30+31+2 1,'' 3*365+31+28+31+30+31+30+31+31+2 1,'' 3*365+31+28+31+30+31+30+31+31+30+2 1,'' 3*365+31+28+31+30+31+30+31+31+30+31+2 1,'' 3*365+31+28+31+30+31+30+31+31+30+31+30+3 1,'2010' 4*365+2,'' 4*365+31+2 1,'' 4*365+31+28+2 1,'' 4*365+31+28+31+2 1,'' 4*365+31+28+31+30+2 1,'' 4*365+31+28+31+30+31+2 1,'' 4*365+31+28+31+30+31+30+2 1,'' 4*365+31+28+31+30+31+30+31+2 1,'' 4*365+31+28+31+30+31+30+31+31+2 1,'' 4*365+31+28+31+30+31+30+31+31+30+2 1,'' 4*365+31+28+31+30+31+30+31+31+30+31+2 1,'' 4*365+31+28+31+30+31+30+31+31+30+31+30+3 1)")
#gp2.plot(Data(hetsdata,title='Cts/Day',with_='histeps lt 1'),Data(hetsdataeff,axes='x1y2',title='Cts/Day Corr',with_='histeps lt 2'),Data(hetsdataeff2,axes='x1y2',title='Cts/Day CorrMag',with_='histeps lt 3'),Data(herunav,title='Running Mean (+-13 Days)',with_='l lt 4 lw 3'),Data(herunaveff,title='Running Mean (+-13 Days) Corr',with_='l lt 5 lw 3',axes='x1y2'),Data(herunaveff2,title='Running Mean (+-13 Days) Corr',with_='l lt 6 lw 3',axes='x1y2'),Data(semdat,title='SEM UV',with_="histeps lt 7 lw 3"))
gp2.plot(Data(hetsdata,title='Cts/Day',with_='histeps lt 1'),Data(hetsdataeff,axes='x1y2',title='Cts/Day Corr',with_='histeps lt 2'),Data(hetsdataeff2,axes='x1y2',title='Cts/Day CorrMag',with_='histeps lt 3'),Data(herunav,title='Running Mean (+-13 Days)',with_='l lt 4 lw 3'),Data(herunaveff,title='Running Mean (+-13 Days) Corr',with_='l lt 5 lw 3',axes='x1y2'),Data(herunaveff2,title='Running Mean (+-13 Days) Corr',with_='l lt 6 lw 3',axes='x1y2'))
#gp2.plot(Data(herunav,title='Running Mean (+-13 Days)',with_='histeps lt 1'),Data(herunaveff,title='Running Mean (+-13 Days) Eff',with_='histeps lt 3',axes='x1y2'))
gp2.hardcopy("He1+_all_corr_mag.ps",color=True)
