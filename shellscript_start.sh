#!/bin/bash

# To run on terminal: ./shellscript_start.sh

fileName1="result_report-cpu.txt"
fileName2="result_report-serie-runtime.txt"
fileName3="result_report-parallel-runtime.txt"
fileName4="result_report-speedup.txt"
fileName5="result_report-array.txt"
fileName6="result_report-ordered_array.txt"

fileHeader1="\n/* \n * CPU Report                                 \n */\n"
fileHeader2="\n/* \n * Serie Runtime Report In Seconds            \n */  "
fileHeader3="\n/* \n * Parallel Runtime Report In Seconds         \n */  "
fileHeader4="\n/* \n * Speedup Report In %                        \n */  "
fileHeader5="\n/* \n * Array Report                               \n */\n"
fileHeader6="\n/* \n * Parallel Calculation Report: Ordered Array \n */  "

echo -e "$fileHeader1" >> $fileName1
echo -e "$fileHeader2" >> $fileName2
echo -e "$fileHeader3" >> $fileName3
echo -e "$fileHeader4" >> $fileName4
echo -e "$fileHeader5" >> $fileName5
echo -e "$fileHeader6" >> $fileName6

insertCPUInfo(){
	cat /proc/cpuinfo | grep "$2" | uniq >> $1	
}
insertCPUInfo $fileName1 'model name'
insertCPUInfo $fileName1 'vendor'
insertCPUInfo $fileName1 'cpu cores'
insertCPUInfo $fileName1 'siblings'
insertCPUInfo $fileName1 'cache size'

#serie compiler
g++ -O0 -g -W -ansi -pedantic -std=c++11 -o odd-even-transposition-sort-serial odd-even-transposition-sort-serial.cpp
#parallel compiler
mpic++ -g -Wall odd-even-transposition-sort-parallel.cpp -o odd-even-transposition-sort-parallel -lm
#analysis compiler
g++ -O0 -g -W -ansi -pedantic -std=c++11 -o calculates-serie-parallel-analysis calculates-serie-parallel-analysis.cpp

#get a size set random array (range 0 to 100)
problemSize=200
count=1
while [ "$count" -le $problemSize ]; do
 number[$count]=$(($RANDOM % 100))
 let "count += 1"
done
echo -e " ${number[*]}" >> $fileName5

#attempts by number of cores and size
attempts=5
for cores in 2 4 8
do
	echo -e "\n $cores $problemSize\t\c                        " >> $fileName2
	echo -e "\n $cores $problemSize\t\c                        " >> $fileName3
	echo -e "\n $cores $problemSize\t\c                        " >> $fileName4
	echo -e "\n $cores Cores CPU - Size Problem $sizeProblem \n" >> $fileName6
	for attempt in $(seq $attempts)
	do
		echo -e "  Try $attempt" >> $fileName6
		#serie execute
		./odd-even-transposition-sort-serial ${number[*]}
		#parallel execute
		mpirun -np $cores --oversubscribe ./odd-even-transposition-sort-parallel ${number[*]}
		#analysis execute
        ./calculates-serie-parallel-analysis
	done
done

showOnTerminal(){
	while IFS= read -r line
	do
	    echo "$line"
	done <"$1"
}
showOnTerminal $fileName1
showOnTerminal $fileName2
showOnTerminal $fileName3
showOnTerminal $fileName4
showOnTerminal $fileName5
echo -e

txt2pdf(){
    vim $1 -c "hardcopy > $1.ps | q";ps2pdf $1.ps; rm $1.ps
}
txt2pdf $fileName1
txt2pdf $fileName2
txt2pdf $fileName3
txt2pdf $fileName4
txt2pdf $fileName5
txt2pdf $fileName6

pdfunite $fileName1.pdf $fileName2.pdf $fileName3.pdf $fileName4.pdf $fileName5.pdf $fileName6.pdf report.pdf

rm $fileName1.pdf $fileName2.pdf $fileName3.pdf $fileName4.pdf $fileName5.pdf $fileName6.pdf
rm $fileName1 $fileName2 $fileName3 $fileName4 $fileName5 $fileName6
rm odd-even-transposition-sort-serial
rm odd-even-transposition-sort-parallel
rm calculates-serie-parallel-analysis
