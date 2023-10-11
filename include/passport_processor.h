#include <chrono>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class PassportProcessor {
private:
  std::vector<std::unordered_map<std::string, std::string>> clean_creds;
  bool is_key_inside(std::string key, int idx);
  void parse_and_append_str_to_map(std::unordered_map<std::string, std::string> myMap, std::string messy_entr, bool debug=false);
  void tidy_credentials(std::vector<std::string> messy_creds);

public:
  void get_num_valid_p1();
  void print_clean_creds_entry_size();
  PassportProcessor(std::vector<std::string> messy_credentials) {
      tidy_credentials(messy_credentials);
  }
  ~PassportProcessor() {}
};
