#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <iostream>
#include <iomanip>
using namespace std;

struct State {
  char state = 'x';
  int value1 = -1;
  int value2 = -1;  
};

_Monitor Printer {
  private:
    size_t numstudent;
    size_t nummachine;
    size_t numcourier;
    size_t numobjects;
    size_t buffercount;
    State *buffer;
    void ReleaseBuffer(bool state = false);
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
    size_t GetRealIndex(Kind kind, int lid);
};

#endif // __PRINTER_H__
