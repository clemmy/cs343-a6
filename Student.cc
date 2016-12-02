#include "Student.h"
#include "VendingMachine"
#include "RNG.h"
#include "Watcard.h"

Student::Student(Printer &prt, NameServer &nameserver, WATCardOffice &cardoffice, Groupoff &groupoff,
  unsigned int id, unsigned int maxPurchases):
  printer(prt), 
  nameserver(nameServer),
  office(cardOffice),
  groupoff(groupoff),
  id(id),
  maxpurchase(maxPurchases) {}

Student::~Student() {
  printer.print(Printer::Kind::Student, 'F');
}

void Student::main() {
  int numBottlesToPurchase = rng(1, maxpurchases);
  VendingMachine::Flavours favouriteFlavour = (VendingMachine::Flavours)rng(3);

  printer.print(Printer::Kind::Student, 'S', (int)favouriteFlavour, numBottlesToPurchase);
  WATCard::FWATCard watcard = office.create(id, 5);
  WATCard::FWATCard giftcard = groupoff.giftCard();
  VendingMachine *machine = nameserver.getMachine(id);
  printer.print(Printer::Kind::Student, 'V', machine->getId());

  // buy sodas
  size_t purchased = 0;
  while (purchased < numBottlesToPurchase) {
    try {
      _Select(watcard || giftcard) {
        if (watcard.available()) {
          WATCard *physicalcard = watcard(); // Checking if an exception is thrown

          for (;;) {
            try {
              yield(1, 10);
              machine->buy(favouriteFlavour, *physicalcard);
              printer.print(Printer::Kind::Student, 'B', physicalcard->getBalance());
            } catch (VendingMachine::Funds e) {
              watcard = office.transfer(id, machine->cost() + 5, physicalcard);
              break;
            } catch (VendingMachine::Stock e) {
              machine = nameserver.getMachine(id);
              printer.print(Printer::Kind::Student, 'V', machine->getId());
            }
          }
        } else if (giftcard.available()) {
          for (;;) {
            try {
              yield(1, 10);
              machine->buy(favouriteFlavour, *giftcard());
              printer.print(Printer::Kind::Student, 'G', giftcard()->getBalance());
              giftcard.reset();
            } catch (VendingMachine::Stock e) {
              machine = nameserver.getMachine(id);
              printer.print(Printer::Kind::Student, 'V', machine->getId());
            }
          }
        }
      }
      purchased += 1;
    } catch (WATCardOffice::Lost e) {
      printer.print(Printer::Kind::Student, 'L');
      watcard.reset();
      watcard = office.create(id, 5);
    }
  }

/*
  try {
    Watcard *physicalcard = watcard();
    delete physicalcard;
  } catch (WATCardOffice::Lost e) {
  }
*/
}
