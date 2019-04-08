//
//  zad1.cpp
//  DSA Practices
//


#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <list>

struct Node
{
    int data;
    Node* left;
    Node* right;
    
    Node(int nData, Node* nLeft = nullptr, Node* nRight = nullptr) :
    data(nData),
    left(nLeft),
    right(nRight)
    {}
};

void addElement(Node* newNode, int data)
{
    try {
        newNode = new Node(data);
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory\n";
        throw;
    }
}

void insert(Node*& root, int element)
{
    if (!root) {
        addElement(root, element);
        return;
    }
    
    if(element < root->data)
    {
        insert(root->left, element);
    }
    else
    {
        insert(root->right, element);
    }
}


Node* builtBst(std::vector<int> numbers)
{
    
    size_t median = numbers.size()/2;
    Node* tree = new Node(median);
    for(size_t i = 0; i < numbers.size(); ++i)
    {
        insert(tree, numbers[i]);
    }
    return tree;
}


// Zad. 2

void findElementPath(Node* root, std::vector<Node*>& array, int element)
{
    array.push_back(root);
    if(root->data == element)
    {
        return;
    }
    if(element < root->data)
    {
        findElementPath(root->left, array, element);
    }
    else
    {
        findElementPath(root->right, array, element);
    }
}

Node* findCommonParent(Node* root, int a, int b)
{
    if((a > root->data && b < root->data) || (a < root->data && b > root->data))
    {
        return root;
    }
    if(a < root->data && b < root->data)
    {
        return findCommonParent(root->left, a, b);
    }
    if(a > root->data && b > root->data)
    {
        return findCommonParent(root, a, b);
    }
    return nullptr;
}

// Zad. 3


Node* BFS(Node* root, int key)
{
    std::queue<Node*> visited;
    if(root->left)
    {
        visited.push(root->left);
    }
    if(root->right)
    {
        visited.push(root->right);
    }
    if(root->data == key)
    {
        return nullptr;
    }
    Node* previous = root;
    while(!visited.empty())
    {
        if(key == visited.front()->data)
        {
            return previous;
        }
        if(visited.front()->left)
        {
            visited.push(visited.front()->left);
        }
        if(visited.front()->right)
        {
            visited.push(visited.front()->right);
        }
        previous = visited.front();
        visited.pop();
    }
    return nullptr;
}

// Zad. 6





int main()
{
    
    
    return 0;
}



