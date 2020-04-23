/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** reciever
*/

#include <unistd.h>
#include <string>
#include "../IPC.hpp"

int main(int argc, char **argv)
{
    IPC reciever(atoi(argv[1]));

    while (1) {
        reciever.lookForMessages();
        // for (auto it = reciever.getMessages().begin(); it != reciever.getMessages().end(); it++)
        //     printf("%s\n", it->c_str());
        sleep(2);
    }
}