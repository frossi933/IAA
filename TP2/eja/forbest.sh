#!/bin/bash
# genero diez entrenamientos para quedarme con el mas representativo para graficarlo
#
# ./eja file lr m

I=0
BP=/home/chino/Desktop/IAA/TP2/bp


for I in {1..10}
do
	cp ${1}".data" ${1}${I}".data"
	cp ${1}".test" ${1}${I}".test"
	FILE=${1}${I}".net"
	echo "2" > $FILE
	echo "6" >> $FILE
	echo "1" >> $FILE
	echo "500" >> $FILE
	echo "400" >> $FILE
	echo "2000" >> $FILE
	echo "40000" >> $FILE
	echo $2 >> $FILE
	echo $3 >> $FILE
	echo "200" >> $FILE
	echo "0" >> $FILE
	echo "0" >> $FILE
	echo "0" >> $FILE
	echo "spawn $lr $m ..."
	$BP ${1}${I}	
done

echo "esperando..."
wait
echo "fin"
