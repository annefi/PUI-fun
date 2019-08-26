from numpy import zeros

class ace_elem(object):
    def __init__(self,d):
        self.d = d

    def calc_mean_ch(self,elem="Fe",chst=range(7,17)):
        ionlist=[]
        for ch in chst:
            ionlist.append(elem+str(ch)+"+")

        sdens = zeros(self.d.data["d"+ionlist[0]].shape)
        wdens = zeros(self.d.data["d"+ionlist[0]].shape)
        for c,ion in enumerate(ionlist):
            sdens += self.d.data["d"+ion]
            wdens += self.d.data["d"+ion]*chst[c]

        mch = wdens/sdens
        if "mch"+elem in self.d.data.keys():
            self.d.data["mch"+elem]=mch
        else:
            self.d.add_data("mch"+elem,mch)
        if "d"+elem in self.d.data.keys():
            self.d.data["d"+elem]=sdens
        else:
            self.d.add_data("d"+elem,sdens)

    def calc_elem_cts(self,elem="Fe",chst=range(7,17)):
        ionlist=[]
        for ch in chst:
            ionlist.append(elem+str(ch)+"+")
        scts = zeros(self.d.data["d"+ionlist[0]].shape)
        for ion in ionlist:
            scts += self.d.data["cts"+ion]
        if "cts"+elem in self.d.data.keys():
            self.d.data["cts"+elem]=scts
        else:
            self.d.add_data("cts"+elem,scts)
         
