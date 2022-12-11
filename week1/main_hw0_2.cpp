/*
 * Title: main_hw0_2.cpp
 * Abstract: Displays the minimum, maximum, and median of a set of 5 numbers.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 01/23/2022
 */

#include <iostream>
#include <array>
#include <algorithm>

int main() {
    const int AMT_NUMS {5};
    std::array<int, AMT_NUMS> nums {};

    for (std::size_t i = 0; i < AMT_NUMS; i++)
        std::cin >> nums.at(i);
    
    std::sort(nums.begin(), nums.end());

    std::cout << "MIN:" << nums.front() << '\n';
    std::cout << "MAX:" << nums.back() << '\n';
    std::cout << "MEDIAN:" << nums.at(2) << '\n';

    return EXIT_SUCCESS;
}
