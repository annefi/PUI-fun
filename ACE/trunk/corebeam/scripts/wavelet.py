from pycwt import cwt_f,Morlet
from numpy import array,linspace,zeros,sin,exp,arange,pi,cos,arccos,sqrt,sum,arctan2,histogram,cross
from Gnuplot import Gnuplot,Data,GridData
from libacepy.mag import magdata
from pylib.etTools import fftPlot


year=2001
tstep=1./84400.*64.
i=8
timeframe=[[33.341,33.41]]
timeframe=[[222.160972,222.160972+2./120.]]
timeframe=[[39.20456,39.20456+6./120.]]
timeframe=[[4.087384,4.087384+6./120]]
timeframe=[[153.991,154.002]]
timeframe=[[153.98,153.99]]

#timeframe=[[325.92+float(i)/24./5.,325.92+float(i+1)/24./5.]]
#timeframe=[[325.6,325.8]]
magdat=magdata(1.,year,timeframe,"/data/etph/ace/mag/")

tdim=2000

signal=zeros([tdim])
time=arange(float(tdim))

def crossp(a,b):
    return array([a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]])

def gauss(t,t0,sig):
    return exp((-(t-t0)**2)/(2*sig**2))

def sinus(t,t0,f):
    lam=1./f
    return sin((t-t0)/lam*2.*pi)

signal=gauss(time,45.,10.)*sinus(time,10.,0.1)+gauss(time,115.,50.)*sinus(time,0.,0.01)
#signal=gauss(time,115.,15.)*sinus(time,0.,0.05)


# calculate mean magnetic field vector and transform into mean mag vec coords
mask=(magdat.time>timeframe[0][0])*(magdat.time<timeframe[0][1])
meanb=[sum(magdat.magbx[mask]),sum(magdat.magby[mask]),sum(-magdat.magbz[mask])]
ebx=array(meanb/(sqrt(meanb[0]**2+meanb[1]**2+meanb[2]**2)))
#by=array([magdat.magbx[mask][0],magdat.magby[mask][0],magdat.magbz[mask][0]])
by=array([0.,0.,-1.])
eby=-cross(ebx,by)
eby=eby/sqrt(sum(eby**2))
ebz=cross(ebx,eby)
ebz=ebz/sqrt(sum(ebz**2))
#ebx=array([1.,0.,0.])
#eby=array([0.,1.,0.])
#ebz=array([0.,0.,1.])

gpcs=Gnuplot()
gpcs.splot(Data([[0.,0.,0.,ebx[0],ebx[1],ebx[2]]],with_="vectors",title="'ebx'"),Data([[0.,0.,0.,eby[0],eby[1],eby[2]]],with_="vectors",title="'eby'"),Data([[0.,0.,0.,ebz[0],ebz[1],ebz[2]]],with_="vectors",title="'ebz'"))

nbx=zeros(len(magdat.time[mask]))
nby=zeros(len(magdat.time[mask]))
nbz=zeros(len(magdat.time[mask]))

for i in range(len(magdat.time[mask])):
   tmpmag=array([magdat.magbx[mask][i],magdat.magby[mask][i],magdat.magbz[mask][i]])
   nbx[i]=sum(ebx*tmpmag)
   nby[i]=sum(eby*tmpmag)
   nbz[i]=sum(ebz*tmpmag)
   #nbx[i]=sqrt(sum((ebx*tmpmag)**2))
   #nby[i]=sqrt(sum((eby*tmpmag)**2))
   #nbz[i]=sqrt(sum((ebz*tmpmag)**2))

nrfreq=120
morletwidth=1.
freqs=zeros([nrfreq])
freqs[0]=.5
for i in range(1,nrfreq):
    freqs[i]=freqs[i-1]/1.05

resy=cwt_f(nby,freqs,wavelet=Morlet(f0=morletwidth))
tdim=len(nby)
resyarr=zeros([tdim,nrfreq])
for i in range(tdim):
    resyarr[i,:]=abs(resy[:,i])

#theta=arccos(cos(magdat.phi)*cos(magdat.theta))/pi*180.

