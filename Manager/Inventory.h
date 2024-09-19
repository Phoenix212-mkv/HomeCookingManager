#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <string>
#include "Product.h"

// Предварительное объявление класса Recipe
class Recipe;

class Inventory
{
private:
    std::map<int, double> inventory_; // Хранит продукты и их количество {productId, quantity}
    std::map<int, Product> products_; // Список продуктов
    // Вспомогательный метод для поиска продукта в products.txt
    Product findProductInFile(int productId, const std::string& filename) const;

public:
    // Добавление продукта в инвентарь
    void addProduct(int productId, double quantity);

    // Добавление продукта в инвентарь по имени
    void addProductByName(const std::string& productName, double quantity);

    // Удаление продукта из инвентаря по имени
    void removeProductByName(const std::string& productName);

    // Установка конкретного количества продукта в инвентаре
    void modifyProductQuantity(int productId, double newQuantity);

    // Проверка наличия продукта в инвентаре
    bool hasProduct(int productId) const;

    // Уменьшение количества продукта по его ID
    bool reduceProductById(int productId, double quantity);

    // Получение названий продуктов и единиц измерения
    std::map<int, std::string> getProductNames() const;
    std::map<int, std::string> getProductUnits() const;

    // Получение текущего количества продукта
    double getProductQuantity(int productId) const;

    // Проверка наличия достаточного количества ингредиентов для рецепта
    bool canFulfillRecipe(const Recipe& recipe) const;

    // Уменьшение количества продуктов по рецепту
    bool useIngredientsForRecipe(const Recipe& recipe);

    // Сохранение данных инвентаря в файл
    void saveToFile(const std::string& filename) const;

    // Загрузка данных инвентаря из файла
    void loadFromFile(const std::string& filename);

    // Загрузка продуктов из файла
    void loadProductsFromFile(const std::string& filename);

    // Вывод текущего состояния инвентаря
    void printInventory(const std::map<int, std::string>& productNames) const;

    // Получить карту продуктов
    const std::map<int, Product>& getProducts() const { return products_; }

    // Удаление продукта из инвентаря
    void removeProductFromInventory(int productId);
};

#endif // INVENTORY_H