# [Heap]( http://en.wikipedia.org/wiki/Heap_\(data_structure\) ) Implementation in C++

This is an implementation of a **binary min-heap**.   
Heaps maintain an implicit binary tree structure in an array (I used the STL vector so that we do not have to specify an array size at creation time).   
**Min-heap property**: All nodes are less than or equal of its children. Thus, the minimum key always sits at the top of the heap.

## Usage
Compile:

    $ g++ heap.cpp example.cpp

Run:

    $ ./a.out

## Tests
Compile (needs googletest header files):   

    $ make

Run:   

    $ ./unittest.out

You should see that all tests have PASSED.  

##Operations
*n* = number of items in the heap

- **Insert** - *O(log n)*: add a new item to the heap
- **Extract min** - *O(log n)*: remove an item with minimum value    
- **Delete** - *O(log n)*: remove an item from the heap
- **bubbleUp/bubbleDown** - *O(log n)*: rearrage heap to maintain its property
- **Heapsort** - *O(n log n)*: calls extract-min *n* items to sort the heap
- **Make heap** - *O(n)*: given an unsorted array, each element for *n* elements has to be added into the internal queue and bubbleDown *O(log n)*. Not all heapify operations are *O(log n)*, this is why you are getting [O(n)](http://www.cs.umd.edu/~meesh/351/mount/lectures/lect14-heapsort-analysis-part.pdf).  

## Applications:
 - Event manager
 - Median maintenance
 - Speeding up Dijkstra's shortest-path algorithm with *n* vertices and *m* edges.   
  O(nm) => O(m log n).  *n* loop iteations, *m* work per iteration (linear scan through edges for min computations)

## Google C++ Testing
Note that I have included the Google Test object file (gtest_main.a) 
so that you do not need to re-build Google's C++ test framework.
The object file is built against version 1.7.     

If you wish to re-build another version, you may download the 
test framework at http://code.google.com/p/googletest/   

Move the gtest folder somewhere permenant, e.g. ~/Documents.   
Create a symlink to the gtest folder where Makefile resides.   
     
    > ln -s ~/Documents/lib/gtest-1.7.0 gtest  

To use it, comment out the .INTERMEDIATE line in the Makefile.    
This will build the gtest object file located at GTEST_DIR.    
Replace $(GTEST_OBJECT) with $(GTEST_HEADERS)

## Random Trivia
max-heap vs sorted array:   

1. Find the maximum element quickly:    
O(1) for both. Root of max-heap and last element in array.    
2. Delete an element quickly:   
O(log n) for max-heap. O(n) for array without the element index, otherwise, O(1).   
3. Form the structure quickly:  
O(n) to build a heap, O(n log n) to sort an array.      
4. Find the minimum element quickly:  
O(log n) to find the min element. O(1) for the array as the first element.   