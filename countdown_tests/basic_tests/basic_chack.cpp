#include <gtest/gtest.h>
#include <tuple>
#include "../../countdown/countdown.cpp"


TEST(basic_check, test_eq) {
    EXPECT_EQ(1, 1);
}

TEST(PostfixEvaluatorTest, value_sum) {
    std::vector<int> expression = {2, 3, -1};
    EXPECT_EQ(evaluate_postfix(expression).first, 5);
}

TEST(PostfixEvaluatorTest, value_difference) {
    std::vector<int> expression = {15, 3, -2};
    EXPECT_EQ(evaluate_postfix(expression).first, 12);
}

TEST(PostfixEvaluatorTest, value_multiplication) {
    std::vector<int> expression = {6, 3, -3};
    EXPECT_EQ(evaluate_postfix(expression).first, 18);
}

TEST(PostfixEvaluatorTest, value_division) {
    std::vector<int> expression = {6, 3, -4};
    EXPECT_EQ(evaluate_postfix(expression).first, 2);
}


TEST(PostfixEvaluatorTest, value_ignore) {
    std::vector<int> expression = {6, 5, -5};
    EXPECT_EQ(evaluate_postfix(expression).first, 6);
}

TEST(PostfixEvaluatorTest, value_random_1) {
    std::vector<int> expression = {2, 6, 3, -4, -1};
    EXPECT_EQ(evaluate_postfix(expression).first, 4);
}

TEST(PostfixEvaluatorTest, value_random_2) {
    std::vector<int> expression = {2, 6, 3, -4, -1, 12, -1};
    EXPECT_EQ(evaluate_postfix(expression).first, 16);
}