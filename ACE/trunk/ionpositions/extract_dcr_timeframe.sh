startdoy=1
enddoy=1
umask 2
path="/data/ivar/berger/testco/"
year=2007
resolution=12m

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
    echo "cp $path\src/extract_dcr_oneday.py ."
    cp $path\src/extract_dcr_oneday.py .
    echo "cp $path\america/axlv2/axlv2 ."
    cp $path\america/axlv2/axlv2 .
    echo "cp $path\america/axlv2/tools/axlv2.in ."
    cp $path\america/axlv2/tools/axlv2.in .
    echo "cp $path\america/axlv2/tools/run-axlv2-many.pl ."
    cp $path\america/axlv2/tools/run-axlv2-many.pl .
    #starts extraction of et-slices using the axlv2 data processor from Jim Raines
    doy=`echo $PWD | sed s/'\/.*\/'$year'\/'/''/g`
    echo "./run-axlv2-many.pl $year$doy --accum=$resolution --config_file='axlv2.in'"
    ./run-axlv2-many.pl $year$doy --accum=$resolution --config_file='axlv2.in'
    #creates input lists for analyse_data and swicslv3
    (echo axlv2_et_slices_*|sed "s/axlv2_et_slices_\*//g"|wc -w;ls -1 axlv2_et_slices_*) > list.in 
    echo ./ > pathlist.in
    
    python extract_dcr_oneday.py

    cd -
done
