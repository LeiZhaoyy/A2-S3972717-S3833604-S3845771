#include "Node.h"


// Constructor
Node::Node() {
    data = new FoodItem(); // Allocate memory for the FoodItem object
    next = nullptr; // Initialize next pointer to nullptr
}

// Destructor
Node::~Node() {
    delete data; // Free the memory allocated for the FoodItem object
}