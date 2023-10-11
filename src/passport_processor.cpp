#include "../include/passport_processor.h"

bool PassportProcessor::is_key_inside(std::string key, int idx) {
return clean_creds[idx].find(key) != clean_creds[idx].end();
}


/* Parse string into unordered map. */
void PassportProcessor::parse_and_append_str_to_map(std::unordered_map<std::string, std::string> myMap, std::string messy_entry, bool debug) {
  int idx = 3;/* Colons must always be at idx >= 3 */
  while (idx < messy_entry.size()) {
    if (messy_entry.find(":", idx) != std::string::npos) {/*Is there a match at idx?*/
      /*Key always starts 3 before colon ":"*/
      std::string key = messy_entry.substr(idx-3, 3);
      /* If no " " is found, then the entry is final and the value goes until the end of messy_entry */
      int val_final_idx = (messy_entry.find(" ", idx) == std::string::npos) ? messy_entry.size() - 1 : messy_entry.find(" ", idx) - 1;
      std::string value = messy_entry.substr(idx + 1, val_final_idx - idx);
      // std::cout << "Value : " << value << std::endl;
      myMap.emplace(key, value);
      std::pair<std::string, std::string> entry(key, value);
      std::cout << "entry->first : " << entry.first << std::endl;
      std::cout << "entry->second : " << entry.second << std::endl;
      idx += 5 + value.size();
      continue;
    } else {
      break;
    }
  }
}

void PassportProcessor::tidy_credentials(std::vector<std::string> messy_creds) {
  /* clear vector clean_creds before starting */
  this->clean_creds.erase(clean_creds.begin(), clean_creds.end());
  std::unordered_map<std::string, std::string> clean_cred_entry;
  for (auto m : messy_creds) {
    std::cout << m << std::endl;
    if (m.empty()) {
      /* Empty line means end of passport entry -> pushback */
      clean_creds.push_back(clean_cred_entry);
    } else {
      parse_and_append_str_to_map(clean_cred_entry, m);
    }
  }
  // throw std::runtime_error("Error: something unexpected happened.");
  std::cout << "Credentials have been processed!" << std::endl;
}

void PassportProcessor::get_num_valid_p1() {
  int valid_count = 0;
  std::vector<std::string> fields = {"ecl", "pid", "eyr", "hcl",
                                     "byr", "iyr", "hgt"};
  /*#pragma omp for schedule(dynamic)*/
  std::vector<std::unordered_map<std::string, std::string>>::iterator c;
  // for (auto c : clean_creds) {
  for (c = clean_creds.begin(); c < clean_creds.begin() + 3; c++) {
    std::cout << "Next!" << std::endl;
    for (auto v : *c) {
      std::cout << "v.first: [" << v.first << "]" << std::endl;
    }
    if (c->empty()) {
      std::cout << "Map is empty!" << std::endl;
    }
    for (auto f : fields) {
      // std::cout << (c.count(f) == 0) << std::endl;
      // if (c.count(f) == 0) {
      if (c->count(f) == 0) {
        std::cout << "f : [" << f << "]" << std::endl;
      } else {
        std::cout << "Bleck" << std::endl;
      }
    }
    valid_count += 1;
  }
  std::cout << "Valid passports : " << valid_count << std::endl;
}

void PassportProcessor::print_clean_creds_entry_size() {
  for (auto a : clean_creds) {
    std::cout << "Size of clean_creds entry : " << a.size() << std::endl;
  }
}


