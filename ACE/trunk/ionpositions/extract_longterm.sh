#!/bin/bash
#if [ `groups|cut -f 1 -d " "` != ace ]; then 
#    echo "Changing group to ace..."
#    sg ace -c $0
#    exit
#fi

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
startdoy=001
enddoy=365
umask 2

path="/data/ivar/berger/testco/"
startyear=2001
endyear=2010
resolution=1d

for year in `seq $startyear 1 $endyear`; do 
    mkdir $year
    cd $year
    echo "cp $path\america/axlv2/axlv2 ."
    cp $path\america/axlv2/axlv2 .
    echo "cp $path\america/axlv2/tools/extract_longterm.in ."
    cp $path\america/axlv2/tools/extract_longterm.in .
    echo "cp $path\america/axlv2/tools/run-axlv2-many.pl ."
    cp $path\america/axlv2/tools/run-axlv2-many.pl .
    #starts extraction of et-slices using the axlv2 data processor from Jim Raines
    echo "./run-axlv2-many.pl $year$doy --accum=$resolution --config_file='axlv2.in'"
    ./run-axlv2-many.pl $year$startdoy $year$enddoy --accum=$resolution --config_file='extract_longterm.in'
    cd -
done
umask 22