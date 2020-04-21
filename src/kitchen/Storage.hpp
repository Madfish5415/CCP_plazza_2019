/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Storage.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_STORAGE_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_STORAGE_HPP

#include <map>
#include <mutex>
#include <string>

namespace kitchen {

class Storage {
    using Ingredients = std::map<std::string, int>;

  private:
    Ingredients _ingredients;
    std::mutex _mutex;

  public:
    Storage();
    ~Storage();

  public:
    void addIngredients(const Ingredients& ingredients);
    bool hasIngredients(const Ingredients& ingredients);
    void removeIngredients(const Ingredients& ingredients);

  private:
    void fill();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_STORAGE_HPP
