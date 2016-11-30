#include "Printer.h"

#include <iostream>
#include <iomanip>
using namespace std;

/*
 *  Printer Constructor that sets the values and produce the header.
 */
Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers)
  : numstudent(numStudents), nummachine(numVendingMachines), numcourier(numCouriers), buffercount(0) {
  numobjects = 6 + numstudent + nummachine + numcourier;
  buffer = new State[numobjects];

  // Producing the header
  cout << setw(8);
  cout << left << "Parent";
  cout << left << "Groupoff";
  cout << left << "WATOff";
  cout << left << "Names";
  cout << left << "Truck";
  cout << left << "Plant";
  // Student(s)
  for (size_t index = 0; index < numstudent; index++) {
    cout << left << "Stud" << index;
  }
  // Machine(s)
  for (size_t index = 0; index < nummachine; index++) {
    cout << left << "Mach" << index;
  }
  // Courier(s)
  for (size_t index = 0; index < numcourier; index++) {
    cout << left << "Cour" << index;
  }
  cout << endl;
  cout << setw(8);
  // Second line with stars
  for (size_t objindex = 0; objindex < numobjects; objindex++) {
    cout << left << "*******";
  }
  cout << endl;
}

/*
 *  Destructor to produce the footer
 */
Printer::~Printer() {
  cout << "*******************" << endl;
}

/*
 *  GetRealIndex helper function calculates the real index
 */
size_t GetRealIndex(Kind kind, int lid) {
  size_t indexofkind;
  size_t studentindex = static_cast<size_t>(Kind::Student);
  switch (kind) {
    case Kind::Student:
      indexofkind = studentindex + lid;
      break;
    case Kind::Vending:
      indexofkind = studentindex + numstudent + lid;
      break;
    case Kind::Courier: 
      indexofkind = studentindex + numstudent + nummachine + lid;
      break;
    default:
      cerr << "GetRealIndex is called by a wrong object" << endl;
  }
  return indexofkind;
}

void Printer::ReleaseBuffer(bool special) {
  cout << setw(8);
  if (special) {
    for (size_t objindex = 0; objindex < numobjects; objindex++) {
      char state = buffer[objindex].state;
      if (state == 'f') {
        cout << left << "F";
      } else {
        cout << left << "...";
      }
    } 
    cout << endl;
    return;
  } 
  for (size_t objindex = 0; objindex < numobjects; objindex++) {
    State info = buffer[objindex];
    if (info.state != 'x') {
      if (info.value1 != -1 && info.value2 != -1) {
        cout << left << info.state << info.value1 << "," << info.value2;
      } else if (info.value1 != -1) {
        cout << left << info.state << info.value1;
      } else {
        cout << left << info.state;
      }
    }
    buffer[objindex].state  = 'x';
    buffer[objindex].value1 = -1;
    buffer[objindex].value2 = -1;
  }
  cout << endl;
  buffercount = 0;
}

void Printer::print(Kind kind, char state) {
  char oldstate = buffer[kind].state;
  if (state == 'F') {
    if (buffercount > 0) {
      ReleaseBuffer();
    }
    buffer[kind].state = 'f';
    ReleaseBuffer(true);
  } else if (oldstate != 'x' && oldstate != state) {
    ReleaseBuffer();
  }
  buffer[kind].state = state;
  buffercount += 1;
}

void Printer::print(Kind kind, char state, int value1) {
  print(kind, state);
  buffer[kind].value1 = value1;
}

void Printer::print(Kind kind, char state, int value1, int value2) {
  print(kind, state);
  buffer[kind].value1 = value1;
  buffer[kind].value2 = value2;
}

void Printer::print(Kind kind, unsigned int lid, char state) {
  size_t indexofkind = GetRealIndex(kind, lid);
  print(static_cast<Kind>(indexofkind), state);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1) {
  size_t indexofkind = GetRealIndex(kind, lid);
  print(static_cast<Kind>(indexofkind), state);
  buffer[indexofkind].value1 = value1;
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2) {
  size_t indexofkind = GetRealIndex(kind, lid);
  print(static_cast<Kind>(indexofkind), state);
  buffer[indexofkind].value1 = value1;
  buffer[indexofkind].value2 = value2;
}
