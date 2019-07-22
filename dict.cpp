#include "dict.h"
#include <algorithm>

void Dictionary::add(const std::string& new_word) {
    std::string word = new_word;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);  
    if(!dict.insert(word).second){
        throw InsertFailed();
    }
}

bool Dictionary::contains(const std::string& query) const {
    return dict.find(query) != dict.end();
}