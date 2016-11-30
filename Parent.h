#ifndef PARENT_H
#define PARENT_H

#include "MPRNG.h"
#include "Printer.h"
#include "Bank.h"

extern MPRNG mprng;

_Task Parent {
    Printer &prt;
    Bank &bank;
    unsigned int numStudents;
    unsigned int parentalDelay;
    void main();
  public:
    Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay);
    ~Parent();
};

#endif
