#include "NoArgsCommandHandler.hpp"
#include "WithArgsCommandHandler.hpp"
#include <iostream>

int main(int p_num_args, char **p_args)
{
    gba::CommandHandler *command_handler;

    if(1 == p_num_args)
        command_handler = new gba::NoArgsCommandHandler();
    else
        command_handler = new gba::WithArgsCommandHandler();

    command_handler->execute(p_num_args, p_args);

    delete command_handler;
    command_handler = 0;

    return 0;
}