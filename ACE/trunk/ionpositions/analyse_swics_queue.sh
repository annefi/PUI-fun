#if run under batch-queue the path of the working directory has to be set explicitly!!!
cd $PBS_O_WORKDIR
local=$PBS_O_WORKDIR
#path should be set to directory that contains analyse_data (e.g. /home/ivar/berger/projects/ionpositions/. (make sure that programs are already build by rebuild.sh!)
path="/data/ivar/berger/testco/"

cd $PBS_O_WORKDIR
#copy all necessary files into working directory
cp $path\analyse_data .
cp $path\analyse_data.in .
cp $path\ion_para_mitalles_clean.dat .\ion_para.dat
cp $path\america/axlv2/axlv2 .
cp $path\america/axlv2/tools/axlv2.in .
cp $path\america/axlv2/tools/run-axlv2-many.pl .
cp $path\src/calcswicslv2.py .
#starts extraction of et-slices using the axlv2 data processor from Jim Raines
./run-axlv2-many.pl 2001001 --accum=1d --config_file='axlv2.in'
#creates input lists for analyse_data and swicslv3
(echo axlv2_et_slices_*|wc -w;ls -1 axlv2_et_slices_*) > list.in 
echo ./ > pathlist.in
#analysis via maximum-likeliehood  
./analyse_data
#in this place the axlv2_et_slices_* files should be removed in further versions to safe disk space!
#lv2 data products are calculated
ipython calcswicslv2.py
