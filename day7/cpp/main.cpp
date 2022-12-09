#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <set>
#include <cctype>
#include <map>
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

int main() {
    std::ifstream file(SAMPLE);
    std::string str; 

    // part one - parse into trees
    // given terminal output of cd and ls commands
    // does part two has rm? or other commands?
    // Maybe 2022 AoC will be busybox implementation instead of assembly interpreter!

    // first - test if regex can be used to strip start of string

    // rethink and tackle tomorrow
    // Tried a tree before. This time, just do a map.
    std::map<std::string, long int> fs;
    std::string current_path = "root/";
    while (std::getline(file, str))
    {
        // in ls output
        if (str.find("$ cd") != std::string::npos) {
            auto dirname = split(str, " cd ")[1];
            if (dirname == "..") {
                // pop off everything after last '/' in current_path
                current_path.pop_back();
                while (current_path.back() != '/') {
                    current_path.pop_back();
                }
            }
            else {
                // add to current path
                if (dirname != "/") {
                    current_path.append(dirname + "/");
                }
            }
        }    
        else if (str.find("$") == std::string::npos) {
            if (str.find("dir") != std::string::npos) {
                // do nothing with dirs until we try to cd into them
            }
            else {
                std::string fname = split(str, " ")[1];
                long size = stol(split(str, " ")[0]);
                fs.insert({current_path + fname, size});
            }
        }
    }

    std::map<std::string, long> dirSizes;
    for (auto p : fs) {
        //std::cout << p.first << " " << p.second << std::endl;
        auto dirs = split(p.first, "/");
        dirs.pop_back(); // get rid of filename
        std::string dirname;
        for (auto dir : dirs) {
            dirname = dirname + dir + "/";
            dirSizes[dirname] += p.second;
        }
    }
    // get list of subdirs
    long partOne = 0;
    for (auto d : dirSizes) {
        //std::cout << d.first << " " << d.second << std::endl;
        if (d.second <= 100000) {
            partOne += d.second;
        }
    }
    std::cout << partOne << std::endl;

    // part two - find smallest single directory to delete to get enough free space
    long totalSpace = 70'000'000;

    // really want to have the map iterate in order sorted by value, not key...
    // make a vector of pairs and sort on the second value?
    std::vector<std::pair<std::string, long>> sortedBySize;
    for (auto d : dirSizes) {
        sortedBySize.push_back(std::make_pair(d.first, d.second));
    }

    std::sort(sortedBySize.begin(), sortedBySize.end(), [=](auto& a, auto& b)
    {
        return a.second < b.second;
    });

    auto used = sortedBySize.back().second;
    auto needed = 30'000'000 - (totalSpace - used);
    for (auto d : sortedBySize) {
        if (d.second > needed) {
            std::cout << d.second << std::endl;
            break;
        }
    }
}