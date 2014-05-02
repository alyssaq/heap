#include <iostream>
#include "heap.h"

int main()
{
  Heap h;
  int array[] = {3, 70, 4, 80,90,5,6,82,84,91,92,7,8};
  h.makeHeap(array, 13);

  std::cout << h.toString() << std::endl;
  h.remove(80);
  std::cout << h.toString() << std::endl;
  
  return 0;
}