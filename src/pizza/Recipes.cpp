/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Recipes.cpp
*/

#include "Recipes.hpp"

#include <fstream>
#include <filesystem>

#include "Ingredients.hpp"

std::map<std::string, pizza::Recipe>& pizza::Recipes::_recipes()
{
    static std::map<std::string, pizza::Recipe> recipes;

    return recipes;
}

std::map<std::string, pizza::Recipe>& pizza::Recipes::get()
{
    return Recipes::_recipes();
}

void pizza::Recipes::load(const std::string& path)
{
    if (!pizza::Recipes::filewatcher(path)) {
        return;
    }

    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        Recipe recipe;

        recipe.unpack(line);

        Recipes::_recipes().emplace(recipe.getType(), recipe);

        for (const auto& ingredient : recipe.getIngredients())
            Ingredients::get().emplace(ingredient.first);
    }
}

bool pizza::Recipes::filewatcher(const std::string& path)
{
    static std::string path_to_file;
    static std::filesystem::file_time_type file_time = std::filesystem::last_write_time(path);

    if (path_to_file != path) {
        path_to_file = path;
        file_time = std::filesystem::last_write_time(path);
        return true;
    } else if (file_time != std::filesystem::last_write_time(path)) {
        file_time = std::filesystem::last_write_time(path);
        return true;
    } else {
        return false;
    }
}