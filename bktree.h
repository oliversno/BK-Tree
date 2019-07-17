#ifndef BKTREE_H
#define BKTREE_H

#include<string>
#include <unordered_map>
#include <vector>
#include <list>
#include <algorithm>

class InvalidKeyException{
    private:
        int key;
    public:
        InvalidKeyException(int key_) : key(key_){}
        int operator()(){
            return key;
        }
};

class Node{
    private:
    std::string word;
    std::unordered_map<int, Node*> children;

    public:
    //ctor
    Node(std::string word_);

    //dtor
    ~Node();

    const std::string getWord() const;

    void addChild(int key, const std::string& word_);

    const std::vector<int> keys() const;

    const bool containsKey(int key) const;

    Node* &operator[](int i);

};

class BKTree{
    private:
    Node* root;    

    void recursiveSearch(Node* current_node, std::list<std::string>& results,
     const std::string& query, int tolerence) const;

    int distence(const std::string& a, const std::string& b) const;

    public:
    //ctor
    BKTree() : root(nullptr){}
    BKTree(Node* ptr) : root(ptr){}

    //dtor
    ~BKTree();

    void add(const std::string& word);

    const std::list<std::string> search(const std::string& query_, int tolerence) const;
    
};

#endif