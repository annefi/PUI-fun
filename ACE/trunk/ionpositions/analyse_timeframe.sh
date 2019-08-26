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
#echo "year=$tmp_year"
#echo "resolution=$tmp_resolution"
#echo "startdoy=$tmp_startdoy"
#echo "enddoy=$tmp_enddoy"
startdoy=1
enddoy=2
umask 2

path="/data/ivar/berger/testco/"
year=2003
resolution=1d

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
    cd $dirname
    #copy all necessary files into working directory
    echo "cp $path\analyse_timesteps_queue.py ."
    cp $path\analyse_timesteps_queue.py .
    echo "cp $path\analyse_data ."
    cp $path\analyse_data .
    echo "cp $path\analyse_data.in ."
    cp $path\analyse_data.in .
    echo "cp $path\ion_para.dat ."
    cp $path\ion_para.dat .
    echo "cp $path\america/axlv2/axlv2 ."
    cp $path\america/axlv2/axlv2 .
    echo "cp $path\america/axlv2/tools/axlv2.in ."
    cp $path\america/axlv2/tools/axlv2.in .
    echo "cp $path\america/axlv2/tools/run-axlv2-many.pl ."
    cp $path\america/axlv2/tools/run-axlv2-many.pl .
    echo "cp $path\src/calcswicslv2.py ."
    cp $path\src/calcswicslv2.py .
    #starts extraction of et-slices using the axlv2 data processor from Jim Raines
    doy=`echo $PWD | sed s/'\/.*\/'$year'\/'/''/g`
    echo "./run-axlv2-many.pl $year$doy --accum=$resolution --config_file='axlv2.in'"
    ./run-axlv2-many.pl $year$doy --accum=$resolution --config_file='axlv2.in'
    #creates input lists for analyse_data and swicslv3
    (echo axlv2_et_slices_*|sed "s/axlv2_et_slices_\*//g"|wc -w;ls -1 axlv2_et_slices_*) > list.in 
    echo ./ > pathlist.in
    
    python analyse_timesteps_queue.py

    cd -
done
umask 22