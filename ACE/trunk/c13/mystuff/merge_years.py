#!/usr/bin/python
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan,pi,exp
from os import popen2
from libacepy.frange import frange
Float=float
matrixmultiply=dot

data_all=zeros([65536],Float)

gdata=zeros([10,2])
n=zeros([365],Float)


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

y=[2001,2002,2003,2004,2005,2006,2007]
#v_int_array=frange(0.0,0.25,0.005)
v_int_array=range(345,850,10)
for v in v_int_array:
    v_int=str(v)
    #v_int_2=str(v+0.005)
    #system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_"+v_int_2+"_he")
    #system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_"+v_int_2+"_he/e_files")
    #system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_"+v_int_2+"_he/t_files")
    #system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_"+v_int_2+"_he/diff_files")
    #system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_"+v_int_2+"_he/fit_results")
    system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_he")
    system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_he/e_files")
    system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_he/t_files")
    system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_he/diff_files")
    system("mkdir /data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_he/fit_results")
    for step in range(60):
        for i in range(65536):
            data_all[i]=0.0
        for year in y:
            print v_int, year, step
            file1=open("/data/wimmer/mu/jahresdaten/"+str(year)+"_data/step_files/"+v_int+"_he/step_"+str(step)+"_o_cme")
            #file1=open(src+v_int+"/step_"+str(step))
            l=0
            for i in file1:
                x=i.split()
                if (len(x)>0):
                    data_all[l]+=float(x[2])
                    l+=1
            file1.close()


        file2=open("/data/wimmer/mu/jahresdaten/all_data/step_files/"+v_int+"_he/step_"+str(step)+"_o_cme","w")
        l=0
        for i in range(128):
            for j in range(512):
                file2.write(str(i+1))
                file2.write("   ")
                file2.write(str(j+1))
                file2.write("   ")
                file2.write(str(data_all[l]))
                file2.write("   ")
                if (data_all[l]>0.):
                    file2.write(str((data_all[l])**0.5))
                else:
                    file2.write("1")
                file2.write("\n")
                l+=1
            file2.write("\n")
        file2.close()

"""
t=[]
ns=0.0
#src="/data/zechine/ace/1hdata/2004/"
#src="/data/kleopatra/ace/1hdata/2007/"
src="/data/wimmer/ace/1hdata/2002/"
for i in range(365):
#    if not ((i==136) or (i==137) or (i==102)):
    if (i==331):#(2002) am tag 332 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
        ns+=2#(2002)
    if (i==332):#(2002) am tag 333 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
        ns+=1#(2002)
    if not ((i==0) or (i==1) or (i==330) or (i==331) or (i==332) or (i==340) or ((i>=342) and (i<=361))):#(2002)


        j=i+1
        if (j < 10):
            day="00"+str(j)
            print day
#            system("ls "+src+day+"|wc")
#            system("wc "+src+day+"/list.in")
            file3=open(src+day+"/list.in")
            l=0
            for k in file3:
                if (l==0):
                    p=k.split()
                    n[i]=float(p[0])
                    ns+=n[i]
                l+=1
            print n[i], ns
            file3.close()
        if ((j >= 10) and j < 100):
            day="0"+str(j)
            print day
#            system("ls "+src+day+"|wc")
#            system("wc "+src+day+"/list.in")
            file3=open(src+day+"/list.in")
            l=0
            for k in file3:
                if (l==0):
                    p=k.split()
                    n[i]=float(p[0])
                    ns+=n[i]
                l+=1
            print n[i], ns
            file3.close()

        if (j >= 100):
            day=str(j)
            print day
#            system("ls "+src+day+"|wc")
#            system("wc "+src+day+"/list.in")
            file3=open(src+day+"/list.in")
            l=0
            for k in file3:
                if (l==0):
                    p=k.split()
                    n[i]=float(p[0])
                    ns+=n[i]
                l+=1
            print n[i], ns
            file3.close()

        t+=day
"""