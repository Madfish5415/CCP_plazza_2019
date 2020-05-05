/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Manager.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP

#include "../kitchen/Kitchen.hpp"
#include "../pizza/Pizza.hpp"
#include "../process/Kitchen.hpp"

namespace reception {

class Manager {
  private:
    unsigned int _cooks;
    std::map<std::string, unsigned int> _ingredients;
    std::list<process::Kitchen> _kitchens;

  public:
    Manager(unsigned int cooks, const std::map<std::string, unsigned int>& ingredients);
    ~Manager();

  public:
    void handle(const pizza::Pizza& pizza);
    void manage();
    void status();

  private:
    void createKitchen();
    void updateKitchens();
    void receivePizza();
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_MANAGER_HPP
