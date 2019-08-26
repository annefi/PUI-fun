#from libacepy.fft import ifft
from Gnuplot import Gnuplot,Data
from math import sin,cos
from cmath import pi, exp
from scipy import fft 
data=[]
dim=1024
for i in range(dim):
    data.append(sin(float(i)/2.*2.)+sin(float(i)/2.*1.))
#    for j in range(128):
#        if (j>10 and j<50.):
#            data.append(1.)
#        else:
#            data.append(0.)

fftdata=fft(data)
print fftdata
#print fftdata[10].imag
plotdata=[]
plotdata2=[]
N=len(fftdata)
for i in range(len(fftdata)/2+1):
    plotdata.append([float(i)/float(N)*2.,2.*abs(fftdata[i].imag)/dim])
    plotdata2.append([float(i)/float(N)*2.,2.*abs(fftdata[i].real)/dim])

#for i in range(len(fftdata)/2):
#    plotdata.append([-float(i)/float(N),abs(exp(fftdata[len(fftdata)-i-1]))])

sumdata=[]
for i in range(dim):
    tmpsum=0.
    for j in range(len(fftdata)/2+1):
        tmpsum+=-sin(float(j)/float(N)*2*pi*float(i))*(fftdata[j].imag)+cos(float(j)/float(N)*2*pi*float(i))*(fftdata[j].real)
#    tmpsum=tmpsum*2.
    for j in range(len(fftdata)/2):
        tmpsum+=-sin(float(len(fftdata)-j-1)/float(N)*2*pi*float(i))*(fftdata[len(fftdata)-j-1].imag)+cos(float(len(fftdata)-j-1)/float(N)*2*pi*float(i))*(fftdata[len(fftdata)-j-1].real)
    tmpsum=tmpsum/dim
    sumdata.append([float(i)/2.,tmpsum])

sumdata2=[]
for i in range(dim):
    tmpsum=0.
    for j in range(len(fftdata)/2+1):
        tmpsum+=sin(float(j)/float(N)*2*pi*float(i))*(fftdata[j].real)+cos(float(j)/float(N)*2*pi*float(i))*(fftdata[j].imag)
#    tmpsum=tmpsum*2.
    for j in range(len(fftdata)/2):
        tmpsum+=sin(float(len(fftdata)-j-1)/float(N)*2*pi*float(i))*(fftdata[len(fftdata)-j-1].real)+cos(float(len(fftdata)-j-1)/float(N)*2*pi*float(i))*(fftdata[len(fftdata)-j-1].imag)
    tmpsum=tmpsum/dim
    sumdata2.append([float(i)/2.,tmpsum])


plotsum=Data(sumdata)
plotsum.set_option_colonsep("with", "line")
plotsum2=Data(sumdata2)
plotsum2.set_option_colonsep("with", "line")

gp=Gnuplot()
gp("set logscale y")
#gp("set logscale x")
gp.plot(plotdata,plotdata2)
gp2=Gnuplot()
#gp2("set logscale y")
gp2("set samples 12800")
gp2("set xrange[80:128]")
gp2.plot("(sin(x)+sin(2*x))",plotsum,plotsum2)
