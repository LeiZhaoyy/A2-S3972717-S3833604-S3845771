#include "LinkedList.h"
#include <iostream>
#include <iomanip> // For setw
#include <fstream>
#include <sstream>

// Constructor
LinkedList::LinkedList() : head(nullptr), count(0)  {}

// Destructor
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current; // Delete the node
        current = next;
    }
}

// Function to insert a node into the linked list
void LinkedList::insertNode(const FoodItem& food) {
    Node* newNode = new Node(); // Create a new node
    newNode->data = new FoodItem(food); // Copy the FoodItem data to the new node
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
        count++;

}


void LinkedList::displayMenu() const {
    std::cout << "Food Menu" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "ID   |Name                                     |Length" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    displayList();
}

void LinkedList::displayList() const {
    Node* current = head;
    while (current != nullptr) {
        // Format and print each food item
        std::cout << current->data->id << "|";
        std::cout << std::left << std::setw(40) << current->data->name << " |";
        std::cout << "$" << std::fixed << std::setprecision(2) << current->data->price.dollars + (current->data->price.cents / 100.0) << std::endl;
        current = current->next;
    }
}



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

                // Insert into linked list
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
void LinkedList::addFoodItem() {
    getchar();
    FoodItem newFood;
    std::string name, description;
    double price;

    // Generate the next food item ID
    unsigned nextID = count + 1; // Assuming 'count' tracks the number of FoodItems
    newFood.id = "F" + std::to_string(nextID);
    while(newFood.id.length() < 5) {
        newFood.id.insert(1, "0"); // Ensure the ID is 5 characters long
    }

    // Prompt user for food item details
    std::cout << "This new meal item will have the Item id of " << newFood.id << "." << std::endl;
    std::cout << "Enter the item name: ";
    std::cin.ignore(); // Important to clear the newline character left in the input buffer
    getline(std::cin, name);
    newFood.name = name;

    std::cout << "Enter the item description: ";
    getline(std::cin, description);
    newFood.description = description;

    std::cout << "Enter the price for this item (in cents): ";
    std::cin >> price; // Assuming the input is in dollars, not cents, based on the format "8.00"
    newFood.price.dollars = static_cast<unsigned>(price);
    newFood.price.cents = static_cast<unsigned>((price - newFood.price.dollars) * 100);

    // Assign default on-hand value
    newFood.on_hand = DEFAULT_FOOD_STOCK_LEVEL;

    // Insert the new food item into the list
    insertNode(newFood);

    // Output the confirmation message
    std::cout << "This item \"" << newFood.name << " - " << newFood.description
              << "\" has now been added to the food menu." << std::endl;
}
bool LinkedList::removeFoodItemById(const std::string& id) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data->id == id) {
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
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false; // Return false if not found
}