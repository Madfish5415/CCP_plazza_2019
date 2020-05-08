/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_MQ_WAITER_HPP
#define CPP_PLAZZA_2019_SRC_MQ_WAITER_HPP

#include <queue>
#include <string>
#include <vector>

#include "SystemV.hpp"

namespace mq {

class Waiter {
  private:
    SystemV _receiver;
    SystemV _sender;
    std::queue<std::string> _messages;

  public:
    Waiter();
    Waiter(int receiver, int sender);
    Waiter(int receiver, int sender, int flags);
    ~Waiter();

  public:
    void close() const;
    std::vector<std::string> receive(long* priority) const;
    void send(const std::vector<std::string>& message, long priority) const;
};

} // namespace mq

#endif // CPP_PLAZZA_2019_SRC_MQ_WAITER_HPP
