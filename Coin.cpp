

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
    cout <<  "                    $  " << fixed << setprecision(2) << totalValue << endl;
}