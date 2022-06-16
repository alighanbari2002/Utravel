#include "tools.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <random>
#include <sstream>
#include <string>
#include <vector>

std::string randString(int length) {
    std::string str(length, '0');

    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    thread_local static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    thread_local static std::uniform_int_distribution<int> dist(0, sizeof(charset) - 2);

    std::generate_n(str.begin(), length, [charset]() -> char {
        return charset[dist(gen)];
    });

    return str;
}

void trimLeft(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}
void trimRight(std::string& str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}
void trim(std::string& str) {
    trimLeft(str);
    trimRight(str);
}

std::vector<std::string> splitByDelim(const std::string& str, char delim) {
    std::vector<std::string> result;
    std::istringstream sstr(str);
    std::string part;
    while (std::getline(sstr, part, delim)) {
        trimRight(part);
        result.push_back(part);
        while (std::isspace(static_cast<unsigned char>(sstr.peek()))) sstr.ignore();
    }
    return result;
}