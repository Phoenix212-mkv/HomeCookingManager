#ifndef PRODUCTDATABASE_H
#define PRODUCTDATABASE_H

#include <string>
#include <map>
#include "Product.h"

class ProductDatabase {
private:
    std::map<int, Product> products_; // Хранение продуктов по ID
    std::string filename_; // Имя файла базы данных

public:
    // Конструктор с загрузкой данных из файла
    ProductDatabase(const std::string& filename);

    Product* findProductByName(const std::string& productName);

    // Загрузка и сохранение продуктов в файл
    void loadFromFile();
    void saveToFile() const;

    // Добавление, удаление и редактирование продукта
    bool addProduct(const Product& product);
    bool removeProduct(int productId);
    bool editProduct(int productId, const std::string& newName, const std::string& newUnit);

    // Поиск продукта по ID
    Product* findProduct(int productId);

    // Получение всех продуктов
    const std::map<int, Product>& getAllProducts() const;
};

#endif // PRODUCTDATABASE_H