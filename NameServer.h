#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "Printer.h"
#include "VendingMachine.h"

_Task VendingMachine;

_Task NameServer {
  private:
    Printer &printer;
    size_t listsize; // number of machines registered
    size_t nummachines; // total number of machines
    size_t numstudents; // number of students
    size_t *studenttomachine; // maps student to their currently assigned machine
    VendingMachine **machinelist; // array of all the vending machines
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void Stop();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif // __NAMESERVER_H__
