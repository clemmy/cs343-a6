#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "Printer.h"
#include "Watcard.h"
#include "Bank.h"
#include "RNG.h"
#include <uFuture.h>
#include <queue>

using namespace std;

_Task WATCardOffice {
  private:
    struct Job {                              // marshalled arguments and return future
      size_t sid;
      size_t amount;
      WATCard *watcard;
      WATCard::FWATCard result;             // return future
      Job(size_t sid, size_t amount, WATCard *card)
        : sid(sid), amount(amount), watcard(card) {}
    };

    _Task Courier {
      private:
        Bank &bank;
        WATCardOffice &office;
        Printer &printer;
        size_t courierid;
        void main() {
          printer.print(Printer::Kind::Courier, courierid, 'S');
          for (;;) {
            Job *job = office.requestWork();
            if (job == nullptr) {
              break;
            }
            printer.print(Printer::Kind::Courier, courierid, 't', static_cast<int>(job->sid),
                                                                  static_cast<int>(job->amount));

            bank.withdraw(job->sid, job->amount);
            job->watcard->deposit(job->amount);
            printer.print(Printer::Kind::Courier, courierid, 'T', static_cast<int>(job->sid),
                                                                  static_cast<int>(job->amount));

            // 1/6th chance that the card will be lost
            if (rng(5) == 0) {
              printer.print(Printer::Kind::Courier, courierid, 'L');
              delete job->watcard;
              job->result.exception(new WATCardOffice::Lost);
            } else {
              job->result.delivery(job->watcard);
            }
            delete job;
          }
        }
      public:
        Courier(Bank &bank, WATCardOffice &office, Printer &printer, size_t id)
          : bank(bank), office(office), printer(printer), courierid(id) {}
        ~Courier() {
          printer.print(Printer::Kind::Courier, courierid, 'F');
        }
    };                    // communicates with bank
    void main();
    Printer &printer;
    Bank &bank;
    size_t numcourier;
    queue<Job*> joblist; // queue of job list
    Courier **courierlist; // array of couriers
  public:
    _Event Lost {};                           // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
    void Stop();
};

#endif // __WATCARDOFFICE_H__
