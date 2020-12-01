#include <iostream>
#include <string>
#include <vector>

std::vector<int> find_sum_2020p1(std::vector<int> int_vec)
{
	std::vector<int> nums;
	for (auto i: int_vec) {
		for (auto j: int_vec) {
			if (i+j == 2020) {
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
	for (auto i: nums) {
		std::cout << i << std::endl;
	}
	return nums;
}

std::vector<int> find_sum_2020p2(std::vector<int> int_vec)
{
	std::vector<int> nums;
	for (auto& i: int_vec) {
		for (auto& j: int_vec) {
			for (auto& k: int_vec) {
				if (i+j+k == 2020) {
					nums.push_back(k);
					break;				
				}
			}
			if (nums.size()==1) {
				nums.push_back(j);
				break;
			}
		}
		if (nums.size()==2){
			nums.push_back(i);
			break;
		}
	}
	std::cout << "Size of vector:" << nums.size() << std::endl;
	std::cout << "Expenses that sum to 2020:" << std::endl;
	for (auto i: nums) {
		std::cout << i << std::endl;
	}
	return nums;
}


