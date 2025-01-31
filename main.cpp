#include <iostream>
#include <cstring>
#include "Student.h"
#include <iomanip>

using namespace std;

struct Node{
  Student* value;
  Node* next;
};


void insert(Student* newstudent, Node** &ht, int hash);
void print(Node** &ht, int &size);
int hashfunc(char* name, int &size);
void DELETE(Node** &ht, int check_id, int &size);
Node** rehash(Node** &ht, int& size);

int main()
{
  Node** ht;
  int size = 101;
  ht = new Node*[size];
  for (int i = 9; i < 101; i++){
    ht[i] = NULL;
  }
  
  char input[10];
  while (strcmp(input, "QUIT") != 0){
    cout << "ADD, PRINT, DELETE, QUIT, RANDOM." << endl;
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
      
      insert(student, ht, hashfunc(student->getFirst(), size)); 
 
    }

    else if (strcmp(input, "PRINT") == 0){
      print(ht, size);
    }

    else if (strcmp(input, "DELETE") == 0){
      int check_id;
      cout << "ID: ";
      cin >> check_id;
      cin.ignore();
      DELETE(ht, check_id, size);
    }
  }
}

int hashfunc(char* name, int& size)
{
  int v = 0;
  for (int i = 0; i < strlen(name); i++){
    v += name[i];
  }
  return (v % size);
}

void insert(Student* newstudent, Node** &ht, int hash)
{
  Node* newNode = new Node();
  newNode->value = newstudent;
  newNode->next = NULL;
  
  Node* current = ht[hash];
  if (current == NULL){
    ht[hash] = newNode;
  }
  else{
    int count = 1;
    while (current->next != NULL){
      current = current->next;
      count++;
    }
    current->next = newNode;
  }
}

void print(Node** &ht, int &size){
  for (int i = 0; i < size; i++){
    Node* current = ht[i];
    while (current != NULL){
      cout << current->value->getFirst() << " " << current->value->getLast() << ", " << current->value->getId() << ", " << fixed << setprecision(2) << current->value->getGPA() << endl;
      current = current->next;
    }
    
  }
}

void DELETE(Node** &ht, int check_id, int &size)
{
  for (int i = 0; i < size; i++){
    Node* current = ht[i];
    Node* prev = NULL;
    while (current != NULL){
      if (prev == NULL && current->value->getId() == check_id){
	Node* temp = current;
	current = current->next;
	ht[i] = current;
	delete temp;
      }
      else if (current->value->getId() == check_id){
	Node* temp2 = current;
	prev->next = current->next;
	delete temp2;
      }
      else{
	prev = current;
	current = current->next;
      }
    }
      
  }
}

void rehash (Node** &ht, int& size)
{
  
}









