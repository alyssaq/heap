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

  heap.insert(1);
  EXPECT_FALSE(heap.isEmpty());
}

TEST(Heap, parent) { 
  Heap heap;
  EXPECT_EQ(-1, heap.parent(1));
  heap.insert(1);
  EXPECT_EQ(-1, heap.parent(1));
  heap.insert(3);
  EXPECT_EQ(1, heap.parent(2));
}
