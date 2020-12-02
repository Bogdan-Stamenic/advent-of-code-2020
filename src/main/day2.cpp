#include <chrono>
#include <cstring>
#include <iostream>
#include <regex>
#include <span>
#include <typeinfo>
#include <vector>

struct policy {
  std::vector<int> limits;
  std::string policy;
  std::string password;
};

std::vector<std::string> file_to_string_vec(std::string file_name);
const policy parse_password_policy(std::string password_and_policy_from_file) {
  /* Delimiters: "-", " ", ": " */
  std::vector<std::regex> match_this = {
      std::regex("^[0-9]+"), std::regex("[0-9]+(?=[[:space:]])"),
      std::regex("[a-z]{1}(?=:)"), std::regex("[a-z]+$")};
  std::vector<std::string> helper;
  std::smatch sm;

  for (auto exp : match_this) {
    std::regex_search(password_and_policy_from_file, sm, exp);
    helper.push_back(sm[0].str());
  }
  policy parsed = {.limits = {helper[0], helper[1]},
                   .policy = helper[2],
                   .password = helper[3]};
  return parsed;
  // throw std::runtime_error("Error: couldn't find any matches.");
}

/* Replace all non-policy chars and search the remaining string for a match */
// bool check_password(policy entry){
// 	auto const exp = std::regex("^" + entry.policy + "{" + entry.limits[0] +
// "," + entry.limits[1] + "}$"); 	return std::regex_search(entry.password, exp);
// }

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  std::vector<std::string> passwords_and_policies_from_file =
      file_to_string_vec("day2_input.txt");
  std::vector<policy> policy_vec;
  for (auto a : passwords_and_policies_from_file) {
    policy_vec.push_back(parse_password_policy(a));
  }
  std::cout << check_password(policy_vec[0]) << std::endl;

  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
