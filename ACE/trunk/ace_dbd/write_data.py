from ace_data import ace_data
from numpy import *

class wdata(object):
    def __init__(self,db,ions=["H1+","He2+","O6+","Fe10+"]):
        self.db = db
        self.ions = ions
    def write_data(self):
        t,ind = unique(self.db.data["time"],return_index="True")
        t = append(t,t[-1]+1./24./5.)
        nrv = {}
        vel = {}
        cts = {}
        den = {}
        vth = {}
        dv = {}
        alpha = self.db.data["alpha"][ind]
        B = self.db.data["B"][ind]
        vsw = self.db.data["vsw"][ind]
        tsw = self.db.data["tsw"][ind]
        dsw = self.db.data["dsw"][ind]
        for ion in self.ions:
            self.db.reset_mask("Master")
            if ion != "H1+":
                self.db.set_mask("Master","cr"+ion,0.01,op="ge",reset=True)
            else:
                self.db.add_data("cr"+ion,self.db.data["dcr"+ion]+self.db.data["tcr"+ion])
                self.db.set_mask("Master","cr"+ion,0.01,op="ge",reset=True)
            
            H,x = histogram(self.db.get_data("Master","time"),bins=t)
            nrv[ion] = H
            vel[ion] = self.db.data["vel"+ion][ind]
            cts[ion] = self.db.data["cts"+ion][ind]
            den[ion] = self.db.data["d"+ion][ind]
            vth[ion] = self.db.data["vth"+ion][ind]
            if ion != "H1+":
                dv[ion] = self.db.data["dv"+ion][ind]
            else:
                dv[ion] = self.db.data["vel"+ion][ind]-self.db.data["vsw"][ind]
                
        for ion in self.ions:
            fout = open("./jana/"+ion+"_%i_%i-%i.dat"%(self.db.year[0],self.db.timeframe[0][0],self.db.timeframe[0][1]),"w")
            dat = zeros((12,t.shape[0]-1))
            dat[0,:] = t[:-1]
            dat[1,:] = vsw
            dat[2,:] = dsw
            dat[3,:] = tsw
            dat[4,:] = alpha
            dat[5,:] = B
            dat[6,:] = vel[ion]
            dat[7,:] = den[ion]
            dat[8,:] = vth[ion]
            dat[9,:] = dv[ion]
            dat[10,:] = cts[ion]
            dat[11,:] = nrv[ion]
            savetxt(fout,dat.T,fmt=("%.8f","%.2f","%.2f","%.0f","%.2f","%.4f","%.2f","%.3f","%.2f","%.2f","%.2f","%i"),delimiter="  ",header="doy  vsw[kms^-1]  dsw[cm^-3]  tsw[K]  alpha[deg]  B[nT]  vion[kms^-1]  dion[arb]  vthion[kms^-1]  dvion-sw[kms^-1]  ctsion[#]  nrv[#]")
            fout.close()
            
            
            
            
