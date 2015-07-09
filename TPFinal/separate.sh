#!/bin/bash
# transformo el archivo .data al archivo de ejemplo necesario para svmlight

DATA=${1}.data
C0=${1}0.data
C1=${1}1.data

rm $C0
rm $C1
while read -r line
do
	NEWLINE=( `echo $line | awk -F ',' '{print $1 " " $2 " " $3 " " $4 " " $5 " " $6 " " $7 " " $8 " " $9 " " $10}'` )
	if [ ${NEWLINE[9]} == "0" ]
	then
		echo ${NEWLINE[*]} >> $C0
	else
		echo ${NEWLINE[*]} >> $C1
	fi
done < $DATA

