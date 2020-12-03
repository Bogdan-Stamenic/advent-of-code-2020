#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name);

class DownhillToboggan {
private:
  std::vector<std::string> m_downhill_slope;
  int toboggan_x, toboggan_y = 0;
  int crash_counter = 0;
  int m_finish_line;

  bool m_is_there_a_tree(char snowbank) {
    if (snowbank == '#') {
      return true;
    } else {
      return false;
    }
    throw std::runtime_error("Error: something unexpexted happened.");
  }

  bool m_did_i_crash(){
      bool arg = m_is_there_a_tree(m_downhill_slope[toboggan_y][toboggan_x]);
      if (arg) {
          return true;
      } else {
          return false;
      }
  }

  bool m_is_out_of_bounds(std::string str, int idx) {
    if (idx > str.size()) {
      return true;
    } else {
      return false;
    }
    throw std::runtime_error("Error: something unexpexted happened.");
  }

public:
  DownhillToboggan(std::vector<std::string> downhill_slope);
  ~DownhillToboggan(){}

  /* Move sled down and check for crashes. Positive y-increment for downhill and
   * positive x-increment for right. */
  void m_downhill_increment(int x_inc = 3, int y_inc = 1) {
    toboggan_y += y_inc;
    if (m_is_out_of_bounds(m_downhill_slope[toboggan_y], toboggan_x + x_inc)) {
      toboggan_x =
          toboggan_x + x_inc - m_downhill_slope[toboggan_y].size();
    } else {
      toboggan_x = toboggan_x + x_inc;
    }
    if(m_did_i_crash()){
        crash_counter++;
    }
  }

  int m_downhill_toboggan(){
    for (int i = 0; i < m_downhill_slope.size(); i++) {
        m_downhill_increment();
        std::cout << "Increment " << i << " crashes : " << crash_counter << std::endl;
    }
    std::cout << "Crash count is : " << crash_counter << std::endl;
    return crash_counter;
  }
};

DownhillToboggan::DownhillToboggan(std::vector<std::string> downhill_slope)
    : m_downhill_slope(downhill_slope), m_finish_line(downhill_slope.size()) {}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point tic =
      std::chrono::high_resolution_clock::now();

  std::vector<std::string> downhill_slope =
      file_to_string_vec("day3_input.txt");
  int finish_line = downhill_slope.size();
  std::cout << std::boolalpha;
  DownhillToboggan sled(downhill_slope);
  sled.m_downhill_toboggan();

  std::chrono::high_resolution_clock::time_point toc =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
