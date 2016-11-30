#ifndef __PARENT_H__
#define __PARENT_H__

#include "RNG.h"
#include "Printer.h"
#include "Bank.h"

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

#endif // __PARENT_H__
