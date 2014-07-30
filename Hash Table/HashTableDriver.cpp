// Lab 11a
// Programmer: Marshall Hampson
// Editor: gvim
// Compiler: g++

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <cassert>
#include <cstring>

#include "HashTable.h"
#include "HashTable.h" //ifndef testing

struct Course
{
  string term;
  int section;
  string course;
  string instructor;
  string whenWhere;
  string subjectCode;

  bool operator==(const Course&) const;
  int hashCode() const;
};

bool Course::operator==(const Course& param) const
{
  if(term == param.term && section == param.section)
    return true;
  else
    return false;
}

int Course::hashCode() const
{
  int hashCode = 0;
  for(int i = 0; i < term.length(); ++i)
    hashCode += int(term[i]);
  hashCode += section;
  return hashCode;
}

int main()
{
  cout << "Lab 11a\nProgrammer: Marshall Hampson" << endl;

  HashTable<Course> table;
  Course a,b,temp;

  a.section = 1234;
  a.term = "SP 2013";
  table.insert(a); // test insert()
  assert(table.size() == 1);  //test size()
  assert(table.retrieve(a) == true); //test retrieve

  b = a;
  a.course = "Jazz";
  table.replace(a); //test replace()
  table.retrieve(b);
  assert(b == a);

  b.section = 2345;
  b.term = "FA 2013";
  b.course = "OOP";
  table.insert(b);

  table.first(temp); // test first()
  assert(temp == a);
  table.getNext(temp);  // test getNext()
  assert(temp == b);

  // object copy testing assignment UPON declaration
  {
    const HashTable<Course> copy = table;
    assert(copy.size() == 2);
    assert(copy.retrieve(a) == true);
  }

  // object copy testing assignment AFTER declaration
  {
    HashTable<Course> copy; copy = table;
    temp.section = 1432;
    assert(copy.remove(temp) == false);
    assert(copy.size() == 2);
    assert(copy.retrieve(a) == true);
  }

  table.clear();
  assert(table.retrieve(b) == false);

  HashTable<Course> courses;
  int duplicateCount = 0;

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  // read the input file
  for(int i = 0; i < 100; ++i)
  {
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue;

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line
    const string subjectCode(course.begin(), course.begin() + course.find('-'));
    int sectionNum = atoi(section.c_str());

    temp.term = term;
    temp.section = sectionNum;
    temp.course = course;
    temp.instructor = instructor;
    temp.whenWhere = whenWhere;
    temp.subjectCode = subjectCode;

    courses.insert(temp);
  }
  fin.close();
  assert(courses.size() == 98);

  fin.open("dvc-schedules.txt");
  // read the input file
  for(int i = 0; i < 100; ++i)
  {
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue;

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line
    const string subjectCode(course.begin(), course.begin() + course.find('-'));
    int sectionNum = atoi(section.c_str());

    temp.term = term;
    temp.section = sectionNum;
    temp.course = course;
    temp.instructor = instructor;
    temp.whenWhere = whenWhere;
    temp.subjectCode = subjectCode;

    assert(courses.retrieve(temp) == true);
    courses.remove(temp);
    assert(courses.retrieve(temp) == false);
  }
  fin.close();
}

