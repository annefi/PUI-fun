 
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
data3=zeros([51,60,128,512],Float)

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
#Dieser Teil dient dazu, das Geschwindigkeitsintervall zu finden, das am häufigsten auftritt
"""

for k in range(50):
    j=0
#    for i in range(8753):#(2007)
#    for i in range(8446):#(2006)
    for i in range(8568):#(2001)
#    for i in range(8223):#(2004)
        if not ((data[i][2][3][0]) == "C6+"):
            print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
        if (((data[i][2][3][1][0]) > (300.+k*10.)) and ((data[i][2][3][1][0]) < (300+(k+1)*10.))):
#            print i, data[i][2][3][1][0]
            j+=1
    print (300.+k*10.), (300+(k+1)*10.), j
"""


# bd = broken days (hier existieren weder res_files noch ein list.in file)
bd_2001=[37,38,205,206,207]
bd_2002=[1,2]
bd_2003=[]
bd_2004=range(101,120)+[137,138]
bd_2005=[]
bd_2006=[346]
bd_2007=[]


# bbrd = broken but repairable days (hier stimmen tatsächliche anzahl der res_files nicht mit der in list.in überein)
bbrd_2001=[]
bbrd_2002=[331,332,333,340,341,343,344,353,356,357,358,359,360,361]
bbrd_2003=[18,19,31,169,175,188,228,230,236,281,304,335]
bbrd_2004=[140]
bbrd_2005=[37,38,42,46,52,56,61,62,63,104,123,129,134,192,230,237,249,258,269,271,274,282,286,310]
bbrd_2006=[]
bbrd_2007=[]

# norf = number of res files on the respective  broken but repairable days

norf_2001=[]
norf_2002=[0,2,1,23,0,1,1,9,1,1,1,1,1,1]
norf_2003=[5,4,23,12,4,12,15,12,3,5,25,19]
norf_2004=[16]
norf_2005=[7,0,3,8,12,22,15,12,14,2,19,9,1,18,23,17,0,10,17,18,7,3,1,4]
norf_2006=[]
norf_2007=[]

years=range(2006,2008)

for year_int in years:
    year=str(year_int)
    data2=[]
    names=[]
    data3=zeros([51,60,128,512],Float)
    import cPickle
    data=cPickle.load(open("cPickle_files/res_"+year+".dat", "rb")) 


    system("rm list.in")
    system("rm axlv2_et_slices*.dat")
    counter=int(0.0)
    if (year == "2001"):
        bd=bd_2001
        bbrd=bbrd_2001
        norf=norf_2001
    if (year == "2002"):
        bd=bd_2002
        bbrd=bbrd_2002
        norf=norf_2002
    if (year == "2003"):
        bd=bd_2003
        bbrd=bbrd_2003
        norf=norf_2003
    if (year == "2004"):
        bd=bd_2004
        bbrd=bbrd_2004
        norf=norf_2004
    if (year == "2005"):
        bd=bd_2005
        bbrd=bbrd_2005
        norf=norf_2005
    if (year == "2006"):
        bd=bd_2006
        bbrd=bbrd_2006
        norf=norf_2006
    if (year == "2007"):
        bd=bd_2007
        bbrd=bbrd_2007
        norf=norf_2007
    if (1 == 1):
        kt=0
        for z in range(365):
            if z+1 in bbrd:
                counter=counter+norf[kt]
                kt+=1
            if not ((z+1 in bd) or (z+1 in bbrd)):
                print "Tag ",z+1
    
                if (z < 9):
                   day="00"+str(z+1)
                if ((z >= 9) and (z < 99)):
                    day="0"+str(z+1)
                if (z >= 99):
                    day=str(z+1)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                #system("(echo axlv2_et_slices_*|wc -w;ls -1 axlv2_et_slices_*) > list.in") # das und 
                #listin=open("list.in") # das und den mv befehl weiter unten einschaten wenn die listinfiles noch nicht existieren
                listin=open(year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in") # das einschalten, wenn die listin files existieren
                s=0
                names=[]
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                #system("mv list.in "+year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in")
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    if not ((data[y][2][0][0]) == "He2+"):
                        print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
                    for va in range(51):
                        if (((data[y][2][0][1][0]) > (340.+va*10)) and ((data[y][2][0][1][0]) < (340.+(va+1)*10))):
                            file=open(names[u])
                            i=0
                            l=0
                            for j in file:
                                x=j.split()
                                if (i > 5):
                                    if ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        l+=1
                                        i=5
                                    if not ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        for k in range(512):
                                            data3[va,l,i-6,k]+=float(x[k])
                                i+=1
                            file.close()
                    u+=1
                system("rm axlv2_et_slices_*.dat")

        for va in range(51):
            v_int=str(345+va*10)
            #system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
