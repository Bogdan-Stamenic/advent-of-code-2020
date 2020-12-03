#include <chrono>
#include <iostream>
#include <span>
#include <stdexcept>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name);

class DownhillToboggan {
private:
  std::vector<std::string> m_downhill_slope;
  int m_toboggan_x, m_toboggan_y = 0;
  int m_crash_counter = 0;
  int m_slope_width;
  int m_finish_line;

  bool is_there_a_tree(char snowbank) {
    if (snowbank == '#') {
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
  ~DownhillToboggan() {}

  void print_downhill_slope() {
    for (auto a : m_downhill_slope) {
      std::cout << a << std::endl;
    }
  }

  /* Move sled down and check for crashes. Positive y-increment for downhill and
   * positive x-increment for right. */
  void downhill_increment(int x_inc = 3, int y_inc = 1) {
    m_toboggan_y += y_inc;
    if (is_out_of_bounds(m_downhill_slope[m_toboggan_y],
                         m_toboggan_x + x_inc)) {
      m_toboggan_x += x_inc - m_slope_width;
    } else {
      m_toboggan_x += x_inc;
    }
    if (m_downhill_slope[m_toboggan_y][m_toboggan_x] == '#') {
      std::cout << "Crash!" << std::endl;
      m_crash_counter++;
    } else {
    }
  }

  int downhill_toboggan() {
    std::cout << "Finish line : " << m_finish_line << std::endl;
    for (int i = 0; i < m_finish_line; i++) {
      downhill_increment();
      std::cout << "Increment " << i + 1 << " crashes : " << m_crash_counter
                << " --- Symbol ["
                << m_downhill_slope[m_toboggan_y][m_toboggan_x] << "]"
                << std::endl;
    }
    std::cout << "Crash count is : " << m_crash_counter << std::endl;
    return m_crash_counter;
  }
};

DownhillToboggan::DownhillToboggan(std::vector<std::string> downhill_slope)
    : m_downhill_slope(downhill_slope), m_finish_line(downhill_slope.size()),
      m_slope_width(m_downhill_slope[0].size()) {}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point tic =
      std::chrono::high_resolution_clock::now();

  std::vector<std::string> downhill_slope =
      file_to_string_vec("day3_input.txt");
  std::cout << std::boolalpha;
  DownhillToboggan sled(downhill_slope);
  // sled.print_downhill_slope();
  //sled.downhill_toboggan();
  std::cout << downhill_slope[322][0] << std::endl;

  std::chrono::high_resolution_clock::time_point toc =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
