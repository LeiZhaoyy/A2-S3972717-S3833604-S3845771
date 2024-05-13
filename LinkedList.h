#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    void insertNode(const FoodItem& food); // Insert a node into the linked list
    void displayList() const; // Display the linked list
    // more functions to be added perhaps...
    void displayMenu() const;
    void loadFromFile(const std::string& filename);

    FoodItem* getFoodItemById(const std::string& id) const;
    void saveToFile(const std::string& filename);
    void addFoodItem();
    bool removeFoodItemById(const std::string& id);
    
private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


