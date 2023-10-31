#ifndef FILE_TO_VEC_H
#define FILE_TO_VEC_H
#include <vector>
#include <string>

std::vector<int> file_to_int_vec(std::string file_name);
std::vector<int64_t> file_to_long_vec(std::string file_name);
std::vector<std::string> file_to_string_vec(std::string file_name, char delim = '\n');
#endif
