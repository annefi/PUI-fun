from ace_swics import ace_swics
from ace_sweswi import ace_sweswi
from numpy import unique,append
ions=["He2+"]
years=[2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011]
#years=[2001]
for year in years:
    print year
    d=ace_swics(ion=ions,year=year,tf="all",fmt="new")
    p=ace_sweswi(year=year,tf="all",fmt="old")
    ud00=unique(d.data["d00"])
    time=unique(d.data["time"])
    p.bin_data(append(ud00,ud00[-1]+1./24./5.),time)
    p.save_bin()    
