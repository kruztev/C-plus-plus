//
//  Graph.cpp
//  DSA Practices
//

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <unordered_map>
#include <utility>


//typedef std::vector<std::vector<bool>> matrix;
//typedef std::vector<std::list<unsigned>> adjList;
//
//matrix createMatrix(unsigned n)
//{
//    matrix A;
//    A.resize(n);
//    for(int i = 0; i < n; ++i)
//    {
//        for(int j = 0; j < n; ++j)
//        {
//            A[i].push_back(rand()%2);
//        }
//    }
//    return A;
//}
//
//void addEdje(matrix T, unsigned v1, unsigned v2)
//{
//    if(v1 < T.size())
//    {
//        if(v2 < T[v1].size())
//        {
//            T[v1][v2] = 1;
//        }
//    }
//}
//
//void printMatrix(matrix A)
//{
//    for(int i = 0; i < A.size(); ++i)
//    {
//        for(int j = 0; j < A.size(); ++j)
//        {
//            std::cout << A[i][j];
//        }
//        std::cout << '\n';
//    }
//}
//
//void printAdjList(adjList list)
//{
//    for(int i = 0; i < list.size(); ++i)
//    {
//        for(unsigned j : list[i])
//        {
//            std::cout << j;
//        }
//        std::cout << '\n';
//    }
//}
//
//adjList convertToList(matrix A)
//{
//    adjList B;
//    B.resize(A.size());
//    for(int i = 0; i < A.size(); ++i)
//    {
//        for(unsigned j = 0; j < A.size(); ++j)
//        {
//            if(A[i][j])
//            {
//                B[i].push_back(j);
//            }
//        }
//    }
//    return B;
//}
//
//int main()
//{
//    matrix B = createMatrix(6);
//    printMatrix(B);
//    std::cout << '\n';
//    adjList H = convertToList(B);
//    printAdjList(H);
//    std::cout << std::endl;
//    return 0;
//}


using graphHolder = std::vector<std::list<int>>;
using edje = std::pair<size_t, size_t>;

int dfs(graphHolder graph, bool* visited, int currentVertex)
{
    if (visited[currentVertex])
    {
        return 0;
    }
    int traversedVertices = 1;
    visited[currentVertex] = 1;
    
    for (const int adjacent : graph[currentVertex])
    {
        traversedVertices += dfs(graph, visited, adjacent);
    }
    
    return traversedVertices;
    
}

void fillGraph(graphHolder& graph)
{
    std::ifstream inStream;
    inStream.open("graph.txt");
    if(!inStream)
    {
        return;
    }
    
    int countOfAdjecentVertices;
    int countOfVertices;
    inStream >> countOfVertices;
    for(size_t i = 0; i < countOfVertices; ++i)
    {
        graph.push_back(std::list<int>());
        inStream >> countOfVertices;
        int adjecent;
        inStream >> adjecent;
        while(adjecent != '\n')
        {
            
        }
    }
    
    
}

void path(std::unordered_map<size_t, std::vector<edje>>, size_t start, std::vector<size_t> distances)
{
    
}

int main()
{
    graphHolder graph;
    
    
    return 0;
}

