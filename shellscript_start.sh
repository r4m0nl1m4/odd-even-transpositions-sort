#!/bin/bash

# To run on terminal: ./shellscript_start.sh

fileName0="README.txt"
fileName1="result_report-cpu.txt"
fileName2="result_report-problem_size.txt"
fileName3="result_report-serie-runtime.txt"
fileName4="result_report-parallel-cores.txt"
fileName5="result_report-parallel-runtime.txt"
fileName6="result_report-speedup.txt"
fileName7="result_report-efficiency.txt"
fileName8="result_report-array.txt"
fileName9="result_report-ordered_array.txt"

fileHeader1="\n/* \n * CPU Report                                 \n */\n"
fileHeader2="\n/* \n * Problem Size Report                        \n */  "
fileHeader3="\n/* \n * Serie Runtime Report In Seconds            \n */  "
fileHeader4="\n/* \n * Parallel Cores Report                      \n */  "
fileHeader5="\n/* \n * Parallel Runtime Report In Seconds         \n */  "
fileHeader6="\n/* \n * Speedup Report                             \n */  "
fileHeader7="\n/* \n * Efficiency Report                          \n */  "
fileHeader8="\n/* \n * Array Report                               \n */\n"
fileHeader9="\n/* \n * Parallel Calculation Report: Ordered Array \n */  "

echo -e "$fileHeader1" >> $fileName1
echo -e "$fileHeader2" >> $fileName2
echo -e "$fileHeader3" >> $fileName3
echo -e "$fileHeader4" >> $fileName4
echo -e "$fileHeader5" >> $fileName5
echo -e "$fileHeader6" >> $fileName6
echo -e "$fileHeader7" >> $fileName7
echo -e "$fileHeader8" >> $fileName8
echo -e "$fileHeader9" >> $fileName9

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
echo -e " ${number[*]}" >> $fileName8

#attempts by number of cores and size
attempts=5
for cores in 2 4 8
do
	echo -e "" >> $fileName2
	echo -e "" >> $fileName3
	echo -e "" >> $fileName4
	echo -e "" >> $fileName5
	echo -e "" >> $fileName6
	echo -e "" >> $fileName7
	echo -e "\n $cores Cores CPU - Size Problem $problemSize \n" >> $fileName9
	for attempt in $(seq $attempts)
	do
        echo -e ":$problemSize\c" >> $fileName2
        echo -e ":$cores\c      " >> $fileName4
		echo -e "  Try $attempt " >> $fileName9
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
showOnTerminal $fileName6
showOnTerminal $fileName7
showOnTerminal $fileName8
echo -e

txt2pdf(){
    vim $1 -c "hardcopy > $1.ps | q";ps2pdf $1.ps; rm $1.ps
}
txt2pdf $fileName0
txt2pdf $fileName1
txt2pdf $fileName2
txt2pdf $fileName3
txt2pdf $fileName4
txt2pdf $fileName5
txt2pdf $fileName6
txt2pdf $fileName7
txt2pdf $fileName8
txt2pdf $fileName9

pdfunite $fileName0.pdf $fileName1.pdf $fileName2.pdf $fileName3.pdf $fileName4.pdf $fileName5.pdf $fileName6.pdf $fileName7.pdf $fileName8.pdf $fileName9.pdf report.pdf

rm $fileName0.pdf $fileName1.pdf $fileName2.pdf $fileName3.pdf $fileName4.pdf $fileName5.pdf $fileName6.pdf $fileName7.pdf $fileName8.pdf $fileName9.pdf
rm $fileName1 $fileName2 $fileName3 $fileName4 $fileName5 $fileName6 $fileName7 $fileName8 $fileName9
rm odd-even-transposition-sort-serial
rm odd-even-transposition-sort-parallel
rm calculates-serie-parallel-analysis
