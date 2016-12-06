#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"

_Task BottlingPlant;

_Task Truck {
  private:
    Printer &printer;
    NameServer &nameserver;
    BottlingPlant &plant;
    unsigned int nummachines; // total number of machines
    unsigned int maxstockperflavour;
    size_t numflavours;
    unsigned int *cargo; // array stock per flavour
    void main();
    void Stop(); // stop function (destructor alternative)
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
};

#endif // __TRUCK_H__
