#include "Inventory.h"
#include "Recipe.h"
#include <iostream>
#include <fstream>
#include <sstream>



// ���������� �������� � ���������
void Inventory::addProduct(int productId, double quantity) {
    // ��������� ����� ������� � products.txt
    Product product = findProductInFile(productId, "products.txt");

    if (product.getId() != 0) { // ���� ������� ������ (��������� �� ID)
        if (inventory_.find(productId) == inventory_.end()) {
            // ��������� ����� ������� � ���������
            inventory_[productId] = quantity;
            products_[productId] = product;
        }
        else {
            // ��������� ���������� ������������� ��������
            inventory_[productId] += quantity;
        }
    }
    else {
        std::cerr << "Product with ID " << productId << " does not exist in the possible products list.\n";
    }
}

void Inventory::addProductByName(const std::string& productName, double quantity) {
    // ����� �������� �� �����
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
    // ����� �������� �� �����
    auto it = std::find_if(products_.begin(), products_.end(),
        [&productName](const auto& pair) { return pair.second.getName() == productName; });

    if (it != products_.end()) {
        int productId = it->first;
        // ���������, ���� �� ������� � ���������
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
        return Product(); // ���������� ������ �������
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string productIdStr, name, unit;

        if (std::getline(ss, productIdStr, ';') && std::getline(ss, name, ';') && std::getline(ss, unit, ';')) {
            int currentProductId = std::stoi(productIdStr);
            if (currentProductId == productId) {
                // ����� ������� � ������ ID
                return Product(currentProductId, name, unit);
            }
        }
    }

    file.close();
    return Product(); // ���� �� ������, ���������� ������ �������
}

// ���������� ����� ID �������� � �� ����
std::map<int, std::string> Inventory::getProductNames() const {
    std::map<int, std::string> productNames;
    for (const auto& product : products_) {
        productNames[product.first] = product.second.getName();
    }
    return productNames;
}

// ���������� ����� ID �������� � �� ������ ���������
std::map<int, std::string> Inventory::getProductUnits() const {
    std::map<int, std::string> productUnits;
    for (const auto& product : products_) {
        productUnits[product.first] = product.second.getUnit();
    }
    return productUnits;
}

// �������� ������� �������� � ���������
bool Inventory::hasProduct(int productId) const {
    return products_.find(productId) != products_.end();
}

// ���������� ���������� �������� �� ��� ID
bool Inventory::reduceProductById(int productId, double quantity)
{
    if (inventory_[productId] >= quantity) {
        inventory_[productId] -= quantity;
        return true;
    }
    return false; // ������������ ��������
}

// ��������� �������� ���������� ��������
double Inventory::getProductQuantity(int productId) const
{
    auto it = inventory_.find(productId);
    if (it != inventory_.end()) {
        return it->second;
    }
    return 0.0; // ������� �� ������
}

// �������� ������� ������������ ���������� ������������ ��� �������
bool Inventory::canFulfillRecipe(const Recipe& recipe) const
{
    const auto& ingredients = recipe.getIngredients();
    for (const auto& ingredient : ingredients) {
        int productId = ingredient.first;
        double requiredQuantity = ingredient.second;
        if (getProductQuantity(productId) < requiredQuantity) {
            return false; // ������������ ���������� ���� �� ������ �����������
        }
    }
    return true; // ���������� ���� ������������
}

// ���������� ���������� ��������� �� �������
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

// �������� ������ ��������� �� �����
void Inventory::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    inventory_.clear(); // ������� ������� ���������

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

// �������� ��������� �� �����
void Inventory::loadProductsFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    products_.clear(); // ������� ������� ������ ���������

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

// ����� �������� ��������� ���������
void Inventory::printInventory(const std::map<int, std::string>& productNames) const
{
    std::cout << "Inventory:\n";
    for (const auto& item : inventory_) {
        int productId = item.first;
        double quantity = item.second;
        // �������� ������� ���������
        std::string unit = products_.at(productId).getUnit();
        std::cout << " - " << productNames.at(productId) << ": "
            << quantity << " " << unit << std::endl;
    }
}
// �������� �������� �� ���������
void Inventory::removeProductFromInventory(int productId) {
    if (inventory_.find(productId) != inventory_.end()) {
        inventory_.erase(productId);
    }
    else {
        std::cerr << "Product with ID " << productId << " not found in inventory.\n";
    }
}

// ���������� ������ ��������� � ����
void Inventory::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // �������� �� ���� ��������� � ���������
    for (const auto& item : inventory_) {
        int productId = item.first;
        double quantity = item.second;
        file << productId << ";" << quantity << "\n"; // ��������� ID �������� � ��� ����������
    }

    file.close();
}