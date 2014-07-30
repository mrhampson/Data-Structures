// Lab 10c
// Programmer: Marshall Hampson
// Editor/Compiler: Visual Studios Ultimate 2012

#include <iostream> // for cout and endl
#include <string> // for string
using namespace std;

#include <cassert> // for assert
#include <cmath> // for log and pow
#include <cstdlib> //for srand() and rand()
#include <ctime> // for clock() and clock_t

#include "LinkedList.h"

int main()
{
  cout << "Lab 10c\nProgrammer: Marshall Hampson" << endl << endl;

  // problem setup goes here
  srand(time(0)); rand();
  int length;
  double getNextValue;

  // programmer customizations go here
  int n = 5000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  string bigOh = "O(1)"; // YOUR PREDICTION: O(1), O(log n), O(n), O(n log n), or O(n squared)
  int REPS = 10000000; // for timing fast operations, use REPS up to 100th of the starting n

  int elapsedTimeTicksNorm = 0;
  double expectedTimeTicks = 0;
  
  cout << "operator[] assignment at zeroth index, O(1)" << endl;
  for (int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    // more problem setup goes here -- the stuff not timed
    LinkedList<double> list;
    for(int i = 0; i < n; ++i)
      list.insert(rand());

    // assert that n is the size of the data structure
    assert(list.length() == n); 

    // start the timer, do something, and stop the timer
    clock_t startTime = clock();
    // do something where n is the "size" of the problem
    for(int reps = 0; reps < REPS; reps++)
      list[0] = 2.345;
    clock_t endTime = clock(); 

    // validation block -- assure that process worked
    assert(list[0] >= 2.344999 && list[0] <= 2.345001);
    // compute timing results
    long elapsedTimeTicks = (long)(endTime - startTime);
    double factor = pow(2.0, cycle);
    if (cycle == 0)
      elapsedTimeTicksNorm = elapsedTimeTicks;
    else if (bigOh == "O(1)")
      expectedTimeTicks = elapsedTimeTicksNorm;
    else if (bigOh == "O(log n)")
      expectedTimeTicks = log(double(n)) / log(n / factor) * elapsedTimeTicksNorm;
    else if (bigOh == "O(n)")
      expectedTimeTicks = factor * elapsedTimeTicksNorm;
    else if (bigOh == "O(n log n)")
      expectedTimeTicks = factor * log(double(n)) / log(n / factor) * elapsedTimeTicksNorm;
    else if (bigOh == "O(n squared)")
      expectedTimeTicks = factor * factor * elapsedTimeTicksNorm;

    // reporting block
    cout << elapsedTimeTicks;;
    if (cycle == 0) cout << " (expected " << bigOh << ')';
    else cout << " (expected " << expectedTimeTicks << ')';
    cout << " for n=" << n << endl;
  }

  cout << endl << "operator[] assignment at 100th index, O(1)" << endl;

  // programmer customizations go here
  n = 5000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  bigOh = "O(1)"; // YOUR PREDICTION: O(1), O(log n), O(n), O(n log n), or O(n squared)
  //const int REPS = 10000000; // for timing fast operations, use REPS up to 100th of the starting n

  for (int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    // more problem setup goes here -- the stuff not timed
    LinkedList<double> list;
    for(int i = 0; i < n; ++i)
      list.insert(rand());

    // assert that n is the size of the data structure
    assert(list.length() == n); 

    // start the timer, do something, and stop the timer
    clock_t startTime = clock();
    // do something where n is the "size" of the problem
    for(int reps = 0; reps < REPS; reps++)
      list[100] = 2.345;
    clock_t endTime = clock(); 

    // validation block -- assure that process worked
    assert(list[100] >= 2.344999 && list[100] <= 2.345001);
    // compute timing results
    long elapsedTimeTicks = (long)(endTime - startTime);
    double factor = pow(2.0, cycle);
    if (cycle == 0)
      elapsedTimeTicksNorm = elapsedTimeTicks;
    else if (bigOh == "O(1)")
      expectedTimeTicks = elapsedTimeTicksNorm;
    else if (bigOh == "O(log n)")
      expectedTimeTicks = log(double(n)) / log(n / factor) * elapsedTimeTicksNorm;
    else if (bigOh == "O(n)")
      expectedTimeTicks = factor * elapsedTimeTicksNorm;
    else if (bigOh == "O(n log n)")
      expectedTimeTicks = factor * log(double(n)) / log(n / factor) * elapsedTimeTicksNorm;
    else if (bigOh == "O(n squared)")
      expectedTimeTicks = factor * factor * elapsedTimeTicksNorm;

    // reporting block
    cout << elapsedTimeTicks;;
    if (cycle == 0) cout << " (expected " << bigOh << ')';
    else cout << " (expected " << expectedTimeTicks << ')';
    cout << " for n=" << n << endl;
  }

  cout << endl << "iteration from first to last using operator[], O(n)" << endl;

  // programmer customizations go here
  n = 1000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  bigOh = "O(n)"; // YOUR PREDICTION: O(1), O(log n), O(n), O(n log n), or O(n squared)
  REPS = 10000; // for timing fast operations, use REPS up to 100th of the starting n

  for (int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    // more problem setup goes here -- the stuff not timed
    LinkedList<double> list;
    for(int i = 0; i < n; ++i)
      list.insert(rand());

    // assert that n is the size of the data structure
    assert(list.length() == n); 

    // start the timer, do something, and stop the timer
    clock_t startTime = clock();
    // do something where n is the "size" of the problem
    for(int j = 0; j < REPS; ++j)
      for (int i = 0; i < list.length(); list[i], i++);
    clock_t endTime = clock(); 

    // validation block -- assure that process worked
    assert(list.getNext(getNextValue) == false);
    // compute timing results
    long elapsedTimeTicks = (long)(endTime - startTime);
    double factor = pow(2.0, cycle);
    if (cycle == 0)
      elapsedTimeTicksNorm = elapsedTimeTicks;
    else if (bigOh == "O(1)")
      expectedTimeTicks = elapsedTimeTicksNorm;
    else if (bigOh == "O(log n)")
      expectedTimeTicks = log(double(n)) / log(n / factor) * elapsedTimeTicksNorm;
    else if (bigOh == "O(n)")
      expectedTimeTicks = factor * elapsedTimeTicksNorm;
    else if (bigOh == "O(n log n)")
      expectedTimeTicks = factor * log(double(n)) / log(n / factor) * elapsedTimeTicksNorm;
    else if (bigOh == "O(n squared)")
      expectedTimeTicks = factor * factor * elapsedTimeTicksNorm;

    // reporting block
    cout << elapsedTimeTicks;;
    if (cycle == 0) cout << " (expected " << bigOh << ')';
    else cout << " (expected " << expectedTimeTicks << ')';
    cout << " for n=" << n << endl;
  }

  cout << endl << "length, O(1)" << endl;

  // programmer customizations go here
  n = 500000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  bigOh = "O(1)"; // YOUR PREDICTION: O(1), O(log n), O(n), O(n log n), or O(n squared)
  REPS = 10000000; // for timing fast operations, use REPS up to 100th of the starting n

  for (int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    // more problem setup goes here -- the stuff not timed
    LinkedList<double> list;
    for(int i = 0; i < n; ++i)
      list.insert(rand());

    // assert that n is the size of the data structure
    assert(list.length() == n); 

    // start the timer, do something, and stop the timer
    clock_t startTime = clock();
    // do something where n is the "size" of the problem
    for(int j = 0; j < REPS; ++j)
      length = list.length();
    clock_t endTime = clock(); 

    // validation block -- assure that process worked
    
    // compute timing results
    long elapsedTimeTicks = (long)(endTime - startTime);
    double factor = pow(2.0, cycle);
    if (cycle == 0)
      elapsedTimeTicksNorm = elapsedTimeTicks;
    else if (bigOh == "O(1)")
      expectedTimeTicks = elapsedTimeTicksNorm;
    else if (bigOh == "O(log n)")
      expectedTimeTicks = log(double(n)) / log(n / factor) * elapsedTimeTicksNorm;
    else if (bigOh == "O(n)")
      expectedTimeTicks = factor * elapsedTimeTicksNorm;
    else if (bigOh == "O(n log n)")
      expectedTimeTicks = factor * log(double(n)) / log(n / factor) * elapsedTimeTicksNorm;
    else if (bigOh == "O(n squared)")
      expectedTimeTicks = factor * factor * elapsedTimeTicksNorm;

    // reporting block
    cout << elapsedTimeTicks;;
    if (cycle == 0) cout << " (expected " << bigOh << ')';
    else cout << " (expected " << expectedTimeTicks << ')';
    cout << " for n=" << n << endl;
  }

  cout << endl << "Program has finished. Press ENTER to continue." << endl;
  cin.get();
}