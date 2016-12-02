#include "VendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameserver, unsigned int id,
															 unsigned int sodaCost, unsigned int maxStockPerFlavour)
  : printer(prt), nameserver(nameserver), restocking(false), buying(false), machineid(id), sodacost(sodaCost), maxstock(maxStockPerFlavour) {
  stockstatus = new size_t[3];
	for (size_t index = 0; index < 3; index++) {
		stockstatus = 0;
	}
}

VendingMachine::~VendingMachine() {
  delete[] stockstatus;
  printer.print(Printer::Kind::Vending, machineid, 'F');
}

void VendingMachine::buy(Flavours flavour, WATCard &card) {
  int flavourindex = static_cast<int>(flavour);
  size_t numsoda   = stockstatus[flavourindex];
  if (numsoda == 0) {
    // The specific flavour soda is not available
    _Throw Funds();
  } else if (card.getBalance() < sodacost) {
    // Insufficient fund
    _Throw Stock();
  } else {
    // Withdrawing soda cost from the Watcard
    card.withdraw(sodacost);
    stockstatus[flavourindex] -= 1;
    printer.print(Printer::Kind::Vending, machineid, 'B', flavourindex, numsoda - 1);
  }
}

unsigned int * VendingMachine::inventory() {
  printer.print(Printer::Kind::Vending, machineid, 'r');
  restocking = true;
	return reinterpret_cast<unsigned int *>(stockstatus);
}

void VendingMachine::restocked() {
  printer.print(Printer::Kind::Vending, machineid, 'R');
  restocking = bool();
}

unsigned int VendingMachine::cost() {
	return sodacost;
}

unsigned int VendingMachine::getId() {
	return machineid;
}

void VendingMachine::Stop() {}

void VendingMachine::main() {
  printer.print(Printer::Kind::Vending, machineid, 'S');
	// Registering itself to the Name Server
	nameserver.VMregister(this);

  for (;;) {
    _When(!restocking && !buying)  _Accept(Stop, inventory) {
      break;
    } or _When(restocking)  _Accept(restocked) {
    } or _When(!restocking)  _Accept(buy) {
    }
  }
}
