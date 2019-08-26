pylab.show()from numpy import *
from ACE import ace_swics_pha

class write_pha_subset(object):
    def __init__(self,d):
        self.d = d

    def write_data(self,fname,prodlist,fmt):
        try:
            open(fname,"r")
            print "File ,",fname," exists. No data written"
            return 0
        except:
            fout = open(fname,"w")
            header = ""
            for s in prodlist:
                header+=s+"\t"
            header+="\n"
            fout.write(header)
            dat = [] 
            for s in prodlist:
                if dat==[]:
                    dat=[self.d.data[s]]
                else:
                    dat=append(dat,[self.d.data[s]],axis=0)
            savetxt(fout,dat.T,fmt=fmt)

pui_prodlist=["year","doy","tof","esd","did","sec","rng","swt","twt","epq","mq","aspang","aspphi","asptheta","vsw","dsw","tsw","B","Bx","By","Bz","Balpha","Bphi","Btheta","wHe1+"]
pui_fmt = ["%.4i","%.6f","%i","%i","%i","%i","%i","%.2f","%.2f","%i","%.3f","%f","%f","%f","%.2f","%.2f","%.1f","%.3f","%.3f","%.3f","%.3f","%.1f","%.1f","%.1f","%.3f"]

for year in range(2003,2012):
    try:
        d = ace_swics_pha(year=[year],tf=[[1,367]],path="/data/ivar/ace/swics/lv0/",rng=(0,),mqrange=(3.5,4.5))
        w = write_pha_subset(d)
        w.write_data("mq_3.5-4.5_rng_0_%.4i.dat"%(year),prodlist=pui_prodlist,fmt=pui_fmt)
        del(d)
        del(w)
    except:
        print "Problems Year ",year
