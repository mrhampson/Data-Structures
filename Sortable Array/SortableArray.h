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

// Lab 14a
// Programmer: Marshall Hampson
// Compiler: g++
// Editor: gvim

#ifndef SORTABLE_ARRAY_H 
#define SORTABLE_ARRAY_H 

#include<string>
using namespace std;

// Error Codes
const int GOOD = 0;
const int ERR_INIT_CAPACITY = 1;
const int ERR_INDEX = 2;
const int ERR_RESIZE_CAPACITY = 4;
const int MAX_ERR_SIZE = 7;

template<typename T>
class SortableArray
{
public:
  SortableArray(int size);
  SortableArray(const SortableArray<T>&);
  ~SortableArray();
  SortableArray<T>& operator=(const SortableArray<T>& a);
  T& operator[](int index);
  int capacity() const {return cap;}
  void changeCapacity(int);
  int lsearch(const T& matchMe) const;
  int bsearch(T&) const;
  string err() const;
  void sort(int,int); 

private:
  int cap;
  int errorCode;
  T* data;
  T dummy;
  int binarySearch(T&, int, int) const;
};

template<typename T>
SortableArray<T>::SortableArray(int initCapacity)
:cap(initCapacity), errorCode(0), data(0)
{
  if(initCapacity > 0)
    data = new T[cap];
  else
    errorCode |= 1;
}

template<typename T>
SortableArray<T>::SortableArray(const SortableArray<T>& a)
:cap(a.cap), errorCode(a.errorCode), data(0)
{
  if (cap > 0)
    data = new T[cap];
  for (int i = 0; i < cap; i++)
    data[i] = a.data[i];
}

template<typename T>
SortableArray<T>::~SortableArray()
{
  delete[] data;
}

template<typename T>
SortableArray<T>& SortableArray<T>::operator=(const SortableArray<T>& a)
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

template<typename T>
T& SortableArray<T>::operator[](int index)
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

template<typename T>
void SortableArray<T>::changeCapacity(int n)
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

template <typename T>
int SortableArray<T>::lsearch(const T& matchMe) const
{
  if(data == 0) 
    return -1;
  for(int i = 0; i < cap; i++)
    if(matchMe == data[i])
      return i;
  return -1;
}

template <typename T>
int SortableArray<T>::bsearch(T& param) const
{
  return binarySearch(param, 0, cap-1);  
}

template <typename T>
int SortableArray<T>::binarySearch(T& value, int s, int e) const
{
  int m = (s + e) / 2; // the middle element 
  if (value == data[m]) // got lucky -- matches middle element 
  { 
    value = data[m]; // copy whole struct (if DataType's a struct) 
    return m; // return index of found element 
  } 
  else if (s == e) // 1-element array 
    return -1; // only element in array did not match 
  else if (value < data[m]) // look between s and m-1 
  { 
    if (s == m) return -1; // but that range is empty, no match 
    else return binarySearch(value, s, m - 1); // look in s to m-1 
  } 
  else // look between m+1 and e 
  { 
    if (m == e) return -1; // but that range is empty, no match 
    else return binarySearch(value, m + 1, e); // look in m-1 to e 
  }
}

template <typename T>
string SortableArray<T>::err() const
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

template <typename T>
void SortableArray<T>::sort(int s, int e)
{
  if (s >= e) return; // done! 
  int pivot = (s + e) / 2; 
  int l = s; // index of left-most element 
  int r = e; // index of right-most element

  while (true) 
  { 
    while(l < pivot) 
      if (data[pivot] < data[l]) break; else ++l; 
    while(pivot < r) 
      if (data[r] < data[pivot]) break; else --r; 
    if (l == r) // balanced 
    { 
      sort(s, pivot - 1); 
      sort(pivot + 1, e); 
      break; // done 
    } 
    else if (l == pivot) // swap w/pivot 
    { 
      T temp = data[pivot]; 
      data[pivot] = data[r]; 
      data[r] = temp; 
      pivot = r; 
      ++l; 
    } 
    else if (pivot == r) // swap w/pivot 
    { 
      T temp = data[pivot]; 
      data[pivot] = data[l]; 
      data[l] = temp; 
      pivot = l; 
      --r; 
    } 
    else // swap around the pivot 
    { 
      T temp = data[l]; 
      data[l] = data[r]; 
      data[r] = temp; 
      ++l; 
      --r; 
    } 
  }
}
#endif
