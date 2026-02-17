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
    