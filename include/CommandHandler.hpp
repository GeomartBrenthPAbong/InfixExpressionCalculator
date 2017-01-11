#ifndef COMMAND_HANDLDER_H
#define COMMAND_HANDLDER_H

#include <iostream>
#include "Calculator.hpp"

namespace gba
{

    class CommandHandler
    {
        public:
            virtual ~CommandHandler(){};

            virtual void execute(int p_num_args, char **p_args) = 0;
    };

}

#endif