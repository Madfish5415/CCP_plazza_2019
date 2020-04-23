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

IPC::IPC(int key)
{
    this->_key = key == -1 ? rand() % 10000 : key;
    printf("%d\n", this->_key);
    this->_msgId = msgget(this->_key, 0666 | IPC_CREAT);
}

IPC::~IPC()
{
    msgctl(this->_key, IPC_RMID, NULL);
}

void IPC::sendMessage(std::string message)
{
    this->_message.type = 1;
    if (message.length() >= 256)
        return;
    strcpy(this->_message.text, message.c_str());
    msgsnd(this->_msgId, &this->_message, sizeof(this->_message), 0);
}

int IPC::lookForMessages()
{
    std::string msg;

    if (msgrcv(this->_msgId, &this->_message, sizeof(this->_message), 1, 0) == -1) {
        printf("Error");
        return (-1);
    }
    msg.assign(this->_message.text);
    printf("%s\n", this->_message.text);
    this->messages.push_back(msg);
}
