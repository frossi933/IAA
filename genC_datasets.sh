#!/usr/bin/bash

# ~~~~~~~~~~~~~~~~~~
# ESPIRALES datasets
# ~~~~~~~~~~~~~~~~~~

# ./genC ptos sets sten

genc="/home/chino/Desktop/IAA/TP0/genC "

n=$1
m=$2
sten=$3

mkdir $sten
cd $sten

for ((i=1;i<=$m;i++))
do
	eval "$genc $n esp_$sten$i"
	sleep 1
	echo "datasets $sten$i generado..."
done

echo "fin"
