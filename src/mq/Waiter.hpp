/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_MQ_WAITER_HPP
#define CPP_PLAZZA_2019_SRC_MQ_WAITER_HPP

#include <mqueue.h>

#include <queue>
#include <string>

#include "POSIX.hpp"
#include "SystemV.hpp"

namespace mq {

class Waiter {
  private:
    SystemV _receiver;
    SystemV _sender;

  public:
    Waiter();
    Waiter(int receiver, int sender);
    Waiter(int receiver, int sender, int flags);
    ~Waiter();

  public:
    void close();
    std::vector<std::string> receiveMessage(long* priority);
    void sendMessage(const std::vector<std::string>& message, long priority);
};

} // namespace mq

#endif // CPP_PLAZZA_2019_SRC_MQ_WAITER_HPP
