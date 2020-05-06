/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** POSIX.hpp
*/

#ifndef CPP_PLAZZA_2019_SRC_MQ_POSIX_HPP
#define CPP_PLAZZA_2019_SRC_MQ_POSIX_HPP

#include <string>

namespace mq {

class POSIX {
  public:
    class Attributes {
      public:

    };

  private:
    std::string _name;
    int _flags;
    int _mode;
    Attributes _attributes;
    int _fd;

  public:
    POSIX();
    POSIX(std::string name, int flags);
    POSIX(std::string name, int flags, int mode, const Attributes& attr);
    ~POSIX();

  public:
    std::string getName() const;
    int getFlags() const;
    int getMode() const;
    Attributes& getAttributes() const;

  public:
    void close();
    std::string receive(unsigned int *priority);
    void send(const std::string& message, unsigned int priority);
};

} // namespace mq

#endif // CPP_PLAZZA_2019_SRC_MQ_POSIX_HPP
