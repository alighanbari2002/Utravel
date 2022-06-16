#ifndef TOOLS_HPP_INCLUDE
#define TOOLS_HPP_INCLUDE

#include <string>
#include <vector>

std::string randString(int length);

void trimLeft(std::string& str);
void trimRight(std::string& str);
void trim(std::string& str);

std::vector<std::string> splitByDelim(const std::string& str, char delim = ',');

#endif // TOOLS_HPP_INCLUDE