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

typedef std::vector<std::vector<char>> Crates;

struct Move {
    int from;
    int to;
    int amount;
};

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    // part 1
    // parse into crates container and move list
    Crates crates;
    std::vector<Move> moves;

    // sample looks like
    //     [D]    
    // [N] [C]    
    // [Z] [M] [P]
    //  1   2   3 
    //
    // move 1 from 2 to 1
    // move 3 from 1 to 3
    // move 2 from 2 to 1
    // move 1 from 1 to 2

    // break between crates section and moves - can use for parsing
    bool cratesEnd = false;
    int columns = 0;
    while (std::getline(file, str))
    {
        if (str.length() == 0) {
            cratesEnd = true;
        }

        // crate parsing
        // figure out # of crate columns
        if (!cratesEnd && columns == 0) {
            columns = (str.length() - 3) / 4 + 1;
            for (int i = 0; i < columns; i++) {
                crates.push_back({});
            }
        }
        
        if (!cratesEnd) {
            for (int i = 0; i < columns; i++) {
                char c = str[1+i*4];
                if (isalpha(c)) crates[i].push_back(str[1+i*4]);
            }
        }

        // parse moves
        if (cratesEnd && str.length() != 0) {
            int from;
            int to;
            int amount;
            std::sscanf(str.c_str(), "move %d from %d to %d", &amount, &from, &to);
            moves.push_back({from - 1, to - 1, amount});
        }
    }
    // flip all the columns around
    for (auto& column : crates) {
        std::reverse(column.begin(), column.end());
    }

    auto cratesTwo = crates;

    auto doMove9000 = [](Crates& crates, Move move) {
        for (int i = 0; i < move.amount; i++) {
            crates[move.to].push_back(crates[move.from].back());
            crates[move.from].pop_back();
        }   
    };

    auto doMove9001 = [](Crates& crates, Move move) {
        std::vector<char> subColumn;
        for (int i = 0; i < move.amount; i++) {
            subColumn.push_back(crates[move.from].back());
            crates[move.from].pop_back();
        }

        for (int i = 0; i < move.amount; i++) {
            crates[move.to].push_back(subColumn.back());
            subColumn.pop_back();
        }        
    };

    for (auto m : moves) {
        doMove9000(crates, m);
        doMove9001(cratesTwo, m);
    }

    for (auto c : crates) 
        std::cout << c.back();

    std::cout << '\n';

    for (auto c : cratesTwo) 
        std::cout << c.back();
}