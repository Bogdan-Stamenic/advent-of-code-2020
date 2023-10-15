#include "../include/customs_declaration.h"
#include <iostream>
#include <regex>

CustomsDeclaration::CustomsDeclaration(const std::vector<std::string>& input_str){
    input_customs_forms(input_str);
}

void CustomsDeclaration::print_all_customs_forms_by_group(){
    for(const auto& line: m_customs_forms_by_group){
        std::cout << line << std::endl;
    }
}

void CustomsDeclaration::input_customs_forms(const std::vector<std::string>& input_str) {
    bool parsing_customs_form = false;
    std::regex e("[a-z]");
    for(const auto& line: input_str) {
        if(std::regex_search(line, e)) {
            if(parsing_customs_form){
                m_customs_forms_by_group.back().append(std::string(" ").append(line));
            } else {
                m_customs_forms_by_group.push_back(line);
                parsing_customs_form = true;
            }
        } else {
            parsing_customs_form = false;
        }
    }
}

unsigned int CustomsDeclaration::count_at_least_one_person_said_yes(){
    std::vector<unsigned int> at_least_one_person_said_yes_by_group;
    unsigned int yes_count = 0;
    for (const auto& customs_forms: m_customs_forms_by_group) {
        for (const auto& an_answer: m_possible_answers) {
            if (customs_forms.find(an_answer) != std::string::npos) {
                yes_count++;
            }
        }
        at_least_one_person_said_yes_by_group.push_back(yes_count);
        yes_count = 0;
    }
    /* yes_count should be 0 after prev for-loop terminates */
    for (auto yes_count_by_group: at_least_one_person_said_yes_by_group) {
        yes_count += yes_count_by_group;
    }
    return yes_count;
}
