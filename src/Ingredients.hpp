/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Ingredients.hpp
*/

#ifndef CCP_PLAZZA_2019_INGREDIENTS_HPP
#define CCP_PLAZZA_2019_INGREDIENTS_HPP

#include <set>
#include <string>

class Ingredients {
  public:
    Ingredients() = delete;
    ~Ingredients() = delete;

  public:
    static void add(const std::string& ingredient);
    static bool has(const std::string& ingredient);
    static std::set<std::string>& get();

  private:
    static std::set<std::string>& ingredients();
};

#endif // CCP_PLAZZA_2019_INGREDIENTS_HPP
