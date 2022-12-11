/*
 * Title: main_hw5_1.cpp
 * Abstract: Reverses a given integer, trimming any leading zeros.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/27/2022
 */

#include <iostream>
#include <string>
#include <cstdlib>

std::string reverse_num(const int num, std::string s);

int main() {
    int num;
    std::cin >> num;
    std::cout << reverse_num(num, "") << '\n';

    return 0;
}

std::string reverse_num(const int num, std::string s) {
    if (num == 0)
        return s;
    if (num % 10 == 0)
        return reverse_num(num / 10, s);

    s += std::to_string(num % 10);
    return reverse_num(num / 10, s);
}
