i=1
while [ $i -le 58 ]
do
  echo python plotlongtermpos.py $i
  python plotlongtermpos.py $i
  i=`expr $i + 1`
done