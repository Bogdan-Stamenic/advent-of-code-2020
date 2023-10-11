#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

//std::vector<int> file_to_int_vec(std::string file_name);
//std::vector<std::string> file_to_string_vec(std::string file_name, char delim);

std::vector<int> file_to_int_vec(std::string file_name)
{
	std::ifstream input_stream;
	std::string line;
	std::vector<int> output_vec;
	
	input_stream.open(file_name);
	if (input_stream.is_open()) {
		while( std::getline(input_stream, line) ){
			output_vec.push_back(std::stoi(line));
		}
		input_stream.close();
	}else{
		throw std::logic_error{"Error: file couldn't be read."};
	}	
	if (!output_vec.empty()) {
		std::cout << "Successfully inputted \"" << file_name << "\"." << std::endl;
	}

	return output_vec;
}

std::vector<std::string> file_to_string_vec(std::string file_name, char delim = '\n')
{
	std::ifstream input_stream;
	std::string line;
	std::vector<std::string> output_vec;
	
	input_stream.open(file_name);
	if (input_stream.is_open()) {
		while( std::getline(input_stream, line, delim) ){
			output_vec.push_back(line);
		}
		input_stream.close();
	}else{
		throw std::logic_error("Error: file couldn't be read.");
	}	
	if (!output_vec.empty()) {
		std::cout << "Successfully inputted \"" << file_name << "\"." << std::endl;
	}

	return output_vec;
}
