#!/bin/sh
#if run under batch-queue the path of the working directory has to be set explicitly!!!
#check if number of arguments is ok!
#if [ -z "$tmp_year" ]; then 
#    echo "year is not set"
#    exit 1
#fi
#if [ -z "$tmp_resolution" ]; then 
#    echo "year is not set"
#    exit 1
#fi
#if [ -z "$tmp_doy" ]; then 
#    echo "year is not set"
#    exit 1
#fi
#year=$tmp_year
#resolution=$tmp_resolution
#doy=$tmp_doy
#echo "calling ./analyse_swics_queue_auto.sh $year $resolution $doy"

cd $PBS_O_WORKDIR
local=$PBS_O_WORKDIR
#path should be set to directory that contains analyse_data (e.g. /home/ivar/berger/projects/ionpositions/. (make sure that programs are already build by rebuild.sh!)
# Next three variables must be set by user to initialize the script correctly
path="/data/ivar/berger/testco/"
year=2003
resolution=1d

cd $PBS_O_WORKDIR
#copy all necessary files into working directory
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
#analysis via maximum-likeliehood  
echo "./analyse_data"
./analyse_data
#remove ASCII et_slices, to save disk space
echo "remove et-slices"
rm axlv2_et_slices_*
#lv2 data products are calculated
export PYTHONPATH=$PYTHONPATH:$path
echo $PYTHONPATH
echo "ipython calcswicslv2.py"
ipython calcswicslv2.py
echo "remove fit.log"
rm fit.log
echo "remove axlv2"
rm axlv2
echo "remove axlv2.in"
rm axlv2.in
echo "remove run-axlv2-many.pl"
rm run-axlv2-many.pl
