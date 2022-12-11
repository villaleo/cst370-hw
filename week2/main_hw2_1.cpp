/*
 * Title: main_hw2_1.cpp
 * Abstract: Given a number n, followed by n pairs of numbers, this program computes the range
 *           where all n ranges overlap. If no such range exists, -1 is displayed.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/08/2022
 */

#include <iostream>
#include <cstdlib>
#include <utility>
#include <optional>
#include <limits>
#include <vector>

using range = std::pair<int, int>;
std::optional<range> getMinMax(std::vector<range> &list);

int main() {
    std::size_t amount;
    std::cin >> amount;
    if (amount <= 0)
        return EXIT_SUCCESS;

    std::vector<range> ranges(amount);
    for (auto &[x, y]: ranges)
        std::cin >> x >> y;

    const auto intersection = getMinMax(ranges);
    if (intersection.has_value()) {
        const auto &[x, y] = intersection.value();
        std::cout << x << ' ' << y << '\n';
    } else
        std::cout << "-1\n";
    return EXIT_SUCCESS;
}

std::optional<range> getMinMax(std::vector<range> &list) {
    int min = std::numeric_limits<int>::max(), max = std::numeric_limits<int>::min();
    for (const auto &[x, y]: list) {
        if (x > max)
            max = x;
        if (y < min)
            min = y;
    }
    return max > min? std::optional<range>() : std::make_pair(max, min);
}
