// Unittests using Google C++ testing framework.
//
// Author: Alyssa Quek

#include <vector>

#include "gtest/gtest.h" // Google testing framework.
#include "heap.h"

using namespace std;

TEST(Heap, isEmpty) { 
  Heap heap;
  EXPECT_TRUE(heap.isEmpty());
  EXPECT_EQ("", heap.toString());
  heap.insert(1);
  EXPECT_FALSE(heap.isEmpty());
  EXPECT_EQ("1", heap.toString());
}

TEST(Heap, parent) { 
  Heap heap;
  EXPECT_EQ(-1, heap.parent(1));
  heap.insert(1);
  EXPECT_FALSE(heap.isEmpty());
  EXPECT_EQ(-1, heap.parent(1));
  heap.insert(3);
  EXPECT_EQ(1, heap.parent(2));
  EXPECT_EQ("1 3", heap.toString());
}

TEST(Heap, insert) { 
  Heap heap;
  heap.insert(1);
  heap.insert(7);
  heap.insert(10);
  heap.insert(3);
  heap.insert(2);

  EXPECT_TRUE(heap.getItem(heap.parent(2)) < heap.getItem(2));
  EXPECT_TRUE(heap.getItem(heap.parent(5)) < heap.getItem(5));
  EXPECT_EQ("1 2 10 7 3", heap.toString());
}