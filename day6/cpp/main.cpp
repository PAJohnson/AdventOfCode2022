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
    std::ifstream file(INPUT);
    std::string str; 

    while (std::getline(file, str))
    {
    }
    // now str has entire input
    // part one - find index of first char following first unique 4 character sequence
    auto isUnique = [](std::string buff, int count, int index) {
        std::set<char> subStr;
        for (int i = 0; i < count; i++){
            subStr.emplace(buff[index+i]);
        }
        return subStr.size() == count;
    };
    for (int i = 0; i < str.length() - 3; i++) {
        if (isUnique(str, 4, i)) {
            std::cout << i+4 << std::endl;
            break;
        }
    }
    // part two - same as part one but looking for unique 14 character sequence
    for (int i = 0; i < str.length() - 3; i++) {
        if (isUnique(str, 14, i)) {
            std::cout << i+14 << std::endl;
            break;
        }
    } 
}