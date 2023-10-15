#include "../../include/day6.h"

int main(int argc, char *argv[]) {
/* Start timer */
std::chrono::high_resolution_clock::time_point t1 =
    std::chrono::high_resolution_clock::now();

if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
  /* day6 - part 1 */
  std::vector<std::string> raw_input = file_to_string_vec("input/day6_input.txt");
  CustomsDeclaration cust(raw_input);
  unsigned int yes_count_for_part1 = cust.count_at_least_one_person_said_yes();
  std::cout << "Yes count in input : " << yes_count_for_part1 << std::endl;
} else if ((argc == 2) && (*argv[1] == '2')) {
  /* day6 - part 2 */
  std::vector<std::string> raw_input = file_to_string_vec("input/day6_input.txt");
} else if ((argc == 2) && (*argv[1] == '3')) {
    /* developement */
  std::vector<std::string> raw_input = file_to_string_vec("input/day6_dev.txt");
  CustomsDeclaration cust(raw_input);
  unsigned int yes_count_for_part1 = cust.count_at_least_one_person_said_yes();
  std::cout << "Yes count in input : " << yes_count_for_part1 << std::endl;
} else {
  std::cout << "Error: Invalid argument. Must be \"1\" or \"2\" for solver or \"3\" for developement." << std::endl;
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
