from os import system
from libacepy.ancil import int2str,getlocaltime
from sys import argv

# check data from given days and write results to check.log file
# usage : check_data.py -help for further information


def check_erg(erg):
    for i in range(51):
        s=erg.readline()
        if (len(s)==0):
            raise Exception
        k=s.split()
        if k[0]=="*****":
            break
    if (i==50):
        raise Exception
    for step in range(58):
        s=erg.readline()
        k=s.split()
        if (int(k[2])!=step+1):
            raise Exception
        nrions=int(k[5])
        for ion in range(nrions+1):
            s=erg.readline()
            if (len(s)==0):
                raise Exception
    s=erg.readline()
    if (len(s)!=0):
        raise Exception
    return True

def check_res(res):
    nrions=0
    s=res.readline()
    if (len(s)==0):
        raise Exception
    k=s.split()
    reflen=len(k)
    if (k[0]!="Ion"):
        raise Exception
    s=res.readline()
    while len(s)!=0:
        k=s.split()
        if (k[0][len(k[0])-1:len(k[0])]!="+" or len(k)!=reflen):
            raise Exception
        nrions+=1
        s=res.readline()
    return nrions

def check_flux(flux,nrions):
    if (nrions==-1):
        raise Exception
    # check if each ion complete
    for ion in range(nrions):
        s=flux.readline()
        if (len(s)==0):
            raise Exception
        k=s.split()
        if (k[0][len(k[0])-1:len(k[0])]!="+"):
            raise Exception
        s=flux.readline()
        s=flux.readline()
        s=flux.readline()
        k=s.split()
        if (k[0]!="vel"):
            raise Exception
        reflen=len(k)
        for step in range(58):
            s=flux.readline()
            k=s.split()
            if (len(k)!=reflen):
                raise Exception
    return True

def recalc_checkday(reextract,reanalyse,recalclv2):
    if (reextract==1):
        return True
    if len(reanalyse)>0:
        return True
    if len(recalclv2)>0:
        return True
    return False

def recalc_reextract(script,res,year,doy,reanalyse):
    command="cp /data/ivar/berger/testco/america/axlv2/tools/run-axlv2-many.pl .\n"
    script.write(command)
    command="cp /data/ivar/berger/testco/america/axlv2/axlv2 .\n"
    script.write(command)
    command="cp /data/ivar/berger/testco/america/axlv2/tools/axlv2.in .\n"
    script.write(command)
    command="./run-axlv2-many.pl %i%.3i --accum=%s --config_file='axlv2.in'\n"%(year,doy,res)
    script.write(command)
    # remove ET-slices of existing erg_* files
    removelist=[]
    liste=open("%sdata/%i/%.3i/list.in"%(res,year,doy))
    liste.readline()
    for s in liste:
        remove=1
        k=s.split()
        for val in reanalyse:
            if val==k[0]:
                remove=0
        if remove:
            command="rm -rf %s\n"%(k[0])
            script.write(command)

def recalc_reanalyse(script,res,year,doy,reanalyse):
    # First copy necessary tools 
    if len(reanalyse)>0:
        command="cp /data/ivar/berger/testco/analyse_data .\n"
        script.write(command)
        command="cp /data/ivar/berger/testco/analyse_data.in .\n"
        script.write(command)
        command="cp /data/ivar/berger/testco/ion_para.dat .\n"
        script.write(command)
        command="cp /data/ivar/berger/testco/src/calcswicslv2.py .\n"
        script.write(command)
    for val in reanalyse:
        script2=open("%sdata/%i/%.3i/reanalyse_%s.sh"%(res,year,doy,val),"w")
        script2.write("#!/bin/bash\n")
        script2.write("./analyse_data %s\n"%(val))
        script2.write("rm %s\n"%(val))
        script2.write("rm reanalyse_%s.sh\n"%(val))
        script2.write("python calcswicslv2.py %s\n"%(val))
        script2.close()
        script.write("chmod u+x reanalyse_%s.sh\n"%(val))
        script.write("qsub -cwd -S /bin/bash -r y -p -512 reanalyse_%s.sh\n"%(val))

