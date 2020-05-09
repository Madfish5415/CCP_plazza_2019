/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include <pizza/Factory.hpp>
#include <pizza/Ingredients.hpp>
#include <pizza/Recipes.hpp>
#include <pizza/Sizes.hpp>
#include <reception/Manager.hpp>
#include <error/ErrorManager.hpp>

int main(int argc, char **argv)
{
    if (ErrorManager::check(argc, argv))
        return 84;

    kitchen::Settings settings {
        .timeMultiplier = std::stof(argv[1]),
        .cooks = static_cast<unsigned int>(std::stoi(argv[2])),
        .refillInterval = static_cast<unsigned int>(std::stoi(argv[3])),
        .maxPerCook = MAX_PER_COOK,
        .maxWaiting = MAX_WAITING
    };

    return 0;
}
