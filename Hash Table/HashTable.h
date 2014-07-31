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

// Lab 11a
// Programmer: Marshall Hampson
// Editor: gvim
// Compiler: g++

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <algorithm>
#include <list>
using namespace std;

#include <cassert>

#define HASHTABLE_CAPACITY 1009

template <typename T>
class HashTable
{
public:
  HashTable();
  void insert(const T&);
  bool retrieve(T&) const;
  bool remove(T&);
  bool replace(const T&);
  bool first(T&);
  bool getNext(T&);
  void clear();
  int size() const {return count;}
private:
  list<T> data[HASHTABLE_CAPACITY];
  int count;
  int current;
  int capacity;
  typename list<T>::const_iterator itCurrent;
  T dummy;

  int getWrappedIndex(const T& param) const;
};

template <typename T>
HashTable<T>::HashTable()
:count(0), current(-1), capacity(HASHTABLE_CAPACITY)
{
}

template <typename T>
void HashTable<T>::insert(const T& insertMe)
{
  int WI = getWrappedIndex(insertMe);
  typename list<T>::iterator it;
  it = find(data[WI].begin(), data[WI].end(), insertMe);
  if(it != data[WI].end()) *it = insertMe;
  else
  {
    data[WI].push_back(insertMe);
    ++count;
  }
}

template <typename T>
bool HashTable<T>::retrieve(T& retrieveMe) const
{
  int i = getWrappedIndex(retrieveMe);
  typename list<T>::const_iterator it;
  it = find(data[i].begin(), data[i].end(), retrieveMe);
  if(it == data[i].end()) return false;
  retrieveMe = *it;
  return true;
}

template<typename T>
bool HashTable<T>::remove(T& removeMe)
{
  int i = getWrappedIndex(removeMe);
  typename list<T>::iterator it;
  it = find(data[i].begin(), data[i].end(), removeMe);
  if(it == data[i].end() ) return false;
  removeMe = *it;
  data[i].erase(it);
  --count;
  return true;
}

template <typename T>
bool HashTable<T>::replace(const T& replaceMe)
{
  int i = getWrappedIndex(replaceMe);
  typename list<T>::iterator it;
  it = find(data[i].begin(), data[i].end(), replaceMe);
  if(it == data[i].end()) return false;
  *it = replaceMe;
  return true;
}

template <typename T>
bool HashTable<T>::first(T& parameter)
{
  assert(current >= -1 && current < capacity);
  for (current = 0; current < capacity; current++)
  {
    if (!data[current].empty())
    {
      itCurrent = data[current].begin();
      break;
  } }
  if (current == capacity) current = -1;
  if (current == -1) return false;
  parameter = *itCurrent;
  return true;
}

template <typename T>
bool HashTable<T>::getNext(T& parameter)
{
  assert(current >= -1 && current < capacity);
  if (current == -1) return false;
  assert(!data[current].empty());
  if (++itCurrent == data[current].end())
  {
    for (current = current + 1; current < capacity; current++)
    {
      if (!data[current].empty())
      {
        itCurrent = data[current].begin();
        break;
  } } }
  if (current == capacity) current = -1;
  else parameter = *itCurrent;
  return current >= 0;
}

template<typename T>
void HashTable<T>::clear()
{
  count = 0;
  current = -1;
  for(int i = 0; i < capacity; i++)
    data[i].clear();
}


template <typename T>
int HashTable<T>::getWrappedIndex(const T& param) const
{
  int WI = param.hashCode() % capacity;
  if(WI < 0) WI += capacity;
  return WI;
}

#endif

