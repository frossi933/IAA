#!/bin/bash

NB=/home/chino/Desktop/IAA/TP3/ej_a/nb_n
DT=c4.5

rm tab
rm dt_tab
rm nb_tab
rm svml_tab
rm svmnl_tab
touch tab
touch dt_tab
touch nb_tab
touch svml_tab
touch svmnl_tab
for i in {0..9}
do
	cd ${1}$i
	rm model
	echo `svm_learn -c 0.05 train.example model` > salida$i		# linear kernel
	RES=`svm_classify test.example model output_l | sed -n '4p' | awk -F ': ' '{print $2}' | awk -F '%' '{print $1}'`
	ERRORL=`echo "scale=2; 100.0 - $RES" | bc`

	rm model
	echo `svm_learn -c 0.9 -t 2 -g 0.5 train.example model` >> salida$i	# radial basis kernel
	RES=`svm_classify test.example model output_p | sed -n '4p' | awk -F ': ' '{print $2}' | awk -F '%' '{print $1}'`
	ERRORNL=`echo "scale=2; 100.0 - $RES" | bc`

	echo 9 >${1}${i}.nb
	echo 2 >> ${1}${i}.nb
	PTOT=`wc -l train.data | awk -F ' ' '{print $1}'`
	echo $PTOT >> ${1}${i}.nb
	echo $PTOT >> ${1}${i}.nb
	echo `wc -l test.data` | awk -F ' ' '{print $1}' >> ${1}${i}.nb
	echo 0 >> ${1}${i}.nb
	echo 0 >> ${1}${i}.nb
	sed s/' '/','/g train.data > ${1}${i}.data
	sed s/' '/','/g test.data > ${1}${i}.test
	SAL=( `$NB ${1}${i} | sed -n '14p;16p' | awk -F ':' '{print $2}'` )
	ERRORNB=${SAL[1]:0:5}
	
	cp cmc.names ${1}${i}.names
	ERRORDT=`$DT -g -u -f ${1}${i} -v 0 | grep "<<" | sed s/'('/' '/g | sed s/'%)'/' '/g | awk -F ' ' '{print $6}' | tail -n 1`

	cd ..
	echo $i $ERRORDT $ERRORNB $ERRORL $ERRORNL >> tab
	echo $ERRORDT >> dt_tab
	echo $ERRORNB >> nb_tab
	echo $ERRORL >> svml_tab
	echo $ERRORNL >> svmnl_tab
done
