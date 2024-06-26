#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "LinkedList.h"
#include "Coin.h"
#include "Helper.h"





void updateCoins(std::vector<Coin>& coins, int denomination, int count) {
    for (auto& coin : coins) {
        if (coin.denom == denomination) {
            coin.count += count;
            return; // Exit the function once the denomination is found and updated
        }
    }
    // Handle case where the denomination was not found, if necessary
}

bool provideChange(std::vector<Coin>& coins, int change) {
    std::vector<std::pair<int, int>> changeGiven;
    bool success = true;
    bool done = false;

    for (auto& coin : coins) {
        if (!done) {
            int denomValue = coin.denom;
            int numCoins = std::min(change / denomValue, static_cast<int>(coin.count)); // Cast coin.count to int
            if (numCoins > 0) {
                changeGiven.push_back({denomValue, numCoins});
                change -= numCoins * denomValue;
                coin.count -= numCoins;
            }

            if (change <= 0) {
                done = true;
            }
        }
    }

    if (change > 0) {
        success = false;
    }

    if (success) {
        // Display the change given
        std::cout << "Your change is:" << std::endl;
        for (const auto& cg : changeGiven) {
            std::cout << "$" << std::fixed << std::setprecision(2) << cg.first / 100.0 << " x " << cg.second << std::endl;
        }
    } else {
        // If unable to provide exact change, refund the coins added back to the vector
        for (const auto& cg : changeGiven) {
            updateCoins(coins, cg.first, cg.second);
        }
        std::cout << "Sorry, unable to provide exact change. Transaction cancelled." << std::endl;
    }

    return success;
}

int roundToNearest(int amount, int nearest) {
    return std::round(static_cast<double>(amount) / nearest) * nearest;
}

void purchaseMeal(LinkedList& foodList, std::vector<Coin>& coins) {
    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;

    // Loop until a valid food ID is entered
    std::string foodId;
    FoodItem* foodItemPtr = nullptr;
    bool running = true;
    bool cancel = false;

    while (running) {
        // Display instructions
        std::cout << "Please enter the ID of the food you wish to purchase:" << std::endl;
        std::cin >> foodId;

        // Check for EOF (Ctrl-D) to cancel
        if (std::cin.eof()) {
            std::cin.clear();
            cancel = true;
            running = false;
        } else {
            // Retrieve the FoodItem from the linked list based on the provided ID
            foodItemPtr = foodList.getFoodItemById(foodId);

            // Check if the food item exists
            if (foodItemPtr == nullptr) {
                std::cerr << "Error: Food item not found. Please try again." << std::endl;
            } else {
                // If food ID exists, break out of the loop
                running = false;
            }
        }
    }

    if (!cancel && foodItemPtr != nullptr) {
        // Dereference the pointer to access the actual FoodItem object
        FoodItem foodItem = *foodItemPtr;

        // Display the selected food item and its price
        std::cout << "You have selected \"" << foodItem.name << " - " << foodItem.description << "\"." << std::endl;
        int priceInCents = foodItem.price.dollars * 100 + foodItem.price.cents;
        int roundedPriceInCents = roundToNearest(priceInCents, 5); // Round to the nearest 5 cents
        std::cout << "This will cost you $" << std::fixed << std::setprecision(2)
                  << roundedPriceInCents / 100.0 << " (rounded to the nearest 5 cents)" << std::endl;

        // Collect payment from the user
        std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
        std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << std::endl;

        // Initialize variables to keep track of the total payment
        int totalPayment = roundedPriceInCents;
        int remainingPayment = totalPayment;
        running = true;

        while (running && remainingPayment > 0) {
            std::cout << "You still need to give us $ " << std::fixed << std::setprecision(2)
                      << (remainingPayment / 100.0) << ": ";

            int payment;
            std::cin >> payment;

            // Check for EOF (Ctrl-D) to cancel
            if (std::cin.eof()) {
                std::cin.clear();
                cancel = true;
                running = false;
            } else {
                // Extract denominations from the coins vector
                std::vector<int> denominations;
                for (const Coin& coin : coins) {
                    denominations.push_back(coin.denom);
                }

                // Check if the input is valid and matches any of the allowed denominations
                while (!cancel && (std::cin.fail() || std::find(denominations.begin(), denominations.end(), payment) == denominations.end())) {
                    std::cerr << "Error: Invalid input or denomination. Please use one of the allowed denominations." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Please enter a valid denomination: ";
                    std::cin >> payment;

                    // Check for EOF (Ctrl-D) again after error correction
                    if (std::cin.eof()) {
                        std::cin.clear();
                        cancel = true;
                        running = false;
                    }
                }

                if (!cancel) {
                    // Update the remaining payment and the coins vector
                    remainingPayment -= payment;
                    updateCoins(coins, payment, 1); // Add the coin to the balance
                }
            }
        }

        if (!cancel) {
            if (remainingPayment < 0) {
                // Provide change if the user overpaid
                int change = -remainingPayment;
                if (!provideChange(coins, change)) {
                    std::cout << "Sorry, unable to provide exact change. Transaction cancelled." << std::endl;
                    updateCoins(coins, totalPayment - remainingPayment, -1); // Refund the payment
                } else {
                    std::cout << "Thank you for your payment." << std::endl;
                }
            } else if (remainingPayment == 0) {
                std::cout << "Thank you for your payment." << std::endl;
            } else {
                std::cout << "Refunding money..." << std::endl;
                updateCoins(coins, totalPayment - remainingPayment, -1); // Refund the payment
            }
        }
    }

    if (cancel) {
        std::cout << "Purchase cancelled." << std::endl;
    }
}




