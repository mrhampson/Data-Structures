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

// Lab 8c
// Marshall Hampson
// Editor: gvim
// Compiler: g++

#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
public:
  Queue();
  Queue(const Queue<T>&);
  ~Queue();
  Queue<T>&  operator=(const Queue<T>&);
  bool push(const T&);
  int getSize() const;
  bool empty() const;
  bool front(T&) const;
  bool end(T&) const;
  bool pop();
  bool pop(T&);
private:
  int capacity;
  int size;
  int head, tail;
  T* data;
  void changeCapacity();
};

template <class T>
Queue<T>::Queue()
:capacity(10), size(0), head(-1), tail(-1)
{
  data = new T[10];
}

template <class T>
Queue<T>::Queue(const Queue<T>& copyThis)
:capacity(copyThis.capacity), size(copyThis.size), head(copyThis.head),
  tail(copyThis.tail)
{
  this->data = new T[capacity];
  for(int i = 0; i < size; ++i)
    this->data[i] = copyThis.data[i];
} 

template <class T>
Queue<T>::~Queue()
{
  delete[] data;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& equalThis)
{
  if(this != &equalThis)
  {
    delete[] data;
    
    head = equalThis.head;
    tail = equalThis.tail;
    capacity = equalThis.capacity;
    size = equalThis.size;
    this->data = new T[capacity];
    for(int i = 0; i < size; i++)
      this->data[i] = equalThis.data[i];
  }
  return *this;
}

template <class T>
bool Queue<T>::push(const T& pushThis)
{
  if(tail == capacity-1) 
    changeCapacity();
  ++tail;
  if(size == 0)
    head = tail;
  data[tail] = pushThis;
  ++size;
  return true;
}

template <class T>
int Queue<T>::getSize() const
{
  return size;
}

template <class T>
bool Queue<T>::empty() const
{
  return size == 0;
}

template <class T>
bool Queue<T>::front(T& theFront) const
{
  if(head > -1)
  {
    theFront = data[head];
    return true;
  }
  else 
    return false;
}

template <class T>
bool Queue<T>::end(T& theEnd) const
{
  if(tail > -1)
  {
    theEnd = data[tail];
    return true;
  }
  else
    return false;
}

template <class T>
bool Queue<T>::pop()
{
  if(head > -1)
  {
    if(size <= capacity/4)
      changeCapacity();
    for(int i = 0; i < size-1; i++)
      data[i] = data[i+1];
    if(tail) --tail;
    if(head) --head;
    --size;
    return true;
  }
  else
    return false;
}

template <class T>
bool Queue<T>::pop(T& popValue)
{
  if(head > -1)
  {
    if(size <= capacity/4)
      changeCapacity();
    popValue = data[head];
    for(int i = 0; i < size-1; i++)
      data[i] = data[i+1];
    if(tail) --tail;
    if(head) --head;
    --size;
    return true;
  }
  else
    return false;
}

template <class T>
void Queue<T>::changeCapacity()
{
  T* temp;
  temp = data;
  if(size <= capacity/4)
  {
    capacity = capacity >> 1;
    data = new T[capacity];
    for(int i = 0; i < size; ++i)
      data[i] = temp[i];
    delete[] temp;
  }
  else
  {
    T* temp;
    temp = data;
    capacity = capacity << 1;
    data = new T[capacity];
    for(int i = 0; i < size; ++i)
      data[i] = temp[i];
    delete[] temp;
  }
}
#endif
