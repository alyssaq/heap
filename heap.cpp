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

Heap::Heap() : queue_(1,0), size_(0) {}

bool Heap::isEmpty() const {
  return (size_ == 0);
}

int Heap::size() const {
  return size_;
}

void Heap::clear() {
  queue_.clear();
  queue_.push_back(0); //first item is a dud
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

int Heap::find(unsigned int idx, int val) const { //O(log n)
  if (idx > size_) return -1; //base case: idx out of bounds
  if (val < queue_[idx]) return -1;   //base case: val not in min-heap
  if (queue_[idx] == val) return idx; //Found the val, return its index

  int childIdx = child(idx), i = -1;

  if (childIdx != -1) { //find in left and right children
    i = max(find(childIdx, val), find(childIdx + 1, val));
  }

  return i;
} 

void Heap::bubbleUp(int idx) { //O(log n)
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

// @Precondition: index aIdx and bIdx exist in the array
int Heap::getMinIdx(int aIdx, int bIdx, int cIdx) {
  bool isLeftSmaller = (queue_[aIdx] < queue_[bIdx]);

  if (cIdx > (int) size_) { //the last right child doesnt exist
    return isLeftSmaller ? aIdx : bIdx;
  } else if (isLeftSmaller) {
    return (queue_[aIdx] < queue_[cIdx]) ? aIdx : cIdx;
  } else {
    return (queue_[bIdx] < queue_[cIdx]) ? bIdx : cIdx;
  }
}

void Heap::bubbleDown(int idx) { //O(log n)
  int childIdx = child(idx);
  if (childIdx == -1) return; //base case: no children left
  int minIdx = getMinIdx(idx, childIdx, childIdx + 1);
  
  if (minIdx != idx) {
    swap(queue_[minIdx], queue_[idx]);
    bubbleDown(minIdx);
  }
}

void Heap::remove(int val) { //O(2 * log n)
  int idx = find(1, val);
  if (idx == -1) return;

  queue_[idx] = queue_[size_--]; // swap current with last item
  queue_.resize(size_ + 1); //idx 0 is a dud item
  bubbleDown(idx);
}

int Heap::extractMin() { //Special case of remove: O(2 * log n)
  if (isEmpty()) throw "Empty Heap!";
  
  int min = queue_[1];
  remove(min);
  return min;
}

vector<int> Heap::heapSort() { //O(n log n)
  vector<int> sortedItems;
  sortedItems.reserve(size_);
  while(!isEmpty()) {
    sortedItems.push_back(extractMin());
  }

  return sortedItems;
}

// Create the heap given an unsorted array
void Heap::makeHeap (int array[], int n){ //O(n log n)
  size_ = n;
  int i = 0;

  for (; i < n; i++) { // O(n)
    queue_.push_back(array[i]);
  }
  for (i = n; i > 0; i--) {
    bubbleDown(i); //O(log n)
  }
}

string Heap::toString() const {
  if (isEmpty()) return "";

  ostringstream sstream;
  copy(queue_.begin() + 1, queue_.end() - 1, ostream_iterator<int>(sstream, " "));
  sstream << *(queue_.end() - 1);
  
  return sstream.str();
}