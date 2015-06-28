#!/bin/bash


for n in 2 3 5 7 10 15 30
do
	D_ARR_TE=( `cat training_diag_$n/diag_training/diag_test_res$n | sort -g` )
	D_ARR_TR=( `cat training_diag_$n/diag_training/diag_train_res$n | sort -g` )
	D_MED_TE=`echo "scale=2; ( ${D_ARR_TE[5]} + ${D_ARR_TE[6]} ) / 2.0" | bc`
	D_MED_TR=`echo "scale=2; ( ${D_ARR_TR[5]} + ${D_ARR_TR[6]} ) / 2.0" | bc`
	P_ARR_TE=( `cat training_par_$n/par_training/par_test_res$n | sort -g` )
	P_ARR_TR=( `cat training_par_$n/par_training/par_train_res$n | sort -g` )
	P_MED_TE=`echo "scale=2; ( ${P_ARR_TE[5]} + ${P_ARR_TE[6]} ) / 2.0" | bc`
	P_MED_TR=`echo "scale=2; ( ${P_ARR_TR[5]} + ${P_ARR_TR[6]} ) / 2.0" | bc`

	echo $n $D_MED_TR $D_MED_TE $P_MED_TR $P_MED_TE >> tab
done
