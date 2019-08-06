//
//  main.cpp
//  Game Maps project
//
// Alexander Krustev FN: 45314
// Code ran and tested on Xcode 10.1
// Clang 10.0.1
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

const size_t BUFFER_SIZE = 256;

// A data structure where the graph will be stored.
typedef std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> graph;

// Creating the graph from the input file.
void addZones(std::ifstream& stream, graph& holder) {
    char line[BUFFER_SIZE]; // The file will be read line by line.
    stream.getline(line, BUFFER_SIZE); // Reading the first line of the file ("[zones]").
    
    while (stream.good()) {
        std::string zoneName;
        std::string adjacentName;
        std::string keyOfAdjacent;
        bool hasKey = false;
        
        stream.getline(line, BUFFER_SIZE);
        
        if (strlen(line) == 0) // A check whether all the zones are read from the file.
            break;
        size_t i = 0;
        
        for (; line[i] != '-'; ++i)
            zoneName.push_back(line[i]);
        
        zoneName.pop_back(); // Removing the white space right after the zone's name.
        i += 3; // Skipping '>' and ' ' characters.
        for (; line[i] != ';'; ++i) {
            adjacentName.push_back(line[i]);
            if (line[i] == '[') {
                hasKey = true;
                i++; // Skipping '[' character.
                for (; line[i] != ']'; ++i)
                    keyOfAdjacent.push_back(line[i]);
            }
        }
        
        if (hasKey) {
            adjacentName.pop_back(); // Pop '[' character.
            adjacentName.pop_back(); // Pop the white space.
        }
        else {
            keyOfAdjacent = "";
        }
        
        holder[zoneName].push_back({adjacentName, keyOfAdjacent});
    }
}

// Reading information about key location.
void addKeysToZones(std::ifstream& stream, std::unordered_map<std::string, std::string>& keychain) {
    char line[BUFFER_SIZE]; // The file will be read line by line.
    stream.getline(line, BUFFER_SIZE); // Reading line "[keys]".
    while (stream.good()) {
        std::string key;
        std::string zone;
        
        stream.getline(line, BUFFER_SIZE);
        if (stream.eof())
            break;
        
        size_t i = 0;
        for (; line[i] != '-'; ++i)
            key.push_back(line[i]);
        
        key.pop_back(); // Remove the white space after the name of the key.
        i += 3;
        
        for (; line[i] != ';'; ++i)
            zone.push_back(line[i]);
        
        keychain[zone] = key;
    }
}

// A check whether a key is located in the zone "zoneName".
bool checkForKeyAndCollect(const std::string& zoneName, const std::unordered_map<std::string, std::string>& keyLocation,
                           std::string& newKey) {
    auto t = keyLocation.find(zoneName);
    if (t != keyLocation.end()) {
            newKey = t->second; // Collect the new key.
            return 1;
    }
    return 0;
}

// Check if currentZone is visited.
bool isVisited(const std::unordered_set<std::string>& visitedZones, const std::string& currentZone) {
    return visitedZones.find(currentZone) != visitedZones.end();
}

void mergeVisitedZones(std::unordered_set<std::string>& visitedZones, std::unordered_set<std::string>& newVisitedZones) {
    
    for (auto it_newVisitedZones : newVisitedZones) {
        if (visitedZones.find(it_newVisitedZones) == visitedZones.end())
            visitedZones.insert(it_newVisitedZones);
    }
}

bool hasAdjacentZone (const graph& holder, const std::string& zoneName) {
    auto it_adjacentZones = holder.find(zoneName)->second.begin();
    return it_adjacentZones->first != "";
}

void BFStraversal(const std::string startingZone,
                  const graph& holder,
                  const std::unordered_map<std::string, std::string>& keyLocation,
                  std::unordered_set<std::string>& foundKeys,
                  std::unordered_set<std::string>& visitedZones) {
    std::queue<std::string> BFSqueue;
    
    BFSqueue.push(startingZone);
    while (!BFSqueue.empty()) {
        std::string currentZone = BFSqueue.front();
        BFSqueue.pop();
        
        auto it = holder.find(currentZone);
        if (it == holder.end())
            throw std::invalid_argument("Nonexistent zone");
        for (auto stringPair : it->second) {
            // Check whether the adjacent zone requires a key. If stringPair.second is "", it means it doesn't require a key.
            if (stringPair.second != "" && foundKeys.find(stringPair.second) == foundKeys.end())
                continue;
            // Check whether the adjacent zone is visited.
            if (!isVisited(visitedZones, stringPair.first)) {
                std::string newKey;
                if (checkForKeyAndCollect(stringPair.first, keyLocation, newKey)) {
                    if (hasAdjacentZone(holder, stringPair.first)) {
                        if (foundKeys.find(newKey) == foundKeys.end()) {
                            foundKeys.insert(newKey);
                            // Initialize a new set for visited vertices to start with it a new traversal from the vertex with the key.
                            std::unordered_set<std::string> newVisitedZones;
                            // Start a new traversal.
                            BFStraversal(stringPair.first, holder, keyLocation, foundKeys, newVisitedZones);
                            // Add unvisited before vertices to the main set of visited vertices.
                            mergeVisitedZones(visitedZones, newVisitedZones);
                        }
                    }
                }
                // Vertices which don't have adjancent ones should not be pushed to the queue.
                if (stringPair.first == "")
                    continue;
                // Push the adjacent vertex to the queue.
                BFSqueue.push(stringPair.first);
            }
        }
        // After adding the adjacent vertices to the queue, the current vertex should be marked as visted.
        visitedZones.insert(currentZone);
    }
}

