import sys
from scipy import zeros, sqrt,mean
from numpy import float

oldfile = "/data/ivar/berger/testco/ion_para.dat"
newfile = "./new_ion_para.dat"

oldf=open(oldfile)
newf=open(newfile,'w')

# über alle steps
for i in range(58):
    #Kopfzeile einlesen und kopieren
    kopfzeile=oldf.readline()
    newf.writelines(kopfzeile)
    #Kopfzeile auswerten
    k=kopfzeile.split()
    step = float(k[2])
    numpoints1=int(k[5])

    #Spaltenüberschriften kopieren
    ueberschriften = oldf.readline()
    newf.writelines(ueberschriften)

    #über alle (laut kopfzeile) enthaltenen Ionen
    for j in range(numpoints1):
        # Ion-Zeile einlesen und auswerten
        zeile=oldf.readline()
        n=zeile.split()
        
        #alle elemente bis auf das erste in float casten
        m = []
        m.append(n[0])
        for y in range(1,len(n)):
            m.append(float(n[y]))

        mass=float(m[8])
        charge=float(m[9])

        #Energie und ToF transformieren
        m[1] = sqrt(float(m[2])/(float(m[2])-0.42*charge))*float(m[1])+(175-float(m[1]))*(step-25)*0.005
        m[2] = float(m[2])-0.42*charge
        if (step < 20):
            m[1] += 2.5

        #Ion-Zeile formatieren und abspeichern
        newzeile = "%5s\t\t%5.2f\t%5.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%6.2f\t%4.2f\t%4.2f\t\t%4.2f" % (m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10])
        newf.writelines(newzeile + "\n")

oldf.close()
newf.close()