int main(int argc, char** argv) {
    bool hasError = false;
    int exitCode = EXIT_SUCCESS;

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <foodsfile> <coinsfile>" << std::endl;
        hasError = true;
        exitCode = EXIT_FAILURE;
    }

    std::string foodsFile;
    std::string coinsFile;
    LinkedList foodList;
    std::vector<Coin> coins;

    if (!hasError) {
        // Extract filenames from command line arguments
        foodsFile = argv[1];
        coinsFile = argv[2];

        // Process the coin file
        coins = Coin::processCoinsFile(coinsFile);

        // Check if there was an error in processing the coin file
        if (coins.empty()) {
            std::cerr << "Error: Invalid coin file or file contains invalid denominations." << std::endl;
            hasError = true;
            exitCode = EXIT_FAILURE;
        }
    }
    if (!(foodList.loadFromFile(foodsFile))){
            hasError = true;
        }
    if (!hasError) {
        bool running = true;
        while (running) {
            bool validInput = false;
            int option = -1;

            while (!validInput) {
                Helper::printMainMenu();
                std::cout << "Select your option (1-7)  : ";
                std::cin >> option;

                if (std::cin.eof()) {
                    // Handle Ctrl-D input
                    std::cout << "Exiting program..." << std::endl;
                    running = false;
                    validInput = true;
                } else if (std::cin.fail()) {
                    std::cin.clear(); // clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                    std::cout << "Invalid input. Please enter a number between 1 and 7." << std::endl;
                } else if (option < 1 || option > 7) {
                    std::cout << "Invalid choice. Please select a valid option (1-7)." << std::endl;
                } else {
                    validInput = true;
                }
            }

            if (running) {
                if (option == 1) {
                    foodList.displayMenu();
                    std::cout << std::endl;
                } else if (option == 2) {
                    purchaseMeal(foodList, coins);
                } else if (option == 3) {
                    foodList.saveToFile(foodsFile);
                    Coin::saveCoinsToFile(coins, coinsFile);
                    running = false;
                } else if (option == 4) {
                    foodList.addFoodItem();
                } else if (option == 5) {
                    std::string foodId;
                    std::cout << "Enter the food id of the food to remove from the menu: ";
                    std::cin >> foodId;
                    if (std::cin.eof()) {
                        std::cout << "Exiting program..." << std::endl;
                        running = false;
                    } else if (!foodList.removeFoodItemById(foodId)) {
                        std::cout << "Food item with ID " << foodId << " not found." << std::endl;
                    }
                } else if (option == 6) {
                    Coin::displayBalanceSummary(coins);
                } else if (option == 7) {
                    foodList.saveToFile(foodsFile);
                    Coin::saveCoinsToFile(coins, coinsFile);
                    running = false;
                }
            }
        }
    }

    return exitCode;
}