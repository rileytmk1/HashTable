#include <iostream>
#include <cstring>
#include "Student.h"
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

//Node struct
struct Node{
  Student* value;
  Node* next;
};


void insert(Student* newstudent, Node** &ht, int hash, int &size);
void print(Node** &ht, int &size);
int hashfunc(int id, int &size);
void DELETE(Node** &ht, int check_id, int &size);
void rehash(Node** &ht, int& size);
void random(Node** &ht, int &size, vector<string> fnames, vector<string> lnames, int n, int &id);


int main()
{
  Node** ht;
  //initialize size of hash table
  int size = 101;
  //initialize id to be incremented for random function
  int id = 400000;
  ht = new Node*[size];
  for (int i = 0; i < 101; i++){
    ht[i] = NULL;
  }
  
  char input[10];
  while (strcmp(input, "QUIT") != 0){
    cout << "ADD, PRINT, DELETE, QUIT, RANDOM." << endl;
    cin.get(input,10);
    cin.get();
    
    if (strcmp(input, "ADD") == 0){
      // input student values
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
      cout << hashfunc(student->getId(), size) << endl;
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
      //input names from text files into vectors
      vector<string> fnames;
      vector<string> lnames;
      
      ifstream f("firstnames.txt");
      string s;
      while(getline(f, s)){
	fnames.push_back(s);
      }

      ifstream f2("lastnames.txt");
      string s2;
      while(getline(f2,s2)){
	lnames.push_back(s2);
      }
      int n;
      cout << "How many students? ";
      cin >> n;
      cin.ignore();
      random(ht, size, fnames, lnames, n, id);
    }
  }
}

// pre-existing hash formula based on the student's id
// alters based on size of the table
int hashfunc(int id, int& size)
{
  int v = 0;
  while (id != 0){
    int r = id % 10;
    v = (v* 31 + r) % size;
    id = id / 10;
  }
  v = (v + (size*3)) % size;
  return v;
}

void insert(Student* newstudent, Node** &ht, int hash, int &size)
{

  // create node for new student
  Node* newNode = new Node();
  newNode->value = newstudent;
  newNode->next = NULL;

  // set current to head node of index hash
  Node* current = ht[hash];

  //if linked list is empty
  if (current == NULL){
    ht[hash] = newNode;
  }

  //else traverse through the linked list until the end
  else{
    int count = 1;
    while (current->next != NULL){
      current = current->next;
      count++;
      // Three nodes in the linked list means 3 collisions
      if (count == 3) {
	//rehash
	rehash(ht, size);
	hash = hashfunc(newstudent->getId(), size);
	insert(newstudent, ht, hash, size);

      }
    }
    current->next = newNode;
  }

}

void print(Node** &ht, int &size){
  // iterate through the table
  for (int i = 0; i < size; i++){
    Node* current = ht[i];
    //traverse through each linked list and print all the nodes
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
  //set current to head node at index hash
  Node* current = ht[hash];
  Node* prev = NULL;
  //traverse the linked list to match the id
  while (current != NULL){
    if (current->value->getId() == check_id){
      if (prev == NULL){ // current is the head node
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
      
    else{ // move prev and current to next node
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
  //double the size of table
  size = size * 2;
  //create a new table with new size and initialize values to null
  Node** newTable = new Node*[size];
  for (int i = 0; i < size; i++){
    newTable[i] == NULL;
  }

  //iterate through old table and insert values into new table with new hash.
  for (int i = 0; i < size / 2; i++){
    Node* current = ht[i];
    while (current != NULL){
      insert(current->value, newTable, hashfunc(current->value->getId(), size), size);
      current = current->next;
    }
  }
  delete[] ht;
  ht = newTable;
}


void random(Node** &ht, int& size, vector<string> fnames, vector<string> lnames, int n, int &id)
{
  srand(time(0));
  int c = 0;
  
  while (c != n){
    int random = rand() % fnames.size(); // get random index between 0 and the size of the vector
    double decimal = static_cast<double>(rand()) / RAND_MAX; //generate a random decimal
    double gpa = 4 * decimal; // get value between 0 and 4
    gpa = round(gpa * 100) / 100; //round to 2 places
    
    Student* nstudent = new Student();
    nstudent->getId() = id;
    nstudent->getGPA() = gpa;
    strcpy(nstudent->getFirst(), fnames[random].c_str());
    strcpy(nstudent->getLast(), lnames[random].c_str());
    insert(nstudent, ht, hashfunc(nstudent->getId(), size), size);
    
    id++; // increment id
    c++; // keep track of students added
    fnames.erase(fnames.begin() + random);
    lnames.erase(lnames.begin() + random);
  }

  
}







