#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__

#include "RNG.h"
#include "Watcard.h"
#include "Printer.h"
#include <vector>

using namespace std;

_Task Groupoff {
    Printer &printer;
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupOffDelay;
    vector<WATCard::FWATCard> unusedWatCards;
    vector<WATCard::FWATCard> usedWatCards;

    void main();
  public:
    Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupOffDelay);
    WATCard::FWATCard giftCard();
};

#endif // __GROUPOFF_H__
