#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream> //stringstream

#include "heap.h"

using namespace std;
typedef vector<int>::iterator vecIter;
typedef vector<int>::const_iterator vecCiter;

bool Heap::isEmpty() const {
  return (size_ == 0);
}

int Heap::size() const {
  return size_;
}

int Heap::getItem(unsigned int idx) const {
  return queue_[idx];
}

int Heap::parent(unsigned int idx) const {
  if (size_ <= 1) return -1; //empty or root has no parent
  return ((int) idx / 2); //floor (idx/2)
}

int Heap::child(unsigned int idx) const {
  if (size_ <= 1 || 2 * idx > size_ ) return -1; //empty or root has no child
  return (2 * idx);
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

int Heap::find(int val) const {
  for (unsigned int i = 1; i <= size_; i++) {
    if (queue_[i] == val) return i;
  }
  return -1;
}

// @Precondition: index aIdx and bIdx exist in the array
int Heap::getMinIdx(int aIdx, int bIdx, int cIdx) {
  bool isLeftSmaller = (queue_[aIdx] < queue_[bIdx]);

  if (cIdx > (int) size_) { //the last right child doesnt exist
    return isLeftSmaller ? aIdx : bIdx;
  }

  if (isLeftSmaller)
    return (queue_[aIdx] < queue_[cIdx]) ? aIdx : cIdx;
  else
    return (queue_[bIdx] < queue_[cIdx]) ? bIdx : cIdx;
}

void Heap::bubbleDown(int idx) {
  int childIdx = child(idx);
  if (childIdx == -1) return; //base case: no children left
  int minIdx = getMinIdx(idx, childIdx, childIdx + 1);
  
  if (minIdx != idx) {
    swap(queue_[minIdx], queue_[idx]);
    bubbleDown(minIdx);
  }
}

void Heap::remove(int val) {
  int idx = find(val);
  if (idx == -1) return;

  queue_[idx] = queue_[size_--]; // swap current with last item
  queue_.resize(size_ + 1); //idx 0 is a dud item
  bubbleDown(idx);
}

string Heap::toString() const {
  if (isEmpty()) return "";

  ostringstream sstream;
  copy(queue_.begin() + 1, queue_.end() - 1, ostream_iterator<int>(sstream, " "));
  sstream << *(queue_.end() - 1);
  
  return sstream.str();
}