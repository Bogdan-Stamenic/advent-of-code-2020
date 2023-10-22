#!/bin/bash
ANALYSISFILE=analysis.txt

if [ $# -eq 1 ]; then
	make $1_pg
	if [ -f ./$1_pg ]; then
		./$1_pg
		gprof $1_pg gmon.out > "$ANALYSISFILE"
	else
		echo "Something went wrong."
	fi
else
	echo "Needs at least one argument."
fi

