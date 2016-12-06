#ifndef __BANK_H__
#define __BANK_H__

_Monitor Bank {
    size_t *balances; // holds balances for every student
  public:
    Bank(unsigned int numStudents);
    ~Bank();
    void deposit(unsigned int id, unsigned int amount);
    void withdraw(unsigned int id, unsigned int amount);
};

#endif // __BANK_H__
