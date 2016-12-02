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
    unsigned int nummachines;
    unsigned int maxstockperflavour;
    size_t numflavours;
    size_t *cargo;
    void main();
    void Stop();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
};

#endif // __TRUCK_H__
