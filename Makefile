DepsDay1 = file_to_vec.o find_sum_2020.o

day1: day1.o $(DepsDay1)
	g++ -o day1 $(DepsDay1) day1.o
	make clean

day1.o: day1.cpp
	g++ -c day1.cpp

## Object files compiled from src/
file_to_vec.o: src/file_to_vec.cpp
	g++ -c src/file_to_vec.cpp

find_sum_2020.o: src/find_sum_2020.cpp
	g++ -c src/find_sum_2020.cpp

clean: FORCE
	rm *.o

FORCE:
