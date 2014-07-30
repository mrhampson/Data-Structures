// Lab 8c
// Marshall Hampson
// Editor: gvim
// Compiler: g++

#include <iostream>
using namespace std;

#include<cassert>

#include "Queue.h"
#include "Queue.h" //ifndef test

int main()
{
  // idnetifying output
  cout << "Lab 8c\n"
    << "Programmer: Marshall Hampson" << endl;

  // variables
  Queue<double> q;
  double front;
  double end;
  double popValue;

  // test push, front, end, getSize, and empty functinos
  q.push(1.1); q.push(2.2); q.push(3.3); q.push(4.4); q.push(5.5);
  q.front(front);
  q.end(end);
  assert(q.getSize() == 5);
  assert(q.empty() == false);
  assert(front >= 1.09999 && front <= 1.10001); 
  assert(end >= 5.49999 && end <= 5.50001); 
  
  // test pop
  q.pop(popValue);
  assert(popValue == 1.1);
  q.pop();
  q.front(front);
  q.end(end);
  assert(front == 3.3);
  assert(end == 5.5); 

  // const object copy testing w/ assingment ON declaration
  {
    const Queue<double> copy = q;
    copy.front(front);
    copy.end(end);
    assert(copy.empty() == false);
    assert(copy.getSize() == 3);
    assert(front <= 3.30001 && front >= 3.29999);
    assert(end <= 5.50001 && end >= 5.49999); 
  }

  // object copy testing with assignment AFTER declaration
  {
    Queue<double> copy; copy = q;
    copy.front(front);
    copy.end(end);
    assert(copy.empty() == false);
    assert(copy.getSize() == 3);
    assert(front <= 3.30001 && front >= 3.29999);
    assert(end <= 5.50001 && end >= 5.49999);
  }
}
