# abgespeckte version von tof_distribution.py
# dient nur dazu energie-histogramm-files zu bauen uas den pha daten
# gespeichert werden diese in ~/daten/giessen/ und heissen z.B. swxli21.hste
 
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan
from os import popen2
from sys import stdin

Float=float
matrixmultiply=dot


gp=Gnuplot()


xx=zeros([500000,3],Float)
ech=zeros([256],Float)
tch=zeros([1024],Float)
data=zeros([256,1024],Float)
datagrid=None

res=zeros([600,14],Float)
tof_data=zeros([1022,5],Float)
tof_data2=zeros([1022,3],Float)
low=1
high=562
do=int(1)
counter=0



if (1 == 1):

    for n in range(low,high+1):
        print n
        data=zeros([256,1024],Float)
        binned_data=zeros([128,512],Float)
        xx=zeros([500000,3],Float)

        counter+=1
        try:
            file1=open("/home/kleopatra/mu/daten/giessen/swxli"+str(n)+".hst")
        except IOError:
            print "swxli"+str(n)+".hst existiert nicht"
            continue
        l=0
        for i in file1:
            x=i.split()
            if (l > 1):
                for j in range(5):
                    tof_data[l-2,j]=float(x[j])
            l+=1
        file1.close()

        try:
            mp=open("/home/kleopatra/mu/daten/giessen/swxli"+str(n)+".pha")
        except IOError:
            print "swxli"+str(n)+".pha existiert nicht"
            continue

        zz=0
        ll=0
        for jj in mp:
            tt=jj.split()
            if (zz > 2):
                for ii in range(3):
                    xx[ll,ii]=float(tt[ii])
                ll+=1
            zz+=1

        for i in range(ll):
            data[int(xx[i,0]),int(xx[i,1])]+=1
        datagrid=GridData(data)

         


#        fout=open("matrices/swxli"+str(n)+"_matrix", "w")
#        for i in range(256):
#            for j in range(1024):
#                fout.write(str(i))
#                fout.write("   ")
#                fout.write(str(j))
#                fout.write("   ")
#                fout.write(str(data[i,j]))
#                fout.write("\n")
#        fout.close()


        """
        limit1=str(0)
        limit2=str(255)
        limit3=str(0)
        limit4=str(1023)
        ech=zeros([256],Float)
        tch=zeros([1024],Float)
        for i in range(int(limit1),int(limit2)+1):
            for j in range(int(limit3),int(limit4)+1):
                ech[i]+=data[i,j]
                tch[j]+=data[i,j]
        file3=open("/home/kleopatra/mu/daten/giessen/swxli"+str(n)+".hstt","w")
        for i in range(int(limit3),int(limit4)+1):
            file3.write(str(i))
            file3.write("   ")
            file3.write(str(tch[i]))
            file3.write("   ")
            if (int(tch[i]) == 0 ):
                file3.write("1")
            else:
                file3.write(str(tch[i]**0.5))
            file3.write("\n")
        file3.close()
        file4=open("/home/kleopatra/mu/daten/giessen/swxli"+str(n)+".hste","w")
        for i in range(int(limit1),int(limit2)+1):
            file4.write(str(i))
            file4.write("   ")
            file4.write(str(ech[i]))
            file4.write("   ")
            if (int(ech[i]) == 0 ):
                file4.write("1")
            else:
                file4.write(str(ech[i]**0.5))
            file4.write("\n")
        file4.close()
        """

        binned_data[0,0]=data[0,0]
        k=1
        bc=int(0)
        for i in range(1,255):
            binned_data[k,0]+=data[i,0]
            bc+=1
            if (bc == 2):
                bc=0
                k+=1

        k=1
        bc=int(0)
        for i in range(1,1023):
            binned_data[0,k]+=data[0,i]
            bc+=1
            if (bc == 2):
                bc=0
                k+=1

        bc1=int(0)
        bc2=int(0)
        l=1
        k=1
        for i in range(1,255):
            for j in range(1,1023):
                binned_data[k,l]+=data[i,j]
                bc2+=1
                if (bc2 == 2):
                    bc2=0
                    l+=1
            bc1+=1
            l=1
            if (bc1 == 2):
                bc1=0
                k+=1

        fout=open("/data/kleopatra/mu/jahresdaten/matrices/swxli"+str(n)+"_matrix_binned", "w")
        for i in range(128):
            for j in range(512):
                fout.write(str(i))
                fout.write("   ")
                fout.write(str(j))
                fout.write("   ")
                fout.write(str(binned_data[i,j]))
                fout.write("\n")
        fout.close()

        limit1=str(0)
        limit2=str(127)
        limit3=str(0)
        limit4=str(511)
        ech_binned=zeros([128],Float)
        tch_binned=zeros([512],Float)
        for i in range(int(limit1),int(limit2)+1):
            for j in range(int(limit3),int(limit4)+1):
                ech_binned[i]+=binned_data[i,j]
                tch_binned[j]+=binned_data[i,j]
        file3=open("/home/kleopatra/mu/daten/giessen/swxli"+str(n)+"_binned.hstt","w")
        for i in range(int(limit3),int(limit4)+1):
            file3.write(str(i))
            file3.write("   ")
            file3.write(str(tch_binned[i]))
            file3.write("   ")
            if (int(tch_binned[i]) == 0 ):
                file3.write("1")
            else:
                file3.write(str(tch_binned[i]**0.5))
            file3.write("\n")
        file3.close()
        file4=open("/home/kleopatra/mu/daten/giessen/swxli"+str(n)+"_binned.hste","w")
        for i in range(int(limit1),int(limit2)+1):
            file4.write(str(i))
            file4.write("   ")
            file4.write(str(ech_binned[i]))
            file4.write("   ")
            if (int(ech[i]) == 0 ):
                file4.write("1")
            else:
                file4.write(str(ech_binned[i]**0.5))
            file4.write("\n")
        file4.close()
        
        cc=0
        for i in range(255):
            for j in range(1023):
                cc+=data[i,j]
        ccb=0
        for i in range(128):
            for j in range(512):
                ccb+=binned_data[i,j]
        print cc, ccb