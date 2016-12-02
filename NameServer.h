#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "Printer.h"
#include "VendingMachine.h"

_Task VendingMachine;

_Task NameServer {
  private:
    Printer &printer;
    size_t listsize;
    size_t nummachines;
    size_t numstudents;
    size_t *studenttomachine;
    VendingMachine **machinelist;
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
