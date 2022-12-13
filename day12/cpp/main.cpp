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
std::set<std::pair<int,int>> visited;
struct Point {
    Point(int x_, int y_, int size_) : x(x_), y(y_), size(size_) {};
    std::set<std::pair<int,int>> visited;
    int x = 0;
    int y = 0;
    int size = 0;
    bool operator<(Point const &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

bool cycleCheck(Point& current, int x, int y) {
    if (visited.find(std::make_pair(x,y)) != visited.end()) {
        return true;
    }
    return false;
}

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    std::vector<std::string> grid;

    Point start{0, 0, 0};
    int row = 0;
    int col = 0;

    while (std::getline(file, str))
    {
        // parse into a grid of points
        // bleh, this is a search space problem
        // do this tomorrow to learn about how this works
        if (grid.size() == 0) {
            for (auto& c : str) {
                grid.push_back({});
            }
        }
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == 'S') {
                start = {i, row, 0};
                grid[i].push_back('a' - 1);
            }
            else if (str[i] == 'E') {
                grid[i].push_back('{');
            }
            else {
                grid[i].push_back(str[i]);
            }
        }
        row++;
    }

    // maintain a list of candidates
    // iterate over candidates until candidate list is empty, indicating all paths are terminated
    std::vector<Point> goodPaths;

    bool allTerminated = false;
    int loopCount = 0;
    std::set<Point> candidates{start};
    while (!allTerminated) {
        std::set<Point> newCandidates;
        //std::cout << candidates.size() << std::endl;
        //std::cout << visited.size() << std::endl;
        //std::cout << "candidates are: ";
        // for (auto point : candidates) {
        //     std::cout << "(" << point.x << ", " << point.y << ") ";
        // }
        //std::cout << std::endl;
        for (auto point : candidates) {
            // up
            if (point.y - 1 >= 0 && // bounds check
                (grid[point.x][point.y-1] == grid[point.x][point.y] + 1  || // at most 1 greater
                grid[point.x][point.y-1] <= grid[point.x][point.y]) && // end condition
                !(cycleCheck(point, point.x, point.y - 1))) // dont backtrack
            {
                Point newPoint = point;
                newPoint.size += 1;
                visited.emplace(std::make_pair(newPoint.x, newPoint.y));
                newPoint.y -= 1;
                newCandidates.insert(newPoint);
                if (grid[newPoint.x][newPoint.y] == '{') {
                    goodPaths.push_back(newPoint);
                }
                //std::cout << "Moving Up to " << newPoint.x << " " << newPoint.y << std::endl;
            }
            // down
            if (point.y + 1 < grid[0].size() && // bounds check
                (grid[point.x][point.y + 1] == grid[point.x][point.y] + 1  || // at most 1 greater
                grid[point.x][point.y + 1] <= grid[point.x][point.y]) && // end condition
                !(cycleCheck(point, point.x, point.y + 1))) // dont backtrack
            {
                Point newPoint = point;
                newPoint.size += 1;
                visited.emplace(std::make_pair(newPoint.x, newPoint.y));
                newPoint.y += 1;
                newCandidates.insert(newPoint);
                if (grid[newPoint.x][newPoint.y] == '{') {
                    goodPaths.push_back(newPoint);
                }
                //std::cout << "Moving Down to " << newPoint.x << " " << newPoint.y << std::endl;
            }
            // left
            if (point.x - 1 >= 0 && // bounds check
                (grid[point.x - 1][point.y] == grid[point.x][point.y] + 1  || // at most 1 greater
                grid[point.x - 1][point.y] <= grid[point.x][point.y]) && // end condition
                !(cycleCheck(point, point.x - 1, point.y))) // dont backtrack
            {
                Point newPoint = point;
                newPoint.size += 1;
                visited.emplace(std::make_pair(newPoint.x, newPoint.y));
                newPoint.x -= 1;
                newCandidates.insert(newPoint);
                if (grid[newPoint.x][newPoint.y] == '{') {
                    goodPaths.push_back(newPoint);
                }
                //std::cout << "Moving Left to " << newPoint.x << " " << newPoint.y << std::endl;
            }
            // right
            if (point.x + 1 < grid.size() && // bounds check
                (grid[point.x + 1][point.y] == grid[point.x][point.y] + 1  || // at most 1 greater
                grid[point.x + 1][point.y] <= grid[point.x][point.y]) && // end condition
                !(cycleCheck(point, point.x + 1, point.y))) // dont backtrack
            {
                Point newPoint = point;
                newPoint.size += 1;
                visited.emplace(std::make_pair(newPoint.x, newPoint.y));
                newPoint.x += 1;
                newCandidates.insert(newPoint);
                if (grid[newPoint.x][newPoint.y] == '{') {
                    goodPaths.push_back(newPoint);
                }
                //std::cout << "Moving Right to " << newPoint.x << " " << newPoint.y << std::endl;
            }
        }
        //std::cout << "*********************** " << loopCount << std::endl;
        loopCount++;
        if (newCandidates.size() == 0) {
            allTerminated = true;
        }
        else {
            candidates = newCandidates;
        }
    }

    std::vector<int> pathLengths;
    for (auto point : goodPaths) {
        pathLengths.push_back(point.size);
    }

    std::sort(pathLengths.begin(), pathLengths.end());
    std::cout << pathLengths[0] << std::endl;

    // part two
    // same, but starting from any square marked "a"
    // maintain a list of candidates
    // iterate over candidates until candidate list is empty, indicating all paths are terminated

    allTerminated = false;
    loopCount = 0;
    visited.clear();
    candidates.clear();
    candidates.insert(start);
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[0].size(); y++) {
            if (grid[x][y] == 'a') {
                candidates.insert(Point(x,y,0));
            }
        }
    }
    while (!allTerminated) {
        std::set<Point> newCandidates;
        // std::cout << candidates.size() << std::endl;
        // std::cout << visited.size() << std::endl;
        // std::cout << "candidates are: ";
        // for (auto point : candidates) {
        //     std::cout << "(" << point.x << ", " << point.y << ") ";
        // }
        //std::cout << std::endl;
        for (auto point : candidates) {
            // up
            if (point.y - 1 >= 0 && // bounds check
                (grid[point.x][point.y-1] == grid[point.x][point.y] + 1  || // at most 1 greater
                grid[point.x][point.y-1] <= grid[point.x][point.y]) && // end condition
                !(cycleCheck(point, point.x, point.y - 1))) // dont backtrack
            {
                Point newPoint = point;
                newPoint.size += 1;
                visited.emplace(std::make_pair(newPoint.x, newPoint.y));
                newPoint.y -= 1;
                newCandidates.insert(newPoint);
                if (grid[newPoint.x][newPoint.y] == '{') {
                    goodPaths.push_back(newPoint);
                }
                //std::cout << "Moving Up to " << newPoint.x << " " << newPoint.y << std::endl;
            }
            // down
            if (point.y + 1 < grid[0].size() && // bounds check
                (grid[point.x][point.y + 1] == grid[point.x][point.y] + 1  || // at most 1 greater
                grid[point.x][point.y + 1] <= grid[point.x][point.y]) && // end condition
                !(cycleCheck(point, point.x, point.y + 1))) // dont backtrack
            {
                Point newPoint = point;
                newPoint.size += 1;
                visited.emplace(std::make_pair(newPoint.x, newPoint.y));
                newPoint.y += 1;
                newCandidates.insert(newPoint);
                if (grid[newPoint.x][newPoint.y] == '{') {
                    goodPaths.push_back(newPoint);
                }
                //std::cout << "Moving Down to " << newPoint.x << " " << newPoint.y << std::endl;
            }
            // left
            if (point.x - 1 >= 0 && // bounds check
                (grid[point.x - 1][point.y] == grid[point.x][point.y] + 1  || // at most 1 greater
                grid[point.x - 1][point.y] <= grid[point.x][point.y]) && // end condition
                !(cycleCheck(point, point.x - 1, point.y))) // dont backtrack
            {
                Point newPoint = point;
                newPoint.size += 1;
                visited.emplace(std::make_pair(newPoint.x, newPoint.y));
                newPoint.x -= 1;
                newCandidates.insert(newPoint);
                if (grid[newPoint.x][newPoint.y] == '{') {
                    goodPaths.push_back(newPoint);
                }
                //std::cout << "Moving Left to " << newPoint.x << " " << newPoint.y << std::endl;
            }
            // right
            if (point.x + 1 < grid.size() && // bounds check
                (grid[point.x + 1][point.y] == grid[point.x][point.y] + 1  || // at most 1 greater
                grid[point.x + 1][point.y] <= grid[point.x][point.y]) && // end condition
                !(cycleCheck(point, point.x + 1, point.y))) // dont backtrack
            {
                Point newPoint = point;
                newPoint.size += 1;
                visited.emplace(std::make_pair(newPoint.x, newPoint.y));
                newPoint.x += 1;
                newCandidates.insert(newPoint);
                if (grid[newPoint.x][newPoint.y] == '{') {
                    goodPaths.push_back(newPoint);
                }
                //std::cout << "Moving Right to " << newPoint.x << " " << newPoint.y << std::endl;
            }
        }
        //std::cout << "*********************** " << loopCount << std::endl;
        loopCount++;
        if (newCandidates.size() == 0) {
            allTerminated = true;
        }
        else {
            candidates = newCandidates;
        }
    }

    pathLengths.clear();
    for (auto point : goodPaths) {
        pathLengths.push_back(point.size);
    }

    std::sort(pathLengths.begin(), pathLengths.end());
    std::cout << pathLengths[0] << std::endl;
}