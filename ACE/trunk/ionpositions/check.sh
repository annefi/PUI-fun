rm incomplete.in
startdoy=1
enddoy=365
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
#    echo erg_*|sed "s/erg_\*//g"|wc -w;ls -1 erg_*
    erg=`echo erg_*|wc -w`
    flux=`echo flux_*|wc -w`
    res=`echo res_*|wc -w`
    elem=`echo elem_*|wc -w`
    cd -
    if [ $erg != $flux ]; then
	echo $dirname >> incomplete.in
    elif [ $erg != $res ]; then
	echo $dirname >> incomplete.in
    elif [ $erg != $elem ]; then
	echo $dirname >> incomplete.in
    fi
done

