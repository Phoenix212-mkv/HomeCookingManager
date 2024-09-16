#include <string>
#include<iostream>

class Product {
private:
    std::string name;   // Название продукта
    int quantity;       // Количество продукта в инвентаре
    std::string unit;   // Единица измерения (например, "кг", "л", "шт")

public:
    Product(const std::string& name, int quantity, const std::string& unit)
        : name(name), quantity(quantity), unit(unit) {}

    // Геттеры
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    std::string getUnit() const { return unit; }

    // Сеттеры
    void setQuantity(int newQuantity) { quantity = newQuantity; }
};