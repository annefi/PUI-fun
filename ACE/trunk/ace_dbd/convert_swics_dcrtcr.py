from ace_swics import ace_swics
from ace_swics_dcrtcr import ace_swics_dcrtcr
from numpy import unique,append
ions=["He2+"]
years=[2001,2002,2003,2005,2006,2007,2008,2009,2010]
#years=[2008]
for year in years:
    print year
    for i in range(19):
        print i*20.+1,(i+1)*20.
        d=ace_swics(ion=ions,year=year,tf=[[i*20.+1,(i+1)*20.]],fmt="new")
        p=ace_swics_dcrtcr(year=year,tf=[[i*20.+1,(i+1)*20.+1.]],fmt="old",path="/data/etph/ace/pui/12mdata/")
        ud00=unique(d.data["d00"])
        time=unique(d.data["time"])
        p.bin_data(ud00,time)
        p.save_spec()    
