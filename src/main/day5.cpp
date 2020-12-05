#include <chrono>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name,
                                            char delim = '\n');

std::string replace_str(std::string old,
                        std::string repl){auto it = std::regex_replac(old, )}

std::vector<int> letter_code_to_seat_num(std::string letter_code) {
  int row, column;
  row = decode_row(letter_code.substr(0, 7));
  column = decode_column(letter_code.substr(7, 3));
  std::vector<int> seat_pos = {row, column};
  return seat_pos;
}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  /* insert code here */
  std::string test = "FBFBBFFRLR";

  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
