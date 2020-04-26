#!/bin/bash

rm -r resultsL1

mkdir resultsL1

cc=gcc
echo "CC : " $cc

mkdir resultsL1/$cc

for opt in O2 O3
do
	echo "Opt : " $opt

	mkdir resultsL1/$cc/$opt

	for var in baseline tab_1d independant independant_split block_cache independant_parallel \
	 	independant_split_parallel block_cache_parallel
	do
		echo "Variante : " $var
		make $var CC=$cc FLAG=$opt
		./exec 48 380000 380000 >> resultsL1/$cc/$opt/"resultat_"$var".txt"

		echo
	done

	echo
done

for opt in march=native funroll-loops
do
	echo "Opt : " $opt

	mkdir resultsL1/$cc/$opt

	for var in baseline tab_1d independant independant_split block_cache
	do
		echo "Variante : " $var
		make $var CC=$cc OFLAGS=-O3 FLAG=$opt
		./exec 48 380000 380000 >> resultsL1/$cc/$opt/"resultat_"$var".txt"

		echo
	done

	echo
done

opt=fprofile-use
echo "Opt : " $opt

mkdir resultsL1/$cc/$opt

for var in baseline tab_1d independant independant_split block_cache
do
	echo "Variante : " $var
	make $var CC=$cc OFLAGS=-O3 FLAG=fprofile-generate
	./exec 48 38000 38000 > /dev/null
	make $var CC=$cc OFLAGS=-O3 FLAG=$opt
	./exec 48 38000 38000 >> resultsL1/$cc/$opt/"resultat_"$var".txt"

	echo
done

echo


cc=icc
echo "CC : " $cc

mkdir resultsL1/$cc

for opt in O2 O3
do
	echo "Opt : " $opt

	mkdir resultsL1/$cc/$opt

	for var in baseline tab_1d independant independant_split block_cache independant_parallel \
	 	independant_split_parallel block_cache_parallel
	do
		echo "Variante : " $var
		make $var CC=$cc FLAG=$opt
		./exec 48 380000 380000 >> resultsL1/$cc/$opt/"resultat_"$var".txt"

		echo
	done

	echo
done

for opt in xHost
do
	echo "Opt : " $opt

	mkdir resultsL1/$cc/$opt

	for var in baseline tab_1d independant independant_split block_cache
	do
		echo "Variante : " $var
		make $var CC=$cc OFLAGS=-O3 FLAG=$opt
		./exec 48 380000 380000 >> resultsL1/$cc/$opt/"resultat_"$var".txt"

		echo
	done

	echo
done

opt=prof-use
echo "Opt : " $opt

mkdir resultsL1/$cc/$opt

for var in baseline tab_1d independant independant_split block_cache
do
	echo "Variante : " $var
	make $var CC=$cc OFLAGS=-O3 FLAG=prof-gen=threadsafe
	./exec 48 38000 38000 > /dev/null
	make $var CC=$cc OFLAGS=-O3 FLAG=$opt
	./exec 48 38000 38000 >> resultsL1/$cc/$opt/"resultat_"$var".txt"

	echo
done

echo

make clean
