/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** SystemV.cpp
*/

#include "Print.hpp"

#include "SystemV.hpp"

#include <cstring>
#include <stdexcept>

mq::SystemV::SystemV() = default;

mq::SystemV::SystemV(int key, int flags) : _key(key), _flags(flags)
{
    thread::Print() << "SystemV === Creating a new queue === " << key << std::endl;
    this->_fd = msgget(key, flags);
}

mq::SystemV::~SystemV() = default;

int mq::SystemV::getKey() const
{
    return this->_key;
}

int mq::SystemV::getFlags() const
{
    return this->_flags;
}

void mq::SystemV::close() const
{
    if (this->_flags & IPC_CREAT)
        msgctl(this->_fd, IPC_RMID, nullptr);
}

std::string mq::SystemV::receive(long *type, int flag) const
{
    data data {};

    data.type = (type) ? *type : 0;

    memset(data.message, 0, MAX_MESSAGE_SIZE);

    if (msgrcv(this->_fd, &data, MAX_MESSAGE_SIZE, data.type, flag) == -1)
        throw std::runtime_error(strerror(errno));

    if (type)
        *type = data.type;

    return data.message;
}

void mq::SystemV::send(const std::string &message, long type, int flag) const
{
    data data {};

    data.type = type;

    memset(data.message, 0, MAX_MESSAGE_SIZE);
    strncpy(data.message, message.c_str(), MAX_MESSAGE_SIZE - 1);

    if (msgsnd(this->_fd, &data, message.length(), flag) == -1)
        throw std::runtime_error(strerror(errno));
}
