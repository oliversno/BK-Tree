#ifndef DICT_H
#define DICT_H

#include <unordered_set>
#include <string>

class Dictionary{
    private:
    std::unordered_set<std::string> dict;

    public:
    // adds new_word to the dictionary
    // throws a InsertFailed Exception if the value can not be added
    void add(const std::string& new_word);

    // returns true if query is in thhe dictionary, false otherwise
    bool contains(const std::string& query) const;
};

#endif