#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <vector>
#include <string>
#include "Recipe.h"
#include "Product.h"
#include "ProductDatabase.h"
class RecipeBook
{
private:
    std::vector<Recipe> recipes_; // Список рецептов

public:
    // Добавление и удаление рецептов
    void addRecipe(const Recipe& recipe);
    bool removeRecipe(int recipeId);
    bool removeRecipeByName(const std::string& name); // Удаление по имени

    int getNextRecipeId() const;
    // Изменение рецепта
    bool modifyRecipeByName(const std::string& name, ProductDatabase& productDatabase);

    const Recipe* findRecipeByName(const std::string& name) const;

    bool RecipeBook::hasRecipe(const std::string& name) const;

    // Метод для получения ссылки на рецепты
    std::vector<Recipe>& getRecipes();

    // Поиск рецептов
    std::vector<Recipe> findRecipesByName(const std::string& name) const;
    std::vector<Recipe> findRecipesByIngredient(int productId) const;

    // Загрузка и сохранение рецептов
    void loadFromFile(const std::string& filename, const std::map<int, Product>& products);
    void saveToFile(const std::string& filename) const;

    // Печать всех рецептов
    void printAllRecipes(const std::map<int, std::string>& productNames,
        const std::map<int, std::string>& productUnits) const;
};

#endif // RECIPEBOOK_H