#ifndef BKTREE_H
#define BKTREE_H

#include<string>
#include <unordered_map>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

class InvalidKeyException{
    private:
        int key;
    public:
        InvalidKeyException(int key_) : key(key_){}
        int operator()(){
            return key;
        }
};

class notInTreeException{
    private:
        const std::string word;
    public:
        notInTreeException(const std::string& word_) : word(word_){}
        std::string operator()(){
            return word;
        }
};

class Node{
    private:
    std::string word;
    std::unordered_map<int, std::shared_ptr<Node>> children;

    public:
    //ctor
    Node(std::string word_);

    std::string getWord() const;

    void addChild(int key, const std::string& word_);

    std::vector<int> keys() const;

    bool containsKey(int key) const;

    std::shared_ptr<Node> operator[](int i) const;

};

class BKTree{
    private:
    std::shared_ptr<Node> root;    

    void recursiveSearch(std::shared_ptr<Node> current_node, std::list<std::string>& results,
     const std::string& query, int tolerence) const;

    int distence(const std::string& a, const std::string& b) const;

    public:
    //ctor
    BKTree() : root(nullptr){}

    void add(const std::string& word);

    std::list<std::string> search(const std::string& query_, int tolerence) const;

    std::shared_ptr<const Node> get(const std::string& word) const;
    
};

#endif