cd $PBS_O_WORKDIR
local=$PBS_O_WORKDIR
#path should be set to directory that contains analyse_data (e.g. /home/ivar/berger/projects/ionpositions/. (make sure that programs are already build by rebuild.sh!)
# Next three variables must be set by user to initialize the script correctly
path="/data/ivar/berger/testco"

cd $PBS_O_WORKDIR
echo "cp $path/src/calcswicslv2.py ."
cp $path\src/calcswicslv2.py .
#lv2 data products are calculated
echo "ipython calcswicslv2.py"
ipython calcswicslv2.py
