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

eff_data=zeros([58,3],Float)
eff_data2=zeros([58,3],Float)
o_data=zeros([58,3],Float)
error=zeros([58],Float)

listmion=["1H","3He","4He","12C","13C","14N","16O","20Ne","24Mg","28Si","32S","40Ca","56Fe"]
listmionraw=["H","3He","He","C","13C","N","O","Ne","Mg","Si","S","Ca","Fe"]
listchargehigh=["1","2","2","6","6","7","8","8","12","12","12","14","26"]
listchargelow=["1","1","1","3","3","4","4","7","5","5","5","6","5"]
#listmion=["4He"]
#listmionraw=["He"]
#listchargelow=["1"]
#listchargehigh=["2"]

#listcharge=["6","8"]
#listmion=["12C","16O"]
for m in range(len(listmionraw)):
        for h in range(int(listchargelow[m])-1,int(listchargehigh[m])):
            stop=0
            dateiname1="tamam_neu/tamam3/"+listmionraw[m]+str(h+1)+"+.eff"
            print dateiname1
            file1=open(dateiname1)
            l=0
            for i in file1:
                data=i.split()
                if not ((float(data[1])) == 0.):
                    for k in range(3):
                        eff_data[l,k]=float(data[k])
                    error[l]=eff_data[l,2]/eff_data[l,1]
                if ((float(data[1])) == 0.):
                    eff_data[l,0]=float(data[0])
                    for k in range(1,2):
                        eff_data[l,k]=0.0
                    error[l]=0.0
                    stop=1
                if (data[1] == "NAN"):
                    eff_data[l,0]=float(data[0])
                    for k in range(1,2):
                        eff_data[l,k]=0.0
                    error[l]=0.0
                    stop=2
                l=l+1
            file1.close()
#            print eff_data

            for zz in range(3,16):
                for yy in range(18):
                    stop=0
                    dateiname2="aspang_"+str(zz)+"/thang_"+str(yy)+"/tamam1/"+listmion[m]+str(h+1)+"+.eff"
                    print dateiname2
                    file2=open(dateiname2)
                    l=0
                    for i in file2:
                        data=i.split()
                        if not ((float(data[1])) == 0.):
                            for k in range(2):
                                eff_data2[l,k]=float(data[k])
                        if ((float(data[1])) == 0.):
                            eff_data2[l,0]=float(data[0])
                            for k in range(1,2):
                                eff_data2[l,k]=0.0
                            stop=1
                        if (data[1] == "NAN"):
                            eff_data2[l,0]=float(data[0])
                            for k in range(1,2):
                                eff_data2[l,k]=0.0
                            stop=2
                        l=l+1
                    file2.close()
#                    print eff_data2
                    dateiname3="aspang_"+str(zz)+"/thang_"+str(yy)+"/tamam3/"+listmionraw[m]+str(h+1)+"+.eff"
                    print dateiname3
                    file3=open(dateiname3,"w")
                    for i in range(58):
                        file3.write(str(eff_data2[i,0]))
                        file3.write("   ")
                        file3.write(str(eff_data2[i,1]))
                        file3.write("   ")
                        file3.write(str(eff_data2[i,1]*error[i]))
                        file3.write("\n")
                    file3.close()
                