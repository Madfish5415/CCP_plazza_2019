/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP
#define CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP

#include <mqueue.h>

#include <queue>
#include <string>

namespace communication {

class Waiter {
  private:
    std::string _name;
    mq_attr _attr {};
    int _id = 0;
    bool _created = false;

  public:
    Waiter();
    Waiter(const std::string& name, int flags);
    ~Waiter();

  public:
    int getId() const;
    std::string getName() const;

  public:
    void close();
    std::string receiveMessage(unsigned int* priority) const;
    void sendMessage(const std::string& message, unsigned int priority) const;
};

} // namespace communication

#endif // CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP
