#!/bin/bash
# transformo el archivo .data al archivo de ejemplo necesario para svmlight

DATA=${1}.data
EXA=${1}.example

rm $EXA
while read -r line
do
	NEWLINE=( `echo $line | awk -F ' ' '{print $10 " 1:" $1 " 2:" $2 " 3:" $3 " 4:" $4 " 5:" $5 " 6:" $6 " 7:" $7 " 8:" $8 " 9:" $9}'` )
	if [ ${NEWLINE[0]} == "0" ]
	then
		NEWLINE[0]="-1"
	fi
	echo ${NEWLINE[*]} >> $EXA
done < $DATA

