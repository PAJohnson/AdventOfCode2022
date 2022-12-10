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
#define SAMPLE2 "../inputs/sample2.txt"

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

// similar to intcode
struct Computer {
    Computer() {
        x = 1;
        ip = 0;
        waiting = false;
        waitCount = 0;
    }

    int x; // one register
    int ip; // instruction pointer

    bool waiting; // for multi-cycle ops
    int waitCount;

    void reset() {
        x = 1;
        ip = 0;
        waiting = false;
        waitCount = 0;
    }

    void step(std::vector<std::string>& program) {
        auto toks = split(program[ip], " ");
        auto opcode = toks[0];

        if (opcode == "noop") {
            // do nothing
            ip++;
        }
        else if (opcode == "addx") {
            if (!waiting) {
                waiting = true;
                waitCount = 1;
            }
            else {
                waitCount--;
                if(waitCount == 0) {
                    waiting = false;
                    ip++;
                    x += stoi(toks[1]);
                }
            }
        }
    }
};

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    Computer comp;

    std::vector<std::string> program;
    while (std::getline(file, str))
    {
        program.push_back(str);
    }

    // run until end of program
    int cycle = 1;
    int signalSum = 0;
    int cycleToCheck = 20;
    while(true) {
        //std::cout << "Cycle is: " << cycle << ", ip is " << comp.ip << ",  reg x is" << comp.x << std::endl;
        if (cycle == cycleToCheck) {
            signalSum += cycle * comp.x;
            cycleToCheck += 40;
        }
        comp.step(program);
        cycle++;
        if (comp.ip == program.size()) {
            break;
        }
    }
    std::cout<< "PartOne: " << signalSum << std::endl;

    // part two - draw to screen
    // comp.x is position of the middle of a 3 character sprite in the x axis - "###"
    comp.reset();

    std::vector<char> row(40, ' ');
    std::vector<std::vector<char>> screen(6, row);

    cycle = 1;
    while(true) {
        int x = (cycle - 1) % 40;
        int y = (cycle - 1) / 40;

        if (x == comp.x - 1 || x == comp.x || x == comp.x + 1) {
            screen[y][x] = '#';
        }

        comp.step(program);
        cycle++;
        if (comp.ip == program.size()) {
            break;
        }
    }

    for (auto& row : screen) {
        for (auto& c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}