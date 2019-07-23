#include "dict.h"
#include <algorithm>

void Dictionary::add(const std::string& word) { 
    if(!dict.insert(word).second){
        throw InsertFailed();
    }
}

bool Dictionary::contains(const std::string& query) const {
    return dict.find(query) != dict.end();
}