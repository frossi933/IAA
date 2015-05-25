#!/bin/bash

# agrego la primer columna con las epocas
# ./addEp step file

STEP=$1

while read line
do
	echo $STEP $line >> ${2}_tab
	STEP=$(( $STEP+$1 ))
done < $2
	
