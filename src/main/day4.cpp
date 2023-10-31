#include "../../include/day4.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point tic =
      std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
  if (argc==2) {
	  std::string filepath = std::string(argv[1]);
	  std::vector<std::string> passport_credentials_messy =
		  file_to_string_vec(filepath);
	  PassportProcessor bob(passport_credentials_messy);
	  const unsigned int answer = bob.count_passports_with_all_req_fields();
	  std::cout << "Valid number of passports (day4-p1) is : " << answer << std::endl;
	  const unsigned int answer_p2 = bob.count_valid_passports();
	  std::cout << "Number of valid passports (day4-p2) is : " << answer_p2 << std::endl;
  } else {
	  std::cout << "Usage:\n./day11 <input_file_path>" << std::endl;
  }
#else
  /* Solution to 2020 Day 4 problem */
  if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {/*solve part 1*/
	  std::vector<std::string> passport_credentials_messy =
		  file_to_string_vec("input/day4_input.txt");
	  PassportProcessor bob(passport_credentials_messy);
	  const unsigned int answer = bob.count_passports_with_all_req_fields();
	  std::cout << "Valid number of passports for day4-p1 is : " << answer << std::endl;
  } else if ((argc == 2) && (*argv[1] == '2')) {/*solve part 2*/
	  std::vector<std::string> passport_credentials_messy =
		  file_to_string_vec("input/day4_input.txt");
	  PassportProcessor bob(passport_credentials_messy);
	  const unsigned int answer_p2 = bob.count_valid_passports();
	  std::cout << "Number of valid passports is : " << answer_p2 << std::endl;
  } else if ((argc == 2) && (*argv[1] == '3')) {/*no part 3 -> developement*/
	  /*Small test file; 4 passports have all required fields; Only 2 count when considering "cid" */
	  std::vector<std::string> passport_credentials_messy =
		  file_to_string_vec("input/day4_dev.txt");
	  PassportProcessor bob(passport_credentials_messy);
	  const unsigned int answer_p1 = bob.count_passports_with_all_req_fields();
	  std::cout << "Number of passports with all required fields is : " << answer_p1 << std::endl;
	  const unsigned int answer_p2 = bob.count_valid_passports();
	  std::cout << "Number of valid passports is : " << answer_p2 << std::endl;
  } else {
	  std::cout << "Error: Invalid argument. Must be \"1\" or \"2\" for solver or \"3\" for debugging."
		  << std::endl;
  }
#endif

  std::chrono::high_resolution_clock::time_point toc =
	  std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
	  std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
