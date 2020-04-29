/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP
#define CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP

#include <queue>
#include <string>

namespace communication {

class Waiter {
  private:
    std::queue<std::string> _messages;

  public:
    Waiter();
    Waiter(int key);
    ~Waiter();

  public:
    int getKey() const;
    std::queue<std::string>& getMessages() const;

  public:
    void fetchMessages();
    std::string popMessage();
    void sendMessage(const std::string& message);
};

} // namespace communication

#endif // CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP
