#ifndef CHINESE_REMAINDER_THEOREM_H
#define CHINESE_REMAINDER_THEOREM_H
#include <cstdint>
#include <string>
#include <vector>

/* Implements direct solution construction
 * For an explanation of the problem, see : https://en.wikipedia.org/wiki/Chinese_remainder_theorem */
int64_t solve_with_chinese_remainder_theorem(const std::vector<int64_t>& n_divisors, const std::vector<int64_t>& r_remainders);
/* Greastest common denominator from Bézout's Identity */
int64_t gcd(int64_t a, int64_t b);
/* From Wikipedia; uses Extended Euler Algorithm */
int64_t mod_inverse(int64_t a, int64_t n);
std::pair<int64_t,int64_t> find_bezout_coeficients(int64_t a, int64_t b);

void test_find_bezout_coeficients();
void test_solve_with_chinese_remainder_theorem();
#endif
