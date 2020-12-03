#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name);

class DownhillToboggan {
private:
  std::vector<std::string> m_downhill_slope;
  int m_toboggan_x, m_toboggan_y = 0;
  int m_crash_counter = 0;
  int m_finish_line;

  bool is_there_a_tree(char snowbank) {
    if (snowbank == '#') {
      return true;
    }
    return false;
  }

  bool did_i_crash(){
      bool arg = is_there_a_tree(m_downhill_slope[m_toboggan_y][m_toboggan_x]);
      if (arg) {
          return true;
      }
      return false;
  }

  bool is_out_of_bounds(std::string str, int idx) {
    if (idx > str.size()) {
      return true;
    }
  return false;
  }

public:
  DownhillToboggan(std::vector<std::string> downhill_slope);
  ~DownhillToboggan(){}

  /* Move sled down and check for crashes. Positive y-increment for downhill and
   * positive x-increment for right. */
  void downhill_increment(int x_inc = 3, int y_inc = 1) {
    m_toboggan_y += y_inc;
    if (is_out_of_bounds(m_downhill_slope[m_toboggan_y], m_toboggan_x + x_inc)) {
      m_toboggan_x =
          m_toboggan_x + x_inc - m_downhill_slope[m_toboggan_y].size();
    } else {
      m_toboggan_x = m_toboggan_x + x_inc;
    }
    if(did_i_crash()){
        m_crash_counter++;
    }
  }

  int downhill_toboggan(){
    for (int i = 0; i < m_downhill_slope.size(); i++) {
        downhill_increment();
        std::cout << "Increment " << i << " crashes : " << m_crash_counter << std::endl;
    }
    std::cout << "Crash count is : " << m_crash_counter << std::endl;
    return m_crash_counter;
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
  sled.downhill_toboggan();

  std::chrono::high_resolution_clock::time_point toc =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
