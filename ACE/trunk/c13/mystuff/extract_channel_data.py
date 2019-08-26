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


edata=zeros([128],Float)
edata=zeros([512],Float)
data=zeros([128,512],Float)
esumdata=zeros([512],Float)
tsumdata=zeros([128],Float)

v_int="375"
timespan="all"
#timespan="2007"
for v in range(345,360,10):
    v_int=str(v)
    for step in range(60):
        print v_int, step
        file0=open("/data/kleopatra/mu/jahresdaten/"+timespan+"_data/step_files/"+v_int+"_he/step_"+str(step))
        l=0
        m=0
        for j in file0:
            t=j.split()
            for k in [2]:
                data[l,m]=float(t[k])
            m+=1
            if (m==512):
                l+=1
                m=0
        file0.close()
    
        for echannel in range(128):
            file1=open("/data/kleopatra/mu/jahresdaten/"+timespan+"_data/step_files/"+v_int+"_he/e_files/"+v_int+"_step_"+str(step)+"_e"+str(echannel+1),"w")
            for i in range(512):
                file1.write(str(i+1))
                file1.write("   ")
                file1.write(str(data[echannel,i]))
                file1.write("   ")
                if (int(data[echannel,i]) == 0):
                    file1.write("1.0")
                if (int(data[echannel,i]) > 0):
                    file1.write(str((data[echannel,i])**0.5))
                file1.write("\n")
            file1.close()
    
        for tchannel in range(512):
            file2=open("/data/kleopatra/mu/jahresdaten/"+timespan+"_data/step_files/"+v_int+"_he/t_files/"+v_int+"_step_"+str(step)+"_t"+str(tchannel+1),"w")
            for i in range(128):
                file2.write(str(i+1))
                file2.write("   ")
                file2.write(str(data[i,tchannel]))
                file2.write("   ")
                if (int(data[i,tchannel]) == 0):
                    file2.write("1.0")
                if (int(data[i,tchannel]) > 0):
                    file2.write(str((data[i,tchannel])**0.5))
                file2.write("\n")
            file2.close()
    
#    for tchannel in range(512):
#        esumdata[tchannel]=0.0
#    for echannel in range(128):
#        tsumdata[echannel]=0.0
#    for tchannel in range(512):
#        for echannel in range(10,35):
#            esumdata[tchannel]+=data[echannel,tchannel]
#    for echannel in range(128):
#        for tchannel in range(160,170):
#            tsumdata[echannel]+=data[echannel,tchannel]
    """
    file3=open("/data/kleopatra/mu/jahresdaten/"+timespan+"_data/step_files/"+v_int+"/e_files/"+v_int+"_step_"+str(step)+"_e_20_25","w")
#    file3=open(timespan+"_data/step_files/"+v_int+"/e_files/"+v_int+"_step_"+str(step)+"_e_20_25","w")
    for tchannel in range(512):
        file3.write(str(tchannel+1))
        file3.write("   ")
        file3.write(str(esumdata[tchannel]))
        file3.write("   ")
        if (int(esumdata[tchannel]) == 0):
            file3.write("1.0")
        if (int(esumdata[tchannel]) > 0):
            file3.write(str((esumdata[tchannel])**0.5))
        file3.write("\n")
    file3.close()
    """
#    file4=open("/data/kleopatra/mu/jahresdaten/"+timespan+"_data/step_files/"+v_int+"/t_files/"+v_int+"_step_"+str(step)+"_t_10_35_160_170","w")
#    file4=open(timespan+"_data/step_files/"+v_int+"/t_files/"+v_int+"_step_"+str(step)+"_t_all","w")
#    for echannel in range(128):
#        file4.write(str(echannel+1))
#        file4.write("   ")
#        file4.write(str(tsumdata[echannel]))
#        file4.write("   ")
#        if (int(tsumdata[echannel]) == 0):
#            file4.write("1.0")
#        if (int(tsumdata[echannel]) > 0):
#            file4.write(str((tsumdata[echannel])**0.5))
#        file4.write("\n")
#    file4.close()
    