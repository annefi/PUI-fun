from libacepy.swicsiondata import swicsiondata

path="/data/wimmer/ace/1hdata/2007/"
timeframe=[[1.,200.]]

c6=swicsiondata("C6+",timeframe,path)
c6.load()
n7=swicsiondata("N7+",timeframe,path)
n7.load()
o8=swicsiondata("O8+",timeframe,path)
o8.load()
he2=swicsiondata("He2+",timeframe,path)
he2.load()

co=0.
con=0
cn=0.
cnn=0

for i in range(len(he2.time)):
    if (he2.vel[i]>600. and he2.vel[i]<700.):
        if (c6.dens[i][0]>0. and o8.dens[i][0]>0.):
            co+=o8.dens[i][0]/c6.dens[i][0]
            con+=1
        if (c6.dens[i][0]>0. and n7.dens[i][0]>0.):
            cn+=n7.dens[i][0]/c6.dens[i][0]
            cnn+=1

co=co/con
cn=cn/cnn

print "o/c = ",co
print "n/c = ",cn
