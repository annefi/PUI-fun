#path should be set to directory that contains analyse_data (e.g. /home/ivar/berger/projects/ionpositions/. (make sure that code is already build via rebuild.sh!)
path="/home/kleopatra/mu/Desktop/swics/c13/"
local=$PWD

cd $local
#copy all necessary files into working directory
cp $path\analyse_data .
cp $path\analyse_data.in .
cp $path\ion_para.dat .
cp $path\america/axlv2/axlv2 .
cp $path\america/axlv2/tools/axlv2.in .
cp $path\america/axlv2/tools/run-axlv2-many.pl .
#starts extraction of et-slices using the axlv2 data processor from Jim Raines
./run-axlv2-many.pl 2007003 2007003 --accum=1h --config_file='axlv2.in'
#creates input lists for analyse_data and swicslv3
(echo axlv2_et_slices_*|wc -w;ls -1 axlv2_et_slices_*) > list.in 
echo ./ > pathlist.in
