from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan
from os import popen2

Float=float
matrixmultiply=dot


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


if (1):
    for step in range(60):
        data=zeros([128,512],Float)
        file0=open("/data/wimmer/mu/jahresdaten/all_data/step_files/all/step_"+str(step)+"_o_cme")
        l=0
        m=0
        for j in file0:
            t=j.split()
            if (len(t)>0):
                data[l,m]=float(t[2])
                m+=1
            if (m==512):
                l+=1
                m=0
        file0.close()
        print step, " eingelesen"
        for echannel in range(128):
            file1=open("/data/wimmer/mu/jahresdaten/all_data/step_files/all/e_files/all_step_"+str(step)+"_e"+str(echannel+1),"w")
            for i in range(512):
                file1.write(str(i+1))
                file1.write("   ")
                file1.write(str(data[echannel,i]))
                file1.write("   ")
                if (int(data[echannel,i]) > 0):
                    file1.write(str((data[echannel,i])**0.5))
                else:
                    file1.write("1.0")
                file1.write("\n")
            file1.close()
        print step, " echannel fertig"
        for tchannel in range(512):
            file2=open("/data/wimmer/mu/jahresdaten/all_data/step_files/all/t_files/all_step_"+str(step)+"_t"+str(tchannel+1),"w")
            for i in range(128):
                file2.write(str(i+1))
                file2.write("   ")
                file2.write(str(data[i,tchannel]))
                file2.write("   ")
                if (int(data[i,tchannel]) > 0):
                    file2.write(str((data[i,tchannel])**0.5))
                else:
                    file2.write("1.0")
                file2.write("\n")
            file2.close()
        print step, " tchannel fertig"