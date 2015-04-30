#!/usr/bin/bash

# ~~~~~~~~~~~~~~~~~
# PARALLEL datasets
# ~~~~~~~~~~~~~~~~~

# ./genB d c ptos sets sten

genb="/home/chino/Desktop/IAA/TP0/genB "

inputs=$1
c=$2
n=$3
m=$4
sten=$5

mkdir $sten
cd $sten

for ((i=1;i<=$m;i++))
do
	eval "$genb $inputs $n $c par_$sten$i"
	sleep 1
	echo "datasets $sten$i generado..."
done

echo "fin"
