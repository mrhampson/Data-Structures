// Marshall Hampson
// Lab 12 A
// Editor: gvim
// Compiler: g++
#include <iostream>
using namespace std;

#include <cassert>

#include "PriorityQueue.h"
#include "PriorityQueue.h" //ifndef test

int main()
{
  cout << "Lab 12a\nProgrammer: Marshall Hampson" << endl;

  PriorityQueue<int> pq;
  int temp;
  
  for(int i = 0; i < 100; ++i) //test enqueue
    pq.enqueue(i);
  
  assert(pq.isEmpty() == false); // test isEmpty 
  pq.top(temp); // test top
  assert(pq.getSize() == 100);  // test getSize
  assert(temp == 99);
  for(int i = 0; i < 80; ++i) //test dequeue
    pq.dequeue(temp);
  pq.top(temp);
  assert(temp == 19);
  assert(pq.getSize() == 20);
 
  // Object copy testing with assignment UPON declaration
  {
    const PriorityQueue<int> copy = pq;
    assert(copy.getSize() == 20);
    assert(copy.isEmpty() == false);
  }

  // Object copy testing with assignment AFTER declaration
  {
    PriorityQueue<int> copy; copy = pq;
    pq.makeEmpty();
    assert(pq.getSize() == 0);
    assert(pq.isEmpty() == true);
    assert(pq.makeEmpty() == false); //test makeEmpty
  }
}
