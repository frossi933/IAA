#/bin/bash
# ./genDatasetsC sten

sten=$1

gena=/home/chino/Desktop/IAA/genA_datasets.sh	# DIAGONAL
genb=/home/chino/Desktop/IAA/genB_datasets.sh	# PARALELO

for n in 100 200 300 500 1000 5000
do
	mkdir "${sten}_diag_${n}"
	cd ${sten}_diag_${n}
	eval "$gena 2 0.75 $n 20 diag_${sten}"
	eval "$gena 2 0.75 10000 1 diag_test"
	cd ..

	mkdir "${sten}_par_${n}"
	cd ${sten}_par_${n}
	eval "$genb 2 0.75 $n 20 par_${sten}"
	eval "$genb 2 0.75 10000 1 par_test"
	cd ..
done
