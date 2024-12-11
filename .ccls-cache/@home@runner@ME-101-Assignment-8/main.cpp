// Uwaterloo Mechanical Engineering 101 Final Assignment

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

const int ADD_REMOVE = 25;
const int MAX_SIZE = 50;

//Part B
void originalParking(ifstream &fin, bool staffStudent[MAX_SIZE],
                     string nameArr[MAX_SIZE]) 
{
  bool staff = 0; // 1 is staff, 0 is student
  string name = "";
  int parkingSpace = 0;
  for (int count = 0; count < 50; count++) {
    fin >> staff >> name >> parkingSpace;
    staffStudent[parkingSpace - 1] = staff;
    nameArr[parkingSpace - 1] = name;
  }
}

// PART C
void read_file(ifstream &fin, bool staff[ADD_REMOVE], string name[ADD_REMOVE])
{
  for (int index = 0; index < 25; index++) {
    fin >> staff[index] >> name[index];
  }
}

// PART D
void deletePeople(string removeName, bool status[MAX_SIZE],
                  string name[MAX_SIZE]) {
  for (int index = 0; index < MAX_SIZE; index++) 
  {
    if (removeName == name[index]) 
    {
      name[index] = "";
      status[index] = 0;
    }
  }
}
//PART E
int lowest_parking_space(bool status, string name[MAX_SIZE],
                         bool staffStudent[MAX_SIZE]) 
{
  // find first parking spot that is open
  int space = 0;
  if (status == 0) 
  {
    space = 25;
    for (int index = space; index < MAX_SIZE; index++)
    {
      if (name[index] == "") 
      {
        staffStudent[index] = 0;
        return index;
      }
    }
  }
  else 
  {
    space = 0;
    for (int index = space; index < MAX_SIZE; index++) 
    {
      if (name[index] == "") 
      {
        staffStudent[index] = 1;
        return index;
      }
    }
  }
  return -20;
}
//PART F/G
bool addPeople(string parkingSpaces[MAX_SIZE], string tempName, bool status1,
               bool staffStudent[MAX_SIZE]) 
{
  int spaceNum = lowest_parking_space(status1, parkingSpaces, staffStudent);
  if (spaceNum >= 0) 
  {
    parkingSpaces[spaceNum] = tempName;
    return true;
  } 
  else if (tempName != "") 
  {
    cout << endl << tempName << " did not find a parking space" << endl;
    return false;
  }
  return false;
}
//PARTT F/G
void rearrange(string name[MAX_SIZE], bool status[MAX_SIZE]) 
{
  string deleteName = "";
  for (int index = 25; index < MAX_SIZE; index++) 
  {
    if (status[index] == 1) 
    {
      deleteName = name[index];
      deletePeople(deleteName, 0, name);
      bool spaceOrNot = addPeople(name, deleteName, 1, status);
      status[index] = 0;
    }
  }
}

int main() {

  ifstream fin_current("parking_current.txt");
  ifstream fin_add("parking_add.txt");
  ifstream fin_remove("parking_remove.txt");

  ofstream fout("parking_update.txt");

  if (!fout) 
  {
    cout << "Failed to create output file" << endl;
    return EXIT_FAILURE;
  }

  if (!fin_current || !fin_add || !fin_remove) 
  {
    cout << "File failed to open";
    return EXIT_FAILURE;
  }

  bool staffStudent[MAX_SIZE] = {0};
  string name1[MAX_SIZE];
  for (int index = 0; index < MAX_SIZE; index++) {
    name1[index] = "";
  }

  bool staff[ADD_REMOVE] = {0};
  string name2[ADD_REMOVE];

  originalParking(fin_current, staffStudent, name1);

  fout << "The initial state of parking lot" << endl;
  fout << setw(5) << "SPOT#" <<setw(15) <<"STATUS" << setw(15) << "NAME" << endl <<       endl;
  
  for (int i = 0; i < 50; i++) 
  {
    fout << setw(5) << i + 1 << ".  " << setw(10) << staffStudent[i] << setw(25) <<         name1[i] << endl;
  }

  read_file(fin_remove, staff, name2);

  for (int index = 0; index < 25; index++) 
  {
    string tempName = name2[index];
    deletePeople(tempName, staffStudent, name1);
  }

  rearrange(name1, staffStudent);

  read_file(fin_add, staff, name2);

  for (int index = 0; index < 25; index++) 
  {
    string tempName = name2[index];
    bool status = staff[index];
    bool added = addPeople(name1, tempName, status, staffStudent);
  }

  fout << "The final state of parking lot" << endl;
  fout << setw(5) << "SPOT#" <<setw(15) <<"STATUS" << setw(15) << "NAME" << endl <<       endl;
  
  for (int i = 0; i < 50; i++) 
  {
    fout << setw(5) << i + 1 << ".  " << setw(10) << staffStudent[i] << setw(20) <<         name1[i] << endl;
  }

  fin_current.close();
  fin_add.close();
  fin_remove.close();
  fout.close();

  return EXIT_SUCCESS;
}

/* Console output:
Lamarr_H did not find a parking space

Fleming_San did not find a parking space

*/