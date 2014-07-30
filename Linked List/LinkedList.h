// Lab 10a
// Programmer: Marshall Hampson
// Editor/Compiler: Visual Studios Ultimate 2012

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cassert>

#ifndef NODE
#define NODE
template<class T>
struct Node
{
  T data;
  Node<T>* next;
};
#endif

template<class T>
class LinkedList
{
public:
  LinkedList();
  LinkedList(const LinkedList<T>&);
  ~LinkedList();
  LinkedList<T>& operator=(const LinkedList<T>&);
  T& operator[] (int index); // O(n)
  void insert(const T&); // O(1)
  bool first(T&); // O(1)
  bool getNext(T&); // O(1)
  bool find(const T&); // O(n)
  bool retrieve(T&); // O(n)
  bool replace(const T&); // O(1)
  bool remove(T&); // O(n)
  bool isEmpty() const {return head == 0;} // O(1)
  void makeEmpty(); // O(n)
  int length() const {return myLength;} //O(1)
private:
  Node<T>* head;
  Node<T>* current;
  int myLength;
  int currentIndex;
  T dummy;
};

template <class T>
LinkedList<T>::LinkedList()
: head(0), current(0), myLength(0), currentIndex(-1) {}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& a)
: head(0), current(0), myLength(a.myLength), currentIndex(a.currentIndex)
{
  Node<T>* p;
  Node<T>* end = 0;
  for (p = a.head; p; p = p->next)
  {
    Node<T>* node = new Node<T>;
    node->data = p->data;
    node->next = 0;
    if (end) end->next = node;
    else head = node;
    end = node;
    if (p == a.current) current = node; 
  }
}

template <class T>
LinkedList<T>::~LinkedList()
{
  Node<T>* p;
  while (head) 
  { 
    p = head->next; 
    delete head; 
    head = p;
  }
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& a)
{
  if (this != &a)
  {
    current = 0;
    Node<T>* p;
    Node<T>* end = 0;
    while (head) 
    { 
      p = head->next; 
      delete head; 
      head = p;
    }
    for (p = a.head; p; p = p->next)
    {
      Node<T>* node = new Node<T>;
      node->data = p->data;
      node->next = 0;
      if (end) end->next = node;
      else head = node;
      end = node;
      if (p == a.current) current = node; 
    }
    myLength = a.myLength;
    currentIndex = a.currentIndex;
  }
  return *this;
}

template <class T>
T& LinkedList<T>::operator[] (int index)  // O(n)
{
  //validate the current index
  if(current == 0) assert(currentIndex == -1);
  else assert(currentIndex >= 0);

  T firstValue, getNextValue;
  // if the list is empty return the dummy
  if(isEmpty() || index >= myLength) 
    return dummy;
  else if(index == currentIndex)
    return current->data;
  else if(index == currentIndex + 1 && currentIndex != -1)
  {
    getNext(getNextValue);
    return current->data;
  }
  else
  {
    first(firstValue);
    for(int i = 0; i < index; ++i)
      getNext(getNextValue);
    return current->data;
  }
}

template <class T>
void LinkedList<T>::insert(const T& parameter) // O(1)
{
  current = 0;
  currentIndex = -1;
  Node<T>* node = new Node<T>;
  node->data = parameter;
  node->next = head;
  head = node;
  myLength++;
}

template <class T>
bool LinkedList<T>::first(T& parameter) // O(1)
{
  if (!head) return false;
  parameter = head->data;
  current = head;
  currentIndex = 0;
  return true;
}

template <class T>
bool LinkedList<T>::getNext(T& parameter) // O(1)
{
  if (!current) return false;
  current = current->next;
  if (!current) return false;
  parameter = current->data;
  currentIndex++;
  return true;
}

template <class T>
bool LinkedList<T>::find(const T& parameter) // O(n)
{
  T temp;
  if (first(temp)) do
  {
    if (parameter == temp) return true; // found it
  } while (getNext(temp));
  return false; // no match
}

template <class T>
bool LinkedList<T>::retrieve(T& parameter) // O(n)
{
  if (!find(parameter)) return false;
  parameter = current->data; // set in find
  return true;
}

template <class T>
bool LinkedList<T>::replace(const T& parameter) // O(1)
{
  if (!current) return false;
  current->data = parameter;
  return true;
}

template <class T>
bool LinkedList<T>::remove(T& parameter) // O(n)
{
  // find node to remove
  Node<T>* p;
  Node<T>* prev;
  for (prev = 0, p = head; p; prev = p, p = p->next)
    if (p->data == parameter)
      break;

  // deallocate node here
  if (!p) return false; // no match
  if (prev) prev->next = p->next; else head = p->next;
  if (p == current) current = current->next;
  if(current) currentIndex++;
  else currentIndex = -1;
  parameter = p->data;
  delete p;

  myLength--;

  return true;
}

template <class T>
void LinkedList<T>::makeEmpty() // O(n)
{
  while (head) 
  { 
    current = head->next; 
    delete head; 
    head = current;
  }
  myLength = 0;
}

#endif