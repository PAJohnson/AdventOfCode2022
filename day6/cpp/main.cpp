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

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    std::getline(file, str);

    // now str has entire input
    // part one - find index of first char following first unique 4 character sequence
    auto isUnique = [](std::string buff, int count, int index) {
        std::set<char> subStr;
        for (int i = 0; i < count; i++){
            subStr.emplace(buff[index+i]);
        }
        return subStr.size() == count;
    };

    for (int i = 0; i < str.length() - 4; i++) {
        if (isUnique(str, 4, i)) {
            std::cout << i+4 << std::endl;
            break;
        }
    }

    // part two - same as part one but looking for unique 14 character sequence
    for (int i = 0; i < str.length() - 14; i++) {
        if (isUnique(str, 14, i)) {
            std::cout << i+14 << std::endl;
            break;
        }
    } 
}