from libacepy.lmfit import maxlifit
from scipy import zeros
from numpy import array
from math import sqrt
from Gnuplot import Gnuplot,Data

def g(x,p,dg):
    dg[0]=x**3
    dg[1]=x**2
    dg[2]=x
    dg[3]=1.
    return p[0]*x**3+p[1]*x**2+p[2]*x+p[3]

a=2.
b=5.
c=45.
p=zeros([4])
p0=zeros([3])
p0[0]=2.0
p0[1]=1.5
p0[2]=100.

p[0]=10.1
p[1]=25.2
p[2]=-55.0
p[3]=40.1
alpha=zeros([4,4])
covar=zeros([4,4])
ia=zeros([4],int)
ia[0]=ia[1]=1
ia[2]=ia[3]=1

x=range(-5,6)
x=array(x)
y=zeros([11])
sig=zeros([11])
for i in range(len(x)):
    y[i]=a*x[i]**3+b*x[i]**2+c
    sig[i]=sqrt(abs(y[i]))
print x
print y
merit=0.
merit=maxlifit(x,y,sig,p,ia,covar,alpha,merit,g)

data=[]
for i in range(len(x)):
    data.append([x[i],y[i],sig[i]])

pdata=Data(data)
pdata.set_option_colonsep("using","1:2:3")
pdata.set_option_colonsep("with","yerrorbars")


gp=Gnuplot()
gp("f(x)=%f*x**3+%f*x**2+%f*x+%f"%(p[0],p[1],p[2],p[3]))
gp("g(x)=%f*x**2+%f*x+%f"%(p0[0],p0[1],p0[2]))
gp.plot(pdata,"f(x)")
