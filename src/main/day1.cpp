#include "../../include/day1.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include <vector>

int find_sum_2020p1(std::span<int> int_span) {
  for (auto &i : int_span) {
    for (auto &j : int_span) {
      if (i + j == 2020) {
        return i * j;
      }
    }
  }
  throw std::runtime_error{"Could not find entries."};
}

int find_sum_2020p2(std::span<int> int_span) {
  for (auto &i : int_span) {
    for (auto &j : int_span) {
      for (auto &k : int_span) {
        if (i + j + k == 2020) {
          return i * j * k;
        }
      }
    }
  }
  throw std::runtime_error{"Could not find entries."};
}

std::vector<int> read_expense_report()
{
	return file_to_int_vec("input/day1_input.txt");
}

int main(int argc, char *argv[]){
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::vector<int> expenses = read_expense_report();
	int sum_2020;

	if ( ((argc==2) && (*argv[1]=='1'))||(argc==1)  ) {
		sum_2020 = find_sum_2020p1(expenses);
	}else if(  (argc==2) && (*argv[1]=='2') ){
		sum_2020 = find_sum_2020p2(expenses);
	}else{
		std::cout << "Error: Invalid argument. Must be \"1\" or \"2\"." << std::endl;
		return 1;
	}
	std::cout << "Answer: " << sum_2020 << std::endl;
	
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Duration: " << time_span.count() << "s" << std::endl;

	return 0;
}
