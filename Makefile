DepsDay1 = file_to_vec.o find_sum_2020.o

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
day2.o: src/main/day2.cpp
	g++ -c -std=c++20 src/main/day2.cpp

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
