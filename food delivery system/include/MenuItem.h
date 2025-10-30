#pragma once
#include <string>

class MenuItem {
protected:
    std::string name;
    float price;
public:
    MenuItem(const std::string &n, float p) : name(n), price(p) {}
    virtual float getGST() const = 0; // Virtual Function
    virtual float getDiscount() const = 0;
    std::string getName() const { return name; }
    float getPrice() const { return price; }
    virtual ~MenuItem() {}
};

class FastFood : public MenuItem {
public:
    FastFood(const std::string &n, float p) : MenuItem(n, p) {}
    float getGST() const override { return 0.05f * price; }
    float getDiscount() const override { return 0.10f * price; }
};

class Beverage : public MenuItem {
public:
    Beverage(const std::string &n, float p) : MenuItem(n, p) {}
    float getGST() const override { return 0.12f * price; }
    float getDiscount() const override { return 0.05f * price; }
};

class Dessert : public MenuItem {
public:
    Dessert(const std::string &n, float p) : MenuItem(n, p) {}
    float getGST() const override { return 0.18f * price; }
    float getDiscount() const override { return 0.15f * price; }
};
