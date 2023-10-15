#ifndef CUSTOMS_DECLARATION_H
#define CUSTOMS_DECLARATION_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class CustomsDeclaration {
    public:
        CustomsDeclaration(const std::vector<std::string>& input_str);
        ~CustomsDeclaration() = default;
        void print_all_customs_forms_by_group();
        unsigned int count_at_least_one_person_said_yes();

    private:
        const std::vector<char> m_possible_answers = {'a','b','c','d','e',
            'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u',
            'v','w','x','y','z'};
        std::vector<std::string> m_customs_forms_by_group;
        void input_customs_forms(const std::vector<std::string>& input_str);
};
#endif
