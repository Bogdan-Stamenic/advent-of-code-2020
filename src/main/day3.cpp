#include <chrono>
#include <iostream>
#include <vector>
#include <stdexcept>

std::vector<std::string> file_to_string_vec(std::string file_name);

bool is_there_a_tree (char snowbank){
    if (snowbank == '#') {
        return true;
    }else{
        return false;
    }
    throw std::runtime_error("Error: something unexpexted happened.");
}

int main(int argc, char *argv[])
{
    std::chrono::high_resolution_clock::time_point tic = std::chrono::high_resolution_clock::now();

    std::vector<std::string> downhill_slope = file_to_string_vec("day3_input.txt");
    int finish_line = downhill_slope.size();
    std::cout << std::boolalpha;
    std::cout << "downhill_slope[0][3]: " << downhill_slope[0][3] << std::endl;
    std::cout << "Crash into tree? : " << is_there_a_tree(downhill_slope[0][3]) << std::endl;
    /* insert code here */

    std::chrono::high_resolution_clock::time_point toc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
    std::cout << "Duration: " << time_span.count() << "s" << std::endl;
    return 0;
}
