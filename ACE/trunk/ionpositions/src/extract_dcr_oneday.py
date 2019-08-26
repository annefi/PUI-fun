from os import system
from libacepy.extractdcr import extractdcr

liste=open("list.in")
liste.readline()

for filename in liste:
    k=filename.split()
    dcr=extractdcr(k[0])
    system("rm %s\n"%(k[0]))

system("rm axlv2*")
system("rm run-axlv2-many.pl")
