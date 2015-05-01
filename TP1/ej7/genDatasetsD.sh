#/bin/bash
# ./genDatasetsC sten

sten=$1

gena=/home/chino/Desktop/IAA/genA_datasets.sh	# DIAGONAL
genb=/home/chino/Desktop/IAA/genB_datasets.sh	# PARALELO

for d in 2 3 5 7 10 15 30
do
	mkdir "${sten}_diag_${d}"
	cd ${sten}_diag_${d}
	eval "$gena $d 0.75 250 20 diag_${sten}"
	eval "$gena $d 0.75 10000 1 diag_test"
	cd ..

	mkdir "${sten}_par_${d}"
	cd ${sten}_par_${d}
	eval "$genb $d 0.75 250 20 par_${sten}"
	eval "$genb $d 0.75 10000 1 par_test"
	cd ..
done
