#!/bin/bash
# genero la tabla para dsp graficarla con gnuplot
# ./genTab file numData

for ((i=1;i<=$2;i++))
do
	MSE_TRAIN=`sed '-n '"${i}"'p '"$1" | awk -F ' ' '{print $2}'`
	MSE_VAL=`sed -n "${i}p" $1 | awk -F ' ' '{print $3}'`
	MSE_TEST=`sed -n "${i}p" $1 | awk -F ' ' '{print $4}'`
	echo $i $MSE_TRAIN $MSE_VAL $MSE_TEST >> tabPlot
done
