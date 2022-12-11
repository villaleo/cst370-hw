/*
 * Title: main_hw4_2.cpp
 * Abstract: Partitions n positive integers into two disjoint sets 
 *           with the same sum.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/25/2022
 */

#include <iostream>
#include <deque>
#include <cmath>
#include <string>
#include <algorithm>
#include <numeric>

std::string to_binary(int n);
std::string generate_padding(int n);

template <class Type>
std::ostream &operator<<(std::ostream &os, const std::deque<Type> &list);

int main() {
    int amount;
    std::cin >> amount;

    std::deque<int> nums(amount);
    for (int& n: nums) std::cin >> n;

    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 == 1) {
        std::cout << "Equal Set: 0\n";
        return 0;
    }
    int expected_sum = sum / 2;

    int exponential_amount = static_cast<int>(pow(2, amount));
    std::deque<std::string> bits(exponential_amount);
    for (size_t i = 0; i < exponential_amount; i++)
        bits[i] = generate_padding(amount - to_binary(i).size()) + to_binary(i);

    std::deque<int> zeroes_digits, ones_digits;
    for (size_t i = 0; i < exponential_amount; i++) {
        int zeroes_sum = 0, ones_sum = 0;
        for (size_t j = 0; j < nums.size(); j++) {
            if (bits[i][j] == '0') {
                zeroes_digits.push_back(nums[j]);
                zeroes_sum += nums[j];
            } else {
                ones_digits.push_back(nums[j]);
                ones_sum += nums[j];
            }
        }

        if (zeroes_sum != expected_sum) {
            zeroes_digits.clear();
            ones_digits.clear();
            continue;
        }

        std::sort(zeroes_digits.begin(), zeroes_digits.end());
        std::sort(ones_digits.begin(), ones_digits.end());

        std::cout << "Equal Set: ";
        std::cout << (zeroes_digits.front() < ones_digits.front()? zeroes_digits : ones_digits);
        return 0;
    }

    std::cout << "Equal Set: 0\n";    
    return 0;
}

std::string to_binary(int n) {
    std::deque<char> out;
    if (n == 0) return "0";
    while (n > 0) {
        out.push_front(n % 2 == 0? '0' : '1');
        n /= 2;
    }
    return std::string(out.begin(), out.end());
}

std::string generate_padding(int n) {
    std::string out;
    for (int i = 0; i < n; i++) out += "0";
    return out;
}

template <class Type>
std::ostream &operator<<(std::ostream &os, const std::deque<Type> &list) {
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list.at(i);
        if (i == list.size() - 1) {
            os << '\n';
            break;
        }
        os << ' ';
    }
    return os;
}
