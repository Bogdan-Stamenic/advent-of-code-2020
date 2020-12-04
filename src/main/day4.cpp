#include <chrono>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name,
                                            char delim = '\n');

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point tic =
      std::chrono::high_resolution_clock::now();

  /* insert code here */
  std::vector<std::string> passport_credentials_messy =
      file_to_string_vec("day4_input.txt");
  for (auto a : passport_credentials_messy) {
    std::cout << a << std::endl;
  }

  std::chrono::high_resolution_clock::time_point toc =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
