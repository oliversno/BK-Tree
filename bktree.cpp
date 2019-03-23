#include "bktree.h"
#include "dict.h"

    Node::Node(std::string word_){
        std::transform(word_.begin(), word_.end(), word_.begin(), ::tolower);
        word = word_;
    }

    Node::~Node(){
        for(auto child : children){
            child.second->~Node();
            child.second = nullptr;
        }
    }

    void Node::addChild(int key, std::string& word){
        children[key] = new Node(word);
    }

    std::vector<int>& Node::keys() const{
        std::vector<int> keys;
        keys.reserve(children.size());
        for(auto child : children){
            keys.push_back(child.first);
        }
        return keys;
    }

    bool Node::containsKey(int key) const{
        return children.find(key) != children.end();
    }

    Node* &Node::operator[](int i){
        if(i > children.size()){
            throw OutOfSizeException();
        }
        auto pair_it = children.find(i);
        if(pair_it == children.end()){
            throw InvalidKeyException();
        }
        return *pair_it.second;
    }