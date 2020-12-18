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

SeatPos letter_code_to_seat_num(std::string letter_code) {
  unsigned int row, column;
  row = decode_row(letter_code.substr(0, 7));
  column = decode_column(letter_code.substr(7, 3));
  SeatPos seat_pos = {row, column};
  return seat_pos;
}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  /* insert code here */
  std::string test = "FBFBBFFRLR";
  SeatPos seat_pos = letter_code_to_seat_num(test);
  std::cout << "Row: " << seat_pos.row << "\nColumn: " << seat_pos.column << std::endl;

  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
