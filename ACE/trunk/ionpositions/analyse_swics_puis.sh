#path should be set to directory that contains analyse_data (e.g. /home/ivar/berger/projects/ionpositions/. (make sure that programs are already build by rebuild.sh!)
# Next three variables must be set by user to initialize the script correctly
path="/data/ivar/berger/testco/"
path2="/home/ivar/berger/projects/ionpositions/"
path3="/home/ivar/berger/projects/puis/"
year=2007
resolution=1d

#copy all necessary files into working directory
echo "cp $path3\ion_para.dat ."
cp $path3\/ion_para.dat .
echo "cp $path2\src/calcprotons.py ."
cp $path2\/src/calcpuis.py .
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
python calcpuis.py
#remove ASCII et_slices, to save disk space
echo "remove et-slices"
rm axlv2_et_slices_*
echo "remove axlv2"
rm axlv2
echo "remove axlv2.in"
rm axlv2.in
echo "remove run-axlv2-many.pl"
rm run-axlv2-many.pl
