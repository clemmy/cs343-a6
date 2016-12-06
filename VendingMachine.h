#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "Printer.h"
#include "NameServer.h"
#include "Watcard.h"

_Task NameServer;

_Task VendingMachine {
  private:
    Printer &printer;
    NameServer &nameserver;
    bool restocking; // restocking state flag
    bool buying; // buying state flag
    bool exception; // exception flag
    size_t machineid;
    size_t sodacost;
    size_t maxstock;
    unsigned int *stockstatus; // status of the stock
    void main();
  public:
    enum Flavours {FANTAORANGE, COFFEE, DRPEPPER, MILKIS, COUNT};      // flavours of soda (YOU DEFINE)
    _Event Funds {};                          // insufficient funds
    _Event Stock {};                          // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    void Stop();
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif // __VENDINGMACHINE_H__
