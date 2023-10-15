#ifndef PASSPORT_PROCESSOR_H
#define PASSPORT_PROCESSOR_H
#include <cstdio>
#include <iostream>
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
  const std::unordered_map<std::string,unsigned int> m_encode_passport_cred{{"byr",0},{"iyr",1},{"eyr",2},{"hgt",3},{"hcl",4},{"ecl",5},{"pid",6},{"cid",7}};
  const std::unordered_map<unsigned int,std::string> m_decode_passport_cred{{0,"byr"},{1,"iyr"},{2,"eyr"},{3,"hgt"},{4,"hcl"},{5,"ecl"},{6,"pid"},{7,"cid"}};
  std::vector<std::string> m_passports;
  std::vector<std::unordered_map<unsigned int,std::string>> m_processed_passports;

  std::pair<unsigned int, std::string> extract_key_value_from_passport(const std::string& passport, const unsigned int sep_idx);
  void input_to_passport_vec(const std::vector<std::string>& input_str);
  void parse_passport_credentials();
  const bool does_processed_passport_have_all_req_fields(const std::unordered_map<unsigned int, std::string>& passport, std::initializer_list<unsigned int> required_creds={0,1,2,3,4,5,6});
  std::vector<std::unordered_map<unsigned int,std::string>> collect_candidate_valid_passports();
};
#endif
