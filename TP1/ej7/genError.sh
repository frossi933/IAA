#/bin/bash
# ./genError 100 200 300 ...

n=$(($# - 1))
TRresd="resume_diag_train.dat"
TEresd="resume_diag_test.dat"
TRresp="resume_par_train.dat"
TEresp="resume_par_test.dat"
touch $TRresd
touch $TEresd
touch $TRresp
touch $TEresp

for i in $@
do
	prom=`cat training_diag_$i/diag_training/diag_training.res | tail -2`
	# Train Test
	# TRsizeBP TRerrorBP TRsizeAP TRerrorAP TEsizeBP TEerrorBP TEsizeAP TEerrorAP
	train=`echo $prom | awk -F ' ' '{print $1 , $2 , $3 , $4}'`
	test=`echo $prom | awk -F ' ' '{print $5 , $6 , $7 , $8}'`
	echo "$i $train" >> $TRresd
	echo "$i $test" >> $TEresd
	prom=`cat training_par_$i/par_training/par_training.res | tail -2`
	train=`echo $prom | awk -F ' ' '{print $1 , $2 , $3 , $4}'`
	test=`echo $prom | awk -F ' ' '{print $5 , $6 , $7 , $8}'`
	echo "$i $train" >> $TRresp
	echo "$i $test" >> $TEresp
done
