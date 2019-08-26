from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData, GnuplotOpts
GnuplotOpts.prefer_fifo_data=False
GnuplotOpts.prefer_inline_data=False
#GnuplotOpts.recognizes_binary_splot=False
from math import sin,cos,tan,asin,acos,atan
from os import popen2
from sys import stdin

Float=float
matrixmultiply=dot


gp=Gnuplot()
gp2=Gnuplot()
gp3=Gnuplot()



data=zeros([10000],Float)
tof=zeros([10000],Float)
tch=zeros([10000],Float)
tof_data=zeros([1024],Float)
tof_data_binned=zeros([512],Float)
ech=zeros([10000],Float)
e_data=zeros([256],Float)
e_data_binned=zeros([128],Float)
ionmass=[4]
im=0
for ion in [2]:
    #for e in [(1.34703+24.868179)*6]:
    #for e in [(1.34703+24.)*2.,(1.34703+24.2)*2.,(1.34703+24.4)*2.,(1.34703+24.6)*2., (1.34703+24.8)*2.,(1.34703+25.)*2., (1.25372+24.)*2.,(1.25372+24.2)*2.,(1.25372+24.4)*2.,(1.25372+24.6)*2., (1.25372+24.8)*2.,(1.25372+25.)*2., (1.16687+24.)*2.,(1.16687+24.2)*2.,(1.16687+24.4)*2.,(1.16687+24.6)*2., (1.16687+24.8)*2.,(1.16687+25.)*2., (1.44729+24.)*2.,(1.44729+24.2)*2.,(1.44729+24.4)*2.,(1.44729+24.6)*2., (1.44729+24.8)*2.,(1.44729+25.)*2., (1.55501+24.)*2.,(1.55501+24.2)*2.,(1.55501+24.4)*2.,(1.55501+24.6)*2., (1.55501+24.8)*2.,(1.55501+25.)*2. ]:
    for e in [50.0]:
        #for thick in [111.0]:
        #for thick in [80.0,90.0,100.0,110.0,120.0,130.0,140.0]:
        for thick in [110.0]:
            tof_data=zeros([1024],Float)
            tof_data_binned=zeros([512],Float)
            e_data=zeros([256],Float)
            e_data_binned=zeros([128],Float)
            file1=open("/home/kleopatra/mu/Desktop/swics/efficiencies/srim/SRIM 2003/dotfiles/"+str(ion)+"_"+str(e)+"_"+str(thick)+".dot")
            l=0
            for i in file1:
                x=i.split()
                if (l > 11):
                    data[l-12]=float(x[2])
                l+=1
            file1.close()
            print ion, ionmass[im], e, thick
            for i in range(10000):
                tof[i]=0.1/((((data[i]/(6.24150974*10.**18.)))*2./(ionmass[im]*1.66053886*10.**-27.)))**0.5*10.**9.
                tch[i]=tof[i]*1024./200.-1
                ech[i]=(data[i]/1000.)*256./610.78-1
                if (tch[i]<1024):
                    tof_data[int(tch[i])]+=1
                if (ech[i]<256):
                    e_data[int(ech[i])]+=1
            tof_data_binned[0]=tof_data[0]
            k=int(1)
            l=int(0)
            for i in range(1,1023):
                tof_data_binned[k]+=tof_data[i]
                l+=1
                if (l == 2):
                    k+=1
                    l=0
            e_data_binned[0]=e_data[0]
            k=int(1)
            l=int(0)
            for i in range(1,255):
                e_data_binned[k]+=e_data[i]
                l+=1
                if (l == 2):
                    k+=1
                    l=0

            file2=open("hst_files/"+str(ion)+"_"+str(ionmass[im])+"_"+str(e)+"_"+str(thick)+".hstt", "w")
            for i in range(1024):
                file2.write(str(i))
                file2.write("   ")
                file2.write(str(tof_data[i]))
                file2.write("   ")
                if ((tof_data[i]) > 0):
                    file2.write(str((tof_data[i])**0.5))
                if ((tof_data[i]) == 0):
                    file2.write(str(1))
                file2.write("\n")
            file2.close()
            file2=open("hst_files/"+str(ion)+"_"+str(ionmass[im])+"_"+str(e)+"_"+str(thick)+"_binned.hstt", "w")
            for i in range(512):
                file2.write(str(i))
                file2.write("   ")
                file2.write(str(tof_data_binned[i]))
                file2.write("   ")
                if ((tof_data_binned[i]) > 0):
                    file2.write(str((tof_data_binned[i])**0.5))
                if ((tof_data_binned[i]) == 0):
                    file2.write(str(1))
                file2.write("\n")
            file2.close()
            file2=open("hst_files/"+str(ion)+"_"+str(ionmass[im])+"_"+str(e)+"_"+str(thick)+".hste", "w")
            for i in range(256):
                file2.write(str(i))
                file2.write("   ")
                file2.write(str(e_data[i]))
                file2.write("   ")
                if ((e_data[i]) > 0):
                    file2.write(str((e_data[i])**0.5))
                if ((e_data[i]) == 0):
                    file2.write(str(1))
                file2.write("\n")
            file2.close()
            file2=open("hst_files/"+str(ion)+"_"+str(ionmass[im])+"_"+str(e)+"_"+str(thick)+"_binned.hste", "w")
            for i in range(128):
                file2.write(str(i))
                file2.write("   ")
                file2.write(str(e_data_binned[i]))
                file2.write("   ")
                if ((e_data_binned[i]) > 0):
                    file2.write(str((e_data_binned[i])**0.5))
                if ((e_data_binned[i]) == 0):
                    file2.write(str(1))
                file2.write("\n")
            file2.close()

    im+=1
