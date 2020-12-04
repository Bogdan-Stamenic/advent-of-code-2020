#include <chrono>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name,
                                            char delim = '\n');

class PassportProcessor {
    private:
          std::vector<std::map<std::string, std::string>> clean_creds;

          std::map<std::string, std::string> messy_entry_to_map (std::string messy_entry){
              std::map<std::string, std::string> myMap;
              int idx = 0;
              while(idx < messy_entry.size()){
              /*insert code here*/
                  if (messy_entry.find(:, idx) != std::string::npos) {
                      std::string key = messy_entry.substr(idx, 3);
                      std::cout << "Key : " << key << std::endl;
                      /* should equal std::string::npos when at final entry --> */
                      int eov = messy_entry.find(" ", idx); 
                      std::string value = messy_entry.substr(idx+4, eov - (idx + 4));
                      std::cout << "Value : " << value << std::endl;
                      myMap.insert(std::pair<std::string, std::string>(key, value));
                      idx += 5 + value.size();
                      continue;
                  } else {
                      break;
                  }
              }
              return myMap;
          }

          bool is_key_inside (std::string key, int idx){
              return clean_creds[idx].find(key) != clean_creds[idx].end();
          }

    public:
        void
        tidy_credentials(std::vector<std::string> messy_creds) {
          std::map<std::string, std::string> clean_cred_entry;
          for (auto messy_cred_entry : messy_creds) {
            if (messy_cred_entry.empty()) {
              clean_creds.push_back(clean_cred_entry);
              clean_cred_entry.erase(clean_cred_entry.begin(), clean_cred_entry.end());
            } else {
            }
            //return clean_creds
          }
          throw std::runtime_error("Error: something unexpected happened.");
        }
};

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point tic =
      std::chrono::high_resolution_clock::now();

  /* insert code here */
  std::vector<std::string> passport_credentials_messy =
      file_to_string_vec("day4_input.txt");
  // for (auto a : passport_credentials_messy) {
  //  std::cout << a << std::endl;
  //}

  std::chrono::high_resolution_clock::time_point toc =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
