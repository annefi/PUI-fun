from ace_swics import ace_swics

ions=["He2+","O8+","O7+","O6+","C6+","C5+","C4+","N5+","N6+","N7+","Ne7+","Ne8+","Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+","S7+","S8+","S9+","S10+","S11+","S12+","Ca7+","Ca8+","Ca9+","Ca10+","Ca11+","Ca12+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+"]
#years=[2000]
years=[2005,2008]
for year in years:
    print year
    for doy in range(1,367):
        d=ace_swics(ion=ions,year=year,tf=[[doy,doy]],fmt="old",path="/data/etph/ace/12mdata/")
        d.save_spec()
