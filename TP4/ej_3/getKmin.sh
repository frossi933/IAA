#!/bin/bash
# obtengo el K minimo segun el error minimo de validacion

INFO=${1}.info
KNN=/home/chino/Desktop/IAA/TP4/ej_1/knn
MIN=0
BEST=100.0
ERRORES=errores

rm $ERRORES
touch $ERRORES
for k in {1..40}
do
	sed '7 s/.*/'"$k"'/' $INFO > tmp
	mv tmp $INFO 
	SAL=`$KNN $1 | sed -n '16p' | awk -F ':' '{print $2}'`
	VAL=${SAL:0:5}
	echo $k $VAL >> $ERRORES
	if (( $(bc <<< "$BEST > $VAL") == 1 ))
	then
		MIN=$k
		BEST=$VAL
	fi
done
echo $MIN $BEST > best