#resy=cwt_f(theta,freqs)
#tdim=len(theta)
#resyarr=zeros([tdim,100])
#for i in range(tdim):
#    resyarr[i,:]=abs(resy[:,i])

resz=cwt_f(nbz,freqs,wavelet=Morlet(f0=morletwidth))
tdim=len(nbz)
reszarr=zeros([tdim,nrfreq])
for i in range(tdim):
    reszarr[i,:]=abs(resz[:,i])

resx=cwt_f(nbx,freqs,wavelet=Morlet(f0=morletwidth))
tdim=len(nbx)
resxarr=zeros([tdim,nrfreq])
for i in range(tdim):
    resxarr[i,:]=abs(resx[:,i])

respol=zeros([tdim,nrfreq])
for i in range(tdim):
    respol[i,:]=(arctan2(resz[:,i].imag,resz[:,i].real)-arctan2(resy[:,i].imag,resy[:,i].real))
respol[respol>pi]=(2*pi-respol[respol>pi])
respol[respol<-pi]=(-2*pi-respol[respol<-pi])
respol[(respol<=pi)*(respol>=-pi)]/=pi
#respol[respol>pi]=(2*pi-respol[respol>pi])/pi
#respol[respol<pi]=(-2*pi+respol[respol<pi])/pi
    #respol[i,:]=tmppol

respolxy=zeros([tdim,nrfreq])
for i in range(tdim):
    respolxy[i,:]=(arctan2(resx[:,i].imag,resx[:,i].real)-arctan2(resy[:,i].imag,resy[:,i].real))
respolxy[respolxy>pi]=(2*pi-respolxy[respolxy>pi])
respolxy[respolxy<-pi]=(-2*pi-respolxy[respolxy<-pi])
respolxy[(respolxy<=pi)*(respolxy>=-pi)]/=pi

respolxz=zeros([tdim,nrfreq])
for i in range(tdim):
    respolxz[i,:]=(arctan2(resx[:,i].imag,resx[:,i].real)-arctan2(resz[:,i].imag,resz[:,i].real))
respolxz[respolxz>pi]=(2*pi-respolxz[respolxz>pi])
respolxz[respolxz<-pi]=(-2*pi-respolxz[respolxz<-pi])
respolxz[(respolxz<=pi)*(respolxz>=-pi)]/=pi



#resz=cwt_f(magdat.theta,freqs)
#tdim=len(magdat.theta)
#reszarr=zeros([tdim,100])
#for i in range(tdim):
#    reszarr[i,:]=abs(resz[:,i])

y,x=histogram(respol[:,0:30],linspace(-1.,1.,21))
#y,x=histogram(respol,linspace(-1.,1.,21))
y2,x2=histogram(respol[:,50:80],linspace(-1.,1.,21))
y3,x4=histogram(respolxy[:,5:20],linspace(-1.,1.,21))
#y,x=histogram(respol,linspace(-1.,1.,21))
y4,x4=histogram(respolxy[:,50:65],linspace(-1.,1.,21))

gp6=Gnuplot()
gp6("set style data histeps")
gp6.plot(Data(x[:-1]+0.05,y),Data(x2[:-1]+0.05,y2,with_="histeps lt 3"))

#respol[(respol>0.75)]=-1.
#respol[(respol<0.25)*(respol>-0.25)]=-1.
#respol[(respol<-0.75)]=-1.



#respolxz[(respolxz>0.75)]=-1.
#respolxz[(respolxz<0.25)*(respol>-0.25)]=-1.
#respolxz[(respolxz<-0.75)]=-1.

#respolxy[(respolxy>0.75)]=-1.
#respolxy[(respolxy<0.25)*(respolxz>-0.25)]=-1.
#respolxy[(respolxy<-0.75)]=-1.


