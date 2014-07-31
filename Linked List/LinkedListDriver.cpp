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

// Lab 10a
// Programmer: Marshall Hampson
// Editor/Compiler: Visual Studios Ultimate 2012

#include <iostream>
#include <string>
using namespace std;

#include <cassert>
#include <ctime> // for time()

#include "LinkedList.h"
#include "LinkedList.h" //ifndef test

struct Student
{
  int id; // key
  string name;
  string phoneNum;
};

bool operator==(Student x, Student y)
{
  return x.id == y.id;
}

int main()
{
  // identifying output
  cout << "Lab 10a\nProgrammer: Marshall Hampson" << endl;

  //variables
  Student returnValue;

  //create some Student objects
  Student a = {1111111, "Stanley", "5557871234"};
  Student b = {2222222, "Mavis", "5551234567"};
  Student c = {3333333, "Parker", "123456789"};

  Student findThis;
  findThis.id = 1111111;
  Student replaceWith = {4444444, "Marshall", "9999999999"};

  //create a linked list of the Students
  LinkedList<Student> l;

  // make sure these return false for an empty list
  assert(l.first(returnValue) == false);
  assert(l.getNext(returnValue) == false);

  // fill the list
  l.insert(a);
  l.insert(b);
  l.insert(c);

  // test all setters and getters except makeEmpty()
  assert(l[0] == c); // [] test
  assert(l.length() == 3);  // length() test
  l.first(returnValue); // first() test
  assert(returnValue == c); 
  l.getNext(returnValue); //getNext() test
  assert(returnValue == b); 
  assert(l.find(findThis) == true); // find() test
  l.retrieve(findThis);  //retrieve() test
  assert(findThis.name == "Stanley");
  assert(findThis.phoneNum == "5557871234");
  l.replace(replaceWith);  // replace() test
  assert(l.retrieve(findThis) == false); //this should be false b/c replace overwrote it
  l.remove(replaceWith);  // remove() test
  assert(l.retrieve(replaceWith) == false);
  assert(l.isEmpty() == false); // isEmpty() test

  // const object copy testing w/ assignment UPON declaration
  {
    const LinkedList<Student> copy = l;
    assert(copy.isEmpty() == false);
    assert(copy.length() == 2);
  }


  //object copy testing w/ assignment AFTER declaration
  {
    LinkedList<Student> copy; copy = l;
    assert(l.length() == 2);  // length() test
    l.first(returnValue); // first() test
    assert(returnValue == c); 
    l.getNext(returnValue); //getNext() test
    assert(returnValue == b); 
    findThis = b;
    assert(l.find(findThis) == true); // find() test
    assert(l.isEmpty() == false); // isEmpty() test
  }
  
  l.makeEmpty(); // test makeEmpty()
  assert(l.length() == 0);

  cout << "Program has finished.  Press ENTER to quit." << endl;
  cin.get();
}
