/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP
#define CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include "Process.hpp"
#include "kitchen/Settings.hpp"
#include "mq/Waiter.hpp"
#include "pizza/Pizza.hpp"

namespace process {

class Kitchen {
  private:
    kitchen::Settings _settings;
    mq::Waiter _waiter;
    Process _process;
    unsigned int _pending {};
    std::chrono::time_point<std::chrono::system_clock> _last;

  public:
    Kitchen(const kitchen::Settings& settings, const std::map<std::string, unsigned int>& ingredients, int receiver,
        int sender);
    ~Kitchen();

  public:
    [[nodiscard]] unsigned int getPending() const;
    [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> getLast() const;

  public:
    std::shared_ptr<pizza::Pizza> ask();
    bool handle(std::shared_ptr<pizza::Pizza> pizza);
    void status();
};

} // namespace process

#endif // CPP_PLAZZA_2019_SRC_PROCESS_KITCHEN_HPP
