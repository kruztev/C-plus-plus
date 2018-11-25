//
//
//
#include <iostream>
#include <fstream>
#include <float.h>
#include "wallet.hpp"
#include "transaction.hpp"

const unsigned short BUFFER_SIZE = 32;
const unsigned short ATTRACT_INVESTORS_COUNT = 10;

enum Commands
{
    INVALID_COMMAND = -1,
    
    ADD_WALLET,
    MAKE_ORDER,
    WALLET_INFO,
    ATTRACT_INVESTORS,
    QUIT,
    
    COMMANDS_COUNT
};

int action(char* buffer, const char* dictionary[])
{
    for(unsigned i = 0; i < COMMANDS_COUNT; ++i)
    {
        if(!strcasecmp(buffer, dictionary[i]))
        {
            return i;
        }
    }
    return INVALID_COMMAND;
}

void addWallet(Wallet temp)
{
    setId(temp);
    std::cin.ignore(); // Ignores the white space between the last digit (fiatMoney) and the name (Owner).
    setOwner(temp);
    saveWallet(temp);
    systemTransaction(temp);
}

void addOrder(Order& newOrder)
{
    setFmiCoins(newOrder);
    setWalletId(newOrder);
    setTime(newOrder);
    setIsCompletedFlag(newOrder);
    saveOrder(newOrder);
}

void walletInfo()
{
    unsigned newId;
    std::cin >> newId;
    if(!newId)
    {
        std::cerr << "Wrong input. Try again.\n";
        std::cin.ignore();
    }
    if (getWalletInfo(newId))
    {
        std::cout << "FmiCoins: " << fmiCoinCount(newId) << '\n';
    }
}

bool checkInput() // Checks the input command's arguments.
{
    if((char)std::cin.peek() == '\n')
    {
        std::cerr << "This command requiers arguments. Try again.\n";
        std::cin.clear();
        std::cin.ignore(UINT32_MAX, '\n');
        return 0;
    }
    return 1;
}

void completeOrders()
{
    long long countOfOrders = getCountOfOrders();
    Order* temp = getOrdersInArray();
    
    for (long long i = 0; i < countOfOrders; ++i)
    {
        if(!temp[i].isCompleted)
        {
            if(temp[i].type == 0)
            {
                switch (sellCoins(temp[i])) // If sellCoins return -1 it means the wallet doesn't have enough money. Hence the order must be removed.
                {
                    case -1:
                        temp[i].isCompleted = 1;
                        updateOrdersFile(temp);
                        break;
                    case 1:
                        temp[i].isCompleted = 1;
                        updateOrdersFileAndCopyCompletedOrders(temp);
                        break;
                    case 0:
                        break;
                }
                break;
            }
            if(temp[i].type == 1)
            {
                switch (buyCoins(temp[i])) // If sellCoins return -1 it means the wallet doesn't have enough money. Hence the order must be removed.
                {
                    case -1:
                        temp[i].isCompleted = 1;
                        updateOrdersFile(temp);
                        break;
                    case 1:
                        temp[i].isCompleted = 1;
                        updateOrdersFileAndCopyCompletedOrders(temp);
                        break;
                    case 0:
                        break;
                }
                break;
            }
        }
    }
    delete[] temp;
    return;
}

bool ordersFileIsEmpty()
{
    std::ifstream file;
    file.open("orders.dat", std::ios::binary | std::ios::in | std::ios::app);
    if(file.tellg())
    {
        return 1;
    }
    return 0;
}

long long getCountOfWalletsOrders (unsigned newId)
{
    std::ifstream file;
    file.open("completedOrders.dat", std::ios::binary | std::ios::in);
    if(!file)
    {
        std::cerr << "Cannot open \"completedOrders.dat\" for reading.\n";
        file.close();
        return -1;
    }
    Order temp;
    long long size = getCountOfOrders();
    long long countOfOrders = 0;
    for(long long i = 0; i < size; ++i)
    {
        file.read((char*)&temp, sizeof(Wallet));
        if(temp.walletId == newId)
        {
            countOfOrders++;
        }
    }
    if(!file.good())
    {
        std::cerr << "There is a problem with \"completedOrders.dat\".\n";
        file.close();
        return -1;
    }
    file.close();
    return countOfOrders;
}

