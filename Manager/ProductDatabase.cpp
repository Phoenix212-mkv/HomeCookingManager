#include "ProductDatabase.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Конструктор
ProductDatabase::ProductDatabase(const std::string& filename) : filename_(filename) {
    loadFromFile();
}

Product* ProductDatabase::findProductByName(const std::string& productName) {
    for (auto& [id, product] : products_) {
        if (product.getName() == productName) {
            return &product;
        }
    }
    return nullptr;
}

// Загрузка продуктов из файла
void ProductDatabase::loadFromFile() {
    std::ifstream file(filename_);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла для чтения: " << filename_ << std::endl;
        return;
    }

    products_.clear(); // Очищаем текущий список продуктов

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string productIdStr, name, unit;

        if (std::getline(ss, productIdStr, ';') && std::getline(ss, name, ';') && std::getline(ss, unit, ';')) {
            int productId = std::stoi(productIdStr);
            Product product(productId, name, unit);
            products_[productId] = product;
        }
    }

    file.close();
}

// Сохранение продуктов в файл
void ProductDatabase::saveToFile() const {
    std::ofstream file(filename_);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла для записи: " << filename_ << std::endl;
        return;
    }

    for (const auto& [id, product] : products_) {
        file << id << ";" << product.getName() << ";" << product.getUnit() << "\n";
    }

    file.close();
}

// Добавление продукта
bool ProductDatabase::addProduct(const Product& product) {
    if (products_.find(product.getId()) != products_.end()) {
        std::cerr << "Продукт с ID " << product.getId() << " уже существует.\n";
        return false;
    }
    products_[product.getId()] = product;
    return true;
}

// Удаление продукта
bool ProductDatabase::removeProduct(int productId) {
    if (products_.erase(productId) == 0) {
        std::cerr << "Продукт с ID " << productId << " не найден.\n";
        return false;
    }
    return true;
}

// Редактирование продукта
bool ProductDatabase::editProduct(int productId, const std::string& newName, const std::string& newUnit) {
    auto it = products_.find(productId);
    if (it == products_.end()) {
        std::cerr << "Продукт с ID " << productId << " не найден.\n";
        return false;
    }
    it->second.setName(newName);
    it->second.setUnit(newUnit);
    return true;
}

// Поиск продукта по ID
Product* ProductDatabase::findProduct(int productId) {
    auto it = products_.find(productId);
    if (it != products_.end()) {
        return &it->second;
    }
    return nullptr;
}

// Получение всех продуктов
const std::map<int, Product>& ProductDatabase::getAllProducts() const {
    return products_;
}