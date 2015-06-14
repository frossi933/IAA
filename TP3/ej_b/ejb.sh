#!/bin/bash
# borramos archivos anteriores y aplico el clasificador bayesiano

NB=/home/chino/Desktop/IAA/TP3/ej_a/nb_n
TAB=/home/chino/Desktop/IAA/TP3/ej_b/res_nb
touch $TAB

for d in 2 3 5 7 10 15 30
do
	cd training_diag_${d}/diag_training/
	rm diag_diag_training?.prediction
	rm diag_diag_training??.prediction
	rm diag_diag_training?.tree
	rm diag_diag_training??.tree
	rm diag_diag_training?.unpruned
	rm diag_diag_training??.unpruned
	rm diag_diag_training?.names
	rm diag_diag_training??.names
	touch diag_train_res$d
	touch diag_test_res$d
	for i in {1..20}
	do
		rm diag_diag_training${i}.nb
		echo $d > diag_diag_training${i}.nb
		echo 2 >> diag_diag_training${i}.nb
		echo 250 >> diag_diag_training${i}.nb
		echo 250 >> diag_diag_training${i}.nb
		echo 10000 >> diag_diag_training${i}.nb
		echo 0 >> diag_diag_training${i}.nb
		echo 0 >> diag_diag_training${i}.nb
		SAL=( `$NB diag_diag_training${i} | sed -n '14p;16p' | awk -F ':' '{print $2}'` )
		TR=${SAL[0]:0:5}
		TE=${SAL[1]:0:5}
		echo $TR >> diag_train_res$d
		echo $TE >> diag_test_res$d
	done
	cd ../../training_par_${d}/par_training/
	rm par_par_training?.prediction
	rm par_par_training??.prediction
	rm par_par_training?.names
	rm par_par_training??.names
	rm par_par_training?.unpruned
	rm par_par_training??.unpruned
	rm par_par_training?.tree
	rm par_par_training??.tree
	touch par_train_res$d
	touch par_test_res$d
	for i in {1..20}
	do
		echo $d > par_par_training${i}.nb
		echo 2 >> par_par_training${i}.nb
		echo 250 >> par_par_training${i}.nb
		echo 250 >> par_par_training${i}.nb
		echo 10000 >> par_par_training${i}.nb
		echo 0 >> par_par_training${i}.nb
		echo 0 >> par_par_training${i}.nb
		SAL=( `$NB par_par_training${i} | sed -n '14p;16p' | awk -F ':' '{print $2}'` )
		TR=${SAL[0]:0:5}
		TE=${SAL[1]:0:5}
		echo $TR >> par_train_res$d
		echo $TE >> par_test_res$d
	done
	cd ../..

done
