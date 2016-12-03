#include "Groupoff.h"

using namespace std;

Groupoff::Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupOffDelay) :
  printer(prt),
  numStudents(numStudents),
  sodaCost(sodaCost),
  groupOffDelay(groupOffDelay) {
    unusedWatCards = new vector<WATCard::FWATCard *>();
    usedWatCards = new vector<WATCard::FWATCard *>();

    for (size_t i = 0; i < numStudents; ++i) {
      unusedWatCards->push_back(new WATCard::FWATCard());
    }
  }

// Return future to a random gift card, it will be delivered after a groupOffDelay
WATCard::FWATCard Groupoff::giftCard() {
  unsigned int randCardIndex = rng(unusedWatCards->size() - 1);

  // move from unusedWatCards to usedWatCards
  WATCard::FWATCard * c = unusedWatCards->at(randCardIndex);
  unusedWatCards->erase(unusedWatCards->begin() + randCardIndex);
  usedWatCards->push_back(c);

  return *c;
}

void Groupoff::main() {
  printer.print(Printer::Kind::Groupoff, 'S');

  for (size_t i = 0; i<numStudents;) {
    _Accept(~Groupoff) {
      break;
    } or _Accept(giftCard) {
      yield(groupOffDelay);

      WATCard *card = new WATCard();
      card->deposit(sodaCost);
      printer.print(Printer::Kind::Groupoff, 'D', sodaCost);
      usedWatCards->back()->delivery(card);
      i++;
    } _Else {
    }
  }
  printer.print(Printer::Kind::Groupoff, 'F');
}

Groupoff::~Groupoff() {
  for (size_t i=0; i<unusedWatCards->size(); ++i) {
    delete unusedWatCards->at(i);
  }
  for (size_t i=0; i<usedWatCards->size(); ++i) {
    delete usedWatCards->at(i);
  }
  delete unusedWatCards;
  delete usedWatCards;
}
