from libacepy.swicsiondata import swicsiondata
from libacepy.swepamdata import swepamdata,sync_h

he2001=swicsiondata("He2+",[[1.,365.]],"/data/wimmer/ace/1hdata/2001/")
he2004=swicsiondata("He2+",[[1.,135.],[141.,365.]],"/data/wimmer/ace/1hdata/2004/")
he2007=swicsiondata("He2+",[[1.,365.]],"/data/wimmer/ace/1hdata/2007/")

sphe2001=swepamdata(720.,2001,1.,365.,"/data/ivar/ace/swepam/")
sphe2007=swepamdata(720.,2007,1.,365.,"/data/ivar/ace/swepam/")

sphe2001.load()
sphe2007.load()


he2001.load()
he2004.load()
he2007.load()

ssphe2001=sync_h(sphe2001,he2001)
ssphe2007=sync_h(sphe2007,he2007)

he3002001=0.
he6002001=0.
he3002004=0.
he6002004=0.
he3002007=0.
he6002007=0.

sphe3002001=0.
sphe6002001=0.
sphe3002007=0.
sphe6002007=0.

nsp3002001=0.
nsp3002007=0.
nsp6002001=0.
nsp6002007=0.

n3002001=0.
n3002004=0.
n3002007=0.
n6002001=0.
n6002004=0.
n6002007=0.

for i in range(len(he2001.dens)):
    if (he2001.vel[i]>300. and he2001.vel[i]<400. and ssphe2001.heh[i][1]>0.):
        he3002001+=he2001.dens[i][0]
        n3002001+=1.
    if (he2001.vel[i]>600. and he2001.vel[i]<700. and ssphe2001.heh[i][1]>0.):
        he6002001+=he2001.dens[i][0]
        n6002001+=1.
if (n3002001>0.):
    he3002001/=n3002001
if (n6002001>0.):
    he6002001/=n6002001

for i in range(len(he2004.dens)):
    if (he2004.vel[i]>300. and he2004.vel[i]<400. and ssphe2004.heh[i][1]>0.):
        he3002004+=he2004.dens[i][0]
        n3002004+=1.
    if (he2004.vel[i]>600. and he2004.vel[i]<700. and ssphe2004.heh[i][1]>0.):
        he6002004+=he2004.dens[i][0]
        n6002004+=1.
if (n3002004>0.):
    he3002004/=n3002004
if (n6002004>0.):
    he6002004/=n6002004

for i in range(len(he2007.dens)):
    if (he2007.vel[i]>300. and he2007.vel[i]<400. and ssphe2007.heh[i][1]>0.):
        he3002007+=he2007.dens[i][0]
        n3002007+=1.
    if (he2007.vel[i]>600. and he2007.vel[i]<700. and ssphe2007.heh[i][1]>0.):
        he6002007+=he2007.dens[i][0]
        n6002007+=1.
if (n3002007>0.):
    he3002007/=n3002007
if (n6002007>0.):
    he6002007/=n6002007

for i in range(len(ssphe2001.heh)):
    if (he2001.vel[i][1]>300. and he2001.vel[i][1]<400. and ssphe2001.heh[i][1]>0.):
        sphe3002001+=ssphe2001.dens[i][1]*ssphe2001.heh[i][1]
        nsp3002001+=1.
    if (he2001.vel[i][1]>600. and he2001.vel[i][1]<700. and ssphe2001.heh[i][1]>0.):
        sphe6002001+=ssphe2001.dens[i][1]*ssphe2001.heh[i][1]
        nsp6002001+=1.
if (nsp3002001>0.):
    sphe3002001/=nsp3002001
if (nsp6002001>0.):
    sphe6002001/=nsp6002001

for i in range(len(ssphe2007.heh)):
    if (he2007.vel[i][1]>300. and he2007.vel[i][1]<400. and ssphe2007.heh[i][1]>0.):
        sphe3002007+=ssphe2007.dens[i][1]*ssphe2007.heh[i][1]
        nsp3002007+=1.
    if (ssphe2007.vel[i][1]>600. and ssphe2007.vel[i][1]<700. and ssphe2007.heh[i][1]>0.):
        sphe6002007+=ssphe2007.dens[i][1]*ssphe2007.heh[i][1]
        nsp6002007+=1.
if (nsp3002007>0.):
    sphe3002007/=nsp3002007
if (nsp6002007>0.):
    sphe6002007/=nsp6002007



print "he3002001 = ",he3002001," sphe3002001 = ",sphe3002001
print "he3002004 = ",he3002004
print "he3002007 = ",he3002007," sphe3002007 = ",sphe3002007
print "he6002001 = ",he6002001," sphe6002001 = ",sphe6002001
print "he6002004 = ",he6002004
print "he6002007 = ",he6002007," sphe6002007 = ",sphe6002007
