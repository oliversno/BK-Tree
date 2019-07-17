#include "dict.cpp"
#include <gtest/gtest.h>

TEST(ApplyTest, InitDict){
    Dictionary dict;
    SUCCEED();
}

TEST(ApplyTest, AddDict){
    Dictionary dict;
    dict.add("testing");
    EXPECT_TRUE(dict.contains("testing"));
}

TEST(ApplyTest, AddDict2){
    Dictionary dict;
    dict.add("TESTING");
    EXPECT_FALSE(dict.contains("TESTING"));
}

TEST(ApplyTest, DuplicateDict){
    Dictionary dict;
    dict.add("double");
    EXPECT_TRUE(dict.contains("double"));
    EXPECT_THROW(dict.add("double"), InsertFailed);
}

TEST(ApplyTest, ContainsDict){
    Dictionary dict;
    dict.add("contains");
    EXPECT_TRUE(dict.contains("contains"));
}

TEST(ApplyTest, DoesntContainDict){
    Dictionary dict;
    EXPECT_FALSE(dict.contains("false"));
}