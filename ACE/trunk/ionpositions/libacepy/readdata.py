#!/usr/bin/python
from numpy import float

def readlv1(filename):
    data=[]
    dim=58
    infile=open(filename)
    for step in range(dim):
        stepdata=[]
        s=infile.readline()
        k=s.split()
        numions=int(k[5])
        s=infile.readline()
        for ion in range(numions):
            s=infile.readline()
            k=s.split()
            stepdata.append([k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]),float(k[11]),0.0,0.0])
        data.append(stepdata)
    return data


def readelem(filename):
    data=[]
    infile=open(filename)
    s=infile.readline()
    for s in infile:
        k=s.split()
        data.append([k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8])])
    return data


def readres(filename):
    data=[]
    infile=open(filename)
    s=infile.readline()
    for s in infile:
        k=s.split()
        data.append([k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7])])
    return data

def readflux(filename):
    dim=58
    data=[]
    infile=open(filename)
    for step in range(dim):
        stepdata=[]
        s=infile.readline()
        k=s.split()
        numberions=int(k[5])
        s=infile.readline()
        for ion in range(numberions):
            s=infile.readline()
            k=s.split()
            stepdata.append([k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]),float(k[11]),float(k[12]),float(k[13])])
        data.append(stepdata)
    return data
