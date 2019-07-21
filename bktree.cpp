#include "bktree.h"
#include <queue>

Node::Node(std::string word_){
    word = word_;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
}

std::string Node::getWord() const{
    return word;
}

void Node::addChild(int key, const std::string& word){
    children[key] = std::shared_ptr<Node>{new Node(word)};
}

std::vector<int> Node::keys() const{
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

std::shared_ptr<Node> Node::operator[](int i) const{
    auto pair_it = children.find(i);
    if(pair_it == children.end()){
        throw InvalidKeyException(i);
    }
    return pair_it->second;
}

int BKTree::distence(const std::string& a, const std::string& b) const{
    if(a.length() == 0)
        return (int)b.length();
    if(b.length() == 0)
        return (int)a.length();
    // a.length()+1 by b.length()+1 vector of zereos
    // DP table
    std::vector<std::vector<int>> data_table (a.length()+1, std::vector<int>(b.length()+1, 0));

    for(unsigned int i = 0; i <= a.length(); ++i){
        for(unsigned int j = 0; j <= b.length(); ++j){
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

void BKTree::add(const std::string& word_){
    std::string word = word_;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    if(!root){
        root = std::shared_ptr<Node>{new Node(word)};
        return;
    }
    std::shared_ptr<Node> current = root;
    int dist = distence(current->getWord(), word);
    if(dist == 0)
        return;
    while(current->containsKey(dist)){
        current = (*current)[dist];
        dist = distence(current->getWord(), word);
    }
    current->addChild(dist, word);
}

std::list<std::string> BKTree::search(const std::string& query_, int tolerence) const{
    std::string query = query_;
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);
    std::list<std::string> res;
    recursiveSearch(root, res, query, tolerence);
    return res;
}

void BKTree::recursiveSearch(std::shared_ptr<Node> current_node, std::list<std::string>& results,
    const std::string& query, int tolerence) const{
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

std::shared_ptr<const Node> BKTree::get(const std::string& word) const{
    auto list = search(word, 0);
    if(std::find(list.begin(), list.end(), word) == list.end())
        throw notInTreeException(word);
    std::queue<std::shared_ptr<const Node>> q;
    q.push(root);
    while(q.front()->getWord() != word){
        std::vector<int> keys = q.front()->keys();
        for(int key : keys){
            q.push((*q.front())[key]);
        }
        q.pop();
    }
    return q.front();
}