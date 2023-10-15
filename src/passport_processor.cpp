#include <algorithm>
#include <functional>
#include <regex>
#include "../include/passport_processor.h"


PassportProcessor::PassportProcessor(const std::vector<std::string>& input_str) {
    input_to_passport_vec(input_str);//writes to m_passports
    parse_passport_credentials();//writes to m_processed_passports
}

const unsigned int PassportProcessor::get_passports_size() {
    return m_passports.size();
}

void PassportProcessor::print_passports_contents() {
    for(const auto a: m_passports) {
        std::cout << a << std::endl;
    }
}

/* Counts valid passports according to AOC 2020 day4-part 1. */
unsigned int PassportProcessor::count_passports_with_all_req_fields() {
    unsigned int valid_passport_count = 0;
    for(const auto& passport: m_processed_passports) {
        const bool has_all_req_fields = does_processed_passport_have_all_req_fields(passport);
        valid_passport_count += (has_all_req_fields) ? 1 : 0;
    }
    return valid_passport_count;
}

unsigned int PassportProcessor::count_valid_passports() {
    std::vector<std::unordered_map<unsigned int,std::string>> candidate_passports = collect_candidate_valid_passports();
    auto test_byr = [](auto x){
        std::string y = x.at(0);
        return (y.length() == 4) && (std::stoi(y) >= 1920) && (std::stoi(y) <= 2002);
    };
    auto test_iyr = [](auto x){
        std::string y=x.at(1);
        return (y.length() == 4) && (std::stoi(y) >= 2010) && (std::stoi(y) <= 2020);
    };
    auto test_eyr = [](auto x){
        std::string y=x.at(2);
        return (y.length() == 4) && (std::stoi(y) >= 2020) && (std::stoi(y) <= 2030);
    };
    auto test_hgt = [](auto x){
        std::string y=x.at(3);
        if(y.find("cm") != std::string::npos){
            return (std::stoi(y) >= 150) && (std::stoi(y) <= 193);
        }else if(y.find("in") != std::string::npos){
            return (std::stoi(y) >= 59) && (std::stoi(y) <= 76);
        }
        return false;
    };
    auto test_hcl = [](auto x){
        std::string y=x.at(4);
        std::regex e("#[0-9a-f]{6}");
        return std::regex_search(y,e);
    };
    auto test_ecl = [](auto x){
        std::string y=x.at(5);
        const std::vector<std::string> valid_colors{"amb","blu","brn","gry","grn","hzl","oth"};
        bool is_valid_color = false;
        for (const std::string& str: valid_colors){
            if(y.compare(str) == 0){
                is_valid_color = true;
                break;
            }
        }
        return is_valid_color;
    };
    auto test_pid = [](auto x){return (x.at(6).length() == 9);};
    /* I couldn't figure out how to group and loop over lambdas, so just call once for each lambda instead */
    std::erase_if(candidate_passports, std::not_fn(test_byr));
    std::erase_if(candidate_passports, std::not_fn(test_iyr));
    std::erase_if(candidate_passports, std::not_fn(test_eyr));
    std::erase_if(candidate_passports, std::not_fn(test_hgt));
    std::erase_if(candidate_passports, std::not_fn(test_hcl));
    std::erase_if(candidate_passports, std::not_fn(test_ecl));
    std::erase_if(candidate_passports, std::not_fn(test_pid));
    return candidate_passports.size();
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
            processed_passport.insert(passport_entry);
            sep_idx += 1;
        }
        m_processed_passports.push_back(processed_passport);
    }
}

/* Checks for different passport credentials depending on the initializer list that's passed. */
const bool PassportProcessor::does_processed_passport_have_all_req_fields(const std::unordered_map<unsigned int, std::string>& passport, std::initializer_list<unsigned int> required_creds){
    /* For correspondance, refer to PassportProcessor::m_decode_passport_cred */
    bool has_all_req_fields = true;
    const std::vector<unsigned int> check_creds = required_creds;
    for (auto a: check_creds) {
        if(passport.count(a) == 0) {
            /* Flag as invalid for missing a credential */
            has_all_req_fields = false;
            break;
        }
    }
    return has_all_req_fields;
}

std::vector<std::unordered_map<unsigned int,std::string>> PassportProcessor::collect_candidate_valid_passports() {
    std::vector<std::unordered_map<unsigned int,std::string>> candidate_passports;
    for(const auto passport: m_processed_passports) {
        const bool is_candidate = does_processed_passport_have_all_req_fields(passport);
        if(is_candidate){
            candidate_passports.push_back(passport);
        }
    }
    return candidate_passports;
}

