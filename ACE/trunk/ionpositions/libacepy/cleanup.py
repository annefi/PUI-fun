# script to cleanup data repository
# ------------ caution ------------
# !!! all axlv2*, analyse*, and reanalyse* files will be deleted !!!
# !!! This means that all remaining E-T slices and the scripts/software for data analysis will be deleted !!! 
# Use only if sure that data analysis is in final stage! If unsure run check_data.py before to check current status of data products!

from os import system
from sys import argv

if (len(argv)==2 and argv[1]=="-h"):
    print "Clean data repository of given days"
    print "Usage : cleanup.py [option(s)] ...[-h | -r] [args]"
    print "Options and arguments:"
    print "-h\t: print this help message and exit"
    print "-r args\t: go to specified days and delete all axlv*, analyse*, and reanalyse* files"  
    print "args\t: res year startdoy stopdoy (e.g. 12m 2008 30 45)"
    exit()
elif len(argv)>1 and argv[1]=="-r" and len(argv)!=6:
    print "Wrong usage : try 'cleanup.py -r resolution year startday stopday' or 'cleanup.py -h' for help"
    exit()
elif len(argv)>1 and argv[1]=="-r" and len(argv)==6:
    resolution=str(argv[2])
    year=int(argv[3])
    startdoy=int(argv[4])
    stopdoy=int(argv[5])
    if (startdoy>stopdoy):
        print "Error : stopdoy should be greater or equal startday!"
        exit()
    if (resolution!="12m" and resolution!="1h" and resolution!="1d"):
        print "Error : resolution should be 12m,1h or 1d"
        exit()
else:
    print "Wrong usage : try 'check_data.py -h' for help" 
    exit()

for doy in range(stopdoy-startdoy+1):
    print "Cleaning %sdata/%i/.3i/"%(resolution,year,doy)
    system("rm -rf %sdata/%i/.3i/axlv2*"%(resolution,year,doy))
    system("rm -rf %sdata/%i/.3i/analyse*"%(resolution,year,doy))
    system("rm -rf %sdata/%i/.3i/reanalyse*"%(resolution,year,doy))
