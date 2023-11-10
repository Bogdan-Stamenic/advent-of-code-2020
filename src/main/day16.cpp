#include "../../include/day16.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <exception>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct TicketRule {
	std::string field_name;
	std::pair<int, int> lr;
	std::pair<int, int> ur;
	constexpr bool in_valid_range(int n) {
		bool in_range =
			((n >= lr.first) && (n <= lr.second))
			|| ((n >= ur.first) && (n <= ur.second));
		if (in_range) {
			return true;
		}
		return false;
	}
};

class TicketTranslator {
	public:
		TicketTranslator(std::vector<std::string> input){
			init_rules(input);
		}
		int scanning_error_rate() {
			int err = 0;
			auto it_num = vv_iterator<int>::begin(m_nearby_tickets);
			for (it_num; it_num != vv_iterator<int>::end(m_nearby_tickets); it_num++) {
				if (violates_all_rules(*it_num)) {
					err += *it_num;
				}
			}
			return err;
		}
	private:
		std::vector<TicketRule> m_rules;
		std::vector<int> m_my_ticket;
		std::vector<std::vector<int>> m_nearby_tickets;

		// TODO
		void remove_invalid_tickets(){
			for (const auto& ticket : m_nearby_tickets) {
				for (const auto& num : ticket) {
					if (violates_all_rules(num)) {
						break;
					}
				}
			}
		}

		bool violates_all_rules(int num) {
			for (auto& rule : m_rules) {
				if (rule.in_valid_range(num)) {
					return false;
				}
			}
			return true;
		}

		void init_rules(std::vector<std::string> input){
			/* Split into 3 chunks */
			int which_chunk = 0;
			int rules_end = 0;
			int my_ticket_end = 0;
			int line_nr = 0;
			for (const auto& line : input) {
				bool cond = (line.find(':') == std::string::npos)
					&& (line.find(',') == std::string::npos);
				if (cond) {
					switch(which_chunk) {
						case 0:
							rules_end = line_nr;
							break;
						case 1:
							my_ticket_end = line_nr;
							break;
						default: throw std::runtime_error("Uh-oh");
					};
					which_chunk++;
				}
				if (which_chunk > 1) {break;}
				line_nr++;
			}
			//std::vector<std::string> input_rules;
			auto input_rules = std::ranges::subrange(input.begin(),input.begin() + rules_end - 1);
			auto input_my_ticket = std::ranges::subrange(input.begin() + rules_end + 1, input.begin() + my_ticket_end - 1);
			auto input_nearby_tickets = std::ranges::subrange(input.begin() + my_ticket_end + 1, input.end());
			/* 1: Ticket rules */
			for (const auto& line : input_rules) {
				/* Figure out where formatting symbols are */
				int colon = line.find(':');
				int first_hyphen = line.find('-', colon);
				int second_hyphen = line.find('-', first_hyphen + 1);
				int end_first_range = line.find(' ', first_hyphen + 1);
				/* Parse */
				std::string field_name = line.substr(0,colon);
				std::pair<int, int> lr = std::pair<int, int>(
						std::stoi(line.substr(colon + 2, first_hyphen - colon - 2)),
						std::stoi(line.substr(first_hyphen + 1, end_first_range - first_hyphen - 1))
						);
				std::pair<int, int> ur = std::pair<int, int>(
						std::stoi(line.substr(end_first_range + 4, second_hyphen - end_first_range - 4)),
						std::stoi(line.substr(second_hyphen + 1, line.length() - second_hyphen - 1))
						);
				m_rules.emplace_back(field_name,lr,ur);
			}
			std::cout << "Ticket rules : Pass" << std::endl;
			/* 2: My ticket */
			int idx_fst = 0;
			int idx_lst = 0;
			std::string& ticket_info = input_my_ticket[1];
			while (ticket_info.find(',', idx_fst) != std::string::npos) {
				idx_lst = ticket_info.find(',', idx_fst);
				int num = std::stoi(ticket_info.substr(idx_fst,idx_lst - idx_fst));
				m_my_ticket.push_back(num);
				idx_fst = idx_lst + 1;
			}
			int num = std::stoi(ticket_info.substr(idx_fst,ticket_info.size() - idx_fst + 1));
			m_my_ticket.push_back(num);
			std::cout << "My ticket : Pass" << std::endl;
			/* 3: Nearby tickets */
			auto it_line = input_nearby_tickets.begin() + 1; //skip 0; is "nearby tickets:" entry
			std::vector<int> parsed_line = {};
			for (it_line; it_line != input_nearby_tickets.end(); it_line++) {
				idx_fst = 0;
				idx_lst = 0;
				parsed_line = {};
				while (it_line->find(',', idx_fst) != std::string::npos) {
					idx_lst = it_line->find(',', idx_fst);
					int num = std::stoi(it_line->substr(idx_fst,idx_lst - idx_fst));
					parsed_line.push_back(num);
					idx_fst = idx_lst + 1;
				}
				int num = std::stoi(it_line->substr(idx_fst,ticket_info.find('\n') - idx_fst + 1));
				parsed_line.push_back(num);
				m_nearby_tickets.push_back(parsed_line);
			}
			std::cout << "Nearby tickets : Pass" << std::endl;
		}
};

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
		std::cout << "Usage:\n./day16 <input_file_path>" << std::endl;
	}
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day16 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day16_input.txt");
		TicketTranslator bob(input_line_by_line);
		int answer = bob.scanning_error_rate();
		std::cout << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day16 - part 2 */
		//std::vector<std::string> input_line_by_line = file_to_string_vec("input/day16_input.txt");
		std::cout << "Not yet implemented..." << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day16_dev1.txt");
		TicketTranslator bob(input_line_by_line);
		int answer = bob.scanning_error_rate();
		std::cout << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day16_dev2.txt");
		TicketTranslator bob(input_line_by_line);
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
