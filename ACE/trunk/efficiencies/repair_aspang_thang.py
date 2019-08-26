from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from Gnuplot import Gnuplot, GridData
from os import popen2
from numpy import float
from tempfile import mkstemp

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

data=zeros([961,4],Float)


for aspang in range(3,16):
    for thang in range(0,18):
        file0=open("aspang_thang_old/aspang_"+str(aspang)+"_thang_"+str(thang))
        l=0
        for i in file0:
            t=i.split()
            for k in range(4):
                data[l,k]=float(t[k])
            l+=1

        print data

        file1=open("aspang_thang/aspang_"+str(aspang)+"_thang_"+str(thang),"w")
        for i in range(31):
            for j in range(31):
                for k in range(4):
                    file1.write(str(data[j*31+i,k]))
                    file1.write("  ")
                file1.write("\n")