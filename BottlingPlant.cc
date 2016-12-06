#include "BottlingPlant.h"
#include "RNG.h"
#include "VendingMachine.h"

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                             unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                             unsigned int timeBetweenShipments) :
  printer(prt),
  nameserver(nameServer),
  nummachines(numVendingMachines),
  maxshipstock(maxShippedPerFlavour),
  maxstock(maxStockPerFlavour),
  shippingtime(timeBetweenShipments),
  truck(nullptr),
  closed(false) {
  stock = new size_t[VendingMachine::Flavours::COUNT];
  for (size_t i = 0; i < VendingMachine::Flavours::COUNT; ++i) {
    stock[i] = 0;
  }
}

BottlingPlant::~BottlingPlant() {
  delete[] stock;
  if (truck != nullptr) {
    delete truck; 
  }

  printer.print(Printer::Kind::BottlingPlant, 'F');
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
  if (closed) {
    uRendezvousAcceptor();
    _Throw Shutdown();
  }

  // transfer stock to cargo and reset stock
  for (size_t i = 0; i < VendingMachine::Flavours::COUNT; i++) {
    size_t numdrink = stock[i];
    cargo[i] = numdrink;
    stock[i] = 0;
  }
  printer.print(Printer::Kind::BottlingPlant, 'P');
}


void BottlingPlant::main() {
  printer.print(Printer::Kind::BottlingPlant, 'S');
  truck = new Truck(printer, nameserver, *this, nummachines, maxstock); 
  
  for (;;) {
    //produce soda
    yield(shippingtime);

    int produceCount = 0;
    for (size_t i = 0; i < VendingMachine::Flavours::COUNT; ++i) {
      stock[i] = rng(maxshipstock);
      produceCount += stock[i];
    } 
    printer.print(Printer::Kind::BottlingPlant, 'G', produceCount);

    _Accept(~BottlingPlant) {
      closed = true; // set closed flag
      _Accept(getShipment); // wait for truck to arrive
      break;
    } or _When(!closed) _Accept(getShipment); 

    //wait for truck to come pick up
    _Accept(getShipment);
  }
}
