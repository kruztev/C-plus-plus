//
//  main.cpp
//  SDP Practs
//

#include <iostream>
#include "Date.hpp"
#include "LinkedList.hpp"
#include "Vector.hpp"

unsigned gcd(unsigned a, unsigned b) // Greatest common divisor
{
    while(a != b)
    {
        if(a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    return a;
}

void f(unsigned a)
{
    unsigned div = 2;
    while (a!=1)
    {
        while(a%div == 0)
        {
            a/=div;
            std::cout << div << '.';
            if (a == 1)
            {
                break;
            }
        }
        div++;
    }
        
    std::cout << 1;
}

unsigned problem2(unsigned num)
{
    unsigned gcdOf2 = 1;
    unsigned product = 1;
    for(unsigned i = 3; i <= num; ++i)
    {
        gcdOf2 = gcd(gcdOf2, i);
        product *= i;
    }
    unsigned leastCommonMultiple = product / gcdOf2;
    return leastCommonMultiple;
}


void insertionSort(int* arr, unsigned size)
{
    for(unsigned i = 1; i < size; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        
        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}