def recalc_recalclv2(script,res,year,doy,reanalyse,recalclv2):
    # First copy necessary tools 
    if len(reanalyse)==0:
        command="cp /data/ivar/berger/testco/src/calcswicslv2.py .\n"
        script.write(command)
    for val in recalclv2:
        try:
            open("reanalyse_%s.sh"%(val))
        except:
            script2=open("%sdata/%i/%.3i/reanalyse_%s.sh"%(res,year,doy,val),"w")
            script2.write("#!/bin/bash\n")
            script2.write("python calcswicslv2.py %s\n"%(val))
            script2.write("rm reanalyse_%s.sh\n"%(val))
            script2.close()
            script.write("chmod u+x reanalyse_%s.sh\n"%(val))
            script.write("qsub -cwd -S /bin/bash -r y -p -512 reanalyse_%s.sh\n"%(val))

    
def recalcday(res,year,doy,reextract,reanalyse,recalclv2):
    # build shell script to recalculate missing or incomplete data!

    #print "recalcday : ",res,year,doy,reextract,reanalyse,recalclv2

    if recalc_checkday(reextract,reanalyse,recalclv2):
        script=open("%sdata/%i/%.3i/recalc.sh"%(res,year,doy),"w")
        script.write("#!/bin/bash\n")
        if reextract:
            recalc_reextract(script,res,year,doy,reanalyse)
        if len(reanalyse)>0:
            recalc_reanalyse(script,res,year,doy,reanalyse)
            try:
                open("%sdata/%i/%.3i/pathlist.in"%(res,year,doy))
            except:
                pathl=open("%sdata/%i/%.3i/pathlist.in"%(res,year,doy),"w")
                pathl.write("./\n")
                pathl.close()
        if len(recalclv2)!=len(reanalyse):
            recalc_recalclv2(script,res,year,doy,reanalyse,recalclv2)
            try:
                open("%sdata/%i/%.3i/pathlist.in"%(res,year,doy))
            except:
                pathl=open("%sdata/%i/%.3i/pathlist.in"%(res,year,doy),"w")
                pathl.write("./\n")
                pathl.close()
        script.close()
        system("chmod u+x %sdata/%i/%.3i/recalc.sh"%(res,year,doy))
        return True
    return False

if (len(argv)==2 and argv[1]=="-h"):
    print "Checks data from given days"
    print "Usage : check_data.py [option(s)] ...[-h | -c | -r] [args]"
    print "Options and arguments:"
    print "-h\t: print this help message and exit"
    print "-c args\t: just check data and write check.log file"  
    print "-r args\t: check data, write check.log file and try to recalculate missing data (using batch queue should be started at 'verleihnix')"  
    print "args\t: res year startdoy stopdoy (e.g. 12m 2008 30 45)"
    exit()
elif len(argv)>1 and argv[1]=="-c" and len(argv)!=6:
    print "Wrong usage : try 'check_data.py -c resolution year startday stopday' or 'check_data.py -h' for help"
    exit()
elif len(argv)>1 and argv[1]=="-r" and len(argv)!=6:
    print "Wrong usage : try 'check_data.py -r resolution year startday stopday' or 'check_data.py -h' for help"
    exit()
elif len(argv)>1 and argv[1]=="-c" and len(argv)==6:
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
    recalc=False
elif len(argv)>1 and argv[1]=="-r" and len(argv)==6:
    recalc=True
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
    
time=getlocaltime()
#print time

if (recalc):
    reanalysearr=[]
    recalclv2arr=[]
    reextractlv0=[]
    for i in range(stopdoy-startdoy+1):
        reanalysearr.append([])
        recalclv2arr.append([])
        reextractlv0.append(0)

try:
    open("check.log")
    log=open("check.log","a")
    
    log.write("*****\n")
    log.write("%s\n"%(time))
    log.write("checking %sdata/%i/%i -> /%i\n"%(resolution,year,startdoy,stopdoy))
    log.write("+++++\n")
    
