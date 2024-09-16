#ifndef PRODUCT_H
#define PRODUCT_H


#include <string>
#include<iostream>

class Product {
private:
    std::string name_;   // Название продукта
    std::string unit_;   // Единица измерения (например, "кг", "л", "шт")

public:
    Product(const std::string& name, int quantity, const std::string& unit)
        : name_(name), unit_(unit) {}

    // Геттеры
    std::string getName() const { return name_; }
    std::string getUnit() const { return unit_; }

    // Сеттеры
    void setName(std::string name) { name_ = name; }
    void setUnit(std::string unit) { unit_ = unit; }

};

#endif // !PRODUCT_H