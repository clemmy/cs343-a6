#include "Bank.h"

Bank::Bank(unsigned int numStudents) {
  balances = new size_t[numStudents];
  for (size_t i = 0; i < numStudents; ++i) {
    balances[i] = 0;
  }
}

void Bank::deposit(unsigned int id, unsigned int amount) {
  balances[id] += amount;
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
  // block until sufficient balance
  for (;;) {
    if (balances[id] < amount) {
      _Accept(Bank::deposit);
    } else {
      break;
    }
  }
  balances[id] -= amount;
}

Bank::~Bank() {
  delete[] balances;
}
