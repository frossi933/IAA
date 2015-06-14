#!/bin/sh

NB=/home/chino/Desktop/IAA/TP3/ej_d/nb_n
TAB=tab

rm $TAB
touch $TAB

for v in 1600 1800 1900
do
	for b in 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100
	do
		echo 2 > esp.nb
		echo 2 >> esp.nb
		echo 2000 >> esp.nb
		echo $v >> esp.nb
		echo 2000 >> esp.nb
		echo 0 >> esp.nb
		echo 0 >> esp.nb
		echo $b >> esp.nb
		SAL=( `$NB esp | sed -n '15p;16p;17p' | awk -F ':' '{print $2}'` )
		TR=${SAL[0]:0:5}
		VAL=${SAL[1]:0:5}
		TE=${SAL[2]:0:5}
		echo $v $b $TR $VAL $TE >> $TAB
		rm esp.predic
		sleep 1
	done
done
