#!/bin/sh

szas="0 10 20 30 40 50 60 70 80"
lambdas="320 350 400 500"

datadir=$1
n_photons=$2

for sza in $szas
do
	for lambda in $lambdas
	do
		echo "lambda=$lambda, sza=$sza"
		atmfile="$datadir/bsca_babs_lambda$lambda.dat"
		fn="./$lambda-$sza.log"
		./coton t3 $atmfile $sza $n_photons > $fn &
	done
done
