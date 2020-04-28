/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_RECEPTION_WAITER_HPP
#define CPP_PLAZZA_2019_SRC_RECEPTION_WAITER_HPP

#include <list>
#include <string>

namespace reception {

class Waiter {
  private:
    int _key;
    std::list<std::string> _messages;

  public:
    Waiter();
    explicit Waiter(int key);
    ~Waiter();

  public:
    int getKey() const;
    std::list<std::string>& getMessages() const;

  public:
    void fetchMessages();
    void sendMessage(const std::string& message);
    std::string popMessage();
};

}

#endif // CPP_PLAZZA_2019_SRC_RECEPTION_WAITER_HPP
