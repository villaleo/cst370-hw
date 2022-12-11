/*
 * Title: main_hw1_1.cpp
 * Abstract: Given an array of integers, displays the minimum distance followed by
 *           the pairs which have that distance.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 01/29/2022
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cmath>
#include <utility>
#include <algorithm>
#include <limits>

using int_pair = std::pair<int, int>;
using pair_vector = std::vector<int_pair>;

inline int abs_diff(int a, int b) { return abs(a - b); }

struct min_distance_pairs {
    int distance;
    pair_vector min_pairs;
};

min_distance_pairs solve(const std::vector<int> &nums);

int main() {
    std::size_t amount_nums;
    std::cin >> amount_nums;

    std::vector<int> nums(amount_nums);
    for (int& num: nums) {
        std::cin >> num;
    }
    std::sort(nums.begin(), nums.end());

    const auto& [min_distance, min_pairs] = solve(nums);
    std::cout << "Min Distance:" << min_distance << '\n';
    for (const auto& [first, last]: min_pairs) {
        std::cout << "Pair:" << first << ' ' << last << '\n';
    }
    return EXIT_SUCCESS;
}

min_distance_pairs solve(const std::vector<int> &nums) {
    int min_distance = std::numeric_limits<int>::max();
    int_pair min_pair {};
    std::map<int, pair_vector> pairs {};

    // O(n^2) brute force approach:
    for (std::size_t i = 0; i < nums.size() - 1; i++) {
        for (std::size_t j = i + 1; j < nums.size(); j++) {
            int diff = abs_diff(nums[i], nums[j]);
            if (diff <= min_distance) {
                min_distance = diff;
                if (pairs.find(diff) != pairs.end()) {
                    pairs[diff].emplace_back(nums[i], nums[j]);
                } else {
                    pair_vector temp {std::make_pair(nums[i], nums[j])};
                    pairs[diff] = temp;
                }
            }
        }
    }
    return { min_distance, pairs[min_distance] };
}
