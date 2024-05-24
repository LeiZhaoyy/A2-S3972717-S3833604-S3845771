







//HAIHSDFKJBDF



#include "LinkedList.h"
#include <iostream>
#include <iomanip> // For setw
#include <fstream>
#include <sstream>
#include <algorithm>

// Constructor
LinkedList::LinkedList() : head(nullptr), count(0) {}

// Destructor
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current; // Delete the node
        current = next;
    }
}

// Function to insert a node into the linked list in alphabetical order
void LinkedList::insertNode(const FoodItem& food) {
    Node* newNode = new Node(); // Create a new node
    newNode->data = new FoodItem(food); // Copy the FoodItem data to the new node

    if (head == nullptr || head->data->name > food.name) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->data->name < food.name) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    count++;
}

// Function to display the food menu
void LinkedList::displayMenu() const {
    std::cout << "Food Menu" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "ID   |Name                                     |Price" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    displayList();
}

// Function to display the food items in the linked list
void LinkedList::displayList() const {
    Node* current = head;
    int maxPriceWidth = 0;

    // First pass to determine the max width of the price field
    while (current != nullptr) {
        double price = current->data->price.dollars + (current->data->price.cents / 100.0);
        int priceWidth = std::to_string(static_cast<int>(price)).length() + 3; // 3 for decimal point and cents (e.g., 8.50)
        if (priceWidth > maxPriceWidth) {
            maxPriceWidth = priceWidth;
        }
        current = current->next;
    }

    // Second pass to display the items
    current = head;
    while (current != nullptr) {
        // Format and print each food item
        std::cout << current->data->id << " |";
        std::cout << std::left << std::setw(40) << current->data->name << " |";
        std::cout << std::right << "$" << std::setw(maxPriceWidth) << std::fixed << std::setprecision(2)
                  << current->data->price.dollars + (current->data->price.cents / 100.0) << std::endl;
        current = current->next;
    }
}

// Function to load food items from a file and insert them alphabetically
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, description, priceStr;

        // Read data separated by '|'
        if (std::getline(iss, id, '|') >> std::ws &&
            std::getline(iss, name, '|') >> std::ws &&
            std::getline(iss, description, '|') >> std::ws &&
            std::getline(iss, priceStr)) {

            // Convert price string to double
            std::istringstream priceStream(priceStr);
            double price;
            if (priceStream >> price) {
                // Create FoodItem object
                FoodItem foodItem;
                foodItem.id = id;
                foodItem.name = name;
                foodItem.description = description;
                foodItem.price.dollars = static_cast<unsigned>(price);
                foodItem.price.cents = static_cast<unsigned>((price - static_cast<int>(price)) * 100);

                // Insert into linked list alphabetically
                insertNode(foodItem);
            } else {
                std::cerr << "Error: Invalid price format." << std::endl;
            }
        } else {
            std::cerr << "Error: Invalid line format." << std::endl;
        }
    }

    file.close();
}

FoodItem* LinkedList::getFoodItemById(const std::string& id) const {
    Node* current = head;
    FoodItem* foundItem = nullptr; // Initialize foundItem to nullptr
    bool found = false; // Initialize found flag to false

    while (current != nullptr && !found) { // Continue while loop until found or end of list
        if (current->data->id == id) {
            foundItem = current->data; // Assign the matching FoodItem to foundItem
            found = true; // Set found flag to true
        }
        current = current->next;
    }

    return foundItem; // Return foundItem (nullptr if not found)
}

void LinkedList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for saving." << std::endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        file << current->data->id << "|"
             << current->data->name << "|"
             << current->data->description << "|"
             << current->data->price.dollars + (current->data->price.cents / 100.0) << std::endl;
        current = current->next;
    }

    file.close();
}

// void LinkedList::addFoodItem() {
//     FoodItem newFood;
//     std::string name, description;
//     double price;

//     // Generate the next food item ID
//     unsigned nextID = count + 1; // Assuming 'count' tracks the number of FoodItems
//     newFood.id = "F" + std::to_string(nextID);
//     while (newFood.id.length() < 5) {
//         newFood.id.insert(1, "0"); // Ensure the ID is 5 characters long
//     }

