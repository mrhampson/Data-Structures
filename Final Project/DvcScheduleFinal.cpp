// Marshall Hampson
// Term Project
// Editor: gvim
// Compiler: g++

#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <string>
using namespace std;

int main()
{
  // variables
  ifstream fin;
  map<string, map<string, int> > subjects;
  set<string> addedCourses;
  map<string, map<string, int> >::iterator it1;
  map<string, int>::iterator it2;
  string line;
  string subjectCode;
  string course;
  string termAndSection;
  size_t start, dashPos, end;
  // open the "dvc-schedule.txt" file
  fin.open("dvc-schedule.txt");
  if(!fin.good())
    throw "I/O error";
  // read the input file
  while(fin.good())
  {
    // parse the line
    getline(fin, line);
    dashPos = line.find('-'); //find the first ocurrence of a '-'
    if(dashPos == string::npos) 
      continue; //if no '-' this line is invalid
    start = line.find_last_of('\t', dashPos) + 1;
    termAndSection = line.substr(0, start-1);
    end = line.find_first_of('\t', dashPos);
    subjectCode = line.substr(start, dashPos-start);
    course = line.substr(start, end-start);
    if(addedCourses.find(termAndSection) == addedCourses.end()) // only add non duplicates
    {
      // add subject/corse to the map
      ++subjects[subjectCode][course];
      // add to the set of added courses
      addedCourses.insert(termAndSection);
    }
  }
  // print out the subject/courses 
  for(it1 = subjects.begin(); it1 != subjects.end(); ++it1)
  {
    cout.setf(ios::left, ios::adjustfield);
    cout << it1->first << ", " << it1->second.size();
    it1->second.size() > 1 ? cout << " courses" : cout << " course";
    cout << endl << "------------------------------" << endl;
    for(it2 = subjects[it1->first].begin(); it2 != subjects[it1->first].end(); ++it2)
    {
      cout << "  " << setw(15) << it2->first << setw(5) << it2->second;
      it2->second > 1 ? cout << " classes" : cout << " class";
      cout << endl;
    }
    cout << "----------------------------------------------------------------"
      << endl;
  }
  //close the file
  fin.close();
}