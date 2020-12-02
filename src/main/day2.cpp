#include <chrono>
#include <iostream>
#include <regex>
#include <vector>

struct policy_info {
  std::vector<int> limits;
  std::string policy;
  std::string password;
};

std::vector<std::string> file_to_string_vec(std::string file_name);
const policy_info
&parse_password_policy(std::string passwords_and_policies_from_file) {
  /* Delimiters: "-", " ", ": " */
  std::regex match_this("[[:digit:]]+");
	std::smatch sm;
	policy_info parsed;

	if (std::regex_match(passwords_and_policies_from_file, sm, match_this)) {
		for (int i=0; i<2; ++i) {
			std::string helper = sm[i];
			parsed.limits.push_back(std::stoi(helper));
		}
		//parsed.policy = sm[2];
		//parsed.password = sm[3];
		return parsed;
	}else{
		for (auto a: sm) {
			std::cout << "[" << a << "] " << std::endl;
		}
		throw std::runtime_error("Error: couldn't find any matches.");
	}
}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  std::vector<std::string> passwords_and_policies_from_file =
      file_to_string_vec("day2_input.txt");
  struct policy_info parsed =  parse_password_policy(passwords_and_policies_from_file[0]);
  std::cout << "Contents of passwords_and_policies_from_file[0]: " << parsed.limits[0]
	  << ", " << parsed.limits[1] << ", "<< parsed.policy << ", " << parsed.password << std::endl;


  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
