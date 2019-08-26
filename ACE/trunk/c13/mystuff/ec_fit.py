 
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan,pi,exp
from os import popen2

Float=float
matrixmultiply=dot


data=zeros([10,128,3],Float)
gdata=zeros([10,2])

class Gnuplot:
    """Interface to gnuplot."""

    def __init__(self):
        """Create a pipe to gnuplot"""
        self.gpwrite,self.gpout=popen2("gnuplot")

    def __call__(self, s):
        """Send string to gnuplot"""

        self.gpwrite.write(s+"\n")
        self.gpwrite.flush()
        
    def getvar(self,var):
        """Get a gnuplot variable

           In order to avoid locking we have to check
           if the variable is really defined.
           This only works with a recent CVS gnuplot
           (having the defined(var) function;
            this is enabled per default).

           FIXME: no real error checking done so far ....
           FIXME: we could try to convert the returned string
                  to a float or int (depending on
                  an optional parameter passed to getvar)

        """
        self(" set print \"-\"\n")      # print output to stdout
        self(" if (defined(%s)) print %s ; else print \"None\" \n" % 
(var,var))
        result=self.gpout.readline()
        self(" set print\n")            # print output to default stderr
        if result[0:4]=="None":
            return None
        return(result)

gp=Gnuplot()

a=zeros([10,3],Float)
b=zeros([10,3],Float)
c=zeros([10,3],Float)
d=zeros([10,3],Float)

asum=zeros([3],Float)
bsum=zeros([3],Float)
csum=zeros([3],Float)
dsum=zeros([3],Float)

asumw=zeros([3],Float)
bsumw=zeros([3],Float)
csumw=zeros([3],Float)
dsumw=zeros([3],Float)

am=zeros([2],Float)
bm=zeros([2],Float)
cm=zeros([2],Float)
dm=zeros([2],Float)

amw=zeros([2],Float)
bmw=zeros([2],Float)
cmw=zeros([2],Float)
dmw=zeros([2],Float)

#src="/data/kleopatra/mu/et_matrices/"
src="all_data/step_files/"
v_int=345
step=48
echannel=22

def ap(x,A,xa,sa):
    return A/(sa*(2*pi)**0.5)*exp(-0.5*((x-xa)/sa)**2)
def bp(x,B,xb,sb):
    return B/(sb*(2*pi)**0.5)*exp(-0.5*((x-xb)/sb)**2)
def cp(x,C,xc,sc):
    return C/(sc*(2*pi)**0.5)*exp(-0.5*((x-xc)/sc)**2)
def dp(x,D,xd,sd):
    return D/(sd*(2*pi)**0.5)*exp(-0.5*((x-xd)/sd)**2)

def kap(x,A,xa,sa):
    return  A*((1/(4*pi*sa**2)))*(1+((x-xa)**2/(4*sa**2)))**-2
def kbp(x,B,xb,sb):
    return  B*((1/(4*pi*sb**2)))*(1+((x-xb)**2/(4*sb**2)))**-2
def kcp(x,C,xc,sc):
    return  C*((1/(4*pi*sc**2)))*(1+((x-xc)**2/(4*sc**2)))**-2
def kdp(x,D,xd,sd):
    return  D*((1/(4*pi*sd**2)))*(1+((x-xd)**2/(4*sd**2)))**-2

gp("a(x)=A/(sa*(2*pi)**0.5)*exp(-0.5*((x-xa)/sa)**2)")
gp("b(x)=B/(sb*(2*pi)**0.5)*exp(-0.5*((x-xb)/sb)**2)")
gp("c(x)=C/(sc*(2*pi)**0.5)*exp(-0.5*((x-xc)/sc)**2)")
gp("d(x)=D/(sd*(2*pi)**0.5)*exp(-0.5*((x-xd)/sd)**2)")

#gp("ka(x)=A*((1/(4*pi*sa**2)))*(1+((x-xa)**2/(4*sa**2)))**-2")
gp("ka(x)=A*(1+((x-xa)**2/(kappa*sa**2)))**-(kappa-1)")
gp("kb(x)=B*((1/(4*pi*sb**2)))*(1+((x-xb)**2/(4*sb**2)))**-2")
gp("kc(x)=C*((1/(4*pi*sc**2)))*(1+((x-xc)**2/(4*sc**2)))**-2")
gp("kd(x)=D*((1/(4*pi*sd**2)))*(1+((x-xd)**2/(4*sd**2)))**-2")

