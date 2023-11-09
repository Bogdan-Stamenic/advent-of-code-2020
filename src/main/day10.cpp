#include "../../include/day10.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class AdapterArray {
	public:
		AdapterArray(std::vector<int>& adapter_list){
			int num_of_adapters = *std::max_element(adapter_list.begin(),adapter_list.end()) + 4;
			m_adapter_list = std::vector<bool>(num_of_adapters,false);
			m_adapter_list.at(0) = true; /*jolts rating of chair is 0*/
			m_adapter_list.back() = true; /*jolts rating of laptop is max_adapter_jolts + 3*/
			for (int num_of_jolts: adapter_list) {
				m_adapter_list.at(num_of_jolts) = true;
			}
			check_chain_all_adapters_possible();
		}
		~AdapterArray() = default;
		
		void solve_day10p1() {
			count_adapter_jolt_distances();
			int answer = m_jolts_distance_count[0] * m_jolts_distance_count[2];
#ifndef GPROF
			std::cout <<  answer << std::endl;
#endif
		}
		/* Number of ways to complete chain from idx */
		int64_t memoize_count_adapter_chains(int idx=0) {
			if (idx >= m_adapter_list.size()) throw std::out_of_range("idx was too large!");
			if (idx == m_adapter_list.size() - 1) {
				return 1;
			} else if (m_num_ways_to_complete_chain_from_idx.count(idx) == 1) {
				return m_num_ways_to_complete_chain_from_idx.at(idx);
			}
			int64_t answer = 0;
			int jdx = idx + 1;
			int jdx_last = (idx + 3 > m_adapter_list.size())
				? m_adapter_list.size()
				: idx + 3;
			for (jdx; jdx <= jdx_last; jdx++) {
				if (m_adapter_list.at(jdx)) {
					answer += memoize_count_adapter_chains(jdx);
				}
			}
			m_num_ways_to_complete_chain_from_idx[idx] = answer;
			return answer;
		}
	private:
		std::vector<bool> m_adapter_list{};
		std::vector<int> m_jolts_distance_count = std::vector<int>(3,0);
		std::unordered_map<int,int64_t> m_num_ways_to_complete_chain_from_idx;
		inline void check_chain_all_adapters_possible() {
			for (auto it_adapter = m_adapter_list.begin(); it_adapter != m_adapter_list.end() - 3; it_adapter++) {
				bool next_adapter_exists = std::any_of(it_adapter, it_adapter+3, [](bool adapter_exists){return adapter_exists;});
				if (!next_adapter_exists) {
					throw std::invalid_argument("can't chain all adapters together.");
				}
			}
		}
		void count_adapter_jolt_distances() {
			int last_idx = 0;
			for (int idx = 1; idx < m_adapter_list.size(); idx++) {
				if (idx - last_idx > 3) throw std::runtime_error("something unexpected happened");
				if (idx - last_idx == 0) throw std::runtime_error("something unexpected happened");
				if (m_adapter_list.at(idx)) {
					int jolts_dist = idx - last_idx;
					m_jolts_distance_count.at(jolts_dist-1) += 1;
					last_idx = idx;
				}
			}
		}
};

int main(int argc, char *argv[]) {
#ifdef GPROF /* Build for profiling */
	for (int i = 0; i < 1000; i++){
		std::vector<std::string> input_line_by_line = file_to_int_vec("input/day10_input.txt");
	}
#else
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();
#ifdef READ_AOC_INPUT_FROM_CMD 
  if (argc==2) {
	  std::string filepath = std::string(argv[1]);
	  std::vector<int> input_line_by_line =  file_to_int_vec(filepath);
	  AdapterArray my_bag(input_line_by_line);
	  my_bag.solve_day10p1();
	  int64_t answer_p2 = my_bag.memoize_count_adapter_chains();
	  std::cout << answer_p2 << std::endl;
  } else {
	  std::cout << "Usage:\n./day10 <input_file_path>" << std::endl;
  }
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day10 - part 1 */
		std::vector<int> input_line_by_line = file_to_int_vec("input/day10_input.txt");
		AdapterArray my_bag(input_line_by_line);
		my_bag.solve_day10p1();
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day10 - part 2 */
		std::vector<int> input_line_by_line = file_to_int_vec("input/day10_input.txt");
		AdapterArray my_bag(input_line_by_line);
		int64_t answer = my_bag.memoize_count_adapter_chains();
		std::cout << "Total possible adapter chains (day10_input.txt) : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<int> input_line_by_line = file_to_int_vec("input/day10_dev.txt");
		AdapterArray my_bag(input_line_by_line);
		my_bag.solve_day10p1();
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<int> input_dev1 = file_to_int_vec("input/day10_dev.txt");
		std::vector<int> input_dev2 = file_to_int_vec("input/day10_dev2.txt");
		AdapterArray my_bag1(input_dev1);
		AdapterArray my_bag2(input_dev2);
		int answer_dev1 = my_bag1.memoize_count_adapter_chains(0);
		int answer_dev2 = my_bag2.memoize_count_adapter_chains(0);
		assert(answer_dev1 == 8);
		assert(answer_dev2 == 19208);
		std::cout << "Total possible adapter chains (day10_dev.txt) : " << answer_dev1 << std::endl;
		std::cout << "Total possible adapter chains (day10_dev2.txt) : " << answer_dev2 << std::endl;
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
