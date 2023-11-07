#include "../../include/day14.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/* Solves part 1 */
uint64_t value_interpret (const std::vector<std::string>& input) {
	// AAA
	// 10X
	// 10A
	// (A & amask) | smask
	uint64_t amask = 0ULL;
	uint64_t smask = 0ULL;
	std::vector<uint64_t> memory(1<<16,0ULL);
	for (const auto& line: input) {
		if (line.substr(0,4) == "mask") {
			// update mask
			amask = 0;
			smask = 0;
			for (auto c : line.substr(7)) {
				amask <<= 1;
				smask <<= 1;
				if (c == 'X') {
					amask |= 1;
				} else {
					smask |= (c == '1') ? 1 : 0;
				}
			}
		} else {
			int idx_first = line.find('[') + 1;
			int adr_len = line.find(']') - idx_first;
			int address = std::stoi(line.substr(idx_first,adr_len));
			idx_first = line.find('=') + 2;
			int val_len = line.size() - idx_first;
			uint64_t value = std::stol(line.substr(idx_first,val_len));
			memory[address] = (value & amask) | smask;
		}
	}
	uint64_t accumulator = 0ULL;
	for (auto num: memory) {
		accumulator += num;
		//if (num) {printf("%#lx\n",num);}
	}
	return accumulator;
}


/* TODO : add optimization for contiguous set of Xs */
void generate_xmasks(std::vector<std::pair<uint64_t,uint64_t>>& xmasks, uint64_t xmask_template) {
	if (xmask_template == 0) {return;}
	uint64_t chk = 0;
	std::vector<uint64_t> base_cases;
	/* Count number of Xs */
	for (int i = 0; i<36; i++) {
		chk = (xmask_template >> i) & 1;
		if (chk) {
			base_cases.push_back(1 << i);
		}
	}
	uint64_t N = base_cases.size();
	if (N > 12) {
		throw std::runtime_error("infeasible number of base cases");
	}
	uint64_t bit = 1ULL;
	/* All 1s in xmask_template represent floating bits 'X' => sets 1 in one mask 0 in other. */
	uint64_t xset0 = 0ULL;
	uint64_t xset1 = 0ULL;
	int case_num = 0;
	/* Use cbn=0..2^N-1 to represent all 2^N subsets of base_cases.
	 * Each additional X doubles number of bit masks needed.*/
	for (uint64_t cbn = 0; cbn < (1 << N); cbn++) {
		xset0 = 0ULL;
		xset1 = 0ULL;
		case_num = 0;
		for (uint64_t i=0; i < 36; i++) {
			bit = (cbn >> i) & 1ULL;
			if (bit) {
				xset0 += base_cases[case_num];
				case_num++;
			} else if (xmask_template >> i & 1ULL) {
				xset1 += base_cases[case_num];
				case_num++;
			}
			if (case_num >= N) {
				break;
			}
		}
		xmasks.push_back(std::pair<uint64_t,uint64_t>(xset0,xset1));
	}
}

// smask1 :          011110001101111000110110111001000001
// xmask_template1 : 000001000010000011001000000000100000
uint64_t memory_interpret(const std::vector<std::string>& input) {
	uint64_t smask = 0ULL;
	uint64_t xmask_template = 0ULL;
	std::unordered_map<uint64_t,uint64_t> memory;
	std::vector<std::pair<uint64_t,uint64_t>> xmasks;
	for (const auto& line: input) {
		if (line.substr(0,4) == "mask") {
			// update mask
			smask = 0;
			xmask_template = 0;
			xmasks.clear();
			for (auto c : line.substr(7)) {
				smask <<= 1;
				xmask_template <<= 1;
				switch (c) {
					case '0': break;
					case '1': smask |= 1; break;
					case 'X': xmask_template |= 1; break;
					default: throw std::invalid_argument("expected 0, 1, or X");
				};
			}
			generate_xmasks(xmasks, xmask_template);//fills xmasks
		} else {
			int idx_first = 4;//where '[' is
			int adr_len = line.find(']') - idx_first;
			uint64_t address = std::stol(line.substr(idx_first,adr_len));
			idx_first = line.find('=') + 2;
			int val_len = line.size() - idx_first;
			uint64_t value = std::stol(line.substr(idx_first,val_len));
			uint64_t new_address = 0ULL;
			for (const auto& [xset0,xset1]: xmasks) {
				/* set 1s -> set some Xs to 0 -> set the other Xs to 1 */
				new_address = ((address | smask) & ~xset0) | xset1;
				memory[new_address] = value;
			}
		}
	}
	uint64_t accumulator = 0ULL;
	for (auto [adr,val]: memory) {
		accumulator += val;
		//printf("%#lx\n",val);
	}
	return accumulator;
}

int main(int argc, char *argv[]) {
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		//std::string filepath = std::string(argv[1]);
		//std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		std::cout << "Not yet implemented..." << std::endl;
	} else {
		std::cout << "Usage:\n./day14 <input_file_path>" << std::endl;
	}
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day14 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day14_input.txt");
		uint64_t answer = value_interpret(input_line_by_line);
		std::cout << answer << std::endl;
		//13496669152158
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day14 - part 2 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day14_input.txt");
		uint64_t answer = memory_interpret(input_line_by_line);
		std::cout << answer << std::endl;
		// tyler569 : 3278997609887
		// me : 430348104736
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day14_dev1.txt");
		value_interpret(input_line_by_line);
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day14_dev2.txt");
		uint64_t answer = memory_interpret(input_line_by_line);
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
