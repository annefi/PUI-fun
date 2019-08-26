from pycwt import cwt_f
from pylib.etTools import fftPlot
from numpy import array,linspace,zeros,sin,exp,arange,pi
from Gnuplot import Gnuplot,Data,GridData
from libacepy.mag import magdata



tdim=100

signal=zeros([tdim])
time=arange(float(tdim))

def gauss(t,t0,sig):
    return exp((-(t-t0)**2)/(2*sig**2))

def sinus(t,t0,f):
    lam=1./f
    return sin((t-t0)/lam*2.*pi)

signal=1.5*gauss(time,52.,1.5)*sinus(time,100.3,0.3)+1.*gauss(time,50.,2.5)*sinus(time,100.9,.5)+1.*gauss(time,47.,2.5)*sinus(time,100.1,.6)
#signal=gauss(time,115.,15.)*sinus(time,0.,0.05)

freqs=zeros([100])
freqs[0]=1.
for i in range(1,100):
    freqs[i]=freqs[i-1]/1.03

res=cwt_f(signal,freqs)
resarr=zeros([tdim,100])
for i in range(tdim):
    resarr[i,:]=abs(res[:,i])



gp=Gnuplot()
gp("set log y")
gp("set pm3d map corners2color c1")
#gp("set log cb")
gp("set yrange[0.01:1.]")
gp("set xrange[%f:%f]"%(0,tdim))

gp.splot(GridData(resarr,time,freqs))


gp2=Gnuplot()
gp2("set style data lines")
gp2.plot(signal)

gp3=Gnuplot()
gp3("set style data lines")
gp3.plot(Data(freqs,resarr[50]))


gpfft=Gnuplot()
gpfft("set log xy")
gpfft("set style data lines")
psd=fftPlot(signal)
gpfft.plot(psd)
