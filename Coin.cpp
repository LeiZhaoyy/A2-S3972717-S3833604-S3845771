#include "Coin.h"
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include <map> 
#include <iomanip> // for std::setw
#include <algorithm> 
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
void Coin::saveCoinsToFile(std::vector<Coin>& coins, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for saving coins." << std::endl;
        return;
    }

    for (auto& coin : coins) {
        file << static_cast<int>(coin.denom) << "," << coin.count << std::endl;
    }

    file.close();
}




void Coin::displayBalanceSummary(const std::vector<Coin>& coins) {
    // Display the Balance Summary header
    std::cout << "Balance Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denom  | Quantity | Value" << std::endl;
    std::cout << "---------------------------" << std::endl;

    // Map to store denomination values
    std::map<int, double> denomValue;

    // Calculate the value for each denomination
    for (const auto& coin : coins) {
        double value = coin.denom * coin.count / 100.0; // Convert denomination to dollars
        denomValue[coin.denom] = value;
    }

    // Sort the coins by denomination in ascending order
    std::vector<int> sortedDenoms;
    for (const auto& pair : denomValue) {
        sortedDenoms.push_back(pair.first);
    }
    std::sort(sortedDenoms.begin(), sortedDenoms.end());

    double totalValue = 0;

  
for (const auto& denom : sortedDenoms) {
    // Find the coin with the current denomination
    auto coinIt = std::find_if(coins.begin(), coins.end(), [&](const Coin& coin) {
        return coin.denom == denom;
    });

    // Output quantity and value
    if (coinIt != coins.end()) {
        std::cout << std::left << std::setw(6) << denom << " |";
        std::cout << std::setw(9) << coinIt->count << " |";
        std::cout << "$ " << std::setw(7) << std::fixed << std::setprecision(2) << denomValue[denom] << std::endl;
        totalValue += denomValue[denom]; // Accumulate total value
    }
}

    std::cout << "---------------------------" << std::endl;

    std::cout << std::endl << "$" << std::fixed << std::setprecision(2) << totalValue << std::endl;
}