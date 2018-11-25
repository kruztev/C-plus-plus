//
//
//
#include <iostream>
#include <fstream>
#include "order.hpp"
#include "transaction.hpp"
#include "wallet.hpp"

const unsigned short FMI_COIN_RATE = 375;
const char* dictionaryOfTypes[] = {"SELL", "BUY"};

void setWalletId(Order& newOrder)
{
    std::cin >> newOrder.walletId;
}

void setFmiCoins(Order& newOrder)
{
    std::cin >> newOrder.fmiCoins;
}

void setIsCompletedFlag(Order& newOrder)
{
    newOrder.isCompleted = 0;
}

void setTime(Order& newOrder)
{
    newOrder.time = time(NULL);
}

int setType(Order& newOrder)
{
    char type[8];
    std::cin >> type;
    for(unsigned i = 0; i < Order::TYPES_COUNT; ++i)
    {
       if(!strcasecmp(type, dictionaryOfTypes[i]) && i == 0)
       {
           newOrder.type = Order::SELL;
           return i;
       }
        else if(!strcasecmp(type, dictionaryOfTypes[i]) && i == 1)
        {
            newOrder.type = Order::BUY;
            return i;
        }
    }
    std::cerr << "Error! You entered an invalid order type. Try again.\n";
    return Order::INVALID_COMMAND;
}

double fmiCoinCount(unsigned walletId) // Calculates FMICoins of a given wallet by Id.
{
    /* A check whether a wallet exists is made in main function.
     
     if(!walletExist(walletId))
    {
        std::cerr << "Wallet with id " << walletId << " does not exist.\n";
        return -1;
    }
     */
    double fmiCoins = 0; // A variable in which values read from the file are added or subtracted.
    
    std::ifstream file;
    file.open("transactions.dat", std::ios::binary | std::ios::in | std::ios::app);
    if(!file)
    {
        std::cerr << "Cannot open \"transactions.dat\" for reading.\n";
        return 1;
    }
    long long countOfTransactions = (long long) file.tellg() / sizeof(Transaction);
    file.seekg(0, std::ios::beg);
    for (long long i = 0; i < countOfTransactions; ++i)
    {
        Transaction temp;
        file.read((char*)&temp, sizeof(Transaction));
        if(temp.receiverId == walletId)
        {
            fmiCoins += temp.fmiCoins;
        }
        if(temp.senderId == walletId)
        {
            fmiCoins -= temp.fmiCoins;
        }
    }
    if(!file.good())
    {
        std::cerr << "There is a problem with \"transactions.dat\".\n";
        file.close();
        return 1;
    }
    
    file.close();
    return fmiCoins;
}

int sellCoins(const Order& sellOrder)
{
    if(!walletExist(sellOrder.walletId)) // A check whether the waleet exists.
    {
        std::cerr << "Wallet with ID " << sellOrder.walletId << " doesn't exist.\n";
        return 0;
    }
    if(fmiCoinCount(sellOrder.walletId) < sellOrder.fmiCoins) // A check whether the wallet has enough FMICoins.
    {
        std::cerr << "The wallet doesn't have enough fmiCoins.\n";
        return -1;
    }
    
    char fileName[2*sizeof(unsigned)*8 + 2 + 4]; // Here an array for the name of the text file is allocated. Two more bytes are a added for a white space and a null character ('\0') and four more for the name of the extension (.txt).
    std::ofstream txtFile;
    
    double orderFmiCoins = sellOrder.fmiCoins; // A variable where the value of the FMICOins of the order is copied.
    long long countOfOrders = getCountOfOrders();
   
    bool startNewOrder = 0; // Becomes 1 when part of the order is completed.
    unsigned countOfTransactions = 0;
    Order* temp = getOrdersInArray();
    
    for(long long i = 0; i < countOfOrders; ++i) // Looks up for orders of type BUY in the file.
    {
        if(temp[i].type == 1 && temp[i].fmiCoins <= orderFmiCoins)
        {
            txtFile.open(generateTxtFileName(sellOrder, fileName), std::ios::out | std::ios::trunc); // Open the text file.
            if(!txtFile)
            {
                std::cerr << "Cannot create \".txt\" file.\n";
                txtFile.close();
                return 0;
            }
            
            makeTransactionSELL(sellOrder, temp[i].walletId);
            char* sellerName = getWalletName(sellOrder.walletId);
            txtFile << sellerName << ' ';
            delete[] sellerName;
            char* buyerName = getWalletName(temp[i].walletId);
            txtFile << buyerName << ' ';
            delete[] buyerName;
            txtFile << temp[i].fmiCoins << '\n';
            countOfTransactions++;
            orderFmiCoins -= temp[i].fmiCoins;
            updateWallet(temp[i].walletId, temp[i].fmiCoins, temp[i].type);
            updateWallet(sellOrder.walletId, temp[i].fmiCoins, sellOrder.type); // Mark the changes in the wallet of the sender.
            temp[i].isCompleted = 1;
            startNewOrder = 1;
        }
    }
    
    if(!startNewOrder) // If the order hasn't changed, function terminates. In this way the order is NOT duplicated.
    {
        delete[] temp;
        return 0;
    }
    txtFile << "Completed transactions: " << countOfTransactions << '\n';
    if(orderFmiCoins > 0) // Check if there are any FMICoins left. (FMICOins of the order)
    {
        createOrderWithLeftFMICoins(sellOrder, orderFmiCoins);
        double selledCoins = sellOrder.fmiCoins - orderFmiCoins;
        txtFile << "Value: " << selledCoins*FMI_COIN_RATE << '\n';
    }
    else
    {
        txtFile << "Value: " << sellOrder.fmiCoins*FMI_COIN_RATE << '\n';
    }
    if(!txtFile.good())
    {
        std::cerr << "There is a problem when trying to write to \".txt\" file.\n";
    }
    txtFile.close();
    updateOrdersFile(temp);
    delete[] temp;
    return 1;
}

