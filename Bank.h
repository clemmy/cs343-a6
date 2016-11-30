#ifndef __BANK_H__
#define __BANK_H__

_Monitor Bank {
    unsigned int* balances;
  public:
    Bank(unsigned int numStudents);
    void deposit(unsigned int id, unsigned int amount);
    void withdraw(unsigned int id, unsigned int amount);
};

#endif // __BANK_H__
