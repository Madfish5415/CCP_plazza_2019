/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** IPC
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <vector>

typedef struct {
    long type;
    char text[256];
} message_t;

class IPC {
    public:
        IPC(int mqId = -1);
        ~IPC();

        int getMQId() const { return this->_mqId; };
        void sendMessage(std::string);
        int lookForMessages();
    protected:
    private:
        int _mqId;
        int _msgId;
        message_t _message;
        std::vector<std::string> messages;
};

#endif /* !IPC_HPP_ */
