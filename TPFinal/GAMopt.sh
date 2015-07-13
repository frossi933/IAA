#!/bin/bash
# optimizacion de los parametros del algoritmo

MAX=0.0
G=0
C=0

rm model
for i in 0.001 0.01 0.03 0.05 0.07 0.08 0.09 0.1 0.3 0.5 0.7 0.9
do
	for g in 0.001 0.005 0.01 0.05 0.07 0.08 0.09 0.1 0.3 0.5 0.7 0.9 1.0
	do
		echo `svm_learn -c $i -t 2 -g $g trainv.example model` >  /etc/null
		ERROR=`svm_classify valid.example model output | sed -n '4p' | awk -F ': ' '{print $2}' | awk -F '%' '{print $1}'`
		ST=`echo "$ERROR > $MAX" | bc`
		if [ $ST -eq 1 ]
		then
			G=$g
			C=$i
			MAX=$ERROR
		fi
	done
done

echo "C: $C G: $G Error: $MAX"
