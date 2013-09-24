# [Heap]( http://en.wikipedia.org/wiki/Heap_\(data_structure\) ) Implementation in C++

**Min-heap property**: All nodes are less than or equal of its children.   

Compile:   
> make

Run:   
> ./unittest.out

You should see all tests PASSED.  

###Operations
*n* = number of items in the heap

- **Insert** - *O(log n)*: add a new item to the heap
- **Extract min** - *O(log n)*: remove an item with minimum value    
- **Delete** - *O(log n)*: remove an item from the heap
- **Heapify** - *O(n)*: create a heap out of given array of items
- **Heapsort** - *O(n log n)*: calls extract-min *n* items to sort the heap

###Applications:
 - Event manager
 - Median maintenance
 - Speeding up Dijkstra's shortest-path algorithm with *n* vertices and *m* edges.   
  O(nm) => O(m log n).  *n* loop iteations, *m* work per iteration (linear scan through edges for min computations)

## Google C++ Testing
Note that I have included the Google Test object file (gtest_main.a) 
so that you do not need to download Google's C++ test framework.
The object file is built against version 1.7.     

If you wish to re-build another version, you may download the 
test framework at http://code.google.com/p/googletest/   

Move the gtest folder somewhere permenant, e.g. ~/Documents.   
Create a symlink to the gtest folder where Makefile resides.        
> ln -s ~/Documents/lib/gtest-1.7.0 gtest  

To use it, comment out the .INTERMEDIATE line in the Makefile.    
This will build the gtest object file located at GTEST_DIR.    
Replace $(GTEST_OBJECT) with $(GTEST_HEADERS)
