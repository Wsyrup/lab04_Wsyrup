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
  copy(start, end, vdata.begin());
  
  int current_index = (vdata.size() - 2)/2;
  
  heapify(vdata, current_index);

  // while (current_index >= 0) {
  //   left_child = 2 * current_index + 1;
  //   right_child = 2 * current_index + 2;

  //   if (right_child > vdata.size()) { //only left child. Special case of first node
  //     if (vdata[left_child] < vdata[current_index]) swap(left_child, current_index);
  //   }
  //   else { //two children. Swap with lesser of the two
  //     if (vdata[current_index] > vdata[left_child] || vdata[current_index] > vdata[right_child]) {
  //       //heap property is unsatisfied
  //       (vdata[left_child] < vdata[right_child]) ? swap(left_child, current_index) : swap(right_child, current_index);
  //     }
  //   }

  //   //if neither condition runs, the heap property is satisfied for the data.
  //   //move on to the next nonleaf node (current_index - 1) and repeat.
  //   //if we swap, we need to enter that subtree to make sure the heap property is satisfied there too
  //   //we can do this by setting current_index to the child and running the loop again. Once the 
  //   //loop satisfies, we return to previous indeices and move on.
  //   //maybe recursive?

  // }



}

void Heap::heapify(std::vector<int>& vdata, int current_index) {
  if (current_index < 0) return;
  int left_child = 2 * current_index + 1;
  int right_child = 2 * current_index + 2;

  if (left_child >= vdata.size()) return;

  if (right_child >= vdata.size()) { //only left child. Special case of first node
    if (vdata[left_child] < vdata[current_index]) swap(left_child, current_index);
    heapify(vdata, left_child);
  }
  else { //two children. Swap with lesser of the two
    if (vdata[current_index] > vdata[left_child] || vdata[current_index] > vdata[right_child]) {
      //heap property is unsatisfied
      (vdata[left_child] < vdata[right_child]) ? swap(left_child, current_index) : swap(right_child, current_index);
      (vdata[left_child] < vdata[right_child]) ? heapify(vdata, left_child) : heapify(vdata, right_child);
    }
  }

  heapify(vdata, current_index - 1);
  return;
}

// Pushes a value into the heap, then ensures
// the heap is correctly arranged
void Heap::push(int value){
  //needs to reheapify upward
  //push_back into the vector.
  //then, while the value is smaller than its parent, swap the two.
  //reverse iteration?  from index i we go to (i-1) // 2

  vdata.push_back(value);
  std::vector<int>::iterator current = vdata.begin() + vdata.size() - 1;
  int current_index = vdata.size() - 1;
  int parent_index = 0;

  while (current_index > 0) {
    parent_index = (current_index - 1) / 2;  
    
    if (vdata[current_index] < vdata[parent_index]) {
      swap(current, vdata.begin() + parent_index);
      current = vdata.begin() + parent_index;
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
  while (current_index <= (vdata.size()-2)/2) { //vdata.size()-1 gives n, but the last parent is at n-1/2
    //compare with children
    left_child_index = (2 * current_index) + 1;
    if (*(current + left_child_index) < *current || *(current + left_child_index + 1) < *current) {
      if (*(current + left_child_index) < *(current + left_child_index + 1)) {
        swap(current, current + left_child_index);
        current_index = left_child_index;
      }
      else {
        swap(current, current + left_child_index + 1);
        current_index = left_child_index + 1;
      }

      current = (*(current + left_child_index) < *(current + left_child_index + 1)) ? current + left_child_index : current + left_child_index + 1;
    }
    else { // !(left < current || right < current) = (left >= current && right >= current)
      return;
    }

    //need to handle case where no right child
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
void Heap::swap(std::vector<int>::iterator first, std::vector<int>::iterator second) {
  int temp = *first;
  *first = *second;
  *second = temp;
}

//precondition: index1, index2 are valid indices in vdata
void Heap::swap(int index1, int index2) {
  int temp = vdata[index1];
  vdata[index1] = vdata[index2];
  vdata[index2] = temp;
}
    