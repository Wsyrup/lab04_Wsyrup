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
  //start from the first nonleaf node. Fill out its subtree (based on nodes 2i + 1, 2i + 2 and swapping)
  //then repeat for the next nonleaf node.  

  //at this point, vdata should be an empty array
  vdata.insert(vdata.end(), start, end);
  
  int current_index = (vdata.size() - 2)/2; //first non-leaf index
  //need to keep track of which index we need to return to as well
  int return_index = current_index;
  
  // heapify(vdata, current_index);
  int left_child = 2*current_index + 1;
  int right_child = left_child + 1;

  while (current_index >= 0) {
    //analyze left and right
    //if heap property is not fulfilled, swap with lesser, then enter the subtree and ensure heap property is fulfilled there as well
    //if heap property is fulfilled, decrement by one to move onto the next nonleaf node.

    //base case: leaf node. 
    if (left_child >= int(vdata.size())) {
      return_index--;
      current_index = return_index; //"return" to the original spot, since we've reached a leaf => heap property was satisfied all the way down
    }
    //special case: no right child -> only check left;
    else if (right_child >= int(vdata.size())) {
      if (vdata[left_child] < vdata[current_index]) {
        swap(left_child, current_index);
        current_index = left_child; //enter the subtree to ensure heap property is satisfied there as well
      }
      else {
        return_index--;
        current_index = return_index; //"return" to where we left from
      }
    }
    else if (vdata[left_child] < vdata[current_index] || vdata[right_child] < vdata[current_index]) {
      if (vdata[left_child] < vdata[right_child]) {
        swap(left_child, current_index);
        current_index = left_child;
      }
      else {
        swap(right_child, current_index);
        current_index = right_child;
      }
    }
    else { //heap property is satisfied.
      return_index--;
      current_index = return_index; //move on to next "nonleaf" node
    }

    left_child = 2*current_index + 1;
    right_child = left_child + 1;
  }

}

// Pushes a value into the heap, then ensures
// the heap is correctly arranged
void Heap::push(int value){
  vdata.push_back(value);
  int current_index = vdata.size() - 1;
  int parent_index = 0;

  while (current_index > 0) {
    parent_index = (current_index - 1) / 2;  
    
    if (vdata[current_index] < vdata[parent_index]) {
      swap(current_index, parent_index);
      current_index = parent_index; //current index halves on every iteration. O(logn runtime)
    }
    else { //heap property is finally fulfilled
      return;
    }
  }

  return;
}

// Pops the minimum value off the heap
// (but does not return it), then ensures
// the heap is correctly arranged
void Heap::pop(){
  if (vdata.size() <= 0) return;

  swap(0, vdata.size()-1);
  vdata.pop_back();

  int current_index = 0;
  int left_index = 1;
  int right_index = left_index + 1;

  while (left_index < int(vdata.size())) {
    if (right_index >= int(vdata.size())) {
      //only left index is valid.
      if (vdata[current_index] > vdata[left_index]) {
        swap(current_index, left_index);
        current_index = left_index;
      }
      else {
        return;
      }
    }
    else { //bubble down, and send current down to bubbled down index.
      if (vdata[current_index] > vdata[left_index] || vdata[current_index] > vdata[right_index]) {
        if (vdata[right_index] > vdata[left_index]) {
          swap(current_index, left_index);
          current_index = left_index;
        }
        else {
          swap(current_index, right_index);
          current_index = right_index;
        }
      }
      else {
        return;
      }
    }
    
    left_index = 2 * current_index + 1;
    right_index = left_index + 1;
  }

  return;
}

// Returns the minimum element in the heap
int Heap::top(){
  return vdata[0];
}

// Returns true if the heap is empty, false otherwise
bool Heap::empty(){
  if (vdata.size() == 0) {
    return true;
  }
  return false;
}

//precondition: index1, index2 are valid indices in vdata
void Heap::swap(int index1, int index2) {
  int temp = vdata[index1];
  vdata[index1] = vdata[index2];
  vdata[index2] = temp;
}
    