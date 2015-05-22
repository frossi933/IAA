#!/bin/bash

# Obtenemos el test discreto a partir de las salids del algoritmo

# ./getError

for lr in 0.1 0.05 0.01 0.005 0.001
do
	for m in 0.0 0.3 0.5 0.7 0.9
	do
		ARR=(`grep "Test discreto:" sal_${lr}_${m}  | awk -F ':' '{print $2}' | sed s/'%'/' '/g`)
		for i in {1..10}
		do
			echo ${ARR[$i]} >> tmp
		done
		ARRSORT=( `sort -g tmp` )
		rm tmp
		MED=`echo "scale=2; ( ${ARRSORT[5]} + ${ARRSORT[6]} ) / 2.0" | bc`
		echo $lr $m $MED >> tab
	done
done
