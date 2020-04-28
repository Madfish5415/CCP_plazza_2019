/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** sender
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/msg_queue.h"

int main()
{
    msg_queue_t message;
    key_t key;
    int i = 0;
    int msgid;

    // ftok to generate unique key
    key = ftok("../main.cpp", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(456789, 0666 | IPC_CREAT);
    message.message_type = 1;

    while (i < 100) {
        printf("Write Data : ");
        asprintf(message.message_text, "%d", i++);

        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);

        // display the message
        printf("Data send is : %s \n", message.message_text);
    }

    return 0;
}