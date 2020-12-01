#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <span>

int find_sum_2020p1(std::span<int> int_span) {
  for (auto &i : int_span) {
    for (auto &j : int_span) {
      if (i + j == 2020) {
        return i * j;
      }
    }
  }
  throw std::runtime_error{"Could not find entries."};
}

int find_sum_2020p2(std::span<int> int_span) {
  for (auto &i : int_span) {
    for (auto &j : int_span) {
      for (auto &k : int_span) {
        if (i + j + k == 2020) {
          return i * j * k;
        }
      }
    }
  }
  throw std::runtime_error{"Could not find entries."};
}
