#include "../include/passport_processor.h"


PassportProcessor::PassportProcessor(const std::vector<std::string>& input_str) {
    input_to_passport_vec(input_str);
    parse_passport_credentials();
}

int PassportProcessor::get_passports_size() {
    return m_passports.size();
}

void PassportProcessor::print_passports_contents() {
    for(const auto a: m_passports) {
        std::cout << a << std::endl;
    }
}

/* Gets vector of passport input file that was read line-by-lines (delim=\n).
 * Passport entries that spanned multiple lines are grouped into their own single vector entry in passport.
 * */
void PassportProcessor::input_to_passport_vec(const std::vector<std::string>& input_str) {
    bool parsing_passport = false;
    for(const auto& line: input_str) {
        if(line.find(':') != std::string::npos) {
            if(parsing_passport){
                m_passports.back().append(std::string(" ").append(line));
            } else {
                m_passports.push_back(line);
                parsing_passport = true;
            }
        } else {
            parsing_passport = false;
        }
    }
}

/* Gets key and value and returns them as a pair */
std::pair<unsigned int, std::string> PassportProcessor::extract_key_value_from_passport(const std::string& passport, const unsigned int sep_idx) {
            /* Find where the key starts and value ends of key-value pair embedded in passport */
            unsigned int key_idx = (passport.rfind(' ', sep_idx) == std::string::npos) ? 0 : passport.rfind(' ', sep_idx);
            unsigned int val_idx = (passport.find(' ', sep_idx) == std::string::npos) ? passport.length() : passport.find(' ', sep_idx);
            /* Extract key and value from string*/
            std::string key = passport.substr(sep_idx-3,3);
            unsigned int encoded_key = m_encode_passport_cred.at(key);
            unsigned int val_length = val_idx - (sep_idx + 1);
            std::string value = passport.substr(sep_idx+1, val_length);
            /* Construct pair and return it */
            std::pair<unsigned int, std::string> passport_entry{encoded_key, value};
            return passport_entry;
}

/* Read credentials for each passport into a hash map and save it to m_processed_passports */
void PassportProcessor::parse_passport_credentials() {
    for (const auto passport: m_passports) {
        unsigned int sep_idx = 0;
        std::unordered_map<unsigned int, std::string> processed_passport;
        while(passport.find(':', sep_idx) != std::string::npos) {
            sep_idx = passport.find(':', sep_idx);
            std::pair<unsigned int, std::string> passport_entry = extract_key_value_from_passport(passport, sep_idx);
            std::cout << "passport_entry.first : " << passport_entry.first << "; passport_entry.second : " << passport_entry.second << std::endl;
            processed_passport.insert(passport_entry);
            sep_idx += 2;
        }
        m_processed_passports.push_back(processed_passport);
    }
}
