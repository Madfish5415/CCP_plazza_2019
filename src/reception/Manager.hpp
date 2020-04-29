/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP

#include "../kitchen/Kitchen.hpp"
#include "../pizza/IPizza.hpp"

namespace reception {

class Manager {
  private:
    std::list<kitchen::Kitchen> _kitchens;

  public:
    Manager();
    ~Manager();

  public:
    void handle(const pizza::IPizza::pointer& pizza);
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP
