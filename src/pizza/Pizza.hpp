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
    const PizzaType _type;
    const std::map<std::string, int> _ingredients;
    const int _cookTime;
    const PizzaSize _size;

  public:
    Pizza(PizzaType type, const std::map<std::string, int>& ingredients, int cookTime);
    ~Pizza() override;

  public:
    int getCookTime() const override;
    std::map<std::string, int>& getIngredients() const override;
    PizzaSize getSize() const override;
    PizzaType getType() const override;
    void setSize(PizzaSize) override;

  public:
    std::string pack() const override;
    void unpack(const std::string& pack) const override;
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
