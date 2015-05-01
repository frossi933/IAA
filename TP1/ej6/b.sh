#/bin/bash

cd $1/par_test
rm par_par_test1.names
for i in {1..20}
do
	cp par_par_test1.data ../par_training/par_par_training$i.test
done
rm par_par_test1.data

