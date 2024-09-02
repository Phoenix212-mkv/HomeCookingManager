set(projectName "Product")

project(${projectName})

set (source_files Product.cpp Product.h "Inventory.h" "Invetory.cpp" "Recipe.h" "Recipe.cpp")

add_library (${projectName} ${source_files})