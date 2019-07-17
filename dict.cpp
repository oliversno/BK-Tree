#include "dict.h"

void Dictionary::add(const std::string& new_word) {
        if(!dict.insert(new_word).second){
            throw InsertFailed();
    }
}

bool Dictionary::contains(const std::string& query) const {
    return dict.find(query) != dict.end();
}