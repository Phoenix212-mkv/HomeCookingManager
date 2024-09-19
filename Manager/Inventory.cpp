#include "Inventory.h"
#include "Recipe.h"
#include <iostream>
#include <fstream>
#include <sstream>



// Добавление продукта в инвентарь
void Inventory::addProduct(int productId, double quantity) {
    // Попробуем найти продукт в products.txt
    Product product = findProductInFile(productId, "products.txt");

    if (product.getId() != 0) { // Если продукт найден (проверяем по ID)
        if (inventory_.find(productId) == inventory_.end()) {
            // Добавляем новый продукт в инвентарь
            inventory_[productId] = quantity;
            products_[productId] = product;
        }
        else {
            // Обновляем количество существующего продукта
            inventory_[productId] += quantity;
        }
    }
    else {
        std::cerr << "Product with ID " << productId << " does not exist in the possible products list.\n";
    }
}

void Inventory::addProductByName(const std::string& productName, double quantity) {
    // Поиск продукта по имени
    auto it = std::find_if(products_.begin(), products_.end(),
        [&productName](const auto& pair) { return pair.second.getName() == productName; });

    if (it != products_.end()) {
        int productId = it->first;
        inventory_[productId] += quantity;
        std::cout << "Product '" << productName << "' added to inventory with quantity " << quantity << ".\n";
    }
    else {
        std::cerr << "Product '" << productName << "' not found in product database.\n";
    }
}

void Inventory::removeProductByName(const std::string& productName) {
    // Поиск продукта по имени
    auto it = std::find_if(products_.begin(), products_.end(),
        [&productName](const auto& pair) { return pair.second.getName() == productName; });

    if (it != products_.end()) {
        int productId = it->first;
        // Проверяем, есть ли продукт в инвентаре
        if (inventory_.find(productId) != inventory_.end()) {
            removeProductFromInventory(productId);
            std::cout << "Product '" << productName << "' removed from inventory.\n";
        }
        else {
            std::cerr << "Product '" << productName << "' not found in inventory.\n";
        }
    }
    else {
        std::cerr << "Product '" << productName << "' not found in product database.\n";
    }
}

void Inventory::modifyProductQuantity(int productId, double newQuantity) {
    if (inventory_.find(productId) != inventory_.end()) {
        inventory_[productId] = newQuantity;
        std::cout << "Product ID " << productId << " quantity updated to " << newQuantity << ".\n";
    }
    else {
        std::cerr << "Product ID " << productId << " not found in inventory.\n";
    }
}

Product Inventory::findProductInFile(int productId, const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return Product(); // Возвращаем пустой продукт
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string productIdStr, name, unit;

        if (std::getline(ss, productIdStr, ';') && std::getline(ss, name, ';') && std::getline(ss, unit, ';')) {
            int currentProductId = std::stoi(productIdStr);
            if (currentProductId == productId) {
                // Нашли продукт с нужным ID
                return Product(currentProductId, name, unit);
            }
        }
    }

    file.close();
    return Product(); // Если не найден, возвращаем пустой продукт
}

// Возвращает карту ID продукта и их имен
std::map<int, std::string> Inventory::getProductNames() const {
    std::map<int, std::string> productNames;
    for (const auto& product : products_) {
        productNames[product.first] = product.second.getName();
    }
    return productNames;
}

// Возвращает карту ID продукта и их единиц измерения
std::map<int, std::string> Inventory::getProductUnits() const {
    std::map<int, std::string> productUnits;
    for (const auto& product : products_) {
        productUnits[product.first] = product.second.getUnit();
    }
    return productUnits;
}

// Проверка наличия продукта в инвентаре
bool Inventory::hasProduct(int productId) const {
    return products_.find(productId) != products_.end();
}

// Уменьшение количества продукта по его ID
bool Inventory::reduceProductById(int productId, double quantity)
{
    if (inventory_[productId] >= quantity) {
        inventory_[productId] -= quantity;
        return true;
    }
    return false; // Недостаточно продукта
}

// Получение текущего количества продукта
double Inventory::getProductQuantity(int productId) const
{
    auto it = inventory_.find(productId);
    if (it != inventory_.end()) {
        return it->second;
    }
    return 0.0; // Продукт не найден
}

// Проверка наличия достаточного количества ингредиентов для рецепта
bool Inventory::canFulfillRecipe(const Recipe& recipe) const
{
    const auto& ingredients = recipe.getIngredients();
    for (const auto& ingredient : ingredients) {
        int productId = ingredient.first;
        double requiredQuantity = ingredient.second;
        if (getProductQuantity(productId) < requiredQuantity) {
            return false; // Недостаточно количества хотя бы одного ингредиента
        }
    }
    return true; // Достаточно всех ингредиентов
}

// Уменьшение количества продуктов по рецепту
bool Inventory::useIngredientsForRecipe(const Recipe& recipe)
{
    if (canFulfillRecipe(recipe)) {
        const auto& ingredients = recipe.getIngredients();
        for (const auto& ingredient : ingredients) {
            int productId = ingredient.first;
            double quantity = ingredient.second;
            reduceProductById(productId, quantity);
        }
        return true;
    }
    return false;
}

// Загрузка данных инвентаря из файла
void Inventory::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    inventory_.clear(); // Очищаем текущий инвентарь

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string productIdStr, quantityStr;

        try {
            if (std::getline(ss, productIdStr, ';') && std::getline(ss, quantityStr, ';')) {
                int productId = std::stoi(productIdStr);
                double quantity = std::stod(quantityStr);

                

                if (products_.find(productId) != products_.end()) {
                    addProduct(productId, quantity); 
                }
                else {
                    std::cerr << "Product ID " << productId << " not found in products list." << std::endl;
                }
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data format in file: " << filename << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Value out of range in file: " << filename << std::endl;
        }
    }

    file.close();
}

// Загрузка продуктов из файла
void Inventory::loadProductsFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    products_.clear(); // Очищаем текущий список продуктов

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string productIdStr, name, unit;

        try {
            if (std::getline(ss, productIdStr, ';') && std::getline(ss, name, ';') && std::getline(ss, unit, ';')) {
                int productId = std::stoi(productIdStr);
                Product product(productId, name, unit);
                products_[productId] = product;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data format in file: " << filename << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Value out of range in file: " << filename << std::endl;
        }
    }

    file.close();
}

// Вывод текущего состояния инвентаря
void Inventory::printInventory(const std::map<int, std::string>& productNames) const
{
    std::cout << "Inventory:\n";
    for (const auto& item : inventory_) {
        int productId = item.first;
        double quantity = item.second;
        // Получаем единицу измерения
        std::string unit = products_.at(productId).getUnit();
        std::cout << " - " << productNames.at(productId) << ": "
            << quantity << " " << unit << std::endl;
    }
}
// Удаление продукта из инвентаря
void Inventory::removeProductFromInventory(int productId) {
    if (inventory_.find(productId) != inventory_.end()) {
        inventory_.erase(productId);
    }
    else {
        std::cerr << "Product with ID " << productId << " not found in inventory.\n";
    }
}

// Сохранение данных инвентаря в файл
void Inventory::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // Проходим по всем продуктам в инвентаре
    for (const auto& item : inventory_) {
        int productId = item.first;
        double quantity = item.second;
        file << productId << ";" << quantity << "\n"; // Сохраняем ID продукта и его количество
    }

    file.close();
}