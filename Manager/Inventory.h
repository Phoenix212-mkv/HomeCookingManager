#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <string>
#include "Product.h"

// ��������������� ���������� ������ Recipe
class Recipe;

class Inventory
{
private:
    std::map<int, double> inventory_; // ������ �������� � �� ���������� {productId, quantity}
    std::map<int, Product> products_; // ������ ���������
    // ��������������� ����� ��� ������ �������� � products.txt
    Product findProductInFile(int productId, const std::string& filename) const;

public:
    // ���������� �������� � ���������
    void addProduct(int productId, double quantity);

    // ���������� �������� � ��������� �� �����
    void addProductByName(const std::string& productName, double quantity);

    // �������� �������� �� ��������� �� �����
    void removeProductByName(const std::string& productName);

    // ��������� ����������� ���������� �������� � ���������
    void modifyProductQuantity(int productId, double newQuantity);

    // �������� ������� �������� � ���������
    bool hasProduct(int productId) const;

    // ���������� ���������� �������� �� ��� ID
    bool reduceProductById(int productId, double quantity);

    // ��������� �������� ��������� � ������ ���������
    std::map<int, std::string> getProductNames() const;
    std::map<int, std::string> getProductUnits() const;

    // ��������� �������� ���������� ��������
    double getProductQuantity(int productId) const;

    // �������� ������� ������������ ���������� ������������ ��� �������
    bool canFulfillRecipe(const Recipe& recipe) const;

    // ���������� ���������� ��������� �� �������
    bool useIngredientsForRecipe(const Recipe& recipe);

    // ���������� ������ ��������� � ����
    void saveToFile(const std::string& filename) const;

    // �������� ������ ��������� �� �����
    void loadFromFile(const std::string& filename);

    // �������� ��������� �� �����
    void loadProductsFromFile(const std::string& filename);

    // ����� �������� ��������� ���������
    void printInventory(const std::map<int, std::string>& productNames) const;

    // �������� ����� ���������
    const std::map<int, Product>& getProducts() const { return products_; }

    // �������� �������� �� ���������
    void removeProductFromInventory(int productId);
};

#endif // INVENTORY_H