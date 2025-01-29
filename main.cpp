#include <iostream>
#include <cstring>
#include <Student.h>

using namespace std;

void insert(Student* newstudent, Node** &ht);
int hashfunc(char* name, int slots);

struct Node{
  Student* value;
  Node* next;
}

int main()
{
  Node** ht;
  ht = new Node*[101];
  
  char input[10];
  while (strcmp(input, "QUIT") != 0){
    cin.get(input,10);
    cin.get();
    
    if (strcmp(input, "ADD") == 0){
      char fname[50];
      char lname[50];
      int id;
      double gpa;

      cout << "First Name: ";
      
      cin.get(fname, 50);
      cin.get();

      cout << "Last Name: ";
      cin.get(lname, 50);
      cin.get();

      cout << "ID: ";
      cin >> id;
      cin.ignore();

      cout << "GPA: ";
      cin >> gpa;
      cin.ignore();

      Student* student = new Student();
      student->getId() = id;
      student->getGPA() = gpa;
      strcpy(student->getFirst(), fname);
      strcpy(student->getLast(), lname);
      
      insert(student, ht, hashfunc(student->getFirst(), 101)); 
      
    }

    else if (strcmp(input, "PRINT") == 0){
      
    }

    else if (strcmp(input, "DELETE") == 0){
      
    }
  }
}

int hashfunc(char* name, int slots)
{
  int v = 0;
  for (int i = 0; i < strlen(name); i++){
    v += name[i];
  }
  return v % slots;
}

void insert(Student* newstudent, Node** &ht, int hash)
{
  current = ht[hash];
  while (current != NULL){
    current = current->next;
  }
  current->next->value = newstudent;
}
