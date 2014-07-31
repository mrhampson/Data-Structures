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

// Marshall Hampson
// Lab 15b
// Editor: Visual Studios 2010
// Compiler: VC++

#include <algorithm> // for remove_if
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <utility> // for pair
#include <vector>
using namespace std;

struct Vertex
{
  string name;

  bool isVisited;
  list<int> adjacentVertices;
  int prev;
  double cost;
};

pair<stack<int>, double> getShortestRoute(int iStart, int iEnd, vector<Vertex>& database)
{

  pair<stack<int>, double> result;
  queue<int> vertexQueue;

  if (iStart < 0 || iStart >= database.size() || iEnd < 0 || iEnd >= database.size()) 
    return result; // empty queue -- no such city
 
  for(int i = 0; i < database.size(); i++)
  {
    database[i].isVisited = false;
    database[i].cost = 0;
    database[i].prev = -1;
  }

  database[iStart].isVisited = true;
  vertexQueue.push(iStart);

  int currentVertex;
  list<int>::iterator it;
  while(!vertexQueue.empty())
  {
    currentVertex = vertexQueue.front();
    vertexQueue.pop();

    for(it = database[currentVertex].adjacentVertices.begin();
        it != database[currentVertex].adjacentVertices.end();
        ++it)
    {
      if(!database[*it].isVisited)
      {
        database[*it].isVisited = true;
        database[*it].cost = 1 + database[currentVertex].cost;
        database[*it].prev = currentVertex;
        vertexQueue.push(*it);
      }
      if(*it == iEnd)
        break;
    }
  }
  result.second = database[currentVertex].cost;
  while(database[currentVertex].prev != -1)
  {
    result.first.push(currentVertex);
    currentVertex = database[currentVertex].prev;
  } 
  result.first.push(iStart);
  return result;
}

int main()
{
  ifstream fin;
  fin.open("cities.txt");
  if (!fin.good()) throw "I/O error";  

  // process the input file
  vector<Vertex> database;
  while (fin.good()) // EOF loop
  {
    string fromCity, toCity;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    fin.ignore(1000, 10); // skip the line with distance
    fin.ignore(1000, 10); // skip the separator
    // eliminate whitespace
    fromCity.erase(remove_if(fromCity.begin(), fromCity.end(), ::isspace), fromCity.end());
    toCity.erase(remove_if(toCity.begin(), toCity.end(), ::isspace), toCity.end());
    // add vertices for new cities included in the edge
    int iToVertex = -1, iFromVertex = -1, i;
    for (i = 0; i < database.size(); i++) // seek "to" city
      if (database[i].name == fromCity)
        break;
    if (i == database.size()) // not in database yet
    {
      // store the vertex if it is new
      Vertex fromVertex;
      fromVertex.name = fromCity;
      database.push_back(fromVertex);
    }
    iFromVertex = i; 

    for (i = 0; i < database.size(); i++) // seek "from" city
      if (database[i].name == toCity)
        break;
    if (i == database.size()) // not in vector yet
    {
      // store the vertex if it is new
      Vertex toVertex;
      toVertex.name = toCity;
      database.push_back(toVertex);
    }
    iToVertex = i; 

    // store bi-directional edges
    database[iFromVertex].adjacentVertices.push_back(iToVertex);
    database[iToVertex].adjacentVertices.push_back(iFromVertex);
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    string fromCity, toCity;
    cout << "\nEnter the source city [blank to exit]: ";
    getline(cin, fromCity);
    if (fromCity.length() == 0) break;
    // eliminate whitespace
    fromCity.erase(remove_if(fromCity.begin(), fromCity.end(), ::isspace), fromCity.end());

    // find the from city
    int iFrom;
    for (iFrom = 0; iFrom < database.size(); iFrom++)
      if (database[iFrom].name == fromCity)
        break;

    cout << "Enter the destination city [blank to exit]: ";
    getline(cin, toCity);
    if (toCity.length() == 0) break;
    // eliminate whitespace
    toCity.erase(remove_if(toCity.begin(), toCity.end(), ::isspace), toCity.end());

    // find the destination city
    int iTo;
    for (iTo = 0; iTo < database.size(); iTo++)
      if (database[iTo].name == toCity)
        break;

    pair<stack<int>, double> result = getShortestRoute(iFrom, iTo, database);
    cout << "Total edges: " << result.second;
    while (!result.first.empty()){cout << '-' << database[result.first.top()].name; result.first.pop();} 
    cout << endl;
  }
}
