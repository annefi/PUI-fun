#!/bin/sh
if [ `groups|cut -f 1 -d " "` != ace ]; then 
    echo "Changing group to ace..."
    sg ace -c $0
    exit
fi

startdoy=163
enddoy=194
umask 2
for i in `seq $startdoy 1 $enddoy`; do 
    if [ `echo $i | wc -c` == 2 ]; then
	dirname=00$i
    fi
    if [ `echo $i | wc -c` == 3 ]; then
	dirname=0$i
    fi
    if [ `echo $i | wc -c` == 4 ]; then
	dirname=$i
    fi
    cd $dirname
    rm res_*
    rm flux_*
    rm elem_*
    rm fit.log
    cd -
done
umask 22