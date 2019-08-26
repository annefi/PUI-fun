from ace_data import ace_data
import numpy as np
import matplotlib.pyplot as plt

ionlist = ["He2+","C5+","C6+","O6+","O7+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+"]


def load_period(year=[2001],tf=[[10,20]],ions=ionlist):
    d=ace_data(ion=ionlist,year=year,tf=tf,fmt="new")
    d.add_data("O7O6",d.data["ctsO7+"]/d.data["ctsO6+"])
    d.add_data("C6C5",d.data["ctsC6+"]/d.data["ctsC5+"])
    mqFe=(d.data["ctsFe7+"]*7+d.data["ctsFe8+"]*8+d.data["ctsFe9+"]*9+d.data["ctsFe10+"]*10+d.data["ctsFe11+"]*11+d.data["ctsFe12+"]*12+d.data["ctsFe13+"]*13+d.data["ctsFe14+"]*14+d.data["ctsFe15+"]*15+d.data["ctsFe16+"]*16)/(d.data["ctsFe7+"]+d.data["ctsFe8+"]+d.data["ctsFe9+"]+d.data["ctsFe10+"]+d.data["ctsFe11+"]+d.data["ctsFe12+"]+d.data["ctsFe13+"]+d.data["ctsFe14+"]+d.data["ctsFe15+"]+d.data["ctsFe16+"])
    mqO=(d.data["ctsO7+"]*7+d.data["ctsO6+"]*6)/(d.data["ctsO7+"]+d.data["ctsO6+"])
    mqC=(d.data["ctsC6+"]*6+d.data["ctsC5+"]*5)/(d.data["ctsC6+"]+d.data["ctsC5+"])
    mqFe[np.isnan(mqFe)]=7
    mqFe[np.isinf(mqFe)]=7
    mqO[np.isnan(mqO)]=6
    mqO[np.isinf(mqO)]=7
    mqC[np.isnan(mqC)]=5
    mqC[np.isinf(mqC)]=6
    d.add_data("mqFe",mqFe)
    d.add_data("mqO",mqO)
    d.add_data("mqC",mqC)
    #vswnn=d.data["vsw"]
    #vswnn[np.isnan(vswnn)]=0
    dswnn=d.data["dsw"]
    dswnn[np.isnan(dswnn)]=0
    tswnn=d.data["tsw"]
    tswnn[np.isnan(tswnn)]=0
    #d.add_data("vswnn",vswnn)
    d.add_data("dswnn",dswnn)
    d.add_data("tswnn",tswnn)
    d.add_data("OHe2",(d.data["dO6+"]+d.data["dO7+"])/(d.data["dHe2+"]))
    d.add_data("OHe",(d.data["dO6+"]+d.data["dO7+"])/(d.data["dHe2+"]))
    d.add_data("FeHe",(d.data["dFe7+"]+d.data["dFe8+"]+d.data["dFe9+"]+d.data["dFe10+"]+d.data["dFe11+"]+d.data["dFe12+"]+d.data["dFe13+"]+d.data["dFe14+"]+d.data["dFe15+"]+d.data["dFe16+"])/(d.data["dHe2+"]))
    d.add_data("FeO",(d.data["dFe7+"]+d.data["dFe8+"]+d.data["dFe9+"]+d.data["dFe10+"]+d.data["dFe11+"]+d.data["dFe12+"]+d.data["dFe13+"]+d.data["dFe14+"]+d.data["dFe15+"]+d.data["dFe16+"])/(d.data["dO6+"]+d.data["dO7+"]))
    d.data["FeO"][np.isnan(d.data["FeO"])]=0.
    d.data["FeO"][np.isinf(d.data["FeO"])]=0.
    d.add_data("PHe",(d.data["dswnn"])/(d.data["dHe2+"]))
    return d


def plot_period(d):
    d.set_mask("Master","vsw",1.,op="ge",reset=True)
    #d.set_mask("Master","dsw",0.,1000.,reset=True)
    #d.set_mask("Master","tsw",0.,1.e8,reset=True)

    d.timeseries(prody=["vsw","dswnn","tswnn","mqO","mqC","mqFe","dHe2+","OHe","FeHe","FeO","PHe","B","phi","theta"],time=np.unique(d.data["time"]))

def save_period(d):
    plt.savefig("%s_%s_%s.pdf"%(str(d.year[0]),str(d.timeframe[0][0]),str(d.timeframe[0][1])),bbox_inches="tight")
