/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Storage.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_KITCHEN_STORAGE_HPP
#define CPP_PLAZZA_2019_SRC_KITCHEN_STORAGE_HPP

#include <map>
#include <mutex>
#include <string>

namespace kitchen {

class Storage {
  private:
    std::map<std::string, unsigned int> _ingredients;
    std::mutex _mutex;
    std::chrono::time_point<std::chrono::system_clock> _last;

  public:
    explicit Storage(std::map<std::string, unsigned int> ingredients);
    ~Storage();

  public:
    std::chrono::time_point<std::chrono::system_clock> getLast();

  public:
    void add(const std::map<std::string, unsigned int>& ingredients);
    bool removeHas(const std::map<std::string, unsigned int>& ingredients);
    void refill();
    void status();
};

} // namespace kitchen

#endif // CPP_PLAZZA_2019_SRC_KITCHEN_STORAGE_HPP
