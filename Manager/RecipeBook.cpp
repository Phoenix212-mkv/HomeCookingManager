#include "RecipeBook.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <algorithm>


// ���������� ������� � �����
void RecipeBook::addRecipe(const Recipe& recipe) {
    if (!hasRecipe(recipe.getName())) {
        recipes_.push_back(recipe);
    }
    else {
        std::cerr << "Recipe with name \"" << recipe.getName() << "\" already exists in recipe book.\n";
    }
}

std::vector<Recipe>& RecipeBook::getRecipes() {
    return recipes_;
}

bool RecipeBook::removeRecipeByName(const std::string& name) {
    auto it = std::find_if(recipes_.begin(), recipes_.end(), [&](const Recipe& recipe) {
        return recipe.getName() == name;
        });

    if (it != recipes_.end()) {
        recipes_.erase(it);
        return true;
    }
    return false;
}
const Recipe* RecipeBook::findRecipeByName(const std::string& name) const {
    for (const auto& recipe : recipes_) {
        if (recipe.getName() == name) {
            return &recipe;
        }
    }
    return nullptr;
}
int RecipeBook::getNextRecipeId() const {
    int maxId = 0;
    for (const auto& recipe : recipes_) {
        if (recipe.getId() > maxId) {
            maxId = recipe.getId();
        }
    }
    return maxId + 1;
}

// ��������� ������� �� �����
bool RecipeBook::modifyRecipeByName(const std::string& name, ProductDatabase& productDatabase) {
    for (auto& recipe : recipes_) {
        if (recipe.getName() == name) {
            std::cout << "Enter new instructions: ";
            std::string newInstructions;
            std::getline(std::cin, newInstructions);
            recipe.setInstructions(newInstructions);

            // �������� ������� �����������
            std::map<int, double> newIngredients;
            // �������� ������� �����������
            recipe.clearIngredients();

            while (true) {
                std::cout << "Enter product name (or 'done' to finish): ";
                std::string productName;
                std::getline(std::cin, productName);
                if (productName == "done") break;

                const Product* product = nullptr;
                for (const auto& [id, prod] : productDatabase.getAllProducts()) {
                    if (prod.getName() == productName) {
                        product = &productDatabase.getAllProducts().at(id);
                        break;
                    }
                }

                if (product) {
                    std::cout << "Enter quantity (" << product->getUnit() << "): ";
                    double quantity;
                    std::cin >> quantity;
                    std::cin.ignore();

                    // ���������� ����� addIngredient ��� ���������� ������� �����������
                    recipe.addIngredient(product->getId(), quantity);
                }
                else {
                    std::cout << "[Error] Product not found in the database.\n";
                }
            }
            return true;
        }
    }
    return false;
}

// �������� ������� ������� �� �����
bool RecipeBook::hasRecipe(const std::string& name) const {
    return std::any_of(recipes_.begin(), recipes_.end(), [&](const Recipe& recipe) {
        return recipe.getName() == name;
        });
}

// �������� ������� �� ID
bool RecipeBook::removeRecipe(int recipeId) {
    auto it = std::find_if(recipes_.begin(), recipes_.end(), [recipeId](const Recipe& recipe) {
        return recipe.getId() == recipeId;
        });

    if (it != recipes_.end()) {
        recipes_.erase(it);
        return true; // ������� ������
    }
    return false; // �� ������
}

// ����� �������� �� ��������
std::vector<Recipe> RecipeBook::findRecipesByName(const std::string& name) const {
    std::vector<Recipe> foundRecipes;
    for (const auto& recipe : recipes_) {
        if (recipe.getName().find(name) != std::string::npos) {
            foundRecipes.push_back(recipe);
        }
    }
    return foundRecipes;
}

// ����� �������� �� �����������
std::vector<Recipe> RecipeBook::findRecipesByIngredient(int productId) const {
    std::vector<Recipe> foundRecipes;
    for (const auto& recipe : recipes_) {
        if (recipe.getIngredients().find(productId) != recipe.getIngredients().end()) {
            foundRecipes.push_back(recipe);
        }
    }
    return foundRecipes;
}

// �������� �������� �� �����
void RecipeBook::loadFromFile(const std::string& filename, const std::map<int, Product>& products) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    recipes_.clear(); // ������� ������� ����� ��������

    // ��������� ������ "C" ��� ����������� ������ ����� � ���������� ������
    std::locale originalLocale = std::locale::global(std::locale("C"));

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string recipeIdStr, name, instructions, ingredientsStr;

        if (std::getline(ss, recipeIdStr, ';') && std::getline(ss, name, ';') && std::getline(ss, instructions, ';') && std::getline(ss, ingredientsStr, ';')) {
            try {
                int recipeId = std::stoi(recipeIdStr);
                std::map<int, double> ingredients;

                std::istringstream ingredientsSS(ingredientsStr);
                std::string ingredientStr;
                while (std::getline(ingredientsSS, ingredientStr, ',')) {
                    std::istringstream ingredientSS(ingredientStr);
                    std::string productIdStr, quantityStr;

                    if (std::getline(ingredientSS, productIdStr, ':') && std::getline(ingredientSS, quantityStr, ':')) {
                        int productId = std::stoi(productIdStr);

                        // �������� �������� � �������� ����� ������
                        quantityStr.erase(quantityStr.find_last_not_of(" \n\r\t") + 1);

                        double quantity = std::stod(quantityStr);
                        // �������� �� ������� �������� � ����� ���������
                        if (products.find(productId) != products.end()) {
                            ingredients[productId] = quantity;
                        }
                    }
                }

                Recipe recipe(recipeId, name, instructions, ingredients);
                addRecipe(recipe);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid data format in file: " << filename << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Value out of range in file: " << filename << std::endl;
            }
        }
    }

    // �������������� ������������ ������
    std::locale::global(originalLocale);

    file.close();
}

// ���������� �������� � ����
void RecipeBook::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& recipe : recipes_) {
        file << recipe.getId() << ";" << recipe.getName() << ";" << recipe.getInstructions() << ";";

        const auto& ingredients = recipe.getIngredients();
        bool first = true;
        for (const auto& ingredient : ingredients) {
            if (!first) {
                file << ", ";
            }
            file << ingredient.first << ":" << ingredient.second;
            first = false;
        }
        file << "\n";
    }

    file.close();
}

// ������ ���� ��������
void RecipeBook::printAllRecipes(const std::map<int, std::string>& productNames,
    const std::map<int, std::string>& productUnits) const {
    for (const auto& recipe : recipes_) {
        recipe.printRecipe(productNames, productUnits);
        std::cout << "----------------------\n";
    }
}