#include "Manager/Manager.h"
#include <iostream>

void manageProductDatabase(ProductDatabase& database) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Product Database Management ===\n";
        std::cout << "1. View all products\n";
        std::cout << "2. Add a new product\n";
        std::cout << "3. Edit an existing product\n";
        std::cout << "4. Remove a product\n";
        std::cout << "5. Save changes to file\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cout << "----------------------\n";
        switch (choice) {
        case 1: {
            std::cout << "\n=== All Products ===\n";
            for (const auto& [id, product] : database.getAllProducts()) {
                std::cout << "ID: " << id << ", Name: " << product.getName()
                    << ", Unit: " << product.getUnit() << "\n";
            }
            std::cout << "----------------------\n";
            break;
        }
        case 2: {
            std::cout << "\n=== Add New Product ===\n";
            int id;
            std::string name, unit;
            std::cout << "Enter product ID: ";
            std::cin >> id;
            std::cout << "Enter product name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter product unit: ";
            std::getline(std::cin, unit);
            if (database.addProduct(Product(id, name, unit))) {
                std::cout << "Product '" << name << "' added successfully.\n";
            }
            std::cout << "----------------------\n";
            break;
        }
        case 3: {
            std::cout << "\n=== Edit Product ===\n";
            int id;
            std::string newName, newUnit;
            std::cout << "Enter product ID to edit: ";
            std::cin >> id;
            std::cout << "Enter new product name: ";
            std::cin.ignore();
            std::getline(std::cin, newName);
            std::cout << "Enter new product unit: ";
            std::getline(std::cin, newUnit);
            if (database.editProduct(id, newName, newUnit)) {
                std::cout << "Product '" << newName << "' edited successfully.\n";
            }
            std::cout << "----------------------\n";
            break;
        }
        case 4: {
            std::cout << "\n=== Remove Product ===\n";
            int id;
            std::cout << "Enter product ID to remove: ";
            std::cin >> id;
            if (database.removeProduct(id)) {
                std::cout << "Product removed successfully.\n";
            }
            std::cout << "----------------------\n";
            break;
        }
        case 5: {
            std::cout << "\n=== Save Changes ===\n";
            database.saveToFile();
            std::cout << "Changes saved to 'products.txt'.\n";
            std::cout << "----------------------\n";
            break;
        }
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::cout << "----------------------\n";
            break;
        }
    }
}

// Функция для управления инвентарем
void manageInventory(Inventory& inventory, const ProductDatabase& productDatabase) {
    while (true) {
        std::cout << "\n===== Inventory Management =====\n";
        std::cout << "1. View Inventory\n";
        std::cout << "2. Add Product to Inventory\n";
        std::cout << "3. Modify Product Quantity in Inventory\n";
        std::cout << "4. Remove Product from Inventory\n";
        std::cout << "5. Save Inventory to File\n";
        std::cout << "6. Exit\n";
        std::cout << "==============================\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 6) break;

        switch (choice) {
        case 1: {
            // Отображение инвентаря
            std::cout << "\n----- Current Inventory -----\n";
            inventory.printInventory(inventory.getProductNames());
            std::cout << "-----------------------------\n";
            break;
        }
        case 2: {
            // Добавление продукта в инвентарь
            std::cout << "\nEnter product name to add: ";
            std::string productName;
            std::cin.ignore(); // Очищаем буфер
            std::getline(std::cin, productName);

            // Находим продукт по имени
            const Product* product = nullptr;
            for (const auto& [id, prod] : productDatabase.getAllProducts()) {
                if (prod.getName() == productName) {
                    product = &productDatabase.getAllProducts().at(id);
                    break;
                }
            }

            if (product) {
                // Отображаем единицу измерения перед вводом количества
                std::cout << "Enter quantity (" << product->getUnit() << "): ";
                double quantity;
                std::cin >> quantity;

                inventory.addProduct(product->getId(), quantity);
                std::cout << "\n[Success] Product '" << product->getName() << "' added to inventory.\n";
            }
            else {
                std::cout << "\n[Error] Product name not found in the database.\n";
            }
            break;
        }
        case 3: {
            // Модификация количества продукта в инвентаре
            std::cout << "\nEnter product name to modify: ";
            std::string productName;
            std::cin.ignore(); // Очищаем буфер
            std::getline(std::cin, productName);

            const Product* product = nullptr;
            for (const auto& [id, prod] : productDatabase.getAllProducts()) {
                if (prod.getName() == productName) {
                    product = &productDatabase.getAllProducts().at(id);
                    break;
                }
            }

            if (product) {
                // Отображаем единицу измерения перед вводом количества
                std::cout << "Enter new quantity (" << product->getUnit() << "): ";
                double quantity;
                std::cin >> quantity;

                // Используем метод изменения продукта
                inventory.modifyProductQuantity(product->getId(), quantity);
             
            }
            else {
                std::cout << "\n[Error] Product not found in the database.\n";
            }
            break;
        }
        case 4: {
            // Удаление продукта из инвентаря
            std::cout << "\nEnter product name to remove: ";
            std::string productName;
            std::cin.ignore(); // Очищаем буфер
            std::getline(std::cin, productName);

            int productId = -1;
            for (const auto& [id, product] : productDatabase.getAllProducts()) {
                if (product.getName() == productName) {
                    productId = id;
                    break;
                }
            }

            if (productId != -1) {
                inventory.removeProductFromInventory(productId);
                std::cout << "\n[Success] Product '" << productName << "' removed from inventory.\n";
            }
            else {
                std::cout << "\n[Error] Product not found in the inventory.\n";
            }
            break;
        }
        case 5: {
            // Сохранение инвентаря в файл
            inventory.saveToFile("inventory.txt");
            std::cout << "\n[Success] Inventory saved to 'inventory.txt'.\n";
            break;
        }
        default:
            std::cout << "\n[Error] Invalid choice. Please try again.\n";
        }
    }
}

