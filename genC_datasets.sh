#!/usr/bin/bash

# ~~~~~~~~~~~~~~~~~~
# ESPIRALES datasets
# ~~~~~~~~~~~~~~~~~~

if [$# > 0]
then
	echo "Error en los argumentos."
	exit 1
fi

genc="/home/chino/Desktop/IAA/TP0/genC "

echo "cantidad de puntos?"
read n
echo "cantidad de sets?"
read m
echo "Nombre del dataset? "
read sten

mkdir $sten
cd $sten

for ((i=1;i<=$m;i++))
do
	eval "$genc $n esp_$sten$i"
	echo "datasets $sten$i generado..."
done

echo "fin"
