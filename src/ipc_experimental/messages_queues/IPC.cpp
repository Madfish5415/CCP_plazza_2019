/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** IPC
*/

#include <random>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "IPC.hpp"

IPC::IPC(int mqId)
{
    this->_mqId = mqId == -1 ? rand() % 10000 : mqId;
    this->_msgId = msgget(this->_mqId, 0666 | IPC_CREAT);
}

IPC::~IPC()
{
    msgctl(this->_mqId, IPC_RMID, NULL);
}

void IPC::sendMessage(std::string message)
{
    this->_message.type = 1;
    msgsnd(this->_msgId, &message, sizeof(message), 0);
}

int IPC::lookForMessages()
{
    if (msgrcv(this->_mqId, &this->_message, sizeof(this->_message), 1, 0) == -1) {
        return (-1);
    }
    this->messages.push_back(strdup(this->_message.text));
}
