#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> file_to_int_vec(std::string file_name)
{
	std::ifstream input_stream;
	std::string line;
	std::vector<int> output_vec;
	std::cout << file_name << std::endl;
	
	input_stream.open(file_name);
	if (input_stream.is_open()) {
		while( std::getline(input_stream, line) ){
			output_vec.push_back(std::stoi(line));
		}
		input_stream.close();
	}else{
		std::cout << "Error: "<< file_name << " couldn't be read." << std::endl;
	}	
	if (!output_vec.empty()) {
		std::cout << "Successfully inputted \"" << file_name << "\"." << std::endl;
	}

	return output_vec;
}
