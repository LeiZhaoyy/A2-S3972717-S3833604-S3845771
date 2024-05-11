#include "Coin.h"
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// Function to process the coins.dat file
std::vector<Coin> Coin::processCoinsFile(const string& filename) {
    vector<Coin> coins;  // Vector to store Coin objects
    ifstream file(filename);  // Open the file

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return coins;  // Return empty vector if file cannot be opened
    }

    string line;
    while (getline(file, line)) {  // Read file line by line
        stringstream ss(line);
        string token;

        // Split the line by delimiter ","
        if (getline(ss, token, ',')) {
            Coin coin;

            // Parse denomination from token and convert to enum
            coin.denom = static_cast<Denomination>(stoi(token));

            // Get count of coins from the next token
            if (getline(ss, token)) {
                coin.count = stoi(token);
                coins.push_back(coin);  // Add Coin object to vector
            } else {
                cerr << "Error: Missing count for denomination" << endl;
            }
        } else {
            cerr << "Error: Invalid line format" << endl;
        }
    }

    file.close();  // Close the file
    return coins;  // Return vector of Coin objects
}