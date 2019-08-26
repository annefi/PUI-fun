 
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


for yearfloat in [2001,2002,2004,2006,2007]:
    year=str(yearfloat)
#    year="bla"
    data2=[]
    names=[]
    heh_data=[]
    heh_data_2=[]
    data3=zeros([51,60,128,512],Float)
    import cPickle
    data=cPickle.load(open("cPickle_files/res_"+year+".dat", "rb")) 

    file0=open("/data/zechine/rodde/ACE_MAG/ACE_SW_"+year+"_ges")
#    file0=open("/data/zechine/rodde/ACE_MAG/ACE_SW_2001_ges")
    l=0
    for i in file0:
        sw=i.split()
        heh_data+=[float(sw[3])]
        l+=1

    dummy=0.
    counter=0.
    for i in range(l):
        if (abs(heh_data[i]) < 1.):
            dummy+=heh_data[i]
            counter+=1
        if (((i+1) % 5) == 0):
            if (counter > 0.):
                heh_data_2+=[dummy/counter]
            else:
                heh_data_2+=[0]
            dummy=0.
            counter=0.
    file0.close()

    system("rm list.in")
    system("rm axlv2_et_slices*.dat")
    counter=int(0.0)
    if (year == "2001"):
        kk=0
        for z in range(365):
            if (((z>=204) and (z<=206)) or (z==36) or (z==37)):#(2001)
                kk+=24
            if not (((z>=204) and (z<=206)) or (z==36) or (z==37)):#(2001)
                print "Tag ",z+1
    
                if (z < 9):
                   day="00"+str(z+1)
                if ((z >= 9) and (z < 99)):
                    day="0"+str(z+1)
                if (z >= 99):
                    day=str(z+1)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    for va in range(51):
                        if ((heh_data_2[kk] > (va*0.005)) and (heh_data_2[kk] < ((va+1)*0.005))):
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
                system("rm axlv2_et_slices_"+year+"*.dat")
                kk+=1

        for va in range(51):
            heh_ratio=str(va*0.005)+"_"+str((va+1)*0.005)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
    if (year == "2002"):
        kk=0
        for z in range(365):
            if (z==331):#(2002) am tag 332 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
                counter=counter+2#(2002) anzahl res_files=2, list.in sagt 24
            if (z==332):#(2002) am tag 333 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
                counter=counter+1#(2002) anzahl res_files=1, list.in sagt 24
            if (z==339):#(2002) am tag 340 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
                counter=counter+23#(2002) anzahl res_files=23, list.in sagt 24

            if ((z==0) or (z==1) or (z==330) or (z==331) or (z==332) or (z==339) or (z==340) or ((z>=342) and (z<=361))):#(2002)
                kk+=24

            if not ((z==0) or (z==1) or (z==330) or (z==331) or (z==332) or (z==339) or (z==340) or ((z>=342) and (z<=361))):#(2002)
        #        #die restlichen tage, die ausgelassen wurden, sind nicht vorhanden, enthalten also weder res_files noch list.in_files
                print "Tag ",z+1
    
                if (z < 9):
                   day="00"+str(z+1)
                if ((z >= 9) and (z < 99)):
                    day="0"+str(z+1)
                if (z >= 99):
                    day=str(z+1)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    for va in range(51):
                        if ((heh_data_2[kk] > (va*0.005)) and (heh_data_2[kk] < ((va+1)*0.005))):
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
                system("rm axlv2_et_slices_"+year+"*.dat")
                kk+=1

        for va in range(51):
            heh_ratio=str(va*0.005)+"_"+str((va+1)*0.005)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
    if (year == "2004"):
        kk=0
        for z in range(365):
            if (z==139):#(2004) am tag 140 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
                counter=counter+16#(2004)

            if (((z>=100) and (z<=118)) or (z==136) or (z==137) or (z==139)):#(2004)
                kk+=1

            if not (((z>=100) and (z<=118)) or (z==136) or (z==137) or (z==139)):#(2004)
                print "Tag ",z+1
    
                if (z < 9):
                   day="00"+str(z+1)
                if ((z >= 9) and (z < 99)):
                    day="0"+str(z+1)
                if (z >= 99):
                    day=str(z+1)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    for va in range(51):
                        if ((heh_data_2[kk] > (va*0.005)) and (heh_data_2[kk] < ((va+1)*0.005))):
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
                system("rm axlv2_et_slices_"+year+"*.dat")
                kk+=1

        for va in range(51):
            heh_ratio=str(va*0.005)+"_"+str((va+1)*0.005)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
    if (year == "2006"):
        kk=0
        for z in range(358):
            if not (((z>=235) and (z<=238)) or (z==345) or (z==346)):#(2006)
                kk+=1

            if not (((z>=235) and (z<=238)) or (z==345) or (z==346)):#(2006)

                print "Tag ",z+1
    
                if (z < 9):
                   day="00"+str(z+1)
                if ((z >= 9) and (z < 99)):
                    day="0"+str(z+1)
                if (z >= 99):
                    day=str(z+1)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    for va in range(51):
                        if ((heh_data_2[kk] > (va*0.005)) and (heh_data_2[kk] < ((va+1)*0.005))):
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
                system("rm axlv2_et_slices_"+year+"*.dat")
                kk+=1

        for va in range(51):
            heh_ratio=str(va*0.005)+"_"+str((va+1)*0.005)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()

    if (year == "2007"):
        kk=0
        for z in range(365):
            if (1 == 1):#(2007)
                print "Tag ",z+1

                if (z < 9):
                   day="00"+str(z+1)
                if ((z >= 9) and (z < 99)):
                    day="0"+str(z+1)
                if (z >= 99):
                    day=str(z+1)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    for va in range(51):
                        if ((heh_data_2[kk] > (va*0.005)) and (heh_data_2[kk] < ((va+1)*0.005))):
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
                system("rm axlv2_et_slices_"+year+"*.dat")
                kk+=1

        for va in range(51):
            heh_ratio=str(va*0.005)+"_"+str((va+1)*0.005)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+heh_ratio+"_he/step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
