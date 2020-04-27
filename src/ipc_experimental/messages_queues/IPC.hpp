/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** IPC
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <vector>

namespace ipc {
    class Waiter {
        public:
            Waiter(int mqId = -1);
            ~Waiter();

            int getKey() const { return this->_key; };
            void sendMessage(std::string);
            int lookForMessages();
            std::vector<std::string> getMessages() const { return this->messages; };
        protected:
        private:
            typedef struct {
                long type;
                char text[256];
            } message_t;
            int _key;
            int _msgId;
            message_t _message;
            std::vector<std::string> messages;
    };
}

#endif /* !IPC_HPP_ */
