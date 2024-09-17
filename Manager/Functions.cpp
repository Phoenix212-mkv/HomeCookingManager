#include "Functions.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Функция для чтения рецептов из файла
std::vector<Recipe> loadRecipes(const std::string& filename) {
    std::vector<Recipe> recipes;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, name, instructions;
            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, instructions);

            int id = std::stoi(idStr);
            recipes.push_back(Recipe(id, name, instructions));
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return recipes;
}

// Функция для чтения ингредиентов из файла и добавления их в рецепты
void loadRecipeIngredients(const std::string& filename, std::vector<Recipe>& recipes) {
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string recipeIdStr, productIdStr, quantityStr;
            std::getline(ss, recipeIdStr, ',');
            std::getline(ss, productIdStr, ',');
            std::getline(ss, quantityStr);

            int recipeId = std::stoi(recipeIdStr);
            int productId = std::stoi(productIdStr);
            double quantity = std::stod(quantityStr);

            // Найти рецепт по ID и добавить ингредиент
            for (auto& recipe : recipes) {
                if (recipe.getId() == recipeId) {
                    recipe.addIngredient(productId, quantity);
                    break;
                }
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}