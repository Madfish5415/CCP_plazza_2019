/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** RecipesTests.cpp
*/

#include <criterion/criterion.h>
#include <fstream>
#include <iostream>
#include <cstdio>

#include "../src/pizza/Recipes.hpp"

Test(Recipes, Load_01)
{
    std::string fileName = "./tests/data/testRecipes1.txt";
    std::ofstream outfile (fileName);

    outfile << "type=\"regina\";ingredients=\"doe\":1;cookTime=1;" << std::endl
            << "type=\"regina\";ingredients=\"item1\":1;cookTime=1;" << std::endl
            << "type=\"regina\";ingredients=\"item2\":1;cookTime=1;" << std::endl;

    outfile.close();

    pizza::Recipes::load(fileName);

    remove(fileName.c_str());

    auto recipes = pizza::Recipes::get();

    if (recipes.size() == 1 && recipes.count("regina") == 1 && recipes.at("regina").pack() == "type=\"regina\";ingredients=\"doe\":1;cookTime=1;")
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipes, Load_02)
{
    std::string fileName = "./tests/data/testRecipes2.txt";
    std::ofstream outfile (fileName);

    outfile << "type=\"regina\";ingredients=\"doe\":1;cookTime=1;" << std::endl
            << "type=\"margarita\";ingredients=\"item1\":1;cookTime=1;" << std::endl
            << "type=\"fantasia\";ingredients=\"item2\":1;cookTime=1;" << std::endl;

    outfile.close();

    pizza::Recipes::load(fileName);

    remove(fileName.c_str());

    auto recipes = pizza::Recipes::get();

    if (recipes.size() == 3 && recipes.count("regina") == 1 &&
        recipes.at("regina").pack() == "type=\"regina\";ingredients=\"doe\":1;cookTime=1;" &&
        recipes.count("margarita") == 1 && recipes.at("margarita").pack() == "type=\"margarita\";ingredients=\"item1\":1;cookTime=1;" &&
        recipes.count("fantasia") == 1 && recipes.at("fantasia").pack() == "type=\"fantasia\";ingredients=\"item2\":1;cookTime=1;")
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}