/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Recipes.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_RECIPES_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_RECIPES_HPP

#include <map>
#include <string>

#include "Recipe.hpp"

namespace pizza {

class Recipes {
  private:
    static std::map<std::string, Recipe>& _recipes();

  public:
    static std::map<std::string, Recipe>& get();

  public:
    static void load(const std::string& path);

  private:
    static bool filewatcher(const std::string& path);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_RECIPES_HPP
