//
//  main.cpp
//  DNSBL checker
//
// Alexander Krustev 
// Code ran and tested on Xcode 11.3.1
// Clang 11.0.0
//

#include <iostream>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

const std::string SPAM_HOUSE_STR = ".zen.spamhaus.org";

// Reverse the IP address
std::string convertIp(const std::string &ip) {
    std::string firstOctet;
    std::string secondOctet;
    std::string thirdOctet;
    std::string fourthOctet;
    
    size_t i = 0;
    for (; ip[i] != '.'; ++i) {
        firstOctet.push_back(ip[i]);
    }
    i++; // Skipping the '.'
    for (; ip[i] != '.'; ++i) {
        secondOctet.push_back(ip[i]);
    }
    i++; // Skipping the '.'
    for (; ip[i] != '.'; ++i) {
        thirdOctet.push_back(ip[i]);
    }
    i++; // Skipping the '.'
    for (; ip[i] != '\0'; ++i) {
        fourthOctet.push_back(ip[i]);
    }
    
    std::string newIp = "";
    
    newIp += fourthOctet;
    newIp += ".";
    newIp += thirdOctet;
    newIp += ".";
    newIp += secondOctet;
    newIp += ".";
    newIp += firstOctet;
    
    return newIp;
}

// Extract the fourth octet of the returned IP address
const std::string parseReturnedIp (const char* ip) {
    
    std::string fourthOctet = "";
    
    short cnt = 0; // Count of '.' in the ip address
    for (short i = 0; ip[i] != '\0'; ++i) {
        if (cnt == 3) {
            // If cnt is 3, the counter has reached the fourth octet of the address
            fourthOctet.push_back(ip[i]);
            continue;
        }
        if (ip[i] == '.') {
            cnt++;
        }
    }
    return fourthOctet;
}

void readReturnedCodes (const std::string& fourthOctet, const char* ip) {
        
    int val = std::stoi(fourthOctet); // Convert the fourth octet to a value
    switch (val) {
        case 2:
            std::cout << "The IP address: " << ip << " is found in the following Spamhaus public IP zone: '127.0.0.2 - SBL - Spamhaus SBL Data'\n";
            break;
        case 3:
            std::cout << "The IP address: " << ip << " is found in the following Spamhaus public IP zone: '127.0.0.3 - SBL - Spamhaus SBL CSS Data'\n";
            break;
        case 4:
            std::cout << "The IP address: " << ip << " is found in the following Spamhaus public IP zone: '127.0.0.4 - XBL - CBL Data'\n";
            break;
        case 9:
            std::cout << "The IP address: " << ip << " is found in the following Spamhaus public IP zone: '127.0.0.9 - SBL - Spamhaus DROP/EDROP Data'\n";
            break;
        case 10:
            std::cout << "The IP address: " << ip << " is found in the following Spamhaus public IP zone: '127.0.0.10 - PBL - ISP Maintained'\n";
            break;
        case 11:
            std::cout << "The IP address: " << ip << " is found in the following Spamhaus public IP zone: '127.0.0.11 - PBL - Spamhaus Maintained'\n";
            break;
            
    }
}


int main(int argc, const char* argv[])
{
    if (argc < 2) {
        std::cerr << "No arguments\n";
        return 1;
    }
    
    struct hostent *tmp = nullptr; // tmp is used to read the info in the DNS response
    char* returnedAddr = nullptr; // In returnedAddr is saved the returned address from the DNS query
    std::string hostname = ""; // hostname is the reversed IP concatenated with .zen.spamhause.org
    std::string fourthOctet = ""; // In fourthOctet is saved the fourth octet of the DNS response address
    
    for (size_t ipArg = 1; ipArg < argc; ++ipArg) {
        hostname = convertIp(argv[ipArg]); // Reverse the IP address
        hostname += SPAM_HOUSE_STR; // Create a hostname for the DNS query
        
        tmp = gethostbyname(hostname.c_str()); // Make a DNS query
        if (!tmp) {
            std::cout << "The IP address: " << argv[ipArg] << " is NOT found in the Spamhaus blacklists.\n";
            continue;
        }
        
        // Iterate through the array of IPs returned as a response from the DNS query
        for (int structAddr = 0; tmp->h_addr_list[structAddr] != NULL; ++structAddr) {
            
           struct in_addr* inAddrPtr = (struct in_addr *) tmp->h_addr_list[structAddr];
            returnedAddr = inet_ntoa(*inAddrPtr); // Convert the stored address to char*
            fourthOctet = parseReturnedIp(returnedAddr); // Get the fourth octet from the response of the DNS query
            readReturnedCodes(fourthOctet, argv[ipArg]); // Determine the zone of the IP
        }
    }
    

    return 0;
}
