#!/bin/bash

# Obtenemos el test discreto a partir de las salids del algoritmo

# ./getError

for n in 2 5 10 20 40
do
	ARR=(`grep "Test discreto:" sal_${n}  | awk -F ':' '{print $2}' | sed s/'%'/' '/g`)
	for i in {1..10}
	do
		echo ${ARR[$i]} >> tmp
	done
	ARRSORT=( `sort -g tmp` )
	rm tmp
	MED=`echo "scale=2; ( ${ARRSORT[5]} + ${ARRSORT[6]} ) / 2.0" | bc`
	echo $n $MED >> tab
done
