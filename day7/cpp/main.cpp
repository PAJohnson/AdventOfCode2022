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

// tree data structure to represent directories and contents
// use easy solutions, not good ones
struct File {
    std::string name;
    size_t size;
};

struct Tree;

struct Tree {
    Tree* parent;
    std::string name;
    std::vector<Tree> dirs;
    std::vector<File> files;
};

// recursive
void printTree(Tree& t, int indent) {
    std::cout << std::string(indent, ' ') << t.name << std::endl;
    for (auto dir : t.dirs) {
        printTree(dir, indent + 1);
    }
    for (auto f : t.files) {
        std::cout << std::string(indent+1, ' ') << "- " << f.name << " " << f.size << std::endl;
    }
}

unsigned long long calcSizes(Tree& t, std::unordered_map<std::string, unsigned long long>& sizes) {
    unsigned long long size = 0;
    // sum files
    for (auto f : t.files) {
        size += f.size;
    }
    // sum subdirs
    for (auto d : t.dirs) {
        size += calcSizes(d, sizes);
    }
    sizes[t.name] = size;
    //std::cout << size << std::endl;
    return size;
}

void printSizes(std::unordered_map<std::string, unsigned long long> sizes) {
    for (auto s : sizes) {
        std::cout << s.first << " " << s.second << std::endl;
    }
}

void partOne() {
    return;
}

void partTwo() {
    return;
}

int main() {
    std::ifstream file(INPUT);
    std::string str; 

    // part one - parse into trees
    // given terminal output of cd and ls commands
    // does part two has rm? or other commands?
    // Maybe 2022 AoC will be busybox implementation instead of assembly interpreter!

    // first - test if regex can be used to strip start of string

    // rethink and tackle tomorrow
    Tree root;
    Tree* current = &root;
    while (std::getline(file, str))
    {
        //std::cout << str << std::endl;
        if (str == "$ cd /") {
            current->name = "/";
        }
        else if (str == "$ ls") {
            //std::cout << "ls" << std::endl;
            // following lines contain dirs and files
            // make a new tree to insert into root
        }
        else if (str.find("$") == std::string::npos) {
            // in ls output
            if (str.find("dir") != std::string::npos) {
                auto dirname = split(str, " ")[1];
                //std::cout << "dir in line, inserting " << dirname << std::endl;
                current->dirs.push_back(Tree{current, dirname});
            }
            else {
                size_t size = stol(split(str, " ")[0]);
                std::string fname = split(str, " ")[1];
                //std::cout << "Inserting " << fname << std::endl;
                current->files.push_back(File{fname, size});
            }
        }
        else if (str.find("$ cd") != std::string::npos) {
            auto dirname = split(str, " cd ")[1];
            if (dirname == "..") {
                current = current->parent;
                //std::cout << "moving up a directory " << std::endl;
            }
            else {
                //std::cout << "moving down a directory " << std::endl;
                for (auto& d: current->dirs){
                    if (dirname == d.name) {
                        current = &d;
                    }
                }
            }
        }    
    }
    printTree(root, 1);
    std::unordered_map<std::string, unsigned long long> sizeMap;
    calcSizes(root, sizeMap);
    //printSizes(sizeMap);
    unsigned long long partOne = 0;
    for (auto s : sizeMap) {
        if (s.second <= 100000) {
            partOne += s.second;
            std::cout << partOne << std::endl;
        }
    }
    std::cout << partOne << std::endl;
}