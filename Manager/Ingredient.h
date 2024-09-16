#include "Product.h"

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "Product.h"

class Ingredient {
private:
    Product product_;  // Объект продукта
    double quantity_;     // Количество ингредиента

public:
    // Конструктор
    Ingredient(const Product& product, int quantity) : product_(product), quantity_(quantity) {};

    // Метод для получения информации об ингредиенте
    std::string getInfo() const 
    { return product_.getName() + ": " + std::to_string(quantity_) + product_.getUnit();}

    // Методы для доступа и изменения количества
    double getQuantity() const { return quantity_; }
    void setQuantity(int newQuantity) { quantity_ = newQuantity; }

    // Метод для доступа и изменения объекта продукта
    Product getProduct() const { return product_; }
    void setProduct(const Product& newProduct) { product_ = newProduct; }
};

#endif // INGREDIENT_H