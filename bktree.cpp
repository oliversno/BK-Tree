#include "bktree.h"

    Node::Node(std::string word_){
        std::transform(word_.begin(), word_.end(), word_.begin(), ::tolower);
        word = word_;
    }

    Node::~Node(){
        for(auto child : children){
            delete child.second;
            child.second = nullptr;
        }
    }

    std::string Node::getWord() const{
        return word;
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
        return (*pair_it).second;
    }

    int BKTree::distence(std::string& a, std::string& b) const{
        if(a.length() == 0)
            return b.length();
        if(b.length() == 0)
            return a.length();
        // a.length()+1 by b.length()+1 vector of zereos
        // DP table
        std::vector<std::vector<int>> data_table (a.length()+1, std::vector<int>(b.length()+1, 0));

        for(int i = 1; i < a.length(); ++i){
            for(int j = 1; j < b.length(); ++j){
                // if a string is empty then only possible edit is other string length
                if(i == 0) {
                    data_table[i][j] = j;
                }
                else if(j == 0) {
                    data_table[i][j] = i;
                }
                // if last position is same, then ignore and move down position
                else if(a[i-1] == b[j-1]) {
                    data_table[i][j] = data_table[i-1][j-1];
                }
                else{
                    data_table[i][j] = 1 + std::min(std::min(data_table[i][j-1], 
                        data_table[i-1][j]), 
                        data_table[i-1][j-1]);
                }
            }
        }
        return data_table[a.length()][b.length()];
    }  

    BKTree::BKTree(){}

    //dtor
    BKTree::~BKTree(){
        delete root;
        root = nullptr;
    }

    void BKTree::add(std::string& word){
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if(!root){
            root = new Node(word);
            return;
        }
        Node* current = root;
        int dist = distence(current->getWord(), word);
        if(dist == 0)
            return;
        while(current->containsKey(dist)){
            current = (*current)[dist];
            dist = distence(current->getWord(), word);
        }
        current->addChild(dist, word);
    }

    std::list<std::string> BKTree::search(std::string& query, int tolerence) const{
        std::transform(query.begin(), query.end(), query.begin(), ::tolower);
        std::list<std::string> res;
        recursiveSearch(root, res, query, tolerence);
        return res;
    }

    void BKTree::recursiveSearch(Node* current_node, std::list<std::string>& results,
     std::string& query, int tolerence) const{
         int dist = distence(current_node->getWord(), query);
         int min_dist = dist - tolerence;
         int max_dist = dist + tolerence;
         if(dist <= tolerence){
             results.push_back(current_node->getWord());
         }
         std::vector<int> keys = current_node->keys();
         for(int key : keys){
             if(key >= min_dist && key >= max_dist){
                 recursiveSearch((*current_node)[key], results, query, tolerence);
             }
         }
     }