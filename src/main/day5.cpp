#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::string> file_to_string_vec(std::string file_name,
                                            char delim = '\n');

std::unordered_map<char, int> decoder({ {'F', 0}, {'B', 1}, {'L',0}, {'R',1} });

struct SeatPos{
    unsigned int row;
    unsigned int column;
};

int decode_row(std::string row_code) {
    /* 7-digit binary number --> start with 64 */
    unsigned int num = 64;
    unsigned int sum = 0;
    for (auto a: row_code) {
        sum += decoder[a] * num;
        //std::cout << "sum : " << sum << std::endl;
        num = num >> 1;
    }
    return sum;
}

int decode_column(std::string column_code) {
    /* 3-digit binary number --> start with 4 */
    unsigned int num = 4;
    unsigned int sum = 0;
    for (auto a: column_code) {
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

std::vector<SeatPos> parse_seat_codes(std::vector<std::string> seat_codes) {
    std::vector<SeatPos> parsed;
    for (auto a: seat_codes) {
        parsed.push_back(letter_code_to_seat_pos(a));
    }
    return parsed;
}
    
int calc_seat_id(SeatPos seat_pos)
{
    int id = seat_pos.row * 8 + seat_pos.column;
    return id;
}

int find_highest_id(std::vector<SeatPos> parsed) {
    int highest = 0;
    for (auto a: parsed) {
        if (calc_seat_id(a) > highest) {
            highest = calc_seat_id(a);
        }
    }
    return highest;
}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  /* insert code here */
  std::vector<std::string> seat_codes = file_to_string_vec("day5_input.txt");
  std::vector<SeatPos> parsed = parse_seat_codes(seat_codes);
  int highest = find_highest_id(parsed);
  std::cout << "The highest seat id is : " << highest << std::endl;

  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
