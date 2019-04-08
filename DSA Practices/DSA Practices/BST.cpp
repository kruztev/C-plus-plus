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
    
    Tree(int nValue, Tree* nLeft = nullptr, Tree* nRight = nullptr) :
        value(nValue),
        left(nLeft),
        right(nRight)
    {}
};

void addElement(Tree* &ptr, int element)
{
    try {
        ptr = new Tree(element);
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new tree\n";
        throw;
    }
}

void insert(Tree* &root, int element)
{
    if(root->value == element)
    {
        throw std::logic_error("This element is already inserted");
    }
     else if(element < root->value)
    {
        if(!root->left)
        {
            addElement(root->left, element);
            return;
        }
        insert(root->left, element);
    }
    else
    {
        if(!root->right)
        {
            addElement(root->right, element);
            return;
        }
        insert(root->right, element);
    }
}

void printAsc(Tree* root)
{
    if(root->left)
    {
        printAsc(root->left);
    }
    std::cout << root->value << ' ';
    if(root->right)
    {
        printAsc(root->right);
    }
}

void printDesc(Tree* root)
{
    if(root->right)
    {
        printDesc(root->right);
    }
    std::cout << root->value << ' ';
    if(root->left)
    {
        printDesc(root->left);
    }
}

void cleanTree(Tree* root)
{
    if(root->left)
    {
        cleanTree(root->left);
    }
    if(root->right)
    {
        cleanTree(root->right);
    }
    delete root;
}

//int main()
//{
//    std::string fileName;
//    std::cout << "Enter absolute path to file: ";
//    std::cin >> fileName;
//    std::cout << std::endl;
//    
//    std::ifstream stream;
//    stream.open(fileName, std::ios::in);
//    if(!stream)
//        return -1;
//    
//    int element;
//    stream >> element;
//    
//    Tree* root = new Tree(element);
//    if(!root)
//        return -1;
//
//        while(!stream.eof())
//        {
//            stream >> element;
//            insert(root, element);
//        }
//    
//    std::cout << "Numbers ascending: ";
//    printAsc(root);
//    std::cout << '\n';
//    std::cout << "Numbers descending: ";
//    printDesc(root);
//    std::cout << '\n';
//    cleanTree(root);
//    
//    
//    return 0;
//}
