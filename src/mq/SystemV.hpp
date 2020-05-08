/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** SystemV.hpp
*/

#ifndef CPP_PLAZZA_LITE_2019_SRC_MQ_SYSTEMV_HPP
#define CPP_PLAZZA_LITE_2019_SRC_MQ_SYSTEMV_HPP

#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <string>

#include "def/max.hpp"

namespace mq {

class SystemV {
  private:
    struct data {
        long type;
        char message[MAX_MESSAGE_SIZE];
    };

  private:
    int _key {};
    int _flags {};
    int _fd {};

  public:
    SystemV();
    SystemV(int key, int flags);
    ~SystemV();

  public:
    [[nodiscard]] int getKey() const;
    [[nodiscard]] int getFlags() const;

  public:
    void close() const;
    std::string receive(long* type, int flag) const;
    void send(const std::string& message, long type, int flag) const;
};

} // namespace mq

#endif // CPP_PLAZZA_LITE_2019_SRC_MQ_SYSTEMV_HPP
