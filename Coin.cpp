// #include "Coin.h"
 
// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// using namespace std;
// #include <map> 
// #include <iomanip> // for std::setw
// #include <algorithm> 


// bool Coin::isValidDenomination(int value) {
//     static const unordered_set<int> validDenominations = {
//         FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS,
//         ONE_DOLLAR, TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS,
//         TWENTY_DOLLARS, FIFTY_DOLLARS
//     };

//     return validDenominations.find(value) != validDenominations.end();
// }




// // // Function to process the coins.dat file
// // std::vector<Coin> Coin::processCoinsFile(const string& filename) {
// //     vector<Coin> coins;  // Vector to store Coin objects
// //     ifstream file(filename);  // Open the file

// //     if (!file.is_open()) {
// //         cerr << "Error: Unable to open file " << filename << endl;
// //         return coins;  // Return empty vector if file cannot be opened
// //     }

// //     string line;
// //     while (getline(file, line)) {  // Read file line by line
// //         stringstream ss(line);
// //         string token;

// //         // Split the line by delimiter ","
// //         if (getline(ss, token, ',')) {
// //             Coin coin;

// //             // Parse denomination from token and convert to enum
// //             coin.denom = static_cast<Denomination>(stoi(token));

// //             // Get count of coins from the next token
// //             if (getline(ss, token)) {
// //                 coin.count = stoi(token);
// //                 coins.push_back(coin);  // Add Coin object to vector
// //             } else {
// //                 cerr << "Error: Missing count for denomination" << endl;
// //             }
// //         } else {
// //             cerr << "Error: Invalid line format" << endl;
// //         }
// //     }

// //     file.close();  // Close the file
// //     return coins;  // Return vector of Coin objects
// // }
// std::vector<Coin> Coin::processCoinsFile(const string& filename) {
//     vector<Coin> coins;  // Vector to store Coin objects
//     ifstream file(filename);  // Open the file

//     if (!file.is_open()) {
//         cerr << "Error: Unable to open file " << filename << endl;
//         return coins;  // Return empty vector if file cannot be opened
//     }

//     string line;
//     while (getline(file, line)) {  // Read file line by line
//         stringstream ss(line);
//         string token;
//         Coin coin;
//         bool validLine = false;

//         // Split the line by delimiter ","
//         if (getline(ss, token, ',')) {
//             int denomValue = stoi(token);

//             // Validate the denomination
//             if (isValidDenomination(denomValue)) {
//                 // Parse denomination from token and convert to enum
//                 coin.denom = static_cast<Denomination>(denomValue);

//                 // Get count of coins from the next token
//                 if (getline(ss, token)) {
//                     coin.count = stoi(token);
//                     validLine = true;
//                 } else {
//                     cerr << "Error: Missing count for denomination" << endl;
//                 }
//             } else {
//                 cerr << "Error: Invalid denomination " << denomValue << " in line: " << line << endl;
//             }
//         } else {
//             cerr << "Error: Invalid line format" << endl;
//         }

//         if (validLine) {
//             coins.push_back(coin);  // Add Coin object to vector only if the line is valid
//         }
//     }

//     file.close();  // Close the file
//     return coins;  // Return vector of Coin objects
// }






// void Coin::saveCoinsToFile(std::vector<Coin>& coins, const std::string& filename) {
//     std::ofstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error: Unable to open file for saving coins." << std::endl;
//         return;
//     }

//     for (auto& coin : coins) {
//         file << static_cast<int>(coin.denom) << "," << coin.count << std::endl;
//     }

//     file.close();
// }




// void Coin::displayBalanceSummary(const std::vector<Coin>& coins) {
//     // Display the Balance Summary header
//     std::cout << "Balance Summary" << std::endl;
//     std::cout << "-------------" << std::endl;
//     std::cout << "Denom  | Quantity | Value" << std::endl;
//     std::cout << "---------------------------" << std::endl;

//     // Map to store denomination values
//     std::map<int, double> denomValue;

//     // Calculate the value for each denomination
//     for (const auto& coin : coins) {
//         double value = coin.denom * coin.count / 100.0; // Convert denomination to dollars
//         denomValue[coin.denom] = value;
//     }

