#ifndef BKTREE_H
#define BKTREE_H

#include<string>
#include <unordered_map>
#include <vector>
#include <list>
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

    std::vector<int>& keys() const;

    bool containsKey(int key) const;

    Node* &operator[](int i);

};

class BKTree{
    private:
    Node* root;

    void recursiveSearch(Node* current_node, std::list<std::string>& results,
     std::string& query, int tolerence) const;

    int distence(std::string& a, std::string& b) const;

    public:
    void add(std::string& word);

    std::list<std::string> search(std::string& query, int tolerence) const;
    
};

#endif