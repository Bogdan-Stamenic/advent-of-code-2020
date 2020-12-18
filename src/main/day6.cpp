#include <chrono>

int main(int argc, char *argv[]) {
  /* Start timer */
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  /* insert code here */

  /* Stop timer */
  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Duration: " << time_span.count() << "s" << std::endl;
  return 0;
}
