#!/usr/bin/python
from numpy import float


def writefluxheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\typos\tsigxp\tsigxm\tsigyp\tsigym\tvel\tmass\tcharge\t\tpeakh\t\tnormh\t\tflux\t\tdens\n")

def writefluxion(file,iondata):
    file.write("%s\t\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.2f\t\t%.2f\t\t%.4e\t%.4e\n" %(iondata[0],iondata[1],iondata[2],iondata[3],iondata[4],iondata[5],iondata[6],iondata[7],iondata[8],iondata[9],iondata[10],iondata[11],iondata[12],iondata[13]))

def writeflux(data,filename):
    fluxfile=open(filename,"w")
    for step in range(len(data)):
        writefluxheader(fluxfile,len(data[step]),step+1)
        for ion in range(len(data[step])):
            writefluxion(fluxfile,data[step][ion])

def writeres(vdfval,filename):
    resfile=open(filename,"w")
    resfile.write("Ion\t\tVelocity\tMaxVel\t\tTemp\t\t\tFlux\t\t\tNumFlux\t\t\tDens\t\t\tNumDens\n") 
    for ion in range(len(vdfval)):
        resfile.write("%s\t\t%.2f\t\t%.2f\t\t%.4e\t\t%.4e\t\t%.4e\t\t%.4e\t\t%.4e\n" %(vdfval[ion][0],vdfval[ion][1],vdfval[ion][2],vdfval[ion][3],vdfval[ion][4],vdfval[ion][5],vdfval[ion][6],vdfval[ion][7]))
    resfile.close()

def writeelem(elemarr,filename):
    elemfile=open(filename,"w")
    elemfile.write("Element\t\tFlux\t\tNumFlux\t\tDens\t\tNumDens\t\tTfreez\t\tNumTfreez\tMeanCharge\tNumMCh\n") 
    for elem in range(len(elemarr)):
        elemfile.write("%s\t\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.2f\t\t%.2f\n" %(elemarr[elem][0],elemarr[elem][1],elemarr[elem][2],elemarr[elem][3],elemarr[elem][4],elemarr[elem][5],elemarr[elem][6],elemarr[elem][7],elemarr[elem][8]))
    elemfile.close()
    print globals()["test"]
