runtimeBin=day1_O3 day2_O3 day3_O3 day4_O3\
		   day5_O3 day6_O3 day7_O3 day8_O3\
		   day9_O3 day10_O3 day11_O3
debugBin=day1 day2 day3 day4 day5 day6\
		 day7 day8 day9 day10 day11
profilerBin=day1_pg day2_pg day3_pg day4_pg\
			day5_pg day6_pg day7_pg day8_pg\
			day9_pg day10_pg day11_pg

all: $(runtimeBin)

debug: $(debugBin)

profiler: $(profilerBin)

%: %.o file_to_vec.o
	g++ -o $* file_to_vec.o $*.o

%_pg: %_pg.o file_to_vec_pg.o
	g++ -pg -o $*_pg file_to_vec_pg.o $*_pg.o

%_O3: %_O3.o file_to_vec.o
	g++ -o $*_O3 file_to_vec.o $*_O3.o

# Compile all files in debug-mode by default
%.o: src/main/%.cpp include/%.h
	g++ -g -c -std=c++20 src/main/$*.cpp

%_pg.o: src/main/%.cpp include/%.h
	g++ -g -D GPROF -c -std=c++20 src/main/$*.cpp -o $*_pg.o

%_O3.o: src/main/%.cpp include/%.h
	g++ -O3 -o $*_O3.o -c -std=c++20 src/main/$*.cpp

%.o: src/%.cpp include/%.h
	g++ -g -c -std=c++20 -fopenmp src/$*.cpp

%_pg.o: src/%.cpp include/%.h
	g++ -g -D GPROF -c -std=c++20 src/$*.cpp -o $*_pg.o

%_O3.o: src/%.cpp include/%.h
	g++ -O3 -o $*_O3.o -c -std=c++20 src/$*.cpp

include .specific_rules.mk

clean: FORCE
	rm *.o

clear: FORCE
	make clean
	rm day*

FORCE:
