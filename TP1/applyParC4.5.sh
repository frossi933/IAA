#!/bin/bash
# ./applyParC4.5.sh dir n

cd $1
res=${1##*/}".res"
touch $res
TRsizeBP=0
TEsizeBP=0
TRerrorBP=0.0
TEerrorBP=0.0
TRsizeAP=0
TEsizeAP=0
TRerrorAP=0.0
TEerrorAP=0.0

for ((i=1;i<=($2);i++))
do
	sal=`c4.5 -g -u -f par_${1##*/}$i -v 0 | grep "<<" | sed s/'('/' '/g | sed s/'%)'/' '/g`
	train=`echo $sal | awk -F '<<' '{print $1}'`
	test=`echo $sal | awk -F '<<' '{print $2}'`
	echo $train >> $res
	echo $test >> $res
	TRsizeBP=$(($TRsizeBP + `echo $train | awk -F ' ' '{print $1}'`))
	TEsizeBP=$(($TEsizeBP + `echo $test | awk -F ' ' '{print $1}'`))
#	echo $TRsizeBP
	TRebp=`echo $train | awk -F ' ' '{print $3}'`
	TEebp=`echo $test | awk -F ' ' '{print $3}'`
#	echo $TRebp
	TRerrorBP=`echo "scale=2;$TRerrorBP + $TRebp" | bc`
	TEerrorBP=`echo "scale=2;$TEerrorBP + $TEebp" | bc`
#	echo $TRerrorBP
	TRsizeAP=$(($TRsizeAP + `echo $train | awk -F ' ' '{print $4}'`))
	TEsizeAP=$(($TEsizeAP + `echo $test | awk -F ' ' '{print $4}'`))
#	echo $TRsizeAP
	TReap=`echo $train | awk -F ' ' '{print $6}'`
	TEeap=`echo $test | awk -F ' ' '{print $6}'`
#	echo $TReap
	TRerrorAP=`echo "scale=2;$TRerrorAP + $TReap" | bc`
	TEerrorAP=`echo "scale=2;$TEerrorAP + $TEeap" | bc`
#	echo $TRerrorAP
done
echo `echo "scale=2;$TRsizeBP / $2" | bc` `echo "scale=2;$TRerrorBP / $2" | bc` `echo "scale=2;$TRsizeAP / $2" | bc` `echo "scale=2;$TRerrorAP / $2" | bc` >> $res
echo `echo "scale=2;$TEsizeBP / $2" | bc` `echo "scale=2;$TEerrorBP / $2" | bc` `echo "scale=2;$TEsizeAP / $2" | bc` `echo "scale=2;$TEerrorAP / $2" | bc` >> $res
