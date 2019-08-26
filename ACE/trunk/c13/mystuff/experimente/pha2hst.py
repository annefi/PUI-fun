from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData

Float=float
matrixmultiply=dot

x=zeros([50000,3],Float)
ech=zeros([256],Float)
tch=zeros([1024],Float)
data=zeros([256,1024],Float)

earray=[31,32,33,34,35,36,37,38,39,40]
for k in range(len(earray)):
    print earray[k]
    mp=open("/home/kleopatra/mu/daten/giessen/swxli"+str(earray[k])+".pha")
    zz=0
    l=0
    for j in mp:
        t=j.split()
        if (zz > 2):
            for i in range(3):
                x[l,i]=float(t[i])
            l+=1
        zz+=1
#    for i in range(l):
#        print i
#        for j in range(256):
#            if (int(x[i,0]) == int(j)):
#                ech[j]+=1
#        for j in range(1024):
#            if (int(x[i,0]) <> 0):
#                if (int(x[i,1]) == int(j)):
#                    tch[j]+=1

#    fout=open("swxli"+str(earray[k])+".mu.hst", "w")
#    for i in range(1024):
#        fout.write("%f\t" % i)
#        fout.write("  ")
#        fout.write("%f\t" % tch[i])
#        fout.write("\n")
#    fout.close()

    for i in range(l):
        data[int(x[i,0]),int(x[i,1])]+=1


#    for i in range(256):
#        fout=open("e_files/swxli"+str(earray[k])+"_e"+str(i), "w")
#        for j in range(1024):
#            fout.write(str(j))
#            fout.write("   ")
#            fout.write(str(data[i,j]))
#            fout.write("\n")
#        fout.close()

#    for i in range(1024):
#        fout=open("t_files/swxli"+str(earray[k])+"_t"+str(i), "w")
#        for j in range(256):
#            fout.write(str(j))
#            fout.write("   ")
#            fout.write(str(data[j,i]))
#            fout.write("\n")
#        fout.close()

    fout=open("matrices/swxli"+str(earray[k])+"_matrix", "w")
    for i in range(256):
        for j in range(1024):
            fout.write(str(i))
            fout.write("   ")
            fout.write(str(j))
            fout.write("   ")
            fout.write(str(data[i,j]))
            fout.write("\n")
    fout.close()