# keep these first
/bin/bash  >& bashtest.out <<ENDOFJOB
echo run starting at `date` in `pwd`

# make PS MMQ plot (with directory attached to mmq filename)
echo making ps plot with idl...
d=`pwd`  
/usr/local/bin/idl<<IDL
print, "$d"
@~/ace/swindal/c
smmq, file="$d"+'/axlv2_mmq.dat', data=mmq
exit
IDL

# keep these last
echo run finished at `date`
ENDOFJOB
