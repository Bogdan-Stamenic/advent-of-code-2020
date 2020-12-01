#include <cstdlib>
#include <fstream>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> file_to_int_vec(std::string file_name);
int find_sum_2020p1(std::span<int> int_vec);
int find_sum_2020p2(std::span<int> int_vec);

std::vector<int> read_expense_report() {
  return file_to_int_vec("expense_report.txt");
}

int main(int argc, char *argv[]) {
  std::vector<int> expenses = read_expense_report();

  if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
    auto sum_2020 = find_sum_2020p1(expenses);
    std::cout << sum_2020 << std::endl;
  } else if ((argc == 2) && (*argv[1] == '2')) {
    auto sum_2020 = find_sum_2020p2(expenses);
    std::cout << sum_2020 << std::endl;
  } else {
    throw std::runtime_error{"Invalid argument!"};
  }
  return 0;
}