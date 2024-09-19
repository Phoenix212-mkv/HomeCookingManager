#include "ProductDatabase.h"
#include <fstream>
#include <sstream>
#include <iostream>

// �����������
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

// �������� ��������� �� �����
void ProductDatabase::loadFromFile() {
    std::ifstream file(filename_);
    if (!file.is_open()) {
        std::cerr << "������ ��� �������� ����� ��� ������: " << filename_ << std::endl;
        return;
    }

    products_.clear(); // ������� ������� ������ ���������

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

// ���������� ��������� � ����
void ProductDatabase::saveToFile() const {
    std::ofstream file(filename_);
    if (!file.is_open()) {
        std::cerr << "������ ��� �������� ����� ��� ������: " << filename_ << std::endl;
        return;
    }

    for (const auto& [id, product] : products_) {
        file << id << ";" << product.getName() << ";" << product.getUnit() << "\n";
    }

    file.close();
}

// ���������� ��������
bool ProductDatabase::addProduct(const Product& product) {
    if (products_.find(product.getId()) != products_.end()) {
        std::cerr << "������� � ID " << product.getId() << " ��� ����������.\n";
        return false;
    }
    products_[product.getId()] = product;
    return true;
}

// �������� ��������
bool ProductDatabase::removeProduct(int productId) {
    if (products_.erase(productId) == 0) {
        std::cerr << "������� � ID " << productId << " �� ������.\n";
        return false;
    }
    return true;
}

// �������������� ��������
bool ProductDatabase::editProduct(int productId, const std::string& newName, const std::string& newUnit) {
    auto it = products_.find(productId);
    if (it == products_.end()) {
        std::cerr << "������� � ID " << productId << " �� ������.\n";
        return false;
    }
    it->second.setName(newName);
    it->second.setUnit(newUnit);
    return true;
}

// ����� �������� �� ID
Product* ProductDatabase::findProduct(int productId) {
    auto it = products_.find(productId);
    if (it != products_.end()) {
        return &it->second;
    }
    return nullptr;
}

// ��������� ���� ���������
const std::map<int, Product>& ProductDatabase::getAllProducts() const {
    return products_;
}