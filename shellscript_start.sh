#!/bin/bash

# To run on terminal: ./shellscript_start.sh
rm result_report-array.txt
rm result_report-cpu.txt
rm result_report-ordered_array.txt
rm result_report-serie-runtime.txt
rm result_report-parallel-runtime.txt
rm odd-even-transposition-sort-serial
rm odd-even-transposition-sort-parallel

#serie compiler
g++ -O0 -g -W -ansi -pedantic -std=c++11 -o odd-even-transposition-sort-serial odd-even-transposition-sort-serial.c
#parallel compiler
mpic++ -g -Wall odd-even-transposition-sort-parallel.cpp -o odd-even-transposition-sort-parallel -lm

echo -e "\n/* \n * Array Report \n */\n" >> "result_report-array.txt"
echo -e "\n/* \n * CPU Report \n */\n" >> "result_report-cpu.txt"
echo -e "\n/* \n * Ordered Array Report \n */" >> "result_report-ordered_array.txt"
echo -e "\n/* \n * Runtime Report In Seconds\n */" >> "result_report-serie-runtime.txt"
echo -e "\n/* \n * Runtime Report In Seconds\n */" >> "result_report-parallel-runtime.txt"

cat /proc/cpuinfo | grep 'model name' | uniq >> "result_report-cpu.txt"
cat /proc/cpuinfo | grep 'vendor' | uniq >> "result_report-cpu.txt"
cat /proc/cpuinfo | grep 'cpu cores' | uniq >> "result_report-cpu.txt"
cat /proc/cpuinfo | grep 'siblings' | uniq >> "result_report-cpu.txt"
cat /proc/cpuinfo | grep 'cache size' | uniq >> "result_report-cpu.txt"

#get a size set random array (range 0 to 100)
problemSize=200
count=1
while [ "$count" -le $problemSize ]; do
 number[$count]=$(($RANDOM % 100))
 let "count += 1"
done
echo -e " ${number[*]}" >> "result_report-array.txt"

#attempts by number of cores and size
attempts=5
for cores in 2 4 8
do
	echo -e "\n $cores $problemSize\t\c" >> "result_report-serie-runtime.txt"
	echo -e "\n $cores $problemSize\t\c" >> "result_report-parallel-runtime.txt"
	echo -e "\n $cores Cores CPU - Size Problem $sizeProblem \n" >> "result_report-ordered_array.txt"
	for attempt in $(seq $attempts)
	do
		echo -e "  Try $attempt" >> "result_report-ordered_array.txt"
		#serie execute
		./odd-even-transposition-sort-serial ${number[*]}
		#parallel execute
		mpirun -np $cores --oversubscribe ./odd-even-transposition-sort-parallel ${number[*]}
	done
done

#txt2pdf
vim result_report-cpu.txt -c "hardcopy > cpu.ps | q"; ps2pdf cpu.ps; rm cpu.ps
vim result_report-array.txt -c "hardcopy > array.ps | q"; ps2pdf array.ps; rm array.ps
vim result_report-serie-runtime.txt -c "hardcopy > serie-runtime.ps | q"; ps2pdf serie-runtime.ps; rm serie-runtime.ps
vim result_report-parallel-runtime.txt -c "hardcopy > parallel-runtime.ps | q"; ps2pdf parallel-runtime.ps; rm parallel-runtime.ps
vim result_report-ordered_array.txt -c "hardcopy > ordered_array.ps | q"; ps2pdf ordered_array.ps; rm ordered_array.ps
pdfunite cpu.pdf array.pdf serie-runtime.pdf parallel-runtime.pdf ordered_array.pdf report.pdf; rm cpu.pdf; rm array.pdf; rm serie-runtime.pdf; rm parallel-runtime.pdf; rm ordered_array.pdf