#include "Truck.h"
#include "RNG.h"
#include "VendingMachine.h"

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
  unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
  printer(prt),
  nameserver(nameServer),
  plant(plant),
  nummachines(numVendingMachines),
  maxstockperflavour(maxStockPerFlavour) {
  numflavours = VendingMachine::Flavours::COUNT;
  cargo = new unsigned int[numflavours];
  for (size_t index = 0; index < numflavours; index++) {
    cargo[index] = 0;
  }
}

Truck::~Truck() {
  delete[] cargo;
  printer.print(Printer::Kind::Truck, 'F');
}

void Truck::Stop() {}

void Truck::main() {
  printer.print(Printer::Kind::Truck, 'S');
  try {
    // get machine list from name server
    VendingMachine **machines = nameserver.getMachineList();
    size_t lastvendingmachine = 0;

    for (;;) {
      // Tom Hortons coffee is the best
      yield(rng(1, 10));
      
      // stock up truck with cargo from the factory
      plant.getShipment(cargo);
      size_t shippedproduct = 0;
      for (size_t index = 0; index < VendingMachine::Flavours::COUNT; index++) {
        shippedproduct += cargo[index];
      }
      printer.print(Printer::Kind::Truck, 'P', shippedproduct);

      // stock up vending machines
      size_t remaining = shippedproduct;
      size_t travel = 0;

      // Begin delivering to the vendingmachines with two stopping conditions
      while (remaining > 0 && travel < nummachines) {
        VendingMachine *machine = machines[lastvendingmachine];
        printer.print(Printer::Kind::Truck, 'd', machine->getId(), remaining);
        unsigned int *machinestock = machine->inventory();
        size_t missing = 0; // Counting how many drinks not replenished for each machine
        // Fill up each flavour soda drink at each time
        for (size_t flavour = 0; flavour < numflavours; flavour++) {
          size_t transfercount = 0;
          while (cargo[flavour] > 0 && machinestock[flavour] < maxstockperflavour) {
            machinestock[flavour] += 1;
            cargo[flavour] -= 1;
            transfercount += 1;
          }
          missing += maxstockperflavour - machinestock[flavour];
          remaining -= transfercount;
        }
        if (missing > 0) {
          printer.print(Printer::Kind::Truck, 'U', machine->getId(), missing);
        }
        printer.print(Printer::Kind::Truck, 'D', machine->getId(), remaining);
        machine->restocked();
        // Keep track of the last vending machine
        lastvendingmachine = (lastvendingmachine + 1) % nummachines;
        travel += 1;
      }
    }
  } catch (BottlingPlant::Shutdown e) {
    _Accept(~Truck);
       
  }
}
