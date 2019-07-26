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

// Function printLevel is used as a helper function in BFS function below.
// Queue currLevel stores the vertices from the current level and if any of them
// has a child, it is pushed to queue nextLevel.
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

// BFS algorithm is used to read the data of the tree nodes level by level.
void BFS(Node*& root, unsigned verticesCount) {
    bool* visited = nullptr;
    try {
        visited = new bool[verticesCount];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << 'n';
        return;
    }
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
    
    delete[] visited;
}


// Function handleNewSymbol is used as a helper function in readTree function below.
// Stack countOfChildren is used to control the count of children of all vertices.
// At the bottom is the count of children of the root.
// Stack treeTracing is used to trace the way back to the root of the tree.
// vertexCounter is the number which is assigned as a key to a new node.
// Symbol is the character extracted of the stream.
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

// readTree extracts characters of the stream and constructs a tree with nodes in which data the characters are saved.
// vertexCounter is passed by reference, because during the construction of the tree it is incremented every
// time a new node is created.
bool readTree(Node*& root, std::ifstream& stream, unsigned& vertexCounter)
{
    std::stack<Node*> treeTracing;
    std::stack<unsigned short> countOfChildren;
    char symbol = '\0';
    
    stream >> symbol;
    stream >> symbol;
    
    if (stream.eof())
        return 0;
    
    root = new Node(vertexCounter++, symbol);
    treeTracing.push(root);
    countOfChildren.push(0);
    
    while(stream.good())
    {
        stream >> symbol;
        if (stream.eof())
            break;
        
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
    return 1;
}

bool loadTreeFromFile(Node*& root, unsigned& vertexCounter)
{
    std::ifstream stream("ternary_tree.txt");
    if (!stream) {
        std::cerr << "Cannot open file for reading\n";
        return 0;
    }
    
    if (readTree(root, stream, vertexCounter)) {
        stream.close();
        return 1;
    }
    stream.close();
    return 0;

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
    if (loadTreeFromFile(root, vertexCounter)) {
        BFS(root, vertexCounter);
        deleteTree(root);
    }

    return 0;
}
