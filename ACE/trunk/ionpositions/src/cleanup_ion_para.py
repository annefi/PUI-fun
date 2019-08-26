#!/usr/bin/python
from scipy import zeros

def writeheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\typos\tsigxp\tsigxm\tsigyp\tsigym\tvel\tmass\tcharge\t\tpeakhigh\n")

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh):
    file.write("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh))

paraname="ion_para_new.dat"
paraoutname="ion_para_new_clean.dat"

dim=58
vellimit=200.
echlimit=6.
echlimit2=127.
peakhlimit=-1.
dirtboxx=220.
dirtboxy=12.
filter_arr=[300,300,300,300,300,300,300,300,300,300,310,320,320,295,300,305,310,315,320,290,295,300,300,305,310,310,315,320,320,320,300,305,305,305,305,305,305,305,305,305,290,280,260,255,240,240,240,240,240,240,220,220,220,220,220,220,220,220]
path="/home/ivar/berger/projects/ionpositions/paramfiles/"

f=open(path+paraname)

numionstrue=zeros([dim])

for i in range(dim):
    s=f.readline()
    header=s.split()
    numions=int(header[5])
    s=f.readline()
    for j in range(numions):
        s=f.readline()
        line=s.split()
        if ((float(line[7])>=vellimit)and(float(line[2])>=echlimit)and(float(line[2])<=echlimit2)and(float(line[10])>peakhlimit)and not((float(line[2])<dirtboxy)and(float(line[1])>dirtboxx))and(float(line[1])<float(filter_arr[i]))):
            numionstrue[i]+=1.
f.close()

f=open(path+paraname)
w=open(path+paraoutname,"w")

for i in range(dim):
    s=f.readline()
    k=s.split()
    s=f.readline()
    writeheader(w,int(numionstrue[i]),i+1)
    for j in range(int(k[5])):
        s=f.readline()
        line=s.split()
        if ((float(line[7])>=vellimit)and(float(line[2])>=echlimit)and(float(line[2])<=echlimit2)and(float(line[10])>peakhlimit)and not((float(line[2])<dirtboxy)and(float(line[1])>dirtboxx))and(float(line[1])<float(filter_arr[i]))):
            if (line[0]=="H+"):
                line[0]="H1+"
            if (line[0]=="20Ne6+"):
                line[0]="Ne6+"
            if (line[0]=="20Ne7+"):
                line[0]="Ne7+"
            if (line[0]=="20Ne8+"):
                line[0]="Ne8+"
            if (line[0]=="20Ne9+"):
                line[0]="Ne9+"
            if (line[0]=="20Ne10+"):
                line[0]="Ne10+"
            for l in range(4):
                if (float(line[3+l])<1.5):
                    line[3+l]="1.5"

            writeion(w,line[0],float(line[1]),float(line[2]),float(line[3]),float(line[4]),float(line[5]),float(line[6]),float(line[7]),float(line[8]),float(line[9]),float(line[10]))
f.close()
w.close()
