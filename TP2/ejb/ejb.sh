#!/bin/bash
# ejercicio A:
#
# ./eja file

I=0
BP=/home/chino/Desktop/IAA/TP2/bp

train() {
	echo "entrenando $2 - $1 ..."
	for i in {1..10}
	do
		$BP $2 >> "sal_${1}"
	done
	echo "fin entrenamiento $1 $2 ..."
}

for n in 2 5 10 20 40
do
	cp ${1}".data" ${1}${I}".data"
	cp ${1}".test" ${1}${I}".test"
	FILE=${1}${I}".net"
	echo "2" > $FILE
	echo $n >> $FILE
	echo "1" >> $FILE
	echo "2000" >> $FILE
	echo "1600" >> $FILE
	echo "2000" >> $FILE
	echo "40000" >> $FILE
	echo "0.01" >> $FILE
	echo "0.5" >> $FILE
	echo "400" >> $FILE
	echo "0" >> $FILE
	echo "0" >> $FILE
	echo "0" >> $FILE
	echo "spawn $n neuronas ..."
	train $n ${1}${I}
	I=$(( $I+1 ))
done

echo "esperando..."
wait
echo "fin"
