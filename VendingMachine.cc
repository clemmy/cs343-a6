#include "VendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameserver, unsigned int id,
															 unsigned int sodaCost, unsigned int maxStockPerFlavour)
  : printer(ptr), nameserver(nameserver), machineid(id), sodacost(sodaCost), maxstock(maxStockPerFlavour) {
  stockstatus = new size_t[3];
	for (size_t index = 0; index < 3; index++) {
		stockstatus = 0;
	}

}

VendingMachine::~VendingMachine() {
  delete[] stockstatus;
  printer.print(Printer::Kind::VendingMachine, 'F');
}

void VendingMachine::buy(Flavours flavour, WATCard &card) {

}

unsigned int * VendingMachine::inventory() {
	return stockstatus;
}

void VendingMachine::restocked() {

}

unsigned int VendingMachine::cost() {
	return sodacost;
}

unsigned int VendingMachine::getId() {
	return machineid;
}

void VendingMachine::main() {
  printer.print(Printer::Kind::VendingMachine, 'S');
	// Registering itself to the Name Server
	nameserver.register(this);

}
