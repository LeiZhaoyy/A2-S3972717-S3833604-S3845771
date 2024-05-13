#include <iostream>
#include <limits>
#include "Coin.h"

#include "LinkedList.h"
#include "Helper.h"
#include <iomanip>

void purchaseMeal(LinkedList& foodList, const std::vector<Coin>& coins) {
    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;

    // Loop until a valid food ID is entered
    std::string foodId;
    FoodItem* foodItemPtr = nullptr;
    bool running = true;
    while (running) {
        // Display instructions
        std::cout << "Please enter the ID of the food you wish to purchase:" << std::endl;
        std::cin >> foodId;

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

    // Dereference the pointer to access the actual FoodItem object
    FoodItem foodItem = *foodItemPtr;

    // Display the selected food item and its price
    std::cout << "You have selected \"" << foodItem.name << " - " << foodItem.description << "\"." << std::endl;
    std::cout << "This will cost you $" << std::fixed << std::setprecision(2) << foodItem.price.dollars +
        (foodItem.price.cents / 100.0) << std::endl;

    // Collect payment from the user
    std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
    std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << std::endl;

    // Initialize variables to keep track of the total payment
    int totalPayment = foodItem.price.dollars * 100 + foodItem.price.cents;
    int remainingPayment = totalPayment;

    while (remainingPayment > 0) {
        std::cout << "You still need to give us $" << std::fixed << std::setprecision(2)
            << (remainingPayment / 100.0) << ": ";

        // Read the amount of money provided by the user
        int payment;
        std::cin >> payment;

        // Check if the input is valid
        if (std::cin.fail()) {
            std::cerr << "Error: Invalid input." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Update the remaining payment
        remainingPayment -= payment;

        // Check if the payment is sufficient
        if (remainingPayment < 0) {
            std::cerr << "Error: You have given too much money." << std::endl;
            std::cout << "Your change is $" << std::fixed << std::setprecision(2)
                << (-remainingPayment / 100.0) << std::endl;
            break;
        } else if (remainingPayment == 0) {
            std::cout << "Thank you for your payment." << std::endl;
            break;
        }
    }

    // If the purchase is cancelled, refund the payment
    if (remainingPayment > 0) {
        std::cout << "Refunding money..." << std::endl;
        //TODO
    }

    
}




int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " <foodsfile> <coinsfile>" << std::endl;
		return EXIT_FAILURE;
	}

	// Extract filenames from command line arguments
	std::string foodsFile = argv[1];
	std::string coinsFile = argv[2];

	// Create an instance of the LinkedList class
	LinkedList foodList;
    std::vector<Coin> coins = Coin::processCoinsFile(coinsFile);

	// Load food data from the specified file
	foodList.loadFromFile(foodsFile);
    bool running = true;

	while (running){
        Helper::printMainMenu();
		int option;
		std::cin>>option;
        std::cout << "Select your option (1-7) : " << std::endl;
		 
		if (option == 1){
                foodList.displayMenu();
                std::cout<<std::endl;
		}
        else if(option ==2){
			purchaseMeal(foodList, coins);
		}

		else if (option == 3){
			return EXIT_SUCCESS;
		}
        else if (option == 4) {
            foodList.addFoodItem();
        } else if (option == 5) {
            std::string foodId;
            std::cout << "Enter the food id of the food to remove from the menu: ";
            std::cin >> foodId;
            if (!foodList.removeFoodItemById(foodId)) {
                std::cout << "Food item with ID " << foodId << " not found." << std::endl;
            }
        }
        else if (option == 6){
            Coin::displayBalanceSummary(coins);
        }
        else{
            foodList.saveToFile(foodsFile);
            Coin::saveCoinsToFile(coins, coinsFile);
            running = false;
        }


	}





}


