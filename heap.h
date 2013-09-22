#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>

class Heap {
  std::vector<int> queue_;
  unsigned long size_;

  // Called by insert() when the parent is greater than current
  void bubbleUp(int idx);

public:
  Heap() : queue_(1,0), size_(0) {};
  ~Heap() {};
  bool isEmpty() const;
  int getItem(int idx) const;
  int parent(int n) const;
  void insert(int val);
  std::string toString() const;
};

#endif