from decoded import *
from bittools import *
from expand import expand
from Scientific.IO import NetCDF

phas=[]
for doy in range(365,366):
    filein=NetCDF.NetCDFFile("/data/ivar/berger/acedata/2007/2006%.3i.nc"%(doy),"r")
    cyc=filein.variables['cyc'][:]
    #cyc=vectorize(uint8)(cyc)
    cyc2=cyc.view(uint8)
    QAC=filein.variables["QAC"][:]
    time=filein.variables["time"][:]
    #expcyc=SBCYC()
    #expand(cyc2[0],time[0],QAC[0],expcyc)

    for i in range(120,121):
        try :
            expcyc=SBCYC()
            expand(cyc2[i],time[i],QAC[i],expcyc)
            print "Doy,EDB : "+str(doy)+","+str(i)
            for step in range(60):
                for nrpha in range(expcyc.asxNof[step]):
                    phas.append([step,expcyc.asxtof[step,nrpha],expcyc.abxesd[step,nrpha],expcyc.abxdid[step,nrpha],expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha],expcyc.afxmas[step,nrpha],expcyc.afxmoq[step,nrpha],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],8],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha]]])
        except :
            print "Doy,EDB : "+str(doy)+","+str(i), "NO DATA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
            
step = 0
tof = 1
esd = 2
did = 3
rng = 4
sec = 5
mas = 6
moq = 7
twgt = 8
swgt = 9
phas=array(phas)
