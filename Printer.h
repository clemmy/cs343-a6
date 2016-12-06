#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <iostream>
#include <iomanip>
using namespace std;

// object representation of data in the buffer
struct State {
  char state = 'x';
  int value1 = -1;
  int value2 = -1;  
};

_Monitor Printer {
  private:
    size_t numstudent; // number of students
    size_t nummachine; // number of machines
    size_t numcourier; // number of couriers
    size_t numobjects; // number of objects
    size_t buffercount; // current buffer index
    State *buffer; // data structure to store what to print
    void ReleaseBuffer(bool state = false); // flush buffer
  public:
    enum Kind {Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier};
    Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers);
    ~Printer();
    void print(Kind kind, char state);
    void print(Kind kind, char state, int value1);
    void print(Kind kind, char state, int value1, int value2);
    void print(Kind kind, unsigned int lid, char state);
    void print(Kind kind, unsigned int lid, char state, int value1);
    void print(Kind kind, unsigned int lid, char state, int value1, int value2);
  private:
    size_t GetRealIndex(Kind kind, int lid); // converts from enum to int
};

#endif // __PRINTER_H__
