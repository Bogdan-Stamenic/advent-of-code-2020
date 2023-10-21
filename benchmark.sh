#!/bin/bash
if [ "$#" -eq 1 ]; then
	hyperfine --warmup 10 --min-runs 15 "./${1}" >> hyperfine_benchmark_results.log
elif  [ "$#" -eq 2 ]; then
	hyperfine --warmup 10 --min-runs 15 "./${1} ${2}" >> hyperfine_benchmark_results.log
else
	echo "Something went wrong."
fi
