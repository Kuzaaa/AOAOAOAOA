#!/bin/bash

rm -r resultsRAM

mkdir resultsRAM

cc=gcc
echo "CC : " $cc

mkdir resultsRAM/$cc

for opt in O1 O2 O3 Ofast
do
	echo "Opt : " $opt

	mkdir resultsRAM/$cc/$opt

	for var in baseline tab_1d independant independant_split block_cache block_cache_mod independant_parallel \
	 	independant_split_parallel block_cache_parallel
	do
		echo "Variante : " $var
		make $var CC=$cc FLAG=$opt
		./exec 1000 300 600 >> resultsRAM/$cc/$opt/"resultat_"$var".txt"

		echo
	done

	echo
done

for opt in march=native funroll-loops fsplit-loops fgcse-las fallow-store-data-races funswitch-loops floop-nest-optimize
do
	echo "Opt : " $opt

	mkdir resultsRAM/$cc/$opt

	for var in baseline tab_1d independant independant_split block_cache block_cache_mod independant_parallel \
	 	independant_split_parallel block_cache_parallel
	do
		echo "Variante : " $var
		make $var CC=$cc OFLAGS=-O3 FLAG=$opt
		./exec 1000 300 600 >> resultsRAM/$cc/$opt/"resultat_"$var".txt"

		echo
	done

	echo
done

opt=fprofile-use
echo "Opt : " $opt

mkdir resultsRAM/$cc/$opt

for var in baseline tab_1d independant independant_split block_cache block_cache_mod independant_parallel \
 	independant_split_parallel block_cache_parallel
do
	echo "Variante : " $var
	make $var CC=$cc OFLAGS=-O3 FLAG=fprofile-generate
	./exec 1000 300 600 > /dev/null
	make $var CC=$cc OFLAGS=-O3 FLAG=$opt
	./exec 1000 300 600 >> resultsRAM/$cc/$opt/"resultat_"$var".txt"

	echo
done

echo


cc=icc
echo "CC : " $cc

mkdir resultsRAM/$cc

for opt in O1 O2 O3 Ofast
do
	echo "Opt : " $opt

	mkdir resultsRAM/$cc/$opt

	for var in baseline tab_1d independant independant_split block_cache block_cache_mod independant_parallel \
	 	independant_split_parallel block_cache_parallel
	do
		echo "Variante : " $var
		make $var CC=$cc FLAG=$opt
		./exec 1000 300 600 >> resultsRAM/$cc/$opt/"resultat_"$var".txt"

		echo
	done

	echo
done

for opt in xHost finline parallel funroll-loops
do
	echo "Opt : " $opt

	mkdir resultsRAM/$cc/$opt

	for var in baseline tab_1d independant independant_split block_cache block_cache_mod independant_parallel \
	 	independant_split_parallel block_cache_parallel
	do
		echo "Variante : " $var
		make $var CC=$cc OFLAGS=-O3 FLAG=$opt
		./exec 1000 300 600 >> resultsRAM/$cc/$opt/"resultat_"$var".txt"

		echo
	done

	echo
done

opt=prof-use
echo "Opt : " $opt

mkdir resultsRAM/$cc/$opt

for var in baseline tab_1d independant independant_split block_cache block_cache_mod independant_parallel \
 	independant_split_parallel block_cache_parallel
do
	echo "Variante : " $var
	make $var CC=$cc OFLAGS=-O3 FLAG=prof-gen=threadsafe
	./exec 1000 300 600 > /dev/null
	make $var CC=$cc OFLAGS=-O3 FLAG=$opt
	./exec 1000 300 600 >> resultsRAM/$cc/$opt/"resultat_"$var".txt"

	echo
done

echo

make clean
