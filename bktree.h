#ifndef BKTREE_H
#define BKTREE_H

#include<string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Node{
    private:
    std::string word;
    std::unordered_map<int, Node*> children;

    public:
    //ctor
    Node(std::string word_);

    //dtor
    ~Node();

    void addChild(int key, std::string& word);

    std::vector<int> keys() const;

    bool containsKey(int key) const;

    Node &operator[](int i);

};

#endif