/*
 * Title: main_hw3_2.cpp
 * Abstract: Given two strings, determines whether they are strings or not.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/14/2022
 */

#include <iostream>
#include <string>
#include <map>

void displayIfAnagram(std::string, std::string);

int main() {
    std::string str_a, str_b;
    std::cin >> str_a >> str_b;

    displayIfAnagram(str_a, str_b);
    return 0;
}

void displayIfAnagram(std::string str_a, std::string str_b) {
    std::map<char, int> mapA;
    for (char c: str_a) mapA[c]++;

    auto mapB = mapA;
    for (char c: str_b) {
        if (mapB.count(c) == 0 or mapB[c] == 0) break;
        if (mapB[c] == 1) {
            mapB.erase(c);
        } else {
            mapB[c]--;
        }
    }

    if (!mapB.empty()) {
        std::cout << "NO ANAGRAM\n";
        return;
    }

    std::cout << "ANAGRAM\n";
    for (auto [key, value]: mapA) {
        std::cout << key << ':' << value << '\n';
    }
}
