#path should be set to directory that contains analyse_data (e.g. /home/ivar/berger/projects/ionpositions/
path="/home/ivar/berger/projects/ionpositions/"

#copy all necessary files into working directory
cp $path\ion_para.dat .
cp $path\src/generateerrorpara.py .
cp $path\src/error_analyse_data .
cp $path\src/testcalcerror.py .

#generate parameterfiles
python generateerrorpara.py
#creates input lists for errordatagen 
(echo error_para_*|wc -w;ls -1 error_para_*) > paralist.in 
#do fitting
./error_analyse_data
#creates input lists for errordatagen 
(echo erg_error_data_*|ls -1 erg_error_data_*) > erglist.in 
#calculate errors
python testcalcerror.py