#ifndef NO_ARGS_COMMAND_HANDLER_H
#define NO_ARGS_COMMAND_HANDLER_H

#include "CommandHandler.hpp"

namespace gba
{

    class NoArgsCommandHandler: public CommandHandler
    {

        public:
            void execute(int p_num_args, char **p_args);

    };

}

#endif