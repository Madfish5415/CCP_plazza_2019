/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** RecipeTests.cpp
*/

#include <criterion/criterion.h>
#include <cstdio>
#include <iostream>

#include "../src/pizza/Recipe.hpp"

Test(Recipe, Constructor_01)
{
    auto recipe = new pizza::Recipe();

    (void) recipe;

    cr_assert_eq(1, 1);
}

Test(Recipe, Constructor_02)
{
    auto recipe = new pizza::Recipe("test", {{"Bla", 1}, {"Blou", 2}}, 2);

    (void) recipe;

    cr_assert_eq(1, 1);
}

Test(Recipe, getType_01)
{
    auto recipe = new pizza::Recipe();

    if (recipe->getType().empty())
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipe, getType_02)
{
    auto recipe = new pizza::Recipe("test", {{"Bla", 1}, {"Blou", 2}}, 2);

    if (recipe->getType() == "test")
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipe, getIngredients_01)
{
    auto recipe = new pizza::Recipe();

    if (recipe->getIngredients().empty())
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipe, getIngredients_02)
{
    auto recipe = new pizza::Recipe("test", {{"Bla", 1}, {"Blou", 2}}, 2);

    std::map<std::string, unsigned int> compare = {{"Bla", 1}, {"Blou", 2}};

    if (recipe->getIngredients() == compare)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipe, getCookTime_01)
{
    auto recipe = new pizza::Recipe();

    if (recipe->getCookTime() == 0)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipe, getCookTime_02)
{
    auto recipe = new pizza::Recipe("test", {{"Bla", 1}, {"Blou", 2}}, 2);

    if (recipe->getCookTime() == 2)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipe, pack_01)
{
    auto recipe = new pizza::Recipe();

    if (recipe->pack() == "type=\"\";ingredients=;cookTime=0;")
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipe, pack_02)
{
    auto recipe = new pizza::Recipe("test", {{"Bla", 1}, {"Blou", 2}}, 2);


    if (recipe->pack() == "type=\"test\";ingredients=\"Bla\":1,\"Blou\":2;cookTime=2;")
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Recipe, unpack_01)
{
    auto recipe = new pizza::Recipe();

    recipe->unpack("type=\"test\";ingredients=\"Bla\":1,\"Blou\":2;cookTime=2;");

    if (recipe->pack() == "type=\"test\";ingredients=\"Bla\":1,\"Blou\":2;cookTime=2;")
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}