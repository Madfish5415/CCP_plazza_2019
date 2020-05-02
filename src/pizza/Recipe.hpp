/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Recipe.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_RECIPE_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_RECIPE_HPP

#include <map>
#include <string>

namespace pizza {

class Recipe {
  private:
    std::string _type;
    std::map<std::string, unsigned int> _ingredients;
    int _cookTime;

  public:
    Recipe();
    Recipe(const std::string& type, const std::map<std::string, unsigned int>& ingredients, int cookTime);
    ~Recipe();

  public:
    std::string getType() const;
    const std::map<std::string, unsigned int>& getIngredients() const;
    int getCookTime() const;

  public:
    std::string pack() const;
    void unpack(const std::string& pack);
};

}

#endif // CPP_PLAZZA_2019_SRC_PIZZA_RECIPE_HPP
