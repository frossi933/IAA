#!/usr/bin/bash

# ~~~~~~~~~~~~~~~~~
# DIAGONAL datasets
# ~~~~~~~~~~~~~~~~~

# ./genA d c ptos sets sten
gena="/home/chino/Desktop/IAA/TP0/genA "

inputs=$1
c=$2
n=$3
m=$4
sten=$5

mkdir $sten
cd $sten

for ((i=1;i<=$m;i++))
do
	eval "$gena $inputs $n $c diag_$sten$i"
	sleep 1
	echo "datasets $sten$i generado..."
done

echo "fin"

