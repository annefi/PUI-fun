 
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan
from os import popen2

Float=float
matrixmultiply=dot

data2=[]
names=[]
data3=zeros([60,128,512],Float)

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

year="2007"

import cPickle
data=cPickle.load(open("res_"+year+".dat", "rb")) 

#Dieser Teil dient dazu, das Geschwindigkeitsintervall zu finden, der am häufigsten auftritt
"""
for k in range(50):
    j=0
    for i in range(4726):
        if not ((data[i][2][3][0]) == "C6+"):
            print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
        if (((data[i][2][3][1][0]) > (300.+k*10.)) and ((data[i][2][3][1][0]) < (300+(k+1)*10.))):
#            print i, data[i][2][3][1][0]
            j+=1
    print (300.+k*10.), (300+(k+1)*10.), j
"""

for z in range(3,4):
    if (z < 9):
        day="00"+str(z+1)
    if ((z > 9) and (z < 99)):
        day="0"+str(z+1)
    if (z > 99):
        day=str(z+1)
#    print day

    system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1d --config_file='axlv2.in'")
    system("(echo axlv2_et_slices_*|wc -w;ls -1 axlv2_et_slices_*) > list.in ")
    
    listin=open("list.in")
    s=0
    for w in listin:
        v=w.split()
        if (s > 0):
            names+=v
        s+=1
    print names
    system("rm list.in")
    u=0
    for y in range(z*24,(z+1)*24):
        if not ((data[y][2][3][0]) == "C6+"):
            print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
#        if (((data[y][2][3][1][0]) > (340.)) and ((data[y][2][3][1][0]) < (350.))):
        if (1==1):
            file=open(names[u])
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
#                            print i,l, float(x[k])
                            data3[l,i-6,k]+=float(x[k])
                i+=1
            file.close()
        u+=1


for i in range(60):
    file2=open("step_"+str(i),"w")
    for j in range(128):
        for k in range(512):
            file2.write(str(j+1))
            file2.write("   ")
            file2.write(str(k+1))
            file2.write("   ")
            file2.write(str(data3[i,j,k]))
            file2.write("\n")
    file2.close()
