#include "WithArgsCommandHandler.hpp"

void gba::WithArgsCommandHandler::execute(int p_num_args, char **p_args)
{
    if(2 != p_num_args)
    {
        std::cout << "Invalid number of arguments." << std::endl;
        return;
    }

    Calculator calculator;
    calculator.calculate(p_args[1]);
}