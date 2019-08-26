from numpy import loadtxt,array,zeros,mean,isnan,sqrt,sin,histogram,pi,linspace
from Gnuplot import Gnuplot,Data


def getinstrcorr(vel):
    corrarr=array([[ 200.0 , 5.49043483295 ],[ 225.0 , 5.67983733619 ],[ 250.0 , 5.68227155074 ],[ 275.0 , 5.56193846422 ],[ 300.0 , 5.8442144413 ],[ 325.0 , 5.37170390505 ],[ 350.0 , 5.51616229145 ],[ 375.0 , 5.48969782001 ],[ 400.0 , 6.15855302221 ],[ 425.0 , 6.09834530612 ],[ 450.0 , 5.8778300313 ],[ 475.0 , 6.37243586564 ],[ 500.0 , 5.39150817977 ],[ 525.0 , 5.22520842997 ],[ 550.0 , 5.10068013994 ],[ 575.0 , 4.5366337662 ],[ 600.0 , 3.5623656857 ],[ 625.0 , 3.26938069237 ],[ 650.0 , 3.76627813166 ],[ 675.0 , 3.50477821859 ],[ 700.0 , 3.94211947081 ],[ 725.0 , 3.66596461895 ],[ 750.0 , 4.11088663212 ],[ 775.0 , 3.72749123149 ],[ 800.0 , 4.24417441485 ],[ 825.0 , 3.53773234342 ],[ 850.0 , 4.31035803605 ],[ 875.0 , 4.61747840259 ],[ 900.0 , 4.29183966838 ],[ 925.0 , 4.72521771599 ],[ 950.0 , 4.94615529973 ],[ 975.0 , 4.69948229037 ],[ 1000.0 , 5.0640806196 ]])
    corrarr[:,1]/=2.
    ergarr=[]
    for v in vel:
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
        ergarr.append(y0+m*x)
    return array(ergarr)


years=[2006,2007,2008,2009,2010]
doys=[365,365,366,365,365]

data=loadtxt("/data/etph/ace/tmp/hepswepam.dat",skiprows=1)

print "daten geladen"

hedoydata=[]
hedoydatainstr=[]
hedoydatainstrmag=[]

ycount=0
for year in years:
    for doy in range(1,doys[ycount]+1):
        mask=(data[:,0]==float(year))*(data[:,1]>float(doy))*(data[:,1]<float(doy)+1.)
        hedoydata.append([float(year)+float(doy)/float(doys[ycount]+1.),mean(data[mask][:,2])])
        instr1=getinstrcorr(data[mask][:,3])
        instr2=getinstrcorr(data[mask*(data[:,4]>0.)][:,3])
        hedoydatainstr.append([float(year)+float(doy)/float(doys[ycount]+1.),mean(data[mask][:,2]/instr1)])
        #hedoydatainstrmag.append([float(year)+float(doy)/float(doys[ycount]+1.),mean(data[mask][:,2]/instr/(data[mask*(data[:,4]>0.)][:,4]*sin(data[mask*(data[:,4]>0.)][:,5])))])
        hedoydatainstrmag.append([float(year)+float(doy)/float(doys[ycount]+1.),mean(data[mask*(data[:,4]>0.)][:,2]/instr2/data[mask*(data[:,4]>0.)][:,4]/(sin(data[mask*(data[:,4]>0.)][:,5])+1.)*2.)])
    ycount+=1

hedoydata=array(hedoydata)
hedoydata=hedoydata[~isnan(hedoydata[:,1])]
hedoydatainstr=array(hedoydatainstr)
hedoydatainstr=hedoydatainstr[~isnan(hedoydatainstr[:,1])]
hedoydatainstrmag=array(hedoydatainstrmag)
hedoydatainstrmag=hedoydatainstrmag[~isnan(hedoydatainstrmag[:,1])]
xdim,ydim=hedoydatainstr.shape
hedoyinstrrm=zeros([xdim,ydim])
hedoyinstrrm[:,0]=hedoydatainstr[:,0]
bw=27
for i in range(bw/2,xdim-bw/2+1):
    year=int(hedoydatainstr[i,0])
    br=13.1/float(doys[year-2006])
    hedoyinstrrm[i,1]=mean(hedoydatainstr[(hedoydatainstr[:,0]>=hedoydatainstr[i,0]-br)*(hedoydatainstr[:,0]<=hedoydatainstr[i,0]+br)][:,1])
xdim,ydim=hedoydatainstrmag.shape
hedoyinstrmagrm=zeros([xdim,ydim])
hedoyinstrmagrm[:,0]=hedoydatainstrmag[:,0]
bw=27
for i in range(bw/2,xdim-bw/2+1):
    year=int(hedoydatainstr[i,0])
    br=13.1/float(doys[year-2006])
    hedoyinstrmagrm[i,1]=mean(hedoydatainstrmag[(hedoydatainstrmag[:,0]>=hedoydatainstrmag[i,0]-br)*(hedoydatainstrmag[:,0]<=hedoydatainstrmag[i,0]+br)][:,1])
    #hedoyinstrmagrm[i,1]=mean(hedoydatainstrmag[i-bw/2:i+bw/2+1,1])


gp=Gnuplot()
gp("set title 'data'")
gp.plot(Data(data[:,0]+data[:,1]/366.,data[:,2],with_="p lt 1"),Data(data[:,0]+data[:,1]/366.,data[:,4],with_="l lt 3"))
gp2=Gnuplot()
gp2("set title 'instr'")
gp2.plot(Data(hedoydatainstr,with_="steps lt 3"),Data(hedoyinstrrm,with_="steps lt 1 lw 3"))
gp3=Gnuplot()
gp3("set title 'instrmag'")
gp3.plot(Data(hedoydatainstrmag,with_="steps lt 3"),Data(hedoyinstrmagrm,with_="steps lt 1 lw 3"))
gp4=Gnuplot()
gp4("set title 'data/instr hires'")
gp4.plot(Data(data[:,0]-2000+data[:,1]/366.,data[:,2]/getinstrcorr(data[:,3]),with_="l lt 1"),Data(data[:,0]-2000+data[:,1]/366.,sqrt(data[:,4])*sin(data[:,5]),with_="l lt 3"),Data(data[:,0]-2000+data[:,1]/366.,sqrt(data[:,4]),with_="l lt 4"))


#timemask=(data[:,1]>300.)*(data[:,1]<365.)
mask=(data[:,3]>600.)*(data[:,3]<700.)*(data[:,4]>3.)*(data[:,4]<5.)#*timemask
thetacounts,thetabins=histogram(data[mask][:,5],linspace(0,pi,19),weights=data[mask][:,2])
normthetacounts,x=histogram(data[mask][:,5],linspace(0,pi,19))
thetacounts/=normthetacounts

thetamag,thetabins=histogram(data[mask][:,5],linspace(0,pi,19),weights=data[mask][:,4])
normthetamag,x=histogram(data[mask][:,5],linspace(0,pi,19))
thetamag/=normthetamag


#thetabins=thetabins[:-1]

thetavsw,thetabins=histogram(data[:,5],linspace(0,pi,19),weights=data[:,3])
normthetavsw,x=histogram(data[:,5],linspace(0,pi,19))
thetavsw/=normthetavsw

thetabins=thetabins[:-1]

gp5=Gnuplot()
gp5.plot(Data(thetabins,thetacounts,with_="steps"),Data(thetabins,thetamag,with_="steps"))
gp6=Gnuplot()
gp6.plot(Data(thetabins,thetavsw,with_="steps"))
