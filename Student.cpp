#include "Student.h"

#include <iostream>
#include <cstring>

using namespace std;

Student::Student() {
  
}

char* Student::getFirst(){
  return first;
}

char* Student::getLast(){
  return last;
}

int& Student::getId(){
  return id;
}

double& Student::getGPA(){
  return GPA;
}
