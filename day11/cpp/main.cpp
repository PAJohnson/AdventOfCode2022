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
#include <deque>
#include <functional>

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

using worry = long long;

// monkey problem
// start with modeling
struct Monkey {
    Monkey(std::function<worry(worry)> operation_, std::function<size_t(worry)> test_, std::deque<worry> items_) {
        operation = operation_;
        items = items_;
        test = test_;
        inspected = 0;
    }

    long int inspected;
    std::deque<worry> items;

    // operation associated with monkey like "divide by 23"
    std::function<worry(worry)> operation;

    // test takes an integer result and returns index of monkey to "throw"
    // item to
    std::function<size_t(worry)> test;
};

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    std::vector<Monkey> monkeys;

    // monkey ends at newline in input
    // reset everything at that point
    std::deque<worry> tempItems;
    std::function<worry(worry)> tempOperation;
    std::function<size_t(worry)> tempTest;
    int divideBy;
    size_t trueTarget;
    size_t falseTarget;
    long int modFactor = 1;

    while (std::getline(file, str))
    {
        // newline
        if (str.size() == 0) {
            auto fcn = [divideBy, trueTarget, falseTarget](worry w) {
                if (w % divideBy == 0) {
                    return trueTarget;
                }
                else {
                    return falseTarget;
                }
            };
            tempTest = fcn;
            monkeys.push_back(Monkey(tempOperation, tempTest, tempItems));
            tempItems.clear();
        }
        else if (str.contains("Starting items")) {
            auto toks = split(str, ": ");
            std::vector<std::string> items;
            if (toks[1].contains(",")){
                items = split(toks[1], ", ");
            }
            else {
                items.push_back(toks[1]);
            }

            for (auto& item : items) {
                tempItems.push_back(std::stoi(item));
            }
        }

        //TODO
        // handle the case of old * old instead of old * number for the operation part
        else if (str.contains("Operation:")) {
            auto toks = split(str, "old ");
            auto op = split(toks[1], " ")[0];
            auto lhs = split(toks[1], " ")[0];
            auto rhs = split(toks[1], " ")[1];

            if (op == "+") {
                if (rhs == "old") {
                    auto fcn = [](worry w) {
                        return w + w;
                    };
                    tempOperation = fcn;
                    }
                else {
                    worry num = worry(stoi(rhs));
                    auto fcn = [num](worry w) {
                        return w + num;
                    };
                    tempOperation = fcn;
                }
            }
            else if (op == "*") {
                if (rhs == "old") {
                    auto fcn = [](worry w) {
                        return w * w;
                    };
                    tempOperation = fcn;
                    }
                else {
                    worry num = worry(stoi(rhs));
                    auto fcn = [num](worry w) {
                        return w * num;
                    };
                    tempOperation = fcn;
                }
            }
        }
        else if (str.contains("Test: ")) {
            divideBy = std::stoi(split(str, "by ")[1]);
            modFactor *= divideBy;
        }
        else if (str.contains("If true: ")) {
            trueTarget = std::stoi(split(str, "monkey ")[1]);
        }
        else if (str.contains("If false: ")) {
            falseTarget = std::stoi(split(str, "monkey ")[1]);
        }
    }
    // and once more after the end of the loop...
    auto fcn = [divideBy, trueTarget, falseTarget](worry w) {
        if (w % divideBy == 0) {
            return trueTarget;
        }
        else {
            return falseTarget;
        }
    };
    tempTest = fcn;
    monkeys.push_back(Monkey(tempOperation, tempTest, tempItems));
    tempItems.clear();

    std::vector<Monkey> monkeysTwo{monkeys};

    // part 1
    // 1 turn: a monkey inspects all items
    // 1 round: each monkey gets a turn
    // count the total # of items inspected for each monkey
    // answer is maxInspected[0] * maxInspected[1] after 20 rounds
    int round = 0;
    for (round = 0; round < 20; round++) {
        for (auto& monkey : monkeys) {
            while (monkey.items.size() != 0) {
                worry w = monkey.items.front() % modFactor;
                monkey.items.pop_front();
                worry newWorry = monkey.operation(w) / 3;
                //std::cout << "worry = " << w << " newWorry = " << newWorry << " throwing to monkey " << monkey.test(newWorry) << std::endl;
                monkeys[monkey.test(newWorry)].items.push_back(newWorry);
                monkey.inspected++;
            }
        }
    }

    std::vector<long long int> inspections;
    for (auto& monkey : monkeys) {
        inspections.push_back(monkey.inspected);
    }
    std::sort(inspections.begin(), inspections.end(), std::greater<long long>());
    for (auto i : inspections) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::sort(inspections.begin(), inspections.end(), std::greater<long long>());
    std::cout << inspections[0] * inspections[1] << std::endl;

    // part 2
    // same, but for more rounds...
    // this will overflow even the biggest integer types
    // instead, turn this into a symbolic math deal? either that or find a bignum library
    for (round = 0; round < 10000; round++) {
        for (auto& monkey : monkeysTwo) {
            while (monkey.items.size() != 0) {
                worry w = monkey.items.front() % modFactor;
                monkey.items.pop_front();
                worry newWorry = monkey.operation(w);
                //std::cout << "worry = " << w << " newWorry = " << newWorry << " throwing to monkey " << monkey.test(newWorry) << std::endl;
                monkeysTwo[monkey.test(newWorry)].items.push_back(newWorry);
                monkey.inspected++;
            }
        }
    }

    inspections.clear();
    for (auto& monkey : monkeysTwo) {
        inspections.push_back(monkey.inspected);
    }
    std::sort(inspections.begin(), inspections.end(), std::greater<long long>());
    for (auto i : inspections) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << inspections[0] * inspections[1] << std::endl;
}