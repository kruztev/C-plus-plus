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
    std::string first_octet;
    std::string second_octet;
    std::string third_octet;
    std::string fourth_octet;
    
    size_t i = 0;
    for (; ip[i] != '.'; ++i) {
        first_octet.push_back(ip[i]);
    }
    i++; // Skipping the '.'
    for (; ip[i] != '.'; ++i) {
        second_octet.push_back(ip[i]);
    }
    i++; // Skipping the '.'
    for (; ip[i] != '.'; ++i) {
        third_octet.push_back(ip[i]);
    }
    i++; // Skipping the '.'
    for (; ip[i] != '\0'; ++i) {
        fourth_octet.push_back(ip[i]);
    }
    
    std::string newIp = "";
    
    newIp += fourth_octet;
    newIp += ".";
    newIp += third_octet;
    newIp += ".";
    newIp += second_octet;
    newIp += ".";
    newIp += first_octet;
    
    return newIp;
}

// Extract the fourth octet of the returned IP address
const std::string parseReturnedIp (const char* ip) {
    
    std::string fourth_octet = "";
    
    short cnt = 0; // Count of '.' in the ip address
    for (short i = 0; ip[i] != '\0'; ++i) {
        if (cnt == 3) {
            fourth_octet.push_back(ip[i]);
            continue;
        }
        if (ip[i] == '.') {
            cnt++;
        }
    }
    return fourth_octet;
}

void readReturnedCodes (const std::string& fourth_octet, const char* ip) {
        
    int val = std::stoi(fourth_octet); // Convert the fourth octet to a value
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


int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "No arguments\n";
        return 1;
    }
    //std::cout << argv[1];
    
    struct hostent *tmp = nullptr; // tmp is used for the DNS response
    char* returnedAddr = nullptr; // In returnedAddr is saved the returned address from the DNS query
    std::string hostname = ""; // hostname is the reversed IP concatenated with .zen.spamhause.org
    std::string fourth_octet = ""; // In fourth_octet is saved the fourth octet of the DNS response address
    
    for (size_t ip_arg = 1; ip_arg < argc; ++ip_arg) {
        hostname = convertIp(argv[ip_arg]); // Reverse the IP address
        hostname += SPAM_HOUSE_STR; // Create a hostname for the DNS query
        
        tmp = gethostbyname(hostname.c_str()); // Make a DNS query
        if (!tmp) {
            std::cout << "The IP address: " << argv[ip_arg] << " is NOT found in the Spamhaus blacklists.\n";
            continue;
        }
        
        // Iterate through the array of IPs returned as a response from the DNS query
        for (int struct_addr = 0; tmp->h_addr_list[struct_addr] != NULL; ++struct_addr) {
            
           struct in_addr* in_addr_ptr = (struct in_addr *) tmp->h_addr_list[struct_addr];
            returnedAddr = inet_ntoa(*in_addr_ptr); // Convert the stored address to char*
            fourth_octet = parseReturnedIp(returnedAddr); // Get the fourth octet from the response of the DNS query
            readReturnedCodes(fourth_octet, argv[ip_arg]); // Determine the zone of the IP
        }
    }
    

    return 0;
}
