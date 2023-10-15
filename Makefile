runtimeBin=day1 day2 day3 day4 day5
debugBin=day1_debug day2_debug day3_debug day4_debug day5_debug

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

%_debug: %.o file_to_vec.o
	g++ -o $*_debug file_to_vec.o $*.o

day4_debug: day4.o file_to_vec.o passport_processor.o
	g++ -o day4_debug file_to_vec.o passport_processor.o day4.o

day1_debug: day1.o file_to_vec.o find_sum_2020.o
	g++ -o day1_debug file_to_vec.o find_sum_2020.o day1.o

day1: day1.o file_to_vec.o find_sum_2020.o
# NEW: Object files compiled from src/main/ %.o: src/main/%.cpp include/%.h
	g++ -c -std=c++20 src/main/$*.cpp

# OLD: Object files compiled from src/main/
%.o: src/main/%.cpp
	g++ -c -std=c++20 src/main/$*.cpp

## Object files compiled from src/
#passport_processor.o: src/passport_processor.cpp include/passport_processor.h
#	g++ -c -std=c++20 src/passport_processor.cpp
%.o: src/%.cpp include/%.h
	g++ -c -std=c++20 src/$*.cpp

file_to_vec.o: src/file_to_vec.cpp
	g++ -c -std=c++20 src/file_to_vec.cpp

find_sum_2020.o: src/find_sum_2020.cpp
	g++ -c -std=c++20 src/find_sum_2020.cpp

clean: FORCE
	rm *.o

clear: FORCE
	make clean
	rm day*

FORCE:
