/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** IPizza.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PIZZA_IPIZZA_HPP
#define CPP_PLAZZA_2019_SRC_PIZZA_IPIZZA_HPP

#include <map>
#include <memory>
#include <string>

namespace pizza {

enum PizzaSize { S = 1, M = 2, L = 4, XL = 8, XXL = 16 };

enum PizzaType { Regina = 1, Margarita = 2, Americana = 4, Fantasia = 8 };

class IPizza {
  public:
    using pointer = std::shared_ptr<IPizza>;

  public:
    virtual ~IPizza() = 0;

  public:
    virtual int getCookTime() const = 0;
    virtual std::map<std::string, int>& getIngredients() const = 0;
    virtual PizzaSize getSize() const = 0;
    virtual PizzaType getType() const = 0;
    virtual void setSize(PizzaSize) = 0;

  public:
    virtual std::string pack() const = 0;
    virtual void unpack(const std::string& pack) const = 0;
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_IPIZZA_HPP
