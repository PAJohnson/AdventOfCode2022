#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

// return greatest amount of calories held my and single elf
void partOne(const std::vector<long int>& calories) {
    // useful but equivalent to calories[0] for a sorted vector
    //int i = std::distance(calories.begin(),std::max_element(calories.begin(), calories.end()));
    std::cout << calories[0] << '\n';
}

// return total calories from top 3 elves
void partTwo(const std::vector<long int>& calories) {
    std::cout << calories[0] + calories[1] + calories[2] << '\n';
}

void vectorPrint(const std::vector<long int>& in) {
    for (auto i : in) {
        std::cout << i << '\n';
    }
}

int main() {
    std::vector<long int> calories;
    std::ifstream file("../inputs/input.txt");
    std::string str; 

    long int calSum = 0;

    while (std::getline(file, str))
    {
        if (str.length() > 0) { // check for empty line
            long int i = std::stol(str);
            calSum = calSum + i;
        }
        else {
            calories.push_back(calSum);
            calSum = 0;
        }
    }

    // do a sort from most to least
    std::sort(calories.begin(), calories.end(), std::greater<long int>());

    partOne(calories);
    partTwo(calories);
}