/*
** EPITECH PROJECT, 2020
** CPP_plazza_lite_2019
** File description:
** SystemV.hpp
*/

#ifndef CPP_PLAZZA_LITE_2019_SRC_MQ_SYSTEMV_HPP
#define CPP_PLAZZA_LITE_2019_SRC_MQ_SYSTEMV_HPP

#include <sys/msg.h>
#include <sys/ipc.h>
#include <fcntl.h>

#include <string>

#define MAX_MSG_SIZE (8196)

namespace mq {

class SystemV {
  private:
    struct data {
        long type;
        char message[MAX_MSG_SIZE];
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
    int getKey() const;
    int getFlags() const;

  public:
    void close();
    std::string receive(long *type, int flag);
    void send(const std::string& message, long type, int flag);
};

}

#endif // CPP_PLAZZA_LITE_2019_SRC_MQ_SYSTEMV_HPP
