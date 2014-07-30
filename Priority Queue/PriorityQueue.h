// Marshall Hampson
// Lab 12 A
// Editor: gvim
// Compiler: g++

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include<vector>

template <typename T>
class PriorityQueue
{
public:
  PriorityQueue();
  PriorityQueue(const PriorityQueue<T>&);
  ~PriorityQueue();
  PriorityQueue<T>& operator=(const PriorityQueue<T>&);
  
  void enqueue(const T&);
  bool top(T&);
  bool dequeue(T&);
  int getSize() const {return size;}
  bool isEmpty() const {return size == 0;}
  bool makeEmpty();
private:
  vector<T> data;
  int size;
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
:data(20), size(0) {}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& param)
:data(param.data), size(param.size) {}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& param)
{
  data = param.data;
  size = param.size;
  return *this;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{}

template <typename T>
void PriorityQueue<T>::enqueue(const T& param)
{
  int parentIndex;
  int index = size;
  T temp;
  if(index >= data.capacity())
    data.resize(2*data.capacity());
  
  data[index] = param;
  while(true)
  {
    parentIndex = (index+1)/2 - 1;
    if(parentIndex < 0) break;
    if(data[parentIndex] >= data[index]) break;
    temp = data[parentIndex];
    data[parentIndex] = data[index];
    data[index] = temp;
    index = parentIndex;
  }
  ++size;
}

template <typename T>
bool PriorityQueue<T>::top(T& param)
{
  if(size == 0)
    return false;
  param = data[0];
  return true;
}

template<typename T>
bool PriorityQueue<T>::dequeue(T& param)
{
  if(size == 0)
    return false;
  param = data[0];
  int index = 0;
  int leftChild;
  int rightChild;
  int parentIndex;
  T temp;
  while(true)
  {
    leftChild = 2*index+1;
    rightChild = 2*index+2;
    if(leftChild >= size) break;
    if(leftChild == size-1 || data[leftChild] >= data[rightChild])
    {
      data[index] = data[leftChild];
      index = leftChild;
    }
    else
    {
      data[index] = data[rightChild];
      index = rightChild;
    }
  }
  --size;
  if(size < data.capacity()/4)
    data.resize(data.capacity()/4);
  data[index] = data[size];
  while(true)
  {
    parentIndex = (index+1)/2 - 1;
    if(parentIndex < 0) break;
    if(data[parentIndex] >= data[index]) break;
    temp = data[parentIndex];
    data[parentIndex] = data[index];
    data[index] = temp;
    index = parentIndex;
  }
  return true;
}

template <typename T>
bool PriorityQueue<T>::makeEmpty()
{
  if(size == 0)
    return false;
  data.clear();
  size = 0;
  return true;
}

#endif
