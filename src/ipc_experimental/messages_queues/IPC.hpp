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

        int getKey() const { return this->_key; };
        void sendMessage(std::string);
        int lookForMessages();
        std::vector<std::string> getMessages() const { return this->messages; };
    protected:
    private:
        int _key;
        int _msgId;
        message_t _message;
        std::vector<std::string> messages;
};

#endif /* !IPC_HPP_ */
