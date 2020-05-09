/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Reception.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_RECEPTION_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_RECEPTION_HPP

#include "Manager.hpp"
#include "kitchen/Settings.hpp"

namespace reception {

class Reception {
  private:
    Manager _manager;
    bool _running;

  public:
    explicit Reception(const kitchen::Settings& settings, std::map<std::string, unsigned int> ingredients);
    ~Reception();

  public:
    void run();
};

} // namespace reception

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_RECEPTION_HPP
