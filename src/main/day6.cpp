#include <iostream>
#include <chrono>
#include <string>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name,
                                            char delim = '\n');

int main(int argc, char *argv[]) {
/* Start timer */
std::chrono::high_resolution_clock::time_point t1 =
    std::chrono::high_resolution_clock::now();

if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
  /* day6 - part 1 */
  std::vector<std::string> raw_input = file_to_string_vec("day6_input.txt");
  int i = 0;
  for (auto a: raw_input) {
      std::cout << a << std::endl;
      if (a == "") {
          i++;
          std::cout << i << ": End of Group" << std::endl;
      }
  }
} else if ((argc == 2) && (*argv[1] == '2')) {
  /* day6 - part 2 */
  std::vector<std::string> raw_input = file_to_string_vec("day6_input.txt");
} else {
  std::cout << "Error: Invalid argument. Must be \"1\" or \"2\"." << std::endl;
  return 1;
}

/* Stop timer */
std::chrono::high_resolution_clock::time_point t2 =
    std::chrono::high_resolution_clock::now();
std::chrono::duration<double> time_span =
    std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
std::cout << "Duration: " << time_span.count() << "s" << std::endl;
return 0;
}