fmin=0.1
gp=Gnuplot()
gp("set log y")
gp("set pm3d map corners2color c1")
#gp("set log cb")
#gp("set palette model RGB functions gray<0.0000001 ? 1 : gray , gray<0.0000001 ? 1 : 0.5-gray , gray <0.0000001 ? 1 : (1-gray)*0.7")
gp("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp("set yrange[%f:1.]"%(fmin))
gp("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
gp("set title 'by'")
gp.splot(GridData(resyarr,magdat.time[mask],freqs))

gp2=Gnuplot()
gp2("set log y")
gp2("set pm3d map corners2color c1")
#gp("set log cb")
#gp2("set palette model RGB functions gray<0.0000001 ? 1 : gray , gray<0.0000001 ? 1 : 0.5-gray , gray <0.0000001 ? 1 : (1-gray)*0.7")
gp2("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp2("set yrange[%f:1.]"%(fmin))
#gp2("set yrange[0.1:1.]")
gp2("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
gp2("set title 'bz'")

gp2.splot(GridData(reszarr,magdat.time[mask],freqs))

gp3=Gnuplot()
gp3("set log y")
gp3("set pm3d map corners2color c1")
#gp("set log cb")
#gp3("set palette model RGB functions gray<0.0000001 ? 1 : gray , gray<0.0000001 ? 1 : 0.5-gray , gray <0.0000001 ? 1 : (1-gray)*0.7")
gp3("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
#gp3("set yrange[0.1:1.]")
gp3("set yrange[%f:1.]"%(fmin))
gp3("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
gp3("set title 'bx'")

gp3.splot(GridData(resxarr,magdat.time[mask],freqs))


gp5=Gnuplot()
gp5("set log y")
gp5("set pm3d map corners2color c1")
#gp("set log cb")
#gp3("set palette model RGB functions gray<0.0000001 ? 1 : gray , gray<0.0000001 ? 1 : 0.5-gray , gray <0.0000001 ? 1 : (1-gray)*0.7")
#gp5("set palette model RGB functions gray<0.5 ? gray*2 : 1 , gray<0.5 ? gray*2 : 2-gray*2,  gray<0.5 ? 1-sqrt(gray*2) : 0")
gp5("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp5("set yrange[%f:1.]"%(fmin))
#gp5("set yrange[0.1:1.]")
gp5("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
gp5("set cbrange[-1.:1.]")
gp5("set title 'polyz'")

gp5.splot(GridData(respol,magdat.time[mask],freqs))


gp6=Gnuplot()
gp6("set log y")
gp6("set pm3d map corners2color c1")
#gp("set log cb")
#gp3("set palette model RGB functions gray<0.0000001 ? 1 : gray , gray<0.0000001 ? 1 : 0.5-gray , gray <0.0000001 ? 1 : (1-gray)*0.7")
#gp6("set palette model RGB functions gray<0.5 ? gray*2 : 1 , gray<0.5 ? gray*2 : 2-gray*2,  gray<0.5 ? 1-sqrt(gray*2) : 0")
gp6("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp6("set yrange[%f:1.]"%(fmin))
#gp5("set yrange[0.1:1.]")
gp6("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
gp6("set cbrange[-1.:1.]")
gp6("set title 'polxy'")

gp6.splot(GridData(respolxy,magdat.time[mask],freqs))

gp7=Gnuplot()
gp7("set log y")
gp7("set pm3d map corners2color c1")
#gp("set log cb")
#gp3("set palette model RGB functions gray<0.0000001 ? 1 : gray , gray<0.0000001 ? 1 : 0.5-gray , gray <0.0000001 ? 1 : (1-gray)*0.7")
#gp7("set palette model RGB functions gray<0.5 ? gray*2 : 1 , gray<0.5 ? gray*2 : 2-gray*2,  gray<0.5 ? 1-sqrt(gray*2) : 0")
gp7("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp7("set yrange[%f:1.]"%(fmin))
#gp5("set yrange[0.1:1.]")
gp7("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
gp7("set cbrange[-1.:1.]")
gp7("set title 'polxz'")

gp7.splot(GridData(respolxz,magdat.time[mask],freqs))

gp4=Gnuplot()
psdy=fftPlot(nby)
psdz=fftPlot(nbz)
psdx=fftPlot(nbx)
gp4("set style data lines")
gp4("set log xy")
gp4("set title 'fft'")
gp4.plot(psdy,psdz,psdz,psdx)
