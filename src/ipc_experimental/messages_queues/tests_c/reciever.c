/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** reciever
*/

#include <unistd.h>
#include <string.h>
#include "include/msg_queue.h"

int main() {
    msg_queue_t message;
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("../main.cpp", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(456789, 0666 | IPC_CREAT);

    // msgrcv to receive message
    while (strcmp(message.message_text, "STOP")) {
        msgrcv(msgid, &message, sizeof(message), 1, 0);

        // display the message
        printf("Data Received is : %s \n",
                        message.message_text);
        sleep(2);
    }
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}