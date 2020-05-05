/*
** EPITECH PROJECT, 2020
** CPP_plazza_lite_2019
** File description:
** POSIX.cpp
*/

#include "POSIX.hpp"

#include <mqueue.h>

#include <cstring>
#include <memory>
#include <stdexcept>
#include <utility>

mq::POSIX::POSIX() = default;

mq::POSIX::POSIX(std::string name, int flags) : _name(std::move(name)), _flags(flags)
{
    this->_fd = mq_open(this->_name.c_str(), this->_flags);
}

mq::POSIX::POSIX(std::string name, int flags, int mode, const mq::POSIX::attr& attr)
    : _name(std::move(name)), _flags(flags), _attr(attr)
{
    this->_fd = mq_open(this->_name.c_str(), this->_flags, mode, &this->_attr);
}

mq::POSIX::~POSIX() = default;

std::string mq::POSIX::getName()
{
    return this->_name;
}

mq::POSIX::attr mq::POSIX::getAttr()
{
    return this->_attr;
}

void mq::POSIX::close()
{
    mq_close(this->_fd);

    if (this->_flags & O_CREAT)
        mq_unlink(this->_name.c_str());
}

std::string mq::POSIX::receive(unsigned int* priority)
{
    auto message = std::make_unique<char[]>(this->_attr.maxMsgSize);

    memset(message.get(), 0, this->_attr.maxMsgSize);

    if (mq_receive(this->_fd, message.get(), this->_attr.maxMsgSize, priority) == -1)
        throw std::runtime_error(strerror(errno));

    return message.get();
}

void mq::POSIX::send(const std::string& message, unsigned int priority)
{
    if (mq_send(this->_fd, message.c_str(), message.length(), priority) == -1)
        throw std::runtime_error(strerror(errno));
}
