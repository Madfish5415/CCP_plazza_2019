/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP
#define CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP

#include <map>
#include <string>

#include "../kitchen/Kitchen.hpp"
#include "../mq/Waiter.hpp"
#include "Process.hpp"

namespace process {

class Kitchen {
  private:
    unsigned int _cooks;
    mq::Waiter _waiter;
    Process _process;
    unsigned int _pizzas = 0;
    std::chrono::time_point<std::chrono::system_clock> _last;

  public:
    Kitchen(unsigned int cooks, const std::map<std::string, unsigned int>& ingredients, const std::string& mq1,
        const std::string& mq2);
    ~Kitchen();

  public:
    unsigned int getPizzas() const;
    std::chrono::time_point<std::chrono::system_clock> getLast() const;

  public:
    bool handle(const pizza::Pizza& pizza);
    pizza::Pizza receive();
    void send(const pizza::Pizza& pizza);
    void status();
};

} // namespace process

#endif // CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP
