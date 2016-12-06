#include "RNG.h"
#include "config.h"
#include "Printer.h"
#include "Parent.h"
#include "Bank.h"
#include "WatcardOffice.h"
#include "Groupoff.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Student.h"

#include <iostream>
#include <cstring>

void uMain::main() {
  if (argc > 3) {
    cerr << "Usage : soda [ config-file [ Seed > 0] ]" << endl;
    exit(EXIT_FAILURE);
  }

  string configfile = "soda.config";
  size_t seed;
  // read in and parse args
  switch (argc) {
    case 3:
      seed = atoi(argv[2]);

      if (seed <= 0) { // Seed must be positive
        cerr << "Usage : soda [ config-file [ Seed > 0] ]" << endl;
        exit(EXIT_FAILURE);
      }

      rng.set_seed(seed);
    case 2:
      configfile = argv[1];
    default:
      break;
  }

  // parse config file
  ConfigParms params;
  processConfigFile(configfile.c_str(), params);

  // start tasks
  VendingMachine **machinelist = new VendingMachine*[params.numVendingMachines];
  Student **studentlist = new Student*[params.numStudents];

  Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);
  Bank bank(params.numStudents);
  Parent parent(printer, bank, params.numStudents, params.parentalDelay);
  WATCardOffice office(printer, bank, params.numCouriers);
  Groupoff groupoff(printer, params.numStudents, params.sodaCost, params.groupoffDelay);
  NameServer nameserver(printer, params.numVendingMachines, params.numStudents);

  for (size_t numVend = 0; numVend < params.numVendingMachines; numVend++) {
    machinelist[numVend] = new VendingMachine(printer, nameserver, numVend, params.sodaCost,
                                              params.maxStockPerFlavour);
  }

  BottlingPlant *plant = new BottlingPlant(printer, nameserver, params.numVendingMachines,
                                           params.maxShippedPerFlavour, params.maxStockPerFlavour,
                                           params.timeBetweenShipments);

  for (size_t numStudent = 0; numStudent < params.numStudents; numStudent++) {
    studentlist[numStudent] = new Student(printer, nameserver, office, groupoff, numStudent,
                                          params.maxPurchases);
  }

  // end tasks
  for (size_t numStudent = 0; numStudent < params.numStudents; numStudent++) {
    delete studentlist[numStudent];
  }
  delete[] studentlist;

  delete plant;
  for (size_t numVend = 0; numVend < params.numVendingMachines; numVend++) {
    machinelist[numVend]->Stop();
    delete machinelist[numVend];
  }
  delete[] machinelist;
  nameserver.Stop();
  office.Stop();
}
