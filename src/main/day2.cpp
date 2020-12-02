#include <iostream>
#include <chrono>
#include <span>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name);
std::span<std::string> parse_password_policy(std::string);

int main(int argc, char *argv[])
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	std::vector<std::string> passwords_and_policies = file_to_string_vec("day2_input.txt");

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Duration: " << time_span.count() << "s" << std::endl;
	return 0;
}
