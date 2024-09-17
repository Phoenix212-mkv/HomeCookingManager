#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include<map>
class Recipe {
private:
    int id_;
    std::string name_;
    std::string instructions_;
    std::map<int, double> ingredients_; // {productId, quantity}
public:
    Recipe(int id, const std::string& name, const std::string& instructions)
        : id_(id), name_(name), instructions_(instructions) {}

    int getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getInstructions() const { return instructions_; }

    void addIngredient(int productId, double quantity) {
        ingredients_[productId] = quantity;
    }

    const std::map<int, double>& getIngredients() const {
        return ingredients_;
    }


};

#endif // RECIPE_H