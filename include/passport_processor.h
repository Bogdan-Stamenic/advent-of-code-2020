#include <chrono>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class PassportProcessor {
public:
  const unsigned int get_passports_size();
  void print_passports_contents();
  unsigned int count_passports_with_all_req_fields();
  unsigned int count_valid_passports();
  PassportProcessor(const std::vector<std::string>& input_str);
  ~PassportProcessor() = default;

private:
  std::unordered_map<std::string,unsigned int> m_encode_passport_cred{{"pid",0},{"ecl",1},{"hcl",2},{"eyr",3},{"byr",4},{"hgt",5},{"iyr",6},{"cid",7}};
  std::unordered_map<unsigned int,std::string> m_decode_passport_cred{{0,"pid"},{1,"ecl"},{2,"hcl"},{3,"eyr"},{4,"byr"},{5,"hgt"},{6,"iyr"},{7,"cid"}};
  std::vector<std::string> m_passports;
  std::vector<std::unordered_map<unsigned int,std::string>> m_processed_passports;

  std::pair<unsigned int, std::string> extract_key_value_from_passport(const std::string& passport, const unsigned int sep_idx);  void input_to_passport_vec(const std::vector<std::string>& input_str);
  void parse_passport_credentials();
  const bool does_processed_passport_have_all_req_fields(const std::unordered_map<unsigned int, std::string>& passport, std::initializer_list<unsigned int> required_creds={0,1,2,3,4,5,6});
  std::vector<std::unordered_map<unsigned int,std::string>> collect_candidate_valid_passports();
  const bool validate_passport(const std::unordered_map<unsigned int,std::string>& candidate_passport);
};

