 
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan,pi,exp
from os import popen2

Float=float
matrixmultiply=dot


data=zeros([10,512,3],Float)
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

a=zeros([10,12],Float)
b=zeros([10,12],Float)
c=zeros([10,12],Float)
d=zeros([10,12],Float)

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

src="all_data/step_files/"
v_int=345
eq_step=48
a_low=int(150)
a_high=int(170)
b_low=int(175)
b_high=int(185)
pr_low=int(150)
pr_high=int(200)

#def ap(x,A,xa,sa):
#    return A/(sa*(2*pi)**0.5)*exp(-0.5*((x-xa)/sa)**2)
#def bp(x,B,xb,sb):
#    return B/(sb*(2*pi)**0.5)*exp(-0.5*((x-xb)/sb)**2)
def ap(x,A,xa,sa):
    return A*exp(-0.5*((x-xa)/sa)**2)
def bp(x,B,xb,sb):
    return B*exp(-0.5*((x-xb)/sb)**2)
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

#gp("a(x)=A/(sa*(2*pi)**0.5)*exp(-0.5*((x-xa)/sa)**2)")
gp("a(x)=A*exp(-0.5*((x-xa)/sa)**2)")
#gp("b(x)=B/(sb*(2*pi)**0.5)*exp(-0.5*((x-xb)/sb)**2)")
gp("b(x)=B*exp(-0.5*((x-xb)/sb)**2)")
gp("c(x)=C/(sc*(2*pi)**0.5)*exp(-0.5*((x-xc)/sc)**2)")
gp("d(x)=D/(sd*(2*pi)**0.5)*exp(-0.5*((x-xd)/sd)**2)")

gp("ka(x)=A*((1/(4*pi*sa**2)))*(1+((x-xa)**2/(4*sa**2)))**-2")
gp("kb(x)=B*((1/(4*pi*sb**2)))*(1+((x-xb)**2/(4*sb**2)))**-2")
gp("kc(x)=C*((1/(4*pi*sc**2)))*(1+((x-xc)**2/(4*sc**2)))**-2")
gp("kd(x)=D*((1/(4*pi*sd**2)))*(1+((x-xd)**2/(4*sd**2)))**-2")

#gp("s(x)=a(x)+b(x)+c(x)+d(x)")
#gp("s(x)=a(x)+b(x)+d(x)")
gp("s(x)=a(x)+b(x)")
l=0
echannelarray=[20,21,22,23,24,25,26,27,28,29]
for i in echannelarray:
    echannel=i
    l+=1
    file1=open(src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel))
#    file1=open(src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e_all")
    s=0
    for m in file1:
        n=m.split()
        for t in range(3):
            data[l-1,s,t]=float(n[t])
        s+=1
    print data

    gp("A="+str(data[l-1,165,1]))
    gp("B="+str(data[l-1,178,1]))
    gp("C=300")
    gp("D=200")
    gp("xa=167")
    gp("xb=178")
    gp("xc=174")
    gp("xd=193")
    gp("sa=2.2")
    gp("sb=3.0")
    gp("sc=3.3")
    gp("sd=3.3")

    gp("set xrange["+str(a_low)+":"+str(a_high)+"]")
    gp("fit a(x) '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel)+"' u 1:2:3 via A,xa,sa")
#    gp("fit a(x) '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e_all' u 1:2:3 via A,xa,sa")
#    gp("set xrange[165:175")
#    gp("fit ka(x) '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel)+"' u 1:2:3 via sa,A,xa")
    gp("set xrange["+str(b_low)+":"+str(b_high)+"]")
#    gp("sb=sa") 
    gp("fit b(x) '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel)+"' u 1:2:3 via B,xb,sb")
#    gp("fit b(x) '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e_all' u 1:2:3 via B,xb,sb")
    gp("set xrange["+str(pr_low)+":"+str(pr_high)+"]")
    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel)+"' u 1:2:3 with errorbars,a(x),b(x),a(x)+b(x)")
#    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e_all' u 1:2:3 with errorbars , a(x),b(x),a(x)+b(x)")
#    gp("set term postscript color 18")
#    gp("set output '"+src+str(v_int)+"/diff_files/"+"plot_"+str(eq_step)+"_"+str(i)+".ps'")
#    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel)+"' u 1:2:3 with errorbars , a(x),b(x)")
#    gp("set term X11")


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


    for j in range(3):
        asum[j]+=a[l-1,j]
        bsum[j]+=b[l-1,j]
        csum[j]+=c[l-1,j]
        dsum[j]+=d[l-1,j]

    for j in range(2):
        asumw[j]+=(a[l-1,j]*a[l-1,2])
        bsumw[j]+=(b[l-1,j]*b[l-1,2])
        csumw[j]+=(c[l-1,j]*c[l-1,2])
        dsumw[j]+=(d[l-1,j]*d[l-1,2])

