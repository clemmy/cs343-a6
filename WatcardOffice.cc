#include "WatcardOffice.h"

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers)
  : printer(prt), bank(bank), numcourier(numCouriers) {
  joblist = queue<Job*>();
  courierlist = new Courier[numcourier];
}

WATCardOffice::~WATCardOffice() {
  for (size_t index = 0; index < numcourier; index++) {
    delete courierlist[index];
  }
  delete[] courierlist;
  printer.print(Printer::Kind::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
  Watcard *card = new WATCard();
  Job *job = new Job(sid, amount, card);
  joblist.push_back(job);
  printer.print(Printer::Kind::WATCardOffice, 'C', sid, amount);
  return job->result;
}

WATCard::FWATCard WATCard::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
  Job *job = new Job(sid, amount, card);
  joblist.push_back(job);
  printer.print(Printer::Kind::WATCardOffice, 'T', sid, amount);
  return job->result;
}

Job * WATCard::requestWork() {
  if (joblist.empty()) {
    return nullptr;
  }
  Job *job = joblist.front();
  joblist.pop();
  return job;
}

void WATCardOffice::main() {
  printer.print(Printer::Kind::WATCardOffice, 'S');
  // Initiating courier tasks and store them in the list
  for (size_t index = 0; index < numcourier; index++) {
    courierlist[index] = new Courier(bank, *this, printer, index);
  }
  for(;;) {
    _Accept(stop) {
      break;
    } or _Accept(create, transfer) {
    } or _When(joblist.size() > 0) _Accept(requestWork) {
      printer.print(Printer::Kind::WATCardOffice, 'W');
    }
  }

  // To wake up the couriers waiting for the joblist
  for (size_t index = 0; index < numcourier; index++) {
    joblist.push_back(nullptr);
    _Accept(requestWork);
  }
}
