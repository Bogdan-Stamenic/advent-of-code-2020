#include <chrono>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name);

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  std::vector<std::string> passwords_and_policies_from_file =
      file_to_string_vec("day2_input.txt");
  int valid_count = 0;
  for (auto entry : passwords_and_policies_from_file) {
    int dashPosition = entry.find('-');
    int colonPosition = entry.find(':');
    int minCount = std::stoi(entry.substr(0, dashPosition));
    int maxCount = std::stoi(entry.substr(dashPosition + 1, colonPosition - 2));
    std::string policy = entry.substr(colonPosition - 1, 1);
    std::string password = entry.substr(colonPosition + 1, entry.size() - colonPosition + 1);
    //std::cout << "minCount: " << minCount << std::endl;
    //std::cout << "maxCount: " << maxCount << std::endl;
    //std::cout << "policy: " << policy << std::endl;
    //std::cout << "password: " << password << std::endl;

    int policy_count = 0;
    while (password != "") {
      if(password.find(policy) == std::string::npos){
          break;
      }else{
          int idx = password.find(policy);
          password = password.substr(idx + 1);
          //std::cout << "Current password substring is: " << password << std::endl;
          policy_count++;
          //std::cout << "policy count: " << policy_count << std::endl;
      }
    }

    if ( (policy_count >= minCount) && (policy_count <= maxCount) ) {
        valid_count++;
        //std::cout << "Ok\n" << std::endl;
    }
  }
  //std::cout << "Valid passwords: " << valid_count << std::endl;

  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
