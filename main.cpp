#include "bktree.h"
#include <iostream>
#include <fstream>

const int kTolerence = 2;

int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "Incorrect number of arguments\n";
        return 1;
    }
    std::ifstream is{argv[1]};
    if(!is.is_open()){
        std::cerr << "File could not be opened\n";
        return 1;
    }
    BKTree tree;
    std::string input;
    while(is >> input){
        tree.add(input);
    }
    std::cout << "Please Input Text\n";
    while(std::cin >> input){
        if(input == "EXIT"){
            return 0;
        }
        std::list<std::string> possible_words = tree.search(input, kTolerence);
        if(std::find(possible_words.begin(), possible_words.end(),
             input) == possible_words.end()){
                 std::cout << input << " is not spelled correctly\n" <<
                    "Possible correct spellings:\n";
                for(std::string& alternative : possible_words){
                    std::cout << alternative << '\n';
                }
                std::cout << '\n';
        }
    }
}