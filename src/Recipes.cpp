/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Recipes.cpp
*/

#include "Recipes.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <tuple>

#include "Ingredients.hpp"

static std::tuple<std::string, std::string, std::string> splitRecipes(const std::string& line)
{
    size_t pos = 0;
    std::string delimiter = ";";
    std::string tmp = line;
    std::tuple<std::string, std::string, std::string> result;

    if ((pos = tmp.find(delimiter)) != std::string::npos) {
        std::get<0>(result) = tmp.substr(0, pos);
        tmp.erase(0, pos + delimiter.length());
    }
    if ((pos = tmp.find(delimiter)) != std::string::npos) {
        std::get<1>(result) = tmp.substr(0, pos);
        tmp.erase(0, pos + delimiter.length());
    }
    std::get<2>(result) = tmp;
    return result;
}

static bool loadName(const std::string& name, std::string& load)
{
    std::regex rgx(R"(^type=([A-Z][a-z]{2,})$)");
    std::smatch matches;

    if (std::regex_search(name, matches, rgx)) {
        load = matches[1].str();
        return true;
    } else {
        load = "";
        return false;
    }
}

static bool loadIngredient(const std::string& ingredient, std::map<std::string, unsigned int>& load)
{
    std::regex rgx(R"(^([a-zA-Z][a-zA-Z\s]*[a-zA-Z]):([1-9][0-9]*)$)");
    std::smatch matches;

    if (std::regex_search(ingredient, matches, rgx)) {

        Ingredients::add(matches[1].str());

        if (load.count(matches[1].str()) != 0) {
            load[matches[1].str()] += static_cast<unsigned int>(std::stoi(matches[2].str()));
        } else {
            load.emplace(matches[1].str(), static_cast<unsigned int>(std::stoi(matches[2].str())));
        }
        return true;
    } else {
        return false;
    }
}

static bool loadIngredients(const std::string& name, std::map<std::string, unsigned int>& load)
{
    std::regex rgx(R"(^ingredients=([a-zA-Z0-9\s:,]+)$)");
    std::smatch matches;
    size_t pos = 0;
    std::string delimiter = ",";
    std::string tmp;

    load.clear();
    if (std::regex_search(name, matches, rgx)) {
        tmp = matches[1].str();
        while ((pos = tmp.find(delimiter)) != std::string::npos) {
            if (!loadIngredient(tmp.substr(0, pos), load)) {
                load.clear();
                return false;
            }
            tmp.erase(0, pos + delimiter.length());
        }
        if (!loadIngredient(tmp, load)) {
            load.clear();
            return false;
        }
        return true;
    } else {
        return false;
    }
}

static bool loadCookTime(const std::string& cookTime, unsigned int& load)
{
    std::regex rgx(R"(^cookTime=([1-9][0-9]*)$)");
    std::smatch matches;

    if (std::regex_search(cookTime, matches, rgx)) {
        load = static_cast<unsigned int>(std::stoi(matches[1].str()));
        return true;
    } else {
        load = 0;
        return false;
    }
}

void Recipes::load(const std::string& path)
{
    std::ifstream file(path);
    std::string line;
    std::string name;
    std::string ingredients;
    std::string cookTime;
    std::tuple<std::string, std::map<std::string, unsigned int>, unsigned int> recipe;

    if (!Recipes::filewatcher(path)) {
        return;
    }

    Recipes::recipes().clear();

    while (std::getline(file, line)) {
        std::tie(name, ingredients, cookTime) = splitRecipes(line);

        if (loadName(name, std::get<0>(recipe)) &&
            loadIngredients(ingredients, std::get<1>(recipe)) &&
            loadCookTime(cookTime, std::get<2>(recipe))) {
            Recipes::recipes().emplace(recipe);
        } else {
            std::cerr << "Invalid line in \"" << path << "\" : " << line << std::endl;
        }
    }
}

bool Recipes::has(const std::string& name)
{
    for (auto& recipe : Recipes::recipes()) {
        if (std::get<0>(recipe) == name)
            return true;
    }
    return false;
}

std::set<std::tuple<std::string, std::map<std::string, unsigned int>, unsigned int>>& Recipes::get()
{
    return Recipes::recipes();
}

std::set<std::tuple<std::string, std::map<std::string, unsigned int>, unsigned int>>& Recipes::recipes()
{
    static std::set<std::tuple<std::string, std::map<std::string, unsigned int>, unsigned int>> recipes;

    return recipes;
}

bool Recipes::filewatcher(const std::string& path)
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