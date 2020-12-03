#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<std::string> file_to_string_vec(std::string file_name);

class DownhillToboggan {
private:
  std::vector<std::string> m_downhill_slope;
  int m_toboggan_x = 0;
  int m_toboggan_y = 0;
  int m_crash_counter = 0;
  int m_slope_width;
  int m_finish_line;

  bool is_there_a_tree(char snowbank) {
    if (snowbank == '#') {
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
    // std::cout << "m_toboggan_x before : " << m_toboggan_x << " --- ";
    m_toboggan_y += y_inc;
    m_toboggan_x += x_inc;
    if (m_toboggan_x >= m_slope_width) {
      m_toboggan_x -= m_slope_width;
    }
    // std::cout << "m_toboggan_x after : " << m_toboggan_x << std::endl;
    if (is_there_a_tree(m_downhill_slope[m_toboggan_y][m_toboggan_x])) {
      m_crash_counter++;
    }
  }

  int downhill_toboggan(int x_inc = 3, int y_inc = 1) {
    std::cout << "Finish line : " << m_finish_line << std::endl;
    m_toboggan_x = 0;
    m_toboggan_y = 0;
    m_crash_counter = 0;
    for (int i = 0; i < m_finish_line; i += y_inc) {
      downhill_increment(x_inc, y_inc);
      // std::cout << "Increment " << i + 1 << " crashes : " << m_crash_counter
      //          << " --- Symbol ["
      //          << m_downhill_slope[m_toboggan_y][m_toboggan_x] << "]"
      //          << std::endl;
    }
    std::cout << "Crash count along " << x_inc << " Right and " << y_inc
              << " Down is : " << m_crash_counter << std::endl;
    return m_crash_counter;
  }
};

DownhillToboggan::DownhillToboggan(std::vector<std::string> downhill_slope)
    : m_downhill_slope(downhill_slope),
      m_finish_line(downhill_slope.size() - 1),
      m_slope_width(m_downhill_slope[0].size()) {}

int main(int argc, char *argv[]) {
  std::chrono::high_resolution_clock::time_point tic =
      std::chrono::high_resolution_clock::now();


  if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
  std::vector<std::string> downhill_slope = file_to_string_vec("day3_input.txt");
    DownhillToboggan sled(downhill_slope);
    sled.downhill_toboggan(3, 1);
  } else if ((argc == 2) && (*argv[1] == '2')) {
    std::vector<std::string> downhill_slope =
        file_to_string_vec("day3_input.txt");
    std::cout << std::boolalpha;
    DownhillToboggan sled(downhill_slope);
    sled.print_downhill_slope();
    unsigned int R1D1, R3D1, R5D1, R7D1, R1D2;
    R1D1 = sled.downhill_toboggan(1, 1);
    R3D1 = sled.downhill_toboggan(3, 1);
    R5D1 = sled.downhill_toboggan(5, 1);
    R7D1 = sled.downhill_toboggan(7, 1);
    R1D2 = sled.downhill_toboggan(1, 2);
    std::cout << "Product of all crashes : " << R1D1 * R3D1 * R5D1 * R7D1 * R1D2
              << std::endl;
  } else {
    std::cout << "Error: Invalid argument. Must be \"1\" or \"2\"."
              << std::endl;
    return 1;
  }

  std::chrono::high_resolution_clock::time_point toc =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(toc - tic);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
