/*
** EPITECH PROJECT, 2020
** CPP_plazza_lite_2019
** File description:
** POSIX.hpp
*/

#ifndef CPP_PLAZZA_LITE_2019_SRC_MQ_POSIX_HPP
#define CPP_PLAZZA_LITE_2019_SRC_MQ_POSIX_HPP

#include <fcntl.h>

#include <string>

namespace mq {

class POSIX {
  public:
    struct attr {
        long int flags {};
        long int maxMsg {};
        long int maxMsgSize {};
        long int curMsgInQueue {};
        long int _internal[4] {};
    };

  private:
    std::string _name;
    int _flags {};
    attr _attr {};
    int _fd {};

  public:
    POSIX();
    POSIX(std::string name, int flags);
    POSIX(std::string name, int flags, int mode, const attr& attr);
    ~POSIX();

  public:
    std::string getName();
    attr getAttr();

  public:
    void close();
    std::string receive(unsigned int* priority);
    void send(const std::string& message, unsigned int priority);
};

} // namespace mq

#endif // CPP_PLAZZA_LITE_2019_SRC_MQ_POSIX_HPP
