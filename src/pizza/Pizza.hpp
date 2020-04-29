/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Pizza.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP

#include "IPizza.hpp"

namespace pizza {

class Pizza : public IPizza {
  private:
    int _cookTime;
    std::map<std::string, int> _ingredients;
    std::string _size;
    std::string _type;

  public:
    ~Pizza() override;

  public:
    int getCookTime() const override;
    std::map<std::string, int>& getIngredients() const override;
    std::string getSize() const override;
    std::string getType() const override;

  public:
    std::string pack() const override;
    void unpack(const std::string& pack) const override;
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
