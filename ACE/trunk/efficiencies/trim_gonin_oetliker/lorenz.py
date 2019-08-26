from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from Gnuplot import Gnuplot, GridData
from os import popen2
from numpy import float
from tempfile import mkstemp
from math import sin,cos,tan,asin,acos,atan

Float=float

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

x=zeros([50000,9],Float)
tepe=zeros([100],Float)

mp=open("TRANSMIT_100keV_50000.txt")
l=0
for j in mp:
    t=j.split()
    for k in range(9):
        x[l,k]=float(t[k])
    l+=1


for i in range(50000):
    a=acos(x[i,6])
    for j in range(100):
        if ((a > j*0.001) and  (a <= (j+1)*0.001)):
            tepe[j]=tepe[j]+1

fout=open("test","w")
for i in range(100):
    fout.write(str(float(i)/1000))
    fout.write("   ")
    fout.write(str(tepe[i]/(sin((float(i)+0.5)/1000))))
    fout.write("\n")
fout.close()
