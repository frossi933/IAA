#!/bin/bash


C0=${1}0.data
C1=${1}1.data

I=0
while read -r line
do
	N=`echo "scale=0;$I % 10" | bc` 
	echo $line >> set${N}.example
	I=$(( $I+1 ))
done < $C0

I=0
while read -r line
do
	N=`echo "scale=0;$I % 10" | bc`
	echo $line >> set${N}.example
	I=$(( $I+1 ))
done < $C1