void getWalletsOrdersTimes (unsigned newId, long long& firstTime, long long& lastTime)
{
    std::ifstream file;
    file.open("completedOrders.dat", std::ios::binary | std::ios::in);
    if(!file)
    {
        std::cerr << "Cannot open \"completedOrders.dat\" for reading.\n";
        file.close();
        return;
    }
    Order temp;
    long long size = getCountOfOrders();
    long long i;
    bool flag = 0;
    for(i = 0; i < size; ++i)
    {
        file.read((char*)&temp, sizeof(Wallet));
        if(temp.walletId == newId)
        {
            firstTime = temp.time;
            break;
        }
    }
    for(; i < size; ++i)
    {
        file.read((char*)&temp, sizeof(Wallet));
        if(temp.walletId == newId)
        {
            lastTime = temp.time;
            flag = 1;
            break;
        }
    }
    if(!flag)
    {
        lastTime = firstTime;
    }
    if(!file.good())
    {
        std::cerr << "There is a problem with \"completedOrders.dat\".\n";
        file.close();
        return;
    }
    file.close();
}

bool completedOrdersExist()
{
    std::ifstream file;
    file.open("completedOrders", std::ios::binary | std::ios::in);
    if(file.is_open())
    {
        file.close();
        return 1;
    }
    return 0;
}

long long min(long long a, short b)
{
    if(a < b)
    {
        return a;
    }
    return b;
}

void attractInvestors()
{
    long long countOfWallets = getCountOfWallets();
    if(!countOfWallets)
    {
        std::cout << "There are no investors yet.\n";
        return;
    }
    long long minimum = min(countOfWallets, ATTRACT_INVESTORS_COUNT); // Function min returns the less of two numbers. In this way the case when there are less wallets (less than 10 wallets) in the system is covered and the exact allocation of an array is possible.
    Wallet topWallets[minimum];
    getTopWallets(topWallets, minimum, countOfWallets);
    long long firstTime = 0;
    long long lastTime = 0;
    for(short i = 0; i < minimum; ++i)
    {
        std::cout << topWallets[i].id << ' ';
        std::cout << "FmiCoins: " << fmiCoinCount(topWallets[i].id) << '\n';
        if(completedOrdersExist())
        {
            std::cout << "Count of orders: " << getCountOfWalletsOrders(topWallets[i].id) << '\n';
            getWalletsOrdersTimes(topWallets[i].id, firstTime, lastTime);
            std::cout << "First order time: " << firstTime << '\n';
            std::cout << "Last order time: " << lastTime << '\n';
        }
    }
}

int main()
{
    const char* dictionary[] = {"add-wallet", "make-order", "wallet-info", "attract-investors", "quit"};
    bool flag = true; // This flag controls when the program exits the main cycle.
    bool checkForOrders = 0; // This flag guarantees that when the program starts for the first time, the check for orders will be executed once.
    
    while(flag)
    {
        if(ordersFileIsEmpty() && !checkForOrders) // Check whether there are orders before user input.
        {
            completeOrders();
            checkForOrders = 1;
        }
        char buffer[BUFFER_SIZE];
        std::cin >> buffer;

        switch (action(buffer, dictionary))
        {
            case 0:
                if(!checkInput()) // Checks the input command's arguments.
                {
                    break;
                }
                Wallet tempWallet;
                if(!setFiatMoney(tempWallet)) // Checks if the input is valid.
                {
                    std::cin.ignore(UINT32_MAX, '\n');
                    break;
                }
                addWallet(tempWallet);
                break;
            case 1:
                if(!checkInput()) // Checks the input command's arguments.
                {
                    break;
                }
                Order tempOrder;
                if(setType(tempOrder) == -1)
                {
                    break;
                }
                addOrder(tempOrder);
                completeOrders();
                checkForOrders = 1;
                break;
            case 2:
                if(!checkInput()) // Checks the input command's arguments.
                {
                    break;
                }
                    walletInfo();
                break;
            case 3:
                attractInvestors();
                break;
            case 4:
                flag = false;
                break;
            case -1:
                std::cout << "Invalid command.\n";
                std::cin.ignore(UINT32_MAX, '\n');
                break;
        }
    }
    return 0;
}

