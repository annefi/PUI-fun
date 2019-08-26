 
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan
from os import popen2

Float=float
matrixmultiply=dot

data=zeros([60,128,512],Float)

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

#gp=Gnuplot()


#for r in ["axlv2_et_slices_2007_003_00.06.13_2007_004_00.06.13.dat"]:
for r in ["axlv2_et_slices_2007_003_00.06.13_2007_003_01.06.13.dat",
            "axlv2_et_slices_2007_003_01.06.16_2007_003_02.06.16.dat",
            "axlv2_et_slices_2007_003_02.06.18_2007_003_03.06.18.dat",
            "axlv2_et_slices_2007_003_03.06.20_2007_003_04.06.20.dat",
            "axlv2_et_slices_2007_003_04.06.22_2007_003_05.06.22.dat",
            "axlv2_et_slices_2007_003_05.06.24_2007_003_06.06.24.dat",
            "axlv2_et_slices_2007_003_06.06.27_2007_003_07.06.27.dat",
            "axlv2_et_slices_2007_003_07.06.29_2007_003_08.06.29.dat",
            "axlv2_et_slices_2007_003_08.06.31_2007_003_09.06.31.dat",
            "axlv2_et_slices_2007_003_09.06.33_2007_003_10.06.33.dat",
            "axlv2_et_slices_2007_003_10.06.36_2007_003_11.06.36.dat",
            "axlv2_et_slices_2007_003_11.06.38_2007_003_12.06.38.dat",
            "axlv2_et_slices_2007_003_12.06.40_2007_003_13.06.40.dat",
            "axlv2_et_slices_2007_003_13.06.42_2007_003_14.06.42.dat",
            "axlv2_et_slices_2007_003_14.06.44_2007_003_15.06.44.dat",
            "axlv2_et_slices_2007_003_15.06.47_2007_003_16.06.47.dat",
            "axlv2_et_slices_2007_003_16.06.49_2007_003_17.06.49.dat",
            "axlv2_et_slices_2007_003_17.06.51_2007_003_18.06.51.dat",
            "axlv2_et_slices_2007_003_18.06.53_2007_003_19.06.53.dat",
            "axlv2_et_slices_2007_003_19.06.55_2007_003_20.06.55.dat",
            "axlv2_et_slices_2007_003_20.06.58_2007_003_21.06.58.dat",
            "axlv2_et_slices_2007_003_21.07.00_2007_003_22.07.00.dat",
            "axlv2_et_slices_2007_003_22.07.02_2007_003_23.07.02.dat",
            "axlv2_et_slices_2007_003_23.07.04_2007_004_00.07.04.dat"]:
    file=open("../"+r)
    i=0
    l=0
    for j in file:
        x=j.split()
        if (i > 5):
            if ((float(x[0]) == 128) and  (float(x[1]) == 512)):
                l+=1
                i=5
            if not ((float(x[0]) == 128) and  (float(x[1]) == 512)):
                for k in range(512):
#                    print i,l, float(x[k])
                    data[l,i-6,k]+=float(x[k])
        i+=1
    file.close()


for i in range(60):
    file2=open("step_"+str(i),"w")
    for j in range(128):
        for k in range(512):
            file2.write(str(j+1))
            file2.write("   ")
            file2.write(str(k+1))
            file2.write("   ")
            file2.write(str(data[i,j,k]))
            file2.write("\n")
    file2.close()