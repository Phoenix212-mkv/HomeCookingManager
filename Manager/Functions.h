#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <vector>
#include "Recipe.h"

// ������ �������� �� �����
std::vector<Recipe> loadRecipes(const std::string& filename);

// ������ ������������ ��� �������� �� �����
void loadRecipeIngredients(const std::string& filename, std::vector<Recipe>& recipes);

#endif // FILE_OPERATIONS_H