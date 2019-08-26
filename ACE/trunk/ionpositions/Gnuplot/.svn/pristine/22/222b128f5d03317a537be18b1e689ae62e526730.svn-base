#!/usr/bin/python
# This file reads the variables from ~/.gnuplot if it exists and sets the dictionary
# 'vars' with the contents of that file. Default values for certain variables are also specified here.

def readGnuplot():
    evstr=""
    from os import getenv
    var_fn=getenv("HOME")+"/.gnuplot"
    for l in open(var_fn):
        if l.find("#::")!=0:
            continue
        evstr+=l[4:]
    return evstr

def evalOptions(gpvars):
    exec(readGnuplot(), gpvars)
    return gpvars

gpvars={
    }

gpvars=evalOptions(gpvars)
