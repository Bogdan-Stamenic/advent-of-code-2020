#include "../../include/day4.h"

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point tic =
      std::chrono::high_resolution_clock::now();

  /* Solution to 2020 Day 4 problem */
  if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {/*solve part 1*/
      std::vector<std::string> passport_credentials_messy =
          file_to_string_vec("day4_input.txt");
      PassportProcessor bob(passport_credentials_messy);
      // bob.print_clean_creds_entry_size();
      bob.get_num_valid_p1();
  } else if ((argc == 2) && (*argv[1] == '2')) {/*solve part 2*/
    std::cout << "Not yet implemented..."
              << std::endl;
  } else if ((argc == 2) && (*argv[1] == '3')) {/*no part 3 -> debug*/
      /*Small test file; 4 valid "passports" and 1 invalid; Only 2 are valid passports with "cid"*/
      std::vector<std::string> passport_credentials_messy =
          file_to_string_vec("day4_debug.txt");
      PassportProcessor bob(passport_credentials_messy);
      // bob.print_clean_creds_entry_size();
      //bob.get_num_valid_p1();
  } else {
    std::cout << "Error: Invalid argument. Must be \"1\" or \"2\" for solver or \"3\" for debugging."
              << std::endl;
  }

  std::chrono::high_resolution_clock::time_point toc =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
