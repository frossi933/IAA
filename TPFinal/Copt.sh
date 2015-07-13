#!/bin/bash
# optimizacion de los parametros del algoritmo

MAX=0.0
C=0

rm model
for c in 0.0001 0.0005 0.001 0.005 0.01 0.05 0.07 0.09 0.1 0.3 0.4 0.5 0.7 0.9 1.0
do
	echo `svm_learn -c $c trainv.example model` >  tmp
	ERROR=`svm_classify valid.example model output | sed -n '4p' | awk -F ': ' '{print $2}' | awk -F '%' '{print $1}'`
	ST=`echo "$ERROR > $MAX" | bc`
	if [ $ST -eq 1 ]
	then
		C=$c
		MAX=$ERROR
	fi
done
	rm tmp
	echo "C: $C Error: $MAX"
