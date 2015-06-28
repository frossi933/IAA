#!/bin/bash
# borramos archivos anteriores y aplico knn usando validacion y k=1

KNND=/home/chino/Desktop/IAA/TP4/ej_4/knnd
TAB=/home/chino/Desktop/IAA/TP4/ej_4/res.info
rm $TAB
touch $TAB

for d in 2 3 5 7 10 15 30
do
	cd training_diag_${d}/diag_training/
	rm diag_train_res$d
	rm diag_test_res$d
	rm *.nb
	rm *.predic
	touch diag_train_res$d
	touch diag_test_res$d
	for i in {1..20}
	do
		echo $d > diag_diag_training${i}.info
		echo 2 >> diag_diag_training${i}.info
		echo 250 >> diag_diag_training${i}.info
		echo 200 >> diag_diag_training${i}.info
		echo 10000 >> diag_diag_training${i}.info
		echo 0 >> diag_diag_training${i}.info
		D=`cat best | awk -F ' ' '{print $1}'`
		echo $D >> diag_diag_training${i}.info
		SAL=( `$KNND diag_diag_training${i} | sed -n '15p;17p' | awk -F ':' '{print $2}'` )
		TR=${SAL[0]:0:5}
		TE=${SAL[1]:0:5}
		echo $TR >> diag_train_res$d
		echo $TE >> diag_test_res$d
	done
	cd ../../training_par_${d}/par_training/
	rm par_train_res$d
	rm par_test_res$d
	rm *.nb
	rm *.predic
	touch par_train_res$d
	touch par_test_res$d
	for i in {1..20}
	do
		echo $d > par_par_training${i}.info
		echo 2 >> par_par_training${i}.info
		echo 250 >> par_par_training${i}.info
		echo 200 >> par_par_training${i}.info
		echo 10000 >> par_par_training${i}.info
		echo 0 >> par_par_training${i}.info
		D=`cat best | awk -F ' ' '{print $1}'`
		echo $D >> par_par_training${i}.info
		SAL=( `$KNND par_par_training${i} | sed -n '15p;17p' | awk -F ':' '{print $2}'` )
		TR=${SAL[0]:0:5}
		TE=${SAL[1]:0:5}
		echo $TR >> par_train_res$d
		echo $TE >> par_test_res$d
	done
	cd ../..

done
