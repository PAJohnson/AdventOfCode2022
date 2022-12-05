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
#include <array>

#define INPUT "../inputs/input.txt"
#define SAMPLE "../inputs/sample.txt"

void partOne() {
    return;
}

void partTwo() {
    return;
}

// from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
// Neat!
std::vector<std::string> split(const std::string str, const std::string regex_str)
{
    std::regex regexz(regex_str);
    std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                  std::sregex_token_iterator());
    return list;
}

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    // pair of start and end pairs
    // 2-4,6-8
    // 2-3,4-5
    // 5-7,7-9
    // 2-8,3-7
    // 6-6,4-6
    // 2-6,4-8
    // determine how many pairs have one span fully contained in the other
    int contained = 0;
    int overlapping = 0;
    while (std::getline(file, str))
    {
        auto elves = split(str, ",");
        std::array<int, 2> elfOne = {std::stoi(split(elves[0], "-")[0]), std::stoi(split(elves[0], "-")[1])};
        std::array<int, 2> elfTwo = {std::stoi(split(elves[1], "-")[0]), std::stoi(split(elves[1], "-")[1])};
        bool oneWithin = false;
        // is first contained in second?
        if ((elfOne[0] >= elfTwo[0]) && (elfOne[1] <= elfTwo[1])) {
            oneWithin = true;
        }
        // is second contained in first?
        else if ((elfTwo[0] >= elfOne[0]) && (elfTwo[1] <= elfOne[1])) {
            oneWithin = true;
        }

        contained += oneWithin;

        // part two
        // determine how many sequences overlap at all
        if ((elfOne[0] >= elfTwo[0]) && (elfOne[0] <= elfTwo[1]) ||
            (elfOne[1] >= elfTwo[0]) && (elfOne[1] <= elfTwo[1]) ||
            oneWithin) {
            overlapping += 1;
        }
    }
    std::cout << contained << '\n';
    std::cout << overlapping << '\n';
}