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
  list<pair<int, double> > adjacentVertices; // int for index, double for edge cost
  int prev;
  double cost;
};

struct Container // vertex container, for multiple ways to get to a vertex
{
  int vertex; // index in database array
  int prev; // index in database array
  double cost;

  bool operator<(const Container& v) const
  {
    return cost > v.cost; // i'm lying 
  }
};

pair<stack<int>, double> getCheapestRoute(int iStart, int iEnd, vector<Vertex>& database)
{
  pair<stack<int>, double> result;
  priority_queue<Container> containerQueue;

  if (iStart < 0 || iStart >= database.size() || iEnd < 0 || iEnd >= database.size()) 
    return result; // empty queue -- no such city
 
  for(int i = 0; i < database.size(); i++)
  {
    database[i].isVisited = false;
    database[i].prev = -1;
  }
  
  Container start;
  start.vertex = iStart;
  start.cost = 0;
  start.prev = -1;
  containerQueue.push(start);

  Container currentContainer, currentNeighbor;
  int currentVertex;
  list<pair<int, double> >::iterator it;
  while(!containerQueue.empty())
  {
    currentContainer = containerQueue.top();
    currentVertex = containerQueue.top().vertex;
    containerQueue.pop();
    if(database[currentVertex].isVisited)
      continue;
    database[currentVertex].isVisited = true;
    database[currentVertex].cost = currentContainer.cost;
    database[currentVertex].prev = currentContainer.prev;
    if(currentVertex == iEnd)
      break;
    for(it = database[currentVertex].adjacentVertices.begin();
        it != database[currentVertex].adjacentVertices.end();
        ++it)
    {
      currentNeighbor.vertex = it->first;
      currentNeighbor.cost = currentContainer.cost 
                             + it->second; //plus edge cost
      currentNeighbor.prev = currentVertex;
      containerQueue.push(currentNeighbor);
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
    double cost;
    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    fin >> cost; // skip the line with distance
    fin.ignore(1000,'\n');
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
    pair<int, double> temp;
    temp.first = iToVertex;
    temp.second = cost;
    database[iFromVertex].adjacentVertices.push_back(temp);
    temp.first = iFromVertex;
    database[iToVertex].adjacentVertices.push_back(temp);
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

    pair<stack<int>, double> result = getCheapestRoute(iFrom, iTo, database);
    cout << "Total miles: " << result.second;
    while (!result.first.empty()){cout << '-' << database[result.first.top()].name; result.first.pop();} 
    cout << endl;
  }
}