void createOrderWithLeftFMICoins(const Order& order, double leftFmiCoins)
{
    Order temp;
    temp.type = order.type;
    temp.walletId = order.walletId;
    temp.fmiCoins = leftFmiCoins;
    temp.isCompleted = 0;
    temp.time = time(NULL);
    saveOrder(order);
}

void saveOrder(const Order& order)
{
    std::ofstream file;
    file.open("orders.dat", std::ios::binary | std::ios::out | std::ios::app);
    if(!file)
    {
        std::cerr << "Cannot open file \"orders.dat\" for writing.\n";
        return;
    }
    
    file.write((const char*)&order, sizeof(order));
    if(!file.good())
    {
        std::cerr << "There is a problem when saving to file \"orders.dat\".\n";
        file.close();
        return;
    }
    file.close();
    return;
}

int buyCoins(const Order& buyOrder)
{
    if(!walletExist(buyOrder.walletId)) // Check whether the wallet exists.
    {
        std::cerr << "Wallet with ID " << buyOrder.walletId << " doesn't exist.\n";
        return 0;
    }
    
    if(fmiCoinCount(buyOrder.walletId)*FMI_COIN_RATE < buyOrder.fmiCoins*FMI_COIN_RATE) // Check whether the wallet has enough fiat money.
    {
        std::cerr << "The wallet doesn't have enough fiatMoney.\n";
        return -1;
    } //
    
    char fileName[2*sizeof(unsigned)*8 + 2 + 4]; /// Here an array for the name of the text file is allocated. Two more bytes are a added for a white space and a null character ('\0') and four more for the name of the extension (.txt).
    std::ofstream txtFile;
    
    double orderFmiCoins = buyOrder.fmiCoins; // A variable where the value of the FMICOins of the order is copied.
    long long countOfOrders = getCountOfOrders();
    
    bool startNewOrder = 0; // Becomes 1 when part of the order is completed.
    unsigned countOfTransactions = 0;
    Order* temp = getOrdersInArray();
    
    for(long long i = 0; i < countOfOrders; ++i) // Looks up for orders of type BUY in the file.
    {
        if(temp[i].type == 0 && temp[i].fmiCoins <= orderFmiCoins)
        {
            txtFile.open(generateTxtFileName(buyOrder, fileName), std::ios::out | std::ios::trunc); // Open the text file.
            if(!txtFile)
            {
                std::cerr << "Cannot create \".txt\" file.\n";
                txtFile.close();
                return 0;
            }
            
            makeTransactionBUY(buyOrder, temp[i].walletId);
            char* buyerName = getWalletName(buyOrder.walletId);
            txtFile << buyerName << ' ';
            delete[] buyerName;
            char* sellerName = getWalletName(temp[i].walletId);
            txtFile << sellerName << ' ';
            delete[] sellerName;
            txtFile << temp[i].fmiCoins << '\n';
            countOfTransactions++;
            orderFmiCoins -= temp[i].fmiCoins;
            updateWallet(temp[i].walletId, temp[i].fmiCoins, temp[i].type);
            updateWallet(buyOrder.walletId, temp[i].fmiCoins, buyOrder.type); // Mark the changes in the wallet of the sender.
            temp[i].isCompleted = 1;
            startNewOrder = 1;
        }
    }
    
    if(!startNewOrder) // If the order hasn't changed, function terminates. In this way the order is NOT duplicated.
    {
        delete[] temp;
        return 0;
    }
    txtFile << "Completed transactions: " << countOfTransactions << '\n';
    if( orderFmiCoins > 0) // Check if there are any FMICoins left. (FMICOins of the order)
    {
        createOrderWithLeftFMICoins(buyOrder, orderFmiCoins);
        double buyedCoins = buyOrder.fmiCoins - orderFmiCoins;
        txtFile << "Value: " << buyedCoins*FMI_COIN_RATE << '\n';
    }
    else
    {
        txtFile << "Value: " << buyOrder.fmiCoins*FMI_COIN_RATE << '\n';
    }
    if(!txtFile.good())
    {
        std::cerr << "There is a problem when trying to write to \".txt\" file.\n";
    }
    txtFile.close();
    updateOrdersFile(temp);
    delete[] temp;
    return 1;
}

