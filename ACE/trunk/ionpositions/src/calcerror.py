#!/usr/bin/python
from libacepy.lv1data import lv1data
from libacepy.error import error
from scipy import zeros
from numpy import float

class calcerror:
    """ coming soon ... """
   
    def __init__():    
        self.dim=58
        self.listin="erglist.in"
        for step in range(self.dim):
            self.ergdata.append([])
            self.outdata.append([])
            self.ionlist.append([])
            self.countlist.append([])
        self.name=""
        

    def readerg(self):
        listin=open(self.listin)
        for erg in listin:
            tmpdata=error(erg)
            tmpdata.readerrordata()
            tmpdata.calcerror()
            ergdata[tmpdata.step].append(tmpdata)
            self.name=tmpdata.name[0]

    def getoutdata(self):
        for step in range(self.dim):
            for ion in self.ionlist[step]:
                tmpion=[]
                for count in range(len(self.countlist[step])):
                    tmpion.append([ion,0.,0.,0.,0.,0.])
                outdata[step].append(tmpion)
        for step in range(self.dim):
            for erg in self.ergdata[step]:
                for ion in range(len(self.ionlist[step])):
                    for count in range(len(self.countlist[step])):
                        if (erg.name[1]==self.outdata[step][ion][count][0]):
                            if (erg.frac==0.0 and erg.counts==self.countlist[step][count]):
                                self.outdata[step][ion][count][1]=erg.error
                            if (erg.frac==0.1 and erg.counts==self.countlist[step][count]):
                                self.outdata[step][ion][count][2]=erg.error
                            if (erg.frac==1.0 and erg.counts==self.countlist[step][count]):
                                self.outdata[step][ion][count][3]=erg.error
                            if (erg.frac==10.0 and erg.counts==self.countlist[step][count]):
                                self.outdata[step][ion][count][4]=erg.error
                            if (erg.frac==100.0 and erg.counts==self.countlist[step][count]):
                                self.outdata[step][ion][count][5]=erg.error

    def getionlist(self):
        for step in range(self.dim):
            for erg in self.ergdata[step]:
                da=0
                for ion in self.ionlist[step]:
                    if (erg.name[1]==ion):
                        da=1
                if (da==0):
                    ionlist[step].append(erg.name[1])
            
    def getcountlist(self):
        for step in range(self.dim):
            for erg in self.ergdata[step]:
                da=0
                for counts in self.countlist[step]:
                    if (erg.counts==counts):
                        da=1
                if (da==0):
                    countlist[step].append(erg.counts)
        
                
    def writeerrorfile(self):
        self.readerg()
        self.getionlist()
        self.getcountlist()
        self.getoutdata()
        errorfile=open(self.name+".err","w")
        for step in range(self.dim):
            errorfile.write("Step : %i\n" %(step+1))
            for count in range(len(self.countlist[step])):
                errorfile.write("%.1f\n" %(countlist[step][count]))
                errorfile.write("Ion\t0.0\t0.1\t1.0\t10.0\t100.0")
                for ion in range(len(outdata[step])):
                    errorfile.write("%s\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t\n" %(outdata[step][count][0],outdata[step][count][1],outdata[step][count][2],outdata[step][count][3],outdata[step][count][4],outdata[step][count][5]))
        errorfile.close()
                


