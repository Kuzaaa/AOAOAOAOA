#!/bin/bash

rm -r resultsRAM

mkdir resultsRAM

cc=gcc
echo "CC : $cc"

mkdir resultsRAM/$cc

for opt in O2 O3 "O3 -funroll-loops" "O3 -march=native" "O3 -fprofile-use"
do
	echo "Opt : $opt"

	mkdir "resultsRAM/$cc/$opt"

	for var in baseline tab_1d independant independant_split block_cache independant_parallel independant_split_parallel block_cache_parallel
	do
		echo "Variante : $var"
		make $var FLAG="$opt"
		./exec 1000 300 600 >> "resultsRAM/$cc/$opt/resultat_$var.txt"

		echo
	done

	echo
done

cc=icc
echo "CC : $cc"

mkdir resultsRAM/$cc

for opt in O2 O3 "O3 -xHost"
do
	echo "Opt : $opt"

	mkdir "resultsRAM/$cc/$opt"

	for var in baseline tab_1d independant independant_split block_cache independant_parallel independant_split_parallel block_cache_parallel
	do
		echo "Variante : $var"
		make $var CC=$cc FLAG="$opt"
		./exec 1000 300 600 >> "resultsRAM/$cc/$opt/resultat_$var.txt"

		echo
	done

	echo
done

make clean