void updateOrdersFile(Order* arr) // This function removes the completed orders.
{
    long long countOfOrders = getCountOfOrders();
    std::ofstream fileOut;
    fileOut.open("orders.dat", std::ios::binary | std::ios::out | std::ios::trunc);
    if(!fileOut)
    {
        std::cerr << "Cannot open file \"orders.dat\" for writing.\n";
        return;
    }
    do
    {
        fileOut.clear();
        fileOut.seekp(0, std::ios::beg);
        Order temp;
        for(unsigned i = 0; i < countOfOrders; ++i)
        {
            if(arr[i].isCompleted == 0)
            {
                temp = arr[i];
                fileOut.write((const char*)&temp, sizeof(temp));
            }
        }
    } while (!fileOut.good());
    fileOut.close();
}

Order* getOrdersInArray()
{
    long long countOfOrders = getCountOfOrders();
    std::ifstream file;
    file.open("orders.dat", std::ios::binary | std::ios::in);
    if(!file)
    {
        std::cerr << "Cannot open \"orders.dat\" for reading.\n";
        file.close();
        return nullptr;
    }
    
    Order* arr = new(std::nothrow) Order[countOfOrders];
    if(!arr)
    {
        std::cerr << "Cannot allocate memory for all of the orders.\n";
        file.close();
        return nullptr;
    }
    
    Order temp;
    for(long long i = 0; i < countOfOrders; ++i)
    {
        file.read((char*)&temp, sizeof(Order));
        arr[i] = temp;
    }
    
    if(!file.good())
    {
        std::cerr << "There is a problem when trying to read from \"orders.dat\".\n";
        file.close();
        delete[] arr;
        return nullptr;
    }
    file.close();
    return arr;
}

long long getCountOfOrders()
{
    std::ifstream file;
    file.open("orders.dat", std::ios::binary | std::ios::in | std::ios::app);
    if(!file)
    {
        std::cerr << "Cannot open \"orders.dat\" for reading.\n";
        file.close();
        return -1;
    }
    
    long long countOfOrders = (long long) file.tellg() / sizeof(Order);
    
    if(!file.good())
    {
        std::cerr << "There is a problem when trying to read from \"orders.dat\".\n";
        file.close();
        return -1;
    }
    file.close();
    return countOfOrders;
}

char* generateTxtFileName(const Order& order, char* fileName)
{
    sprintf(fileName, "%u", order.walletId);
    long long len = strlen(fileName);
    fileName[len] = ' ';
    fileName[len+1] = '\0';
    char time[16];
    sprintf(time, "%lld", order.time);
    strcat(fileName, time);
    const char extension[8] = ".txt";
    strcat(fileName, extension);
    return fileName;
}

void updateOrdersFileAndCopyCompletedOrders(Order* arr) // This function removes the completed orders and copies them in another file.
{
    long long countOfOrders = getCountOfOrders();
    std::ofstream fileOut;
    fileOut.open("orders.dat", std::ios::binary | std::ios::out | std::ios::trunc);
    if(!fileOut)
    {
        std::cerr << "Cannot open file \"orders.dat\" for writing.\n";
        return;
    }
    std::ofstream fileOutCompleted;
    fileOutCompleted.open("completedOrders.dat", std::ios::binary | std::ios::out | std::ios::app);
    if(!fileOutCompleted)
    {
        std::cerr << "Cannot open \"completedOrders.dat\" for writing.\n";
        fileOutCompleted.close();
        fileOut.close();
        return;
    }
    do
    {
        fileOut.clear();
        fileOut.seekp(0, std::ios::beg);
        fileOutCompleted.clear();
        fileOutCompleted.seekp(0, std::ios::beg);
        Order temp;
        for(unsigned i = 0; i < countOfOrders; ++i)
        {
            if(arr[i].isCompleted == 0)
            {
                temp = arr[i];
                fileOut.write((const char*)&temp, sizeof(temp));
            }
            else
            {
                temp = arr[i];
                fileOutCompleted.write((const char*)&temp, sizeof(Order));
            }
        }
    } while (!fileOut.good() && fileOutCompleted.good());
    fileOut.close();
    fileOutCompleted.close();
}
