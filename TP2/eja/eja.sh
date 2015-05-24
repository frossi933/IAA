#!/bin/bash
# ejercicio A:
#
# ./eja file

I=0
BP=/home/chino/Desktop/IAA/TP2/bp

train() {
	echo "entrenando $3 - $1 $2 ..."
	for i in {1..10}
	do
		$BP $3 >> "sal_${1}_${2}"
	done
	echo "fin entrenamiento $1 $2 ..."
}

for lr in 0.1 0.05 0.01 0.005 0.001
do
	for m in 0.0 0.3 0.5 0.7 0.9
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
		echo $lr >> $FILE
		echo $m >> $FILE
		echo "200" >> $FILE
		echo "0" >> $FILE
		echo "0" >> $FILE
		echo "0" >> $FILE
		echo "spawn $lr $m ..."
		train $lr $m ${1}${I}
		I=$(( $I+1 ))
	done
done

echo "esperando..."
wait
echo "fin"
