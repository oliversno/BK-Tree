#include "bktree.h"
#include <iostream>

int main(){
    BKTree tree;
    tree.add("begin");
    std::shared_ptr<const Node> ptr = tree.get("begin");
    tree.add("");
    bool res = ptr->containsKey(5);
}