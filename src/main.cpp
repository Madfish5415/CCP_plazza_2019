/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include <iostream>
#include <unistd.h>

#include "Parser.hpp"
#include "Ingredients.hpp"
#include "Sizes.hpp"
#include "Recipes.hpp"

int main() {
    std::string command;

    while (true) {
        usleep(2000000);
        Sizes::load("./data/sizes.data");
        Recipes::load("./data/recipes.data");

        auto recipes = Recipes::get();

        std::cout << "Recipes :" << std::endl;
        for (auto& recipe : recipes) {
            std::cout << "[Recipe] : type=" << std::get<0>(recipe) << " | " << "ingredients=";
            for (auto& ingredient : std::get<1>(recipe)) {
                std::cout << ingredient.first << ":" << ingredient.second << " ";
            }
            std::cout << "| cookTime=" <<  std::get<2>(recipe) << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}