#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "Printer.h"
#include "NameServer.h"
#include "WatcardOffice.h"
#include "Groupoff.h"

_Task Student {
  private:
    Printer &printer;
    NameServer &nameserver;
    WATCardOffice &office;
    Groupoff &groupoff;
    size_t id; // student id
    size_t maxpurchase; // max purchases student will make
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
    ~Student();
};

#endif // __STUDENT_H__
