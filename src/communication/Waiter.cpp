/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Waiter.cpp
*/

#include <cstring>
#include "Waiter.hpp"

communication::Waiter::Waiter(const std::string &name, int flags) : _name(name)
{
    this->_id =  mq_open(name.c_str(), flags);
}

communication::Waiter::~Waiter()
{
    mq_close(this->_id);
}

void communication::Waiter::send(const std::string &message) const
{
    size_t message_len = strlen(message.c_str());

    mq_send(this->_id, message.c_str(), message_len, 1);
}

std::string communication::Waiter::receive() const
{
    struct mq_attr msg_attr;
    char *buff = NULL;
    std::string message;

    mq_getattr(this->_id, &msg_attr);
    mq_receive(this->_id, buff, msg_attr.mq_msgsize, NULL);
    message = buff;
    return message;
}