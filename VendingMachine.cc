#include "VendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameserver, unsigned int id,
															 unsigned int sodaCost, unsigned int maxStockPerFlavour)
  : printer(prt), nameserver(nameserver), restocking(false), buying(false), exception(false), machineid(id),
    sodacost(sodaCost), maxstock(maxStockPerFlavour) {
  stockstatus = new unsigned int[Flavours::COUNT];
	for (size_t index = 0; index < Flavours::COUNT; index++) {
		stockstatus[index] = 0;
	}
}

VendingMachine::~VendingMachine() {
  delete[] stockstatus;
  printer.print(Printer::Kind::Vending, machineid, 'F');
}

void VendingMachine::buy(Flavours flavour, WATCard &card) {
  int flavourindex = static_cast<int>(flavour);
  size_t numsoda   = stockstatus[flavourindex];
  buying = true;
  if (numsoda == 0) {
    // The specific flavour soda is not available
    uRendezvousAcceptor();
    exception = true;   
    buying = false;
    _Throw Stock();
  } else if (card.getBalance() < sodacost) {
    // Insufficient fund
    uRendezvousAcceptor();
    exception = true;
    buying = false;
    _Throw Funds();
  } else {
    // Withdrawing soda cost from the Watcard
    card.withdraw(sodacost);
    stockstatus[flavourindex] -= 1;
    printer.print(Printer::Kind::Vending, machineid, 'B', flavourindex, numsoda - 1);
  }
  buying = false;
}

unsigned int * VendingMachine::inventory() {
  printer.print(Printer::Kind::Vending, machineid, 'r');
  restocking = true;
  return stockstatus;
}

void VendingMachine::restocked() {
  printer.print(Printer::Kind::Vending, machineid, 'R');
  restocking = false;
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
    _When(!restocking && !buying)  _Accept(Stop) {
      break;
    } or _When(!restocking && !buying) _Accept(inventory) {
    } or _When(restocking)  _Accept(restocked) {
    } or _When(!restocking)  _Accept(buy) {
    }
  }
}
