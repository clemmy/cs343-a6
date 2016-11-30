#include "VendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameserver, unsigned int id, unsigned int sodaCost,
                               unsigned int maxStockPerFlavour)
  : printer(ptr), nameserver(nameserver), machineid(id), sodacost(sodaCost), maxstock(maxStockPerFlavour) {
  stockstatus = new size_t[3];
}

VendingMachine::~VendingMachine() {
  delete[] stockstatus;
  printer.print(Printer::Kind::VendingMachine, 'F');
}

void VendingMachine::main() {
  printer.print(Printer::Kind::VendingMachine, 'S');
}

void VendingMachine::buy(Flavours flavour, WATCard &card) {

}
