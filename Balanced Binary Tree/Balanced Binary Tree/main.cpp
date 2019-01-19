//
//  main.cpp
//  Balanced Binary Tree
//
//  Alexander Krustev
//  Code ran and tested on Xcode 10.1
//

#include <iostream>

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

void addElement(Tree* &ptr, int element) // Helper function for inserting numbers in the tree.
{
    try {
        ptr = new Tree(element);
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new tree\n";
        throw;
    }
}

void insert(Tree* &root, int element) // Inserting numbers in the tree.
{
    if(root->value == element)
    {
        throw std::logic_error("This element is already inserted");
    }
    else if (element < root->value)
    {
        if (!root->left)
        {
            addElement(root->left, element);
            return;
        }
        insert(root->left, element);
    }
    else
    {
        if (!root->right)
        {
            addElement(root->right, element);
            return;
        }
        insert(root->right, element);
    }
}

void printAsc(Tree* root) // Printing tree numbers in ascending order.
{
    if (root->left)
    {
        printAsc(root->left);
    }
    std::cout << root->value << ' ';
    if (root->right)
    {
        printAsc(root->right);
    }
}

void cleanTree(Tree* root) // Freeing used memory.
{
    if (root->left)
    {
        cleanTree(root->left);
    }
    if (root->right)
    {
        cleanTree(root->right);
    }
    delete root;
}

int* arrayOfInputNumbers(size_t countOfNumbers) // Allocating an array for input sequence.
{
    int* arr = nullptr;
    try {
        arr = new int[countOfNumbers];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for " << countOfNumbers << " numbers\n";
        throw;
    }
    return arr;
}

void getInputNumbers(int* arr, size_t countOfNumbers) // Reading values from console and saving them in an array.
{
    for (size_t i = 0; i < countOfNumbers; ++i)
    {
        std::cin >> arr[i];
    }
}

Tree* createTree(int root) // Creating a tree from a given value (root).
{
    Tree* tree = nullptr;
    try {
        tree = new Tree(root);
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new tree\n";
        throw;
    }
    return tree;
}

void fillTree(Tree* &root, int* inputNumbers, size_t countOfInputNumbers, int median) // Filling the tree with integers from array.
{
    for (size_t i = 0; i < countOfInputNumbers; ++i)
    {
        if (inputNumbers[i] == median)
        {
            continue;
        }
        insert(root, inputNumbers[i]);
    }
}

void createAndPrintTree() // Creating a balanced binary tree and printing it.
{
    std::cout << "Enter count of numbers: ";
    size_t countOfNumbers;
    std::cin >> countOfNumbers;
    
    int* inputNumbers = arrayOfInputNumbers(countOfNumbers);
    getInputNumbers(inputNumbers, countOfNumbers);
    
    size_t median = countOfNumbers/2; // Finding the root.
    
    Tree* root = createTree(inputNumbers[median]);
    
    fillTree(root, inputNumbers, countOfNumbers, inputNumbers[median]);
    
    printAsc(root);
    
    delete[] inputNumbers;
    cleanTree(root);
}

int main()
{
    createAndPrintTree();
    
    std::cout << std::endl;
    return 0;
}
