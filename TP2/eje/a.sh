#!/bin/bash
# Ejercicio (e)

# ./eje

BP=/home/chino/Desktop/IAA/TP2/eje/bp
I=0

cd data
for d in 2 3 5 7 10 15 30
do
	cd training_diag_$d/diag_training/
	I=0
	rm test_diag_$d > /dev/null
	rm train_diag_$d >> /dev/null
	while read line
	do
		if [ $((I%2)) -eq 0 ]
		then
			echo $line >> test_diag_$d
		else
			echo $line >> train_diag_$d
		fi
		I=$((I+1))
	done < salida_diag_$d
	cd ../../training_par_$d/par_training/
	
	I=0
	rm test_par_$d > /dev/null
	rm train_par_$d > /dev/null
	while read line
	do
		if [ $((I%2)) -eq 0 ]
		then
			echo $line >> test_par_$d
		else
			echo $line >> train_par_$d
		fi
		I=$((I+1))
	done < salida_par_$d
	cd ../..
done
