set(projectName "Product")

project(${projectName})

set (source_files Product.cpp Product.h)

add_library (${projectName} ${source_files})