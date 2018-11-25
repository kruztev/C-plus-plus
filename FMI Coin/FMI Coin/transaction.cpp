//
//
//
#include <iostream>
#include <time.h>
#include <fstream>
#include "transaction.hpp"

const unsigned short FMI_COIN_RATE = 375;


void systemTransaction(const Wallet& wallet)
{
    Transaction temp;
    temp.time = time(NULL);
    temp.senderId = SYSTEM_ID;
    temp.receiverId = wallet.id;
    temp.fmiCoins = wallet.fiatMoney / FMI_COIN_RATE;
    saveTransaction(temp);
}

void saveTransaction(const Transaction& transaction)
{
    std::ofstream file;
    file.open("transactions.dat", std::ios::binary | std::ios::out | std::ios::app);
    if (!file)
    {
        std::cerr << "Error! Cannot open transactions file.\n";
        return;
    }
    
    file.write((const char*)&transaction, sizeof(Transaction));
    if(!file.good())
    {
        std::cerr << "There is a problem when writing to file \"transactions.dat\".\n";
        file.close();
        return;
    }
    file.close();
}

void makeTransactionSELL(const Order& order, unsigned newReceiverId)
{
    Transaction temp;
    temp.time = time(NULL);
    temp.senderId = order.walletId;
    temp.receiverId = newReceiverId;
    temp.fmiCoins = order.fmiCoins;
    saveTransaction(temp);
}

void makeTransactionBUY(const Order& order, unsigned newSenderId)
{
    Transaction temp;
    temp.time = time(NULL);
    temp.senderId = newSenderId;
    temp.receiverId = order.walletId;
    temp.fmiCoins = order.fmiCoins;
    saveTransaction(temp);
}
