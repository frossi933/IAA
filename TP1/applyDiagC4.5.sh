#!/bin/bash
# ./applyDiagC4.5.sh dir n

cd $1
res=${1##*/}".res"
touch $res
sizeBP=0
errorBP=0.0
sizeAP=0
errorAP=0.0

for ((i=1;i<=($2);i++))
do
	sal=`c4.5 -g -f diag_${1##*/}$i -v 0 | grep "<<" | sed s/'('/' '/g | sed s/'%)'/' '/g | awk -F ' ' '{print $0}'`
	echo $sal >> $res
	sizeBP=$(($sizeBP + `echo $sal | awk -F ' ' '{print $1}'`))
	ebp=`echo $sal | awk -F ' ' '{print $3}' | sed s/'%'//`
	errorBP=`echo "scale=2;$errorBP + $ebp" | bc`
	sizeAP=$(($sizeAP + `echo $sal | awk -F ' ' '{print $4}'`))
	eap=`echo $sal | awk -F ' ' '{print $6}' | sed s/'%'//`
	errorAP=`echo "scale=2;$errorAP + $eap" | bc`
done
echo `echo "scale=2;$sizeBP / $2" | bc` `echo "scale=2;$errorBP / $2" | bc` `echo "scale=2;$sizeAP / $2" | bc` `echo "scale=2;$errorAP / $2" | bc` >> $res
