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
    std::vector<Recipe> recipes_; // ������ ��������

public:
    // ���������� � �������� ��������
    void addRecipe(const Recipe& recipe);
    bool removeRecipe(int recipeId);
    bool removeRecipeByName(const std::string& name); // �������� �� �����

    int getNextRecipeId() const;
    // ��������� �������
    bool modifyRecipeByName(const std::string& name, ProductDatabase& productDatabase);

    const Recipe* findRecipeByName(const std::string& name) const;

    bool RecipeBook::hasRecipe(const std::string& name) const;

    // ����� ��� ��������� ������ �� �������
    std::vector<Recipe>& getRecipes();

    // ����� ��������
    std::vector<Recipe> findRecipesByName(const std::string& name) const;
    std::vector<Recipe> findRecipesByIngredient(int productId) const;

    // �������� � ���������� ��������
    void loadFromFile(const std::string& filename, const std::map<int, Product>& products);
    void saveToFile(const std::string& filename) const;

    // ������ ���� ��������
    void printAllRecipes(const std::map<int, std::string>& productNames,
        const std::map<int, std::string>& productUnits) const;
};

#endif // RECIPEBOOK_H