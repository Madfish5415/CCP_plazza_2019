/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Pizza.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP

#include <memory>
#include <string>

#include "Recipe.hpp"

namespace pizza {

class Pizza {
  private:
    Recipe _recipe;
    std::string _size;

  public:
    Pizza();
    Pizza(Recipe recipe, std::string size);
    ~Pizza();

  public:
    const Recipe& getRecipe() const;
    std::string getSize() const;

  public:
    std::string pack() const;
    void unpack(const std::string& pack);
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
