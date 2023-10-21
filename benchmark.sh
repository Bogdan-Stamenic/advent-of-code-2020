#!/bin/bash
LOGFILE=hyperfine_benchmark_results.log
make $1
make $1_O3

echo "**************************************************" >> $LOGFILE
if [ -f ./$1 ]; then
	if [ "$#" -eq 1 ]; then
		hyperfine --warmup 10 --min-runs 15 --shell=none "./${1} 1" >> "$LOGFILE"
		hyperfine --warmup 10 --min-runs 15 --shell=none "./${1} 2" >> "$LOGFILE"
		hyperfine --warmup 10 --min-runs 15 --shell=none "./${1}_O3 1" >> "$LOGFILE"
		hyperfine --warmup 10 --min-runs 15 --shell=none "./${1}_O3 2" >> "$LOGFILE"
		echo "Done."
	elif  [ "$#" -eq 2 ]; then
		hyperfine --warmup 10 --min-runs 15 --shell=none "./${1}_O3 ${2}" >> "$LOGFILE"
		echo "Done."
	else
		echo "Something went wrong."
	fi
else
	echo "File $1 not found!"
fi
