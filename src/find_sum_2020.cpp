#include <iostream>
#include <span>
#include <string>
#include <vector>

std::span<int> find_sum_2020p1(std::span<int> int_span) {
  std::span<int> nums;
  for (auto i : int_span) {
    for (auto j : int_span) {
      if (i + j == 2020) {
        nums.push_back(j);
        break;
      }
    }
    if (!nums.empty()) {
      nums.push_back(i);
      break;
    }
  }
  std::cout << "Size of vector:" << nums.size() << std::endl;
  std::cout << "Expenses that sum to 2020:" << std::endl;
  for (auto i : nums) {
    std::cout << i << std::endl;
  }
  return nums;
}

std::span<int> find_sum_2020p2(std::span<int> int_span) {
  std::span<int> nums;
  for (auto &i : int_span) {
    for (auto &j : int_span) {
      for (auto &k : int_span) {
        if (i + j + k == 2020) {
          nums.push_back(k);
          break;
        }
      }
      if (nums.size() == 1) {
        nums.push_back(j);
        break;
      }
    }
    if (nums.size() == 2) {
      nums.push_back(i);
      break;
    }
  }
  std::cout << "Size of vector:" << nums.size() << std::endl;
  std::cout << "Expenses that sum to 2020:" << std::endl;
  for (auto i : nums) {
    std::cout << i << std::endl;
  }
  return nums;
}
