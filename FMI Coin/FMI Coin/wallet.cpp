//
//
//
#include <iostream>
#include <fstream>
#include "wallet.hpp"
#include "order.hpp"

const unsigned short FMI_COIN_RATE = 375;
const double CONTROL_VALUE = -1;

void setOwner (Wallet& wallet)
{
    std::cin.getline(wallet.owner, 256);
}

void setId (Wallet& wallet)
{
    std::ifstream file;
    file.open("wallets.dat", std::ios::binary | std::ios::in | std::ios::app);
    if(!file)
    {
        std::cerr << "Error! Cannot open file \"wallets.dat\" for reading.\n";
        return;
    }
    if (!file.tellg()) // Ако файлът е празен, създаваме първото id с номер 1.
    {
        wallet.id = 1;
        saveWalletId(wallet.id);
    }
    else // Проверяваме колко е последното id и инкрементираме, за да получим новото.
    {
        long long beg = file.tellg();
        file.seekg(beg - sizeof(Wallet));
        Wallet temp;
        file.read((char*)&temp,sizeof(Wallet));
        if(!file.eof())
        {
            wallet.id = temp.id + 1;
            if (wallet.id == SYSTEM_ID)
            {
                std::cerr << "Maximal count of id reached.\n";
                return;
            }
            saveWalletId(wallet.id);
        }
    }
    if(!file.good())
    {
        std::cerr << "Error! Cannot save data to \"wallets.dat\".\n";
        file.close();
        return;
    }
    file.close();
    return;
}

int setFiatMoney (Wallet& wallet)
{
    std::cin >> wallet.fiatMoney;
    if(!std::cin)
    {
       std::cin.clear();
    }
    if(!wallet.fiatMoney)
    {
        std::cerr << "Invalid input. Try again.\n";
        return 0;
    }
    return 1;
}

void saveWallet(Wallet& wallet)
{
    std::ofstream file;
    file.open("wallets.dat", std::ios::binary | std::ios::out | std::ios::app);
    file.write((const char*)&wallet, sizeof(wallet));
    if (!file.good())
    {
        std::cerr << "Error! Cannot save data to \"wallets.dat\".\n";
        file.close();
        return;
    }
    file.close();
}

void saveWalletId (unsigned walletId)
{
    std::ofstream file;
    file.open("walletId.dat", std::ios::binary | std::ios::out | std::ios::app);
    if(!file)
    {
        std::cerr << "Cannot open \"walletId.dat\" to save wallet Id.\n";
        return;
    }
    file.write((const char*)&walletId, sizeof(unsigned));
    if(!file.good())
    {
        std::cerr << "Cannot save data to \"walletId.dat\".\n";
        file.close();
        return;
    }
    file.close();
    return;
}

bool walletExist(unsigned walletId)
{
    std::ifstream file;
    file.open("walletID.dat", std::ios::binary | std::ios::in | std::ios::app);
    if(!file)
    {
        std::cerr << "Cannot open file \"walletID.dat\" for reading.\n";
    }
    long long countOfId = (long long) file.tellg() / sizeof(unsigned);
    file.seekg(0, std::ios::beg);
    
    for(long long i = 0; i < countOfId; ++i)
    {
        unsigned temp;
        file.read((char*)&temp, sizeof(unsigned));
        if(temp == walletId && file.good())
        {
            file.close();
            return 1;
        }
    }
    if(!file.good())
    {
        std::cerr << "There is a problem with \"walletID.dat\".\n";
        file.close();
        return 0;
    }
    file.close();
    return 0;
}

void updateWallet(unsigned id, double fmiCoins, Order::Type type) // Отразява промяна на количество пари в даден портфейл и го презаписва във файла.
{
    Wallet* walletP = getWalletsInArray(); // Подава масив с прочетените от файла данни (за портфейли).
    long long size = getCountOfWallets();
    std::ofstream file;
    file.open("wallets.dat", std::ios::binary | std::ios::out | std::ios::trunc);
    if(!file)
    {
        std::cerr << "Cannot open file \"wallets.dat\" for writing.\n";
        return;
    }
    
    do
    {
        file.clear();
        file.seekp(0, std::ios::beg);
        for(unsigned i = 0; i < size; ++i)
        {
            if(walletP[i].id == id) // Когато стигнем до търсеното id, променяме данните.
            {
                if(type == 0)
                {
                    walletP[i].fiatMoney += fmiCoins*FMI_COIN_RATE;
                }
                else
                {
                    walletP[i].fiatMoney -= fmiCoins*FMI_COIN_RATE;
                }
            }
            file.write((const char*)&walletP[i], sizeof(Wallet));
        }
    } while (!file.good());
    delete[] walletP;
    file.close();
    return;
}

