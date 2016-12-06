#ifndef __WATCARD_H__
#define __WATCARD_H__

#include <uFuture.h>

class WATCard {
  private:
    WATCard( const WATCard & );               // prevent copying
    WATCard &operator=( const WATCard & );
    unsigned int balance; // balance of the Watcard
  public:
    typedef Future_ISM<WATCard *> FWATCard;   // future watcard pointer
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

#endif // __WATCARD_H__