//     // Sort the coins by denomination in ascending order
//     std::vector<int> sortedDenoms;
//     for (const auto& pair : denomValue) {
//         sortedDenoms.push_back(pair.first);
//     }
//     std::sort(sortedDenoms.begin(), sortedDenoms.end());

//     double totalValue = 0;

  
// for (const auto& denom : sortedDenoms) {
//     // Find the coin with the current denomination
//     auto coinIt = std::find_if(coins.begin(), coins.end(), [&](const Coin& coin) {
//         return coin.denom == denom;
//     });

//     // Output quantity and value
//     if (coinIt != coins.end()) {
//         std::cout << std::left << std::setw(6) << denom << " |";
//         std::cout << std::setw(9) << coinIt->count << " |";
//         std::cout << "$ " << std::setw(7) << std::fixed << std::setprecision(2) << denomValue[denom] << std::endl;
//         totalValue += denomValue[denom]; // Accumulate total value
//     }
// }

//     std::cout << "---------------------------" << std::endl;

//     std::cout << std::endl << "$" << std::fixed << std::setprecision(2) << totalValue << std::endl;
// }


#include "Coin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <map> 
#include <iomanip>
#include <algorithm>

using namespace std;

bool Coin::isValidDenomination(int value) {
    static const unordered_set<int> validDenominations = {
        FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS,
        ONE_DOLLAR, TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS,
        TWENTY_DOLLARS, FIFTY_DOLLARS
    };

    return validDenominations.find(value) != validDenominations.end();
}

std::vector<Coin> Coin::processCoinsFile(const string& filename) {
    vector<Coin> coins;
    ifstream file(filename);
    bool hasError = false;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        hasError = true;
    }

    string line;
    while (!hasError && getline(file, line)) {
        stringstream ss(line);
        string token;
        Coin coin;

        if (getline(ss, token, ',')) {
            int denomValue = stoi(token);

            if (isValidDenomination(denomValue)) {
                coin.denom = static_cast<Denomination>(denomValue);

                if (getline(ss, token)) {
                    coin.count = stoi(token);
                    coins.push_back(coin);
                } else {
                    cerr << "Error: Missing count for denomination" << endl;
                    hasError = true;
                }
            } else {
                cerr << "Error: Invalid denomination " << denomValue << " in line: " << line << endl;
                hasError = true;
            }
        } else {
            cerr << "Error: Invalid line format" << endl;
            hasError = true;
        }
    }

    file.close();

    if (hasError) {
        coins.clear();
    }

    return coins;
}


void Coin::saveCoinsToFile(std::vector<Coin>& coins, const std::string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for saving coins." << endl;
        return;
    }

    for (auto& coin : coins) {
        file << static_cast<int>(coin.denom) << "," << coin.count << endl;
    }

    file.close();
}



void Coin::displayBalanceSummary(const std::vector<Coin>& coins) {
    cout << "Balance Summary" << endl;
    cout << "-------------" << endl;
    cout << "Denom  | Quantity | Value" << endl;
    cout << "---------------------------" << endl;

    map<int, double> denomValue;

    for (const auto& coin : coins) {
        double value = coin.denom * coin.count / 100.0;
        denomValue[coin.denom] = value;
    }

    vector<int> sortedDenoms;
    for (const auto& pair : denomValue) {
        sortedDenoms.push_back(pair.first);
    }
    sort(sortedDenoms.begin(), sortedDenoms.end());

    double totalValue = 0;
    int valueWidth = 7; // Width for the values to be right-aligned

    for (const auto& denom : sortedDenoms) {
        auto coinIt = find_if(coins.begin(), coins.end(), [&](const Coin& coin) {
            return coin.denom == denom;
        });

        if (coinIt != coins.end()) {
            cout << left << setw(6) << denom << " | ";
            cout << setw(9) << coinIt->count << " |";
            cout << "$ " << setw(valueWidth) << right << fixed << setprecision(2) << denomValue[denom] << endl;
            totalValue += denomValue[denom];
        }
    }

    cout << "---------------------------" << endl;
    cout << endl << "$" << fixed << setprecision(2) << totalValue << endl;
}