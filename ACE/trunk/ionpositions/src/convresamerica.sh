#!/bin/sh

# small tool that converts result files from axlv2 software to some ion names as used by analyse data!

for i in `cat replacelist.dat`; do
        cp $i $i.bak
done

for i in `cat replacelist.dat`; do
        sed s/"20Ne"/"  Ne"/g < $i > $i.tmp
        mv $i.tmp $i
done
for i in `cat replacelist.dat`; do
        sed s/" Ne9+"/"Ne10+"/g < $i > $i.tmp
        mv $i.tmp $i
done
for i in `cat replacelist.dat`; do
        sed s/" H+"/"H1+"/g < $i > $i.tmp
        mv $i.tmp $i


done