from Gnuplot import Gnuplot

pin=open("/home/ivar/berger/projects/ionpositions/ion_para.dat")
hepos=[]
o6pos=[]
o7pos=[]
for step in range(58):
    s=pin.readline()
    k=s.split()
    ions=float(k[5])
    s=pin.readline()
    for i in range(ions):
        s=pin.readline()
        k=s.split()
        if (k[0]=="He2+"):
            hepos.append([float(k[7]),float(k[2])])
        if (k[0]=="O6+"):
            o6pos.append([float(k[7]),float(k[2])])
        if (k[0]=="O7+"):
            o7pos.append([float(k[7]),float(k[2])])

pin.close()
gp=Gnuplot()
gp("f(x)=8")
gp("set yrange[5:10]")
gp("set xrange[200:700]")
gp.plot(hepos,"f(x)")

#gp.plot(hepos,o6pos,o6pos,o7pos)
