#!/bin/bash

# Obtenemos el promedio de cada caso

DFILE=`pwd`/diag_tab
PFILE=`pwd`/par_tab
SUM=0.0
N=0
PROM1=0.0
PROM2=0.0

cd data
for i in 2 3 5 7 10 15 30
do
	cd training_diag_${i}/diag_training
	while read line
	do
		SUM=`echo "scale=6; $SUM + $line" | bc`
		N=$((N+1))
	done < train_diag_$i
	PROM1=`echo "scale=6; $SUM / $N" | bc`

	SUM=0.0
	N=0
	while read line
	do
		SUM=`echo "scale=6; $SUM + $line" | bc`
		N=$((N+1))
	done < test_diag_$i
	PROM2=`echo "scale=6; $SUM / $N" | bc`
	echo "$i $PROM1 $PROM2" >> $DFILE


	cd ../../training_par_$i/par_training
	SUM=0.0
	N=0
	while read line
	do
		SUM=`echo "scale=6; $SUM + $line" | bc`
		N=$((N+1))
	done < train_par_$i
	PROM1=`echo "scale=6; $SUM / $N" | bc`

	SUM=0.0
	N=0
	while read line
	do
		SUM=`echo "scale=6; $SUM + $line" | bc`
		N=$((N+1))
	done < test_par_$i
	PROM2=`echo "scale=6; $SUM / $N" | bc`
	echo "$i $PROM1 $PROM2" >> $PFILE

	cd ../..
done
