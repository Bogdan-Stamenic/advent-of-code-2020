#include "../../include/day2.h"

void solve_part1(std::vector<std::string> passwords_and_policies_from_file) {
  int valid_count = 0;
  for (auto entry : passwords_and_policies_from_file) {
    int dashPosition = entry.find('-');
    int colonPosition = entry.find(':');
    int minCount = std::stoi(entry.substr(0, dashPosition));
    int maxCount = std::stoi(entry.substr(dashPosition + 1, colonPosition - 2));
    std::string policy = entry.substr(colonPosition - 1, 1);
    std::string password =
        entry.substr(colonPosition + 1, entry.size() - colonPosition + 1);
    // std::cout << "minCount: " << minCount << std::endl;
    // std::cout << "maxCount: " << maxCount << std::endl;
    // std::cout << "policy: " << policy << std::endl;
    // std::cout << "password: " << password << std::endl;

    int policy_count = 0;
    while (password != "") {
      if (password.find(policy) == std::string::npos) {
        break;
      } else {
        int idx = password.find(policy);
        password = password.substr(idx + 1);
        // std::cout << "Current password substring is: " << password <<
        // std::endl;
        policy_count++;
        // std::cout << "policy count: " << policy_count << std::endl;
      }
    }

    if ((policy_count >= minCount) && (policy_count <= maxCount)) {
      valid_count++;
      // std::cout << "Ok\n" << std::endl;
    }
  }
  std::cout << "Valid passwords: " << valid_count << std::endl;
}

void solve_part2(std::vector<std::string> passwords_and_policies_from_file) {
  int valid_count = 0;
  for (auto entry : passwords_and_policies_from_file) {
    int dashPosition = entry.find('-');
    int colonPosition = entry.find(':');
    int posOne = std::stoi(entry.substr(0, dashPosition));
    int posTwo = std::stoi(entry.substr(dashPosition + 1, colonPosition - 2));
    std::string policy = entry.substr(colonPosition - 1, 1);
    std::string password =
        entry.substr(colonPosition + 1, entry.size() - colonPosition + 1);
    //    std::vector<int> policy_positions = {posOne, posTwo};
    // std::cout << "posOne: " << posOne << std::endl;
    // std::cout << "posTwo: " << posTwo << std::endl;
    // std::cout << "policy: " << policy << std::endl;
    // std::cout << "password: " << password << std::endl;

    if ((password.substr(posOne, 1).compare(policy) == 0) !=
        (password.substr(posTwo, 1).compare(policy) == 0)) {
      valid_count++;
      // std::cout << "Ok\n" << std::endl;
    }
  }
  std::cout << "Valid passwords: " << valid_count << std::endl;
}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  std::vector<std::string> passwords_and_policies_from_file =
      file_to_string_vec("input/day2_input.txt");
  if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
    solve_part1(passwords_and_policies_from_file);
  } else if ((argc == 2) && (*argv[1] == '2')) {
    solve_part2(passwords_and_policies_from_file);
  } else {
    std::cout << "Error: Invalid argument. Must be \"1\" or \"2\"."
              << std::endl;
    return 1;
  }

  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
