//
//  main.cpp
//  Game Maps project
//
// Alexander Krustev FN: 45314
// Code ran and tested on Xcode 10.1
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
        if (line[0] == '\n') // Skipping the '\n' character.
            i++;
        
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
        
        
        std::pair<std::string, std::string> pair = std::make_pair(adjacentName, keyOfAdjacent);
        holder[zoneName].push_back(pair);
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
bool checkForKey(const std::string& zoneName,
                  std::unordered_set<std::string>& foundKeys,
                 const std::unordered_map<std::string, std::string>& keychain) {
    auto t = keychain.find(zoneName);
    if (t != keychain.end()) {
            foundKeys.insert(t->second); // Add new key to foundKeys set.
            return 1;
    }
    return 0;
}

// Check if currentZone is visited.
bool isVisited(const std::unordered_set<std::string>& visitedZones, const std::string& currentZone) {

    auto it = visitedZones.find(currentZone);
    if (it != visitedZones.end())
        return true;
    return false;
    
}

void BFStraversal(const std::string startingZone,
                  const graph& holder,
                  const std::unordered_map<std::string, std::string>& keychain,
                  std::unordered_set<std::string>& foundKeys,
                  std::unordered_set<std::string>& visitedZones) {
    std::queue<std::string> BFSqueue;
    
    BFSqueue.push(startingZone);
    while (!BFSqueue.empty()) {
        std::string currentZone = BFSqueue.front();
        BFSqueue.pop();
        
        
        auto it = holder.find(currentZone);

        for (auto stringPair : it->second) {
                // If stringPair.second = "", it means it doesn't require a key.
                if (stringPair.second != "" && foundKeys.find(stringPair.second) == foundKeys.end())
                    continue;
                // Check whether the adjacent zone is visited.
                if (!isVisited(visitedZones, stringPair.first)) {
                    if (checkForKey(stringPair.first, foundKeys, keychain)) {
                        BFStraversal(stringPair.first, holder, keychain, foundKeys, visitedZones);
                    }
                    // Check whether the adjacent zone requires a key.
                    if (stringPair.second != "") {
                        std::unordered_set<std::string>::iterator j = foundKeys.find(stringPair.second);
                        // The case when the the key is not found. The zone is not marked as visited but is pushed to the queue because it should be visited again.
                        if (j == foundKeys.end()) {
                            BFSqueue.push(stringPair.first);
                            continue;
                        }
                    }
                     // Marks as visited and pushes to the queue.
                        visitedZones.insert(stringPair.first);
                    // Vertices who don't have adjancent ones should not be pushed to the queue.
                    if (stringPair.first == "")
                        continue;
                        BFSqueue.push(stringPair.first);
                }
            }
    }
}

void notVisitedAdjacent(std::ofstream& outStream,
                        const std::unordered_map<std::string, std::string>& keychain,
                        const graph::const_iterator& it_holder,
                        const std::unordered_set<std::string>& visitedZones) {
    // Check if the zone is visited. In this way duplicating the zone in the output file is avoided.
    if (visitedZones.find(it_holder->first) == visitedZones.end()) {
        outStream << it_holder->first << "[label=\"" << it_holder->first;
        if (keychain.find(it_holder->first) != keychain.end()) {
            outStream << "\\l" << keychain.find(it_holder->first)->second << "\",color=red,style=filled,fillcolor=\"#ffefef\"];\n";
        }
        else {
            outStream << "\",color=red,style=filled,fillcolor=\"#ffefef\"];\n";
        }
    }
   
    // For all unvisited adjacent zones.
    for (auto adjacentZones : it_holder->second) {
        outStream << adjacentZones.first << "[label=\"" << adjacentZones.first;
        if (visitedZones.find(adjacentZones.first) == visitedZones.end()) {
            if (keychain.find(adjacentZones.first) != keychain.end()) {
                outStream << "\\l" << keychain.find(adjacentZones.first)->second << "\",color=red,style=filled,fillcolor=\"#ffefef\"];\n";
            }
            else {
                outStream << "\",color=red,style=filled,fillcolor=\"#ffefef\"];\n";
            }
        }
        else {
            if (keychain.find(adjacentZones.first) != keychain.end()) {
                outStream << "\\l" << keychain.find(adjacentZones.first)->second << "\"];\n";
            }
            else {
                outStream << "\"];\n";
            }
        }
        outStream << it_holder->first << " -> " << adjacentZones.first;
        if (adjacentZones.second != "") {
            outStream << " [label=\"" << adjacentZones.second;
            outStream << "\"]";
        }
        outStream << ";\n";
    }
    outStream << "\n\n"; // For readability purposes there are two new line characters.
}


void generateDOTfile(const std::unordered_set<std::string>& visitedZones,
                     const graph& holder,
                     const std::unordered_map<std::string, std::string>& keychain) {
    std::ofstream outStream;
    outStream.open("graph.dot", std::ios::out);
    if (!outStream) {
        std::cerr << "Cannot open file for writing\n";
        return;
    }
    
    outStream << "digraph {\n";
    graph::const_iterator it_holder = holder.begin();
    std::unordered_set<std::string>::const_iterator it_visitedZones;
    std::unordered_map<std::string, std::string>::const_iterator it_keychain;
    
    // Checking all zones.
    while(it_holder != holder.end()) {
        // Check if the zone is. visited
        if (visitedZones.find(it_holder->first) != visitedZones.end()) {
            outStream << it_holder->first << "[label=\"" << it_holder->first;
            // Check if the zone has key.
            if (keychain.find(it_holder->first) != keychain.end()) {
                outStream << "\\l" << keychain.find(it_holder->first)->second << "\"];\n";
            }
            else {
                outStream << "\"];\n";
            }
            // For all adjacent zones.
            for (auto adjacentZones : it_holder->second) {
                // Check if the zone is not visited.
                if (visitedZones.find(adjacentZones.first) == visitedZones.end()) {
                    notVisitedAdjacent(outStream, keychain, it_holder, visitedZones);
                    break;
                }
                else {
                    outStream << it_holder->first << " -> " << adjacentZones.first;
                    if (adjacentZones.second != "") {
                        outStream << " [label=\"" << adjacentZones.second << "\"]";
                    }
                    outStream << ";\n";
                }
            }
        }
        else {
            notVisitedAdjacent(outStream, keychain, it_holder, visitedZones);
        }
        
        outStream << "\n\n"; // For readability purposes there are two new line characters.
        it_holder++;
    }
    
    
    outStream << '}';
    
    if (!outStream.good()) {
        std::cerr << "Error during writing occured\n";
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
    std::unordered_map<std::string, std::string> keychain; // A data structure which maps every zone to a key. The key can be taken from the zone.

    std::unordered_set<std::string> foundKeys; // A data structure where found keys will be saved.
    std::unordered_set<std::string> visitedZones; // A data structure where visited zones will be saved.
    
    addZones(stream, holder); // Reading the graph from the input file (Input 1).
    addKeysToZones(stream, keychain); // Reading information about key location.
    addMissedVertices(holder); // Add the vertices which don't have adjacent vertices but they themselves are adjacent vertices.

    
    BFStraversal(startingZone, holder, keychain, foundKeys, visitedZones); // Traversing the graph and finding the keys.
    
    stream.close();
    
   generateDOTfile(visitedZones, holder, keychain); // Generating output .dot file.
    
    return 0;
}
