// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
