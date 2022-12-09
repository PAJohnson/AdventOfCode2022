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

void partOne() {
    return;
}

void partTwo() {
    return;
}

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    // a grid problem!
    // but not an infinite grid
    std::vector<std::vector<int>> grid;
    while (std::getline(file, str))
    {
        std::vector<int> row;
        for (auto c : str) {
            row.push_back(static_cast<int>(c) - '0');
        }
        grid.push_back(row);
    }

    // part 1
    // count # of visible trees
    auto lookUp = [](auto& grid, auto row, auto col, auto& visSet) {
        int visible = 0;
        int max = -1;
        for (int i = row; i >= 0; i--) {
            if (grid[i][col] > max) {
                visible++;
                max = grid[i][col];
                visSet.insert({i, col});
            }
        }
        return visible;
    };
    auto lookDown = [](auto& grid, auto row, auto col, auto& visSet) {
        int visible = 0;
        int max = -1;
        for (int i = row; i < grid.size(); i++) {
            if (grid[i][col] > max) {
                visible++;
                max = grid[i][col];
                visSet.insert({i, col});
            }
        }
        return visible;
    };
    auto lookRight = [](auto& grid, auto row, auto col, auto& visSet) {
        int visible = 0;
        int max = -1;
        for (int i = col; i < grid[0].size(); i++) {
            if (grid[row][i] > max) {
                visible++;
                max = grid[row][i];
                visSet.insert({row, i});
            }
        }
        return visible;
    };
    auto lookLeft = [](auto& grid, auto row, auto col, auto& visSet) {
        int visible = 0;
        int max = -1;
        for (int i = col; i >= 0; i--) {
            if (grid[row][i] > max) {
                visible++;
                max = grid[row][i];
                visSet.insert({row, i});
            }
        }
        return visible;
    };

    int startRow = 0;
    int startCol = 0;
    int endRow = grid.size() - 1;
    int endCol = grid[0].size() - 1;
    std::set<std::pair<int,int>> visSet;

    for (int i = startRow; i <= endRow; i++) {
        lookRight(grid, i, startCol, visSet);
        lookLeft(grid, i, endCol, visSet);
    }
    for (int i = startCol; i <= endCol; i++) {
        lookUp(grid, endRow, i, visSet);
        lookDown(grid, startRow, i, visSet);
    }

    int partOne = visSet.size();
    std::cout << partOne << std::endl;

    // part two
    // calculate scenic scores for each tree
    // get max scenic score
    auto visibleUp = [](auto& grid, auto row, auto col) {
        int visible = 0;
        int max = grid[row][col];
        for (int i = row - 1; i >= 0; i--) {
            visible++;
            if (grid[i][col] >= max && i != row) {
                break;
            }
        }
        return visible;
    };
    auto visibleDown = [](auto& grid, auto row, auto col) {
        int visible = 0;
        int max = grid[row][col];
        for (int i = row + 1; i < grid.size(); i++) {
            visible++;
            if (grid[i][col] >= max && i != row) {
                break;
            }
        }
        return visible;
    };
    auto visibleRight = [](auto& grid, auto row, auto col) {
        int visible = 0;
        int max = grid[row][col];
        for (int i = col + 1; i < grid[0].size(); i++) {
            visible++;
            if (grid[row][i] >= max && i != col) {
                break;
            }
        }
        return visible;
    };
    auto visibleLeft = [](auto& grid, auto row, auto col) {
        int visible = 0;
        int max = grid[row][col];
        for (int i = col - 1; i >= 0; i--) {
            visible++;
            if (grid[row][i] >= max && i != col) {
                break;
            }
        }
        return visible;
    };

    int maxScore = -1;
    for (int i = 1; i < grid.size() - 1; i++) {
        for (int j = 1; j < grid[0].size() - 1; j++) {
            int tempScore = visibleUp(grid, i, j) * visibleDown(grid, i, j) * visibleLeft(grid, i, j) * visibleRight(grid, i, j);
            if (tempScore > maxScore) {
                maxScore = tempScore;
            }
        }
    }
    std::cout << maxScore << std::endl;
}