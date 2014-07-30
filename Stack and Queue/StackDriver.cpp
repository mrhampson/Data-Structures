// Lab 8a
// Marshall Hampson
// Editor: gvim
// Compiler: g++

#include <iostream>
#include <string>
using namespace std;

#include <cassert>

#include "Stack.h"
#include "Stack.h" //ifndef test

int main()
{
  cout << "Lab 8a: Test Driver\n"
    << "Programmer: Marshall Hampson" << endl;
    
  //variables
  double returnVal;

  Stack<double> a;
  assert(a.empty() == true);
  assert(a.size() == 0);
  
  // test push 
  a.push(1.1);
  a.push(2.2);
  a.push(3.3);

  // test pop(returnVal) and size()
  assert(a.pop(returnVal) == true);
  assert(returnVal == 3.3);
  assert(a.size() == 2);

  // test peek
  assert(a.peek(returnVal) == true);
  assert(returnVal == 2.2);

  // test pop() and empty()
  assert(a.pop() == true);
  assert(a.peek(returnVal) == true);
  assert(returnVal == 1.1);
  a.pop();
  assert(a.pop() == false);
  assert(a.empty() == true);

  a.push(1.1);
  a.push(2.2);
  a.push(3.3);

  // const object copy testing w/ assign. ON declaration
  {
    const Stack<double> copy = a;
    assert(copy.size() == 3);
    assert(copy.empty() == false);
  }

  // object copy testing w/ assign AFTER declaration
  {
    Stack<double> copy; copy = a;
    assert(copy.size() == 3);
    assert(copy.empty() == false);
    assert(copy.peek(returnVal) == true);
    assert(returnVal == 3.3);
  }
}
