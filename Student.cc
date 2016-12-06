#include "Student.h"
#include "VendingMachine.h"
#include "RNG.h"
#include "Watcard.h"

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
  unsigned int id, unsigned int maxPurchases):
  printer(prt), 
  nameserver(nameServer),
  office(cardOffice),
  groupoff(groupoff),
  id(id),
  maxpurchase(maxPurchases) {}

Student::~Student() {
  printer.print(Printer::Kind::Student, id, 'F');
}

void Student::main() {
  size_t numBottlesToPurchase = rng(1, maxpurchase);
  VendingMachine::Flavours favouriteFlavour = (VendingMachine::Flavours)rng(3);

  printer.print(Printer::Kind::Student, id, 'S', (int)favouriteFlavour, numBottlesToPurchase);
  WATCard::FWATCard watcard = office.create(id, 5);
  WATCard::FWATCard giftcard = groupoff.giftCard();

  // buy sodas
  size_t purchased = 0;
  while (purchased < numBottlesToPurchase) {
    VendingMachine *machine = nameserver.getMachine(id);
    printer.print(Printer::Kind::Student, id, 'V', machine->getId());
    try {
      // block until student has a card
      _Select(watcard || giftcard) {
        if (watcard.available()) {
          // try to use watcard if available
          WATCard *physicalcard = watcard(); // Checking if an exception is thrown

          for (;;) {
            try {
              yield(rng(1, 10));
              machine->buy(favouriteFlavour, *physicalcard);
              printer.print(Printer::Kind::Student, id, 'B', physicalcard->getBalance());
              break;
            } catch (VendingMachine::Funds e) {
              watcard = office.transfer(id, machine->cost() + 5, physicalcard);
              break;
            } catch (VendingMachine::Stock e) {
              machine = nameserver.getMachine(id);
              printer.print(Printer::Kind::Student, id, 'V', machine->getId());
            }
          }
        } else if (giftcard.available()) {
          // try to use gift card if available
          for (;;) {
            try {
              yield(rng(1, 10));
              machine->buy(favouriteFlavour, *giftcard());
              printer.print(Printer::Kind::Student, id, 'G', giftcard()->getBalance());
              delete giftcard();
              giftcard.reset();
              break;
            } catch (VendingMachine::Stock e) {
              machine = nameserver.getMachine(id);
              printer.print(Printer::Kind::Student, id, 'V', machine->getId());
            }
          }
        }
      }
      purchased += 1;
    } catch (WATCardOffice::Lost e) {
      // create new watcard if lost
      printer.print(Printer::Kind::Student, id, 'L');
      watcard.reset();
      watcard = office.create(id, 5);
    }
  }

  // Freeing (Deallocating) the dynamically allocated spaces
  _Select (watcard) {
    try {
      WATCard *physicalcard = watcard();
      delete physicalcard;
    } catch (WATCardOffice::Lost e) {
    }
  }
  _Select (giftcard) {
    WATCard *gift = giftcard();
    delete gift;
  }
}
