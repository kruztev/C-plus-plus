//
//  main.cpp
//  Ternary tree
//

#include <iostream>
#include <queue>

struct Node {
    Node(unsigned key, char data) : key(key), data(data), left(nullptr), mid(nullptr), right(nullptr) {}
    
    unsigned key;
    char data;
    Node* left;
    Node* mid;
    Node* right;
};

void countChildren(Node* vertex, unsigned& count) {
    if (vertex->left)
        count++;
    if (vertex->mid)
        count++;
    if (vertex->right)
        count++;
}

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

void BFS(Node* root, unsigned verticesCount) {
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
}

int main() {
    Node root(0, 'b');
    Node r1(1, 'x');
    Node r2(2, 'p');
    Node r3(3, 'q');
    Node r4(4, 'r');
    Node r5(5, 'c');
    Node r6(6, 'a');
    Node r7(7, 'y');
    Node r8(8, 's');
    Node r9(9, 't');
    
    root.left = &r1;
    root.mid = &r7;
    r1.left = &r2;
    r1.mid = &r3;
    r1.right = &r4;
    r4.left = &r5;
    r4.right = &r6;
    r7.right = &r8;
    r8.mid = &r9;
    
    BFS(&root, 10);
    
    return 0;
}
