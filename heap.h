// heap.h
// Binary heap tree header file for CS 24 lab
// Christian Kantchev

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

class Heap{

 public:
   Heap() { vdata = std::vector<int>(); }  // default constructor
   Heap(std::vector<int>::iterator start, std::vector<int>::iterator end); // build a heap from a range using heapify
   void push(int value);     // insert value; //duplicates are allowed
   void pop(); // delete the min element
   int top();
   bool empty();

 private:
   std::vector<int> vdata; //store the binary heap tree as a dynamic array

   //additional private helper functions, for the public methods. 
   //iterator swap
   void swap(std::vector<int>::iterator first, std::vector<int>::iterator second);
   
   //index swap
   void swap(int index1, int index2);

   //recursive private heapify helper.
   void heapify(std::vector<int>& vdata, int current_index);

};

#endif