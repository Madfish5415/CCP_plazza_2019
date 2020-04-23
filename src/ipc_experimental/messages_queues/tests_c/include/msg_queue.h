/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** msg_queue
*/

#ifndef MSG_QUEUE_H_
#define MSG_QUEUE_H_

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

typedef struct {
    long message_type;
    char message_text[100];
} msg_queue_t;

#endif /* !MSG_QUEUE_H_ */
