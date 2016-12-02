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
  cout << setw(8);
  cout << left << "Groupoff";
  cout << setw(8);
  cout << left << "WATOff";
  cout << setw(8);
  cout << left << "Names";
  cout << setw(8);
  cout << left << "Truck";
  cout << setw(8);
  cout << left << "Plant";
  // Student(s)
  for (size_t index = 0; index < numstudent; index++) {
    cout << setw(8);
    cout << left << "Stud" + to_string(index);
  }
  // Machine(s)
  for (size_t index = 0; index < nummachine; index++) {
    cout << setw(8);
    cout << left << "Mach" + to_string(index);
  }
  // Courier(s)
  for (size_t index = 0; index < numcourier; index++) {
    cout << setw(8);
    cout << left << "Cour" + to_string(index);
  }
  cout << endl;
  // Second line with stars
  for (size_t objindex = 0; objindex < numobjects; objindex++) {
    cout << setw(8);
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
size_t Printer::GetRealIndex(Printer::Kind kind, int lid) {
  size_t indexofkind;
  size_t studentindex = static_cast<size_t>(Printer::Kind::Student);
  switch (kind) {
    case Printer::Kind::Student:
//      cout << "Student called Index";
      indexofkind = studentindex + lid;
      break;
    case Printer::Kind::Vending:
//      cout << "Machine called Index"; 
      indexofkind = studentindex + numstudent + lid;
      break;
    case Printer::Kind::Courier: 
//      cout << "Courier called Index";
      indexofkind = studentindex + numstudent + nummachine + lid;
      break;
    default:
      indexofkind = -1;
      cerr << "GetRealIndex is called by a wrong object" << endl;
  }
//  cout << "studentindex : " << studentindex << endl;
//  cout << "caller obj id  : " << lid << endl;
//  cout << "returning index : " << indexofkind << endl;
  return indexofkind;
}

void Printer::ReleaseBuffer(bool special) {
  if (special) {
    for (size_t objindex = 0; objindex < numobjects; objindex++) {
      cout << setw(8);
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
//    cout << setw(8);
    if (info.state != 'x') {
      cout << setw(8);
      if (info.value1 != -1 && info.value2 != -1) {
        cout << left << info.state + to_string(info.value1) + "," + to_string(info.value2);
      } else if (info.value1 != -1) {
        cout << left << info.state + to_string(info.value1);
      } else {
        cout << left << info.state;
      }
    } else {
//      cout << setw(8);
      cout << left << "\t";
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
