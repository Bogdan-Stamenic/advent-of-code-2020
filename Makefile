srcFiles=day1 day2 day3 day4 day5

all: $(srcFiles)
	make clean

%: %.o file_to_vec.o
	g++ -o $* file_to_vec.o $*.o
	mkdir -p bin
	mv $* bin/$*

day4: day4.o file_to_vec.o passport_processor.o
	g++ -o day4 file_to_vec.o passport_processor.o day4.o
	mkdir -p bin
	mv day4 bin/day4

day1: day1.o file_to_vec.o find_sum_2020.o
	g++ -o day1 file_to_vec.o find_sum_2020.o day1.o
	mkdir -p bin
	mv day1 bin/day1

# NEW: Object files compiled from src/main/
%.o: src/main/%.cpp include/%.h
	g++ -c -std=c++20 src/main/$*.cpp

# OLD: Object files compiled from src/main/
%.o: src/main/%.cpp
	g++ -c -std=c++20 src/main/$*.cpp

## Object files compiled from src/
passport_processor.o: src/passport_processor.cpp include/passport_processor.h
	g++ -c -std=c++20 src/passport_processor.cpp

file_to_vec.o: src/file_to_vec.cpp
	g++ -c -std=c++20 src/file_to_vec.cpp

find_sum_2020.o: src/find_sum_2020.cpp
	g++ -c -std=c++20 src/find_sum_2020.cpp

clean: FORCE
	rm *.o

clear: FORCE
	rm ./bin/*
	make clean

FORCE:
