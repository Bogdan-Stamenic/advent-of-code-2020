DepsDay1 = file_to_vec.o find_sum_2020.o

day4: day4.o file_to_vec.o
	g++ -o day4 -fopenmp file_to_vec.o day4.o
	mkdir -p bin
	mv day4 bin/day4
	make clean

day3: day3.o file_to_vec.o
	g++ -o day3 file_to_vec.o day3.o
	mkdir -p bin
	mv day3 bin/day3
	make clean

day2: day2.o file_to_vec.o
	g++ -o day2 file_to_vec.o day2.o
	mkdir -p bin
	mv day2 bin/day2
	make clean

day1: day1.o $(DepsDay1)
	g++ -o day1 $(DepsDay1) day1.o
	mkdir -p bin
	mv day1 bin/day1
	make clean

## Object files compiled from src/main/
day4.o: src/main/day4.cpp
	g++ -c -fopenmp src/main/day4.cpp

day3.o: src/main/day3.cpp
	g++ -c src/main/day3.cpp

day2.o: src/main/day2.cpp
	g++ -c src/main/day2.cpp

day1.o: src/main/day1.cpp
	g++ -c -std=c++20 src/main/day1.cpp

## Object files compiled from src/
file_to_vec.o: src/file_to_vec.cpp
	g++ -c src/file_to_vec.cpp

find_sum_2020.o: src/find_sum_2020.cpp
	g++ -c -std=c++20 src/find_sum_2020.cpp

clean: FORCE
	rm *.o

FORCE:
