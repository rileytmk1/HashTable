#include <iostream>
#include <cstring>
#include "Student.h"
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

struct Node{
  Student* value;
  Node* next;
};


void insert(Student* newstudent, Node** &ht, int hash, int &size);
void print(Node** &ht, int &size);
int hashfunc(int id, int &size);
void DELETE(Node** &ht, int check_id, int &size);
void rehash(Node** &ht, int& size);
Student* random(Node** &ht, vector<string> fnames, vector<string> lnames);


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
      
      insert(student, ht, hashfunc(student->getId(), size), size); 
 
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

    else if (strcmp(input, "RANDOM") == 0){
      
    }
  }
}

int hashfunc(int id, int& size)
{
  int v = 0;
  while (id != 0){
    int r = id % 10 + '0';
    v += r;
    id = id / 10;
  }
  return (v % size);
}

void insert(Student* newstudent, Node** &ht, int hash, int &size)
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
      if (count == 3) {
	cout << "test" << endl;
	rehash(ht, size);
      }
    }
    current->next = newNode;
  }
  cout << size << endl;
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
  bool found = false;
  int hash = hashfunc(check_id, size);
  Node* current = ht[hash];
  Node* prev = NULL;
  while (current != NULL){
    if (current->value->getId() == check_id){
      if (prev == NULL){
	Node* temp = current;
	current = current->next;
	ht[hash] = current;
	delete temp;
      }
      else{
	Node* temp2 = current;
	prev->next = current->next;
	delete temp2;
      }
      found = true;
    }
      
    else{
      prev = current;
      current = current->next;
    }
      
 }
  if (found == false){
    cout << "No Student found." << endl;
  }
}

void rehash (Node** &ht, int& size)
{
  size = size * 2;
  Node** newTable = new Node*[size];
  for (int i = 0; i < size / 2; i++){
    Node* current = ht[i];
    while (current != NULL){
      insert(current->value, newTable, hashfunc(current->value->getId(), size), size);
      current = current->next;
    }
  }
  ht = newTable;
}


Student* random(Node** &ht, vector<string> fnames, vector<string> lnames)
{
  
}






