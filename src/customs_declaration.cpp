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

unsigned int CustomsDeclaration::count_everyone_said_yes() {
    std::vector<unsigned int> everyone_said_yes_by_group;
    for (const auto& customs_forms: m_customs_forms_by_group) {
        unsigned int yes_count = count_entire_group_said_yes(customs_forms);
        everyone_said_yes_by_group.push_back(yes_count);
    }
    unsigned int yes_count = 0;
    for (auto yes_count_by_group: everyone_said_yes_by_group) {
        yes_count += yes_count_by_group;
    }
    return yes_count;
}

unsigned int CustomsDeclaration::count_entire_group_said_yes(const std::string& groups_customs_forms) {
    /* split into answers by individuals */
    if (groups_customs_forms.find(' ') == std::string::npos) {
        /* Only one entry -> count all */
        unsigned int yes_count = 0;
        for (const auto& an_answer: m_possible_answers) {
            if (groups_customs_forms.find(an_answer) != std::string::npos) {
                yes_count++;
            }
        }
        return yes_count;
    } else {
        unsigned int idx = 0;
        unsigned int last_idx = 0;
        bool parsing_forms = true;
        std::vector<std::string> individual_customs_forms;
        /* Parse customs forms from a group into customs form by each individual */
        while(parsing_forms) {
            idx = (groups_customs_forms.find(' ',idx) == std::string::npos)
                ? groups_customs_forms.size()
                : groups_customs_forms.find(' ',idx);
            std::string individuals_answers = groups_customs_forms.substr(last_idx, idx - last_idx);
            individual_customs_forms.push_back(individuals_answers);
            if (groups_customs_forms.find(' ',idx) == std::string::npos) {
                parsing_forms = false;
            }
            idx++;
            last_idx = idx;
        } 
        /* Collect all letters found in first customs form */
        std::vector<char> matched_answers;
        for(const auto& an_answer: m_possible_answers){
            if (individual_customs_forms[0].find(an_answer) != std::string::npos) {
                matched_answers.push_back(an_answer);
            }
        }
        /* Remove matched answers that don't show up in the other individual's customs forms */
        //for (auto form: individual_customs_forms) {
        auto it = individual_customs_forms.begin(); it++;//start at second entry
        for (it; it!=individual_customs_forms.end(); it++) {
            auto p = [it](char c){return (it->find(c) == std::string::npos);};
            std::erase_if(matched_answers, p);
            if (matched_answers.size() == 0) {
                break;
            }
        }
        return matched_answers.size();
    }
}
