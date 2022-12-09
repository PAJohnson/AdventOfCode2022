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

enum Direction {
    kUp,
    kDown,
    kLeft,
    kRight
};

using Point = std::pair<int, int>;
using Grid = std::set<Point>;
using Move = std::pair<enum Direction, int>; // direction and distance
std::vector<Move> moves;

void printMoves(std::vector<Move>& moves) {
    for (auto& [dir, dist]  : moves) {
        std::cout << dir << " " << dist << std::endl;
    }
}

void printGrid(Grid& g) {
    for (auto& p : g) {
        std::cout << "(" << p.first << "," << p.second << ")\n";
    }
}

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    // part one - infinite grid problem
    // have a "rope" with a head and tail. tail always 1 away (or overlapping) from head
    // infinite grid problem
    // Q: how many positions does the tail visit at least once?

    // sample input looks like this
    // R 4
    // U 4
    // L 3
    // D 1
    // R 4
    // D 1
    // L 5
    // R 2

    // grid visualization should look like this:
    // ..##..
    // ...##.
    // .####.
    // ....#.
    // s###..

    while (std::getline(file, str))
    {
        auto toks = split(str, " ");
        auto dir = toks[0];
        auto dist = std::stoi(toks[1]);

        if (dir == "R") {
            moves.push_back(std::make_pair(Direction::kRight, dist));
        }
        else if (dir == "L") {
            moves.push_back(std::make_pair(Direction::kLeft, dist));
        }
        else if (dir == "U") {
            moves.push_back(std::make_pair(Direction::kUp, dist));
        }
        else if (dir == "D") {
            moves.push_back(std::make_pair(Direction::kDown, dist));
        }
    }

    // part one
    Point head{0, 0};
    Point tail{0, 0};
    Grid grid;

    auto doMove = [](Move& m, Grid& g, Point& h, Point& t) {
        // move the h and see where the t goes
        // mark locations in grid that the t went as True
        for (int i = 0; i < m.second; i++) {
            if (m.first == Direction::kUp) {
                // t could be 9 possible places
                // same place
                // moving up, which cases will cause a move?
                // same place - no move
                // left - no move
                // right - no move
                // above - no move
                // upleft - no move
                // up right - no move
                // downleft - t move up move right
                // below - t move up
                // downright - t move up move left
                if (t.second == h.second - 1) {
                    if (t.first == h.first - 1) {
                        t.first += 1;
                    }
                    else if (t.first == h.first + 1) {
                        t.first -= 1;
                    }
                    t.second += 1;
                }
                h.second += 1;
            }
            else if (m.first == Direction::kLeft) {
                if (t.first == h.first + 1) {
                    if (t.second == h.second - 1) {
                        t.second += 1;
                    }
                    else if (t.second == h.second + 1) {
                        t.second -= 1;
                    }
                    t.first -= 1;
                }
                h.first -= 1;
            }
            else if (m.first == Direction::kRight) {
                if (t.first == h.first - 1) {
                    if (t.second == h.second - 1) {
                        t.second += 1;
                    }
                    else if (t.second == h.second + 1) {
                        t.second -= 1;
                    }
                    t.first += 1;
                }
                h.first += 1;
            }
            else if (m.first == Direction::kDown) {
                if (t.second == h.second + 1) {
                    if (t.first == h.first - 1) {
                        t.first += 1;
                    }
                    else if (t.first == h.first + 1) {
                        t.first -= 1;
                    }
                    t.second -= 1;
                }
                h.second -= 1;
            } 
            g.insert(t);
        }
    };

    for (auto& m : moves) {
        doMove(m, grid, head, tail);
    }

    std::cout << grid.size() << std::endl;
}