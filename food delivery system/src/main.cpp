#include <iostream>
#include <vector>
#include <limits>
#include "MenuItem.h"
#include "Order.h"

// Exception for closed restaurant
class RestaurantClosedException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Restaurant is closed!";
    }
};

int main() {
    bool restaurantOpen = true;
    try {
        if (!restaurantOpen)
            throw RestaurantClosedException();

        std::string customerName;
        std::cout << "--- Welcome to FoodExpress ---\n";
        std::cout << "Enter your name: ";
        std::getline(std::cin, customerName);

        // Prepare a menu
        std::vector<MenuItem*> menu;
        menu.push_back(new FastFood("Burger", 100));
        menu.push_back(new FastFood("Pizza", 150));
        menu.push_back(new Beverage("Cola", 40));
        menu.push_back(new Beverage("Coffee", 60));
        menu.push_back(new Dessert("Cake", 80));
        menu.push_back(new Dessert("Ice Cream", 50));

        // Show menu
        std::cout << "\n--- MENU ---\n";
        for (size_t i = 0; i < menu.size(); ++i) {
            std::cout << i + 1 << ". " << menu[i]->getName() << " - ₹" << menu[i]->getPrice() << std::endl;
        }

        // User orders
        Order order(customerName);
        char more;
        do {
            std::cout << "Enter item number to add to cart: ";
            size_t choice;
            std::cin >> choice;
            if (choice < 1 || choice > menu.size()) {
                std::cout << "Invalid choice! Try again.\n";
                continue;
            }
            order + menu[choice - 1]; // Operator overloading

            std::cout << "Add more items? (y/n): ";
            std::cin >> more;
            // Clear buffer in case of multiple newline reads
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        } while(more == 'y' || more == 'Y');

        // Show bill summary
        std::cout << "\n--- BILL SUMMARY ---\n";
        std::cout << "Customer: " << customerName << std::endl;
        std::cout << "Items Ordered:\n";
        auto itemNames = order.getItemNames();
        for (auto& nm : itemNames) std::cout << "- " << nm << std::endl;
        std::cout << "Total Bill (inc. GST/discount): ₹" << order.totalBill() << std::endl;

        order.storeOrderHistory();
        std::cout << "Order Stored Successfully\n";
        
        // Clean up dynamically allocated menu items (because Order only deletes those actually added)
        for(auto it : menu) delete it;
    }
    catch(const RestaurantClosedException &e) {
        std::cerr << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Something went wrong with your order!" << std::endl;
    }
    return 0;
}
