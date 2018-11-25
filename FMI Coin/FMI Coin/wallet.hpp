//
//
//
#ifndef wallet_hpp
#define wallet_hpp
#include "order.hpp"

const unsigned SYSTEM_ID = 4294967295;

struct Wallet {
    char owner[256];
    unsigned id;
    double fiatMoney;
};

void setOwner (Wallet&);
void setId (Wallet&);
int setFiatMoney (Wallet&);
void saveWallet (Wallet&);
void saveWalletId (unsigned);
bool walletExist(unsigned);
void updateWallet(unsigned, double, Order::Type);
Wallet* getWalletsInArray();
bool getWalletInfo(unsigned);
long long getCountOfWallets();
char* getWalletName(unsigned);
Wallet findWalletWithMaxFiatMoney(Wallet*, long long);
void getTopWallets(Wallet*, unsigned short, long long);

#endif
