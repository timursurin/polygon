cmake_minimum_required(VERSION 3.10)

# Название проекта
project(SortingTests)

# Добавляем подкаталог с исходниками Google Test
add_subdirectory(/Users/timursurin/CLionProjects/polygon/googletest)

# Основная программа
add_executable(SortingMain main.cpp sort_algorithms.cpp)

# Тесты
add_executable(SortingTests test_example.cpp sort_algorithms.cpp)

# Линковка с библиотеками Google Test
target_link_libraries(SortingTests gtest gtest_main)