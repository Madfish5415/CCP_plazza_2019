/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** sender
*/

#include "include/msg_queue.h"

int main()
{
    msg_queue_t message;
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.message_type = 1;

    printf("Write Data : ");
    gets(message.message_text);

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    // display the message
    printf("Data send is : %s \n", message.message_text);

    return 0;
}