runtimeBin=day1_O3 day2_O3 day3_O3 day4_O3 day5_O3 day6_O3 day7_O3
debugBin=day1 day2 day3 day4 day5 day6 day7
profilerBin=day1_pg day2_pg day3_pg day4_pg day5_pg day6_pg day7_pg

all: $(runtimeBin)

debug: $(debugBin)

profiler: $(profilerBin)

%: %.o file_to_vec.o
	g++ -o $* file_to_vec.o $*.o

%_pg: %_pg.o file_to_vec_pg.o
	g++ -pg -o $*_pg file_to_vec_pg.o $*_pg.o

%_O3: %_O3.o file_to_vec.o
	g++ -o $*_O3 file_to_vec.o $*_O3.o

day7_O3: day7_O3.o file_to_vec.o rules_parser_O3.o
	g++ -o day7_O3 file_to_vec.o rules_parser_O3.o day7_O3.o

day6_O3: day6_O3.o file_to_vec.o customs_declaration_O3.o
	g++ -o day6_O3 file_to_vec.o customs_declaration_O3.o day6_O3.o

day4_O3: day4_O3.o file_to_vec.o passport_processor_O3.o
	g++ -o day4_O3 file_to_vec.o passport_processor_O3.o day4_O3.o

day1_O3: day1_O3.o file_to_vec.o find_sum_2020.o
	g++ -o day1_O3 file_to_vec.o find_sum_2020.o day1_O3.o

day7_pg: day7_pg.o file_to_vec_pg.o rules_parser_pg.o
	g++ -pg -o day7_pg file_to_vec_pg.o rules_parser_pg.o day7_pg.o

day7: day7.o file_to_vec.o rules_parser.o
	g++ -o day7 file_to_vec.o rules_parser.o day7.o

day6: day6.o file_to_vec.o customs_declaration.o
	g++ -o day6 file_to_vec.o customs_declaration.o day6.o

day4: day4.o file_to_vec.o passport_processor.o
	g++ -o day4 file_to_vec.o passport_processor.o day4.o

day1: day1.o file_to_vec.o find_sum_2020.o
	g++ -o day1 file_to_vec.o find_sum_2020.o day1.o

# Compile all files in debug-mode by default
day7_O3.o: src/main/day7.cpp include/day7.h
	g++ -O3 -o day7_O3.o -c -std=c++20 -fopenmp src/main/day7.cpp

day7.o: src/main/day7.cpp include/day7.h
	g++ -O3 -o day7.o -c -std=c++20 -fopenmp src/main/day7.cpp

%.o: src/main/%.cpp include/%.h
	g++ -g -c -std=c++20 src/main/$*.cpp

%_pg.o: src/main/%.cpp include/%.h
	g++ -g -D GPROF -c -std=c++20 src/main/$*.cpp -o $*_pg.o

%_O3.o: src/main/%.cpp include/%.h
	g++ -O3 -o $*_O3.o -c -std=c++20 src/main/$*.cpp

%.o: src/%.cpp include/%.h
	g++ -g -c -std=c++20 src/$*.cpp

%_pg.o: src/%.cpp include/%.h
	g++ -g -D GPROF -c -std=c++20 src/$*.cpp -o $*_pg.o

%_O3.o: src/%.cpp include/%.h
	g++ -O3 -o $*_O3.o -c -std=c++20 src/$*.cpp

find_sum_2020.o: src/find_sum_2020.cpp
	g++ -g -c -std=c++20 src/find_sum_2020.cpp

clean: FORCE
	rm *.o

clear: FORCE
	make clean
	rm day*

FORCE:
