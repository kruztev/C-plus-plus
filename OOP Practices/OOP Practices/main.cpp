//
//  main.cpp
//  OOP Practices
//

#include <iostream>
#include <fstream>
#include <math.h>
#include "Clock.h"

const double DIFFERENCE = 0.0000001;

struct Point
{
    double x, y;
    
    void readInData();
    void print() const;
    double distanceToCenter() const;
    double distanceBetweenTwoPoints(const Point&) const;
};

size_t closestPoint(const Point* arr, const unsigned int size)
{
    size_t indexToReturn = 0;
    for (size_t index = 1; index < size - 1; ++index)
    {
        if (arr[index].x > 0 && arr[index].x < arr[indexToReturn].x &&
            arr[index].y > 0 && arr[index].y < arr[indexToReturn].y)
       {
           indexToReturn = index;
       }
    }
    return indexToReturn;
}

void readArrayFromStandartInput(Point* array, const unsigned int size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        std::cin >> array[i].x;
        std::cin >> array[i].y;
    }
    return;
}

void readArrayFromFile(Point* array, std::ifstream& fileIn, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (!fileIn)
        {
            break;
        }
        fileIn >> array[i].x;
        fileIn >> array[i].y;
    }
    return;
}

void Point::readInData()
{
    std::cin >> x >> y;
    return;
}

void Point::print() const
{
    std:: cout << "x = " << x << ' ' << "y = " << y << std::endl;
    return;
}

double Point::distanceToCenter() const
{
    double distance = sqrt(x*x + y*y);
    return distance;
    
}

double Point::distanceBetweenTwoPoints(const Point& secondPoint) const
{
    double differenceOfX = (x-secondPoint.x)*(x-secondPoint.x);
    double differenceOfY = (y-secondPoint.y)*(y-secondPoint.y);
    double distance = sqrt(differenceOfX + differenceOfY);
    return distance;
}

struct Rectangle
{
    Point startPoint;
    Point pointAtEnd;
    
    void readInRectangle();
    void printRectangle() const;
};

bool compareDouble(double a, double b)
{
    if (std::max(a,b) - std::min(a,b) < DIFFERENCE)
    {
        return 1;
    }
    return 0;
}

void Rectangle::readInRectangle()
{
    startPoint.readInData();
    pointAtEnd.readInData();
    if(compareDouble(startPoint.x, pointAtEnd.x) && compareDouble(startPoint.y, pointAtEnd.y))
    {
        std::cout << "There is no such rectangle\n";
        return;
    }
    return;
}

void Rectangle::printRectangle() const
{
    double height = std::max(startPoint.y, pointAtEnd.y) - std::min(startPoint.y, pointAtEnd.y);
    double width = std::max(startPoint.x, pointAtEnd.x) - std::min(startPoint.x, pointAtEnd.x);
    for (size_t i = 0; i < (size_t) height; ++i) // Печата редовете
    {
        if (i == 0)
        {
            for(size_t j = 0; j < (size_t )width; ++j)
            {
                std::cout << '*';
            }
            std::cout << std::endl;
        }
        if(i == height - 1)
        {
            
            for(size_t j = 0; j < width; j++)
            {
                std::cout << '*';
            }
            std::cout << std::endl;
            break;
        }
        
        size_t temp = 1; //  Временна променлива, която контролира печатането на самия ред
        std::cout << '*';
        while(temp != width - 1)
        {
            std::cout << ' ';
            temp++;
        }
        std::cout << '*';
        std::cout << std::endl;
    }
}

int main()
{
    
    
    
    Clock a;
    a.syncTime();
    a.print();
    return 0;
    
//    Point* arr = nullptr;
//    std::ifstream fileIn;
//    fileIn.open("points.txt", std::ios::in);
//    if (!fileIn)
//    {
//        std::cerr << "Cannot open file\n";
//        return -1;
//    }
//    size_t size = 0;
//    fileIn >> size;
//    arr = new (std::nothrow) Point[size];
//    if(!arr)
//    {
//        std::cerr << "Cannot allocate memory for points\n";
//        return -1;
//    }
//    readArrayFromFile(arr, fileIn, size);
//    std::cout << "Count of points: " << size << '\n';
//    for (size_t i = 0; i < size; ++i)
//    {
//        std::cout << arr[i].x << ' ' << arr[i].y << '\n';
//    }
//
//    return 0;

    //    Rectangle x;
    //    x.readInRectangle();
    //    x.printRectangle();

}
