#include "bktree.h"
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
    EXPECT_EQ(n[1]->getWord(), "rest");
}

TEST(NodeTest, IndexFailNode){
    Node n("test");
    EXPECT_THROW(n[5], InvalidKeyException);
}

TEST(BKTest, InitBK){
    BKTree tree;
    SUCCEED();
}

TEST(BKTest, DistEmptyBK){
    BKTree tree;
    tree.add("begin");
    std::shared_ptr<const Node> ptr = tree.get("begin");
    tree.add("");
    EXPECT_TRUE(ptr->containsKey(5));
}

TEST(BKTest, DistEmptyBK2){
    BKTree tree;
    tree.add("");
    std::shared_ptr<const Node> ptr = tree.get("");
    tree.add("addition");
    EXPECT_TRUE(ptr->containsKey(8));
}

TEST(BKTest, DistEqualBK){
    BKTree tree;
    tree.add("equal");
    std::shared_ptr<const Node> ptr = tree.get("equal");
    tree.add("equal");
    std::vector<int> vec = ptr->keys();
    EXPECT_TRUE(vec.empty());
}

TEST(BKTest, DistAddBK){
    BKTree tree;
    tree.add("sittin");
    std::shared_ptr<const Node> ptr = tree.get("sittin");
    tree.add("sitting");
    EXPECT_TRUE(ptr->containsKey(1));
}

TEST(BKTest, DistDeleteBK){
    BKTree tree;
    tree.add("sitting");
    std::shared_ptr<const Node> ptr = tree.get("sitting");
    tree.add("sittin");
    EXPECT_TRUE(ptr->containsKey(1));
}

TEST(BKTest, DistSubBK){
    BKTree tree;
    tree.add("run");
    std::shared_ptr<const Node> ptr = tree.get("run");
    tree.add("ran");
    EXPECT_TRUE(ptr->containsKey(1));
}

TEST(BKTest, DistComplexBK){
    BKTree tree;
    tree.add("kitten");
    std::shared_ptr<const Node> ptr = tree.get("kitten");
    tree.add("sitting");
    EXPECT_TRUE(ptr->containsKey(3));
}

TEST(BKTest, AddEmptyBK){
    BKTree tree;
    tree.add("this");
    const std::list<std::string> list = tree.search("this",0);
    std::list<std::string>res{1,"this"};
    EXPECT_EQ(list, res);
}

TEST(BKTest, AddMultipleLayersBK){
    BKTree tree;
    tree.add("start");
    std::shared_ptr<const Node> ptr = tree.get("start");
    tree.add("stars");
    std::shared_ptr<Node> next = (*ptr)[1];
    tree.add("tart");
    EXPECT_TRUE(next->containsKey(2));
}

TEST(BKTest, SearchBK){
    BKTree tree;
    tree.add("hell");
    tree.add("help");
    tree.add("shel");
    tree.add("smell");
    tree.add("fell");
    tree.add("felt");
    tree.add("oops");
    tree.add("pop");
    tree.add("oouch");
    tree.add("halt");
    std::list<std::string>list = tree.search("helt", 2);
    std::vector<std::string>vec{"hell","help","fell","shel","felt","halt"};
    std::list<std::string>res{vec.begin(),vec.end()};
    EXPECT_EQ(list,res);
}

TEST(BKTest, notInTreeExceptionBK){
    BKTree tree;
    EXPECT_THROW(tree.get("test"), notInTreeException);
}

TEST(BKTest, getBK){
    BKTree tree;
    tree.add("help");
    tree.add("shel");
    tree.add("smell");
    tree.add("fell");
    tree.add("felt");
    tree.add("oops");
    tree.add("pop");
    tree.add("oouch");
    tree.add("halt");
    auto ptr = tree.get("oops");
    EXPECT_EQ(ptr->getWord(), "oops");
}