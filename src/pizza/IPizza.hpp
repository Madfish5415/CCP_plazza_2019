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

class IPizza {
  public:
    using pointer = std::shared_ptr<IPizza>;

  public:
    virtual ~IPizza() = 0;

  public:
    virtual int getCookTime() const = 0;
    virtual std::map<std::string, int>& getIngredients() const = 0;
    virtual std::string getSize() const = 0;
    virtual std::string getType() const = 0;

  public:
    virtual std::string pack() const = 0;
    virtual void unpack(const std::string& pack) const = 0;
};

} // namespace pizza

#endif // CPP_PLAZZA_2019_SRC_PIZZA_IPIZZA_HPP
