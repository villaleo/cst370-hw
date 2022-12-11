/*
 * Title: main_hw1_2.cpp
 * Abstract: Given two arrays of integers, displays the non-common numbers between both arrays.
 *           Displays "NONE" if all numbers in both arrays are common.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 01/29/2022
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
#include <optional>

using optional_vector = std::optional<std::vector<int>>;

optional_vector solve(const std::set<int> &group1, const std::set<int> &group2);

int main() {
    std::size_t group1_size;
    std::size_t group2_size;

    std::cin >> group1_size;
    std::set<int> group1;
    for (std::size_t i = 0; i < group1_size; i++) {
        int num;
        std::cin >> num;
        group1.insert(num);
    }

    std::cin >> group2_size;
    std::set<int> group2;
    for (std::size_t i = 0; i < group2_size; i++) {
        int num;
        std::cin >> num;
        group2.insert(num);
    }

    auto results = solve(group1, group2);
    std::cout << "Answer:";
    if (results.has_value()) {
        auto nums = results.value();
        for (std::size_t i = 0; i < nums.size(); i++) {
            if (i == nums.size() - 1) {
                std::cout << nums[i];
                break;    
            }
            std::cout << nums[i] << ' ';
        }
        std::cout << '\n';
    } else {
        std::cout << "NONE\n";
    }
    return EXIT_SUCCESS;
}

optional_vector solve(const std::set<int> &group1, const std::set<int> &group2) {
    // O(n) approach using sets:
    std::vector<int> non_commons;
    for (const int num: group1) {
        if (group2.find(num) == group2.end()) {
            non_commons.push_back(num);
        }
    }
    for (const int num: group2) {
        if (group1.find(num) == group1.end()) {
            non_commons.push_back(num);
        }
    }
    std::sort(non_commons.begin(), non_commons.end(), std::greater<int>());
    return non_commons.empty()? std::nullopt : optional_vector {non_commons};
}
