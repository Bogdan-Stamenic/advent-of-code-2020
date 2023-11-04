#include "../../include/day13.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct BusTimestampsP1 {
	const int earliest_timestamp;
	const std::vector<int> bus_IDs;
};

struct BusTimestampsP2 {
	const std::vector<int64_t> bus_IDs;
	const std::vector<int64_t> bus_offsets;
};

struct BusAndWaitTime {
	const int bus_ID;
	const int wait_time;
};

BusTimestampsP1 parse_input_to_bustimestamps_p1(const std::vector<std::string>& input) {
	int earliest_timestamp = std::stoi(input[0]);
	std::vector<int> bus_IDs;
	int idx_start = 0;
	int idx_end = 0;
	while (input[1].find(",",idx_end) != std::string::npos) {
		idx_end += 1;
		idx_end = input[1].find(",",idx_end);
		const std::string& timestamp = input[1].substr(idx_start, idx_end - idx_start);
		if (timestamp != "x") {
			bus_IDs.push_back(std::stoi(timestamp));
		}
		idx_start = idx_end + 1;
	}
	BusTimestampsP1 output = {
		.earliest_timestamp = earliest_timestamp,
		.bus_IDs = bus_IDs,
	};
	return output;
}

BusTimestampsP2 parse_input_to_bustimestamps_p2 (const std::vector<std::string>& input) {
	std::vector<int64_t> bus_IDs;
	std::vector<int64_t> bus_offsets;
	int64_t offset = 0;
	int idx_start = 0;
	int idx_end = 0;
	while (input[1].find(",",idx_end) != std::string::npos) {
		idx_end += 1;
		idx_end = input[1].find(",",idx_end);
		const std::string& timestamp = input[1].substr(idx_start, idx_end - idx_start);
		if (timestamp != "x") {
			int64_t m = std::stoi(timestamp);
			bus_IDs.push_back(m);
			bus_offsets.push_back((m - offset) % m);
		}
		offset += 1;
		idx_start = idx_end + 1;
	}
	BusTimestampsP2 output = {
		.bus_IDs = bus_IDs,
		.bus_offsets = bus_offsets,
	};
	return output;
}

BusAndWaitTime find_bus_and_wait_time(const BusTimestampsP1& bus_timestamps) {
	int best_bus_ID = 2147483647; // largest int32_t; (1 << 31) - 1 does the same, but produces warning
	/* Should always be greater than bus_timestamps.earliest_timestamp */
	auto earliest_bus_time = [bus_timestamps](int bus_ID){
		int bus_time = ((bus_timestamps.earliest_timestamp / bus_ID) + 1) * bus_ID;
		return bus_time;
	};
	for (auto bus_ID: bus_timestamps.bus_IDs) {
		int bus_time = earliest_bus_time(bus_ID);
		if (bus_time < earliest_bus_time(best_bus_ID)) {
			best_bus_ID = bus_ID;
		}
	}
	BusAndWaitTime output = {
		.bus_ID = best_bus_ID,
		.wait_time = earliest_bus_time(best_bus_ID) - bus_timestamps.earliest_timestamp,
	};
	return output;
}



int main(int argc, char *argv[]) {
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		std::string filepath = std::string(argv[1]);
		std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		BusTimestampsP1 stamps_p1 = parse_input_to_bustimestamps_p1(input_line_by_line);
		BusAndWaitTime answer_p1 = find_bus_and_wait_time(stamps_p1);
		std::cout << answer_p1.bus_ID * answer_p1.wait_time << std::endl;
		BusTimestampsP2 stamps_p2 = parse_input_to_bustimestamps_p2(input_line_by_line);
		int64_t answer_p2 = solve_with_chinese_remainder_theorem(stamps_p2.bus_IDs,stamps_p2.bus_offsets);
		std::cout << answer_p2 << std::endl;
	} else {
		std::cout << "Usage:\n./day13 <input_file_path>" << std::endl;
	}
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day13 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day13_input.txt");
		BusTimestampsP1 stamps = parse_input_to_bustimestamps_p1(input_line_by_line);
		BusAndWaitTime answer = find_bus_and_wait_time(stamps);
		std::cout << answer.bus_ID * answer.wait_time << std::endl;
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day13 - part 2 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day13_input.txt");
		BusTimestampsP2 stamps = parse_input_to_bustimestamps_p2(input_line_by_line);
		int64_t answer = solve_with_chinese_remainder_theorem(stamps.bus_IDs,stamps.bus_offsets);
		std::cout << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day13_dev.txt");
		BusTimestampsP1 stamps = parse_input_to_bustimestamps_p1(input_line_by_line);
		BusAndWaitTime answer = find_bus_and_wait_time(stamps);
		std::cout << answer.bus_ID * answer.wait_time << std::endl;
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		test_find_bezout_coeficients();
		test_solve_with_chinese_remainder_theorem();
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day13_dev.txt");
		BusTimestampsP2 stamps = parse_input_to_bustimestamps_p2(input_line_by_line);
		int64_t answer = solve_with_chinese_remainder_theorem(stamps.bus_IDs,stamps.bus_offsets);
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
