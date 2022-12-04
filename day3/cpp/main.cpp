#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <set>
#include <cctype>
#include <unordered_map>

#define INPUT "../inputs/input.txt"
#define SAMPLE "../inputs/sample.txt"

void partOne(const std::vector<std::pair<std::set<int>, std::set<int>>>& compartments) {
    int sum = 0;
    for (auto c : compartments) {
        std::set<int> intersection;
        std::set_intersection(c.first.begin(), c.first.end(), c.second.begin(), c.second.end(), std::inserter(intersection, intersection.begin()));
        for (auto i : intersection) {
            sum += i;
        }
    }
    std::cout << sum << '\n';
}

// split rucksacks into groups of 3 vectors sequentially and find the common element in each group of 3
// sum common elements for answer
void partTwo(std::vector<std::vector<int>>& rucksacks) {
    // process chunks of 3 rucksacks
    int sum = 0;
    for (int i = 0; i < rucksacks.size() - 2; i = i + 3) {
        std::unordered_map<int, int> triple;
        
        for (int item : std::set<int>(rucksacks[i].begin(), rucksacks[i].end())) {
            triple[item] += 1;
        }
        for (int item : std::set<int>(rucksacks[i+1].begin(), rucksacks[i+1].end())) {
            triple[item] += 1;
        }
        for (int item : std::set<int>(rucksacks[i+2].begin(), rucksacks[i+2].end())) {
            triple[item] += 1;
        }

        for (int key = 1; key < 53; key++) {
            if (triple[key] == 3) {
                sum += key;
            }
        }
    }
    std::cout << sum << '\n';
}

// convert chars to numbers like so
// a-z = 1-26
// A-Z = 27-52
int prioritize(const char c) {
    if (isupper(c)) {
        return static_cast<int>(c) - 38;
    }
    else {
        return static_cast<int>(c) - 96;
    }
};

int main() {

    // partOne parsing
    {
        std::ifstream file(INPUT);
        std::string str; 

        // model data for part one as a vector of pairs of sets
        // partOne answer is sum of values of intersections of each pair of sets
        std::vector<std::pair<std::set<int>, std::set<int>>> compartments;
        while (std::getline(file, str))
        {
            // split into two equal length substrings
            std::string leftStr = str.substr(0, str.length() / 2);
            std::string rightStr = str.substr(str.length() / 2);

            std::set<int> left;
            std::set<int> right;

            for (char c : leftStr) {
                left.insert(prioritize(c));
            }

            for (char c : rightStr) {
                right.insert(prioritize(c));
            }

            compartments.push_back({left, right});
        }
        partOne(compartments);
    }

    // partTwo parsing
    {
        std::ifstream file(INPUT);
        std::string str;

        // handle triples in partTwo()
        std::vector<std::vector<int>> rucksacks;

        while (std::getline(file, str)) {
            std::vector<int> rucksack;
            for (char c : str) {
                rucksack.push_back(prioritize(c));
            }
            rucksacks.push_back(rucksack);
        }

        partTwo(rucksacks);
    }
}