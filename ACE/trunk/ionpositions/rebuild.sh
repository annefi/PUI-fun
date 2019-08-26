local=$PWD
#path should be set to directory that contains analyse_data (e.g. /home/ivar/berger/projects/ionpositions/
path=$local

#rebuild all necessary programs for analyse_data
cd $path\/america/axlv2/;make;
cd $path\/libetph/;./rebuild.sh
cd $path\/libetph/;./configure
cd $path\/libetph/;make
cd $path;make

