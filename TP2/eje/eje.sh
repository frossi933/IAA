#!/bin/bash
# Ejercicio (e)

# ./eje

BP=/home/chino/Desktop/IAA/TP2/eje/bp

cd data
for d in 2 3 5 7 10 15 30
do
	cd training_diag_$d/diag_training/
	for i in {1..20}
	do
		$BP diag_diag_training$i | grep ">>" | awk -F ' ' '{print $3 " " $5}' >> salida_diag_$d
		rm 1.wts 
	done
	cd ../../training_par_$d/par_training/
	for i in {1..20}
	do
		$BP par_par_training$i | grep ">>" | awk -F ' ' '{print $3 " " $5}' >> salida_par_$d
		rm 1.wts
	done
	cd ../..
done
