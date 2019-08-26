#!/bin/sh
if [ `groups|cut -f 1 -d " "` != ace ]; then 
    echo "Changing group to ace..."
    sg ace -c $0
    exit
fi

#if [ -z "$4" ]; then 
#    echo "Usage :"
#    echo "\$./analyse_timeframe.sh year resolution startdoy enddoy"
#    echo "year = 4 digits e.g. 2007"
#    echo "resolution= 1h or 1d or 12m"
#    echo "startdoy and enddoy = 3 digits e.g. 001 enddoy should be grater than or equal to startdoy"
#    exit 1
#fi
#export tmp_year=$1
#export tmp_resolution=$2
#export startdoy=$3
#export enddoy=$4
#echo "year=$tmp_year"
#echo "resolution=$tmp_resolution"
#echo "startdoy=$tmp_startdoy"
#echo "enddoy=$tmp_enddoy"
startdoy=20
enddoy=30
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
    mkdir $dirname
    cp analyse_swics_protons.sh ./$dirname
    cd $dirname
    ./analyse_swics_protons.sh
    cd -
done
umask 22