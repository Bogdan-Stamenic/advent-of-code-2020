#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> file_to_int_vec(std::string file_name);
std::vector<int> find_sum_2020p1(std::vector<int> int_vec);
std::vector<int> find_sum_2020p2(std::vector<int> int_vec);

std::vector<int> read_expense_report() {
  return file_to_int_vec("expense_report.txt");
}

int main(int argc, char *argv[]) {
  std::vector<int> expenses = read_expense_report();

  if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
    std::vector<int> sum_2020 = find_sum_2020p1(expenses);
    std::cout << "Answer:" << sum_2020[0] * sum_2020[1] << std::endl;
  } else if ((argc == 2) && (*argv[1] == '2')) {
    std::vector<int> sum_2020 = find_sum_2020p2(expenses);
    std::cout << "Answer:" << sum_2020[0] * sum_2020[1] * sum_2020[2]
              << std::endl;
  } else {
    std::cout << "Error: Invalid argument. Must be \"1\" or \"2\"."
              << std::endl;
    return 1;
  }
  return 0;
}