void manageRecipes(RecipeBook& recipeBook, ProductDatabase& productDatabase, Inventory& inventory) {
    while (true) {
        std::cout << "\n===== Recipe Management =====\n";
        std::cout << "1. View All Recipes\n";
        std::cout << "2. Add New Recipe\n";
        std::cout << "3. Delete Recipe\n";
        std::cout << "4. Modify Recipe\n";
        std::cout << "5. Check Recipe Availability\n";
        std::cout << "6. Save to file\n";
        std::cout << "7. Back to Main Menu\n";
        std::cout << "=============================\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // Просмотр всех рецептов
            const auto& productNames = productDatabase.getAllProducts();
            std::map<int, std::string> productNamesMap;
            std::map<int, std::string> productUnitsMap;
            for (const auto& [id, product] : productNames) {
                productNamesMap[id] = product.getName();
                productUnitsMap[id] = product.getUnit();
            }
            recipeBook.printAllRecipes(productNamesMap, productUnitsMap);
            break;
        }
        case 2: {
            // Добавление нового рецепта
            std::cin.ignore();
            std::cout << "\nEnter recipe name: ";
            std::string recipeName;
            std::getline(std::cin, recipeName);

            std::cout << "Enter instructions: ";
            std::string instructions;
            std::getline(std::cin, instructions);

            std::map<int, double> ingredients;
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

                    ingredients[product->getId()] = quantity;
                }
                else {
                    std::cout << "[Error] Product not found in the database.\n";
                }
            }

            Recipe newRecipe(recipeBook.getNextRecipeId(), recipeName, instructions, ingredients);
            recipeBook.addRecipe(newRecipe);
            std::cout << "\n[Success] Recipe '" << recipeName << "' added to the recipe book.\n";
            break;
        }
        case 3: {
            // Удаление рецепта
            std::cin.ignore();
            std::cout << "\nEnter recipe name to delete: ";
            std::string recipeName;
            std::getline(std::cin, recipeName);

            if (recipeBook.removeRecipeByName(recipeName)) {
                std::cout << "\n[Success] Recipe '" << recipeName << "' removed from the recipe book.\n";
            }
            else {
                std::cout << "\n[Error] Recipe not found.\n";
            }
            break;
        }
        case 4: {
            // Изменение рецепта
            std::cin.ignore();
            std::cout << "\nEnter recipe name to modify: ";
            std::string recipeName;
            std::getline(std::cin, recipeName);

            if (!recipeBook.modifyRecipeByName(recipeName, productDatabase)) {
                std::cout << "\n[Error] Recipe not found.\n";
            }
            break;
        }
        case 5: {
            // Проверка возможности приготовления рецепта
            std::cin.ignore();
            std::cout << "\nEnter recipe name to check: ";
            std::string recipeName;
            std::getline(std::cin, recipeName);

            const Recipe* recipe = recipeBook.findRecipeByName(recipeName);
            if (recipe) {
                if (inventory.canFulfillRecipe(*recipe)) {
                    std::cout << "\n[Success] You have enough ingredients to make '" << recipeName << "'.\n";
                }
                else {
                    std::cout << "\n[Error] Not enough ingredients to make '" << recipeName << "'.\n";
                }
            }
            else {
                std::cout << "\n[Error] Recipe not found.\n";
            }
            break;
        }
        case 6: {
            // Сохранение книги рецептов и выход в главное меню
            recipeBook.saveToFile("recipes.txt");
            std::cout << "\n[Success] Recipe book saved to file.\n";
            break;
        case 7:
            return;
        }
        default:
            std::cout << "\n[Error] Invalid choice. Please try again.\n";
            break;
        }
    }
}

    int main() {
        
        int choice;
        while (true) {
            // Создаем экземпляры базы данных продуктов и инвентаря
            ProductDatabase productDatabase("products.txt");
            Inventory inventory;
            RecipeBook recipebook;
            // Загружаем продукты в инвентарь
            inventory.loadProductsFromFile("products.txt");
            inventory.loadFromFile("inventory.txt");
            RecipeBook recipeBook;
            recipeBook.loadFromFile("recipes.txt", productDatabase.getAllProducts());
            std::cout << "Main Menu:\n";
            std::cout << "1. Manage Product Database\n";
            std::cout << "2. Manage Inventory\n";
            std::cout << "3. Manage Recipe Book\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            if (choice == 0) break;

            switch (choice) {
            case 1:
                manageProductDatabase(productDatabase);
                break;
            case 2:
                manageInventory(inventory, productDatabase);
                break;
            case 3:
                manageRecipes(recipeBook, productDatabase, inventory);
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }

        return 0;
    }