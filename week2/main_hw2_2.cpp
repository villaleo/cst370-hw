/*
 * Title: main_hw2_2.cpp
 * Abstract: Given a number, n, displays 2^n in binary. Also accepts n strings and displays them
 *           based on the position of the bits in the binary string. Example: 0101 -> B D, for 
 *           the queries A, B, C, and D.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/08/2022
 */

#include <iostream>
#include <deque>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

using std::string, std::deque, std::size_t;
using std::cout, std::cin;

string toBinary(int n);
string generatePadding(size_t amount);

int main() {
    size_t amount;
    cin >> amount;

    deque<string> symbols(amount);
    for (auto &symbol: symbols)
        cin >> symbol;

    int powerAmount = static_cast<int>(pow(2, amount));
    size_t width = toBinary(powerAmount).size();
    std::string padding;

    for (size_t i = 0; i < powerAmount; i++) {
        cout << i << ':';

        if (toBinary(i).size() < width)
            padding =  generatePadding(width - toBinary(i).size() - 1);
        cout << padding << toBinary(i) << ':';
        if (i == 0)
            cout << "EMPTY";

        string temp = padding + toBinary(i);
        deque<string> symbolOutput;
        for (size_t j = 0; j < temp.size(); j++) {
            if (temp[j] == '1')
                symbolOutput.push_back(symbols[j]);
        }

        for (size_t j = 0; j < symbolOutput.size(); j++) {
            if (j == symbolOutput.size() - 1)
                cout << symbolOutput[j];
            else
                cout << symbolOutput[j] << ' ';
        }
        cout << '\n';
    }
    return EXIT_SUCCESS;
}

string toBinary(int n) {
    deque<char> bits;
    n = abs(n);

    if (n == 0)
        return "0";

    while (n > 0) {
        bits.push_front((n % 2 == 1) ? '1' : '0');
        n /= 2;
    }
    return string(bits.begin(), bits.end());
}

string generatePadding(size_t amount) {
    std::stringstream ss;
    for (size_t i = 0; i < amount; i++) {
        ss << '0';
    }
    return ss.str();
}
