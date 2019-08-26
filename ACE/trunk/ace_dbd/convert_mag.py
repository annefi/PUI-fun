from ace_swics import ace_swics
from ace_mag import ace_mag
from numpy import unique,append
ions=["He2+"]
years=[2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011]
#years=[2000]
for year in years:
    print year
    d=ace_swics(ion=ions,year=year,tf="all",fmt="new")
    ud00=unique(d.data["d00"])
    time=unique(d.data["time"])
    mag=ace_mag(year=year,tf=[[time[0],time[-1]+1./24./5.]],fmt="old")
    mag.set_mask("Master","time",time[0],time[-1]+1./24./5.,reset=True)
    for key in mag.data.keys():
        mag.data[key]=mag.get_data("Master",key)
    mag.reset_mask("Master")
    mag.transform_data(append(ud00,ud00[-1]+1./24./5.),prodt="d00")
    mag.bin_data(append(ud00,ud00[-1]+1./24./5.),time)
    mag.data["year"][:]=year
    mag.save_bin()    
