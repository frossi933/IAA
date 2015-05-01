#/bin/bash
# ./genDatasetsC sten

sten=$1

gena=/home/chino/Desktop/IAA/genA_datasets.sh	# DIAGONAL
genb=/home/chino/Desktop/IAA/genB_datasets.sh	# PARALELO

for c in 0.5 1.0 1.5 2.0 2.5
do
	mkdir "${sten}_diag_${c}"
	cd ${sten}_diag_${c}
	eval "$gena 5 $c 250 20 diag_${sten}"
	eval "$gena 5 $c 10000 1 diag_test"
	cd ..

	mkdir "${sten}_par_${c}"
	cd ${sten}_par_${c}
	eval "$genb 5 $c 250 20 par_${sten}"
	eval "$genb 5 $c 10000 1 par_test"
	cd ..
done
