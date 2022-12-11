/*
 * Title: main_hw3_3.cpp
 * Abstract: Given two times, finds the time elapsed between them.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/15/2022
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

struct TimeStamp {
    int hour;
    int minute;
    int second;

    static inline int totalSeconds(const TimeStamp &t) {
        return t.hour * 3600 + t.minute * 60 + t.second;
    }

    TimeStamp() {
        hour = 0;
        minute = 0;
        second = 0;
    }

    TimeStamp(int hour, int minute, int second): hour(hour), minute(minute), second(second) {}

    friend std::istream &operator>>(std::istream &in, TimeStamp &time);

    friend std::ostream &operator<<(std::ostream &out, const TimeStamp &time);

    friend TimeStamp operator-(const TimeStamp &t1, const TimeStamp &t2);
};

int main() {
    TimeStamp s1, s2;
    std::cin >> s1 >> s2;

    std::cout << s1 - s2;
    return 0;
}

std::istream &operator>>(std::istream &in, TimeStamp &time) {
    char delim = '\0';
    int hour, minute, second;
    in >> hour >> delim >> minute >> delim >> second;

    time.hour = hour;
    time.minute = minute;
    time.second = second;
    return in;
}

std::ostream &operator<<(std::ostream &out, const TimeStamp &time) {
    if (time.hour < 10) out << '0';
    out << time.hour << ':';
    if (time.minute < 10) out << '0';
    out << time.minute << ':';
    if (time.second < 10) out << '0';
    out << time.second << '\n';
    return out;
}

TimeStamp operator-(const TimeStamp &t1, const TimeStamp &t2) {
    int a = TimeStamp::totalSeconds(t1);
    int b = TimeStamp::totalSeconds(t2);
    int c = b - a;

    int hrs = floor(c / 3600);
    int mins = static_cast<int>(floor(c / 60)) % 60;
    int secs = c - (hrs * 3600) - (mins * 60);

    if (c > 0) {
        return TimeStamp(hrs, mins, secs);
    }

    c = 86400 + b - a;
    hrs = floor(c / 3600);
    mins = static_cast<int>(floor(c / 60)) % 60;
    secs = c - (hrs * 3600) - (mins * 60);

    return TimeStamp(hrs, mins, secs);
}
