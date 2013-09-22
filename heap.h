#ifndef HEAP_H
#define HEAP_H

#include <vector>

class Heap {
  std::vector<int> queue_;
  unsigned long size_;

public:
  Heap() : queue_(1,0), size_(0) {};
  ~Heap() {};
  bool isEmpty() const;
  int parent(int n) const;
  void insert(int val);

};

#endif