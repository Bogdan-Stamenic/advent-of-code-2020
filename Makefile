runtimeBin=day1 day2 day3 day4 day5

all: $(runtimeBin)

debug: $(debugBin)

%: %.o file_to_vec.o
	g++ -o $* file_to_vec.o $*.o

day6: day6.o file_to_vec.o customs_declaration.o
	g++ -o day6 file_to_vec.o customs_declaration.o day6.o

day4: day4.o file_to_vec.o passport_processor.o
	g++ -o day4 file_to_vec.o passport_processor.o day4.o

day1: day1.o file_to_vec.o find_sum_2020.o
	g++ -o day1 file_to_vec.o find_sum_2020.o day1.o

# Compile all files in debug-mode by default
%.o: src/main/%.cpp include/%.h
	g++ -g -c -std=c++20 src/main/$*.cpp

%.o: src/%.cpp include/%.h
	g++ -g -c -std=c++20 src/$*.cpp

file_to_vec.o: src/file_to_vec.cpp
	g++ -g -c -std=c++20 src/file_to_vec.cpp

find_sum_2020.o: src/find_sum_2020.cpp
	g++ -g -c -std=c++20 src/find_sum_2020.cpp

clean: FORCE
	rm *.o

clear: FORCE
	make clean
	rm day*

FORCE:
