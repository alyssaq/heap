/*
  Heap using an array
  Enables us to represent binary trees without pointers:
  - Left child sits at 2n
  - Right child sits at 2n + 1
  - Parent sits at floor(n/2)
*/

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>

class Heap {
  std::vector<int> queue_;
  unsigned    int  size_;

  // Called by insert()
  // If the parent's value is greater than current
  //  the current item bubbles up till we reach root
  void bubbleUp  (int idx);
  // Called by delete() 
  // If the current is greater than children
  //  the current item bubbles down till no more children
  void bubbleDown(int idx);
  // Used by bubbleDown()
  //  Get the index of the min value 
  //  between 3 given indices to the heap array.
  int getMinIdx  (int aIdx, int bIdx, int cIdx);

public:
  Heap();
  ~Heap() {};
  bool              isEmpty   () const;
  int               size      () const;
  void              clear     ();
  int               getItem   (unsigned int idx) const;
  int               parent    (unsigned int idx) const;
  int               child     (unsigned int idx) const;
  int               find      (unsigned int idx, int val) const;
  void              insert    (int val);
  void              remove    (int val);
  void              makeHeap   (int array[], int size);
  int               extractMin(); //Removes and returns min value
  std::vector<int>  heapSort  (); //O(n log n)
  std::string       toString  () const;
};

#endif