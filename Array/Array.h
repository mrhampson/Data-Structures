// Lab 5a
// Programmer: Marshall Hampson
// Compiler: g++
// Editor: gvim

#ifndef Array_h
#define Array_h

#include<string>
using namespace std;

// Error Codes
const int GOOD = 0;
const int ERR_INIT_CAPACITY = 1;
const int ERR_INDEX = 2;
const int ERR_RESIZE_CAPACITY = 4;
const int MAX_ERR_SIZE = 7;

template<class T>
class Array
{
public:
  Array(int size);
  Array(const Array<T>&);
  ~Array();
  Array<T>& operator=(const Array<T>& a);
  T& operator[](int index);
  int capacity() const {return cap;}
  void changeCapacity(int);
  int lsearch(const T& matchMe) const;
  string err() const; 

private:
  int cap;
  int errorCode;
  T* data;
  T dummy;
};

template<class T>
Array<T>::Array(int initCapacity)
:cap(initCapacity), errorCode(0), data(0)
{
  if(initCapacity > 0)
    data = new T[cap];
  else
    errorCode |= 1;
}

template<class T>
Array<T>::Array(const Array<T>& a)
:cap(a.cap), errorCode(a.errorCode), data(0)
{
  if (cap > 0)
    data = new T[cap];
  for (int i = 0; i < cap; i++)
    data[i] = a.data[i];
}

template<class T>
Array<T>::~Array()
{
  delete[] data;
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& a)
{
  if(this != &a)
  {
    delete[] data;
    cap = a.cap;
    if(cap <= 0)
      data = 0;
    else
    {
      data = new T[cap];
      for(int i = 0; i < cap; i++)
        data[i] = a.data[i];
    }
  }
  return *this;
}

template<class T>
T& Array<T>::operator[](int index)
{
  errorCode &= (MAX_ERR_SIZE-ERR_INDEX); // turn off index error
  if(index >= 0 && index < cap)
    return *(data+index);
  else 
  {
    errorCode |= 2;
    return dummy;
  }
}

template<class T>
void Array<T>::changeCapacity(int n)
{
  errorCode &= (MAX_ERR_SIZE-ERR_RESIZE_CAPACITY); // turn off error
  if(n < 0)
    errorCode  |= 4;
  else
  {
    T* temp = new T[n];
    int limit = (n > cap) ? cap : n;
    for(int i = 0; i < limit; i++)
      temp[i] = data[i];
    delete[] data;
    data = temp;
    cap = n;
  }
}

template <class T>
int Array<T>::lsearch(const T& matchMe) const
{
  if(data == 0) 
    return -1;
  for(int i = 0; i < cap; i++)
    if(matchMe == data[i])
      return i;
  return -1;
}

template <class DataType>
string Array<DataType>::err() const
{
  string result;
  if (errorCode & 1)
    result += string(result.length() ? " | " : "") + 
      "invalid capacity parameter in constructor";
  if (errorCode & 2)
    result += string(result.length() ? " | " : "") +
      "invalid index used in []";
  if (errorCode & 4)
    result += string(result.length() ? " | " : "") +
      "invalid new capacity parameter in changeCapacity";
  return result;
}


#endif
