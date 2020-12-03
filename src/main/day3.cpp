#include <chrono>

int main(int argc, char *argv[])
{
    std::chrono::high_resolution_clock::time_point tic = std::chrono::high_resolution_clock::now();

    /* insert code here */

    std::chrono::high_resolution_clock::time_point toc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
    std::cout << "Duration: " << time_span.count() << "s" << std::endl;
    return 0;
}
