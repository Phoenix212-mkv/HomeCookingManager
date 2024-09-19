#ifndef PRODUCTDATABASE_H
#define PRODUCTDATABASE_H

#include <string>
#include <map>
#include "Product.h"

class ProductDatabase {
private:
    std::map<int, Product> products_; // �������� ��������� �� ID
    std::string filename_; // ��� ����� ���� ������

public:
    // ����������� � ��������� ������ �� �����
    ProductDatabase(const std::string& filename);

    Product* findProductByName(const std::string& productName);

    // �������� � ���������� ��������� � ����
    void loadFromFile();
    void saveToFile() const;

    // ����������, �������� � �������������� ��������
    bool addProduct(const Product& product);
    bool removeProduct(int productId);
    bool editProduct(int productId, const std::string& newName, const std::string& newUnit);

    // ����� �������� �� ID
    Product* findProduct(int productId);

    // ��������� ���� ���������
    const std::map<int, Product>& getAllProducts() const;
};

#endif // PRODUCTDATABASE_H