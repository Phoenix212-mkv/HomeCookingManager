#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <map>

class Recipe
{
private:
    int id_;
    std::string name_;
    std::string instructions_;
    std::map<int, double> ingredients_; // {productId, quantity}

public:
    Recipe(int id, const std::string& name, const std::string& instructions, const std::map<int, double>& ingredients = {});

    // Геттеры
    int getId() const;
    std::string getName() const;
    std::string getInstructions() const;
    const std::map<int, double>& getIngredients() const;

    void clearIngredients() {
        ingredients_.clear();
    }

    // Редактирование рецепта
    void addIngredient(int productId, double quantity);
    void removeIngredient(int productId);
    void setName(const std::string& name);
    void setInstructions(const std::string& instructions);

    // Получение ингредиентов для определенного количества порций
    std::map<int, double> getIngredientsForPortions(int portions) const;

    // Печать информации о рецепте
    void printRecipe(const std::map<int, std::string>& productNames,
        const std::map<int, std::string>& productUnits) const;
};

#endif // RECIPE_H