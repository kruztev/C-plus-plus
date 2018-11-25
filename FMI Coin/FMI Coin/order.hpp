//
//
//
#ifndef order_hpp
#define order_hpp

struct Order {
    enum Type
    {
        INVALID_COMMAND = -1,
        SELL,
        BUY,
        TYPES_COUNT
    } type;
    unsigned walletId;
    double fmiCoins;
    bool isCompleted;
    long long time;
};

void setWalletId(Order&);
void setFmiCoins(Order&);
void setIsCompletedFlag(Order&);
void setTime(Order&);
int setType(Order&);
double fmiCoinCount(unsigned);
int sellCoins(const Order&);
int buyCoins(const Order&);
void createOrderWithLeftFMICoins(const Order&, double);
void saveOrder(const Order&);
void updateOrdersFile(Order*);
Order* getOrdersInArray();
long long getCountOfOrders();
char* generateTxtFileName(const Order&, char*);
void updateOrdersFileAndCopyCompletedOrders(Order*);
#endif
