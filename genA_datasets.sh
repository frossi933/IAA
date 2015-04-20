#!/usr/bin/bash

# ~~~~~~~~~~~~~~~~~
# DIAGONAL datasets
# ~~~~~~~~~~~~~~~~~

if [$# > 0]
then
	echo "Error en los argumentos."
	exit 1
fi

gena="/home/chino/Desktop/IAA/TP0/genA "

echo "inputs? "
read inputs
echo "C? "
read c
echo "cantidad de puntos? "
read n
echo "cantidad de sets?"
read m
echo "Nombre del dataset? "
read sten

mkdir $sten
cd $sten

for ((i=1;i<=$m;i++))
do
	eval "$gena $inputs $n $c diag_$sten$i"
	echo "datasets $sten$i generado..."
done

echo "fin"

