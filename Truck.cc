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
  cout << "desturctor" << endl;
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
//      plant.getShipment(reinterpret_cast<unsigned int *>(cargo));
      plant.getShipment(cargo);
      size_t shippedproduct = 0;
      for (size_t index = 0; index < VendingMachine::Flavours::COUNT; index++) {
//        cout << "cargo from the plant : " << cargo[index] << endl;
        shippedproduct += cargo[index];
      }
      printer.print(Printer::Kind::Truck, 'P', shippedproduct);

      // stock up vending machines
      size_t remaining = shippedproduct;
      size_t travel = 0;
//      cout << "Remaining at the beginning : " << remaining << endl;

      // Begin delivering to the vendingmachines with two stopping conditions
      while (remaining > 0 && travel < nummachines) {
//        cout << "Accesing Machine id : " << lastvendingmachine << endl;
        VendingMachine *machine = machines[lastvendingmachine];
        printer.print(Printer::Kind::Truck, 'd', machine->getId(), remaining);
//        size_t *machinestock = reinterpret_cast<size_t *>(machine->inventory());
        unsigned int *machinestock = machine->inventory();
//        cout << "Trying to access to the inventory list" << endl;
        size_t missing = 0; // Counting how many drinks not replenished for each machine
        // Fill up each flavour soda drink at each time
        for (size_t flavour = 0; flavour < numflavours; flavour++) {
//          cout << "Accessing flavour index : " << flavour << endl;
          size_t transfercount = 0;
          while (cargo[flavour] > 0 && machinestock[flavour] < maxstockperflavour) {
//            cout << "Filling out Machine id : " << lastvendingmachine << " && flavour id : " << flavour << endl;
            machinestock[flavour] += 1;
            cargo[flavour] -= 1;
            transfercount += 1;
//            cout << "cargo[flavour] : " << cargo[flavour] << endl;
//            cout << "machinestock[flavour]  : " << machinestock[flavour] << endl;
          }
          missing += maxstockperflavour - machinestock[flavour];
//          cout << "missing : " << missing << endl;
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
    cout << "weird" << endl;
  } catch(BottlingPlant::Shutdown e) {
    _Accept(~Truck);
  }
}
