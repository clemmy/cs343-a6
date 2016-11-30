#include "Parent.h"

void Parent::main() {
  printer.print(Printer::Kind::Parent, 'S');

  for (;;) {
    _Accept(Parent::~Parent) {
      printer.print(Printer::Kind::Parent, 'F');
      return;
    } _Else {
      yield(parentalDelay); // wait

      unsigned int luckyStudent = mprng(numStudents - 1); // student to give money to
      unsigned int amountToGive = mprng(1, 3); // amount of money to give

      printer.print(Printer::Kind::Parent, 'D', (int)luckyStudent, (int)amountToGive);
      bank.deposit(luckyStudent, amountToGive);
    }
  }
}

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) :
  prt(prt),
  bank(bank),
  numStudents(numStudents),
  parentalDelay(parentalDelay) {}

Parent::~Parent() {}
