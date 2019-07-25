//
//  main.cpp
//  Ternary tree
//

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

struct Node {
    Node(unsigned key, char data) : key(key), data(data), left(nullptr), mid(nullptr), right(nullptr) {}
    
    unsigned key;
    char data;
    Node* left;
    Node* mid;
    Node* right;
};

void printLevel(std::queue<Node*>& currLevel, std::queue<Node*>& nextLevel, bool* visited)
{
    while (!currLevel.empty()) {
        Node* firstInQueue = currLevel.front();
        std::cout << firstInQueue->data;
        currLevel.pop();
        
        if (firstInQueue->left) {
            if (!visited[firstInQueue->left->key]) {
                visited[firstInQueue->left->key] = true;
                nextLevel.push(firstInQueue->left);
            }
        }
        if (firstInQueue->mid && !visited[firstInQueue->mid->key]) {
            visited[firstInQueue->mid->key] = true;
            nextLevel.push(firstInQueue->mid);
        }
        if (firstInQueue->right && !visited[firstInQueue->right->key]) {
            visited[firstInQueue->right->key] = true;
            nextLevel.push(firstInQueue->right);
        }
    }
    std::cout << '\n';
}

void BFS(Node*& root, unsigned verticesCount) {
//    if (verticesCount > 0)
//        return;
    bool* visited = new bool[verticesCount]; // Exception thrown by new?
    for (size_t i = 0; i < verticesCount; ++i) {
        visited[i] = false;
    }
    
    std::queue<Node*> verticesCurrLevel;
    std::queue<Node*> verticesNextLevel;
    visited[root->key] = true;
    verticesCurrLevel.push(root);
    
    while(!verticesCurrLevel.empty() || !verticesNextLevel.empty()) {
        printLevel(verticesCurrLevel, verticesNextLevel, visited);
        printLevel(verticesNextLevel, verticesCurrLevel, visited);
    }
    
    delete [] visited;
}

void handleNewSymbol(std::stack<unsigned short>& countOfChildren, std::stack<Node*>& treeTracing, unsigned& vertexCounter, char symbol) {
    
    if (countOfChildren.top() == 0) {
            treeTracing.top()->left = new Node(vertexCounter, symbol);
            treeTracing.push(treeTracing.top()->left);
    }
    if (countOfChildren.top() == 1) {
            treeTracing.top()->mid = new Node(vertexCounter, symbol);
            treeTracing.push(treeTracing.top()->mid);
    }
    if (countOfChildren.top() == 2) {
            treeTracing.top()->right = new Node(vertexCounter, symbol);
        treeTracing.push(treeTracing.top()->right);
    }
    
    ++countOfChildren.top();
    countOfChildren.push(0);
    ++vertexCounter;
}

void readTree(Node*& root, std::ifstream& stream, unsigned& vertexCounter)
{
    std::stack<Node*> treeTracing;
    std::stack<unsigned short> countOfChildren;
    char symbol = '\0';
    
    stream >> symbol;
    stream >> symbol;
    
    if (stream.eof())
        return;
    
    root = new Node(vertexCounter++, symbol);
    treeTracing.push(root);
    countOfChildren.push(0);
    
    while(stream.good())
    {
        stream >> symbol;
        if (stream.eof())
            return;
        
        if (symbol >= 'a' && symbol <= 'z') {
            handleNewSymbol(countOfChildren, treeTracing, vertexCounter, symbol);
        }
        if (symbol == '(') {
            continue;
        }
        if (symbol == '*') {
            ++countOfChildren.top();
            continue;
        }
        if (symbol == ')' && !stream.eof()) {
            treeTracing.pop();
            countOfChildren.pop();
            continue;
        }
    }
}

void loadTreeFromFile(Node*& root, unsigned& vertexCounter)
{
    std::ifstream stream("ternary_tree.txt");
    if (!stream) {
        std::cerr << "Cannot open file for reading\n";
        return;
    }
    
    readTree(root, stream, vertexCounter);
    
    stream.close();
}

void deleteTree(Node* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->mid);
        deleteTree(root->right);
        delete root;
    }
}

int main() {
    
    Node* root = nullptr;
    unsigned vertexCounter = 0;
    loadTreeFromFile(root, vertexCounter);
    BFS(root, vertexCounter);
    deleteTree(root);
    
    
    return 0;
}
