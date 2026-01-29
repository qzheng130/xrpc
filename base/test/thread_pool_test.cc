#include <gtest/gtest.h>
#include <iostream>

// 简单测试
TEST(SimpleTest, BasicAssertions) {
    EXPECT_EQ(2 + 2, 4);
    EXPECT_NE(2 + 2, 5);
    EXPECT_TRUE(2 + 2 == 4);
    EXPECT_FALSE(2 + 2 == 5);
}

// 测试套件
class MathTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 测试前的设置
    }
    
    void TearDown() override {
        // 测试后的清理
    }
};

TEST_F(MathTest, Addition) {
    EXPECT_EQ(1 + 1, 2);
    EXPECT_EQ(10 + 20, 30);
}

// 主函数（如果链接了gtest_main则不需要）
#ifndef LINK_GTEST_MAIN
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
