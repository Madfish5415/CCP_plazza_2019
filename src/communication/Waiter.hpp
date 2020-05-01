/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP
#define CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <vector>
#include <string>

namespace communication {

class Waiter {
  private:
    int _id;
    std::string _name;

  public:
    Waiter(const std::string& name, int flags);
    ~Waiter();

  public:
    int getId() const { return this->_id; };
    std::string getName() const { return this->_name; };

  public:
    std::string receive() const;
    void send(const std::string &message) const;
};

} // namespace communication

#endif // CPP_PLAZZA_2019_SRC_COMMUNICATION_WAITER_HPP
