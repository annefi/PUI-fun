from numpy import array,append,unique

def calc_day00(years,doys):
    d00=array([])
    for year in unique(years):
        dy=year-2000
        if dy==0:
            lpd=0
        else:
            lpd=1+int((dy-1)/4)
        offset=dy*365+lpd
        d00=append(d00,doys[years==year]+offset)
    return d00

def get_mass(name):
    if name[0:2]=="He":
        return 4.
    if name[0:1]=="H":
        return 1.
    elif name[0:1]=="O":
        return 16.
    elif name[0:1]=="C":
        return 12.
    elif name[0:2]=="Ne":
        return 20.
    elif name[0:1]=="N":
        return 14.
    elif name[0:2]=="Fe":
        return 56.
    elif name[0:2]=="Mg":
        return 24.
    elif name[0:2]=="Si":
        return 28.
    elif name[0:1]=="S":
        return 32.
    elif name[0:2]=="Ca":
        return 40.
    else:
        print "get_mass: Element for "+name+" not defined!"
        return 0.
