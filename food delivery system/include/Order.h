#pragma once
#include "MenuItem.h"
#include <vector>
#include <fstream>
#include <string>

class Order {
    std::vector<MenuItem*> cart; 
    std::string customerName;
public:
    Order(const std::string &name) : customerName(name) {}

    Order& operator+(MenuItem* item) {
        cart.push_back(item);
        return *this;
    }

    float totalBill() const {
        float total = 0;
        for(const auto &item : cart)
            total += item->getPrice() + item->getGST() - item->getDiscount();
        return total;
    }

    void storeOrderHistory() {
        std::ofstream file("data/orders.txt", std::ios::app); 
        file << "Customer: " << customerName << "\n";
        file << "Ordered Items: ";
        for(auto &item : cart)
            file << item->getName() << ", ";
        file << "\nTotal Bill: " << totalBill() << "\n---\n";
        file.close();
    }

    std::vector<std::string> getItemNames() const {
        std::vector<std::string> names;
        for(auto &item : cart)
            names.push_back(item->getName());
        return names;
    }

    ~Order() {

    }
};
