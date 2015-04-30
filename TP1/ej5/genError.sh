#/bin/bash
# ./genError 100 200 300 ...

n=$(($# - 1))
resd="resume_diag.dat"
resp="resume_par.dat"
touch $resd
touch $resp

for i in $@
do
	prom=`cat training_diag_$i/training_diag_$i.res | grep -v "<<"`
	# sizeBP errorBP sizeAP errorAP
	echo "$i $prom" >> $resd
	prom=`cat training_par_$i/training_par_$i.res | grep -v "<<"`
	echo "$i $prom" >> $resp
done
