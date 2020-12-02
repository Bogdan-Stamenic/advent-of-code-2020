#include <chrono>
#include <cstring>
#include <iostream>
#include <regex>
#include <span>
#include <typeinfo>
#include <vector>

struct policy {
  std::vector<std::string> limits;
  std::string policy;
  std::string password;
};

std::vector<std::string> file_to_string_vec(std::string file_name);

std::vector<std::string> find_matches(std::string s, std::regex e) {
  std::smatch m;
  std::vector<std::string> matches;
  while (std::regex_search(s, m, e)) {
    matches.push_back(m.str(1));
    s = m.suffix().str();
  }
  return matches;
}

std::vector<policy> setup_policy_test(std::vector<std::string> input) {
  std::vector<policy> output;
  for (auto a : input) {
    std::vector<std::string> helper =
        find_matches(a, std::regex("(([[:digit:]]+(?![[:digit:]]))|([a-z]{1}(?!"
                                   "[[:alpha:]]))|([a-z]+$))"));
    policy next_entry = {.limits = {helper[0], helper[1]},
                         .policy = helper[2],
                         .password = helper[3]};
    output.push_back(next_entry);
  }
  return output;
}

const std::string remove_non_matches(std::string s, std::regex e) {
  std::string filtered = std::regex_replace(s, e, "");
  return filtered;
}

const bool check_policy(policy password_entry) {
  password_entry.password =
      remove_non_matches(password_entry.password,
                         std::regex("(^[" + password_entry.policy + "])"));
  return std::regex_search(password_entry.password,
                           std::regex(password_entry.policy + "{" +
                                      password_entry.limits[0] + "," +
                                      password_entry.limits[1] + "}"));
}

int count_valid_passwords(std::vector<policy> password_entries) {
  int i = 0;
  for (auto a : password_entries) {
    if (check_policy(a)) {
      ++i;
    }
  }
  return i;
}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  std::vector<std::string> passwords_and_policies_from_file =
      file_to_string_vec("day2_input.txt");
  std::vector<policy> policy_vec;
  std::vector<policy> password_entries =
      setup_policy_test(passwords_and_policies_from_file);
  int num_valid_passwords = count_valid_passwords(password_entries);
  std::cout << "Number of valid passwords: " << num_valid_passwords << std::endl;

std::chrono::high_resolution_clock::time_point t2 =
    std::chrono::high_resolution_clock::now();
std::chrono::duration<double> time_span =
    std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
std::cout << "Duration: " << time_span.count() << "s" << std::endl;
return 0;
}
