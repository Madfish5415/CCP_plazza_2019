/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.cpp
*/

#include "Waiter.hpp"

#include <cstring>
#include <stdexcept>

#include "../def/def.hpp"

communication::Waiter::Waiter() = default;

communication::Waiter::Waiter(const std::string& name, int flags) : _name(name)
{
    this->_id = mq_open(name.c_str(), flags);

    if (this->_id == CODE_INVALID) {
        this->_attr.mq_maxmsg = 10;
        this->_attr.mq_msgsize = 1024;

        this->_id = mq_open(name.c_str(), O_CREAT | flags, 0666, &this->_attr);
        this->_created = true;
    }

    if (this->_id == CODE_INVALID)
        throw std::runtime_error(strerror(errno)); // TODO: Custom Error class
}

communication::Waiter::~Waiter() = default;

int communication::Waiter::getId() const
{
    return this->_id;
}

std::string communication::Waiter::getName() const
{
    return this->_name;
}

void communication::Waiter::close()
{
    mq_close(this->_id);

    if (this->_created)
        mq_unlink(this->_name.c_str());
}

std::string communication::Waiter::receiveMessage(unsigned int* priority) const
{
    char message[MAX_MESSAGE_SIZE];

    memset(message, 0, MAX_MESSAGE_SIZE);

    if (mq_receive(this->_id, message, MAX_MESSAGE_SIZE, priority) == CODE_INVALID)
        throw std::runtime_error(strerror(errno)); // TODO: Custom Error class

    return message;
}

void communication::Waiter::sendMessage(const std::string& message, unsigned int priority) const
{
    if (mq_send(this->_id, message.c_str(), message.length(), priority) == CODE_INVALID)
        throw std::runtime_error(strerror(errno)); // TODO: Custom Error class
}
