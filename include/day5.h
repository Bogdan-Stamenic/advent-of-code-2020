#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name, char delim='\n');
//std::vector<int> file_to_int_vec(std::string file_name);

std::unordered_map<char, int> decoder({{'F', 0}, {'B', 1}, {'L', 0}, {'R', 1}});

struct SeatPos {
  unsigned int row;
  unsigned int column;
};


