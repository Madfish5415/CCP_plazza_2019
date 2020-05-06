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

#include "POSIX.hpp"

namespace mq {

class Waiter {
  private:
    POSIX _receiver;
    POSIX _sender;
    std::queue<std::string> _messages;

  public:
    Waiter();
    Waiter(const std::string& receiver, const std::string& sender);
    Waiter(const std::string& receiver, const std::string& sender, int flags);
    ~Waiter();

  public:
    void close();
    std::vector<std::string> receive(unsigned int* priority);
    void send(const std::vector<std::string>& message, unsigned int priority);
    void update();
};

} // namespace mq

#endif // CPP_PLAZZA_2019_SRC_MQ_WAITER_HPP