############################## C12 ##########################
# Bestimmung des chi-quadrat
    xq=0.
    print xq
    for ii in range(a_low,a_high+1):
        xq+=((ap(float(ii),a[l-1,2],a[l-1,0],a[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
    print xq

    exq=2*xq
    step=0.00001

# Bestimmung des sigma-Fehlers

    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(a_low,a_high+1):
            xq+=((ap(float(ii),a[l-1,2],a[l-1,0],(a[l-1,1]+step*jj*a[l-1,1]))-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, a[l-1,1], (a[l-1,1]+step*jj*a[l-1,1]), ((a[l-1,1]+step*jj*a[l-1,1])-a[l-1,1])
    a[l-1,6]=(a[l-1,1]+step*jj*a[l-1,1])
    dummy=((a[l-1,1]+step*jj*a[l-1,1])-a[l-1,1])

    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(a_low,a_high+1):
            xq+=((ap(float(ii),a[l-1,2],a[l-1,0],(a[l-1,1]-step*jj*a[l-1,1]))-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, a[l-1,1], (a[l-1,1]-step*jj*a[l-1,1]), ((a[l-1,1]+step*jj*a[l-1,1])-a[l-1,1])
    a[l-1,7]=(a[l-1,1]-step*jj*a[l-1,1])
    dummy2=((a[l-1,1]+step*jj*a[l-1,1])-a[l-1,1])
    a[l-1,8]=(dummy+dummy2)/2.

# Bestimmung des Positions-Fehlers
    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(a_low,a_high+1):
            xq+=((ap(float(ii),a[l-1,2],(a[l-1,0]+step*jj*a[l-1,0]),a[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, a[l-1,0], (a[l-1,0]+step*jj*a[l-1,0]), ((a[l-1,0]+step*jj*a[l-1,0])-a[l-1,0])
    a[l-1,3]=(a[l-1,0]+step*jj*a[l-1,0])
    dummy=((a[l-1,0]+step*jj*a[l-1,0])-a[l-1,0])

    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(a_low,a_high+1):
            xq+=((ap(float(ii),a[l-1,2],(a[l-1,0]-step*jj*a[l-1,0]),a[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, a[l-1,0], (a[l-1,0]-step*jj*a[l-1,0]), ((a[l-1,0]+step*jj*a[l-1,0])-a[l-1,0])
    a[l-1,4]=(a[l-1,0]-step*jj*a[l-1,0])
    dummy2=((a[l-1,0]+step*jj*a[l-1,0])-a[l-1,0])
    a[l-1,5]=(dummy+dummy2)/2.

# Bestimmung des Höhen-Fehlers
    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(a_low,a_high+1):
            xq+=((ap(float(ii),(a[l-1,2]+step*jj*a[l-1,2]),a[l-1,0],a[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, a[l-1,2], (a[l-1,2]+step*jj*a[l-1,2]), ((a[l-1,2]+step*jj*a[l-1,2])-a[l-1,2])
    a[l-1,9]=(a[l-1,2]+step*jj*a[l-1,2])
    dummy=((a[l-1,2]+step*jj*a[l-1,2])-a[l-1,2])


    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(a_low,a_high+1):
            xq+=((ap(float(ii),(a[l-1,2]-step*jj*a[l-1,2]),a[l-1,0],a[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, a[l-1,2], (a[l-1,2]-step*jj*a[l-1,2]), ((a[l-1,2]+step*jj*a[l-1,2])-a[l-1,2])
    a[l-1,10]=(a[l-1,2]-step*jj*a[l-1,2])
    dummy2=((a[l-1,2]+step*jj*a[l-1,2])-a[l-1,2])
    a[l-1,11]=(dummy+dummy2)/2.


############################## O7 ###########################
# Bestimmung des chi-quadrat
    xq=0.
    for ii in range(b_low,b_high+1):
        xq+=((bp(float(ii),b[l-1,2],b[l-1,0],b[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
    print xq

    exq=2*xq
    step=0.00001

# Bestimmung des sigma-Fehlers

    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(b_low,b_high+1):
            xq+=((bp(float(ii),b[l-1,2],b[l-1,0],(b[l-1,1]+step*jj*b[l-1,1]))-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, b[l-1,1], (b[l-1,1]+step*jj*b[l-1,1]), ((b[l-1,1]+step*jj*b[l-1,1])-b[l-1,1])
    b[l-1,6]=(b[l-1,1]+step*jj*b[l-1,1])
    dummy=((b[l-1,1]+step*jj*b[l-1,1])-b[l-1,1])

    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(b_low,b_high+1):
            xq+=((bp(float(ii),b[l-1,2],b[l-1,0],(b[l-1,1]-step*jj*b[l-1,1]))-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, b[l-1,1], (b[l-1,1]-step*jj*b[l-1,1]), ((b[l-1,1]+step*jj*b[l-1,1])-b[l-1,1])
    b[l-1,7]=(b[l-1,1]-step*jj*b[l-1,1])
    dummy2=((b[l-1,1]+step*jj*b[l-1,1])-b[l-1,1])
    b[l-1,8]=(dummy+dummy2)/2.

# Bestimmung des Positions-Fehlers
    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(b_low,b_high+1):
            xq+=((bp(float(ii),b[l-1,2],(b[l-1,0]+step*jj*b[l-1,0]),b[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, b[l-1,0], (b[l-1,0]+step*jj*b[l-1,0]), ((b[l-1,0]+step*jj*b[l-1,0])-b[l-1,0])
    b[l-1,3]=(b[l-1,0]+step*jj*b[l-1,0])
    dummy=((b[l-1,0]+step*jj*b[l-1,0])-b[l-1,0])

    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(b_low,b_high+1):
            xq+=((bp(float(ii),b[l-1,2],(b[l-1,0]-step*jj*b[l-1,0]),b[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, b[l-1,0], (b[l-1,0]-step*jj*b[l-1,0]), ((b[l-1,0]+step*jj*b[l-1,0])-b[l-1,0])
    b[l-1,4]=(b[l-1,0]-step*jj*b[l-1,0])
    dummy2=((b[l-1,0]+step*jj*b[l-1,0])-b[l-1,0])
    b[l-1,5]=(dummy+dummy2)/2.

# Bestimmung des Höhen-Fehlers
    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(b_low,b_high+1):
            xq+=((bp(float(ii),(b[l-1,2]+step*jj*b[l-1,2]),b[l-1,0],b[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, b[l-1,2], (b[l-1,2]+step*jj*b[l-1,2]), ((b[l-1,2]+step*jj*b[l-1,2])-b[l-1,2])
    b[l-1,9]=(b[l-1,2]+step*jj*b[l-1,2])
    dummy=((b[l-1,2]+step*jj*b[l-1,2])-b[l-1,2])


    xq=0.
    jj=0
    while (xq < exq):
        xq=0.
        for ii in range(b_low,b_high+1):
            xq+=((bp(float(ii),(b[l-1,2]-step*jj*b[l-1,2]),b[l-1,0],b[l-1,1])-data[l-1,ii-1,1])/data[l-1,ii-1,2])**2
        jj+=1
    print xq, b[l-1,2], (b[l-1,2]-step*jj*b[l-1,2]), ((b[l-1,2]+step*jj*b[l-1,2])-b[l-1,2])
    b[l-1,10]=(b[l-1,2]-step*jj*b[l-1,2])
    dummy2=((b[l-1,2]+step*jj*b[l-1,2])-b[l-1,2])
    b[l-1,11]=(dummy+dummy2)/2.


    gp("set xrange["+str(pr_low)+":"+str(pr_high)+"]")
    gp("set term postscript color 18")
    gp("set output '"+src+str(v_int)+"/diff_files/"+"s_low_plot_"+str(eq_step)+"_"+str(i)+".ps'")
    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel)+"' u 1:2:3 with errorbars , a(x),b(x),a(x)+b(x)")
#    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e_all' u 1:2:3 with errorbars , a(x),b(x),a(x)+b(x)")

    gp("sa = "+str(a[l-1,7]))
    gp("sb = "+str(b[l-1,7]))

    gp("set xrange["+str(pr_low)+":"+str(pr_high)+"]")
    gp("set term postscript color 18")
    gp("set output '"+src+str(v_int)+"/diff_files/"+"s_low_plot_"+str(eq_step)+"_"+str(i)+".ps'")
    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel)+"' u 1:2:3 with errorbars , a(x),b(x),a(x)+b(x)")
#    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e_all' u 1:2:3 with errorbars , a(x),b(x),a(x)+b(x)")

    gp("sa = "+str(a[l-1,6]))
    gp("sb = "+str(b[l-1,6]))

    gp("set xrange["+str(pr_low)+":"+str(pr_high)+"]")
    gp("set term postscript color 18")
    gp("set output '"+src+str(v_int)+"/diff_files/"+"s_high_plot_"+str(eq_step)+"_"+str(i)+".ps'")
    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e"+str(echannel)+"' u 1:2:3 with errorbars , a(x),b(x),a(x)+b(x)")
#    gp("plot '"+src+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(eq_step)+"_e_all' u 1:2:3 with errorbars , a(x),b(x),a(x)+b(x)")

    filex=open(src+str(v_int)+"/diff_files/"+"diff_"+str(eq_step)+"_"+str(i),"w")
    for j in range(pr_low,pr_high):
#        print j, ap(float(j),a[l-1,2],a[l-1,0],a[l-1,1]), bp(float(j),b[l-1,2],b[l-1,0],b[l-1,1]), data[l-1,j-1,1], data[l-1,j-1,1]-(ap(float(j),a[l-1,2],a[l-1,0],a[l-1,1])+bp(float(j),b[l-1,2],b[l-1,0],b[l-1,1])), data[l-1,j-1,2]
        filex.write(str(j))
        filex.write("   ")
        filex.write(str(ap(float(j),a[l-1,2],a[l-1,0],a[l-1,1])))
        filex.write("   ")
        filex.write(str(bp(float(j),b[l-1,2],b[l-1,0],b[l-1,1])))
        filex.write("   ")
        filex.write(str(data[l-1,j-1,1]))
        filex.write("   ")
        filex.write(str(data[l-1,j-1,1]-(ap(float(j),a[l-1,2],a[l-1,0],a[l-1,1])+bp(float(j),b[l-1,2],b[l-1,0],b[l-1,1]))))
        filex.write("   ")
        filex.write(str(data[l-1,j-1,1]-(ap(float(j),a[l-1,2],a[l-1,0],a[l-1,6])+bp(float(j),b[l-1,2],b[l-1,0],b[l-1,6]))))
        filex.write("   ")
        filex.write(str(data[l-1,j-1,1]-(ap(float(j),a[l-1,2],a[l-1,0],a[l-1,7])+bp(float(j),b[l-1,2],b[l-1,0],b[l-1,7]))))
        filex.write("   ")
        filex.write(str(data[l-1,j-1,2]))
        filex.write("\n")
    filex.close()

filey=open(src+str(v_int)+"/fit_results/"+"res_c12_"+str(eq_step),"w")
filey.write("# x-pos   sigma   Höhe   x-pos_m   x-pos_p   x_pos_ave   sigma_m   sigma_p   sigma_ave   Höhe_m   Höhe_p   Höhe_ave")
filey.write("\n")
for i in range(l):
    filey.write(str(echannelarray[i]))
    filey.write("   ")
    for kk in range(12):
        filey.write(str(a[i,kk]))
        filey.write("   ")
    filey.write("\n")
filey.close()

filez=open(src+str(v_int)+"/fit_results/"+"res_o7_"+str(eq_step),"w")
filez.write("# x-pos   sigma   Höhe   x-pos_m   x-pos_p   x_pos_ave   sigma_m   sigma_p   sigma_ave   Höhe_m   Höhe_p   Höhe_ave")
filez.write("\n")
for i in range(l):
    filez.write(str(echannelarray[i]))
    filez.write("   ")
    for kk in range(12):
        filez.write(str(b[i,kk]))
        filez.write("   ")
    filez.write("\n")
filez.close()



for i in range(2):
    am[i]=asum[i]/l
    bm[i]=bsum[i]/l
    cm[i]=csum[i]/l
    dm[i]=dsum[i]/l
    amw[i]=asumw[i]/asum[2]
    bmw[i]=bsumw[i]/bsum[2]
    cmw[i]=csumw[i]/csum[2]
    dmw[i]=dsumw[i]/dsum[2]

#print "A =", A
#print "B =", B
#print "C =", C
#print "D =", D
print "xa =", am[0], "  ", amw[0]
print "xb =", bm[0], "  ", bmw[0]
#print "xc =", cm[0], "  ", cmw[0]
print "xd =", dm[0], "  ", dmw[0]
print "sa =", am[1], "  ", amw[1]
print "sb =", bm[1], "  ", bmw[1]
#print "sc =", cm[1], "  ", cmw[1]
print "sd =", dm[1], "  ", dmw[1]
