#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream> //stringstream

#include "heap.h"

using namespace std;
typedef vector<int>::const_iterator vecCiter;

bool Heap::isEmpty() const {
  return (size_ == 0);
}

int Heap::getItem(int idx) const {
  return queue_[idx];
}

int Heap::parent(int n) const {
  if (size_ <= 1) return -1; //empty or root has no parent
  return ((int) n/2); //floor (n/2)
}

void Heap::bubbleUp(int idx) {
  int parentIdx = parent(idx);
  if (parentIdx == -1) return; //base case: root of heap

  if (queue_[parentIdx] > queue_[idx]) {
    swap(queue_[parentIdx], queue_[idx]);
    bubbleUp(parentIdx);
  } 
}

void Heap::insert(int val) {
  queue_.push_back(val);
  size_++;
  bubbleUp(size_);
}

string Heap::toString() const {
  if (isEmpty()) return "";
  
  ostringstream sstream;
  copy(queue_.begin() + 1, queue_.end() - 1, ostream_iterator<int>(sstream, " "));
  sstream << *(queue_.end() - 1);
  
  return sstream.str();
}