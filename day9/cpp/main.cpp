#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <unordered_set>
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

enum Direction {
    kUp,
    kDown,
    kLeft,
    kRight
};

struct Point {
    Point() {
        x = 0;
        y = 0;
    }
    Point(int x_, int y_) {
        x = x_;
        y = y_;
    }

    Point operator+ (Point& rhs) {
        Point res;
        res.x = x + rhs.x;
        res.y = y + rhs.y;
        return res;
    }

    Point operator- (Point& rhs) {
        Point res;
        res.x = x - rhs.x;
        res.y = y - rhs.y;
        return res;
    }

    void move(enum Direction d) {
        if (d == Direction::kUp) {
            y += 1;
        }
        else if (d == Direction::kDown) {
            y -= 1;
        }
        else if (d == Direction::kLeft) {
            x -= 1;
        }
        else if (d == Direction::kRight) {
            x += 1;
        }
    }

    int x;
    int y;
};

bool operator== (Point const& lhs, Point const& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

struct PointHash {
    size_t operator()(const Point& p) const{
        return static_cast<size_t>(std::abs(p.x * p.y));
    }
};

using Grid = std::unordered_set<Point, PointHash>;
using Move = std::pair<enum Direction, int>; // direction and distance
std::vector<Move> moves;

void printMoves(std::vector<Move>& moves) {
    for (auto& [dir, dist]  : moves) {
        std::cout << dir << " " << dist << std::endl;
    }
}

// make this similar to the examples on the page
void printGrid(Grid& g, int xStart, int xEnd, int yStart, int yEnd) {
    std::vector<char> row(xEnd - xStart, '.');
    std::vector<std::vector<char>> dispGrid(yEnd - yStart, row);

    int xOffset = xStart;
    int yOffset = yStart;

    for (auto& point : g) {
        if (point.x < xEnd && point.y < yEnd && point.x >= xStart && point.y >= yStart){
            dispGrid[point.y - yOffset][point.x - xOffset] = '#';
        }
    }

    for (int i = dispGrid.size() - 1; i >= 0; i--) {
        for (auto& c : dispGrid[i]) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

void printRope(std::vector<Point> const& points, int xStart, int xEnd, int yStart, int yEnd) {
    std::vector<char> row(xEnd - xStart, '.');
    std::vector<std::vector<char>> dispGrid(yEnd - yStart, row);

    int xOffset = xStart;
    int yOffset = yStart;

    for (int i = 0; i < points.size(); i++) {
        auto point = points[i];
        if (point.x < xEnd && point.y < yEnd && point.x >= xStart && point.y >= yStart){
            dispGrid[point.y - yOffset][point.x - xOffset] = '0' + points.size() - i - 1;
        }
    }

    for (int i = dispGrid.size() - 1; i >= 0; i--) {
        for (auto& c : dispGrid[i]) {
            std::cout << c;
        }
        std::cout << std::endl;
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
    std::vector<Point> points(2, Point{0, 0});
    Grid grid;

    // part two change - refactor doMove to accept list of points
    // run doMove on pairs of points, pick one to keep track of

    // refactor this to move "head" first and then figure out where the
    // tail is supposed to go
    auto doMove = [](Move& m, Grid& g, std::vector<Point>& points, int tracked) {
        // move the h and see where the t goes
        // mark locations in grid that the t went as True
        for (int i = 0; i < m.second; i++) {
            auto head = points[0];
            head.move(m.first);
            points[0] = head;
            for (int i = 0; i < points.size() - 1; i++) {
                auto& tempHead = points[i];
                auto& tempNext = points[i+1];
                auto diff = tempHead - tempNext;
                // need to handle diagonal moves for part 2
                if (std::abs(diff.x) > 1 || std::abs(diff.y) > 1) {
                    if (diff.y > 0) {
                        tempNext.y += 1;
                    }
                    if (diff.y < 0) {
                        tempNext.y -= 1;
                    }
                    if (diff.x > 0) {
                        tempNext.x += 1;
                    }
                    if (diff.x < 0) {
                        tempNext.x -= 1;
                    }
                }
            }
            g.insert(points[tracked]);
        }
    };

    for (auto& m : moves) {
        doMove(m, grid, points, 1);
    }

    std::cout << grid.size() << std::endl;

    // part two
    // same thing, but with a rope of 10 knots

    // part one
    std::vector<Point> pointsTwo(10, Point());
    Grid gridTwo;

    for (auto& m : moves) {
        doMove(m, gridTwo, pointsTwo, 9);
    }

    std::cout << gridTwo.size() << std::endl;
}