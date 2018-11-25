//
//
//
#ifndef transaction_hpp
#define transaction_hpp
#include "wallet.hpp"
#include "order.hpp"

struct Transaction {
    long long time;
    unsigned senderId;
    unsigned receiverId;
    double fmiCoins;
};

void saveTransaction(const Transaction&);
void systemTransaction(const Wallet&);
void makeTransactionSELL(const Order&, unsigned);
void makeTransactionBUY(const Order&, unsigned);
#endif
