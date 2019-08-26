#!/usr/bin/python
from scipy import zeros, Float

# Program to remove a single element from given parameter file


neq=60
delname=""
nelem=zeros([neq])
delline=0

print "Be careful edited file will be changed permanently -> user has to make a backup!" 
filename = raw_input("Enter Name of file: ")
delname = raw_input("Enter Name of Element to remove : ")

f=open(filename)

cfile=open("tmp2.dat", "w")


for step in range(neq):
    s=f.readline()
    k=s.split()
    nelem[step]=int(k[5])
    header=f.readline()
    for elem in range(nelem[step]):
        s=f.readline()
        k=s.split()
        if (k[0]==delname):
            nelem[step]=nelem[step]-1
            delline+=1
        else:
            cfile.write(s)
        
cfile.close()
f.close()
f=open("tmp2.dat")
cfile=open(filename, "w")
for step in range(neq):
    line1 = "Step : " + str(step+1) + "  Numberions = " + str(nelem[step])
    cfile.write(line1)
    cfile.write("\n")
    cfile.write(header)
    for elem in range(nelem[step]):
        s=f.readline()
        cfile.write(s)
    
cfile.close()
f.close()
rm tmp2.dat

if (delline>0):
    print delname,"has been removed from",filename,"!"
    print delline, "lines have been deleted"
else:
    print "No occurences of element",delname,"found."
    print filename,"has not been modified!"
    
