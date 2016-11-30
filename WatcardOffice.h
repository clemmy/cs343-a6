#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__
#include <uFuture.h>
#include <vector>
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
          printer.print(Printer::Kind::Courier, )
          for (;;) {
            Job *job = requestWork();
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
          printer.print(Printer::Kind::Courier, 'F');
        }
    };                    // communicates with bank
    void main();
    Printer &printer;
    Bank &bank;
    size_t numcourier;
    queue<Job*> joblist;
    Courier *courierlist;
  public:
    _Event Lost {};                           // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};
#endif // __WATCARDOFFICE_H__
