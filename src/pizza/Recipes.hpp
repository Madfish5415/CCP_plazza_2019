/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Recipes.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_RECIPES_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_RECIPES_HPP

#include <set>
#include <string>

#include "Recipe.hpp"

namespace pizza {

class Recipes {
  private:
    std::map<std::string, Recipe> _recipes;

  public:
    Recipes();
    ~Recipes();

  public:
    bool has(const std::string& recipe) const;

  public:
    void load(const std::string& path);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_RECIPES_HPP
