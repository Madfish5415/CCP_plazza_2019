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
  private:
    std::map<std::string, unsigned int> _ingredients;
    std::mutex _mutex;

  public:
    explicit Storage(const std::map<std::string, unsigned int>& ingredients);
    ~Storage();

  public:
    void addIngredients(const std::map<std::string, unsigned int>& ingredients);
    bool hasIngredients(const std::map<std::string, unsigned int>& ingredients) const;
    void removeIngredients(const std::map<std::string, unsigned int>& ingredients);
    void status() const;
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_STORAGE_HPP
