from libacepy.swicsprotondata import swicsprotondata
from libacepy.swicsiondata import swicsiondata
from Gnuplot import Gnuplot,Data


def bindat(ts,days):
    bints=[]
    for doy in range(365/days):
        bints.append([(doy+1)*days,0.])
    i=0
    for val in bints:
        while (ts[i][0]<val[0] and i<len(ts)-1):
            val[1]+=ts[i][1]
            i+=1
    return bints

def sumcounts(ts):
    summe=0.
    for val in ts:
        summe+=val[1]
    return summe

def getwspec(ion,he):
    from libacepy.ancil import histogram
    wspec=[]
    for i in range(len(he.vel)):
        if (he.time[i]==ion.time[i]):
            if he.vel[i]>0. and he.vel[i]<2000.:
                for val in ion.countspec[i]:
                    if val[1]>0.:
                        wspec.append([val[0]/he.vel[i],val[1]])
    whist=histogram(wspec,0.,0.1,30,2)
    return whist

def getts(ion):
    ionts=[]
    for i in range(len(ion.time)):
        summ=0.
        for val in ion.countspec[i]:
            summ+=val[1]
        ionts.append([ion.time[i],summ])
    return ionts

path="/data/wimmer/ace/"
path1="/data/wimmer/ace/puis/1hdata/2001/"
path2="/data/wimmer/ace/puis/1hdata/2002/"
path3="/data/wimmer/ace/puis/1hdata/2003/"
path4="/data/wimmer/ace/puis/1hdata/2004/"
path5="/data/wimmer/ace/puis/1hdata/2005/"
path6="/data/wimmer/ace/puis/1hdata/2006/"
path7="/data/wimmer/ace/puis/1hdata/2007/"
path8="/data/wimmer/ace/puis/1hdata/2008/"
timeframe=[[75.,125.]]
timeframe=[[150.,151.]]
#hedata=swicsiondata("He2+",timeframe2,path2)
#hedata.load()
#o11=swicsprotondata("O1+",timeframe,path1)
#o11.load()
o11=swicsprotondata("He1+",timeframe,path1)
o11.load()
#he2=swicsiondata("He2+",720.*5.,2001,timeframe,path)
#he2.load()
o11ts=[]
for i in range(len(o11.time)):
    summ=0.
    for val in o11.countspec[i]:
        summ+=val[1]
    o11ts.append([o11.time[i],summ])

"""
hev=[]
for i in range(len(he2.time)):
    hev.append([he2.time[i],he2.vel[i]/100.])
whist=getwspec(o11,he2)
pwhist=Data(whist)
"""
#pwhist.set_option_colonsep("with","box

timeframe=[[1,365.]]
o12=swicsprotondata("He1+",timeframe,path2)
o12.load()
o13=swicsprotondata("He1+",timeframe,path3)
o13.load()
timeframe=[[1,365.]]
o14=swicsprotondata("He1+",timeframe,path4)
o14.load()
o15=swicsprotondata("He1+",timeframe,path5)
o15.load()
o16=swicsprotondata("He1+",timeframe,path6)
o16.load()
o17=swicsprotondata("He1+",timeframe,path7)
o17.load()
o18=swicsprotondata("He1+",timeframe,path8)
o18.load()

#c1=swicsprotondata("C1+",timeframe,path)
#c1.load()
#ne1=swicsprotondata("Ne1+",timeframe,path)
#ne1.load()
#si1=swicsprotondata("Si1+",timeframe,path)
#si1.load()
#he1=swicsprotondata("He1+",timeframe,path)
#he1.load()
#h1=swicsprotondata("H1+",timeframe,path)
#h1.load()


#vel=[]
#for i in range(len(hedata.time)):
#    vel.append([hedata.time[i],hedata.vel[i]/100.]) 

#dens=[]
#for i in range(len(hedata.time)):
#    dens.append([hedata.time[i],hedata.dens[i][0]]) 



#o11ts=[]
#for i in range(len(o11.time)):
#    summ=0.
#    for val in o11.countspec[i]:
#        summ+=val[1]
#    o11ts.append([o11.time[i],summ])
o12ts=[]
for i in range(len(o12.time)):
    summ=0.
    for val in o12.countspec[i]:
        summ+=val[1]
    o12ts.append([o12.time[i],summ])
o13ts=[]
for i in range(len(o13.time)):
    summ=0.
    for val in o13.countspec[i]:
        summ+=val[1]
    o13ts.append([o13.time[i],summ])
o14ts=[]
for i in range(len(o14.time)):
    summ=0.
    for val in o14.countspec[i]:
        summ+=val[1]
    o14ts.append([o14.time[i],summ])
o15ts=[]
for i in range(len(o15.time)):
    summ=0.
    for val in o15.countspec[i]:
        summ+=val[1]
    o15ts.append([o15.time[i],summ])
o16ts=[]
for i in range(len(o16.time)):
    summ=0.
    for val in o16.countspec[i]:
        summ+=val[1]
    o16ts.append([o16.time[i],summ])
o17ts=[]
for i in range(len(o17.time)):
    summ=0.
    for val in o17.countspec[i]:
        summ+=val[1]
    o17ts.append([o17.time[i],summ])
o18ts=[]
for i in range(len(o18.time)):
    summ=0.
    for val in o18.countspec[i]:
        summ+=val[1]
    o18ts.append([o18.time[i],summ])

#c1ts=[]
#for i in range(len(c1.time)):
#    summ=0.
#    for val in c1.countspec[i]:
#        summ+=val[1]
#    c1ts.append([c1.time[i],summ])

#ne1ts=[]
#for i in range(len(ne1.time)):
#    summ=0.
#    for val in ne1.countspec[i]:
#        summ+=val[1]
#    ne1ts.append([ne1.time[i],summ])

#si1ts=[]
#for i in range(len(si1.time)):
#    summ=0.
#    for val in si1.countspec[i]:
#        summ+=val[1]
#    si1ts.append([si1.time[i],summ])

#he1ts=[]
#for i in range(len(he1.time)):
#    summ=0.
#    for val in he1.countspec[i]:
#        summ+=val[1]
#    he1ts.append([he1.time[i],summ])

#h1ts=[]
#for i in range(len(h1.time)):
#    summ=0.
#    for val in h1.countspec[i]:
#        if (val[0]<1300.):
#            summ+=val[1]
#    h1ts.append([h1.time[i],summ])

#sumts=[]
#for i in range(len(o1ts)):
#    sumts.append([o1ts[i][0],o1ts[i][1]])
    
gp=Gnuplot()
#gp("set xrange [1:365.]")
#gp.plot(o1ts,c1ts,c1ts,ne1ts,si1ts,vel)
#gp.plot(vel,sumts,sumts)
#gp.plot(o12ts,o13ts,o14ts,o15ts,o16ts,o17ts,o18ts)
#gp.hardcopy("o1p1h2007.ps",color="true")

#gp.plot(pwhist)
gp2=Gnuplot()
gp2.plot(o11ts,o12ts,o13ts,o14ts,o15ts,o16ts,o17ts,o18ts)
#gp2("set xrange [1:365.]")
#gp2.plot(dens)
