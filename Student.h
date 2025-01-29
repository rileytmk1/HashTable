#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

using namespace std;

class Student {
 public:
  Student();
  char* getFirst();
  char* getLast();
  int& getId(); 
  double& getGPA();
 private:
  char first [50];
  char last[50];
  int id;
  double GPA;
};

#endif
