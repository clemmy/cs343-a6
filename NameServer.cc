#include "NameServer.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents)
  : printer(prt), listsize(0), nummachines(numVendingMachines), numstudents(numStudents) {
  studenttomachine = new size_t[numstudents];
  machinelist = new *VendingMachine[nummachines];
  
  // round robin distribution of student to machine
  for (int i = 0; i < numstudents; ++i) {
    studenttomachine[i] = i % numVendingMachines;
  }
}

NameServer::~NameServer() {
  delete[] studenttomachine;
  for (auto machine : machinelist) {
    machine->Stop();
    delete machine;
  }
  delete[] machinelist;
  printer.print(Printer::Kind::NameServer, 'F');
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
  printer.print(Printer::Kind::NameServer, 'R', vendingmachine->getId());

  // add to list of registered machines
  machinelist[listsize] = vendingmachine;
  listsize += 1;
}

VendingMachine * NameServer::getMachine(unsigned int id) {
  size_t index = studentmachine[id];
  printer.print(Printer::Kind::NameServer, 'N', id, machinelist[index]->getId());
  studentmachine[id] = (index + 1) % nummachines;
  return machinelist[index];
}

VendingMachine ** NameServer::getMachineList() {
  return machinelist;
}

void NameServer::Stop() {}

void NameServer::main() {
  printer.print(Printer::Kind::NameServer, 'S');
  for (;;) {
    _Accept (Stop) {
      break;
    } or _When (listsize == nummachines) _Accept(getMachine, getMachineList) {
    } or _When (listsize < nummachines) _Accept(VMregister) {
    }
  }
}
