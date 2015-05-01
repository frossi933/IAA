#/bin/bash

cd $1/diag_test
rm diag_diag_test1.names
for i in {1..20}
do
	cp diag_diag_test1.data ../diag_training/diag_diag_training$i.test
done
rm diag_diag_test1.data

