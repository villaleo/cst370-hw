/*
 * Title: main_hw3_1.cpp
 * Abstract: Given a string, this program determines whether it is a palindrome or
 *           not. Ignores cases.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/14/2022
 */

#include <iostream>
#include <string>

// * Ignore cases
// * String will be alphanumeric
bool isPalindrome(std::string);

int main() {
    std::string s;
    std::cin >> s;

    std::cout << (isPalindrome(s)? "TRUE" : "FALSE") << '\n';
    return 0;
}

bool isPalindrome(std::string str) {
    if (str.size() <= 1) return true;

    for (char &c: str) c = std::tolower(c);

    size_t head = 0, tail = str.size() - 1;
    while (head <= tail) {
        if (str[head++] != str[tail--]) return false;
    }
    return true;
}
