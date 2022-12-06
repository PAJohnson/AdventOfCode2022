#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <set>
#include <cctype>
#include <unordered_map>
#include <regex>

#define INPUT "../inputs/input.txt"
#define SAMPLE "../inputs/sample.txt"

// from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
// Neat!
std::vector<std::string> split(const std::string str, const std::string regex_str)
{
    std::regex regexz(regex_str);
    std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                  std::sregex_token_iterator());
    return list;
}

void partOne() {
    return;
}

void partTwo() {
    return;
}

int main() {
    std::ifstream file(SAMPLE);
    std::string str; 

    while (std::getline(file, str))
    {
    }
}