except:
    log=open("check.log","w")

    log.write("*****\n")
    log.write("%s\n"%(time))
    log.write("checking %sdata/%i/%i -> /%i\n"%(resolution,year,startdoy,stopdoy))
    log.write("+++++\n")




for i in range(startdoy,stopdoy+1):
    print "checking %sdata/%i/%.3i"%(resolution,year,i)
    try:
        liste=open("./%sdata/%i/%.3i/list.in"%(resolution,year,i))
        liste.readline()
        for s in liste:
            # check erg files
            resok=1
            fluxok=1
            try:
                k=s.split()
                erg=open("%sdata/%i/%.3i/erg_%s"%(resolution,year,i,k[0]))
                try:
                    check_erg(erg)
                except:
                    log.write("%sdata/%i/%.3i/erg_%s : corrupt\n"%(resolution,year,i,k[0]))
                    if (recalc):
                        reanalysearr[i-startdoy].append(k[0])
                        recalclv2arr[i-startdoy].append(k[0])
                        resok=0
                        fluxok=0
                        try:
                            open("%sdata/%i/%.3i/%s"%(resolution,year,i,k[0]))
                        except:
                            reextractlv0[i-startdoy]=1
                erg.close()
            except:
                if (recalc):
                    reanalysearr[i-startdoy].append(k[0])
                    recalclv2arr[i-startdoy].append(k[0])
                    resok=0
                    fluxok=0
                    try:
                        open("%sdata/%i/%.3i/%s"%(resolution,year,i,k[0]))
                    except:
                        reextractlv0[i-startdoy]=1
                log.write("%sdata/%i/%.3i/erg_%s : could not open\n"%(resolution,year,i,k[0]))
            # check res files
            nrions=-1
            try:
                k=s.split()
                res=open("%sdata/%i/%.3i/res_%s"%(resolution,year,i,k[0]))
                try:
                    nrions=check_res(res)
                except:
                    nrions=-1
                    log.write("%sdata/%i/%.3i/res_%s : corrupt\n"%(resolution,year,i,k[0]))
                    if (recalc and resok==1):
                        recalclv2arr[i-startdoy].append(k[0])
                        fluxok=0
                res.close()
            except:
                log.write("%sdata/%i/%.3i/res_%s : could not open\n"%(resolution,year,i,k[0]))
                if (recalc and resok==1):
                    recalclv2arr[i-startdoy].append(k[0])
                    fluxok=0
            # check flux files
            try:
                k=s.split()
                flux=open("%sdata/%i/%.3i/flux_%s"%(resolution,year,i,k[0]))
                try:
                    check_flux(flux,nrions)
                except:
                    log.write("%sdata/%i/%.3i/flux_%s : corrupt\n"%(resolution,year,i,k[0]))
                    if (recalc and fluxok==1):
                        recalclv2arr[i-startdoy].append(k[0])
                flux.close()
            except:
                log.write("%sdata/%i/%.3i/flux_%s : could not open\n"%(resolution,year,i,k[0]))
                if (recalc and fluxok==1):
                    recalclv2arr[i-startdoy].append(k[0])
        liste.close()
    except:
        log.write("%sdata/%i/%.3i/ : no list.in\n"%(resolution,year,i))

if (recalc):
    if (len(reanalysearr)>0 or len(recalclv2arr)>0):
        rescr=open("reanalyse_timeframe.sh","w")
        for doy in range(startdoy,stopdoy+1):
            if recalcday(resolution,year,doy,reextractlv0[doy-startdoy],reanalysearr[doy-startdoy],recalclv2arr[doy-startdoy]):
                rescr.write("cd %sdata/%i/%.3i\n"%(resolution,year,doy))
                rescr.write("./recalc.sh\n")
                rescr.write("cd -\n")
        rescr.close()
        system("chmod u+x reanalyse_timeframe.sh")
        system("./reanalyse_timeframe.sh")
        
log.write("-----\n")
log.close()

if (0):
    print "reextractlv0 : ",reextractlv0
    print "reanalysearr : ",reanalysearr
    print "recalclv2arr : ",recalclv2arr


#try:
#    open("list.in")
#except:
    
