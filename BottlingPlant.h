#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "Printer.h"
#include "NameServer.h"
#include "Truck.h"

_Task Truck;

_Task BottlingPlant {
  private:
    Printer &printer;
    NameServer &nameserver;
    size_t nummachines;
    size_t maxshipstock;
    size_t maxstock;
    size_t shippingtime;
    size_t *stock; // cargo to copy to truck
    Truck *truck; // truck pointer
    bool closed; // flag for if plant is closed
    void main();
  public:
    _Event Shutdown {};                       // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[] );
};

#endif // __BOTTLINGPLANT_H__
