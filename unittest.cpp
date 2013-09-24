// Unittests using Google C++ testing framework.
//
// Author: Alyssa Quek

#include <vector>
#include <iterator>
#include <sstream> 

#include "gtest/gtest.h" // Google testing framework.
#include "heap.h"

using namespace std;

static const std::string vector2Str(std::vector<int> &v) { 
  std::ostringstream sstream;
  copy(v.begin(), v.end() - 1, std::ostream_iterator<int>(sstream, " "));
  sstream << *(v.end() - 1);
  
  return sstream.str();
}

class HeapTest : public testing::Test  {
 protected:
  // SetUp() is run immediately before a test starts.
  virtual void SetUp() {
    startTime_ = time(NULL);
    oneItemHeap_.insert(1);
    twoItemHeap_.insert(1);
    twoItemHeap_.insert(3);
    heap_.insert(1);
    heap_.insert(7);
    heap_.insert(10);
    heap_.insert(3);
    heap_.insert(2);
  }

  // TearDown() is invoked immediately after a test finishes.
  virtual void TearDown() {
    const time_t endTime = time(NULL);
    // Asserts that the test took no more than ~5 seconds.
    EXPECT_TRUE(endTime - startTime_ <= 5) << "The test took too long.";
  }
  
  time_t startTime_; // The UTC time (sec) when the test starts
  Heap heap_;
  Heap oneItemHeap_;
  Heap twoItemHeap_;
};

TEST_F(HeapTest, isEmpty) { 
  Heap heap;
  EXPECT_TRUE(heap.isEmpty());
  EXPECT_EQ("", heap.toString());
  EXPECT_FALSE(oneItemHeap_.isEmpty());
}

TEST_F(HeapTest, size) { 
  Heap heap;
  EXPECT_EQ(0, heap.size());
  EXPECT_EQ(1, oneItemHeap_.size());
  EXPECT_EQ(2, twoItemHeap_.size());
  EXPECT_EQ(5, heap_.size());
}

TEST_F(HeapTest, getItem) { 
  EXPECT_EQ(1, heap_.getItem(1));
  EXPECT_EQ(3, heap_.getItem(heap_.size()));
}

TEST_F(HeapTest, parent) { 
  EXPECT_EQ(-1, oneItemHeap_.parent(1));
  EXPECT_EQ(1, twoItemHeap_.parent(2));
  EXPECT_EQ(2, heap_.parent(4));
}

TEST_F(HeapTest, child) { 
  EXPECT_EQ(-1, oneItemHeap_.child(1));
  EXPECT_EQ(2,  twoItemHeap_.child(1));
  EXPECT_EQ(-1, heap_.child(3));
  EXPECT_EQ(4,  heap_.child(2));
}

TEST_F(HeapTest, insert) { 
  EXPECT_TRUE(heap_.getItem(heap_.parent(2)) < heap_.getItem(2));
  EXPECT_TRUE(heap_.getItem(heap_.parent(5)) < heap_.getItem(5));
  EXPECT_EQ("1", oneItemHeap_.toString());
  EXPECT_EQ("1 3", twoItemHeap_.toString());
  EXPECT_EQ("1 2 10 7 3", heap_.toString());
}

TEST_F(HeapTest, find) {
  EXPECT_EQ(-1, oneItemHeap_.find(1, 3));
  EXPECT_EQ(1,  oneItemHeap_.find(1, 1));
  EXPECT_EQ(-1, heap_.find(13, 10));
  EXPECT_EQ(3,  heap_.find(1, 10));
  EXPECT_EQ(5,  heap_.find(1, 3));
}

TEST_F(HeapTest, remove) {
  Heap heap;
  heap.remove(0);
  EXPECT_EQ(0, heap.size());
  oneItemHeap_.remove(100);
  EXPECT_EQ(1, oneItemHeap_.size());
  EXPECT_EQ("1", oneItemHeap_.toString());
  oneItemHeap_.remove(1);
  EXPECT_EQ(0, oneItemHeap_.size());
  twoItemHeap_.remove(1);
  EXPECT_EQ("3", twoItemHeap_.toString());
  heap_.remove(1);
  EXPECT_EQ(4, heap_.size());
  EXPECT_EQ("2 3 10 7", heap_.toString());
}

TEST_F(HeapTest, extractMin) {
  try {
    Heap heap;
    heap.extractMin();
  } catch (const char *msg) {
    EXPECT_EQ("Empty Heap!", msg);
  }

  EXPECT_EQ(1, heap_.extractMin());
  EXPECT_EQ(4, heap_.size());
}

TEST_F(HeapTest, heapSort) {
  EXPECT_EQ(5, heap_.size());
  std::vector<int> sortedItems = heap_.heapSort();
  EXPECT_EQ(0, heap_.size());
  EXPECT_EQ(5, sortedItems.size());
  EXPECT_EQ("1 2 3 7 10", vector2Str(sortedItems));
}

TEST(MakeHeapTest, makeHeap) {
  Heap heap;

  int oneArray[] = {0};
  heap.makeHeap(oneArray, 1);
  EXPECT_EQ("0", heap.toString());

  heap.clear();
  int twoArray[] = {3, 1};
  heap.makeHeap(twoArray, 2);
  EXPECT_EQ("1 3", heap.toString());

  heap.clear();
  int manyArray[] = {10, 24, 13, 2, 11, 7, -1, -3, 0, 5};
  heap.makeHeap(manyArray, 10);
  EXPECT_EQ("-3 0 -1 2 5 7 13 10 24 11", heap.toString());
  vector<int> v = heap.heapSort();
  EXPECT_EQ("-3 -1 0 2 5 7 10 11 13 24", vector2Str(v));
}