gp("s(x)=a(x)+b(x)+d(x)")
l=0
for i in [162]:
#for i in [28]:
    tchannel=i
    l+=1
    file1=open(src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel))
    s=0
    for m in file1:
        n=m.split()
        for t in range(3):
            data[l-1,s,t]=float(n[t])
        s+=1
#    print data

    gp("A=40000")
    gp("B=6000")
    gp("C=2000")
    gp("D=2000")
    gp("xa=22")
    gp("xb=25")
    gp("xc=174")
    gp("xd=28")
    gp("sa=2.")
    gp("sb=2.")
    gp("sc=2.")
    gp("sd=2.")
    gp("kappa=3.5")

    gp("set xrange[13:30]")
#    gp("fit s(x) '"+src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel)+"'u 1:2:3 via sa,A,B,sb,D,sd")
#    gp("plot '"+src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel)+"', s(x), a(x), b(x), d(x)")
#    gp("fit a(x)+b(x)+d(x) '"+src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel)+"'u 1:2:3 via sa,xa,xb,A,D")
#    gp("plot '"+src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel)+"' u 1:2:3 with errorbars, a(x),b(x),d(x),a(x)+b(x)+d(x)")
    gp("fit a(x) '"+src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel)+"'u 1:2:3 via sa,xa,A")
    gp("plot '"+src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel)+"' u 1:2:3 with errorbars, a(x)")
#    gp("fit ka(x) '"+src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel)+"'u 1:2:3 via sa,A,xa,kappa")
#    gp("plot '"+src+str(v_int)+"/t_files/"+str(v_int)+"_step_"+str(step)+"_t"+str(tchannel)+"' u 1:2:3 with errorbars, ka(x)")

    a[l-1,0]=float(str(gp.getvar("xa")))
    b[l-1,0]=float(str(gp.getvar("xb")))
    c[l-1,0]=float(str(gp.getvar("xc")))
    d[l-1,0]=float(str(gp.getvar("xd")))

    a[l-1,1]=float(str(gp.getvar("sa")))
    b[l-1,1]=float(str(gp.getvar("sb")))
    c[l-1,1]=float(str(gp.getvar("sc")))
    d[l-1,1]=float(str(gp.getvar("sd")))

    a[l-1,2]=float(str(gp.getvar("A")))
    b[l-1,2]=float(str(gp.getvar("B")))
    c[l-1,2]=float(str(gp.getvar("C")))
    d[l-1,2]=float(str(gp.getvar("D")))

    xq=0.
    for ii in range(150,171):
#        xq+=(ap(float(ii),a[l-1,2],a[l-1,0],a[l-1,1])-data[0,ii-1,1])**2
        xq+=((ap(float(ii),a[l-1,2],a[l-1,0],a[l-1,1])-data[0,ii-1,1])/data[0,ii-1,2])**2
    print xq

    exq=2*xq
    step=0.00001
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(150,171):
#            xq+=(ap(float(ii),a[l-1,2],a[l-1,0],(a[l-1,1]+step*jj*a[l-1,1]))-data[0,ii-1,1])**2
            xq+=((ap(float(ii),a[l-1,2],a[l-1,0],(a[l-1,1]+step*jj*a[l-1,1]))-data[0,ii-1,1])/data[0,ii-1,2])**2
        jj+=1
    print xq, a[l-1,1], (a[l-1,1]+step*jj*a[l-1,1]), ((a[l-1,1]+step*jj*a[l-1,1])-a[l-1,1])

    step=0.00001
    jj=0
    xq=0.
    while (xq < exq):
        xq=0.
        for ii in range(150,171):
#            xq+=(ap(float(ii),a[l-1,2],a[l-1,0],(a[l-1,1]+step*jj*a[l-1,1]))-data[0,ii-1,1])**2
            xq+=((ap(float(ii),a[l-1,2],a[l-1,0],(a[l-1,1]+step*jj*a[l-1,1]))-data[0,ii-1,1])/data[0,ii-1,2])**2
        jj-=1
    print xq, a[l-1,1], (a[l-1,1]+step*jj*a[l-1,1]), ((a[l-1,1]+step*jj*a[l-1,1])-a[l-1,1])
