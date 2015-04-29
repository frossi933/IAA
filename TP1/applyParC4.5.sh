#!/bin/bash

# ./applyDiagC4.5.sh dir n

cd $1
for ((i=1;i<=($2);i++))
do
	eval "c4.5 -g -f par_${1##*/}$i -v 0"
done
