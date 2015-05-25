#!/bin/bash
# Ejercicio C:
# ./ejc.sh file dir

FILE=$1
BP=/home/chino/Desktop/IAA/TP2/bp

cd $2
for i in {1..10}
do
	$BP "../"$FILE >> salida
	rm ../1.wts
	mv "../"$FILE".predic" $FILE$i".predic"
	mv "../"$FILE".mse" $FILE$i".mse"
done