Wallet* getWalletsInArray()
{
    std::ifstream file;
    file.open("wallets.dat", std::ios::binary | std::ios::in);
    if(!file)
    {
        std::cerr << "Cannot open file \"wallets.dat\" for reading.\n";
        return nullptr;
    }
    long long size = getCountOfWallets();
    Wallet* arr = new (std::nothrow) Wallet[size];
    if(!arr)
    {
        std::cerr << "Cannot allocate memory to copy wallet data./n";
        return nullptr;
    }
    Wallet temp;
    
    for(unsigned i = 0; i < size; ++i)
    {
        file.read((char*)&temp, sizeof(Wallet));
        arr[i] = temp;
    }
    if(!file.good())
    {
        std::cerr << "There is a problem with \"wallets.dat\".\n";
        file.close();
        delete[] arr;
        return nullptr;
    }
    file.close();
    return arr;
}

bool getWalletInfo(unsigned newId)
{
    if(!walletExist(newId))
    {
        std::cerr << "Wallet with id " << newId << " does not exist.\n";
        return 0;
    }
    std::ifstream file;
    file.open("wallets.dat", std::ios::binary | std::ios::in);
    if(!file)
    {
        std::cerr << "File \"wallets.dat\" cannot be open for reading.\n";
        return 0;
    }
    Wallet temp;
    
    long long countOfWallets = getCountOfWallets();
    
    for(long long i = 0; i < countOfWallets; ++i)
    {
        file.read((char*)&temp, sizeof(Wallet));
        if(temp.id == newId)
        {
            std::cout << temp.owner << '\n';
            std::cout << "fiatMoney: " << temp.fiatMoney << '\n';
            break;
        }
    }
    if(!file.good())
    {
        std::cerr << "There is a problem with \"wallets.dat\".\n";
        file.close();
        return 0;
    }
    file.close();
    return 1;
}

long long getCountOfWallets()
{
    std::ifstream file;
    file.open("wallets.dat", std::ios::binary | std::ios::in | std::ios::app);
    if(!file)
    {
        std::cerr << "Cannot open \"wallets.dat\" for reading.\n";
        file.close();
        return -1;
    }
    long long CountOfWallets = (long long) file.tellg() / sizeof(Wallet);
    if(!file.good())
    {
        std::cerr << "There is a problem with \"wallets.dat\".\n";
        file.close();
        return -1;
    }
    file.close();
    return CountOfWallets;
}

char* getWalletName(unsigned walletId)
{
    std::ifstream file;
    file.open("wallets.dat", std::ios::binary | std::ios::in);
    if(!file)
    {
        std::cerr << "Cannot open \"wallets.dat\" for reading.\n";
        file.close();
        return nullptr;
    }
    long long countOfWallets = getCountOfWallets();
    Wallet temp;
    for(long long i = 0; i < countOfWallets; ++i)
    {
        file.read((char*)&temp, sizeof(Wallet));
        if(temp.id == walletId)
        {
            break;
        }
    }
    char* walletName = new (std::nothrow) char[strlen(temp.owner) + 1];
    if(!walletName)
    {
        std::cerr << "Cannot allocate memory for wallet owner's name.\n";
        return nullptr;
    }
    strcpy(walletName, temp.owner);
    if(!file.good())
    {
        std::cerr << "There is a problem with \"wallets.dat\".\n";
        file.close();
        delete[] walletName;
        return nullptr;
    }
    file.close();
    return walletName;
}

Wallet findWalletWithMaxFiatMoney(Wallet* arr, long long countOfWallets)
{
    unsigned pos = 0;
    Wallet temp = arr[pos];
    
    while (arr[pos].fiatMoney == CONTROL_VALUE)
    {
        temp = arr[++pos];
    }
    
    for(long long i = 1; i < countOfWallets; ++i)
    {
        if(fmiCoinCount(arr[i].id) > fmiCoinCount(temp.id) && arr[i].fiatMoney != CONTROL_VALUE) // Портфейлите, които вече са били избрани, са с променена стойност на парите -1 (CONTROL_VALUE).
        {
            temp = arr[i];
        }
    }
    return temp;
}

void getTopWallets(Wallet* topWallets, unsigned short countOfTopWallets, long long countOfWallets)
{
    Wallet* walletArr = getWalletsInArray();
    
    for(short i = 0; i < countOfTopWallets; ++i)
    {
        Wallet temp = findWalletWithMaxFiatMoney(walletArr, countOfWallets);
        topWallets[i] = temp;
        for(long long j = 0; j < countOfWallets; ++j)
        {
            if(walletArr[j].id == temp.id)
            {
                walletArr[j].fiatMoney = CONTROL_VALUE;
                break;
            }
        }
    }
    delete[] walletArr;
}