void generateDOTfile(const std::unordered_set<std::string>& visitedZones,
                     const graph& holder,
                     const std::unordered_map<std::string, std::string>& keyLocation) {
    std::ofstream outStream;
    outStream.open("graph.dot", std::ios::out);
    if (!outStream) {
        std::cerr << "Cannot open file for writing\n";
        return;
    }
    
    outStream << "digraph {\n";
    graph::const_iterator it_holder = holder.begin();
    
    // Check all zones.
    while (it_holder != holder.end()) {
        // Check if the zone is visited.
        if (visitedZones.find(it_holder->first) != visitedZones.end()) {
            // Check if the zone has key.
            if (keyLocation.find(it_holder->first) != keyLocation.end()) {
                outStream << it_holder->first << "[label=\"" << it_holder->first;
                outStream << "\\l" << keyLocation.find(it_holder->first)->second << "\"];\n";
            }
        }
        // Check if the zone is unvisited.
        if (visitedZones.find(it_holder->first) == visitedZones.end()) {
            outStream << it_holder->first << "[label=\"" << it_holder->first;
            // Check if the zone has key.
            if (keyLocation.find(it_holder->first) != keyLocation.end()) {
                outStream << "\\l" << keyLocation.find(it_holder->first)->second << "\",color=red,style=filled,fillcolor=\"#ffefef\"];\n";
            }
            else {
                outStream << "\",color=red,style=filled,fillcolor=\"#ffefef\"];\n";
            }
        }
            // Check and write out all adjacent zones.
            for (auto adjacentZones : it_holder->second) {
                // Vertices which don't have adjacent ones should be skipped.
                if (adjacentZones.first == "")
                    continue;
                else {
                    outStream << it_holder->first << " -> " << adjacentZones.first;
                    if (adjacentZones.second != "") {
                        outStream << " [label=\"" << adjacentZones.second << "\"]";
                    }
                    outStream << ";\n";
                }
            }
        outStream << "\n";
        it_holder++;
        }

    outStream << '}';
    
    if (!outStream.good()) {
        std::cerr << "Error during writing to file\n";
    }
    outStream.close();
}

// Add the vertices which don't have adjacent vertices but they themselves are adjacent vertices.
void addMissedVertices(graph& holder) {
    for (auto it_holder = holder.begin(); it_holder != holder.end(); ++it_holder) {
        for (auto adjacentZones : it_holder->second) {
            if (holder.find(adjacentZones.first) == holder.end()) {
                std::pair<std::string, std::string> pair = std::make_pair("","");
                holder[adjacentZones.first].push_back(pair);
            }
        }
    }
}

int main() {
    
    //std::string filePath; // Input 1
    //std::getline(std::cin, filePath);
    
    
    std::string startingZone = "village"; // Input 2
    //std::cin >> startingZone;
    
    std::ifstream stream;
    stream.open("maps.txt", std::ios::in);
    if (!stream) {
        std::cerr << "Cannot open file\n";
        return 1;
    }
    graph holder;
    std::unordered_map<std::string, std::string> keyLocation; // A data structure which maps every zone to a key. The key can be taken from the zone.

    std::unordered_set<std::string> foundKeys; // A data structure where found keys will be saved.
    std::unordered_set<std::string> visitedZones; // A data structure where visited zones will be saved.
    
    addZones(stream, holder); // Reading the graph from the input file (Input 1).
    addKeysToZones(stream, keyLocation); // Reading information about key location.
    addMissedVertices(holder); // Add the vertices which don't have adjacent vertices but they themselves are adjacent vertices.
    
    try {
        BFStraversal(startingZone, holder, keyLocation, foundKeys, visitedZones); // Traversing the graph and finding the keys.
    } catch (const std::invalid_argument& inv_arg) {
        std::cerr << "Invalid argument exception caught: " << inv_arg.what() << "\n";
        return 1;
    }
    
    stream.close();
    
   generateDOTfile(visitedZones, holder, keyLocation); // Generating output .dot file.
    
    return 0;
}
