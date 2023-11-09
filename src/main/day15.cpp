#include "../../include/day15.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#define MAX_ARR (1 << 25)
#define MAX_HYB (1 << 12)

int64_t elf_memory_game(std::string input, uint64_t N) {
	/* Read starting numbers */
	std::vector<int64_t> starting_numbers;
	int idx_fst = 0;
	int idx_lst = 0;
	while (input.find(',',idx_fst) != std::string::npos) {
		idx_lst = input.find(',',idx_fst);
		int64_t num = std::stol(input.substr(idx_fst,idx_lst - idx_fst));
		starting_numbers.push_back(num);
		idx_fst = idx_lst + 1;
	}
	int64_t num = std::stol(input.substr(idx_fst,input.size() - idx_fst));
	starting_numbers.push_back(num);
	/* Init */
	std::vector<int64_t> memory =
		std::vector<int64_t>(MAX_ARR, -1);
	std::vector<int64_t> memory_prev =
		std::vector<int64_t>(MAX_ARR, -1);
	int64_t turn_counter = 0;
	for (auto num : starting_numbers) {
		memory[num] = turn_counter;
		turn_counter++;
	}
	/* Solve */
	int64_t last_num = starting_numbers.back();
	int64_t nnum = 0;
	while (turn_counter < N) {
		if (memory_prev.at(last_num) == -1) {
			nnum = 0;
		} else {
			nnum = memory.at(last_num) - memory_prev.at(last_num);
		}
		memory_prev[nnum] = memory.at(nnum);
		memory[nnum] = turn_counter;
		last_num = nnum;
		turn_counter++;
	}
	return nnum;
}

int64_t elf_memory_game_hashmap(std::string input, uint64_t N) {
	/* Read starting numbers */
	std::vector<int64_t> starting_numbers;
	int idx_fst = 0;
	int idx_lst = 0;
	while (input.find(',',idx_fst) != std::string::npos) {
		idx_lst = input.find(',',idx_fst);
		int64_t num = std::stol(input.substr(idx_fst,idx_lst - idx_fst));
		starting_numbers.push_back(num);
		idx_fst = idx_lst + 1;
	}
	int64_t num = std::stol(input.substr(idx_fst,input.size() - idx_fst));
	starting_numbers.push_back(num);
	/* Init */
	std::unordered_map<int64_t, int64_t> memory;
	std::unordered_map<int64_t, int64_t> memory_prev;
	int64_t turn_counter = 0;
	for (auto num : starting_numbers) {
		memory[num] = turn_counter;
		memory_prev[num] = -1;
		turn_counter++;
	}
	/* Solve */
	int64_t last_num = starting_numbers.back();
	int64_t nnum = 0;
	while (turn_counter < N) {
		if (memory_prev.at(last_num) == -1) {
			nnum = 0;
		} else {
			nnum = memory.at(last_num) - memory_prev.at(last_num);
		}
		if (memory.count(nnum)) {
			memory_prev[nnum] = memory.at(nnum);
		} else {
			memory_prev[nnum] = -1;
		}
		memory[nnum] = turn_counter;
		last_num = nnum;
		turn_counter++;
	}
	return nnum;
}

class NumHolder {
	public:
		int64_t& operator[](std::size_t idx){
			if (idx < MAX_HYB) {
				return  m_common_small_numbers[idx];
			}
			return m_rare_big_numbers[idx];
		}
		int64_t& at(std::size_t idx){
			if (idx < MAX_HYB) {
				return  m_common_small_numbers.at(idx);
			}
			return m_rare_big_numbers.at(idx);
		}
	private:
		std::vector<int64_t> m_common_small_numbers =
			std::vector<int64_t>(MAX_HYB,-1);
		std::unordered_map<int64_t, int64_t> m_rare_big_numbers{};
};

int64_t elf_memory_game_hybrid(std::string input, uint64_t N) {
	/* Read starting numbers */
	std::vector<int64_t> starting_numbers;
	int idx_fst = 0;
	int idx_lst = 0;
	while (input.find(',',idx_fst) != std::string::npos) {
		idx_lst = input.find(',',idx_fst);
		int64_t num = std::stol(input.substr(idx_fst,idx_lst - idx_fst));
		starting_numbers.push_back(num);
		idx_fst = idx_lst + 1;
	}
	int64_t num = std::stol(input.substr(idx_fst,input.size() - idx_fst));
	starting_numbers.push_back(num);
	/* Init */
	NumHolder memory;
	NumHolder memory_prev;
	int64_t turn_counter = 0;
	for (auto num : starting_numbers) {
		memory[num] = turn_counter;
		std::cout << turn_counter << " : " << memory.at(num) << '\n';
		turn_counter++;
	}
	/* Solve */
	int64_t last_num = starting_numbers.back();
	int64_t nnum = 0;
	while (turn_counter < N) {
		std::cout << turn_counter << " : " << memory.at(nnum) << '\n';
		if (memory_prev.at(last_num) == -1) {
			nnum = 0;
		} else {
			nnum = memory.at(last_num) - memory_prev.at(last_num);
		}
		memory_prev[nnum] = memory.at(nnum);
		memory[nnum] = turn_counter;
		last_num = nnum;
		turn_counter++;
	}
	return nnum;
}



int main(int argc, char *argv[]) {
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		std::string filepath = std::string(argv[1]);
		std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		int64_t answer_p1 = elf_memory_game(input_line_by_line[0],2020);
		int64_t answer_p2 = elf_memory_game(input_line_by_line[0],30000000);
		std::cout << answer_p1 << std::endl;
		std::cout << answer_p2 << std::endl;
	} else {
		std::cout << "Usage:\n./day15 <input_file_path>" << std::endl;
	}
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day15 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day15_input.txt");
		int64_t answer_p1 = elf_memory_game(input_line_by_line[0], 2020);
		std::cout << answer_p1 << std::endl;
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day15 - part 2 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day15_input.txt");
		int64_t answer = elf_memory_game(input_line_by_line[0], 30000000);
		std::cout << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day15_dev.txt");
		int64_t answer = elf_memory_game(input_line_by_line[0], 2020);
		std::cout << answer << std::endl;
		answer = elf_memory_game_hybrid(input_line_by_line[0], 10);
		std::cout << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day15_dev.txt");
		int64_t answer = elf_memory_game(input_line_by_line[0], 30000000);
		std::cout << answer << std::endl;
		answer = elf_memory_game_hybrid(input_line_by_line[0], 30000000);
		std::cout << answer << std::endl;
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
}
