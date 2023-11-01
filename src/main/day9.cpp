#include "../../include/day9.h"
#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

/* xmas property : Do any 2 of the previous preamble_length numbers sum to xmas_num? */
bool has_xmas_property(auto preamble_begin, auto preamble_end, int xmas_num) {
	for (auto it_num1 = preamble_begin; it_num1 != preamble_end; it_num1++) {
		for (auto it_num2 = preamble_begin; it_num2 != it_num1; it_num2++) {
			if (it_num1 == it_num2) continue;
			bool cond = (*it_num1 + *it_num2 == xmas_num);
			if (cond) return true;
		}
	}
	return false;
}

/* Solves day9 part 1 */
unsigned int find_num_without_xmas_property(const std::vector<int64_t>& xmas_cipher, int preamble_length=25) {
	if (xmas_cipher.size() < preamble_length) {
		std::cout << xmas_cipher.size() << " !< " << preamble_length << std::endl;
		throw std::invalid_argument("cipher was shorter than required preamble length.");
	} 
	for (auto it_xmas = xmas_cipher.begin() + preamble_length; it_xmas != xmas_cipher.end(); it_xmas++) {
		bool answer = has_xmas_property(it_xmas - preamble_length,it_xmas,*it_xmas);
		if (!answer) return *it_xmas;
	}
	return 0;
}

inline int sum_smallest_and_largest_nums(auto it_first_num, auto it_last_num) {
	int smallest = *it_first_num;
	int largest = *it_first_num;
	for (it_first_num; it_first_num != it_last_num; it_first_num++) {
		if (*it_first_num < smallest) smallest = *it_first_num;
		if (*it_first_num > largest) largest = *it_first_num;
	}
	return smallest + largest;
}

/* Solves day9 part 2 */
int find_xmas_encryption_weakness(const std::vector<int64_t>& xmas_cipher, int preamble_length=25) {
	int xmas_num = find_num_without_xmas_property(xmas_cipher, preamble_length);
	auto it_first_num = xmas_cipher.begin();
	auto it_last_num = it_first_num;
	int sum = *it_first_num;
	/* Move two iterators to find contiguous set that adds to xmas_num */
	for (it_first_num; it_first_num != xmas_cipher.end(); it_first_num++) {
		while (sum < xmas_num) {
			it_last_num++;
			sum += *it_last_num;
		}
		if (sum == xmas_num) {
			break;
		} else {
			/* Nothing adds to xmas_num -> next iteration */
			sum -= *it_first_num;
		}
	}
	if (it_first_num == it_last_num) {
		throw std::runtime_error("something went wrong");
	}
	int xmas_weakness = sum_smallest_and_largest_nums(it_first_num, it_last_num);
	return xmas_weakness;
}

int main(int argc, char *argv[]) {
#ifdef GPROF /* Build for profiling */
	for (int i = 0; i < 1000; i++){
		std::vector<std::string> input_line_by_line = file_to_long_vec("input/day9_input.txt");
		int answer = find_xmas_encryption_weakness(input_line_by_line);
	}
#else
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
  if (argc==2) {
	  std::string filepath = std::string(argv[1]);
	  std::vector<int64_t> input_line_by_line =  file_to_long_vec(filepath);
	  int answer_p1 = find_num_without_xmas_property(input_line_by_line);
	  std::cout << "First number without XMAS property is (day9-p1) : " << answer_p1 << std::endl;
	  int answer_p2 = find_xmas_encryption_weakness(input_line_by_line);
	  std::cout << "XMAS encryption weakness is (day9-p2) : " << answer_p2 << std::endl;
  } else {
	  std::cout << "Usage:\n./day9 <input_file_path>" << std::endl;
  }
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day9 - part 1 */
		std::vector<int64_t> input_line_by_line = file_to_long_vec("input/day9_input.txt");
		int answer = find_num_without_xmas_property(input_line_by_line);
		std::cout << "First number without XMAS property is : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day9 - part 2 */
		std::vector<int64_t> input_line_by_line = file_to_long_vec("input/day9_input.txt");
		int answer = find_xmas_encryption_weakness(input_line_by_line);
		std::cout << "XMAS encryption weakness is : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<int64_t> input_line_by_line = file_to_long_vec("input/day9_dev.txt");
		int answer = find_num_without_xmas_property(input_line_by_line, 5);
		std::cout << "First number without XMAS property is : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		//std::vector<int64_t> input_line_by_line = file_to_long_vec("input/day9_dev_p2.txt");
		std::cout << "Not implemented yet..." << std::endl;
	} else {
		std::cout << "Error: Invalid argument. Must be \"1\" or \"2\" for solver or \"3\" or \"4\" for developement." << std::endl;
		return 1;
	}
#endif

	/* Stop timer */
	std::chrono::high_resolution_clock::time_point t2 =
		std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span =
		std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Duration: " << time_span.count() << "s" << std::endl;
	return 0;
#endif
}
