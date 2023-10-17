#include "../../include/day7.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class RulesParser {
    public:
        RulesParser(const std::vector<std::string>& input){
            parse_input_to_bag_graph(input);
        };
        ~RulesParser() = default;
        void print_hashing_for_testing(){
            for (auto mod: m_possible_modifiers) {
                for (auto clr: m_possible_colors) {
                    std::string str;
                    str.append(mod.substr(0,2));
                    unsigned int clr_idx = (clr.size() == 3) ? 0 : clr.size() - 4;
                    str.append(clr.substr(clr_idx,3));
                    std::cout << str << std::endl;
                }
            }
        }

    private:
        std::unordered_map<std::string,std::unordered_map<std::string, int>> m_bag_graph;
        /* Possible modifiers and colors found using bash cmds */
        const std::vector<std::string> m_possible_modifiers{"bright","clear","dark","dim","dotted","drab",
            "dull","faded","light","mirrored","muted","pale","plaid","posh","shiny","striped",
            "vibrant","wavy"};
        const std::vector<std::string> m_possible_colors{"aqua","beige","black","blue","bronze","brown",
            "chartreuse","coral","crimson","cyan","fuchsia","gold","gray","green","indigo","lavender",
            "lime","magenta","maroon","olive","orange","plum","purple","red","salmon","silver","tan",
            "teal","tomato","turquoise","violet","white","yellow"};
        void parse_input_to_bag_graph(const std::vector<std::string>& input){
            std::vector<std::pair<std::string,std::string>> parents_and_children_from_input;
            /* Split parents and children from input and build graph */
            for (auto line: input) {
                std::string sep_phrase = " bags contain ";
                unsigned int idx = line.find(sep_phrase);
                if (idx == std::string::npos) {
                    throw std::logic_error("couldn't match \" bags contain \" for parsing key. Re-check input file and parsing code's source file.");
                }
                unsigned int parent_start_idx = 0;
                unsigned int parent_length = idx;
                unsigned int children_start_idx = idx + sep_phrase.size();
                unsigned int children_length = line.size() - (sep_phrase.size() + idx);
                std::string parent_str = line.substr(parent_start_idx, parent_length);
                std::string children_str = line.substr(children_start_idx, children_length);
                std::pair<std::string,std::string> parent_and_children{parent_str, children_str};
                parents_and_children_from_input.push_back(parent_and_children);
            }
            //for (auto pair: parents_and_children_from_input) {
            //    std::cout << pair.first << std::endl;
            //}
            /* For perfect hash tables (and speed) use first 2 letters of key-string (first two letters of modifier) and last 3 letters of key-string (last three letters of color) */
        }
};


int main(int argc, char *argv[]) {
/* Start timer */
std::chrono::high_resolution_clock::time_point t1 =
    std::chrono::high_resolution_clock::now();

if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
  /* day7 - part 1 */
  //std::vector<std::string> input_line_by_line = file_to_string_vec("input/day7_input.txt");
  std::cout << "Not yet implemented..." << std::endl;
  } else if ((argc == 2) && (*argv[1] == '2')) {
  /* day7 - part 2 */
  //std::vector<std::string> input_line_by_line = file_to_string_vec("input/day7_input.txt");
  std::cout << "Not yet implemented..." << std::endl;
} else if ((argc == 2) && (*argv[1] == '3')) {
    /* developement */
  std::vector<std::string> input_line_by_line = file_to_string_vec("input/day7_dev.txt");
  RulesParser stickler(input_line_by_line);
  stickler.print_hashing_for_testing();
} else {
  std::cout << "Error: Invalid argument. Must be \"1\" or \"2\" for solver or \"3\" for developement." << std::endl;
  return 1;
}

/* Stop timer */
std::chrono::high_resolution_clock::time_point t2 =
    std::chrono::high_resolution_clock::now();
std::chrono::duration<double> time_span =
    std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
std::cout << "Duration: " << time_span.count() << "s" << std::endl;
return 0;
}
