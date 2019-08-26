#!/usr/bin/python

# ANLEITUNG:
# Programm liest Dateinamen zeilenweise von der Standardeingabe
# und produziert eine Ausgabedatei (cPickle), die als erster und
# einziger Kommandozeilenparameter angegeben werden muss.
#
# Zum Beispiel so, MU!
# find -name "*res_axlv2_et_slices_*.dat"|<...pfad...>/process-res.py ausgabe.dat
#
# oder am konkreten Beispiel:
# Gehe in Ordner wo die Daten liegen:
# hier /data/kleopatra/ace/1hdata/2007
#
# und dann ...
#
# find -name "*res_axlv2_et_slices_*.dat"|~/Desktop/swics/c13/process-res.py ~/Desktop/swics/c13/mystuff/2007.dat
#
#

from sys import stdin, argv

import re
fnparse=re.compile(r"\.\/([0-9]+)\/res_axlv2_et_slices_([0-9]+)_([0-9]+)_([0-9]+)\.([0-9]+)\.([0-9]+)_([0-9]+)_([0-9]+)_([0-9]+)\.([0-9]+)\.([0-9]+)\.dat")

data=[]

def parseFile(fn):
    f=open(fn)
    f.readline() # discard description header
    outp=[]
    for l in f:
        ls=l.split()
        outp+=[(ls[0], [float(i) for i in ls[1:]])]
    return outp

for fn in stdin:
    fn=fn[:-1]
    timespan=[int(i) for i in fnparse.match(fn).groups()]
    print "Reading file %s" % fn
    hdata=(fn, timespan, parseFile(fn))
    data+=[hdata]

import cPickle
cPickle.dump(data, open(argv[1], "wb"), protocol=1)

