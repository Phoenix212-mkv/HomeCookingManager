#include "Recipe.h"
#include <iostream>
#include <iomanip> // ��� std::setprecision

// �����������
Recipe::Recipe(int id, const std::string& name, const std::string& instructions, const std::map<int, double>& ingredients)
    : id_(id), name_(name), instructions_(instructions), ingredients_(ingredients) {}

// �������
int Recipe::getId() const {
    return id_;
}

std::string Recipe::getName() const {
    return name_;
}

std::string Recipe::getInstructions() const {
    return instructions_;
}

const std::map<int, double>& Recipe::getIngredients() const {
    return ingredients_;
}

// �������������� �������
void Recipe::addIngredient(int productId, double quantity) {
    ingredients_[productId] = quantity;
}

void Recipe::removeIngredient(int productId) {
    ingredients_.erase(productId);
}

void Recipe::setName(const std::string& name) {
    name_ = name;
}

void Recipe::setInstructions(const std::string& instructions) {
    instructions_ = instructions;
}

// ��������� ������������ ��� ������������� ���������� ������
std::map<int, double> Recipe::getIngredientsForPortions(int portions) const {
    std::map<int, double> scaledIngredients;
    for (const auto& ingredient : ingredients_) {
        int productId = ingredient.first;
        double quantity = ingredient.second * portions; // ������������ ����������
        scaledIngredients[productId] = quantity;
    }
    return scaledIngredients;
}

// ������ ���������� � �������
void Recipe::printRecipe(const std::map<int, std::string>& productNames,
    const std::map<int, std::string>& productUnits) const {
    std::cout << name_ << ":\n";
    std::cout << instructions_ << "\n";
    std::cout << "Ingredients:\n";
    for (const auto& ingredient : ingredients_) {
        int productId = ingredient.first;
        double quantity = ingredient.second;

        // �������� ������� �������� � �����
        if (productNames.find(productId) != productNames.end() &&
            productUnits.find(productId) != productUnits.end()) {
            std::cout << " - " << productNames.at(productId) << ": "
                << std::fixed << std::setprecision(2) << quantity << " "
                << productUnits.at(productId) << "\n";
        }
        else {
            std::cerr << "Product ID " << productId << " not found in product maps.\n";
        }
    }
}