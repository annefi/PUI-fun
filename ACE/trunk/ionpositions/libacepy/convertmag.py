from os import system

res=1.
year=2007

header=[]

system("mkdir %isdata/%i"%(int(res),year))

magin=open("%is%i.dat"%(int(res),year))
k=["",""]
while k[0]!="BEGIN" and k[1]!="Data":
    s=magin.readline()
    header.append(s)
    k=s.split()
    if len(k)<2:
        k=["",""]


enddoy=366

for DoY in range(1,enddoy+1):
    print "writing DoY ",DoY
    magout=open("%isdata/%i/%.3i"%(int(res),year,DoY),"w")
    magout.write("doy\tBmag\tBgsex\tBgsey\tBgsez\n")
    magout.write("BEGIN DATA\n")
    if (DoY==1):
        s=magin.readline()
        k=s.split()
    while len(k)==6 and int(float(k[1]))==DoY:
        magout.write("%.7f\t%.3f\t%.3f\t%.3f\t%.3f\n"%(float(k[1]), float(k[2]), float(k[3]), float(k[4]), float(k[5])))
        s=magin.readline()
        k=s.split()
    magout.close()
magin.close()
