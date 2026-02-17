// heap.cpp
// Christian Kantchev

#include "heap.h"
#include <iostream>
using std::cout;

// Builds a heap from the range [start, end) using the heapify algorithm
// Should run in O(n) time
Heap::Heap(std::vector<int>::iterator start, std::vector<int>::iterator end){
  //O(n) average because half of the nodes are never pushed down, a fourth are pushed
  //down only once, etc...
}

// Pushes a value into the heap, then ensures
// the heap is correctly arranged
void Heap::push(int value){
  //needs to reheapify upward
}

// Pops the minimum value off the heap
// (but does not return it), then ensures
// the heap is correctly arranged
void Heap::pop(){
  //needs to reheapify downward
  //store final element.
  //replace root element (idx 0) with final element (idx size()-1) and pop back
  //then, compare new root element with its children. Since we are building a min heap,
  //heap property is that parent is less than children.
  //compare parent with children (at indices 2n + 1, 2n + 2), and evaluate heap property.
  //swap parent with smaller (larger ?) child until heap property is satisfied
  //definitely swap with smaller. That way, the heap property remains satisfied (since the larger child)
  //becomes the child of the swapped smaller one.
  //need to deal with index out of bounds

  int final_leaf = vdata[vdata.size()-1];

  vdata[0] = final_leaf;
  vdata.pop_back();

  std::vector<int>::iterator current = vdata.begin();
  int current_index = 0;
  int left_child_index = 0;

  //last parent node is found at (n-1) // 2
  while (current_index <= (vdata.size()-1)/2) {
    //compare with children
    left_child_index = (2 * current_index) + 1;
    if (*(current + left_child_index) < *current || *(current + left_child_index + 1) < *current) {
      if (*(current + left_child_index) < *(current + left_child_index + 1)) {
        swap(current, current + left_child_index);
      }
      else {
        swap(current, current + left_child_index + 1);
      }

      current = (*(current + left_child_index) < *(current + left_child_index + 1)) ? current + left_child_index : current + left_child_index + 1;
    }
    else { // !(left < current || right < current) = (left >= current && right >= current)
      return;
    }
  }

  return;
}

// Returns the minimum element in the heap
int Heap::top(){
  return (vdata.size() == 0) ? NULL : vdata[0];
}

// Returns true if the heap is empty, false otherwise
bool Heap::empty(){
  if (vdata.size() == 0) {
    return true;
  }
  return false;
}

//Additional private helper function implementations:
void Heap::swap(std::vector<int>::iterator& first, std::vector<int>::iterator& second) {
  int temp = *first;
  *first = *second;
  *second = temp;
}
    