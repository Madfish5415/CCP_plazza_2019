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
    unsigned int _cookTime;

  public:
    Recipe();
    Recipe(const std::string& _type, const std::map<std::string, unsigned int>& ingredients, unsigned int cookTime);
    ~Recipe();

  public:
    [[nodiscard]] std::string getType() const;
    [[nodiscard]] const std::map<std::string, unsigned int>& getIngredients() const;
    [[nodiscard]] unsigned int getCookTime() const;

  public:
    [[nodiscard]] std::string pack() const;
    void unpack(const std::string& pack);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_RECIPE_HPP
