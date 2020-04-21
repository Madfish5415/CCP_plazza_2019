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
    const Ingredients _ingredients;
    const PizzaSize _size;
    const CookTime _cookTime;

  public:
    Pizza(PizzaType type, const Ingredients& ingredients, PizzaSize size,
        CookTime cookTime);
    ~Pizza() override;

  public:
    CookTime getCookTime() const override;
    const Ingredients & getIngredients() const override;
    PizzaSize getSize() const override;
    PizzaType getType() const override;

  public:
    std::string pack() const override;
    void unpack(const std::string &pack) const override;
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_PIZZA_HPP
