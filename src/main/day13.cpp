#include "../../include/day13.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <exception>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

struct BusTimestampsP1 {
	const int earliest_timestamp;
	const std::vector<int> bus_IDs;
};

struct BusTimestampP2 {
	const int bus_ID;
	const int offset_time;
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

/* Find Bézout coeficients using Extended Euclidean Algorithm 
 * If it doesn't make sense... well, it's fancy math
 * See: https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm 
 */
std::pair<int64_t,int64_t> find_bezout_coeficients(int64_t a, int64_t b) {
	int64_t old_r, r, old_s, s, old_t, t;
	old_r = a; r = b;
	old_s = 1; s = 0;//Bézout coefs for a
	old_t = 0; t = 1;//Bézout coefs for b
	while (r != 0) {
		int64_t quotient = old_r / r;//Euclidean division
		int64_t tmp = old_r;
		old_r = r; r = tmp - quotient * r;
		tmp = old_s;
		old_s = s; s = tmp - quotient * s;
		tmp = old_t;
		old_t = t; t = tmp - quotient * t;
	}
	std::pair<int64_t,int64_t> answer(old_s,old_t);
	return answer;
}

void test_find_bezout_coeficients() {
	/* Both examples from Wikipedia */
	std::pair<int64_t,int64_t> test = find_bezout_coeficients(3,4);
	assert(test.first == -1);
	assert(test.second == 1);
	test = find_bezout_coeficients(12,42);
	assert(test.first == -3);
	assert(test.second == 1);
}

/* Greastest common denominator from Bézout's Identity */
/* For coprime numbers, it's always equal to 1 */
int64_t gcd(int64_t a, int64_t b) {
	std::pair<int64_t,int64_t> bezout = find_bezout_coeficients(a,b);
	return a*bezout.first + b*bezout.second;
}

/* From Wikipedia; uses Extended Euler Algorithm
 * Complexity : O(log_2(n))
 * https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Computing_multiplicative_inverses_in_modular_structures */
int64_t mod_inverse(int64_t a, int64_t n){
	int64_t t = 0; int64_t new_t = 1;
	int64_t r = n; int64_t new_r = a;
	while (new_r != 0) {
		int64_t quotient = r / new_r;
		int64_t tmp = t;
		t = new_t;
		new_t = tmp - quotient * new_t;
		tmp = r;
		r = new_r;
		new_r = tmp - quotient * new_r;
	}
	if (r > 1) {
		/* should never happen if n is prime -> because prime field theory */
		throw std::invalid_argument("a is not invertible");
	}
	if (t < 0) {
		t = t + n;
	}
	return t;
}

/* Implements direct solution construction
 * For an explanation of the problem, see : https://en.wikipedia.org/wiki/Chinese_remainder_theorem */
int64_t solve_with_chinese_remainder_theorem(std::vector<int64_t> n_divisors, std::vector<int64_t> r_remainders) {
	if (n_divisors.size() != r_remainders.size()) {
		throw std::invalid_argument("expected equal number of divisors and remainders");
	}
	int64_t N = 1; //Product of all divisors
	N = std::accumulate(n_divisors.begin(),n_divisors.end(),N,std::multiplies<int64_t>());
	int64_t answer = 0;
	for (int64_t idx = 0; idx < n_divisors.size(); idx++) {
		int64_t N_current = N / n_divisors[idx];
		int64_t b = n_divisors[idx];
		int64_t i = r_remainders[idx];
		assert(gcd(N_current,b) == 1);//coprime
		int64_t mi = mod_inverse(N_current,b);
		assert((mi*N_current)%b == 1);//mod inverse condition
		assert((i*mi*N_current)%b == i);//i<b -> this follows from above condition
		int64_t for_r = i*mi*N_current;
		assert(for_r%b == i);
		assert(for_r%N_current == 0);
		answer += for_r;
	}
	answer = answer % N;
	std::cout << "answer = " << answer << std::endl;
	for (int idx = 0; idx < n_divisors.size(); idx++) {
		assert(answer % n_divisors[idx] == r_remainders[idx]);
	}
	return answer;
}

void test_solve_with_chinese_remainder_theorem() {
	/* Example from Wikipedia */
	std::vector<int64_t> n_divisors = {3,4,5};
	std::vector<int64_t> r_remainders = {0,3,4};
	assert(solve_with_chinese_remainder_theorem(n_divisors,r_remainders) == 39);
	/* Examples from AOC day13 part 2 */
	n_divisors = {17,13,19};
	r_remainders = {/*(17-0)%17 =*/0,13-2,19-3};
	assert(solve_with_chinese_remainder_theorem(n_divisors,r_remainders) == 3417);
	n_divisors = {67,7,59,61};
	r_remainders = {/*(67-0)%67 =*/0,7-1,59-2,61-3};
	assert(solve_with_chinese_remainder_theorem(n_divisors,r_remainders) == 754018);
	n_divisors = {67,7,59,61};
	r_remainders = {/*(67-0)%67 =*/0,7-2,59-3,61-4};
	assert(solve_with_chinese_remainder_theorem(n_divisors,r_remainders) == 779210);
	n_divisors = {7,13,59,31,19};
	r_remainders = {/*(7-0)%7 =*/0,13-1,59-4,31-6,19-7};
	assert(solve_with_chinese_remainder_theorem(n_divisors,r_remainders) == 1068781);
	n_divisors = {67,7,59,61};
	r_remainders = {/*(67-0)%67 =*/0,7-1,59-3,61-4};
	assert(solve_with_chinese_remainder_theorem(n_divisors,r_remainders) == 1261476);
	n_divisors = {1789,37,47,1889};
	r_remainders = {/*(1789-0)%1789 =*/0,37-1,47-2,1889-3};
	assert(solve_with_chinese_remainder_theorem(n_divisors,r_remainders) == 1202161486);
	std::cout << "CRT passed." << std::endl;
}

int main(int argc, char *argv[]) {
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		std::string filepath = std::string(argv[1]);
		std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		std::cout << "Not yet implemented..." << std::endl;
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
		//std::vector<std::string> input_line_by_line = file_to_string_vec("input/day13_input.txt");
		std::cout << "Not yet implemented..." << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day13_dev.txt");
		BusTimestampsP1 stamps = parse_input_to_bustimestamps_p1(input_line_by_line);
		BusAndWaitTime answer = find_bus_and_wait_time(stamps);
		std::cout << answer.bus_ID * answer.wait_time << std::endl;
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day13_dev.txt");
		test_find_bezout_coeficients();
		test_solve_with_chinese_remainder_theorem();
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
