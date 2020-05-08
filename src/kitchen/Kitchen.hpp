/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP

#include <list>
#include <map>
#include <string>

#include "Cook.hpp"
#include "Settings.hpp"
#include "Storage.hpp"
#include "mq/Waiter.hpp"

namespace kitchen {

class Kitchen {
  public:
    enum State { Working, Finished };

  private:
    Settings _settings;
    Storage _storage;
    mq::Waiter _waiter;
    State _state;
    std::list<Cook> _cooks;

  public:
    Kitchen(const Settings& settings, const std::map<std::string, unsigned int>& ingredients, int receiver, int sender);
    ~Kitchen();

  public:
    [[nodiscard]] const Settings& getSettings() const;
    Storage& getStorage();

  public:
    void ready(std::shared_ptr<pizza::Pizza> pizza);
    void status() const;

  private:
    void cook();
    std::shared_ptr<pizza::Pizza> ask();
    bool handle(std::shared_ptr<pizza::Pizza> pizza);
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_KITCHEN_HPP
