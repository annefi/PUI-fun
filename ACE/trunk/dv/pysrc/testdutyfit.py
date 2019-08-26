from libacepy.dutyfit import dutyfit
from scipy import zeros

timeframe=[[4.,9.],[17.4,25.25],[30.5,35.],[45.5,55.],[60.,63.],[65.5,70.],[73.25,80.5],[93.,97.5],[103.,107.],[119.,126.5],[129.,135.],[145.25,151.1]]
effpath="/data/ivar/ace/efficencies/aspeff/"
datapath="/data/wimmer/ace/12mdata/2007/"
datapath2="/data/zechine/ace/12mprotons/2007/"
swepampath="/data/ivar/ace/swepam/"
magpath="/data/ivar/ace/mag/"
ionname="O6+"

para=zeros([4])
# He2+
para[0]=0.0
para[1]=1.1
para[2]=49.65
para[3]=40.78
# O6+
para[0]=0.
para[1]=1.195
para[2]=33.3
para[3]=41.00
ia=zeros([4],int)
ia[0]=0
ia[1]=1
ia[2]=0
ia[3]=0
#para[0]=1.27
#para[1]=0.766
#para[2]=26.86
#para[3]=47.11

df=dutyfit(datapath,swepampath,datapath2,magpath,effpath,ionname,timeframe,para)
df.load()
df.hist_data()
df.fit(ia)

from Gnuplot import Gnuplot
gp=Gnuplot()
gp("set autoscale")
gp.plot(df.sumspec,df.sumspecprotons,df.sumspecprotons)
if (1):
    gp("set xrange[0:1.6]")
    gp("set yrange[0:0.8]")
    gp("set format y '%.2f'")
    gp("set ylabel '{/Symbol D}v/v_{Alf}'")
    gp("set xlabel '{/Symbol b} [rad]'")
    gp.plot(df.pdvhist,df.pthdv[0])
    gp.hardcopy("dvvirtobs_%s.ps"%(df.iondata.name),color="true",fontsize=20)
    gp("set autoscale y")
    gp("set format y '%.1f'")
    gp("set ylabel 'vth [km^{1}s^{-1}]'")
    gp("set xlabel '{/Symbol b} [rad]'")
    gp.plot(df.pvthhist,df.pthvth[0])
    gp.hardcopy("vthvirtobs_%s.ps"%(df.iondata.name),color="true",fontsize=20)

