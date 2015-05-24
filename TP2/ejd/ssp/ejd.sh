#!/bin/bash

# Ejercicio (d):
# ./ejd.sh

BP2=/home/chino/Desktop/IAA/TP2/ejd/bp2

for g in 1.0 0.1 0.01 0.001 0.0001 0.00001 0.000001 0.0000001 0.00000001
do
	cp ssp.data ssp${g}.data
	cp ssp.test ssp${g}.test
	sed '14 s/a/'"${g}"'/' ssp.net >> ssp${g}.net
	$BP2 ssp${g} >> sal_${g}
done
