#!/bin/bash
# obtengo el K minimo segun el error minimo de validacion

INFO=${1}.info
KNND=/home/chino/Desktop/IAA/TP4/ej_4/knnd
MIN=0
BEST=100.0
ERRORES=errores

rm $ERRORES
touch $ERRORES
for d in {1..50}
do
	sed '7 s/.*/'"$d"'/' $INFO > tmp
	mv tmp $INFO 
	SAL=`$KNND $1 | sed -n '16p' | awk -F ':' '{print $2}'`
	VAL=${SAL:0:5}
	echo $d $VAL >> $ERRORES
	if (( $(bc <<< "$BEST > $VAL") == 1 ))
	then
		MIN=$d
		BEST=$VAL
	fi
done
echo $MIN > best
