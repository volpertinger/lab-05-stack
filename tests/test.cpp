// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#include <gtest/gtest.h>

#include <string>

#include "header.hpp"

TEST(Stack, empty) {
  Stack<int> stack;
  EXPECT_EQ(stack.empty(), true);

  stack.push(1);
  EXPECT_EQ(stack.empty(), false);
}

TEST(Stack, size) {
  Stack<int> stack;
  EXPECT_EQ(stack.size(), 0);

  stack.push(1);
  EXPECT_EQ(stack.size(), 1);

  stack.push(1);
  EXPECT_EQ(stack.size(), 2);

  stack.push(1);
  EXPECT_EQ(stack.size(), 3);

  stack.pop();
  EXPECT_EQ(stack.size(), 2);

  stack.pop();
  EXPECT_EQ(stack.size(), 1);

  stack.pop();
  EXPECT_EQ(stack.size(), 0);
}

TEST(Stack, push) {
  Stack<int> stack;
  EXPECT_EQ(stack.size(), 0);

  const int x = 100;  // for void push(const T& value);
  stack.push(x);
  EXPECT_EQ(stack.size(), 1);

  stack.push(-1);
  EXPECT_EQ(stack.size(), 2);

  stack.push(0);
  EXPECT_EQ(stack.size(), 3);
}

TEST(Stack, pop) {
  Stack<int> stack;
  stack.push(100);
  stack.push(-1);
  stack.push(0);

  EXPECT_EQ(stack.size(), 3);

  stack.pop();
  EXPECT_EQ(stack.size(), 2);

  stack.pop();
  EXPECT_EQ(stack.size(), 1);

  stack.pop();
  EXPECT_EQ(stack.size(), 0);
}

TEST(Stack, head) {
  Stack<int> stack;

  stack.push(10);
  EXPECT_EQ(stack.head(), 10);

  stack.push(100);
  EXPECT_EQ(stack.head(), 100);

  stack.pop();
  EXPECT_EQ(stack.head(), 10);
}

TEST(Stack, push_emplace) {
  Stack<std::string> stack;

  stack.push_emplace("0");
  EXPECT_EQ(stack.head(), "0");

  stack.push_emplace("1");
  EXPECT_EQ(stack.head(), "1");

  stack.push_emplace("2");
  EXPECT_EQ(stack.head(), "2");
}
