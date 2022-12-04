#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <regex>

enum Hand { rock = 1, paper, scissors };
typedef std::pair<Hand, Hand> Match;

// from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
// Neat!
std::vector<std::string> split(const std::string str, const std::string regex_str)
{
    std::regex regexz(regex_str);
    std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                  std::sregex_token_iterator());
    return list;
}

// given pair of hands in a match, calculate score gained
// first is opponent, second is player
// score is hand you played + 6 for win, 3 for draw, 0 for loss
int matchResult(const Match round) {
    int score;
    if ((round.first == Hand::rock && round.second == Hand::paper) ||
        (round.first == Hand::scissors && round.second == Hand::rock) ||
        (round.first == Hand::paper && round.second == Hand::scissors)) {
        score = 6;
    }
    else if (round.first == round.second) {
        score = 3;
    }
    else {
        score = 0;
    }

    return score + round.second;
}

void partOne(const std::vector<Match> rounds) {
    int totalScore = 0;
    for (auto round : rounds) {
        totalScore += matchResult(round);
    }
    std::cout << totalScore << '\n';
};

void partTwo(const std::vector<Match> rounds) {

};

int main() {
    // rock paper scissors
    // given a "strategy guide" (sequence of games), calculate a score
    std::vector<Match> roundsOne;
    std::vector<Match> roundsTwo;
    std::ifstream file("../inputs/sample.txt");
    std::string str; 

    while (std::getline(file, str))
    {
        // input is like this:
        // A Y
        // B X
        // C Z
        auto round = split(str, " ");
        
        Match m;
        if (round[0] == "A") {
            m.first = Hand::rock;
        } else if (round[0] == "B") {
            m.first = Hand::paper;
        } else if (round[0] == "C") {
            m.first = Hand::scissors;
        } else {
            std::cout << "Failed to parse hand, exiting";
            return 1;
        }

        if (round[1] == "X") {
            m.second = Hand::rock;
        } else if (round[1] == "Y") {
            m.second = Hand::paper;
        } else if (round[1] == "Z") {
            m.second = Hand::scissors;
        } else {
            std::cout << "Failed to parse hand, exiting";
            return 1;
        }

        roundsOne.push_back(m);

        // partTwo parsing is a little different
        // second part is a predetermined result, not a hand to be played
        auto lose = [](Hand h) {
            switch(h) {
                case Hand::rock:
                    return Hand::scissors;
                    break;
                case Hand::paper:
                    return Hand::rock;
                    break;
                case Hand::scissors:
                    return Hand::paper;
                    break;
                default:
                    break;
            }
        };
        auto tie = [](Hand h) {
            return h;
        };
        auto win = [](Hand h) {
            switch(h) {
                case Hand::rock:
                    return Hand::paper;
                    break;
                case Hand::paper:
                    return Hand::scissors;
                    break;
                case Hand::scissors:
                    return Hand::rock;
                    break;
                default:
                    break;
            }
        };

        Match mTwo;
        if (round[0] == "A") {
            mTwo.first = Hand::rock;
        } else if (round[0] == "B") {
            mTwo.first = Hand::paper;
        } else if (round[0] == "C") {
            mTwo.first = Hand::scissors;
        } else {
            std::cout << "Failed to parse hand, exiting";
            return 1;
        }

        if (round[1] == "X") {
            mTwo.second = lose(mTwo.first);
        } else if (round[1] == "Y") {
            mTwo.second = tie(mTwo.first);
        } else if (round[1] == "Z") {
            mTwo.second = win(mTwo.first);
        } else {
            std::cout << "Failed to parse hand, exiting";
            return 1;
        }

        roundsTwo.push_back(mTwo);

    }

    partOne(roundsOne);
    partOne(roundsTwo);
}