#include <iostream>
#include "LinkedList.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/



int main(int argc, char **argv)
{
    /* validate command line arguments */
    bool running = true;
    while (running){ 

 if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <foodsfile> <coinsfile>" << std::endl;
        running = false;
    }

    // Extract filenames from command line arguments
    std::string foodsFile = argv[1];
    std::string coinsFile = argv[2];

    // Create an instance of the LinkedList class
    LinkedList foodList;

    // Load food data from the specified file
    foodList.loadFromFile(foodsFile);

    // Now foodList contains the loaded food data, you can use it to display the menu or perform other operations






    std::cout << "Main Menu" << std::endl;
    std::cout << "    1. Display Meal Options" << std::endl;
    std::cout << "    2. Purchase Meal" << std::endl;
    std::cout << "    3. Save and Exit" << std::endl;
    std::cout << "Administrator-Only Menu:" << std::endl;
    std::cout << "    4. Add Food" << std::endl;
    std::cout << "    5. Remove Food" << std::endl;
    std::cout << "    6. Display Balance" << std::endl;
    std::cout << "    7. Display Balance" << std::endl;
std::cout << "Select your option (1-7) :"<<std::endl;
            int choice;

            std::cin >> choice;


    if (choice == 1){
            foodList.displayMenu();

    }
    else{
        running = false;
    }
    }
   
    
    return EXIT_SUCCESS;
}
