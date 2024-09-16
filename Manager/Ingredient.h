#include "Product.h"

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "Product.h"

class Ingredient {
private:
    Product product_;  // ������ ��������
    double quantity_;     // ���������� �����������

public:
    // �����������
    Ingredient(const Product& product, int quantity) : product_(product), quantity_(quantity) {};

    // ����� ��� ��������� ���������� �� �����������
    std::string getInfo() const 
    { return product_.getName() + ": " + std::to_string(quantity_) + product_.getUnit();}

    // ������ ��� ������� � ��������� ����������
    double getQuantity() const { return quantity_; }
    void setQuantity(int newQuantity) { quantity_ = newQuantity; }

    // ����� ��� ������� � ��������� ������� ��������
    Product getProduct() const { return product_; }
    void setProduct(const Product& newProduct) { product_ = newProduct; }
};

#endif // INGREDIENT_H