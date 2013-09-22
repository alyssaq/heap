#include <iostream>
#include <vector>
#include "heap.h"

using namespace std;

bool Heap::isEmpty() const {
  return (size_ == 0);
}

int Heap::parent(int n) const {
  if (size_ <= 1) return -1; //empty or root has no parent
  return ((int) n/2); //floor (n/2)
}

void Heap::insert(int val) {
  queue_.push_back(val);
  size_++;
}
