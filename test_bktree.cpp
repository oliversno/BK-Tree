#include "bktree.cpp"
#include <gtest/gtest.h>

TEST(NodeTest, InitNode){
    Node n("test");
    EXPECT_EQ(n.getWord(), "test");
}

TEST(NodeTest, LowercaseNode){
    Node n ("CAPS");
    EXPECT_EQ(n.getWord(), "caps");
}

TEST(NodeTest, AddChildNode){
    Node n("test");
    n.addChild(7, "testing");
    EXPECT_TRUE(n.containsKey(7));
}

TEST(NodeTest, KeysNode){
    Node n("test");
    n.addChild(1, "rest");
    n.addChild(7, "quailed");
    n.addChild(2, "resp");
    n.addChild(4, "quip");
    std::vector<int> vec = n.keys();
    std::sort(vec.begin(), vec.end());
    std::vector<int> res{1,2,4,7};
    EXPECT_EQ(vec, res);
}

TEST(NodeTest, ContainsKeyNode){
    Node n("test");
    n.addChild(3, "key");
    EXPECT_TRUE(n.containsKey(3));
}

TEST(NodeTest, DoesntContainsKeyNode){
    Node n("test");
    EXPECT_FALSE(n.containsKey(3));
}

TEST(NodeTest, IndexNode){
    Node n("test");
    n.addChild(1, "rest");
    EXPECT_TRUE(n.containsKey(1));
    EXPECT_EQ(n[1]->getWord, "rest");
}

TEST(NodeTest, IndexFailNode){
    Node n("test");
    EXPECT_THROW(n[5], InvalidKeyException);
}