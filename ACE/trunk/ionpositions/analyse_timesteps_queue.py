from os import system

liste=open("list.in")
liste.readline()

for filename in liste:
    k=filename.split()
    outfile=open("analyse_%s.sh"%(k[0]),"w")
    outfile.write("#!/bin/bash\n")
    outfile.write("./analyse_data %s\n"%(k[0]))
    outfile.write("rm %s\n"%(k[0]))
    outfile.write("rm analyse_%s.sh\n"%(k[0]))
    outfile.write("python calcswicslv2.py %s\n"%(k[0]))
    outfile.close()
    system("chmod u+x analyse_%s.sh"%(k[0]))
    system("qsub -cwd -S /bin/bash -r y -p -1023 analyse_%s.sh"%(k[0]))

