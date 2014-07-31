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

#ifndef NODE
#define NODE
template <class T>
struct Node
{
  T data;
  Node* next;
};
#endif

#ifndef STACK_H
#define STACK_H

const int POP_EMPTY_ERR = 1;
const int PEEK_EMPTY_ERR = 2;
const int TOP_EMPTY_ERR = 4;
const int MAX_SIZE = 15;

template <class T>
class Stack
{
public:
  Stack();
  Stack(const Stack<T>&);
  ~Stack();
  Stack<T>& operator=(const Stack<T>&);
  bool empty() const;
  int size() const;
  bool peek(T&);
  bool pop(T&);
  bool pop();
  void push(const T&);
  
private:
  Node<T>* head;
  Node<T>* tail;
  int sizeVar;
};

template <class T>
Stack<T>::Stack()
:head(0),tail(0),sizeVar(0)
{
}

template <class T>
Stack<T>::Stack(const Stack<T>& copyMe)
:head(0),tail(0),sizeVar(0)
{
  Node<T>* p;
  for(p = copyMe.head; p; p = p->next)
  {
    Node<T>* node = new Node<T>;
    node->data = p->data;
    node->next = 0;
    if(tail) tail->next = node;
    else head = node;
    tail = node;
    sizeVar++;
  }
}

template <class T>
Stack<T>::~Stack()
{
  Node<T>* p;
  while(head)
  {
    p = head->next;
    delete head;
    head = p;
  }
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& equalThis)
{
  Node<T>* p;
  // delete this
  while(head)
  {
    p = head->next;
    delete head;
    head = p;
  }
  tail = 0;
  sizeVar = 0;

  //copy equalThis into the new Stack
  for(p = equalThis.head; p; p = p->next)
  {
    Node<T>* newNode = new Node<T>;
    newNode->data = p->data;
    newNode->next = 0;
    if(tail) tail->next = newNode;
    else head = newNode;
    tail = newNode;
    sizeVar++;
  }

  return *this;
}

template <class T>
bool Stack<T>::empty() const
{
  if(head)
    return false;
  else
    return true;
}

template <class T>
int Stack<T>::size() const
{
  return sizeVar;
}

template <class T>
bool Stack<T>::peek(T& returnVal)
{ 
  if(head)
  {
    returnVal = head->data;
    return true;
  }
  else
    return false;
}

template <class T>
bool Stack<T>::pop(T& returnVal)
{
  if(head)
  {
    returnVal = head->data;
    Node<T>* temp = head->next;
    delete head;
    head = temp;
    sizeVar--;
    return true;
  }
  else
    return false;
} 

template <class T>
bool Stack<T>::pop()
{
  if(head)
  {
    Node<T>* temp = head->next;
    delete head;
    head = temp;
    sizeVar--;
    return true;
  }
  else
    return false;
}

template <class T>
void Stack<T>::push(const T& addThis)
{
  Node<T>* temp = new Node<T>;
  temp->data = addThis;
  temp->next = head;
  head = temp;
  if(!tail) tail = temp;
  sizeVar++;
}

#endif
