#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "TokenType.hpp"

namespace gba
{

    class Token
    {
        public:
            ~Token();

            TokenType type;
            std::string *value;
    };

}

#endif