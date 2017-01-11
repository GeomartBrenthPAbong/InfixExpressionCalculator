#include "NoArgsCommandHandler.hpp"

void gba::NoArgsCommandHandler::execute(int p_num_args, char **p_args)
{
    Calculator calculator;
    std::string input;

    do
    {
        std::cout << "Enter your infix expression:" << std::endl;

        while(std::getline(std::cin, input))
            break;

        if("q" == input)
            break;

        calculator.calculate(input);
    }
    while("q" != input);
}