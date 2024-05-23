#ifndef COIN_H
#define COIN_H
//using namespace std;
#include <string> // Include for std::string
#include <vector>
#include <unordered_set> // Include for unordered_set

// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

// enumeration representing the various types of currency available in the system. 
// enum Denomination
// {
//     FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
//     TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS, TWENTY_DOLLARS
// };
enum Denomination
{
    FIVE_CENTS = 5, TEN_CENTS = 10, TWENTY_CENTS = 20, FIFTY_CENTS = 50,
    ONE_DOLLAR = 100, TWO_DOLLARS = 200, FIVE_DOLLARS = 500, TEN_DOLLARS = 1000, 
    TWENTY_DOLLARS = 2000, FIFTY_DOLLARS = 5000
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    // the denomination type
    enum Denomination denom;
    static void displayBalanceSummary(const std::vector<Coin>& coins);
    // the count of how many of these are in the cash register
    unsigned count;

    static std::vector<Coin> processCoinsFile(const std::string& filename);
    static void saveCoinsToFile(std::vector<Coin>& coins, const std::string& filename);

private:
    static bool isValidDenomination(int value);

};

#endif // COIN_H
