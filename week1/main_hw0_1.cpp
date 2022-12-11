/*
 * Title: main_hw0_1.cpp
 * Abstract: Given two integers, displays the sum and absolute difference.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 01/23/2022
 */

#include <iostream>
#include <cmath>

inline int abs_diff(int a, int b) { return abs(a - b); }

int main() {
    int num_a, num_b;
    std::cin >> num_a >> num_b;
    std::cout << "SUM:" << num_a + num_b << '\n';
    std::cout << "DIFF:" << abs_diff(num_a, num_b) << '\n';
    return EXIT_SUCCESS;
}
