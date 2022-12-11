/*
 * Title: main_hwX_Y.cpp
 * Abstract: Given a list of numbers, displays the largest one using
 *           divide-and-conquer.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 03/25/2022
 */

#include <iostream>
#include <vector>
#include <algorithm>

auto solution(const std::vector<int> &a, int begin, int end) -> int;

int main() {
    int size; std::cin >> size;
    std::vector<int> input(size);

    for (int &num : input) std::cin >> num;

    std::cout << solution(input, 0, size - 1) << '\n';
    return 0;
}

auto solution(const std::vector<int> &a, int begin, int end) -> int {
    if (begin == end) return a[begin];

    int left = solution(a, begin, (begin + end) / 2);
    int right = solution(a, ((begin + end) / 2 + 1), end);
    return std::max(left, right);
}
