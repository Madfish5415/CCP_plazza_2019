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

namespace mq {

class Waiter {
  private:
    POSIX _receiver;
    POSIX _sender;

  public:
    Waiter();
    Waiter(const std::string& receiver, const std::string& sender, int flag = 0);
    ~Waiter();

  public:
    void close();
    std::vector<std::string> receiveMessage(unsigned int* priority);
    void sendMessage(const std::vector<std::string>& message, unsigned int priority);
};

} // namespace mq

#endif // CPP_PLAZZA_2019_SRC_MQ_WAITER_HPP