//     // Prompt user for food item details
//     std::cout << "This new meal item will have the Item id of " << newFood.id << "." << std::endl;
//     std::cout << "Enter the item name: ";
//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character left in the input buffer
//     getline(std::cin, name);
//     newFood.name = name;

//     std::cout << "Enter the item description: ";
//     getline(std::cin, description);
//     newFood.description = description;

//     // Error check for the price input
//     bool validPrice = false;
//     while (!validPrice) {
//         std::cout << "Enter the price for this item (in dollars): ";
//         if (!(std::cin >> price)) {
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             std::cout << "Invalid input. Please enter a valid price." << std::endl;
//         } else if (price <= 0) {
//             std::cout << "Price must be greater than zero. Please enter a valid price." << std::endl;
//         } else {
//             validPrice = true;
//         }
//     }

//     newFood.price.dollars = static_cast<unsigned>(price);
//     newFood.price.cents = static_cast<unsigned>((price - newFood.price.dollars) * 100);

//     // Assign default on-hand value
//     newFood.on_hand = DEFAULT_FOOD_STOCK_LEVEL;

//     // Insert the new food item into the list in alphabetical order
//     insertNode(newFood);

//     // Output the confirmation message
//     std::cout << "This item \"" << newFood.name << " - " << newFood.description
//               << "\" has now been added to the food menu." << std::endl;
// }

void LinkedList::addFoodItem() {
    FoodItem newFood;
    std::string name, description;
    double price;
    auto h = head;
    while (h->next != nullptr)  h = h->next;

    std::string numericPart = h->data->id.substr(1);

    int number = std::stoi(numericPart);

    number++;

    std::stringstream ss;
    ss << "F" << std::setw(4) << std::setfill('0') << number;


    // Generate the next food item ID
    unsigned nextID = count + 1; // Assuming 'count' tracks the number of FoodItems
    newFood.id = "F" + std::to_string(nextID);
    while (newFood.id.length() < 5) {
        newFood.id.insert(1, "0"); // Ensure the ID is 5 characters long
    }

    // Prompt user for food item details
    std::cout << "This new meal item will have the Item id of " << newFood.id << "." << std::endl;
    std::cout << "Enter the item name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character left in the input buffer
    getline(std::cin, name);
    newFood.name = name;

    std::cout << "Enter the item description: ";
    getline(std::cin, description);
    newFood.description = description;

    // Error check for the price input
    bool validPrice = false;
    while (!validPrice) {
        std::cout << "Enter the price for this item (in dollars): ";
        if (!(std::cin >> price)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid price." << std::endl;
        } else if (price <= 0) {
            std::cout << "Price must be greater than zero. Please enter a valid price." << std::endl;
        } else {
            validPrice = true;
        }
    }

    newFood.price.dollars = static_cast<unsigned>(price);
    newFood.price.cents = static_cast<unsigned>((price - newFood.price.dollars) * 100);

    // Assign default on-hand value
    newFood.on_hand = DEFAULT_FOOD_STOCK_LEVEL;

    // Insert the new food item into the list in alphabetical order
    insertNode(newFood);

    // Output the confirmation message
    std::cout << "This item \"" << newFood.name << " - " << newFood.description
              << "\" has now been added to the food menu." << std::endl;
}








bool LinkedList::removeFoodItemById(const std::string& id) {
    Node* current = head;
    Node* previous = nullptr;
    bool found = false;

    while (current != nullptr && !found) {
        if (current->data->id == id) {
            found = true;
            if (previous == nullptr) {
                // Removing the head of the list
                head = current->next;
            } else {
                // Bypass the current node
                previous->next = current->next;
            }
            // Output the confirmation message
            std::cout << "\"" << current->data->id << " – " << current->data->name << " - "
                    << current->data->description << "\" has been removed from the system." << std::endl;

            // Free memory and delete the node
            delete current;
        } else {
            previous = current;
            current = current->next;
        }
    }

    return found; // Return false if not found
}
