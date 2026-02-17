#Makefile by Christian Kantchev
#makes tests
CXX=g++
CXXFLAGS=-g --std=c++20 -Wall

tests: heap.o examheap.o
	${CXX} ${CXXFLAGS} heap.o examheap.o -o tests

heap.o: heap.cpp heap.h
	${CXX} ${CXXFLAGS} heap.cpp -c

examheap.o: examheap.cpp heap.h
	${CXX} ${CXXFLAGS} examheap.cpp -c

clean:
	rm -f *.o tests