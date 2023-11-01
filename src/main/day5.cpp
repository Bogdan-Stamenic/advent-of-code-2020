#include "../../include/day5.h"
#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<char, int> decoder({{'F', 0}, {'B', 1}, {'L', 0}, {'R', 1}});

struct SeatPos {
  unsigned int row;
  unsigned int column;
};

int decode_row(std::string row_code) {
  /* 7-digit binary number --> start with 64 */
  unsigned int num = 64;
  unsigned int sum = 0;
  for (auto a : row_code) {
    sum += decoder[a] * num;
    // std::cout << "sum : " << sum << std::endl;
    num = num >> 1;
  }
  return sum;
}

int decode_column(std::string column_code) {
  /* 3-digit binary number --> start with 4 */
  unsigned int num = 4;
  unsigned int sum = 0;
  for (auto a : column_code) {
    sum += decoder[a] * num;
    num = num >> 1;
  }
  return sum;
}

SeatPos letter_code_to_seat_pos(std::string letter_code) {
  unsigned int row, column;
  row = decode_row(letter_code.substr(0, 7));
  column = decode_column(letter_code.substr(7, 3));
  SeatPos seat_pos = {row, column};
  return seat_pos;
}

std::vector<SeatPos> parse_seat_codesp1(std::vector<std::string> seat_codes) {
  std::vector<SeatPos> parsed;
  for (auto a : seat_codes) {
    parsed.push_back(letter_code_to_seat_pos(a));
  }
  return parsed;
}

int calc_seat_id(SeatPos seat_pos) {
  int id = seat_pos.row * 8 + seat_pos.column;
  return id;
}

int find_highest_id(std::vector<SeatPos> parsed) {
  int highest = 0;
  for (auto a : parsed) {
    if (calc_seat_id(a) > highest) {
      highest = calc_seat_id(a);
    }
  }
  return highest;
}

/* functions for part 2 */

std::vector<int> parse_seat_codesp2(std::vector<std::string> seat_codes) {
  std::vector<int> parsed;
  for (auto a : seat_codes) {
    parsed.push_back(calc_seat_id(letter_code_to_seat_pos(a)));
  }
  return parsed;
}

std::vector<int> gen_all_possible_seat_ids() {
  std::vector<int> all_ids;
  /* first and last rows excluded */
  for (int i = 1; i < 127; ++i) {
    for (int j = 0; j < 8; ++j) {
      all_ids.push_back(i * 8 + j);
    }
  }
  return all_ids;
}

int find_my_id(std::vector<int> id) {
  int my_id = 0;
  std::vector<int> all_ids = gen_all_possible_seat_ids();
  std::vector<bool> could_be_my_id(1016, true);
  for (auto not_my_seat : id) {
    // std::cout << "Before: " << could_be_my_id[not_my_seat] << std::endl;
    could_be_my_id[not_my_seat] = false;
    // std::cout << "After: " << could_be_my_id[not_my_seat] << std::endl;
  }
  int false_count = 0;
  for (auto a : all_ids) {
    // std::cout << a << " : " << could_be_my_id[a] << std::endl;
    if (could_be_my_id[a] == true && false_count > 0) {
      my_id = a;
      break;
    } else if (could_be_my_id[a] == false) {
      false_count++;
    }
  }
  return my_id;
}

SeatPos calc_seat_pos_from_id(int id) {
  SeatPos seat_pos;
  seat_pos.column = id % 8;
  seat_pos.row = (id - seat_pos.column) >> 3;
  return seat_pos;
}

SeatPos find_my_seat(std::vector<int> seat_ids) {
  int my_id = find_my_id(seat_ids);
  SeatPos my_seat = calc_seat_pos_from_id(my_id);
  return my_seat;
}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		std::string filepath = std::string(argv[1]);
		std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		std::vector<SeatPos> parsed_p1 = parse_seat_codesp1(input_line_by_line);
		int highest = find_highest_id(parsed_p1);
		std::cout << "The highest seat id is : " << highest << std::endl;

		std::vector<int> parsed_p2 = parse_seat_codesp2(input_line_by_line);
		std::cout << std::boolalpha;
		SeatPos my_seat = find_my_seat(parsed_p2);
		std::cout << "My seat is in row " << my_seat.row << " and column "
			<< my_seat.column << "." << "\n";
		std::cout << "And the corresponding seat id is: "
			<< my_seat.row * 8 + my_seat.column << std::endl;
	} else {
		std::cout << "Usage:\n./day2 <input_file_path>" << std::endl;
	}
#else
  std::vector<std::string> seat_codes = file_to_string_vec("input/day5_input.txt");
  if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
    /* day5 - part 1 */
    std::vector<SeatPos> parsed = parse_seat_codesp1(seat_codes);
    int highest = find_highest_id(parsed);
    std::cout << "The highest seat id is : " << highest << std::endl;
  } else if ((argc == 2) && (*argv[1] == '2')) {
    /* day5 - part 2 */
    std::vector<int> parsed = parse_seat_codesp2(seat_codes);
    std::cout << std::boolalpha;
    SeatPos my_seat = find_my_seat(parsed);
    std::cout << "My seat is in row " << my_seat.row << " and column "
              << my_seat.column << "." << std::endl;
    std::cout << "And the corresponding seat id is: "
              << my_seat.row * 8 + my_seat.column << std::endl;
  } else {
    std::cout << "Error: Invalid argument. Must be \"1\" or \"2\"."
              << std::endl;
    return 1;
  }
#endif

  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
