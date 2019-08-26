#!/usr/bin/python
from scipy import zeros

def writeheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\typos\tsigxp\tsigxm\tsigyp\tsigym\tvel\tmass\tcharge\t\tpeakhigh\n")

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh):
    file.write("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh))


dim=58
vellimit=200.
echlimit=6.

f=open("/home/ivar/berger/projects/ionpositions/ion_pos_41.dat")

numionstrue=zeros([dim])

for i in range(dim):
    s=f.readline()
    header=s.split()
    numions=int(header[6])
    s=f.readline()
    for j in range(numions):
        s=f.readline()
        line=s.split()
        if ((float(line[7])>=vellimit)and(float(line[2])>=echlimit)):
            numionstrue[i]+=1.
    s=f.readline()
f.close()

f=open("/home/ivar/berger/projects/ionpositions/ion_pos_41.dat")
w=open("/home/ivar/berger/projects/ionpositions/ion_pos_41_clean.dat","w")

for i in range(dim):
    s=f.readline()
    k=s.split()
    s=f.readline()
    writeheader(w,numionstrue[i],i+1)
    for j in range(int(k[6])):
        s=f.readline()
        line=s.split()
        if ((float(line[7])>=vellimit)and(float(line[2])>=echlimit)):
            writeion(w,line[0],float(line[1]),float(line[2]),float(line[3]),float(line[4]),float(line[5]),float(line[6]),float(line[7]),float(line[8]),float(line[9]),float(line[10]))
    s=f.readline()
    w.write(s)
f.close()
w.close()
