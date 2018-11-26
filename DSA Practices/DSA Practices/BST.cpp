//
//  Tree.cpp
//  SDP Practs
//
//
// Напишете програма, която ще получи като вход име на текстов файл, който съдържа много цели
// числа, разделени с празни символи (нов ред или интервал). Вие трябва да добавите тези числа
// в двоично наредено дърво. Изкарайте елементите в нарастващ и намаляващ ред.
//

#include <iostream>
#include <fstream>

struct Tree
{
    int value;
    Tree* left;
    Tree* right;
};

void insert(Tree& root, int element)
{
    if(element < root.value)
    {
        if(root.left == nullptr)
        {
            try {
                root.left = new Tree;
            } catch (const std::bad_alloc& ba) {
                std::cerr << "Cannot allocate memory for a new tree\n";
                throw;
            }
            root.left->value = element;
            return;
        }
        insert(*root.left, element);
    }
    else
    {
        if(root.right == nullptr)
        {
            try {
                root.right = new Tree;
            } catch (const std::bad_alloc& ba) {
                std::cerr << "Cannot allocate memory for a new tree\n";
                throw;
            }
            root.right->value = element;
            return;
        }
        insert(*root.right, element);
    }
}

//void printAsc(Tree& root)
//{
//    if(root.left == nullptr)
//    {
//
//    }
//}

int main()
{
    char* fileName;
    std::ifstream stream;
    stream.open(fileName, std::ios::in);
    if(!stream)
    {
        std::cerr << "Cannot open file for reading\n";
    }
    stream.seekg(std::ios::ate);
    long long size = stream.tellg();
    stream.seekg(0, std::ios::beg);
    
    Tree* root;
    try {
        root = new Tree;
        root->left = nullptr;
        root->right = nullptr;
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate a new tree\n";
        throw;
    }
    
    stream >> root->value;
    
    for(long long i = 0; i < size; ++i)
    {
        int element;
        stream >> element;
        insert(*root, element);
    }
}
